/**
 * @file binary_heap.h
 *
 * The class that implements a binary heap
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <bcslib/base/basic_defs.h>
#include <bcslib/base/key_map.h>
#include <vector>
#include <functional>

namespace bcs
{

	/**
	 * The Concept of a heap class
	 * -----------------------------
	 *
	 * Let H be a heap class, and h be an instance of H.
	 *
	 * The following should be supported.
	 *
	 * In addition to other standard container typedefs, it also defines
	 *
	 * H::value_map_type 		The type of the associated value-map
	 * H::handle_type 			The handle to nodes
	 *
	 * H h(value_map, node_map)
	 *
	 * h.size();
	 *     returns the number of elements in the heap
	 *
	 * h.empty();
	 *     returns whether the heap is empty (i.e. size() == 0)
	 *
	 * h.compare(x, y);
	 *     tests whether x is "more towards the top" as opposed to y.
	 *
	 * h.add_key(key);
	 * 	   add a key (without inserting it to the heap) as a preparation for make_heap
	 *
	 * h.make_heap();
	 *     make heap by organizing the added elements
	 *
	 * h.top_key();
	 *     returns the key of the top element
	 *
	 * h.top_value();
	 *     returns the value of the top element
	 *
	 * h.delete_top();
	 *     removes the top element from the heap and adjusts the heap
	 *     to maintain heap properties
	 *
	 * h.in_heap(key);
	 *     tests whether the element with the specified key is in the heap
	 *
	 * h.insert(key);
	 *     inserts the element with the specified key to the heap
	 *     pre-condition: not in_heap(idx)
	 *
	 * h.update_up(key);
	 * h.update_down(key);
	 *
	 *     notifies the heap to adjust its structure in response to an
	 *     update to the element with the specified key
	 *
	 *     use update_up if the change is towards the top
	 *     use update_down if the change is against the top
	 *
	 */

	struct cbtree_node
	{
		size_t id;

		cbtree_node() : id(0) { }

		cbtree_node(size_t id_) : id(id_) { }

		size_t index() const
		{
			return id - 1;
		}

		bool is_nil() const
		{
			return id == 0;
		}

		bool non_nil() const
		{
			return id > 0;
		}

		bool operator == (const cbtree_node& rhs) const
		{
			return id == rhs.id;
		}

		bool operator != (const cbtree_node& rhs) const
		{
			return id != rhs.id;
		}
	};



	/**
	 * Note: the node index is from 1 to size.
	 */
	template<typename T>
	class consecutive_binary_tree
	{
	public:
		typedef T value_type;
		typedef std::vector<T> container_type;
		typedef typename container_type::size_type size_type;
		typedef typename container_type::difference_type difference_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::pointer pointer;
		typedef typename container_type::const_pointer const_pointer;
		typedef typename container_type::iterator iterator;
		typedef typename container_type::const_iterator const_iterator;

		typedef cbtree_node node_type;

	public:
		size_type size() const
		{
			return m_nodes.size();
		}

		bool empty() const
		{
			return m_nodes.empty();
		}

		void reserve(size_type cap)
		{
			m_nodes.reserve(cap);
		}

		void push(const T& e)
		{
			m_nodes.push_back(e);
		}

		void pop()
		{
			m_nodes.pop_back();
		}

	public:
		const_reference root_value() const
		{
			return m_nodes.front();
		}

		reference root_value()
		{
			return m_nodes.front();
		}

		const_reference back_value() const
		{
			return m_nodes.back();
		}

		reference back_value()
		{
			return m_nodes.back();
		}

		const_reference operator() (node_type node) const
		{
			return m_nodes[node.index()];
		}

		reference operator() (node_type node)
		{
			return m_nodes[node.index()];
		}

		const_iterator begin() const
		{
			return m_nodes.begin();
		}

		const_iterator end() const
		{
			return m_nodes.end();
		}

		iterator begin()
		{
			return m_nodes.begin();
		}

		iterator end()
		{
			return m_nodes.end();
		}

	public:
		node_type root() const
		{
			return 1;
		}

		node_type back() const
		{
			return size();
		}

		node_type last_parent() const
		{
			return size() >> 1;
		}

		node_type parent(node_type v) const
		{
			return v.id >> 1;
		}

		node_type left_child(node_type v) const
		{
			size_type id = v.id << 1;
			return id <= size() ? id : 0;
		}

		node_type right_child(node_type v) const
		{
			size_type id = v.id << 1;
			return id < size() ? id + 1 : 0;
		}

		void get_children(node_type v, node_type& lc, node_type& rc) const
		{
			size_type id = v.id << 1;
			size_type s = size();

			if (id > s)
			{
				lc = 0;
				rc = 0;
			}
			else if (id == s)
			{
				lc = id;
				rc = 0;
			}
			else // id < s
			{
				lc = id;
				rc = id + 1;
			}
		}

		bool is_non_root(node_type v) const
		{
			return v.id > 1;
		}

	private:
		container_type m_nodes;
	};



	template<class ValueMap, class NodeMap, class Compare=std::less<typename key_map_traits<ValueMap>::value_type> >
	class binary_heap
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(is_key_map<ValueMap>::value, "ValueMap should be a key-map.");
		static_assert(is_key_map<NodeMap>::value, "NodeMap should be a key-map.");
