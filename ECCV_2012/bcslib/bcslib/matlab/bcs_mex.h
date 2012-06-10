/**
 * @file bcs_mex.h
 *
 * The interface between bcslib and matlab mex
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_MEX_H
#define BCSLIB_MEX_H

#include <bcslib/matlab/matlab_base.h>
#include <bcslib/matlab/marray.h>

#include <bcslib/array/aview1d.h>
#include <bcslib/array/aview2d.h>
#include <bcslib/array/aview1d_ops.h>
#include <bcslib/array/aview2d_ops.h>

#include <cstring>
#include <vector>
#include <iterator>

namespace bcs {  namespace matlab {

	/********************************************
	 *
	 *  Typedefs
	 *
	 ********************************************/

	typedef caview1d<double>   cvec_f64_view;
	typedef caview1d<float>    cvec_f32_view;
	typedef caview1d<int64_t>  cvec_i64_view;
	typedef caview1d<uint64_t> cvec_u64_view;
	typedef caview1d<int32_t>  cvec_i32_view;
	typedef caview1d<uint32_t> cvec_u32_view;
	typedef caview1d<int16_t>  cvec_i16_view;
	typedef caview1d<uint16_t> cvec_u16_view;
	typedef caview1d<int8_t>   cvec_i8_view;
	typedef caview1d<uint8_t>  cvec_u8_view;

	typedef aview1d<double>   vec_f64_view;
	typedef aview1d<float>    vec_f32_view;
	typedef aview1d<int64_t>  vec_i64_view;
	typedef aview1d<uint64_t> vec_u64_view;
	typedef aview1d<int32_t>  vec_i32_view;
	typedef aview1d<uint32_t> vec_u32_view;
	typedef aview1d<int16_t>  vec_i16_view;
	typedef aview1d<uint16_t> vec_u16_view;
	typedef aview1d<int8_t>   vec_i8_view;
	typedef aview1d<uint8_t>  vec_u8_view;

	typedef caview2d<double, column_major_t>   cmat_f64_view;
	typedef caview2d<float, column_major_t>    cmat_f32_view;
	typedef caview2d<int64_t, column_major_t>  cmat_i64_view;
	typedef caview2d<uint64_t, column_major_t> cmat_u64_view;
	typedef caview2d<int32_t, column_major_t>  cmat_i32_view;
	typedef caview2d<uint32_t, column_major_t> cmat_u32_view;
	typedef caview2d<int16_t, column_major_t>  cmat_i16_view;
	typedef caview2d<uint16_t, column_major_t> cmat_u16_view;
	typedef caview2d<int8_t, column_major_t>   cmat_i8_view;
	typedef caview2d<uint8_t, column_major_t>  cmat_u8_view;

	typedef aview2d<double, column_major_t>   mat_f64_view;
	typedef aview2d<float, column_major_t>    mat_f32_view;
	typedef aview2d<int64_t, column_major_t>  mat_i64_view;
	typedef aview2d<uint64_t, column_major_t> mat_u64_view;
	typedef aview2d<int32_t, column_major_t>  mat_i32_view;
	typedef aview2d<uint32_t, column_major_t> mat_u32_view;
	typedef aview2d<int16_t, column_major_t>  mat_i16_view;
	typedef aview2d<uint16_t, column_major_t> mat_u16_view;
	typedef aview2d<int8_t, column_major_t>   mat_i8_view;
	typedef aview2d<uint8_t, column_major_t>  mat_u8_view;


	// view from marray

	template<typename T>
	inline caview1d<T> view1d(const_marray a)
	{
		return caview1d<T>(a.data<T>(), (index_t)a.nelems());
	}

	template<typename T>
	inline aview1d<T> view1d(marray a)
	{
		return aview1d<T>(a.data<T>(), (index_t)a.nelems());
	}

	template<typename T>
	inline caview2d<T, column_major_t> view2d(const_marray a)
	{
		return caview2d<T, column_major_t>(a.data<T>(), a.nrows(), a.ncolumns());
	}

	template<typename T>
	inline aview2d<T, column_major_t> view2d(marray a)
	{
		return aview2d<T, column_major_t>(a.data<T>(), a.nrows(), a.ncolumns());
	}


	// to matlab vector

	template<class Derived, typename T>
	inline marray to_matlab_row(const IConstRegularAView1D<Derived, T>& v)
	{
		marray a = create_marray<T>(1, v.nelems());
		aview1d<T> dst = view1d<T>(a);
		copy(v.derived(), dst);
		return a;
	}

	template<class Derived, typename T>
	inline marray to_matlab_column(const IConstRegularAView1D<Derived, T>& v)
	{
		marray a = create_marray<T>(v.nelems(), 1);
		aview1d<T> dst = view1d<T>(a);
		copy(v.derived(), dst);
		return a;
	}


	template<typename T>
	inline marray to_matlab_row(const std::vector<T>& v)
	{
		index_t n = (index_t)v.size();
		marray a = create_marray<T>(1, n);
		copy_elements(&(v[0]), a.data<T>(), (size_t)n);
		return a;
	}

	template<typename T>
	inline marray to_matlab_column(const std::vector<T>& v)
	{
		index_t n = (index_t)v.size();
		marray a = create_marray<T>(n, 1);
		copy_elements(&(v[0]), a.data<T>(), (size_t)n);
		return a;
	}


	template<typename TIter>
	inline marray to_matlab_row(TIter first, index_t n)
	{
		typedef typename std::iterator_traits<TIter>::value_type T;

		marray a = create_marray<T>(1, n);
		T *pa = a.data<T>();
		for (index_t i = 0; i < n; ++i) *(pa++) = *(first++);
		return a;
	}

	template<typename TIter>
	inline marray to_matlab_column(TIter first, index_t n)
	{
		typedef typename std::iterator_traits<TIter>::value_type T;

		marray a = create_marray<T>(n, 1);
		T *pa = a.data<T>();
		for (index_t i = 0; i < n; ++i) *(pa++) = *(first++);
		return a;
	}

	// to matlab matrix

	template<class Derived, typename T>
	marray to_matlab_matrix(const IConstRegularAView2D<Derived, T, column_major_t>& v)
	{
		marray a = create_marray<T>(v.nrows(), v.ncolumns());
		aview2d<T, column_major_t> dst = view2d<T>(a);
		copy(v.derived(), dst);
		return a;
	}

} }


#define BCSMEX_MAINDEF \
		void bcsmex_main(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]); \
		void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) \
		{ \
			try { \
				bcsmex_main(nlhs, plhs, nrhs, prhs); \
			} \
			catch(bcs::matlab::mexception& mexc) { \
				mexErrMsgIdAndTxt(mexc.identifier(), mexc.message()); \
			} \
		}


#endif 
