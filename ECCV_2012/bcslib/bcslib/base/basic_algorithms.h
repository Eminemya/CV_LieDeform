/**
 * @file basic_algorithms.h
 *
 * Provide algorithms in addition to the ones in C++ standard
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif


#ifndef BCSLIB_BASIC_ALGORITHMS_H
#define BCSLIB_BASIC_ALGORITHMS_H

#include <bcslib/base/basic_defs.h>
#include <functional>
#include <algorithm>

namespace bcs
{

	// min, max, and minmax

	using std::min;
	using std::max;

	template<typename T>
	inline const T& min(const T& x, const T& y, const T& z)
	{
		return min(min(x, y), z);
	}

	template<typename T, typename Pred>
	inline const T& min(const T& x, const T& y, const T& z, Pred comp)
	{
		return min(min(x, y, comp), z, comp);
	}

	template<typename T>
	inline const T& min(const T& x, const T& y, const T& z, const T& w)
	{
		return min(min(x, y), min(z, w));
	}

	template<typename T, typename Pred>
	inline const T& min(const T& x, const T& y, const T& z, const T& w, Pred comp)
	{
		return min(min(x, y, comp), min(z, w, comp), comp);
	}

	template<typename T>
	inline const T& max(const T& x, const T& y, const T& z)
	{
		return max(max(x, y), z);
	}

	template<typename T, typename Pred>
	inline const T& max(const T& x, const T& y, const T& z, Pred comp)
	{
		return max(max(x, y, comp), z, comp);
	}

	template<typename T>
	inline const T& max(const T& x, const T& y, const T& z, const T& w)
	{
		return max(max(x, y), max(z, w));
	}

	template<typename T, typename Pred>
	const T& max(const T& x, const T& y, const T& z, const T& w, Pred comp)
	{
		return max(max(x, y, comp), max(z, w, comp), comp);
	}


	template<typename T>
	inline std::pair<T, T> minmax(const T& x, const T& y)
	{
		return y < x ? std::pair<T, T>(y, x) : std::pair<T, T>(x, y);
	}

	template<typename T, typename Pred>
	inline std::pair<T, T> minmax(const T& x, const T& y, Pred comp)
	{
		return comp(y, x) ? std::pair<T, T>(y, x) : std::pair<T, T>(x, y);
	}

	template<typename T>
	inline std::pair<T, T> minmax(const T& x, const T& y, const T& z)
	{
		std::pair<T, T> mxy = bcs::minmax(x, y);
		return std::pair<T, T>(min(mxy.first, z), max(z, mxy.second));
	}

	template<typename T, typename Pred>
	inline std::pair<T, T> minmax(const T& x, const T& y, const T& z, Pred comp)
	{
		std::pair<T, T> mxy = bcs::minmax(x, y, comp);
		return std::pair<T, T>(min(mxy.first, z, comp), max(z, mxy.second, comp));
	}

	template<typename T>
	inline std::pair<T, T> minmax(const T& x, const T& y, const T& z, const T& w)
	{
		std::pair<T, T> mxy = bcs::minmax(x, y);
		std::pair<T, T> mzw = bcs::minmax(z, w);
		return std::pair<T, T>(min(mxy.first, mzw.first), max(mzw.second, mxy.second));
	}

	template<typename T, typename Pred>
	inline std::pair<T, T> minmax(const T& x, const T& y, const T& z, const T& w, Pred comp)
	{
		std::pair<T, T> mxy = bcs::minmax(x, y, comp);
		std::pair<T, T> mzw = bcs::minmax(z, w, comp);
		return std::pair<T, T>(min(mxy.first, mzw.first, comp), max(mzw.second, mxy.second, comp));
	}


	// copy_n

	template<typename InputIterator, typename OutputIterator>
	inline void copy_n(InputIterator src, size_t n, OutputIterator dst)
	{
		for (size_t i = 0; i < n; ++i)
		{
			*(dst++) = *(src++);
		}
	}

	// zip and extract

	template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
	void zip_copy(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator dst)
	{
		for(; first1 != last1; ++first1, ++first2, ++dst)
		{
			*dst = make_pair(*first1, *first2);
		}
	}

	template<typename InputIterator, typename OutputIterator1, typename OutputIterator2>
	void dispatch_copy(InputIterator first, InputIterator last, OutputIterator1 dst1, OutputIterator2 dst2)
	{
		for(; first != last; ++first, ++dst1, ++dst2)
		{
			*dst1 = first->first;
			*dst2 = first->second;
		}
	}

	// sort

	template<typename T, typename Comp>
	inline void simple_sort(T& x, T& y, Comp comp)
	{
		using std::swap;
		if (comp(y, x)) swap(x, y);
	}

	template<typename T>
	inline void simple_sort(T& x, T& y)
	{
		simple_sort(x, y, std::less<T>());
	}

	template<typename T, typename Comp>
	inline void simple_sort(T& x, T& y, T& z, Comp comp)
	{
		using std::swap;

		if (comp(y, x)) swap(x, y);
		if (comp(z, y))
		{
			swap(y, z);
			if (comp(y, x)) swap(x, y);
		}
	}

	template<typename T>
	inline void simple_sort(T& x, T& y, T& z)
	{
		simple_sort(x, y, z, std::less<T>());
	}

	template<typename T, typename Comp>
	inline void simple_sort(T& x, T& y, T& z, T& w, Comp comp)
	{
		using std::swap;
		simple_sort(x, y, z, comp);

		if (comp(w, z))
		{
			swap(z, w);

			if (comp(z, y))
			{
				swap(y, z);
				if (comp(y, x))
				{
					swap(x, y);
				}
			}
		}
	}


	template<typename T>
	inline void simple_sort(T& x, T& y, T& z, T& w)
	{
		simple_sort(x, y, z, w, std::less<T>());
	}



	template<typename TKey, typename TValue, typename Comp=std::less<TKey> >
	struct pair_cc
	{
		Comp component_comparer;

		pair_cc() : component_comparer() { }
		pair_cc(Comp comp) : component_comparer(comp) { }

		bool operator()(const std::pair<TKey, TValue>& lhs, const std::pair<TKey, TValue>& rhs) const
		{
			return component_comparer(lhs.first, rhs.first);
		}
	};


	template<typename RandomAccessIterator, typename Comp>  // Tuple type can be pair, tuple, and array
	inline void sort_pairs_by_key(RandomAccessIterator first, RandomAccessIterator last, Comp comp)
	{
		typedef typename std::iterator_traits<RandomAccessIterator>::value_type pair_type;
		typedef typename pair_type::first_type key_type;
		typedef typename pair_type::second_type value_type;

		std::sort(first, last, pair_cc<key_type, value_type, Comp>(comp));
	}

	template<typename RandomAccessIterator>
	inline void sort_pairs_by_key(RandomAccessIterator first, RandomAccessIterator last)
	{
		typedef typename std::iterator_traits<RandomAccessIterator>::value_type pair_type;
		typedef typename pair_type::first_type key_type;

		sort_pairs_by_key(first, last, std::less<key_type>());
	}


	// accumulation

	template<class Cumulator, typename InputIterator, typename Comb>
	void cumulate(Cumulator& cumulator, InputIterator first, InputIterator last, Comb comb)
	{
		for (; first != last; ++first)
		{
			comb(cumulator, *first);
		}
	}

	template<class Cumulator, typename InputIterator, typename Comb>
	void cumulate_n(Cumulator& cumulator, InputIterator first, size_t n, Comb comb)
	{
		for(size_t i = 0; i < n; ++i, ++first)
		{
			comb(cumulator, *first);
		}
	}

}


#endif 
