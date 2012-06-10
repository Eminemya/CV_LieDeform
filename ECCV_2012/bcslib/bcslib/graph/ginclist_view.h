/**
 * @file ginclist_view.h
 *
 * The class that represents a graph as an incidence list
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_GINCLIST_VIEW_H
#define BCSLIB_GINCLIST_VIEW_H

#include <bcslib/graph/gview_base.h>

namespace bcs
{

	template<typename TInt>
	struct gview_traits<ginclist_view<TInt> >
	{
		typedef gvertex<TInt> vertex_type;
		typedef gedge<TInt> edge_type;
		typedef TInt index_type;
		typedef typename natural_vertex_iterator<TInt>::type vertex_iterator;
		typedef typename natural_edge_iterator<TInt>::type edge_iterator;
		typedef const vertex_type* neighbor_iterator;
		typedef const edge_type* incident_edge_iterator;
	};


	/**
	 * The class to represent a graph as an incidence list
	 *
	 * To represent a graph with n vertices and m edges, each object
	 * of this class maintains the following data:
	 *
	 * edges:		an array of vertex pairs, of length m'
	 * neighbors:	an array of vertices, of length m'
	 * inc_edges:	an array of edges, of length m'
	 * degrees:		an array of integers, of length n
	 * offsets:		an array of integers, of length n
	 *
	 * For directed graph:
	 * m' = m
	 * edges is simply a list of vertex pairs of all edges
	 *
	 * For undirected graph
	 * m' = 2 * m
	 * edges[0:m-1] is the original list of vertex pairs of all edges
	 * edges[m:2m-1] is the list of flipped vertex pairs.
	 *
	 * For example, if edge[i] is (u, v) for i < m, then
	 * edge[i + m] is (v, u).
	 *
	 * neighbors[offsets[v] : offsets[v] + degrees[v] - 1]
	 * is the list of the (outgoing) neighbors of the vertex v
	 *
	 * inc_edges[offsets[v] : offsets[v] + degrees[v] - 1]
	 * is the list of the (outgoing) incident edges of the vertex v
	 *
	 * The order of neighbors is the same as the order of inc_edges.
	 *
	 * The objects in this class only maintain a pointer to the base
	 * addresses of these arrays, which are provided externally.
	 */
	template<typename TInt>
	class ginclist_view : public IGraphIncidenceList<ginclist_view<TInt> >
	{
	public:
		BCS_GINCLIST_INTERFACE_DEFS(ginclist_view)

	public:
		ginclist_view(index_type nv, index_type ne, bool is_directed,
				const gvertex_pair<TInt> *edges,
				const vertex_type *neighbors,
				const edge_type *inc_edges,
				const index_type *degrees,
				const index_type *offsets)
		: m_nv(nv), m_ne(ne), m_isdirected(is_directed)
		, m_edges(edges)
		, m_neighbors(neighbors)
		, m_inc_edges(inc_edges)
		, m_degrees(degrees)
		, m_offsets(offsets)
		{
		}

	public:
		BCS_ENSURE_INLINE index_type nvertices() const
		{
			return m_nv;
		}

		BCS_ENSURE_INLINE index_type nedges() const
		{
			return m_ne;
		}

		BCS_ENSURE_INLINE bool is_directed() const
		{
			return m_isdirected;
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_begin() const
		{
			return natural_vertex_iterator<TInt>::get_default();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_end() const
		{
			return natural_vertex_iterator<TInt>::from_id(m_nv + BCS_GRAPH_ENTITY_IDBASE);
		}

		BCS_ENSURE_INLINE edge_iterator edges_begin() const
		{
			return natural_edge_iterator<TInt>::get_default();
		}

		BCS_ENSURE_INLINE edge_iterator edges_end() const
		{
			return natural_edge_iterator<TInt>::from_id(m_ne + BCS_GRAPH_ENTITY_IDBASE);
		}

		BCS_ENSURE_INLINE const vertex_type& source(const edge_type& e) const
		{
			return m_edges[e.index()].s;
		}

		BCS_ENSURE_INLINE const vertex_type& target(const edge_type& e) const
		{
			return m_edges[e.index()].t;
		}

		BCS_ENSURE_INLINE index_type out_degree(const vertex_type& v) const
		{
			return m_degrees[v.index()];
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_begin(const vertex_type& v) const
		{
			index_type vi = v.index();
			return m_neighbors + m_offsets[vi];
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_end(const vertex_type& v) const
		{
			index_type vi = v.index();
			return m_neighbors + m_offsets[vi] + m_degrees[vi];
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_begin(const vertex_type& v) const
		{
			index_type vi = v.index();
			return m_inc_edges + m_offsets[vi];
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_end(const vertex_type& v) const
		{
			index_type vi = v.index();
			return m_inc_edges + m_offsets[vi] + m_degrees[vi];
		}

	private:
		index_type m_nv;
		index_type m_ne;
		bool m_isdirected;

		const gvertex_pair<TInt>* m_edges;

		const vertex_type* m_neighbors;
		const edge_type* m_inc_edges;
		const index_type* m_degrees;
		const index_type* m_offsets;

	}; // end class ginclist_view


	template<typename TInt, typename TIterSrc>
	void augment_edgelist(TInt m, bool is_directed, TIterSrc src_edges, gvertex_pair<TInt>* edges)
	{
		if (is_directed)
		{
			for (TInt i = 0; i < m; ++i)
			{
				const gvertex_pair<TInt>& se = *(src_edges++);
				edges[i] = se;
			}
		}
		else
		{
			for (TInt i = 0; i < m; ++i)
			{
				const gvertex_pair<TInt>& se = *(src_edges++);
				edges[i] = se;
				edges[i + m] = se.flip();
			}
		}
	}


	template<typename TInt>
	void prepare_ginclist_arrays(TInt n, TInt m, const gvertex_pair<TInt> *edges,
			gvertex<TInt> *neighbors,
			gedge<TInt> *inc_edges,
			TInt *degrees,
			TInt *offsets,
			TInt *temp) 	// temp should be able to contain n elements
	{
		// count neighbors

		for (TInt i = 0; i < n; ++i) degrees[i] = 0;
		for (TInt i = 0; i < m; ++i) ++ degrees[edges[i].s.index()];

		// set offsets

		TInt o = 0;
		offsets[0] = o;
		for (TInt i = 1; i < n; ++i)
		{
			offsets[i] = (o += degrees[i-1]);
		}

		// fill in neighbors and inc_edges

		for (TInt i = 0; i < n; ++i) temp[i] = 0;

		for (TInt i = 0; i < m; ++i)
		{
			const gvertex_pair<TInt>& e = edges[i];
			TInt si = e.s.index();
			TInt j = offsets[si] + (temp[si]++);
			neighbors[j] = e.t;
			inc_edges[j].id = i + BCS_GRAPH_ENTITY_IDBASE;
		}
	}


}


#endif 
