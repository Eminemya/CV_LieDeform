/**
 * @file test_graph_shortest_paths.cpp
 *
 * Unit Testing of shortest paths algorithms
 *
 * @author Dahua Lin
 */


#include "bcs_graph_test_basics.h"
#include <bcslib/array/amap.h>
#include <bcslib/graph/ginclist.h>
#include <bcslib/graph/graph_shortest_paths.h>
#include <vector>
#include <cstdio>

using namespace bcs;
using namespace bcs::test;


typedef int32_t gint;
typedef gvertex<gint> vertex_t;
typedef gedge<gint> edge_t;
typedef gvertex_pair<gint> vpair_t;
typedef ginclist<gint> graph_t;

typedef int dist_t;
typedef aview_map<edge_t, dist_t> edge_dist_map_t;
typedef array_map<vertex_t, dist_t> vertex_dist_map_t;
typedef dijkstra_default_heap<graph_t, vertex_dist_map_t>::type heap_t;

// explicit instantiation for syntax checking

template class bcs::dijkstra_traverser<graph_t, edge_dist_map_t, vertex_dist_map_t, heap_t>;

typedef dijkstra_traverser<graph_t, edge_dist_map_t, vertex_dist_map_t, heap_t> dijks_alg_t;


struct dijks_action
{
	enum type
	{
		DIJKS_SOURCE,
		DIJKS_ENROLL,
		DIJKS_EXAMINE,
		DIJKS_DISCOVER,
		DIJKS_RELAX,
		DIJKS_FINISH
	};

	type ty;
	vertex_t u;
	vertex_t v;
	dist_t dist;

	bool operator == (const dijks_action& r) const
	{
		return ty == r.ty && u == r.u && v == r.v && dist == r.dist;
	}

	bool operator != (const dijks_action& r) const
	{
		return !(operator == (r));
	}

	void print() const
	{
		switch (ty)
		{
		case DIJKS_SOURCE:
			printf("source(%d)", u.id);
			break;

		case DIJKS_ENROLL:
			printf("enroll(%d) -> %d", u.id, dist);
			break;

		case DIJKS_EXAMINE:
			printf("examine(%d, %d)", u.id, v.id);
			break;

		case DIJKS_DISCOVER:
			printf("discover(%d, %d) -> %d", u.id, v.id, dist);
			break;

		case DIJKS_RELAX:
			printf("relax(%d, %d) -> %d", u.id, v.id, dist);
			break;

		case DIJKS_FINISH:
			printf("finish(%d)", v.id);
			break;
		}
	}

	static dijks_action source(gint ui)
	{
		return source(make_gvertex(ui));
	}

	static dijks_action source(const vertex_t& u)
	{
		dijks_action a;
		a.ty = DIJKS_SOURCE;
		a.u = u;
		a.v = make_gvertex(gint(-1));
		a.dist = 0;
		return a;
	}

	static dijks_action enroll(gint ui, dist_t d)
	{
		return enroll(make_gvertex(ui), d);
	}

	static dijks_action enroll(const vertex_t& u, const dist_t& d)
	{
		dijks_action a;
		a.ty = DIJKS_ENROLL;
		a.u = u;
		a.v = make_gvertex(gint(-1));
		a.dist = d;
		return a;
	}

	static dijks_action examine(gint ui, gint vi)
	{
		return examine(make_gvertex(ui), make_gvertex(vi));
	}

	static dijks_action examine(const vertex_t& u, const vertex_t& v)
	{
		dijks_action a;
		a.ty = DIJKS_EXAMINE;
		a.u = u;
		a.v = v;
		a.dist = 0;
		return a;
	}

	static dijks_action discover(gint ui, gint vi, dist_t d)
	{
		return discover(make_gvertex(ui), make_gvertex(vi), d);
	}

	static dijks_action discover(const vertex_t& u, const vertex_t& v, const dist_t& d)
	{
		dijks_action a;
		a.ty = DIJKS_DISCOVER;
		a.u = u;
		a.v = v;
		a.dist = d;
		return a;
	}

	static dijks_action relax(gint ui, gint vi, dist_t d)
	{
		return relax(make_gvertex(ui), make_gvertex(vi), d);
	}

	static dijks_action relax(const vertex_t& u, const vertex_t& v, const dist_t& d)
	{
		dijks_action a;
		a.ty = DIJKS_RELAX;
		a.u = u;
		a.v = v;
		a.dist = d;
		return a;
	}

	static dijks_action finish(gint vi, dist_t d)
	{
		return finish(make_gvertex(vi), d);
	}

	static dijks_action finish(const vertex_t& v, const dist_t& d)
	{
		dijks_action a;
		a.ty = DIJKS_FINISH;
		a.u = make_gvertex(gint(-1));
		a.v = v;
		a.dist = d;
		return a;
	}

};


