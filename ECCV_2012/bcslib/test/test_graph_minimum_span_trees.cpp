/*
 * @file test_graph_minimum_span_trees.h
 *
 * Unit Testing of Minimum Spanning Tree Algorithms
 *
 * @author Dahua Lin
 */


#include "bcs_graph_test_basics.h"
#include <bcslib/array/amap.h>
#include <bcslib/graph/gedgelist_view.h>
#include <bcslib/graph/ginclist.h>
#include <bcslib/graph/graph_minimum_span_trees.h>
#include <vector>
#include <iterator>
#include <cstdio>

using namespace bcs;
using namespace bcs::test;

typedef int32_t gint;
typedef gvertex<gint> vertex_t;
typedef gedge<gint> edge_t;
typedef gvertex_pair<gint> vpair_t;
typedef ginclist<gint> graph_t;

typedef int dist_t;
typedef caview_map<edge_t, dist_t> edge_dist_map_t;

// explicit instantiation for syntax checking

template class bcs::prim_traverser<graph_t, edge_dist_map_t, prim_default_heap<graph_t, dist_t>::type>;


bool verify_mst_edges(const std::vector<edge_t>& results, size_t ne, const gint *expects)
{
	if (results.size() != ne) return false;

	for (size_t i = 0; i < ne; ++i)
	{
		if (results[i].id != expects[i]) return false;
	}

	return true;
}


TEST( GraphMinSpanTrees, Kruskal )
{
	const gint n = 7;
	const gint m = 11;

	const gint vpair_ints[m * 2] = {
			1, 2,
			1, 4,
			2, 3,
			2, 4,
			2, 5,
			3, 5,
			4, 5,
			4, 6,
			5, 6,
			5, 7,
			6, 7
	};

	const dist_t edge_ds[m] = {
			7, 5, 8, 9, 7, 5, 15, 6, 8, 9, 11
	};
	edge_dist_map_t edge_distmap(edge_ds, (index_t)m);

	gedgelist_view<gint> g(n, m, false, (const vpair_t*)(vpair_ints));

	std::vector<edge_t> mst_edges;
	size_t ret = kruskal_minimum_span_tree(g, edge_distmap, std::back_inserter(mst_edges));
	ASSERT_EQ(1, ret);

	const gint expected_edges[n - 1] = {2, 6, 8, 1, 5, 10};
	ASSERT_TRUE( verify_mst_edges(mst_edges, n-1, expected_edges) );
}


TEST( GraphMinSpanTrees, Prim )
{
	const gint n = 7;
	const gint m = 11;

	const gint vpair_ints[m * 2] = {
			1, 2,
			1, 4,
			2, 3,
			2, 4,
			2, 5,
			3, 5,
			4, 5,
			4, 6,
			5, 6,
			5, 7,
			6, 7
	};

	const dist_t edge_ds[m * 2] = {
			7, 5, 8, 9, 7, 5, 15, 6, 8, 9, 11,
			7, 5, 8, 9, 7, 5, 15, 6, 8, 9, 11
	};
	edge_dist_map_t edge_distmap(edge_ds, (index_t)m);

	graph_t g(n, m, false, (const vpair_t*)(vpair_ints));

	std::vector<edge_t> mst_edges;
	vertex_t root = make_gvertex(1);
	prim_minimum_span_tree(g, edge_distmap, root, std::back_inserter(mst_edges));

	const gint expected_edges[n - 1] = {2, 8, 1, 5, 17, 10};
	ASSERT_TRUE( verify_mst_edges(mst_edges, n-1, expected_edges) );
}





