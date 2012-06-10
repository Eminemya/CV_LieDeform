/**
 * @file graph_traversal.h
 *
 * Graph algorithms for graph traversal
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef GRAPH_TRAVERSAL_H_
#define GRAPH_TRAVERSAL_H_

#include <bcslib/graph/graph_algbase.h>
#include <bcslib/array/amap.h>
#include <vector>
#include <stack>
#include <queue>
#include <utility>

namespace bcs
{

	/***********************************************************
	 *
	 *   The Concept of Agent
	 *   ----------------------------------
	 *
	 *   Let a be an instance of an agent model
	 *
	 *	 a.source(v);
	 *	     invoked when a source vertex is to be added to
	 *	     the queue
	 *
	 *	     no return
	 *
	 *	 a.examine(u, v, v_status);
	 *	     invoked when an edge is examined.
	 *
	 *	     the agent should return whether the edge (u, v)
	 *	     is viable
	 *
	 *   a.discover(u, v);
	 *       invoked when a new vertex v is attained from u, which
	 *       is to be added to the queue
	 *
	 *       the agent should return whether to continue
	 *
	 *   a.finish(v);
	 *   	 invoked when all neighbors of v have been added
	 *   	 to the queue, and v is removed from the queue
	 *
	 *   	 the agent should return whether to continue
	 *
	 ***********************************************************/


	template<class Derived>
	class trivial_traversal_agent
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;

		void source(const vertex_type& ) { }
		bool examine(const vertex_type&, const vertex_type&, gvisit_status) { return true; }
		bool discover(const vertex_type&, const vertex_type& ) { return true; }
		bool finish(const vertex_type& ) { return true; }
	};


	/***********************************************************
	 *
	 *   Breadth-First Traversal
	 *
	 ***********************************************************/


	template<class Derived, class Queue>
	class breadth_first_traverser
	{
	public:
		typedef Queue queue_type;
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::neighbor_iterator neighbor_iterator;

	public:
		breadth_first_traverser(const IGraphAdjacencyList<Derived>& g, Queue& queue)
		: m_graph(g), m_status(g.nvertices(), GVISIT_NONE), m_queue(queue)
		{
		}

		gvisit_status status(const vertex_type& v) const
		{
			return m_status[v];
		}

		template<class Agent>
		void add_source(const vertex_type& u, Agent& agent)
		{
			if (status(u) < GVISIT_DISCOVERED)
			{
				agent.source(u);
				m_status[u] = GVISIT_DISCOVERED;
				m_queue.push(u);
			}
		}


		template<class Agent> void run(Agent& agent);

	private:
		const IGraphAdjacencyList<Derived>& m_graph;
		array_map<vertex_type, gvisit_status> m_status;
		queue_type& m_queue;
	};


	template<class Derived, class Queue>
	template<class Agent>
	void breadth_first_traverser<Derived, Queue>::run(Agent& agent)
	{
		while (!m_queue.empty())
		{
			vertex_type u = m_queue.front();

			neighbor_iterator it = m_graph.out_neighbors_begin(u);
			neighbor_iterator nb_end = m_graph.out_neighbors_end(u);

			for (; it != nb_end; ++it)
			{
				vertex_type v = *it;
				gvisit_status vstat = status(v);

				if (agent.examine(u, v, vstat) && vstat < GVISIT_DISCOVERED)
				{
					m_status[v] = GVISIT_DISCOVERED;
					m_queue.push(v);

					if (!agent.discover(u, v)) return;
				}
			}

			m_queue.pop();
			m_status[u] = GVISIT_FINISHED;
			if (!agent.finish(u)) return;
		}
	}



	template<class Derived, class Agent>
	inline void breadth_first_traverse(const IGraphAdjacencyList<Derived>& g, Agent& agent,
			const typename gview_traits<Derived>::vertex_type& source)
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		std::queue<vertex_type> Q;
		breadth_first_traverser<Derived, std::queue<vertex_type> > T(g, Q);

		T.add_source(source, agent);
		T.run(agent);
	}

	template<class Derived, class Agent, typename InputIter>
	inline void breadth_first_traverse(const IGraphAdjacencyList<Derived>& g, Agent& agent,
			InputIter first, InputIter last)
	{
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		std::queue<vertex_type> Q;
		breadth_first_traverser<Derived, std::queue<vertex_type> > T(g, Q);

		for (; first != last; ++first) T.add_source(*first, agent);
		T.run(agent);
	}



	/********************************************
	 *
	 *   Depth-First Traversal
	 *
	 ********************************************/

	template<class Derived>
	class depth_first_traverser
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::neighbor_iterator neighbor_iterator;

		struct entry
		{
			vertex_type v;
			neighbor_iterator nb_current;
			neighbor_iterator nb_end;
		};

	public:
		depth_first_traverser(const IGraphAdjacencyList<Derived>& g)
		: m_graph(g), m_status(g.nvertices(), GVISIT_NONE)
		{

		}

		gvisit_status status(const vertex_type& v) const
		{
			return m_status[v];
		}

		template<class Agent>
		void add_source(const vertex_type& u, Agent& agent)
		{
			if (status(u) < GVISIT_DISCOVERED)
			{
				agent.source(u);
				add_discovered(u);
			}
		}


		template<class Agent> void run(Agent& agent);

	private:

		void add_discovered(const vertex_type &v)
		{
			m_status[v] = GVISIT_DISCOVERED;

			entry e;
			e.v = v;
			e.nb_current = m_graph.out_neighbors_begin(v);
			e.nb_end = m_graph.out_neighbors_end(v);

			m_stack.push(e);
		}


	private:
		const IGraphAdjacencyList<Derived>& m_graph;
		array_map<vertex_type, gvisit_status> m_status;
		std::stack<entry> m_stack;
	};


	template<class Derived>
	template<class Agent>
	void depth_first_traverser<Derived>::run(Agent& agent)
	{
		while (!m_stack.empty())
		{
			entry& e = m_stack.top();

			if (e.nb_current != e.nb_end)
			{
				vertex_type v = *e.nb_current;
				++e.nb_current;
				gvisit_status vstatus = status(v);

				if (agent.examine(e.v, v, vstatus) && vstatus < GVISIT_DISCOVERED)
				{
					add_discovered(v);
					if (!agent.discover(e.v, v)) return;
				}
			}
			else
			{
				vertex_type v = e.v;
				m_stack.pop();

				if (!agent.finish(v)) return;
			}
		}
	}


	template<class Derived, class Agent>
	inline void depth_first_traverse(const IGraphAdjacencyList<Derived>& g, Agent& agent,
			const typename gview_traits<Derived>::vertex_type& seed)
	{
		depth_first_traverser<Derived> T(g);

		T.add_source(seed, agent);
		T.run(agent);
	}

	template<class Derived, class Agent, typename InputIter>
	inline void depth_first_traverse(const IGraphAdjacencyList<Derived>& g, Agent& agent,
			InputIter first, InputIter last)
	{
		depth_first_traverser<Derived> T(g);

		for (; first != last; ++first)
		{
			T.add_source(*first, agent);
			T.run(agent);
		}
	}



	/********************************************
	 *
	 *   Connected Components
	 *
	 *   Agent concept
	 *   -------------
	 *
	 *   a.new_component();
	 *   	invoked when a new component is
	 *   	detected and set to be the current
	 *   	component
	 *
	 *   a.add_vertex();
	 *   	invoked when a new vertex is found
	 *   	to be in the current component
	 *
	 *   a.end_component();
	 *   	invoked when the current component
	 *   	is completed
	 *
	 ********************************************/

	template<class Derived>
	class traversal_counter : public trivial_traversal_agent<Derived>
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;

		traversal_counter() : m_count(0) { }

		size_t count() const
		{
			return m_count;
		}

		bool discover(const vertex_type&, const vertex_type& )
		{
			++m_count;
			return true;
		}

	private:
		size_t m_count;
	};


	template<class Derived>
	inline size_t count_reachable_vertices(const IGraphAdjacencyList<Derived>& g,
			const typename gview_traits<Derived>::vertex_type& s)
	{
		traversal_counter<Derived> counter;
		breadth_first_traverse(g, counter, s);
		return counter.count();
	}


	template<class Derived, class CCAgent>
	class connected_components_agent : public trivial_traversal_agent<Derived>
	{
	public:
		typedef typename gview_traits<Derived>::vertex_type vertex_type;

		connected_components_agent(CCAgent& cca) : cc_agent(cca)
		{
		}

		void source(const vertex_type& u)
		{
			cc_agent.add_vertex(u);
		}

		bool discover(const vertex_type& u, const vertex_type& v)
		{
			cc_agent.add_vertex(v);
			return true;
		}

	private:
		CCAgent& cc_agent;
	};


	// return the number of components found
	template<class Derived, class CCAgent>
	inline size_t find_connected_components(const IGraphAdjacencyList<Derived>& g, CCAgent& cc_agent)
	{
		connected_components_agent<Derived, CCAgent> agent(cc_agent);

		typedef typename gview_traits<Derived>::vertex_type vertex_type;
		typedef typename gview_traits<Derived>::vertex_iterator viter;
		std::queue<vertex_type> Q;
		breadth_first_traverser<Derived, std::queue<vertex_type> > T(g, Q);

		size_t ncc = 0;

		viter pend = g.vertices_end();
		for (viter p = g.vertices_begin(); p != pend; ++p)
		{
			const vertex_type& s = *p;
			if (T.status(s) == GVISIT_NONE)
			{
				++ncc;
				cc_agent.new_component();
				T.add_source(s, agent);
				T.run(agent);
				cc_agent.end_component();
			}
		}

		return ncc;
	}

}


#endif /* GRAPH_TRAVERSAL_H_ */
