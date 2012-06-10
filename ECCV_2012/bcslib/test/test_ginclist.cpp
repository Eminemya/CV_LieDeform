/**
 * @file test_ginclist.cpp
 *
 * Unit test of ginclist classes
 * 
 * @author Dahua Lin
 */

#include "bcs_graph_test_basics.h"
#include <bcslib/graph/ginclist.h>

using namespace bcs;
using namespace bcs::test;

// syntax checking by explicit instantiation

typedef int32_t gint;

template class bcs::ginclist_view<gint>;
template class bcs::ginclist<gint>;

#ifdef BCS_USE_STATIC_ASSERT

static_assert( (is_base_of<
		bcs::IGraphEdgeList<bcs::ginclist_view<gint> >,
		bcs::ginclist_view<gint> >::value),
		"ginclist_view base-class assertion failure");

static_assert( (is_base_of<
		bcs::IGraphAdjacencyList<bcs::ginclist_view<gint> >,
		bcs::ginclist_view<gint> >::value),
		"ginclist_view base-class assertion failure");

static_assert( (is_base_of<
		bcs::IGraphIncidenceList<bcs::ginclist_view<gint> >,
		bcs::ginclist_view<gint> >::value),
		"ginclist_view base-class assertion failure");

static_assert( (is_base_of<
		bcs::IGraphEdgeList<bcs::ginclist<gint> >,
		bcs::ginclist<gint> >::value),
		"ginclist base-class assertion failure");

static_assert( (is_base_of<
		bcs::IGraphAdjacencyList<bcs::ginclist<gint> >,
		bcs::ginclist<gint> >::value),
		"ginclist base-class assertion failure");

static_assert( (is_base_of<
		bcs::IGraphIncidenceList<bcs::ginclist<gint> >,
		bcs::ginclist<gint> >::value),
		"ginclist base-class assertion failure");

#endif


// typedefs

typedef gvertex<gint> vertex_t;
typedef gedge<gint> edge_t;
typedef gvertex_pair<gint> vertex_pair_t;
typedef natural_vertex_iterator<gint> viter;
typedef natural_edge_iterator<gint> eiter;

typedef bcs::gedgelist_view<gint> gedgelist_view_t;
typedef bcs::ginclist_view<gint> ginclist_view_t;
typedef bcs::ginclist<gint> ginclist_t;

// auxiliary functions

template<class Derived>
bool ginclist_verify_vertices(const IGraphIncidenceList<Derived>& G, const gint *vertex_ids, gint n)
{
	if (n != G.nvertices()) return false;
	return vertices_equal(G.vertices_begin(), G.vertices_end(), vertex_ids, n);
}

template<class Derived>
bool ginclist_verify_edges(const IGraphIncidenceList<Derived>& G, const gint *edge_ids, gint m)
{
	if (m != G.nedges()) return false;
	return edges_equal(G.edges_begin(), G.edges_end(), edge_ids, m);
}

template<class Derived>
bool ginclist_verify_edge_ends(const IGraphIncidenceList<Derived>& G, const vertex_pair_t *vpairs)
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


template<class Derived>
inline bool ginclist_verify_links(const IGraphIncidenceList<Derived>& G, gint vid, gint deg, const gint *nbs, const gint *eds)
{
	vertex_t v = make_gvertex(vid);
	if (G.out_degree(v) != deg) return false;

	if (deg > 0)
	{
		if (!vertices_equal(G.out_neighbors_begin(v), G.out_neighbors_end(v), nbs, deg)) return false;
		if (!edges_equal(G.out_edges_begin(v), G.out_edges_end(v), eds, deg)) return false;
	}

	return true;
}



// test cases

