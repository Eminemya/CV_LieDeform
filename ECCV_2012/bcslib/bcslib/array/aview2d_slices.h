/**
 * @file aview2d_aux.h
 *
 * Auxiliary facilities for 2D Array slicing
 * 
 * @author Dahua Lin
 */

#ifndef AVIEW2D_AUX_H_
#define AVIEW2D_AUX_H_

#include <bcslib/array/aview1d.h>
#include <bcslib/array/aview2d_base.h>

#define BCS_AVIEW2D_SLICE_TYPEDEFS(T, TOrd) \
	typedef typename bcs::_detail::slice_helper2d<T, TOrd>::row_cview_type row_cview_type; \
	typedef typename bcs::_detail::slice_helper2d<T, TOrd>::row_view_type row_view_type; \
	typedef typename bcs::_detail::slice_helper2d<T, TOrd>::column_cview_type column_cview_type; \
	typedef typename bcs::_detail::slice_helper2d<T, TOrd>::column_view_type column_view_type;

namespace bcs
{

	/******************************************************
	 *
	 *  Slice-views
	 *
	 ******************************************************/

	namespace _detail
	{
		template<typename T, typename TOrd> struct slice_helper2d;

		template<typename T>
		struct slice_helper2d<T, row_major_t>
		{
			typedef caview1d<T> row_cview_type;
			typedef aview1d<T>  row_view_type;
			typedef caview1d_ex<T, step_ind> column_cview_type;
			typedef aview1d_ex<T, step_ind>  column_view_type;

			static row_cview_type row_cview(const T* pbase, row_extent ext, index_t d0, index_t d1, index_t irow)
			{
				return caview1d<T>(pbase + irow * ext.dim(), d1);
			}

			static row_view_type row_view(T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow)
			{
				return aview1d<T>(pbase + irow * ext.dim(), d1);
			}

			static column_cview_type column_cview(const T* pbase, row_extent ext, index_t d0, index_t d1, index_t icol)
			{
				return caview1d_ex<T, step_ind>(pbase + icol, step_ind(d0, ext.dim()));
			}

			static column_view_type column_view(T* pbase, row_extent ext, index_t d0, index_t d1, index_t icol)
			{
				return aview1d_ex<T, step_ind>(pbase + icol, step_ind(d0, ext.dim()));
			}
		};


		template<typename T>
		struct slice_helper2d<T, column_major_t>
		{
			typedef caview1d<T> column_cview_type;
			typedef aview1d<T>  column_view_type;
			typedef caview1d_ex<T, step_ind> row_cview_type;
			typedef aview1d_ex<T, step_ind>  row_view_type;

			static row_cview_type row_cview(const T* pbase, column_extent ext, index_t d0, index_t d1, index_t irow)
			{
				return caview1d_ex<T, step_ind>(pbase + irow, step_ind(d1, ext.dim()));
			}

			static row_view_type row_view(T *pbase, column_extent ext, index_t d0, index_t d1, index_t irow)
			{
				return aview1d_ex<T, step_ind>(pbase + irow, step_ind(d1, ext.dim()));
			}

			static column_cview_type column_cview(const T* pbase, column_extent ext, index_t d0, index_t d1, index_t icol)
			{
				return caview1d<T>(pbase + icol * ext.dim(), d0);
			}

			static column_view_type column_view(T* pbase, column_extent ext, index_t d0, index_t d1, index_t icol)
			{
				return aview1d<T>(pbase + icol * ext.dim(), d0);
			}
		};


		template<typename T, typename TOrd, class TRange> struct slice_row_range_helper2d;
		template<typename T, typename TOrd, class TRange> struct slice_col_range_helper2d;

		template<typename T, class TRange>
		struct slice_row_range_helper2d<T, row_major_t, TRange>
		{
			typedef caview1d_ex<T, typename indexer_map<TRange>::type> cview_type;
			typedef aview1d_ex<T, typename indexer_map<TRange>::type>  view_type;

			static cview_type cview(const T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, const TRange& rgn)
			{
				return cview_type(pbase + ext.dim() * irow + indexer_map<TRange>::get_offset(d1, rgn),
						indexer_map<TRange>::get_indexer(d1, rgn));
			}

