/*
 * @file amap.h
 *
 * Wrap array/array-view as key-value maps
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#include <bcslib/array/array1d.h>
#include <bcslib/base/key_map.h>

#ifndef BCSLIB_AMAP_H_
#define BCSLIB_AMAP_H_

namespace bcs
{

	template<typename TKey, typename TValue>
	class caview_map
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(index_convertible<TKey>::value, "TKey must be index-convertible.");
#endif

		typedef TKey key_type;
		typedef TValue value_type;

		typedef caview1d<value_type> cview_type;
		typedef aview1d<value_type> view_type;

	public:
		caview_map(const value_type *data, index_t n)
		: m_view(data, n)
		{
		}

		caview_map(cview_type& view)
		: m_view(view)
		{
		}

		cview_type cview() const
		{
			return m_view;
		}

	public:
		// STL-like interfaces

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;

		size_type size() const
		{
			return (size_type)(m_view.nelems());
		}

		bool empty() const
		{
			return m_view.is_empty();
		}

		const_iterator begin() const
		{
			return m_view.pbase();
		}

		const_iterator end() const
		{
			return m_view.pbase() + m_view.nelems();
		}

	public:
		// key based access

		const_reference operator[] (const key_type& key) const
		{
			return m_view[key_to_index<key_type>::to_index(key)];
		}

	private:
		cview_type m_view;

	}; // end class caview_map



	template<typename TKey, typename TValue>
	class aview_map
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(index_convertible<TKey>::value, "TKey must be index-convertible.");
#endif

		typedef TKey key_type;
		typedef TValue value_type;

		typedef caview1d<value_type> cview_type;
		typedef aview1d<value_type> view_type;

	public:
		aview_map(value_type *data, index_t n)
		: m_view(data, n)
		{
		}

		aview_map(view_type& view)
		: m_view(view)
		{
		}

		view_type view()
		{
			return m_view;
		}

		cview_type cview() const
		{
			return m_view;
		}

	public:
		// STL-like interfaces

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;

		size_type size() const
		{
			return (size_type)(m_view.nelems());
		}

		bool empty() const
		{
			return m_view.is_empty();
		}

		const_iterator begin() const
		{
			return m_view.pbase();
		}

		const_iterator end() const
		{
			return m_view.pbase() + m_view.nelems();
		}

		iterator begin()
		{
			return m_view.pbase();
		}

		iterator end()
		{
			return m_view.pbase() + m_view.nelems();
		}

	public:
		// key based access

		const_reference operator[] (const key_type& key) const
		{
			return m_view[key_to_index<key_type>::to_index(key)];
		}

		reference operator[] (const key_type& key)
		{
			return m_view[key_to_index<key_type>::to_index(key)];
		}

	private:
		view_type m_view;

	}; // end class aview_map


	template<typename TKey, typename TValue>
	class array_map
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(index_convertible<TKey>::value, "TKey must be index-convertible.");
#endif

		typedef TKey key_type;
		typedef TValue value_type;

		typedef caview1d<value_type> cview_type;
		typedef aview1d<value_type> view_type;

	public:
		array_map(index_t n)
		: m_arr(n)
		{
		}

		array_map(index_t n, const value_type& v0)
		: m_arr(n, v0)
		{
		}

		array_map(index_t n, const value_type* src)
		: m_arr(n)
		{
			for (index_t i = 0; i < n; ++i)
			{
				m_arr[i] = *(src++);
			}
		}

		view_type view()
		{
			return m_arr.view();
		}

		cview_type cview() const
		{
			return m_arr.cview();
		}

	public:
		// STL-like interfaces

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;

		size_type size() const
		{
			return (size_type)(m_arr.nelems());
		}

		bool empty() const
		{
			return m_arr.is_empty();
		}

		const_iterator begin() const
		{
			return m_arr.pbase();
		}

		const_iterator end() const
		{
			return m_arr.pbase() + m_arr.nelems();
		}

		iterator begin()
		{
			return m_arr.pbase();
		}

		iterator end()
		{
			return m_arr.pbase() + m_arr.nelems();
		}

	public:
		// key based access

		const_reference operator[] (const key_type& key) const
		{
			return m_arr[key_to_index<key_type>::to_index(key)];
		}

		reference operator[] (const key_type& key)
		{
			return m_arr[key_to_index<key_type>::to_index(key)];
		}

	private:
		array1d<value_type> m_arr;

	}; // end class array_map


	BCS_SETUP_KEYMAP_CLASS2(caview_map, key_type, value_type)
	BCS_SETUP_KEYMAP_CLASS2(aview_map, key_type, value_type)
	BCS_SETUP_KEYMAP_CLASS2(array_map, key_type, value_type)
}

#endif /* GRAPH_MAP_H_ */
