/**
 * @file aview2d_ops.h
 *
 * 2D array view based operations
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_AVIEW2D_OPS_H_
#define BCSLIB_AVIEW2D_OPS_H_

#include <bcslib/array/aview2d_base.h>
#include <bcslib/base/basic_mem.h>

namespace bcs
{
	// Comparison

	template<class LDerived, class RDerived, typename T, typename TOrd>
	inline bool is_equal(
			const IConstContinuousAView2D<LDerived, T, TOrd>& lhs,
			const IConstContinuousAView2D<RDerived, T, TOrd>& rhs)
	{
		return is_same_shape(lhs, rhs) && elements_equal(lhs.pbase(), rhs.pbase(), lhs.size());
	}


	// Import

	template<class Derived, typename T>
	inline void import_from(IRegularAView2D<Derived, T, row_major_t>& a, const T *src)
	{
		Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t i = 0; i < m; ++i)
		{
			for (index_t j = 0; j < n; ++j)
			{
				ad(i, j) = *(src++);
			}
		}
	}

	template<class Derived, typename T>
	inline void import_from(IRegularAView2D<Derived, T, column_major_t>& a, const T *src)
	{
		Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t j = 0; j < n; ++j)
		{
			for (index_t i = 0; i < m; ++i)
			{
				ad(i, j) = *(src++);
			}
		}
	}

	template<class Derived, typename T, typename TOrd>
	inline void import_from(IContinuousAView2D<Derived, T, TOrd>& a, const T *src)
	{
		copy_elements(src, a.pbase(), a.size());
	}


	// Export

	template<class Derived, typename T>
	inline void export_to(const IConstRegularAView2D<Derived, T, row_major_t>& a, T *dst)
	{
		const Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t i = 0; i < m; ++i)
		{
			for (index_t j = 0; j < n; ++j)
			{
				*(dst++) = ad(i, j);
			}
		}
	}

	template<class Derived, typename T>
	inline void export_to(const IConstRegularAView2D<Derived, T, column_major_t>& a, T *dst)
	{
		const Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t j = 0; j < n; ++j)
		{
			for (index_t i = 0; i < m; ++i)
			{
				*(dst++) = ad(i, j);
			}
		}
	}

	template<class Derived, typename T, typename TOrd>
	inline void export_to(const IConstContinuousAView2D<Derived, T, TOrd>& a, T *dst)
	{
		copy_elements(a.pbase(), dst, a.size());
	}


	// Fill

	template<class Derived, typename T>
	inline void fill(IRegularAView2D<Derived, T, row_major_t>& a, const typename Derived::value_type& v)
	{
		Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t i = 0; i < m; ++i)
		{
			for (index_t j = 0; j < n; ++j)
			{
				ad(i, j) = v;
			}
		}
	}

	template<class Derived, typename T>
	inline void fill(IRegularAView2D<Derived, T, column_major_t>& a, const typename Derived::value_type& v)
	{
		Derived& ad = a.derived();
		index_t m = a.nrows();
		index_t n = a.ncolumns();

		for (index_t j = 0; j < n; ++j)
		{
			for (index_t i = 0; i < m; ++i)
			{
				ad(i, j) = v;
			}
		}
	}

	template<class Derived, typename T, typename TOrd>
	inline void fill(IContinuousAView2D<Derived, T, TOrd>& a, const typename Derived::value_type& v)
	{
		index_t N = a.nelems();
		T *p = a.pbase();

		for (index_t i = 0; i < N; ++i)
		{
			p[i] = v;
		}
	}


	// copy

	template<class LDerived, class RDerived, typename T>
	inline void copy(const IConstRegularAView2D<LDerived, T, row_major_t>& src, IRegularAView2D<RDerived, T, row_major_t>& dst)
	{
		const LDerived& srcd = src.derived();
		RDerived& dstd = dst.derived();

		check_arg(is_same_shape(srcd, dstd), "aview2d copy: the shapes of src and dst are inconsistent.");

		index_t d0 = src.dim0();
		index_t d1 = src.dim1();

		for (index_t i = 0; i < d0; ++i)
		{
			for (index_t j = 0; j < d1; ++j)
			{
				dstd(i, j) = srcd(i, j);
			}
		}
	}

	template<class LDerived, class RDerived, typename T>
	inline void copy(const IConstRegularAView2D<LDerived, T, column_major_t>& src, IRegularAView2D<RDerived, T, column_major_t>& dst)
	{
		const LDerived& srcd = src.derived();
		RDerived& dstd = dst.derived();

		check_arg(is_same_shape(srcd, dstd), "aview2d copy: the shapes of src and dst are inconsistent.");

		index_t d0 = src.dim0();
		index_t d1 = src.dim1();

		for (index_t j = 0; j < d1; ++j)
		{
			for (index_t i = 0; i < d0; ++i)
			{
				dstd(i, j) = srcd(i, j);
			}
		}
	}


	template<class LDerived, class RDerived, typename T, typename TOrd>
	inline void copy(const IConstContinuousAView2D<LDerived, T, TOrd>& src, IContinuousAView2D<RDerived, T, TOrd>& dst)
	{
		const LDerived& srcd = src.derived();
		RDerived& dstd = dst.derived();

		check_arg(is_same_shape(srcd, dstd), "aview2d copy: the shapes of src and dst are inconsistent.");
		copy_elements(srcd.pbase(), dstd.pbase(), srcd.size());
	}

	template<class LDerived, class RDerived, typename T, typename TOrd>
	inline void copy(const IConstContinuousAView2D<LDerived, T, TOrd>& src, IRegularAView2D<RDerived, T, TOrd>& dst)
	{
		const LDerived& srcd = src.derived();
		RDerived& dstd = dst.derived();

		check_arg(is_same_shape(srcd, dstd), "aview2d copy: the shapes of src and dst are inconsistent.");
		import_from(dstd, src.pbase());
	}

	template<class LDerived, class RDerived, typename T, typename TOrd>
	inline void copy(const IConstRegularAView2D<LDerived, T, TOrd>& src, IContinuousAView2D<RDerived, T, TOrd>& dst)
	{
		const LDerived& srcd = src.derived();
		RDerived& dstd = dst.derived();

		check_arg(is_same_shape(srcd, dstd), "aview2d copy: the shapes of src and dst are inconsistent.");
		export_to(srcd, dstd.pbase());
	}

}

#endif