struct dijkstra_recorder
{
	dijkstra_recorder() : stop_enroll(false) { }

	void print_actions() const
	{
		size_t n = actions.size();
		for (size_t i = 0; i < n; ++i)
		{
			actions[i].print();
			printf("\n");
		}
	}

	bool verify_actions(const dijks_action* expected_actions, size_t n)
	{
		if (actions.size() != n) return false;

		for (size_t i = 0; i < n; ++i)
		{
			if (actions[i] != expected_actions[i]) return false;
		}

		return true;
	}

	void source(const vertex_t& u)
	{
		actions.push_back(dijks_action::source(u));
	}

	bool enroll(const vertex_t& u, const dist_t& d)
	{
		actions.push_back(dijks_action::enroll(u, d));
		return !stop_enroll;
	}

	bool examine_edge(const vertex_t& u, const vertex_t& v, const edge_t& e)
	{
		actions.push_back(dijks_action::examine(u, v));
		return true;
	}

	bool discover(const vertex_t& u, const vertex_t& v, const edge_t& e, const dist_t& pl)
	{
		actions.push_back(dijks_action::discover(u, v, pl));
		return true;
	}

	bool relax(const vertex_t& u, const vertex_t& v, const edge_t& e, const dist_t& pl)
	{
		actions.push_back(dijks_action::relax(u, v, pl));
		return true;
	}

	bool finish(const vertex_t& v, const dist_t& pl)
	{
		actions.push_back(dijks_action::finish(v, pl));
		return true;
	}

	std::vector<dijks_action> actions;
	bool stop_enroll;

};

// Test cases

struct bford_visitor
{
	array_map<vertex_t, vertex_t> preds;

	bford_visitor(gint n)
	: preds(n, make_gvertex(gint(0)))
	{
	}

	void update(const vertex_t& u, const vertex_t& v, const dist_t& d)
	{
		preds[v] = u;
	}
};


TEST( GraphShortestPaths, BellmanFord )
{
	const gint n = 5;
	const gint m = 10;
	const dist_t maxlen = 10000;

	const gint vpair_ints[m * 2] = {
			1, 2,
			1, 3,
			2, 3,
			3, 2,
			2, 4,
			3, 5,
			4, 5,
			5, 4,
			3, 4,
			5, 1
	};

	graph_t g(n, m, true, (const vpair_t*)(vpair_ints));

	dist_t edge_dists[m] = {10, 5, 2, 3, 1, 2, 4, 6, 9, 7};
	edge_dist_map_t edge_dist_map(edge_dists, m);

	vertex_dist_map_t spathlens(n, -1);
	vertex_t sv = make_gvertex(1);

	bford_visitor vis(n);

	bool ret = bellman_ford_shortest_paths(g, edge_dist_map, spathlens, maxlen, vis, sv);

	ASSERT_TRUE(ret);

	ASSERT_EQ(0, spathlens[make_gvertex(1)]);
	ASSERT_EQ(8, spathlens[make_gvertex(2)]);
	ASSERT_EQ(5, spathlens[make_gvertex(3)]);
	ASSERT_EQ(9, spathlens[make_gvertex(4)]);
	ASSERT_EQ(7, spathlens[make_gvertex(5)]);

	ASSERT_EQ(0, vis.preds[make_gvertex(1)].id);
	ASSERT_EQ(3, vis.preds[make_gvertex(2)].id);
	ASSERT_EQ(1, vis.preds[make_gvertex(3)].id);
	ASSERT_EQ(2, vis.preds[make_gvertex(4)].id);
	ASSERT_EQ(3, vis.preds[make_gvertex(5)].id);
}