#endif
		typedef typename key_map_traits<ValueMap>::key_type key_type;
		typedef typename key_map_traits<ValueMap>::value_type value_type;

		typedef ValueMap value_map_type;
		typedef NodeMap node_map_type;
		typedef Compare compare_type;

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename value_map_type::reference reference;
		typedef typename value_map_type::const_reference const_reference;

		typedef consecutive_binary_tree<key_type> tree_type;
		typedef typename tree_type::node_type handle_type;

	public:
		binary_heap(const value_map_type& value_map, node_map_type& node_map,
				const compare_type& compare = compare_type())
		: m_value_map(value_map), m_node_map(node_map), m_compare(compare)
		{
			// note: the caller should initialize the node_map before it is used in the heap
		}

	public:
		// concept-required interfaces (for reading)

		size_type size() const
		{
			return m_btree.size();
		}

		bool empty() const
		{
			return m_btree.empty();
		}

		key_type top_key() const
		{
			return m_btree.root_value();
		}

		const_reference top_value() const
		{
			return m_value_map[top_key()];
		}

		bool compare(const value_type& x, const value_type& y) const
		{
			return m_compare(x, y);
		}

		bool in_heap(const key_type& key) const
		{
			return m_node_map[key].non_nil();
		}

	public:
		// concept-required interfaces (for manipulation)

		void add_key(const key_type& key)
		{
			m_btree.push(key);
			m_node_map[key] = m_btree.back();
		}

		void make_heap()
		{
			if (m_btree.size() > 1)
			{
				size_type last_nonleaf_id = m_btree.last_parent().id;
				for (size_type id = last_nonleaf_id; id > 0; --id)
				{
					bubble_down(id, get_by_node(id));
				}
			}
		}

		void insert(const key_type& key) // pre-condition: !in_heap(idx)
		{
			// push to the last node of the tree
			m_btree.push(key);

			// attach to node-map
			handle_type last_node = m_btree.back();
			m_node_map[key] = last_node;

			// adjust position
			if (m_btree.size() > 1)
			{
				bubble_up(last_node, m_value_map[key]);
			}
		}

		void delete_top()
		{
			size_type n = m_btree.size();

			if (n > 0)
			{
				// detach root-node from node-map
				m_node_map[m_btree.root_value()] = handle_type();

				if (n > 1)
				{
					// put back to root
					key_type key = m_btree.root_value() = m_btree.back_value();
					m_node_map[key] = m_btree.root();

					// pop the back
					m_btree.pop();

					// adjust position
					bubble_down(m_btree.root(), m_value_map[key]);
				}
				else
				{
					// simply pop the back
					m_btree.pop();
				}

			}
		}

		void update_up(const key_type& key) // pre-condition: in_heap(key)
		{
			bubble_up(m_node_map[key], m_value_map[key]);
		}

		void update_down(const key_type& key) // pre-condition: in_heap(key)
		{
			bubble_down(m_node_map[key], m_value_map[key]);
		}

	public:

		// binary-tree specific interfaces

		const_reference get_by_node(handle_type u) const
		{
			return m_value_map[m_btree(u)];
		}

		handle_type node(const key_type& key) const
		{
			return m_node_map[key];
		}

		const tree_type& tree() const
		{
			return m_btree;
		}

		const node_map_type& node_map() const
		{
			return m_node_map;
		}

		const value_map_type& value_map() const
		{
			return m_value_map;
		}


	private:

		void bubble_up(handle_type u, const value_type& e)
		{
			bool cont = true;

			while (cont && m_btree.is_non_root(u))
			{
				handle_type p = m_btree.parent(u);
				if (compare(e, get_by_node(p)))
				{
					u = swap(u, p);
				}
				else
				{
					cont = false;
				}
			}
		}

		void bubble_down(handle_type u, const value_type& e)
		{
			bool cont = true;

			handle_type last_nl = m_btree.last_parent();
			while (cont && u.id <= last_nl.id)
			{
				cont = false;

				handle_type lc, rc;
				m_btree.get_children(u, lc, rc);

				if (rc.non_nil())
				{
					const_reference le = get_by_node(lc);
					const_reference re = get_by_node(rc);

					if (compare(le, re))
					{
						if (compare(le, e))
						{
							u = swap(u, lc);
							cont = true;
						}
					}
					else
					{
						if (compare(re, e))
						{
							u = swap(u, rc);
							cont = true;
						}
					}
				}
				else if (lc.non_nil())
				{
					const_reference le = get_by_node(lc);
					if (compare(le, e))
					{
						u = swap(u, lc);
						cont = true;
					}
				}
			}
		}

		handle_type swap(handle_type u, handle_type v)
		{
			key_type ui = m_btree(u);
			key_type vi = m_btree(v);

			m_node_map[ui] = v;
			m_node_map[vi] = u;

			m_btree(u) = vi;
			m_btree(v) = ui;

			return v;
		}

	private:
		const value_map_type& m_value_map;
		node_map_type& m_node_map;
		tree_type m_btree;
		Compare m_compare;

	}; // end class binary_heap


	template<class ValueMap, class Compare>
	void make_heap_with_int_keys(bcs::binary_heap<ValueMap, Compare>& heap,
			const typename key_map_traits<ValueMap>::key_type& first,
			const typename key_map_traits<ValueMap>::key_type& last)
	{
		typedef typename key_map_traits<ValueMap>::key_type key_type;

		for (key_type key = first; key < last; ++key)
		{
			heap.add_key(key);
		}
		heap.make_heap();
	}


	template<class ValueMap, class Compare>
	void update_element(ValueMap& value_map, bcs::binary_heap<ValueMap, Compare>& heap,
			const typename key_map_traits<ValueMap>::key_type& key,
			const typename key_map_traits<ValueMap>::value_type& value)
	{
		typedef typename key_map_traits<ValueMap>::value_type vtype;

		vtype v0 = value_map[key];
		value_map[key] = value;

		if (heap.compare(value, v0))
		{
			heap.update_up(key);
		}
		else
		{
			heap.update_down(key);
		}
	}


}

#endif /* BINARY_TREE_H_ */
