/**
 * @file aview2d.h
 *
 * The classes to represent two-dimensional views
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_AVIEW2D_H_
#define BCSLIB_AVIEW2D_H_

#include <bcslib/array/aview2d_slices.h>

namespace bcs
{

	/******************************************************
	 *
	 *  Sub-views
	 *
	 ******************************************************/

	namespace _detail
	{
		template<typename T, typename TOrd, bool IsCont, class IndexSelector0, class IndexSelector1>
		struct subview_helper2d;
	}

	template<class Derived, typename T, typename TOrd, class TRange0, class TRange1>
	inline typename _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::cview_type
	csubview(const IConstBlockAView2D<Derived, T, TOrd>& a, const TRange0& I, const TRange1& J)
	{
		return _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::cview(
				a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), I, J);
	}

	template<class Derived, typename T, typename TOrd, class TRange0, class TRange1>
	inline typename _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::view_type
	subview(IBlockAView2D<Derived, T, TOrd>& a, const TRange0& I, const TRange1& J)
	{
		return _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::view(
				a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), I, J);
	}


	template<class Derived, typename T, typename TOrd, class TRange0, class TRange1>
	inline typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::cview_type
	csubview(const IConstContinuousAView2D<Derived, T, TOrd>& a, const TRange0& I, const TRange1& J)
	{
		return _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::cview(
				a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), I, J);
	}

	template<class Derived, typename T, typename TOrd, class TRange0, class TRange1>
	inline typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::view_type
	subview(IContinuousAView2D<Derived, T, TOrd>& a, const TRange0& I, const TRange1& J)
	{
		return _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::view(
				a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), I, J);
	}


	/******************************************************
	 *
	 *  Extended Views
	 *
	 ******************************************************/

	template<typename T, typename TOrd, class TIndexer0, class TIndexer1>
	struct aview_traits<caview2d_ex<T, TOrd, TIndexer0, TIndexer1> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
	};

	template<typename T, typename TOrd, class TIndexer0, class TIndexer1>
	class caview2d_ex
	: public IConstRegularAView2D<caview2d_ex<T, TOrd, TIndexer0, TIndexer1>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
		static_assert( is_indexer<TIndexer0>::value, "TIndexer0 must be an indexer type." );
		static_assert( is_indexer<TIndexer1>::value, "TIndexer1 must be an indexer type." );
#endif

		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;
		typedef TIndexer0 indexer0_type;
		typedef TIndexer1 indexer1_type;

	public:
		caview2d_ex(const_pointer pbase, slice_extent_type ext,
				const indexer0_type& indexer0, const indexer1_type& indexer1)
		: m_pbase(const_cast<pointer>(pbase))
		, m_ext(ext)
		, m_d0(indexer0.dim())
		, m_d1(indexer1.dim())
		, m_indexer0(indexer0)
		, m_indexer1(indexer1)
		{
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return m_d0 * m_d1;
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return m_d0 == 0 || m_d1 == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return m_d0;
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return m_d1;
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(m_d0, m_d1);
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return m_ext.dim();
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return m_pbase[offset(i, j)];
		}

	protected:
		index_type offset(index_type i, index_type j) const
		{
			return m_ext.sub2ind(m_indexer0[i], m_indexer1[j]);
		}

		pointer m_pbase;
		slice_extent_type m_ext;
		index_t m_d0;
		index_t m_d1;
		indexer0_type m_indexer0;
		indexer1_type m_indexer1;

	}; // end class caview2d_ex



	template<typename T, typename TOrd, class TIndexer0, class TIndexer1>
	struct aview_traits<aview2d_ex<T, TOrd, TIndexer0, TIndexer1> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
	};

	template<typename T, typename TOrd, class TIndexer0, class TIndexer1>
	class aview2d_ex
	: public caview2d_ex<T, TOrd, TIndexer0, TIndexer1>
	, public IRegularAView2D<aview2d_ex<T, TOrd, TIndexer0, TIndexer1>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
		static_assert( is_indexer<TIndexer0>::value, "TIndexer0 must be an indexer type." );
		static_assert( is_indexer<TIndexer1>::value, "TIndexer1 must be an indexer type." );
