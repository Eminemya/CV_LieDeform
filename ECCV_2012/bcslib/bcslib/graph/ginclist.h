/**
 * @file ginclist.h
 *
 * The class for instantiating a standalone incidence list
 * 
 * @author Dahua Lin
 */

#include <bcslib/graph/gedgelist_view.h>
#include <bcslib/graph/ginclist_view.h>
#include <bcslib/array/array1d.h>

#ifndef BCSLIB_GINCLIST_H_
#define BCSLIB_GINCLIST_H_

namespace bcs
{

	template<typename TInt>
	struct gview_traits<ginclist<TInt> >
	{
		typedef gvertex<TInt> vertex_type;
		typedef gedge<TInt> edge_type;
		typedef TInt index_type;
		typedef typename natural_vertex_iterator<TInt>::type vertex_iterator;
		typedef typename natural_edge_iterator<TInt>::type edge_iterator;
		typedef const vertex_type* neighbor_iterator;
		typedef const edge_type* incident_edge_iterator;
	};


	template<typename TInt>
	class ginclist : public IGraphIncidenceList<ginclist<TInt> >
	{
	public:
		BCS_GINCLIST_INTERFACE_DEFS(ginclist)
		typedef ginclist_view<TInt> view_type;

	public:
		template<typename TIter>
		ginclist(index_type nv, index_type ne, bool is_directed, TIter vertex_pairs)
		: m_ma(is_directed ? ne : 2 * ne)
		, m_edges((index_t)m_ma)
		, m_neighbors((index_t)m_ma)
		, m_inc_edges((index_t)m_ma)
		, m_degrees((index_t)nv)
		, m_offsets((index_t)nv)
		, m_view(nv, ne, is_directed,
				m_edges.pbase(), m_neighbors.pbase(), m_inc_edges.pbase(),
				m_degrees.pbase(), m_offsets.pbase())
		{
			_init_fields(vertex_pairs);
		}


		ginclist(const ginclist& r)
		: m_ma(r.m_ma)
		, m_edges(r.m_edges)
		, m_neighbors(r.m_neighbors)
		, m_inc_edges(r.m_inc_edges)
		, m_degrees(r.m_degrees)
		, m_offsets(r.m_offsets)
		, m_view(r.m_view)
		{
		}

		ginclist(const gedgelist_view<TInt>& g)
		: m_ma(g.is_directed() ? g.nedges() : 2 * g.nedges())
		, m_edges((index_t)m_ma)
		, m_neighbors((index_t)m_ma)
		, m_inc_edges((index_t)m_ma)
		, m_degrees((index_t)g.nvertices())
		, m_offsets((index_t)g.nvertices())
		, m_view(g.nvertices(), g.nedges(), g.is_directed(),
				m_edges.pbase(), m_neighbors.pbase(), m_inc_edges.pbase(),
				m_degrees.pbase(), m_offsets.pbase())
		{
			_init_fields(g.vertex_pairs_begin());
		}

		const view_type& view() const
		{
			return m_view;
		}

	public:
		BCS_ENSURE_INLINE index_type nvertices() const
		{
			return m_view.nvertices();
		}

		BCS_ENSURE_INLINE index_type nedges() const
		{
			return m_view.nedges();
		}

		BCS_ENSURE_INLINE bool is_directed() const
		{
			return m_view.is_directed();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_begin() const
		{
			return m_view.vertices_begin();
		}

		BCS_ENSURE_INLINE vertex_iterator vertices_end() const
		{
			return m_view.vertices_end();
		}

		BCS_ENSURE_INLINE edge_iterator edges_begin() const
		{
			return m_view.edges_begin();
		}

		BCS_ENSURE_INLINE edge_iterator edges_end() const
		{
			return m_view.edges_end();
		}

		BCS_ENSURE_INLINE const vertex_type& source(const edge_type& e) const
		{
			return m_view.source(e);
		}

		BCS_ENSURE_INLINE const vertex_type& target(const edge_type& e) const
		{
			return m_view.target(e);
		}

		BCS_ENSURE_INLINE index_type out_degree(const vertex_type& v) const
		{
			return m_view.out_degree(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_begin(const vertex_type& v) const
		{
			return m_view.out_neighbors_begin(v);
		}

		BCS_ENSURE_INLINE neighbor_iterator out_neighbors_end(const vertex_type& v) const
		{
			return m_view.out_neighbors_end(v);
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_begin(const vertex_type& v) const
		{
			return m_view.out_edges_begin(v);
		}

		BCS_ENSURE_INLINE incident_edge_iterator out_edges_end(const vertex_type& v) const
		{
			return m_view.out_edges_end(v);
		}

	private:

		template<typename TIter>
		void _init_fields(TIter edges)
		{
			index_type n = m_view.nvertices();
			index_type m = m_view.nedges();
			bool is_directed = m_view.is_directed();

			index_type *temp = new index_type[n];

			augment_edgelist(m, is_directed, edges, m_edges.pbase());
			prepare_ginclist_arrays(n, (index_type)m_ma, m_edges.pbase(),
					m_neighbors.pbase(), m_inc_edges.pbase(), m_degrees.pbase(), m_offsets.pbase(), temp);

			delete[] temp;
		}


	private:
		index_t m_ma;  // = ne for directed, = 2 * ne for undirected

		array1d<gvertex_pair<TInt> > m_edges;
		array1d<vertex_type> m_neighbors;
		array1d<edge_type> m_inc_edges;
		array1d<index_type> m_degrees;
		array1d<index_type> m_offsets;

		view_type m_view;

	}; // end class ginclist

}

#endif 