			static view_type view(T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, const TRange& rgn)
			{
				return view_type(pbase + ext.dim() * irow + indexer_map<TRange>::get_offset(d1, rgn),
						indexer_map<TRange>::get_indexer(d1, rgn));
			}
		};

		template<typename T>
		struct slice_row_range_helper2d<T, row_major_t, whole>
		{
			typedef caview1d<T> cview_type;
			typedef aview1d<T>  view_type;

			static cview_type cview(const T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, whole)
			{
				return cview_type(pbase + ext.dim() * irow, d1);
			}

			static view_type view(T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, whole)
			{
				return view_type(pbase + ext.dim() * irow, d1);
			}
		};

		template<typename T>
		struct slice_row_range_helper2d<T, row_major_t, range>
		{
			typedef caview1d<T> cview_type;
			typedef aview1d<T>  view_type;

			static cview_type cview(const T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, const range& rgn)
			{
				return cview_type(pbase + ext.dim() * irow + rgn.begin_index(), rgn.dim());
			}

			static view_type view(T *pbase, row_extent ext, index_t d0, index_t d1, index_t irow, const range& rgn)
			{
				return view_type(pbase + ext.dim() * irow + rgn.begin_index(), rgn.dim());
			}
		};


		template<typename T, class TRange>
		struct slice_col_range_helper2d<T, row_major_t, TRange>
		{
			typedef caview1d_ex<T, typename indexer_map<TRange>::stepped_type> cview_type;
			typedef aview1d_ex<T, typename indexer_map<TRange>::stepped_type>  view_type;

			static cview_type cview(const T *pbase, row_extent ext, index_t d0, index_t d1, index_t icol, const TRange& rgn)
			{
				return cview_type(pbase + ext.dim() * indexer_map<TRange>::get_offset(d0, rgn) + icol,
						indexer_map<TRange>::get_stepped_indexer(d0, ext.dim(), rgn));
			}

			static view_type view(T *pbase, row_extent ext, index_t d0, index_t d1, index_t icol, const TRange& rgn)
			{
				return view_type(pbase + ext.dim() * indexer_map<TRange>::get_offset(d0, rgn) + icol,
						indexer_map<TRange>::get_stepped_indexer(d0, ext.dim(), rgn));
			}
		};


		template<typename T, class TRange>
		struct slice_row_range_helper2d<T, column_major_t, TRange>
		{
			typedef caview1d_ex<T, typename indexer_map<TRange>::stepped_type> cview_type;
			typedef aview1d_ex<T, typename indexer_map<TRange>::stepped_type>  view_type;

			static cview_type cview(const T *pbase, column_extent ext, index_t d0, index_t d1, index_t irow, const TRange& rgn)
			{
				return cview_type(pbase + ext.dim() * indexer_map<TRange>::get_offset(d1, rgn) + irow,
						indexer_map<TRange>::get_stepped_indexer(d1, ext.dim(), rgn));
			}

			static view_type view(T *pbase, column_extent ext, index_t d0, index_t d1, index_t irow, const TRange& rgn)
			{
				return view_type(pbase + ext.dim() * indexer_map<TRange>::get_offset(d1, rgn) + irow,
						indexer_map<TRange>::get_stepped_indexer(d1, ext.dim(), rgn));
			}
		};

		template<typename T, class TRange>
		struct slice_col_range_helper2d<T, column_major_t, TRange>
		{
			typedef caview1d_ex<T, typename indexer_map<TRange>::type> cview_type;
			typedef aview1d_ex<T, typename indexer_map<TRange>::type>  view_type;

			static cview_type cview(const T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, const TRange& rgn)
			{
				return cview_type(pbase + ext.dim() * icol + indexer_map<TRange>::get_offset(d0, rgn),
						indexer_map<TRange>::get_indexer(d0, rgn));
			}

			static view_type view(T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, const TRange& rgn)
			{
				return view_type(pbase + ext.dim() * icol + indexer_map<TRange>::get_offset(d0, rgn),
						indexer_map<TRange>::get_indexer(d0, rgn));
			}
		};

