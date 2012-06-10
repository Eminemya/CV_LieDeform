/*
 * @file dynamic_ordered_sparse_vector.h
 *
 * The class to implement a dynamically sparsed vector
 *
 * @author Dahua Lin
 */

#ifndef BCSLIB_DYNAMIC_SPARSE_VECTOR_H
#define BCSLIB_DYNAMIC_SPARSE_VECTOR_H

#include <bcslib/array/array_base.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>

namespace bcs
{

	template<typename T, typename TComp=std::greater<T> >
	class dynamic_ordered_spvec
	{
	public:
		typedef T value_type;
		typedef index_t index_type;
		typedef size_t size_type;
		typedef TComp comparer_type;
		typedef indexed_entry<value_type, index_type> pair_type;

		typedef std::vector<index_type, aligned_allocator<value_type> > index_container;
		typedef std::vector<value_type, aligned_allocator<value_type> > value_container;

	public:
		dynamic_ordered_spvec(size_type n, value_type thres=value_type())
		: m_d0((index_type)n), m_na(0), m_thres(thres), m_comp()
		{
		}

		dynamic_ordered_spvec(size_type n, comparer_type comp, value_type thres)
		: m_d0((index_type)n), m_na(0), m_thres(thres), m_comp(comp)
		{
		}

		template<typename IndIter, typename ValIter>
		dynamic_ordered_spvec(size_type n, size_type len,
				IndIter inds, ValIter vals, value_type thres=value_type())
		: m_d0((index_type)n), m_na(0), m_thres(thres), m_comp()
		{
			initialize(len, inds, vals);
		}

		template<typename IndIter, typename ValIter>
		dynamic_ordered_spvec(size_type n, size_type len,
				IndIter inds, ValIter vals, comparer_type comp, value_type thres)
		: m_d0((index_type)n), m_na(0), m_thres(thres), m_comp(comp)
		{
			initialize(len, inds, vals);
		}

		template<typename IndIter, typename ValIter>
		void initialize(size_type len, IndIter inds, ValIter vals);

	public:
		index_type dim0() const
		{
			return m_d0;
		}

		size_type nactives() const
		{
			return m_na;
		}

		value_type threshold() const
		{
			return m_thres;
		}

		bool can_be_active_value(const value_type& v) const
		{
			return m_comp(v, m_thres);
		}

		const index_type* active_indices() const
		{
			return m_na > 0 ? &(m_inds[0]) : null_p<const index_type>();
		}

		const value_type* active_values() const
		{
			return m_na > 0 ? &(m_vals[0]) : null_p<const value_type>();
		}

		index_type active_index(size_type i) const
		{
			return m_inds[i];
		}

		value_type active_value(size_type i) const
		{
			return m_vals[i];
		}

		pair_type active_pair(size_type i) const
		{
			pair_type pa;
			pa.value = active_value(i);
			pa.index = active_index(i);
			return pa;
		}

		size_type position_of_index(index_type k) const  // return na if not found
		{
			for(size_type i = 0; i < m_na; ++i)
			{
				if (active_index(i) == k) return i;
			}
			return nactives();
		}

		bool has_index(index_type k) const
		{
			return position_of_index(k) < nactives();
		}

	public:
		size_type set_value(const index_type& k, const value_type& v)
		{
			size_type i = position_of_index(k);
			if (i < nactives())
			{
				return update_value_at_position(i, v);
			}
			else
			{
				return add_new_pair(k, v);
			}
		}

		size_type update_value_at_position(size_type i, const value_type& v) // i in [0, na)
		{
			value_type v0 = active_value(i);

			if (m_comp(v, v0))
			{
				return increase_value_at_position(i, v);
			}
			else if (m_comp(v0, v))
			{
				return decrease_value_at_position(i, v);
			}
			else
			{
				m_vals[i] = v;
				return i;
			}
		}

		size_type add_new_pair(const index_type& k, const value_type& v) // k really did not exist
		{
			if (can_be_active_value(v))
			{
				m_inds.push_back(k);
				m_vals.push_back(v);
				++ m_na;

				return increase_value_at_position(m_na-1, v);
			}
			else
			{
				return nactives();
			}
		}


		size_type increase_value_at_position(size_type i, const value_type& v);

		size_type decrease_value_at_position(size_type i, const value_type& v);

	private:

		struct pair_comparer
		{
			pair_comparer(comparer_type c) : comp(c)
			{
			}

			bool operator() (const pair_type& pa1, const pair_type& pa2)
			{
				return comp(pa1.value, pa2.value);
			}

			comparer_type comp;
		};

	private:
		index_type m_d0;
		size_type m_na;
		value_type m_thres;
		comparer_type m_comp;

		index_container m_inds;
		value_container m_vals;

	}; // end class dynamic_ordered_spvec


	// Some implementation of dynamic_ordered_spvec


	template<typename T, typename TComp>
	template<typename IndIter, typename ValIter>
	void dynamic_ordered_spvec<T, TComp>::initialize(size_type len, IndIter inds, ValIter vals)
	{
		if (m_na > 0)
		{
			throw std::runtime_error("Cannot do initialization when nactives() > 0");
		}

		// put valid ones as pairs

		std::vector<pair_type> pairs;
		pairs.reserve(len);

		for (size_type i = 0; i < len; ++i)
		{
			index_type idx = *(inds++);
			value_type val = *(vals++);

			if (can_be_active_value(val))
			{
				pair_type pa;
				pa.index = idx;
				pa.value = val;

				pairs.push_back(pa);
			}
		}

		m_na = (size_type)(pairs.size());

		// sort them

		std::sort(pairs.begin(), pairs.end(), pair_comparer(m_comp));

		// put sorted ones into internal storage

		m_inds.reserve(m_na);
		m_vals.reserve(m_na);

		for (size_type i = 0; i < m_na; ++i)
		{
			const pair_type& pa = pairs[i];
			m_inds.push_back(pa.index);
			m_vals.push_back(pa.value);
		}

	}



	template<typename T, typename TComp>
	typename dynamic_ordered_spvec<T, TComp>::size_type
	dynamic_ordered_spvec<T, TComp>::increase_value_at_position(size_type i, const value_type& v)
	{
		index_type k = m_inds[i];

		while (i > 0 && m_comp(v, m_vals[i-1]))
		{
			m_inds[i] = m_inds[i-1];
			m_vals[i] = m_vals[i-1];
			-- i;
		}

		m_inds[i] = k;
		m_vals[i] = v;

		return i;
	}

	template<typename T, typename TComp>
	typename dynamic_ordered_spvec<T, TComp>::size_type
	dynamic_ordered_spvec<T, TComp>::decrease_value_at_position(size_type i, const value_type& v)
	{
		size_type max_i = nactives() - 1;
		index_type k = m_inds[i];

		if (can_be_active_value(v))
		{
			while (i < max_i && m_comp(m_vals[i+1], v))
			{
				m_inds[i] = m_inds[i+1];
				m_vals[i] = m_vals[i+1];
				++ i;
			}

			m_inds[i] = k;
			m_vals[i] = v;
		}
		else
		{
			while(i < max_i)
			{
				m_inds[i] = m_inds[i+1];
				m_vals[i] = m_vals[i+1];
				++ i;
			}

			m_inds.pop_back();
			m_vals.pop_back();
			-- m_na;
		}

		return i;
	}




}

#endif
