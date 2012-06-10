/**
 * @file array2d.h
 *
 * Two dimensional array classes
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_ARRAY2D_H
#define BCSLIB_ARRAY2D_H

#include <bcslib/array/aview2d.h>
#include <bcslib/array/aview2d_ops.h>
#include <bcslib/array/array1d.h>

#include <bcslib/array/transpose2d.h>
#include <cmath>

namespace bcs
{

	template<typename T, typename TOrd, class Alloc=aligned_allocator<T> > class array2d;

	template<typename T, typename TOrd, class Alloc>
	struct aview_traits<array2d<T, TOrd, Alloc> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)
	};

	template<typename T, typename TOrd, class Alloc>
	class array2d
	: public IConstContinuousAView2D<array2d<T, TOrd, Alloc>, T, TOrd>
	, public IContinuousAView2D<array2d<T, TOrd, Alloc>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
#endif
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)

		typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;
		typedef shared_block<T, Alloc> storage_type;
		typedef aview2d<T, TOrd> view_type;

	public:
		explicit array2d(index_type m, index_type n)
		: m_storage((size_t)(m * n))
		, m_view(m_storage.pbase(), m, n)
		{
		}

		explicit array2d(const shape_type& shape)
		: m_storage((size_t)(shape[0] * shape[1]))
		, m_view(m_storage.pbase(), shape[0], shape[1])
		{
		}

		array2d(index_type m, index_type n, const T& x)
		: m_storage((size_t)(m * n), x)
		, m_view(m_storage.pbase(), m, n)
		{
		}

		array2d(index_type m, index_type n, const_pointer src)
		: m_storage((size_t)(m * n), src)
		, m_view(m_storage.pbase(), m, n)
		{
		}

		array2d(const array2d& r)
		: m_storage(r.m_storage), m_view(r.m_view)
		{
		}

		template<class Derived>
		explicit array2d(const IConstRegularAView2D<Derived, T, TOrd>& r)
		: m_storage(r.size())
		, m_view(m_storage.pbase(), r.nrows(), r.ncolumns())
		{
			copy(r.derived(), *this);
		}

		array2d& operator = (const array2d& r)
		{
			if (this != &r)
			{
				m_storage = r.m_storage;
				m_view = r.m_view;
			}
			return *this;
		}

		void swap(array2d& r)
		{
			using std::swap;

			m_storage.swap(r.m_storage);
			swap(m_view, r.m_view);
		}

		bool is_unique() const
		{
			return m_storage.is_unique();
		}

		void make_unique()
		{
			m_storage.make_unique();

			index_t m = dim0();
			index_t n = dim1();
			m_view = view_type(m_storage.pbase(), m, n);
		}

		array2d deep_copy()
		{
			return array2d(dim0(), dim1(), pbase());
		}

		operator caview2d<T, TOrd>() const
		{
			return cview();
		}

		operator aview2d<T, TOrd>()
		{
			return view();
		}

		caview2d<T, TOrd> cview() const
		{
			return caview2d<T, TOrd>(pbase(), dim0(), dim1());
		}

		aview2d<T, TOrd> view()
		{
			return aview2d<T, TOrd>(pbase(), dim0(), dim1());
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return m_view.size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return m_view.nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return m_view.is_empty();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return m_view.dim0();
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return m_view.dim1();
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return m_view.nrows();
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return m_view.ncolumns();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return m_view.shape();
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return m_view.slice_extent();
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return m_view.lead_dim();
		}

	public:
		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return m_view.pbase();
		}

		BCS_ENSURE_INLINE pointer pbase()
		{
			return m_view.pbase();
		}

		BCS_ENSURE_INLINE const_reference operator[](index_type i) const
		{
			return m_view[i];
		}

		BCS_ENSURE_INLINE reference operator[](index_type i)
		{
			return m_view[i];
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return m_view(i, j);
		}

		BCS_ENSURE_INLINE reference operator() (index_type i, index_type j)
		{
			return m_view(i, j);
		}

	public:
		row_cview_type row(index_t i) const
		{
			return m_view.row(i);
		}

		row_view_type row(index_t i)
		{
			return m_view.row(i);
		}

		column_cview_type column(index_t i) const
		{
			return m_view.column(i);
		}

		column_view_type column(index_t i)
		{
			return m_view.column(i);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::cview_type
		row(index_t i, const TRange& rgn) const
		{
			return row_view(*this, i, rgn);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::view_type
		row(index_t i, const TRange& rgn)
		{
			return row_view(*this, i, rgn);
		}

		template<class TRange>
		typename _detail::slice_col_range_helper2d<value_type, layout_order, TRange>::cview_type
		column(index_t i, const TRange& rgn) const
		{
			return column_view(*this, i, rgn);
		}

		template<class TRange>
		typename _detail::slice_col_range_helper2d<value_type, layout_order, TRange>::view_type
		column(index_t i, const TRange& rgn)
		{
			return column_view(*this, i, rgn);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::cview_type
		V(const TRange0& I, const TRange1& J) const
		{
			return m_view.V(I, J);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::view_type
		V(const TRange0& I, const TRange1& J)
		{
			return m_view.V(I, J);
		}

		caview1d<T> flatten() const
		{
			return m_view.flatten();
		}

		caview1d<T> flatten()
		{
			return m_view.flatten();
		}

	private:
		storage_type m_storage;
		view_type m_view;

	}; // end class array2d


	template<typename T, typename TOrd, class Alloc>
	inline void swap(array2d<T, TOrd, Alloc>& lhs, array2d<T, TOrd, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

	template<class Derived, typename T, typename TOrd>
	inline array2d<T, TOrd> clone_array(const IConstRegularAView2D<Derived, T, TOrd>& a)
	{
		return array2d<typename Derived::value_type, typename Derived::layout_order>(a);
	}


	/******************************************************
	 *
	 *  Element selection
	 *
	 ******************************************************/

	template<class Derived, typename T, typename TOrd, class IndexSelector>
	array1d<T> select_elems(const IConstRegularAView2D<Derived, T, TOrd>& a, const IndexSelector& I, const IndexSelector& J)
	{
		index_t n = (index_t)I.size();
		check_arg(n == (index_t)J.size(), "Inconsistent selector sizes.");

		array1d<T> r(n);

		const Derived& ad = a.derived();

		for (index_t i = 0; i < n; ++i)
		{
			r[i] = ad(I[i], J[i]);
		}
		return r;
	}


	template<class Derived, typename T, typename TOrd, class IndexSelector>
	array2d<T, TOrd> select_rows(const IConstRegularAView2D<Derived, T, TOrd>& a, const IndexSelector& I)
	{
		index_t m = (index_t)I.size();
		index_t n = a.ncolumns();
		array2d<T, TOrd> r(m, n);

		const Derived& ad = a.derived();
		T* rp = r.pbase();

		if (is_same<TOrd, row_major_t>::value)
		{
			for (index_t i = 0; i < m; ++i)
			{
				index_t si = I[i];
				for (index_t j = 0; j < n; ++j)
				{
					*(rp++) = ad(si, j);
				}
			}
		}
		else
		{
			for (index_t j = 0; j < n; ++j)
			{
				for (index_t i = 0; i < m; ++i)
				{
					*(rp++) = ad(I[i], j);
				}
			}
		}

		return r;
	}


	template<class Derived, typename T, typename TOrd, class IndexSelector>
	array2d<T, TOrd> select_columns(const IConstRegularAView2D<Derived, T, TOrd>& a, const IndexSelector& J)
	{
		index_t m = a.nrows();
		index_t n = (index_t)J.size();
		array2d<T, TOrd> r(m, n);

		const Derived& ad = a.derived();
		T* rp = r.pbase();

		if (is_same<TOrd, row_major_t>::value)
		{
			for (index_t i = 0; i < m; ++i)
			{
				for (index_t j = 0; j < n; ++j)
				{
					*(rp++) = ad(i, J[j]);
				}
			}
		}
		else
		{
			for (index_t j = 0; j < n; ++j)
			{
				index_t sj = J[j];
				for (index_t i = 0; i < m; ++i)
				{
					*(rp++) = ad(i, sj);
				}
			}
		}

		return r;
	}


	template<class Derived, typename T, typename TOrd, class IndexSelectorI, class IndexSelectorJ>
	array2d<T, TOrd> select_rows_cols(const IConstRegularAView2D<Derived, T, TOrd>& a, const IndexSelectorI& I, const IndexSelectorJ& J)
	{
		index_t m = (index_t)I.size();
		index_t n = (index_t)J.size();
		array2d<T, TOrd> r(m, n);

		const Derived& ad = a.derived();
		T* rp = r.pbase();

		if (is_same<TOrd, row_major_t>::value)
		{
			for (index_t i = 0; i < m; ++i)
			{
				for (index_t j = 0; j < n; ++j)
				{
					*(rp++) = ad(I[i], J[j]);
				}
			}
		}
		else
		{
			for (index_t j = 0; j < n; ++j)
			{
				for (index_t i = 0; i < m; ++i)
				{
					*(rp++) = ad(I[i], J[j]);
				}
			}
		}

		return r;
	}


	/******************************************************
	 *
	 *  Transposition
	 *
	 ******************************************************/

	template<typename T>
	inline void transpose_matrix(const T *src, T *dst, index_t m, index_t n)
	{
		const size_t block_size = BCS_TRANSPOSITION_BLOCK_BYTES / sizeof(T);

		aligned_array<T, block_size> cache;

		if (block_size < 4)
		{
			direct_transpose_matrix(src, dst, (size_t)m, (size_t)n);
		}
		else
		{
			size_t bdim = (size_t)std::sqrt((double)block_size);
			blockwise_transpose_matrix(src, dst, (size_t)m, (size_t)n, bdim, cache.data);
		}
	}

	template<class Derived, typename T, typename TOrd>
	inline array2d<T, TOrd> transpose(const IConstContinuousAView2D<Derived, T, TOrd>& a)
	{
		array2d<T, TOrd> r(a.ncolumns(), a.nrows());

		if (is_same<typename Derived::layout_order, row_major_t>::value)
		{
			transpose_matrix(a.pbase(), r.pbase(), a.nrows(), a.ncolumns());
		}
		else
		{
			transpose_matrix(a.pbase(), r.pbase(), a.ncolumns(), a.nrows());
		}

		return r;
	}

}


#endif