		template<typename T>
		struct slice_col_range_helper2d<T, column_major_t, whole>
		{
			typedef caview1d<T> cview_type;
			typedef aview1d<T>  view_type;

			static cview_type cview(const T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, whole)
			{
				return cview_type(pbase + ext.dim() * icol, d0);
			}

			static view_type view(T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, whole)
			{
				return view_type(pbase + ext.dim() * icol, d0);
			}
		};

		template<typename T>
		struct slice_col_range_helper2d<T, column_major_t, range>
		{
			typedef caview1d<T> cview_type;
			typedef aview1d<T>  view_type;

			static cview_type cview(const T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, const range& rgn)
			{
				return cview_type(pbase + ext.dim() * icol + rgn.begin_index(), rgn.dim());
			}

			static view_type view(T *pbase, column_extent ext, index_t d0, index_t d1, index_t icol, const range& rgn)
			{
				return view_type(pbase + ext.dim() * icol + rgn.begin_index(), rgn.dim());
			}
		};
	}


	template<class Derived, typename T, typename TOrd>
	inline typename _detail::slice_helper2d<T, TOrd>::row_cview_type
	row_cview(const IConstBlockAView2D<Derived, T, TOrd>& a, index_t irow)
	{
		typedef _detail::slice_helper2d<T, TOrd> helper;
		return helper::row_cview(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), irow);
	}

	template<class Derived, typename T, typename TOrd>
	inline typename _detail::slice_helper2d<T, TOrd>::row_view_type
	row_view(IBlockAView2D<Derived, T, TOrd>& a, index_t irow)
	{
		typedef _detail::slice_helper2d<T, TOrd> helper;
		return helper::row_view(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), irow);
	}

	template<class Derived, typename T, typename TOrd>
	inline typename _detail::slice_helper2d<T, TOrd>::column_cview_type
	column_cview(const IConstBlockAView2D<Derived, T, TOrd>& a, index_t icol)
	{
		typedef _detail::slice_helper2d<typename Derived::value_type, typename Derived::layout_order> helper;
		return helper::column_cview(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), icol);
	}

	template<class Derived, typename T, typename TOrd>
	inline typename _detail::slice_helper2d<T, TOrd>::column_view_type
	column_view(IBlockAView2D<Derived, T, TOrd>& a, index_t icol)
	{
		typedef _detail::slice_helper2d<typename Derived::value_type, typename Derived::layout_order> helper;
		return helper::column_view(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), icol);
	}


	template<class Derived, typename T, typename TOrd, class TRange>
	inline typename _detail::slice_row_range_helper2d<T, TOrd, TRange>::cview_type
	row_cview(const IConstBlockAView2D<Derived, T, TOrd>& a, index_t irow, const TRange& rgn)
	{
		typedef _detail::slice_row_range_helper2d<T, TOrd, TRange> helper;
		return helper::cview(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), irow, rgn);
	}

	template<class Derived, typename T, typename TOrd, class TRange>
	inline typename _detail::slice_row_range_helper2d<T, TOrd, TRange>::view_type
	row_view(IBlockAView2D<Derived, T, TOrd>& a, index_t irow, const TRange& rgn)
	{
		typedef _detail::slice_row_range_helper2d<T, TOrd, TRange> helper;
		return helper::view(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), irow, rgn);
	}

	template<class Derived, typename T, typename TOrd, class TRange>
	inline typename _detail::slice_col_range_helper2d<T, TOrd, TRange>::cview_type
	column_cview(const IConstBlockAView2D<Derived, T, TOrd>& a, index_t icol, const TRange& rgn)
	{
		typedef _detail::slice_col_range_helper2d<T, TOrd, TRange> helper;
		return helper::cview(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), icol, rgn);
	}

	template<class Derived, typename T, typename TOrd, class TRange>
	inline typename _detail::slice_col_range_helper2d<T, TOrd, TRange>::view_type
	column_view(IBlockAView2D<Derived, T, TOrd>& a, index_t icol, const TRange& rgn)
	{
		typedef _detail::slice_col_range_helper2d<T, TOrd, TRange> helper;
		return helper::view(a.pbase(), a.slice_extent(), a.dim0(), a.dim1(), icol, rgn);
	}

}

#endif 