TEST( GIncList, ViewBasics )
{
	// prepare graph

	const gint n = 7;
	const gint m = 8;

	static gint vpairs_ints[m * 2] = {
			1, 2,
			1, 3,
			2, 4,
			4, 3,
			4, 5,
			5, 6,
			6, 7,
			7, 5
	};

	static gint vertices[n] = {1, 2, 3, 4, 5, 6, 7};
	static gint edges[m] = {1, 2, 3, 4, 5, 6, 7, 8};
	const vertex_pair_t *vpairs = (const vertex_pair_t*)vpairs_ints;

	// directed graph

	ginclist_t Gd(n, m, true, vpairs);
	ASSERT_EQ( Gd.nvertices(), n );
	ASSERT_EQ( Gd.nedges(), m );
	ASSERT_EQ( Gd.is_directed(), true );
	ASSERT_TRUE( ginclist_verify_vertices(Gd, vertices, n) );
	ASSERT_TRUE( ginclist_verify_edges(Gd, edges, m) );
	ASSERT_TRUE( ginclist_verify_edge_ends(Gd, vpairs) );

	const gint gd_deg1 = 2;
	gint gd_nbs1[gd_deg1] = {2, 3};
	gint gd_eds1[gd_deg1] = {1, 2};

	const gint gd_deg2 = 1;
	gint gd_nbs2[gd_deg2] = {4};
	gint gd_eds2[gd_deg2] = {3};

	const gint gd_deg3 = 0;
	const gint *gd_nbs3 = 0;
	const gint *gd_eds3 = 0;

	const gint gd_deg4 = 2;
	gint gd_nbs4[gd_deg4] = {3, 5};
	gint gd_eds4[gd_deg4] = {4, 5};

	const gint gd_deg5 = 1;
	gint gd_nbs5[gd_deg5] = {6};
	gint gd_eds5[gd_deg5] = {6};

	const gint gd_deg6 = 1;
	gint gd_nbs6[gd_deg6] = {7};
	gint gd_eds6[gd_deg6] = {7};

	const gint gd_deg7 = 1;
	gint gd_nbs7[gd_deg7] = {5};
	gint gd_eds7[gd_deg7] = {8};

	ASSERT_TRUE( ginclist_verify_links(Gd, 1, gd_deg1, gd_nbs1, gd_eds1) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 2, gd_deg2, gd_nbs2, gd_eds2) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 3, gd_deg3, gd_nbs3, gd_eds3) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 4, gd_deg4, gd_nbs4, gd_eds4) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 5, gd_deg5, gd_nbs5, gd_eds5) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 6, gd_deg6, gd_nbs6, gd_eds6) );
	ASSERT_TRUE( ginclist_verify_links(Gd, 7, gd_deg7, gd_nbs7, gd_eds7) );


	// undirected graph

	ginclist_t Gu(n, m, false, vpairs);
	ASSERT_EQ( Gu.nvertices(), n );
	ASSERT_EQ( Gu.nedges(), m );
	ASSERT_EQ( Gu.is_directed(), false );
	ASSERT_TRUE( ginclist_verify_vertices(Gu, vertices, n) );
	ASSERT_TRUE( ginclist_verify_edges(Gu, edges, m) );
	ASSERT_TRUE( ginclist_verify_edge_ends(Gu, vpairs) );

	const gint gu_deg1 = 2;
	gint gu_nbs1[gu_deg1] = {2, 3};
	gint gu_eds1[gu_deg1] = {1, 2};

	const gint gu_deg2 = 2;
	gint gu_nbs2[gu_deg2] = {4, 1};
	gint gu_eds2[gu_deg2] = {3, 9};

	const gint gu_deg3 = 2;
	gint gu_nbs3[gu_deg3] = {1, 4};
	gint gu_eds3[gu_deg3] = {10, 12};

	const gint gu_deg4 = 3;
	gint gu_nbs4[gu_deg4] = {3, 5, 2};
	gint gu_eds4[gu_deg4] = {4, 5, 11};

	const gint gu_deg5 = 3;
	gint gu_nbs5[gu_deg5] = {6, 4, 7};
	gint gu_eds5[gu_deg5] = {6, 13, 16};

	const gint gu_deg6 = 2;
	gint gu_nbs6[gu_deg6] = {7, 5};
	gint gu_eds6[gu_deg6] = {7, 14};

	const gint gu_deg7 = 2;
	gint gu_nbs7[gu_deg7] = {5, 6};
	gint gu_eds7[gu_deg7] = {8, 15};

	ASSERT_TRUE( ginclist_verify_links(Gu, 1, gu_deg1, gu_nbs1, gu_eds1) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 2, gu_deg2, gu_nbs2, gu_eds2) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 3, gu_deg3, gu_nbs3, gu_eds3) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 4, gu_deg4, gu_nbs4, gu_eds4) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 5, gu_deg5, gu_nbs5, gu_eds5) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 6, gu_deg6, gu_nbs6, gu_eds6) );
	ASSERT_TRUE( ginclist_verify_links(Gu, 7, gu_deg7, gu_nbs7, gu_eds7) );

}
