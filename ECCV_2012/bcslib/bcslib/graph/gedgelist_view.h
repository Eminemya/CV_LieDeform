/**
 * @file gedgelist_view.h
 *
 * The classes that represent a graph as a list of edges
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_GEDGELIST_VIEW_H
#define BCSLIB_GEDGELIST_VIEW_H

#include <bcslib/graph/gview_base.h>

namespace bcs
{

	template<typename TInt>
	struct gview_traits<gedgelist_view<TInt> >
	{
		typedef gvertex<TInt> vertex_type;
		typedef gedge<TInt> edge_type;
		typedef TInt index_type;
		typedef typename natural_vertex_iterator<TInt>::type vertex_iterator;
		typedef typename natural_edge_iterator<TInt>::type edge_iterator;
	};


	template<typename TInt>
	class gedgelist_view : public IGraphEdgeList<gedgelist_view<TInt> >
	{
	public:
		BCS_GEDGELIST_INTERFACE_DEFS(gedgelist_view)

	public:
		gedgelist_view(index_type nv, index_type ne, bool is_directed, const gvertex_pair<TInt> *edges)
		: m_nv(nv)
		, m_ne(ne)
		, m_isdirected(is_directed)
		, m_edges(edges)
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

		BCS_ENSURE_INLINE const gvertex_pair<TInt>* vertex_pairs_begin() const
		{
			return m_edges;
		}

		BCS_ENSURE_INLINE const gvertex_pair<TInt>* vertex_pairs_end() const
		{
			return m_edges + m_ne;
		}

	private:
		index_type m_nv;
		index_type m_ne;
		bool m_isdirected;

		const gvertex_pair<TInt> *m_edges;

	}; // end class gedgelist_view


}

#endif 