#endif

		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;
		typedef TIndexer0 indexer0_type;
		typedef TIndexer1 indexer1_type;

	public:
		aview2d_ex(pointer pbase, slice_extent_type ext,
				const indexer0_type& indexer0, const indexer1_type& indexer1)
		: caview2d_ex<T, TOrd, TIndexer0, TIndexer1>(pbase, ext, indexer0, indexer1)
		{
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return this->m_d0 * this->m_d1;
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return this->m_d0 == 0 || this->m_d1 == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return this->m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return this->m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return this->m_d0;
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return this->m_d1;
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(this->m_d0, this->m_d1);
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return this->m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return this->m_ext.dim();
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return this->m_pbase[this->offset(i, j)];
		}

		BCS_ENSURE_INLINE reference operator() (index_type i, index_type j)
		{
			return this->m_pbase[this->offset(i, j)];
		}

	}; // end class aview2d_ex


	/******************************************************
	 *
	 *  Block views
	 *
	 ******************************************************/

	template<typename T, typename TOrd>
	struct aview_traits<caview2d_block<T, TOrd> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)
	};

	template<typename T, typename TOrd>
	class caview2d_block : public IConstBlockAView2D<caview2d_block<T, TOrd>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
#endif
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;

	public:
		caview2d_block(const_pointer pbase, slice_extent_type ext, index_type m, index_type n)
		: m_pbase(const_cast<pointer>(pbase)), m_ext(ext), m_d0(m), m_d1(n)
		{
		}

		caview2d_block(const_pointer pbase, slice_extent_type ext, const shape_type& shape)
		: m_pbase(const_cast<pointer>(pbase)), m_ext(ext), m_d0(shape[0]), m_d1(shape[1])
		{
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return dim0() * dim1();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return dim0() == 0 && dim1() == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return dim0();
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return dim1();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(dim0(), dim1());
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return m_ext.dim();
		}

	public:
		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return m_pbase;
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return m_pbase[m_ext.sub2ind(i, j)];
		}

	public:
		row_cview_type row(index_t i) const
		{
			return row_cview(*this, i);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::cview_type
		row(index_t i, const TRange& rgn) const
		{
			return row_cview(*this, i, rgn);
		}

		column_cview_type column(index_t i) const
		{
			return column_cview(*this, i);
		}

		template<class TRange>
		typename _detail::slice_col_range_helper2d<value_type, layout_order, TRange>::view_type
		column(index_t i, const TRange& rgn) const
		{
			return column_cview(*this, i, rgn);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::cview_type
		V(const TRange0& I, const TRange1& J) const
		{
			return csubview(*this, I, J);
		}

	protected:
		pointer m_pbase;
		slice_extent_type m_ext;
		index_t m_d0;
		index_t m_d1;

	}; // end class caview2d_block


	template<typename T, typename TOrd>
	struct aview_traits<aview2d_block<T, TOrd> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)
	};

	template<typename T, typename TOrd>
	class aview2d_block
	: public caview2d_block<T, TOrd>
	, public IBlockAView2D<aview2d_block<T, TOrd>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
#endif
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;

	public:
		aview2d_block(pointer pbase, slice_extent_type ext, index_type m, index_type n)
		: caview2d_block<T, TOrd>(pbase, ext, m, n)
		{
		}

		aview2d_block(pointer pbase, slice_extent_type ext, const shape_type& shape)
		: caview2d_block<T, TOrd>(pbase, ext, shape)
		{
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return dim0() * dim1();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return dim0() == 0 && dim1() == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return this->m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return this->m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return dim0();
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return dim1();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(dim0(), dim1());
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return this->m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return this->m_ext.dim();
		}

	public:
		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return this->m_pbase;
		}

		BCS_ENSURE_INLINE pointer pbase()
		{
			return this->m_pbase;
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return this->m_pbase[this->m_ext.sub2ind(i, j)];
		}

		BCS_ENSURE_INLINE reference operator() (index_type i, index_type j)
		{
			return this->m_pbase[this->m_ext.sub2ind(i, j)];
		}

	public:
		row_cview_type row(index_t i) const
		{
			return row_cview(*this, i);
		}

		row_view_type row(index_t i)
		{
			return row_view(*this, i);
		}

		column_cview_type column(index_t i) const
		{
			return column_cview(*this, i);
		}

		column_view_type column(index_t i)
		{
			return column_view(*this, i);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::cview_type
		row(index_t i, const TRange& rgn) const
		{
			return row_cview(*this, i, rgn);
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
			return column_cview(*this, i, rgn);
		}

		template<class TRange>
		typename _detail::slice_col_range_helper2d<value_type, layout_order, TRange>::view_type
		column(index_t i, const TRange& rgn)
		{
			return column_view(*this, i, rgn);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::cview_type
		V(const TRange0& I, const TRange1& J) const
		{
			return csubview(*this, I, J);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, false, TRange0, TRange1>::view_type
		V(const TRange0& I, const TRange1& J)
		{
			return subview(*this, I, J);
		}

	}; // end class aview2d_block



	/******************************************************
	 *
	 *  Continuous views
	 *
	 ******************************************************/

	template<typename T, typename TOrd>
	struct aview_traits<caview2d<T, TOrd> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)
	};

	template<typename T, typename TOrd>
	class caview2d
	: public IConstContinuousAView2D<caview2d<T, TOrd>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
