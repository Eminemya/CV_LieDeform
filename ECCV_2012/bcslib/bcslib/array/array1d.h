/**
 * @file array1d.h
 *
 * one-dimensional array
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_ARRAY1D_H
#define BCSLIB_ARRAY1D_H

#include <bcslib/array/aview1d.h>
#include <bcslib/array/aview1d_ops.h>
#include <bcslib/base/block.h>

namespace bcs
{

	template<typename T, class Alloc=aligned_allocator<T> > class array1d;

	template<typename T, class Alloc>
	struct aview_traits<array1d<T, Alloc> >
	{
		BCS_AVIEW_TRAITS_DEFS(1u, T, layout_1d_t)
	};

	template<typename T, class Alloc>
	class array1d
	: public IConstContinuousAView1D<array1d<T, Alloc>, T>
	, public IContinuousAView1D<array1d<T, Alloc>, T>
	{
	public:
		BCS_AVIEW_TRAITS_DEFS(1u, T, layout_1d_t)

		typedef shared_block<T, Alloc> storage_type;
		typedef aview1d<T> view_type;

	public:
		explicit array1d(index_type n)
		: m_storage((size_t)n), m_view(m_storage.pbase(), n)
		{
		}

		explicit array1d(const shape_type& shape)
		: m_storage((size_t)(shape[0])), m_view(m_storage.pbase(), shape[0])
		{
		}

		array1d(index_type n, const value_type& x)
		: m_storage((size_t)n, x), m_view(m_storage.pbase(), n)
		{
		}

		array1d(index_type n, const_pointer src)
		: m_storage((size_t)n, src), m_view(m_storage.pbase(), n)
		{
		}

		array1d(const array1d& r)
		: m_storage(r.m_storage), m_view(r.m_view)
		{
		}

		template<class Derived>
		explicit array1d(const IConstRegularAView1D<Derived, T>& r)
		: m_storage(r.size()), m_view(m_storage.pbase(), r.nelems())
		{
			copy(r.derived(), *this);
		}

		array1d& operator = (const array1d& r)
		{
			if (this != &r)
			{
				m_storage = r.m_storage;
				m_view = r.m_view;
			}
			return *this;
		}

		void swap(array1d& r)
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

			index_t n = dim0();
			m_view = view_type(m_storage.pbase(), n);
		}

		array1d deep_copy()
		{
			return array1d(dim0(), pbase());
		}

		operator caview1d<T>() const
		{
			return cview();
		}

		operator aview1d<T>()
		{
			return view();
		}

		caview1d<T> cview() const
		{
			return caview1d<T>(pbase(), dim0());
		}

		aview1d<T> view()
		{
			return aview1d<T>(pbase(), dim0());
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

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return m_view.shape();
		}

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

		BCS_ENSURE_INLINE const_reference operator() (index_type i) const
		{
			return m_view[i];
		}

		BCS_ENSURE_INLINE reference operator() (index_type i)
		{
			return m_view[i];
		}

		template<class IndexSelector>
		typename _detail::subview_helper1d<value_type, IndexSelector>::cview_type
		V(const IndexSelector& I) const
		{
			return csubview(*this, I);
		}

		template<class IndexSelector>
		typename _detail::subview_helper1d<value_type, IndexSelector>::view_type
		V(const IndexSelector& I)
		{
			return subview(*this, I);
		}

	private:
		storage_type m_storage;
		view_type m_view;

	}; // end class array1d


	template<typename T, class Alloc>
	inline void swap(array1d<T, Alloc>& lhs, array1d<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}


	template<class Derived, typename T>
	inline array1d<T> clone_array(const IConstRegularAView1D<Derived, T>& a)
	{
		return array1d<typename Derived::value_type>(a);
	}


	/******************************************************
	 *
	 *  Element selection
	 *
	 ******************************************************/

	template<class Derived, typename T>
	inline array1d<index_t> find(const IConstRegularAView1D<Derived, T>& B)
	{
		index_t n = B.dim0();

		const Derived& Bd = B.derived();

		// count

		index_t c = 0;
		for (index_t i = 0; i < n; ++i)
		{
			if (Bd(i)) ++c;
		}
		array1d<index_t> r(c);

		// extract

		index_t k = 0;
		for(index_t i = 0; k < c; ++i)
		{
			if (Bd(i)) r[k++] = i;
		}

		return r;
	}


	// select elements from 1D array

	template<class Derived, typename T, class IndexSelector>
	inline array1d<T> select_elems(const IConstRegularAView1D<Derived, T>& a, const IndexSelector& inds)
	{
		const Derived& ad = a.derived();

		index_t n = (index_t)inds.size();
		array1d<T> r(n);

		T *pd = r.pbase();
		for (index_t i = 0; i < n; ++i)
		{
			pd[i] = ad(inds[i]);
		}

		return r;
	}

}

#endif 