TEST( GraphShortestPaths, DijkstraDirected )
{
	const gint n = 5;
	const gint m = 10;
	const dist_t maxlen = 10000;

	const gint vpair_ints[m * 2] = {
			1, 2,
			1, 3,
			2, 3,
			3, 2,
			2, 4,
			3, 5,
			4, 5,
			5, 4,
			3, 4,
			5, 1
	};

	graph_t g(n, m, true, (const vpair_t*)(vpair_ints));

	dist_t edge_dists[m] = {10, 5, 2, 3, 1, 2, 4, 6, 9, 7};
	edge_dist_map_t edge_dist_map(edge_dists, m);

	vertex_dist_map_t spathlens(n, -1);
	dijkstra_recorder recorder;
	vertex_t sv = make_gvertex(1);

	static const dijks_action expected_actions[] = {
			dijks_action::source(1),
			dijks_action::examine(1, 2),
			dijks_action::discover(1, 2, 10),
			dijks_action::examine(1, 3),
			dijks_action::discover(1, 3, 5),
			dijks_action::finish(1, 0),

			dijks_action::enroll(3, 5),
			dijks_action::examine(3, 2),
			dijks_action::relax(3, 2, 8),
			dijks_action::examine(3, 5),
			dijks_action::discover(3, 5, 7),
			dijks_action::examine(3, 4),
			dijks_action::discover(3, 4, 14),
			dijks_action::finish(3, 5),

			dijks_action::enroll(5, 7),
			dijks_action::examine(5, 4),
			dijks_action::relax(5, 4, 13),
			dijks_action::examine(5, 1),
			dijks_action::finish(5, 7),

			dijks_action::enroll(2, 8),
			dijks_action::examine(2, 3),
			dijks_action::examine(2, 4),
			dijks_action::relax(2, 4, 9),
			dijks_action::finish(2, 8),

			dijks_action::enroll(4, 9),
			dijks_action::examine(4, 5),
			dijks_action::finish(4, 9)
	};

	size_t nexpected = sizeof(expected_actions) / sizeof(dijks_action);

	dijkstra_shortest_paths(g, edge_dist_map, spathlens, maxlen, recorder, sv);
	// recorder.print_actions();

	ASSERT_TRUE( recorder.verify_actions(expected_actions, nexpected) );

	ASSERT_EQ(0, spathlens[make_gvertex(1)]);
	ASSERT_EQ(8, spathlens[make_gvertex(2)]);
	ASSERT_EQ(5, spathlens[make_gvertex(3)]);
	ASSERT_EQ(9, spathlens[make_gvertex(4)]);
	ASSERT_EQ(7, spathlens[make_gvertex(5)]);
}


TEST( GraphShortestPaths, DijkstraUndirected )
{
	const gint n = 6;
	const gint m = 9;
	const dist_t maxlen = 10000;

	const gint vpair_ints[m * 2] = {
			1, 2,
			1, 3,
			1, 6,
			2, 3,
			2, 4,
			3, 4,
			3, 6,
			4, 5,
			5, 6
	};

	graph_t g(n, m, false, (const vpair_t*)(vpair_ints));

	dist_t edge_dists[m * 2] = {
			7, 9, 14, 10, 15, 11, 2, 6, 1,
			7, 9, 14, 10, 15, 11, 2, 6, 1
	};

	edge_dist_map_t edge_dist_map(edge_dists, m * 2);

	vertex_dist_map_t spathlens(n, -1);
	dijkstra_recorder recorder;
	vertex_t sv = make_gvertex(1);

	static const dijks_action expected_actions[] = {
			dijks_action::source(1),
			dijks_action::examine(1, 2),
			dijks_action::discover(1, 2, 7),
			dijks_action::examine(1, 3),
			dijks_action::discover(1, 3, 9),
			dijks_action::examine(1, 6),
			dijks_action::discover(1, 6, 14),
			dijks_action::finish(1, 0),

			dijks_action::enroll(2, 7),
			dijks_action::examine(2, 3),
			dijks_action::examine(2, 4),
			dijks_action::discover(2, 4, 22),
			dijks_action::examine(2, 1),
			dijks_action::finish(2, 7),

			dijks_action::enroll(3, 9),
			dijks_action::examine(3, 4),
			dijks_action::relax(3, 4, 20),
			dijks_action::examine(3, 6),
			dijks_action::relax(3, 6, 11),
			dijks_action::examine(3, 1),
			dijks_action::examine(3, 2),
			dijks_action::finish(3, 9),

			dijks_action::enroll(6, 11),
			dijks_action::examine(6, 1),
			dijks_action::examine(6, 3),
			dijks_action::examine(6, 5),
			dijks_action::discover(6, 5, 12),
			dijks_action::finish(6, 11),

			dijks_action::enroll(5, 12),
			dijks_action::examine(5, 6),
			dijks_action::examine(5, 4),
			dijks_action::relax(5, 4, 18),
			dijks_action::finish(5, 12),

			dijks_action::enroll(4, 18),
			dijks_action::examine(4, 5),
			dijks_action::examine(4, 2),
			dijks_action::examine(4, 3),
			dijks_action::finish(4, 18)
	};

	size_t nexpected = sizeof(expected_actions) / sizeof(dijks_action);

	dijkstra_shortest_paths(g, edge_dist_map, spathlens, maxlen, recorder, sv);
	// recorder.print_actions();

	ASSERT_TRUE( recorder.verify_actions(expected_actions, nexpected) );

	ASSERT_EQ(0, spathlens[make_gvertex(1)]);
	ASSERT_EQ(7, spathlens[make_gvertex(2)]);
	ASSERT_EQ(9, spathlens[make_gvertex(3)]);
	ASSERT_EQ(18, spathlens[make_gvertex(4)]);
	ASSERT_EQ(12, spathlens[make_gvertex(5)]);
	ASSERT_EQ(11, spathlens[make_gvertex(6)]);
}







