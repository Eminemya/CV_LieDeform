/*
 * @file graph_shortest_paths.h
 *
 * Shortest path algorithms
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif


#ifndef BCSLIB_GRAPH_SHORTEST_PATHS_H_
#define BCSLIB_GRAPH_SHORTEST_PATHS_H_

#include <bcslib/graph/graph_algbase.h>
#include <bcslib/array/amap.h>
#include <bcslib/data_structs/binary_heap.h>
#include <queue>
#include <vector>

namespace bcs
{
	/***********************************************************
	 *
	 *   Bellman-Ford Shortest Path Algorithm
	 *
	 *
	 *   Agent concept
	 *   --------------
	 *
	 *   agent.update(u, v, len);
	 *  	invoked when the bound on the shortest-path-len of
	 *      v is reduced to len via u.
	 *
	 ***********************************************************/

	namespace _detail
	{
		template<class Derived, class EdgeDistMap, class PathLenMap, class Agent>
		bool bellman_ford_shortest_paths_impl(const IGraphIncidenceList<Derived>& graph,
				const EdgeDistMap& edge_dists, PathLenMap& spath_lens, index_t nsources, Agent& agent)
		{
#ifdef BCS_USE_STATIC_ASSERT
			static_assert(is_key_map<EdgeDistMap>::value, "EdgeDistMap must be a key-map.");
			static_assert(is_key_map<PathLenMap>::value, "PathLenMap must be a key-map.");
#endif
			typedef typename gview_traits<Derived>::index_type index_type;
			typedef typename gview_traits<Derived>::vertex_type vertex_type;
			typedef typename gview_traits<Derived>::edge_type edge_type;
			typedef typename gview_traits<Derived>::edge_iterator edge_iter;
			typedef typename key_map_traits<EdgeDistMap>::value_type dist_type;

			index_type max_iters = graph.nvertices() - (index_type)nsources;

			edge_iter ebegin = graph.edges_begin();
			edge_iter eend = graph.edges_end();

			bool changed = true;

			for(index_type i = 1; changed ;++i)
			{
				changed = false;
				for (edge_iter p = ebegin; p != eend; ++p)
				{
					const edge_type& e = *p;
					vertex_type u = graph.source(e);
					vertex_type v = graph.target(e);

					dist_type alt_len = spath_lens[u] + edge_dists[e];
					if (spath_lens[v] > alt_len)
					{
						spath_lens[v] = alt_len;
						changed = true;

						agent.update(u, v, alt_len);
					}
				}

				if (changed && i > max_iters) return false;
			}

			return true; // no negative-cycle
		}
	}


	template<class Derived, class EdgeDistMap, class PathLenMap, class Agent>
	inline bool bellman_ford_shortest_paths(const IGraphIncidenceList<Derived>& graph,
			const EdgeDistMap& edge_dists, PathLenMap& spath_lens,
			const typename key_map_traits<PathLenMap>::value_type& defaultlen,
			Agent& agent, const typename gview_traits<Derived>::vertex_type& source)
	{
		typedef typename gview_traits<Derived>::vertex_iterator vertex_iter;

		vertex_iter vend = graph.vertices_end();
		for (vertex_iter it = graph.vertices_begin(); it != vend; ++it)
		{
			spath_lens[*it] = defaultlen;
		}
		spath_lens[source] = 0;

		return _detail::bellman_ford_shortest_paths_impl(
				graph, edge_dists, spath_lens, 1, agent);
	}


	/***********************************************************
	 *
	 *   Dijkstra Shortest Path Algorithm
	 *
	 *
	 *   Agent concept
	 *   -------------
	 *
	 *   agent.source(u);
	 *       invoked when u is added as source, which has not
	 *       been processed though.
	 *
	 *   agent.enroll(u, len);
	 *       invoked when u's shortest path length has been
	 *       determined, and its neighbors is to be examined.
	 *
	 *       returns whether to continue
	 *
	 *   agent.examine_edge(u, v, e);
	 *       invoked when the edge e that connects between u
	 *       and v is seen.
	 *
	 *       returns whether the edge e is viable
	 *
	 *   agent.discover(u, v, e, len);
	 *       invoked when a new vertex is first attained (via
	 *       e = (u, v)), whose initial path length is len.
	 *
	 *       returns whether to continue
	 *
	 *   agent.relax(u, v, e, len);
	 *       invoked when a shorter path from source(s) to
	 *       v is found (with new length len), via e = (u, v).
	 *
	 *       returns whether to continue
	 *
	 *   agent.finish(u, len);
	 *       invoked when all neighbors of u have been examined.
	 *       Here, len is the shortest path length from sources
	 *       to u.
	 *
	 *       returns whether to continue.
	 *
	 ***********************************************************/

	template<class Derived, class PathLenMap>
	struct dijkstra_default_heap
	{
		typedef typename gview_traits<Derived>::vertex_type key_type;
		typedef typename key_map_traits<PathLenMap>::value_type value_type;
		typedef PathLenMap value_map_type;
		typedef array_map<key_type, cbtree_node> node_map_type;

		typedef binary_heap<value_map_type, node_map_type> type;
	};

	template<class Derived, typename TDist>
	struct trivial_dijkstra_agent
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		void source(const vertex_type& ) { }
		bool enroll(const vertex_type&, const TDist& ) { return true; }
		bool examine_edge(const vertex_type&, const vertex_type&, const edge_type& ) { return true; }
		bool discover(const vertex_type&, const vertex_type&, const edge_type&, const TDist& ) { return true; }
		bool relax(const vertex_type&, const vertex_type&, const edge_type&, const TDist& ) { return true; }
		bool finish(const vertex_type&, const TDist& ) { return true; }
	};


	template<class Derived, class EdgeDistMap, class PathLenMap, class Heap>
	class dijkstra_traverser
	{
	public:
#ifdef BCS_USE_STATIC_ASSERT
		static_assert(is_key_map<EdgeDistMap>::value, "EdgeDistMap must be a key-map.");
		static_assert(is_key_map<PathLenMap>::value, "PathLenMap must be a key-map.");
#endif

		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::edge_type edge_type;

		typedef typename key_map_traits<EdgeDistMap>::value_type distance_type;
		typedef EdgeDistMap edge_distance_map_type;
		typedef PathLenMap path_length_map_type;
		typedef Heap heap_type;

		typedef typename gview_traits<Derived>::vertex_iterator vertex_iterator;
		typedef typename gview_traits<Derived>::incident_edge_iterator incident_edge_iterator;

	public:
		dijkstra_traverser(const IGraphIncidenceList<Derived>& g,
				const edge_distance_map_type& edge_dists,
				path_length_map_type& shortest_path_lens,
				const typename key_map_traits<PathLenMap>::value_type& defaultlen)
		: m_graph(g)
		, m_status(g.nvertices(), GVISIT_NONE)
		, m_edge_dists(edge_dists)
		, m_shortest_path_lens(shortest_path_lens)
		, m_node_map(g.nvertices())
		, m_heap(m_shortest_path_lens, m_node_map)
		{
			vertex_iterator pv = g.vertices_begin();
			vertex_iterator vend = g.vertices_end();

			for (; pv != vend; ++pv)
			{
				const vertex_type& v = *pv;

				m_status[v] = GVISIT_NONE;
				m_shortest_path_lens[v] = defaultlen;
			}
		}

		bool is_ended() const
		{
			return m_sources.empty() && m_heap.empty();
		}

		gvisit_status status(const vertex_type& v) const
		{
			return m_status[v];
		}

		template<class Agent>
		void add_source(const vertex_type& v, Agent& agent)
		{
			agent.source(v);

			m_status[v] = GVISIT_DISCOVERED;
			m_shortest_path_lens[v] = distance_type(0);

			m_sources.push(v);
		}

		template<class Agent> void run(Agent& agent);


	private:

		template<class Agent>
		bool process(const vertex_type& u, const distance_type& spl_u, Agent& agent); // returns whether to continue running


	private:
		const IGraphIncidenceList<Derived>& m_graph;
		array_map<vertex_type, gvisit_status> m_status;
		const edge_distance_map_type& m_edge_dists;
		path_length_map_type& m_shortest_path_lens;

		array_map<vertex_type, typename heap_type::handle_type> m_node_map;
		heap_type m_heap;

		std::queue<vertex_type> m_sources;

	}; // end class dijkstra_traverser


	template<class Derived, class EdgeDistMap, class PathLenMap, class Heap>
	template<class Agent>
	void dijkstra_traverser<Derived, EdgeDistMap, PathLenMap, Heap>::run(Agent& agent)
	{
		while (!m_sources.empty())
		{
			vertex_type u = m_sources.front();
			m_sources.pop();

			if (!process(u, m_shortest_path_lens[u], agent))
				return;
		}

		while (!m_heap.empty())
		{
			vertex_type u = m_heap.top_key();
			distance_type spl_u = m_shortest_path_lens[u];

			if (!agent.enroll(u, spl_u))
				return;

			m_heap.delete_top();

			if (!process(u, spl_u, agent))
				return;
		}
	}

	template<class Derived, class EdgeDistMap, class PathLenMap, class Heap>
	template<class Agent>
	bool dijkstra_traverser<Derived, EdgeDistMap, PathLenMap, Heap>::process(
			const vertex_type& u, const distance_type& spl_u, Agent& agent)
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
					distance_type current_pl = spl_u + m_edge_dists[e];

					if (vstat < GVISIT_DISCOVERED)
					{
						m_status[v] = GVISIT_DISCOVERED;
						m_shortest_path_lens[v] = current_pl;
						m_heap.insert(v);

						if (!agent.discover(u, v, e, current_pl)) return false;
					}
					else if (current_pl < m_shortest_path_lens[v])
					{
						m_shortest_path_lens[v] = current_pl;
						m_heap.update_up(v);

						if (!agent.relax(u, v, e, current_pl)) return false;
					}
				}
			}
		}

		m_status[u] = GVISIT_FINISHED;
		return agent.finish(u, spl_u);
	}


	template<class Derived, class EdgeDistMap, class PathLenMap, class Agent>
	inline void dijkstra_shortest_paths(const IGraphIncidenceList<Derived>& graph,
			const EdgeDistMap& edge_dists, PathLenMap& shortest_path_lens,
			const typename key_map_traits<PathLenMap>::value_type& default_len,
			Agent& agent, typename gview_traits<Derived>::vertex_type& source)
	{
		typedef typename dijkstra_default_heap<Derived, PathLenMap>::type heap_type;

		dijkstra_traverser<Derived, EdgeDistMap, PathLenMap, heap_type> T(
				graph, edge_dists, shortest_path_lens, default_len);

		T.add_source(source, agent);
		T.run(agent);
	}

	template<class Derived, class EdgeDistMap, class PathLenMap, class Agent, typename InputIterator>
	inline void dijkstra_shortest_paths(const IGraphIncidenceList<Derived>& graph,
			const EdgeDistMap& edge_dists, PathLenMap& shortest_path_lens,
			const typename key_map_traits<PathLenMap>::value_type& default_len,
			Agent& agent, InputIterator src_first, InputIterator src_last)
	{

		typedef typename dijkstra_default_heap<Derived, PathLenMap>::type heap_type;

		dijkstra_traverser<Derived, EdgeDistMap, PathLenMap, heap_type> T(
				graph, edge_dists, shortest_path_lens, default_len);

		for(; src_first != src_last; ++src_first)
		{
			T.add_source(*src_first, agent);
		}
		T.run(agent);
	}


}

#endif /* GRAPH_SHORTEST_PATHS_H_ */
