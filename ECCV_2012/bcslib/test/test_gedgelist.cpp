/**
 * @file test_gedgelist.cpp
 *
 * Test gedgelist_view and gedgelist
 * 
 * @author Dahua Lin
 */

#include "bcs_graph_test_basics.h"
#include <bcslib/graph/gedgelist_view.h>


using namespace bcs;
using namespace bcs::test;

// syntax checking by explicit instantiation

typedef int32_t gint;

template class bcs::gedgelist_view<gint>;

#ifdef BCS_USE_STATIC_ASSERT

static_assert( (is_base_of<
		bcs::IGraphEdgeList<bcs::gedgelist_view<gint> >,
		bcs::gedgelist_view<gint> >::value),
		"gedgelist_view base-class assertion failure");

#endif

// typedefs

typedef gvertex<gint> vertex_t;
typedef gedge<gint> edge_t;
typedef gvertex_pair<gint> vertex_pair_t;
typedef natural_vertex_iterator<gint> viter;
typedef natural_edge_iterator<gint> eiter;

typedef bcs::gedgelist_view<gint> gedgelist_view_t;


// auxiliary

template<class Derived>
bool gedgelist_verify_vertices(const IGraphEdgeList<Derived>& G, const gint *vertex_ids, gint n)
{
	if (n != G.nvertices()) return false;
	return vertices_equal(G.vertices_begin(), G.vertices_end(), vertex_ids, n);
}

template<class Derived>
bool gedgelist_verify_edges(const IGraphEdgeList<Derived>& G, const gint *edge_ids, gint m)
{
	if (m != G.nedges()) return false;
	return edges_equal(G.edges_begin(), G.edges_end(), edge_ids, m);
}

template<class Derived>
bool gedgelist_verify_edge_ends(const IGraphEdgeList<Derived>& G, const vertex_pair_t *vpairs)
{
	for (gint i = 0; i < G.nedges(); ++i)
	{
		edge_t e = make_gedge(BCS_GRAPH_ENTITY_IDBASE + i);
		vertex_pair_t vp = vpairs[i];

		vertex_t s = G.source(e);
		vertex_t t = G.target(e);

		if (!(vp.s == s && vp.t == t)) return false;
	}

	return true;
}

// test cases

TEST( GEdgeList, ViewBasics )
{
	const gint n = 7;
	const gint m = 8;

	static gint vpairs_ints[m * 2] = {
			1, 2,
			1, 3,
			2, 4,
			3, 4,
			4, 5,
			5, 6,
			6, 7,
			7, 5
	};

	static gint vertices[n] = {1, 2, 3, 4, 5, 6, 7};
	static gint edges[m] = {1, 2, 3, 4, 5, 6, 7, 8};
	const vertex_pair_t *vpairs = (const vertex_pair_t*)vpairs_ints;

	gedgelist_view_t Gd(n, m, true, vpairs);

	ASSERT_EQ( Gd.nvertices(), n );
	ASSERT_EQ( Gd.nedges(), m );
	ASSERT_EQ( Gd.is_directed(), true );
	ASSERT_TRUE( gedgelist_verify_vertices(Gd, vertices, n) );
	ASSERT_TRUE( gedgelist_verify_edges(Gd, edges, m) );
	ASSERT_TRUE( gedgelist_verify_edge_ends(Gd, vpairs) );

	gedgelist_view_t Gu(n, m, false, vpairs);

	ASSERT_EQ( Gu.nvertices(), n );
	ASSERT_EQ( Gu.nedges(), m );
	ASSERT_EQ( Gu.is_directed(), false );
	ASSERT_TRUE( gedgelist_verify_vertices(Gu, vertices, n) );
	ASSERT_TRUE( gedgelist_verify_edges(Gu, edges, m) );
	ASSERT_TRUE( gedgelist_verify_edge_ends(Gu, vpairs) );
}


