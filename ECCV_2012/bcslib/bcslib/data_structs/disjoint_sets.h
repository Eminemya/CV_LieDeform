/**
 * @file disjoint_sets.h
 *
 *  The data structure for representing disjoint sets
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#include <bcslib/base/basic_defs.h>
#include <bcslib/array/amap.h>


#ifndef BCSLIB_DISJOINT_SETS_H_
#define BCSLIB_DISJOINT_SETS_H_

namespace bcs
{

	template<typename T>
	class disjoint_set_forest
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(index_convertible<T>::value, "T must be index-convertible.");
#endif

		typedef size_t size_type;
		typedef T element_type;

		struct node
		{
			size_t rank;
			index_t parent_idx;
		};

	public:
		explicit disjoint_set_forest(index_t n)
		: m_nodes(n)
		{
			for (index_t i = 0; i < n; ++i)
			{
				node& nd = m_nodes[i];
				nd.rank = 0;
				nd.parent_idx = i;
			}
			m_ncomps = (size_type)n;
		}

		size_type size() const
		{
			return m_nodes.size();
		}

		size_type ncomponents() const
		{
			return m_ncomps;
		}

		bool is_root(const element_type& x) const
		{
			return index(x) == parent_index(x);
		}

		index_t index(const element_type& x) const
		{
			return key_to_index<element_type>::to_index(x);
		}

		index_t parent_index(const element_type& x) const
		{
			return m_nodes[index(x)].parent_idx;
		}

		size_type rank(const element_type& x) const
		{
			return m_nodes[index(x)].rank;
		}

		bool in_same_component(const element_type& x, const element_type& y)
		{
			return find_root(x) == find_root(y);
		}

	public:

		/**
		 * Returns true if x and y were not in the same set, and thus
		 * the joining was actually performed
		 */
		bool join(const element_type& x, const element_type& y)
		{
			index_t rx = find_root(x);
			index_t ry = find_root(y);

			if (rx != ry)
			{
				index_t r = link_root(rx, ry);

				m_nodes[index(x)].parent_idx = r;
				m_nodes[index(y)].parent_idx = r;

				return true;
			}
			else
			{
				return false;
			}
		}

		index_t find_root(const element_type& x)
		{
			return find_root_from_index(index(x));
		}

		void compress_all()
		{
			index_t n = (index_t)size();
			for (index_t i = 0; i < n; ++i)
			{
				index_t ri = find_root_from_index(i);
				m_nodes[i].rank = (ri == i ? 1 : 0);
			}
		}

		index_t trace_root(const element_type& x) const
		{
			index_t p = index(x);
			index_t pp = m_nodes[p].parent_idx;

			while (p != pp)
			{
				p = pp;
				pp = m_nodes[p].parent_idx;
			}

			return p;
		}

	private:
		index_t find_root_from_index(const index_t& xi)
		{
			node& nx = m_nodes[xi];
			if (xi != nx.parent_idx)
			{
				return nx.parent_idx = find_root_from_index(nx.parent_idx);
			}
			else
			{
				return xi;
			}
		}

		index_t link_root(const index_t& rx, const index_t& ry)
		{
			node& nx = m_nodes[rx];
			node& ny = m_nodes[ry];

			-- m_ncomps;

			if (nx.rank > ny.rank)
			{
				ny.parent_idx = rx;

				return rx;
			}
			else
			{
				nx.parent_idx = ry;
				if (nx.rank == ny.rank) ++ ny.rank;

				return ry;
			}
		}

	private:
		array1d<node> m_nodes;
		size_type m_ncomps;

	}; // end class disjoint_set_forest

}

#endif /* DISJOINT_SET_H_ */
