/*
 * @file key_map.h
 *
 * The mapping between keys
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_KEY_MAP_H_
#define BCSLIB_KEY_MAP_H_

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/type_traits.h>

#include <vector>
#include <map>

// macro

#define BCS_SETUP_KEYMAP_CLASS1(C, K, V) \
	template<class A1> \
	struct is_key_map<C<A1> > { static const bool value = true; }; \
	template<class A1> \
	struct key_map_traits<C<A1> > { \
		typedef typename C<A1>::K key_type; \
		typedef typename C<A1>::V value_type; \
	};

#define BCS_SETUP_KEYMAP_CLASS2(C, K, V) \
	template<class A1, class A2> \
	struct is_key_map<C<A1, A2> > { static const bool value = true; }; \
	template<class A1, class A2> \
	struct key_map_traits<C<A1, A2> > { \
		typedef typename C<A1, A2>::K key_type; \
		typedef typename C<A1, A2>::V value_type; \
	};

#define BCS_SETUP_KEYMAP_CLASS3(C, K, V) \
	template<class A1, class A2, class A3> \
	struct is_key_map<C<A1, A2, A3> > { static const bool value = true; }; \
	template<class A1, class A2, class A3> \
	struct key_map_traits<C<A1, A2, A3> > { \
		typedef typename C<A1, A2, A3>::K key_type; \
		typedef typename C<A1, A2, A3>::V value_type; \
	};

#define BCS_SETUP_KEYMAP_CLASS4(C, K, V) \
	template<class A1, class A2, class A3, class A4> \
	struct is_key_map<C<A1, A2, A3, A4> > { static const bool value = true; }; \
	template<class A1, class A2, class A3, class A4> \
	struct key_map_traits<C<A1, A2, A3, A4> > { \
		typedef typename C<A1, A2, A3, A4>::K key_type; \
		typedef typename C<A1, A2, A3, A4>::V value_type; \
	};

#define BCS_SETUP_KEYMAP_CLASS5(C, K, V) \
	template<class A1, class A2, class A3, class A4, class A5> \
	struct is_key_map<C<A1, A2, A3, A4, A5> > { static const bool value = true; }; \
	template<class A1, class A2, class A3, class A4, class A5> \
	struct key_map_traits<C<A1, A2, A3, A4, A5> > { \
		typedef typename C<A1, A2, A3, A4, A5>::K key_type; \
		typedef typename C<A1, A2, A3, A4, A5>::V value_type; \
	};



// forward declaration of some STL containers

namespace bcs
{

	/********************************************
	 *
	 *  key to index conversion
	 *
	 ********************************************/

	namespace _detail
	{
		template<typename TKey, bool IsInt, bool IsSigned> struct key_to_index_helper;

		template<typename TKey>
		struct key_to_index_helper<TKey, true, true>
		{
			BCS_ENSURE_INLINE
			static index_t to_index(const TKey& key) { return key; }
		};

		template<typename TKey>
		struct key_to_index_helper<TKey, true, false>
		{
			BCS_ENSURE_INLINE
			static index_t to_index(const TKey& key) { return (index_t)key; }
		};

		template<typename TKey>
		struct key_to_index_helper<TKey, false, false>
		{
			BCS_ENSURE_INLINE
			static index_t to_index(const TKey& key) { return key.index(); }
		};
	}


	template<typename TKey>
	struct index_convertible
	{
		static const bool value = is_integral<TKey>::value;
	};


	template<typename TKey>
	struct key_to_index
	{
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(index_convertible<TKey>::value, "TKey must be index-convertible.");
#endif

		BCS_ENSURE_INLINE
		static index_t to_index(const TKey& key)
		{
			return _detail::key_to_index_helper<TKey,
					is_integral<TKey>::value,
					is_signed<TKey>::value>::to_index(key);
		}
	};


	/********************************************
	 *
	 *  key_map concept
	 *
	 ********************************************/

	template<class T>
	struct is_key_map
	{
		static const bool value = false;
	};


	template<class T> struct key_map_traits;

	BCS_SETUP_KEYMAP_CLASS2(std::vector, size_type, value_type)
	BCS_SETUP_KEYMAP_CLASS4(std::map, size_type, value_type)

}

#endif /* KEY_MAP_H_ */
