/*
 * @file graph_minimum_span_trees.h
 *
 * The minimum spanning tree algorithms
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_GRAPH_MINIMUM_SPAN_TREES_H_
#define BCSLIB_GRAPH_MINIMUM_SPAN_TREES_H_

#include <bcslib/graph/graph_algbase.h>
#include <bcslib/array/amap.h>
#include <bcslib/data_structs/disjoint_sets.h>
#include <bcslib/data_structs/binary_heap.h>
#include <vector>
#include <algorithm>

namespace bcs
{
	/***********************************************************
	 *
	 *   Kruskal Minimum Spanning Tree Algorithm
	 *
	 *
	 *   Agent concept
	 *   --------------
	 *
	 *   agent.examine_edge(u, v, e);
	 *   	invoked to check whether the edge e = (u, v) is viable.
	 *
	 *   agent.add_edge(u, v, e);
	 *  	invoked when the edge e = (u, v) is added.
	 *
	 *      returns whether to continue
	 *
	 ***********************************************************/


	template<typename E, typename D>
	struct kruskal_entry
	{
		E edge;
		D dist;

		kruskal_entry(const E& e, const D& d)
		: edge(e), dist(d)
		{
		}

		bool operator < (const kruskal_entry& r) const
		{
			return dist < r.dist;
		}
	};


	template<class Derived, class OutputIterator>
	class kruskal_outputer
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		kruskal_outputer(OutputIterator it)
		: m_out_iter(it)
		{
		}

		bool examine_edge(const vertex_type&, const vertex_type&, const edge_type& )
		{
			return true;
		}

		bool add_edge(const vertex_type&, const vertex_type&, const edge_type& e)
		{
			*(m_out_iter++) = e;
			return true;
		}

	private:
		OutputIterator m_out_iter;
	};



	template<class Derived, class EdgeDistMap, class DisjointSets, class Agent>
	size_t kruskal_minimum_span_tree_ex(const IGraphEdgeList<Derived>& graph,
			const EdgeDistMap& edge_dists, DisjointSets& dsets, Agent& agent)
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;
		typedef typename gview_traits<Derived>::edge_iterator edge_iter;
		typedef typename key_map_traits<EdgeDistMap>::value_type dist_type;
		typedef kruskal_entry<edge_type, dist_type> entry;

		typedef typename DisjointSets::size_type dset_index_type;

		// sort edges

		std::vector<entry> entries;
		entries.reserve((size_t)graph.nedges());

		edge_iter eend = graph.edges_end();
		for (edge_iter p = graph.edges_begin(); p != eend; ++p)
		{
			const edge_type& e = *p;
			entries.push_back(entry(e, edge_dists[e]));
		}

		std::sort(entries.begin(), entries.end());

		// scan edges and form the tree

		size_t ne = entries.size();

		for (size_t i = 0; i < ne; ++i)
		{
			const edge_type& e = entries[i].edge;

			vertex_type u = graph.source(e);
			vertex_type v = graph.target(e);

			if (agent.examine_edge(u, v, e))
			{
				if (dsets.join(u, v))
				{
					if (!agent.add_edge(u, v, e)) break;
				}

				if (dsets.ncomponents() == 1) break;
			}
		}

		return (size_t)dsets.ncomponents();
	}


	template<class Derived, class EdgeDistMap, class OutputIterator>
	inline size_t kruskal_minimum_span_tree(const IGraphEdgeList<Derived>& graph,
			const EdgeDistMap& edge_dists, OutputIterator output)
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		disjoint_set_forest<vertex_type> dsets(graph.nvertices());

		kruskal_outputer<Derived, OutputIterator> agent(output);
		return kruskal_minimum_span_tree_ex(graph, edge_dists, dsets, agent);
	}



	/***********************************************************
	 *
	 *   Prim Minimum Spanning Tree Algorithm
	 *
	 *
	 *	 Agent Concepts
	 *	 -----------------
	 *
	 *   agent.examine_edge(u, v, e);
	 *   	invoked to check whether the edge e = (u, v) is viable.
	 *
	 *   agent.add_edge(u, v, e);
	 *  	invoked when the edge e = (u, v) is added.
	 *
	 *
	 ***********************************************************/


	template<typename V, typename E, typename D>
	struct prim_entry
	{
		V pred;
		E edge;
		D dist;

		prim_entry() : dist(0)
		{
		}

		void set(const V& p, const E& e, const D& d)
		{
			pred = p;
			edge = e;
			dist = d;
		}

		bool operator < (const prim_entry& r) const
		{
			return dist < r.dist;
		}
	};


	template<class Derived, typename TDist>
	struct prim_default_heap
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		typedef vertex_type key_type;
		typedef prim_entry<vertex_type, edge_type, TDist> value_type;
		typedef array_map<key_type, value_type> value_map_type;
		typedef array_map<key_type, cbtree_node> node_map_type;

		typedef binary_heap<value_map_type, node_map_type> type;
	};

	template<class Derived, class OutputIterator>
	class prim_outputer
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		prim_outputer(OutputIterator it)
		: m_out_iter(it)
		{
		}

		bool examine_edge(const vertex_type&, const vertex_type&, const edge_type& )
		{
			return true;
		}

		bool add_edge(const vertex_type&, const vertex_type&, const edge_type& e)
		{
			*(m_out_iter++) = e;
			return true;
		}

	private:
		OutputIterator m_out_iter;
	};



	template<class Derived, class EdgeDistMap, class Heap>
	class prim_traverser
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		typedef typename key_map_traits<EdgeDistMap>::value_type distance_type;
		typedef prim_entry<vertex_type, edge_type, distance_type> entry_type;
		typedef EdgeDistMap edge_distance_map_type;
		typedef Heap heap_type;

		typedef typename gview_traits<Derived>::vertex_iterator vertex_iterator;
		typedef typename gview_traits<Derived>::incident_edge_iterator incident_edge_iterator;

	public:
		prim_traverser(const IGraphIncidenceList<Derived>& g,
				const edge_distance_map_type& edge_dists,
				const vertex_type& root)
		: m_graph(g)
		, m_status(g.nvertices(), GVISIT_NONE)
		, m_edge_dists(edge_dists)
		, m_entries(g.nvertices())
		, m_node_map(g.nvertices())
		, m_heap(m_entries, m_node_map)
		, m_root(root)
		, m_root_open(true)
		{
			m_status[root] = GVISIT_DISCOVERED;
		}

		bool is_ended() const
		{
			return !m_root_open && m_heap.empty();
		}

		gvisit_status status(const vertex_type& v) const
		{
			return m_status[v];
		}

		template<class Agent> void run(Agent& agent);


	private:

		template<class Agent>
		void process(const vertex_type& u, Agent& agent); // returns whether to continue running

	private:
		const IGraphIncidenceList<Derived>& m_graph;
		array_map<vertex_type, gvisit_status> m_status;
		const edge_distance_map_type& m_edge_dists;

		array_map<vertex_type, entry_type> m_entries;
		array_map<vertex_type, typename heap_type::handle_type> m_node_map;
		heap_type m_heap;

		vertex_type m_root;
		bool m_root_open;

	}; // end class prim_traverser


	template<class Derived, class EdgeDistMap, class Heap>
	template<class Agent>
	void prim_traverser<Derived, EdgeDistMap, Heap>::run(Agent& agent)
	{
		if (m_root_open)
		{
			m_root_open = false;
			process(m_root, agent);
		}

		while (!m_heap.empty())
		{
			vertex_type u = m_heap.top_key();
			const entry_type& ent = m_entries[u];

			if (!agent.add_edge(ent.pred, u, ent.edge))
				return;

			m_heap.delete_top();
			process(u, agent);
		}
	}


	template<class Derived, class EdgeDistMap, class Heap>
	template<class Agent>
	void prim_traverser<Derived, EdgeDistMap, Heap>::process(
			const vertex_type& u, Agent& agent)
	{
		incident_edge_iterator it = m_graph.out_edges_begin(u);
		incident_edge_iterator oe_end = m_graph.out_edges_end(u);

		for(; it != oe_end; ++it)
		{
			const edge_type& e = *it;
			vertex_type v = m_graph.target(e);

			if (agent.examine_edge(u, v, e))
			{
				gvisit_status vstat = status(v);

				if (vstat < GVISIT_FINISHED)
				{
					distance_type ed = m_edge_dists[e];
					entry_type& ent = m_entries[v];

					if (vstat < GVISIT_DISCOVERED)
					{
						m_status[v] = GVISIT_DISCOVERED;
						ent.set(u, e, ed);
						m_heap.insert(v);
					}
					else if (ed < ent.dist)
					{
						ent.set(u, e, ed);
						m_heap.update_up(v);
					}
				}
			}
		}

		m_status[u] = GVISIT_FINISHED;
	}


	template<class Derived, class EdgeDistMap, class Agent>
	inline void prim_minimum_span_tree_ex(const IGraphIncidenceList<Derived>& graph, const EdgeDistMap& edge_dists,
			const typename gview_traits<Derived>::vertex_type& root, Agent& agent)
	{
		typedef typename key_map_traits<EdgeDistMap>::value_type dist_type;
		typedef typename prim_default_heap<Derived, dist_type>::type heap_type;

		prim_traverser<Derived, EdgeDistMap, heap_type> T(graph, edge_dists, root);
		T.run(agent);
	}

	template<class Derived, class EdgeDistMap, class OutputIterator>
	inline void prim_minimum_span_tree(const IGraphIncidenceList<Derived>& graph, const EdgeDistMap& edge_dists,
			const typename gview_traits<Derived>::vertex_type& root, OutputIterator output)
	{
		prim_outputer<Derived, OutputIterator> agent(output);
		prim_minimum_span_tree_ex(graph, edge_dists, root, agent);
	}


}

#endif /* GRAPH_MINIMUM_SPAN_TREES_H_ */
