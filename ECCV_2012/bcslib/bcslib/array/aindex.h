/**
 * @file aindex.h
 *
 * The indexer classes for array element accessing
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_AINDEX_H
#define BCSLIB_AINDEX_H

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/iterator_wrappers.h>

namespace bcs
{
	/*****
	 *
	 *  The Concept of index selector.
	 *  --------------------------------
	 *
	 *  Let S be an index selector. It should support:
	 *
	 *  - typedefs of the following types:
	 *    - value_type (implicitly convertible to index_t)
	 *    - index_type (index_t)
	 *    - size_type (size_t)
	 *    - const_iterator: of concept forward_iterator
	 *
	 *  - copy-constructible and/or move-constructible
	 *
	 *  - S.size() -> the number of indices, of type size_type
	 *  - S.dim() -> the number of indices, of type index_type
	 *  - S[i] -> the i-th selected index (i is of index_t type)
	 *  - S.begin() -> the beginning iterator, of type const_iterator
	 *  - S.end() -> the pass-by-end iterator, of type const_iterator
	 *
	 *  - is_index_selector<S>::value is explicitly specialized as true.
	 *    (By default, it is false)
	 */


	// forward declarations

	class range;
	class step_range;
	class rep_range;

	template<class T> struct is_index_selector { static const bool value = false; };

	template<> struct is_index_selector<range> { static const bool value = true; };
	template<> struct is_index_selector<step_range> { static const bool value = true; };
	template<> struct is_index_selector<rep_range> { static const bool value = true; };

	struct whole { };
	struct rev_whole { };

	/***************************************
	 *
	 *  range class
	 *
	 ***************************************/

	namespace _detail
	{
		class _range_iter_impl
		{
		public:
			typedef index_t value_type;
			typedef const index_t& reference;
			typedef const index_t* pointer;

			_range_iter_impl() :
				m_idx(0)
			{
			}

			_range_iter_impl(const index_t& i) :
				m_idx(i)
			{
			}

			void move_next()
			{
				++m_idx;
			}

			pointer ptr() const
			{
				return &m_idx;
			}

			reference ref() const
			{
				return m_idx;
			}

			bool operator ==(const _range_iter_impl& rhs) const
			{
				return m_idx == rhs.m_idx;
			}

		private:
			index_t m_idx;

		}; // end _range_iter_impl
	}

	class range
	{
	public:
		typedef index_t value_type;
		typedef size_t size_type;
		typedef index_t index_type;
		typedef forward_iterator_wrapper<_detail::_range_iter_impl> const_iterator;

	public:
		range()
		: m_begin(0), m_end(0)
		{
		}

		range(index_t b, index_t e)
		: m_begin(b), m_end(e)
		{
		}

		BCS_ENSURE_INLINE index_t begin_index() const
		{
			return m_begin;
		}

		BCS_ENSURE_INLINE index_t end_index() const
		{
			return m_end;
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_begin < m_end ? m_end - m_begin : 0;
		}

		BCS_ENSURE_INLINE size_t size() const
		{
			return static_cast<size_t>(dim());
		}

		BCS_ENSURE_INLINE index_t operator[] (const index_t& i) const
		{
			return m_begin + i;
		}

		BCS_ENSURE_INLINE index_t front() const
		{
			return m_begin;
		}

		BCS_ENSURE_INLINE index_t back() const
		{
			return m_end - 1;
		}

		const_iterator begin() const
		{
			return _detail::_range_iter_impl(begin_index());
		}

		const_iterator end() const
		{
			return _detail::_range_iter_impl(end_index());
		}

		bool operator == (const range& rhs) const
		{
			return m_begin == rhs.m_begin && m_end == rhs.m_end;
		}

		bool operator != (const range& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		index_t m_begin;
		index_t m_end;

	}; // end class range


	/***************************************
	 *
	 *  step range class
	 *
	 ***************************************/

	namespace _detail
	{
		class _step_range_iter_impl
		{
		public:
			typedef index_t value_type;
			typedef const index_t& reference;
			typedef const index_t* pointer;

			_step_range_iter_impl() :
				m_idx(0), m_step(1)
			{
			}

			_step_range_iter_impl(const index_t& i, const index_t& s) :
				m_idx(i), m_step(s)
			{
			}

			void move_next()
			{
				m_idx += m_step;
			}

			pointer ptr() const
			{
				return &m_idx;
			}

			reference ref() const
			{
				return m_idx;
			}

			bool operator ==(const _step_range_iter_impl& rhs) const
			{
				return m_idx == rhs.m_idx;
			}

		private:
			index_t m_idx;
			index_t m_step;

		}; // end _step_range_iter_impl
	}

	class step_range
	{
	public:
		typedef index_t value_type;
		typedef size_t size_type;
		typedef index_t index_type;
		typedef forward_iterator_wrapper<_detail::_step_range_iter_impl> const_iterator;

	public:
		step_range()
		: m_begin(0), m_n(0), m_step(0)
		{
		}

	private:
		step_range(index_t b, index_t n, index_t step)
		: m_begin(b), m_n(n), m_step(step)
		{
		}

	public:
		static step_range from_begin_end(index_t b, index_t e, index_t step)
		{
			return step_range(b, _calc_n(b, e, step), step);
		}

		static step_range from_begin_dim(index_t b, index_t n, index_t step)
		{
			return step_range(b, n, step);
		}


	public:
		BCS_ENSURE_INLINE index_t begin_index() const
		{
			return m_begin;
		}

		BCS_ENSURE_INLINE index_t end_index() const
		{
			return m_begin + m_n * m_step;
		}

		BCS_ENSURE_INLINE index_t step() const
		{
			return m_step;
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_n;
		}

		BCS_ENSURE_INLINE size_t size() const
		{
			return static_cast<size_t>(m_n);
		}

		BCS_ENSURE_INLINE index_t operator[] (const index_t& i) const
		{
			return m_begin + i * m_step;
		}

		BCS_ENSURE_INLINE index_t front() const
		{
			return m_begin;
		}

		BCS_ENSURE_INLINE index_t back() const
		{
			return m_begin + (m_n - 1) * m_step;
		}

		const_iterator begin() const
		{
			return _detail::_step_range_iter_impl(begin_index(), step());
		}

		const_iterator end() const
		{
			return _detail::_step_range_iter_impl(end_index(), step());
		}

		bool operator == (const step_range& rhs) const
		{
			return m_begin == rhs.m_begin && m_n == rhs.m_n && m_step == rhs.m_step;
		}

		bool operator != (const step_range& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		static index_t _calc_n(index_t b, index_t e, index_t step)
		{
            return step > 0 ?
            		((e > b) ? ((e - b - 1) / step + 1) : 0) :
            		((e < b) ? ((e - b + 1) / step + 1) : 0);
		}

	private:
		index_t m_begin;
		index_t m_n;
		index_t m_step;

	}; // end class step_range


	/***************************************
	 *
	 *  rep range class
	 *
	 ***************************************/

	namespace _detail
	{
		class _rep_iter_impl
		{
		public:
			typedef index_t value_type;
			typedef const index_t& reference;
			typedef const index_t* pointer;

			_rep_iter_impl() :
				m_index(0), m_i(0)
			{
			}

			_rep_iter_impl(const index_t& idx, const index_t& i) :
				m_index(idx), m_i(i)
			{
			}

			void move_next()
			{
				++m_i;
			}

			pointer ptr() const
			{
				return &m_index;
			}

			reference ref() const
			{
				return m_index;
			}

			bool operator ==(const _rep_iter_impl& rhs) const
			{
				return m_i == rhs.m_i;
			}

		private:
			index_t m_index;
			index_t m_i;

		}; // end _rep_iter_impl
	}

	class rep_range
	{
	public:
		typedef index_t value_type;
		typedef size_t size_type;
		typedef index_t index_type;
		typedef forward_iterator_wrapper<_detail::_rep_iter_impl> const_iterator;

	public:
		rep_range()
		: m_index(0), m_n(0)
		{
		}

		rep_range(index_t index, index_t n)
		: m_index(index), m_n(n)
		{
		}

		BCS_ENSURE_INLINE index_t index() const
		{
			return m_index;
		}

		BCS_ENSURE_INLINE size_t size() const
		{
			return static_cast<size_t>(m_n);
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_n;
		}

		BCS_ENSURE_INLINE index_t operator[] (const index_t& i) const
		{
			return m_index;
		}

		const_iterator begin() const
		{
			return _detail::_rep_iter_impl(m_index, 0);
		}

		const_iterator end() const
		{
			return _detail::_rep_iter_impl(m_index, m_n);
		}

		bool operator == (const rep_range& rhs) const
		{
			return m_index == rhs.m_index && m_n == rhs.m_n;
		}

		bool operator != (const rep_range& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		index_t m_index;
		index_t m_n;

	}; // end class rep_range


	// convenient functions for constructing regular selector

	inline range rgn(index_t dim, whole)
	{
		return range(0, dim);
	}

	inline step_range rgn(index_t dim, rev_whole)
	{
		return step_range::from_begin_dim(dim-1, dim, -1);
	}

	inline range rgn(index_t begin_index, index_t end_index)
	{
		return range(begin_index, end_index);
	}

	inline step_range rgn(index_t begin_index, index_t end_index, index_t step)
	{
		return step_range::from_begin_end(begin_index, end_index, step);
	}

	inline range rgn_n(index_t begin_index, index_t n)
	{
		return range(begin_index, begin_index + n);
	}

	inline step_range rgn_n(index_t begin_index, index_t n, index_t step)
	{
		return step_range::from_begin_dim(begin_index, n, step);
	}

	inline rep_range rep(index_t index, index_t repeat_times)
	{
		return rep_range(index, repeat_times);
	}


	/******************************************************
	 *
	 *  Indexer classes
	 *
	 ******************************************************/

	/*****
	 *
	 *  The Concept of indexer.
	 *  --------------------------------
	 *
	 *  Let S be an index selector. It should support:
	 *
	 *  - copy-constructible and/or move-constructible
	 *
	 *  - S.dim() -> the number of indices, of type index_type
	 *  - S[i] -> the i-th selected index (i is of index_t type)
	 *
	 *  - is_indexer<S>::value is explicitly specialized as true.
	 *    (By default, it is false)
	 */


	// forward declarations

	class id_ind;
	class step_ind;
	class rep_ind;

	template<class T> struct is_indexer { static const bool value = false; };

	template<> struct is_indexer<id_ind> { static const bool value = true; };
	template<> struct is_indexer<step_ind> { static const bool value = true; };
	template<> struct is_indexer<rep_ind> { static const bool value = true; };

	class id_ind
	{
	public:
		explicit id_ind(index_t n) : m_n(n)
		{
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_n;
		}

		BCS_ENSURE_INLINE index_t operator[] (index_t i) const
		{
			return i;
		}

		bool operator == (const id_ind& rhs) const
		{
			return m_n == rhs.m_n;
		}

		bool operator != (const id_ind& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		index_t m_n;

	}; // end class id_ind


	class step_ind
	{
	public:
		explicit step_ind(index_t n, index_t step) : m_n(n), m_step(step)
		{
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_n;
		}

		BCS_ENSURE_INLINE index_t operator[] (index_t i) const
		{
			return i * m_step;
		}

		bool operator == (const step_ind& rhs) const
		{
			return m_n == rhs.m_n && m_step == rhs.m_step;
		}

		bool operator != (const step_ind& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		index_t m_n;
		index_t m_step;

	}; // end class step_ind


	class rep_ind
	{
	public:
		explicit rep_ind(index_t n) : m_n(n)
		{
		}

		BCS_ENSURE_INLINE index_t dim() const
		{
			return m_n;
		}

		BCS_ENSURE_INLINE index_t operator[] (index_t i) const
		{
			return 0;
		}

		bool operator == (const rep_ind& rhs) const
		{
			return m_n == rhs.m_n;
		}

		bool operator != (const rep_ind& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		index_t m_n;

	}; // end class id_ind


	/******************************************************
	 *
	 *  Map from index selector to indexer
	 *
	 ******************************************************/

	template<class R> struct indexer_map;

	template<> struct indexer_map<range>
	{
		typedef id_ind type;
		typedef step_ind stepped_type;

		static index_t get_offset(index_t adim, const range& rgn)
		{
			return rgn.begin_index();
		}

		static type get_indexer(index_t adim, const range& rgn)
		{
			return id_ind(rgn.dim());
		}

		static stepped_type get_stepped_indexer(index_t adim, index_t step, const range& rgn)
		{
			return step_ind(rgn.dim(), step);
		}
	};

	template<> struct indexer_map<step_range>
	{
		typedef step_ind type;
		typedef step_ind stepped_type;

		static index_t get_offset(index_t adim, const step_range& rgn)
		{
			return rgn.begin_index();
		}

		static type get_indexer(index_t adim, const step_range& rgn)
		{
			return step_ind(rgn.dim(), rgn.step());
		}

		static stepped_type get_stepped_indexer(index_t adim, index_t step, const step_range& rgn)
		{
			return step_ind(rgn.dim(), rgn.step() * step);
		}
	};

	template<> struct indexer_map<rep_range>
	{
		typedef rep_ind type;
		typedef rep_ind stepped_type;

		static index_t get_offset(index_t adim, const rep_range& rgn)
		{
			return rgn.index();
		}

		static type get_indexer(index_t adim, const rep_range& rgn)
		{
			return rep_ind(rgn.dim());
		}

		static stepped_type get_stepped_indexer(index_t adim, index_t step, const rep_range& rgn)
		{
			return rep_ind(rgn.dim());
		}
	};

	template<> struct indexer_map<whole>
	{
		typedef id_ind type;
		typedef step_ind stepped_type;

		static index_t get_offset(index_t adim, whole)
		{
			return 0;
		}

		static type get_indexer(index_t adim, whole)
		{
			return id_ind(adim);
		}

		static stepped_type get_stepped_indexer(index_t adim, index_t step, whole)
		{
			return step_ind(adim, step);
		}
	};


	template<> struct indexer_map<rev_whole>
	{
		typedef step_ind type;
		typedef step_ind stepped_type;

		static index_t get_offset(index_t adim, rev_whole)
		{
			return adim - 1;
		}

		static type get_indexer(index_t adim, rev_whole)
		{
			return step_ind(adim, -1);
		}

		static stepped_type get_stepped_indexer(index_t adim, index_t step, rev_whole)
		{
			return step_ind(adim, -step);
		}
	};


}

#endif 

