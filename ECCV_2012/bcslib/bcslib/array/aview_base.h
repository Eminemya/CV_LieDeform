/**
 * @file aview_base.h
 *
 * Basic definitions for array classes
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_AVIEW_BASE_H
#define BCSLIB_AVIEW_BASE_H

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/arg_check.h>



#define BCS_AVIEW_TRAITS_DEFS(nd, T, lorder) \
	static const dim_num_t num_dimensions = nd; \
	typedef array_shape_t<nd> shape_type; \
	typedef T value_type; \
	typedef T* pointer; \
	typedef const T* const_pointer; \
	typedef T& reference; \
	typedef const T& const_reference; \
	typedef size_t size_type; \
	typedef index_t difference_type; \
	typedef index_t index_type; \
	typedef lorder layout_order;

#define BCS_AVIEW_INTERFACE_DEFS(Derived) \
	static const dim_num_t num_dimensions = aview_traits<Derived>::num_dimensions; \
	typedef typename aview_traits<Derived>::value_type value_type; \
	typedef typename aview_traits<Derived>::layout_order layout_order; \
	typedef typename aview_traits<Derived>::pointer pointer; \
	typedef typename aview_traits<Derived>::const_pointer const_pointer; \
	typedef typename aview_traits<Derived>::reference reference; \
	typedef typename aview_traits<Derived>::const_reference const_reference; \
	typedef typename aview_traits<Derived>::size_type size_type; \
	typedef typename aview_traits<Derived>::index_type index_type; \
	typedef typename aview_traits<Derived>::shape_type shape_type; \
	BCS_ENSURE_INLINE const Derived& derived() const { return *(static_cast<const Derived*>(this)); } \
	BCS_ENSURE_INLINE Derived& derived() { return *(static_cast<Derived*>(this)); }


namespace bcs
{
	typedef uint8_t dim_num_t;

	/**********************************
	 *
	 *  array shapes
	 *
	 **********************************/

	template<dim_num_t D>
	struct array_shape_t
	{
		static const dim_num_t num_dimensions = D;

		index_t dim[D];

		dim_num_t ndims() const
		{
			return num_dimensions;
		}

		index_t operator[] (const dim_num_t& i) const
		{
			return dim[i];
		}
	};

	inline bool operator == (const array_shape_t<1>& a, const array_shape_t<1>& b)
	{
		return a[0] == b[0];
	}

	inline bool operator == (const array_shape_t<2>& a, const array_shape_t<2>& b)
	{
		return a[0] == b[0] && a[1] == b[1];
	}

	inline bool operator == (const array_shape_t<3>& a, const array_shape_t<3>& b)
	{
		return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
	}

	template<dim_num_t D>
	inline bool operator != (const array_shape_t<D>& a, const array_shape_t<D>& b)
	{
		return !(a == b);
	}


	inline array_shape_t<1> arr_shape(index_t d0)
	{
		array_shape_t<1> shape;
		shape.dim[0] = d0;
		return shape;
	}

	inline array_shape_t<2> arr_shape(index_t d0, index_t d1)
	{
		array_shape_t<2> shape;
		shape.dim[0] = d0;
		shape.dim[1] = d1;
		return shape;
	}

	inline array_shape_t<3> arr_shape(index_t d0, index_t d1, index_t d2)
	{
		array_shape_t<3> shape;
		shape.dim[0] = d0;
		shape.dim[1] = d1;
		shape.dim[2] = d2;
		return shape;
	}


	/********************************************
	 *
	 *   Array form, access, and layout
	 *
	 ********************************************/

	struct layout_1d_t { };
	struct row_major_t { };
	struct column_major_t { };

	template<class T> struct is_layout_order { static const bool value = false; };
	template<> struct is_layout_order<layout_1d_t> { static const bool value = true; };
	template<> struct is_layout_order<row_major_t> { static const bool value = true; };
	template<> struct is_layout_order<column_major_t> { static const bool value = true; };


	/********************************************
	 *
	 *   Forward declarations of specific
	 *
	 *   array classes
	 *
	 ********************************************/

	template<class AViewClass> struct aview_traits;

	// 1D

	template<class Derived, typename T> class IConstAView1DBase;
	template<class Derived, typename T> class IAView1DBase;
	template<class Derived, typename T> class IConstRegularAView1D;
	template<class Derived, typename T> class IRegularAView1D;
	template<class Derived, typename T> class IConstContinuousAView1D;
	template<class Derived, typename T> class IContinuousAView1D;

	template<typename T> class caview1d;
	template<typename T> class aview1d;

	template<typename T, class TIndexer> class caview1d_ex;
	template<typename T, class TIndexer> class aview1d_ex;

	// 2D

	template<class Derived, typename T, typename TOrd> class IConstAView2DBase;
	template<class Derived, typename T, typename TOrd> class IAView2DBase;
	template<class Derived, typename T, typename TOrd> class IConstRegularAView2D;
	template<class Derived, typename T, typename TOrd> class IRegularAView2D;
	template<class Derived, typename T, typename TOrd> class IConstBlockAView2D;
	template<class Derived, typename T, typename TOrd> class IBlockAView2D;
	template<class Derived, typename T, typename TOrd> class IConstContinuousAView2D;
	template<class Derived, typename T, typename TOrd> class IContinuousAView2D;

	template<typename T, typename TOrd> class caview2d;
	template<typename T, typename TOrd> class aview2d;

	template<typename T, typename TOrd> class caview2d_block;
	template<typename T, typename TOrd> class aview2d_block;

	template<typename T, typename TOrd, class TIndexer0, class TIndexer1> class caview2d_ex;
	template<typename T, typename TOrd, class TIndexer0, class TIndexer1> class aview2d_ex;

}

#endif
