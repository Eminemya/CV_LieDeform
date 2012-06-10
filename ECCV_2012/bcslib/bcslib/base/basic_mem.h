/**
 * @file basic_mem.h
 *
 * Basic facilities for memory management
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif


#ifndef BCSLIB_BASIC_MEM_H
#define BCSLIB_BASIC_MEM_H

#include <bcslib/base/basic_mem_alloc.h>
#include <bcslib/base/type_traits.h>

#include <cstring>  	// for low-level memory manipulation functions
#include <new>   		// for std::bad_alloc

namespace bcs
{

	/********************************************
	 *
	 *	Basic memory manipulation
	 *
	 ********************************************/

	namespace _detail
	{

		/**************************************************
		 *
		 *   helpers for memory operations
		 *
		 **************************************************/

		template<typename T, bool IsTriviallyConstructible> struct _element_construct_helper;

		template<typename T>
		struct _element_construct_helper<T, true>
		{
			static void default_construct(T *, size_t) { }
		};

		template<typename T>
		struct _element_construct_helper<T, false>
		{
			static void default_construct(T *p, size_t n)
			{
				while (n --) { new (p++) T(); }
			}
		};

		template<typename T, bool IsTriviallyCopyable> struct _element_copy_helper;

		template<typename T>
		struct _element_copy_helper<T, true>
		{
			static void copy(const T *src, T *dst, size_t n)
			{
				if (n > 0) std::memcpy(dst, src, sizeof(T) * n);
			}

			static void copy_construct(const T *src, T *dst, size_t n)
			{
				if (n > 0) std::memcpy(dst, src, sizeof(T) * n);
			}

			static void copy_construct(const T& v, T *dst, size_t n)
			{
				while (n--) { *(dst++) = v; }
			}
		};

		template<typename T>
		struct _element_copy_helper<T, false>
		{
			static void copy(const T *src, T *dst, size_t n)
			{
				while (n--) { *(dst++) = *(src++); }
			}

			static void copy_construct(const T *src, T *dst, size_t n)
			{
				while (n--) { new (dst++) T(*(src++)); }
			}

			static void copy_construct(const T& v, T *dst, size_t n)
			{
				while (n--) { new (dst++) T(v); }
			}
		};


		template<typename T, bool IsTriviallyDestructible> struct _element_destruct_helper;

		template<typename T>
		struct _element_destruct_helper<T, true>
		{
			static void destruct(T *, size_t) { }
		};

		template<typename T>
		struct _element_destruct_helper<T, false>
		{
			static void destruct(T *dst, size_t n)
			{
				while (n--) { (dst++)->~T(); }
			}
		};


		template<typename T, bool IsBitwiseComparable> struct _element_compare_helper;

		template<typename T>
		struct _element_compare_helper<T, true>
		{
			static bool all_equal(const T *a, const T *b, size_t n)
			{
				return n == 0 || std::memcmp(a, b, sizeof(T) * n) == 0;
			}
		};

		template<typename T>
		struct _element_compare_helper<T, false>
		{
			static bool all_equal(const T *a, const T *b, size_t n)
			{
				for (size_t i = 0; i < n; ++i)
				{
					if (a[i] != b[i]) return false;
				}
				return true;
			}
		};
	}


	template<typename T>
	inline void default_construct_elements(T *a, size_t n)
	{
		_detail::_element_construct_helper<T, is_pod<T>::value>::default_construct(a, n);
	}


    template<typename T>
    inline void copy_construct_elements(const T& v, T *dst, size_t n)
    {
    	_detail::_element_copy_helper<T, is_pod<T>::value>::copy_construct(v, dst, n);
    }

    template<typename T>
    inline void copy_construct_elements(const T *src, T *dst, size_t n)
    {
    	_detail::_element_copy_helper<T, is_pod<T>::value>::copy_construct(src, dst, n);
    }

    template<typename T>
    inline void copy_elements(const T *src, T *dst, size_t n)
    {
    	_detail::_element_copy_helper<T, is_pod<T>::value>::copy(src, dst, n);
    }

    template<typename T>
    inline bool elements_equal(const T *a, const T *b, size_t n)
    {
    	return _detail::_element_compare_helper<T, is_scalar<T>::value>::all_equal(a, b, n);
    }

    template<typename T>
    inline bool elements_equal(const T& v, const T *a, size_t n)
    {
    	for (size_t i = 0; i < n; ++i)
    	{
    		if (a[i] != v) return false;
    	}
    	return true;
    }

    template<typename T>
    inline void set_zeros_to_elements(T *dst, size_t n)
    {
#ifdef BCS_USE_STATIC_ASSERT
    	static_assert(is_scalar<T>::value, "T should be a scalar type.");
#endif
    	if (n > 0) std::memset(dst, 0, sizeof(T) * n);
    }

    template<typename T>
    inline void fill_elements(T *dst, size_t n, const T& v)
    {
    	while (n--) { *(dst++) = v; }
    }


    template<typename T>
    inline void destruct_elements(T *dst, size_t n)
    {
    	_detail::_element_destruct_helper<T, is_pod<T>::value>::destruct(dst, n);
    }

}

#endif