#endif
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;

	public:
		caview2d(const_pointer pbase, index_type m, index_type n)
		: m_pbase(const_cast<pointer>(pbase)), m_ext(slice_extent_type::from_base_dims(m, n))
		, m_d0(m), m_d1(n)
		{
		}

		caview2d(const_pointer pbase, const shape_type& shape)
		: m_pbase(const_cast<pointer>(pbase)), m_ext(slice_extent_type::from_base_dims(shape[0], shape[1]))
		, m_d0(shape[0]), m_d1(shape[1])
		{
		}

	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return dim0() * dim1();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return dim0() == 0 && dim1() == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return dim0();
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return dim1();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(dim0(), dim1());
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return m_ext.dim();
		}

	public:
		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return m_pbase;
		}

		BCS_ENSURE_INLINE const_reference operator[](index_type i) const
		{
			return m_pbase[i];
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return m_pbase[m_ext.sub2ind(i, j)];
		}

	public:
		row_cview_type row(index_t i) const
		{
			return row_cview(*this, i);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::cview_type
		row(index_t i, const TRange& rgn) const
		{
			return row_cview(*this, i, rgn);
		}

		column_cview_type column(index_t i) const
		{
			return column_cview(*this, i);
		}

		template<class TRange>
		typename _detail::slice_col_range_helper2d<value_type, layout_order, TRange>::view_type
		column(index_t i, const TRange& rgn) const
		{
			return column_cview(*this, i, rgn);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::cview_type
		V(const TRange0& I, const TRange1& J) const
		{
			return csubview(*this, I, J);
		}

		caview1d<T> flatten() const
		{
			return caview1d<T>(pbase(), nelems());
		}

	protected:
		pointer m_pbase;
		slice_extent_type m_ext;
		index_t m_d0;
		index_t m_d1;

	}; // end class caview2d


	template<typename T, typename TOrd>
	struct aview_traits<aview2d<T, TOrd> >
	{
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)
	};

	template<typename T, typename TOrd>
	class aview2d
	: public caview2d<T, TOrd>
	, public IContinuousAView2D<aview2d<T, TOrd>, T, TOrd>
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert( is_layout_order<TOrd>::value, "TOrd must be a layout order type." );
#endif
		BCS_AVIEW_TRAITS_DEFS(2u, T, TOrd)
		BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd)

		typedef typename aview2d_slice_extent<layout_order>::type slice_extent_type;

	public:
		aview2d(pointer pbase, index_type m, index_type n)
		: caview2d<T, TOrd>(pbase, m, n)
		{
		}

		aview2d(pointer pbase, const shape_type& shape)
		: caview2d<T, TOrd>(pbase, shape)
		{
		}


	public:
		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return num_dimensions;
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return static_cast<size_type>(nelems());
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return dim0() * dim1();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return dim0() == 0 && dim1() == 0;
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return this->m_d0;
		}

		BCS_ENSURE_INLINE index_type dim1() const
		{
			return this->m_d1;
		}

		BCS_ENSURE_INLINE index_type nrows() const
		{
			return dim0();
		}

		BCS_ENSURE_INLINE index_type ncolumns() const
		{
			return dim1();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return arr_shape(dim0(), dim1());
		}

		BCS_ENSURE_INLINE slice_extent_type slice_extent() const
		{
			return this->m_ext;
		}

		BCS_ENSURE_INLINE index_type lead_dim() const
		{
			return this->m_ext.dim();
		}

	public:
		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return this->m_pbase;
		}

		BCS_ENSURE_INLINE pointer pbase()
		{
			return this->m_pbase;
		}

		BCS_ENSURE_INLINE const_reference operator[](index_type i) const
		{
			return this->m_pbase[i];
		}

		BCS_ENSURE_INLINE reference operator[](index_type i)
		{
			return this->m_pbase[i];
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i, index_type j) const
		{
			return this->m_pbase[this->m_ext.sub2ind(i, j)];
		}

		BCS_ENSURE_INLINE reference operator() (index_type i, index_type j)
		{
			return this->m_pbase[this->m_ext.sub2ind(i, j)];
		}

	public:
		row_cview_type row(index_t i) const
		{
			return row_cview(*this, i);
		}

		row_view_type row(index_t i)
		{
			return row_view(*this, i);
		}

		column_cview_type column(index_t i) const
		{
			return column_cview(*this, i);
		}

		column_view_type column(index_t i)
		{
			return column_view(*this, i);
		}

		template<class TRange>
		typename _detail::slice_row_range_helper2d<value_type, layout_order, TRange>::cview_type
		row(index_t i, const TRange& rgn) const
		{
			return row_cview(*this, i, rgn);
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
			return column_cview(*this, i, rgn);
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
			return csubview(*this, I, J);
		}

		template<class TRange0, class TRange1>
		typename _detail::subview_helper2d<T, TOrd, true, TRange0, TRange1>::view_type
		V(const TRange0& I, const TRange1& J)
		{
			return subview(*this, I, J);
		}

		caview1d<T> flatten() const
		{
			return caview1d<T>(pbase(), nelems());
		}

		aview1d<T> flatten()
		{
			return aview1d<T>(pbase(), nelems());
		}

	}; // end class aview2d


	/************************************
	 *
	 * sub-view helper implementation
	 *
	 ************************************/

	namespace _detail
	{
		template<typename T, typename TOrd, bool IsCont, class IndexSelector0, class IndexSelector1>
		struct subview_helper2d
		{
			typedef typename indexer_map<IndexSelector0>::type sindexer0_t;
			typedef typename indexer_map<IndexSelector1>::type sindexer1_t;
			typedef caview2d_ex<T, TOrd, sindexer0_t, sindexer1_t> cview_type;
			typedef aview2d_ex<T, TOrd, sindexer0_t, sindexer1_t> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const IndexSelector0& I, const IndexSelector1& J)
			{
				index_t i0 = indexer_map<IndexSelector0>::get_offset(d0, I);
				index_t j0 = indexer_map<IndexSelector1>::get_offset(d1, J);

				const T *p0 = pbase + ext.sub2ind(i0, j0);
				return cview_type(p0, ext,
						indexer_map<IndexSelector0>::get_indexer(d0, I),
						indexer_map<IndexSelector1>::get_indexer(d1, J));
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const IndexSelector0& I, const IndexSelector1& J)
			{
				index_t i0 = indexer_map<IndexSelector0>::get_offset(d0, I);
				index_t j0 = indexer_map<IndexSelector1>::get_offset(d1, J);

				T *p0 = pbase + ext.sub2ind(i0, j0);
				return view_type(p0, ext,
						indexer_map<IndexSelector0>::get_indexer(d0, I),
						indexer_map<IndexSelector1>::get_indexer(d1, J));
			}
		};


		template<typename T, typename TOrd>
		struct subview_helper2d<T, TOrd, false, whole, whole>
		{
			typedef caview2d_block<T, TOrd> cview_type;
			typedef aview2d_block<T, TOrd> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, whole)
			{
				return cview_type(pbase, ext, d0, d1);
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, whole)
			{
				return view_type(pbase, ext, d0, d1);
			}
		};

		template<typename T, typename TOrd>
		struct subview_helper2d<T, TOrd, true, whole, whole>
		{
			typedef caview2d<T, TOrd> cview_type;
			typedef aview2d<T, TOrd> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, whole)
			{
				return cview_type(pbase, d0, d1);
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, whole)
			{
				return view_type(pbase, d0, d1);
			}
		};


		template<typename T, typename TOrd, bool IsCont>
		struct subview_helper2d<T, TOrd, IsCont, whole, range>
		{
			typedef caview2d_block<T, TOrd> cview_type;
			typedef aview2d_block<T, TOrd> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, const range& J)
			{
				return cview_type(pbase + ext.sub2ind(0, J.begin_index()), ext, d0, J.dim());
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, const range& J)
			{
				return view_type(pbase + ext.sub2ind(0, J.begin_index()), ext, d0, J.dim());
			}
		};


		template<typename T>
		struct subview_helper2d<T, column_major_t, true, whole, range>
		{
			typedef caview2d<T, column_major_t> cview_type;
			typedef aview2d<T, column_major_t> view_type;
			typedef column_extent slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, const range& J)
			{
				return cview_type(pbase + d0 * J.begin_index(), d0, J.dim());
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					whole, const range& J)
			{
				return view_type(pbase + d0 * J.begin_index(), d0, J.dim());
			}
		};


		template<typename T, typename TOrd, bool IsCont>
		struct subview_helper2d<T, TOrd, IsCont, range, whole>
		{
			typedef caview2d_block<T, TOrd> cview_type;
			typedef aview2d_block<T, TOrd> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, whole)
			{
				return cview_type(pbase + ext.sub2ind(I.begin_index(), 0), ext, I.dim(), d1);
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, whole)
			{
				return view_type(pbase + ext.sub2ind(I.begin_index(), 0), ext, I.dim(), d1);
			}
		};


		template<typename T>
		struct subview_helper2d<T, row_major_t, true, range, whole>
		{
			typedef caview2d<T, row_major_t> cview_type;
			typedef aview2d<T, row_major_t> view_type;
			typedef row_extent slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, whole)
			{
				return cview_type(pbase + I.begin_index() * d1, I.dim(), d1);
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, whole)
			{
				return view_type(pbase + I.begin_index() * d1, I.dim(), d1);
			}
		};


		template<typename T, typename TOrd, bool IsCont>
		struct subview_helper2d<T, TOrd, IsCont, range, range>
		{
			typedef caview2d_block<T, TOrd> cview_type;
			typedef aview2d_block<T, TOrd> view_type;
			typedef typename aview2d_slice_extent<TOrd>::type slice_extent_type;

			static cview_type cview(const T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, const range& J)
			{
				return cview_type(pbase + ext.sub2ind(I.begin_index(), J.begin_index()),
						ext, I.dim(), J.dim());
			}

			static view_type view(T *pbase, slice_extent_type ext, index_t d0, index_t d1,
					const range& I, const range& J)
			{
				return view_type(pbase + ext.sub2ind(I.begin_index(), J.begin_index()),
						ext, I.dim(), J.dim());
			}
		};

	}


	/************************************
	 *
	 *  Convenient functions
	 *
	 ************************************/

	template<typename T>
	inline caview2d<T, row_major_t> make_caview2d_rm(const T *base, index_t m, index_t n)
	{
		return caview2d<T, row_major_t>(base, m, n);
	}

	template<typename T>
	inline aview2d<T, row_major_t> make_aview2d_rm(T *base, index_t m, index_t n)
	{
		return aview2d<T, row_major_t>(base, m, n);
	}

	template<typename T>
	inline caview2d<T, column_major_t> make_caview2d_cm(const T *base, index_t m, index_t n)
	{
		return caview2d<T, column_major_t>(base, m, n);
	}

	template<typename T>
	inline aview2d<T, column_major_t> make_aview2d_cm(T *base, index_t m, index_t n)
	{
		return aview2d<T, column_major_t>(base, m, n);
	}

	template<typename T, class TIndexer0, class TIndexer1>
	inline caview2d_ex<T, row_major_t, TIndexer0, TIndexer1> make_caview2d_ex_rm(
			const T *base, index_t m, index_t n, const TIndexer0& idx0, const TIndexer1& idx1)
	{
		return caview2d_ex<T, row_major_t, TIndexer0, TIndexer1>(base, row_extent::from_base_dims(m, n), idx0, idx1);
	}

	template<typename T, class TIndexer0, class TIndexer1>
	inline aview2d_ex<T, row_major_t, TIndexer0, TIndexer1> make_aview2d_ex_rm(
			T *base, index_t m, index_t n, const TIndexer0& idx0, const TIndexer1& idx1)
	{
		return aview2d_ex<T, row_major_t, TIndexer0, TIndexer1>(base, row_extent::from_base_dims(m, n), idx0, idx1);
	}

	template<typename T, class TIndexer0, class TIndexer1>
	inline caview2d_ex<T, column_major_t, TIndexer0, TIndexer1> make_caview2d_ex_cm(
			const T *base, index_t m, index_t n, const TIndexer0& idx0, const TIndexer1& idx1)
	{
		return caview2d_ex<T, column_major_t, TIndexer0, TIndexer1>(base, column_extent::from_base_dims(m, n), idx0, idx1);
	}

	template<typename T, class TIndexer0, class TIndexer1>
	inline aview2d_ex<T, column_major_t, TIndexer0, TIndexer1> make_aview2d_ex_cm(
			T *base, index_t m, index_t n, const TIndexer0& idx0, const TIndexer1& idx1)
	{
		return aview2d_ex<T, column_major_t, TIndexer0, TIndexer1>(base, column_extent::from_base_dims(m, n), idx0, idx1);
	}
}

#endif
