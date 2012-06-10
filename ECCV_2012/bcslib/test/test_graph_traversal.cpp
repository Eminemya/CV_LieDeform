/**
 * @file test_graph_traversal.cpp
 *
 * Unit testing of graph traversal
 *
 * @author Dahua Lin
 */


#include "bcs_graph_test_basics.h"
#include <bcslib/graph/ginclist.h>
#include <bcslib/graph/graph_traversal.h>
#include <vector>
#include <cstdio>

using namespace bcs;
using namespace bcs::test;

// explicit instantiation for syntax checking

typedef int32_t gint;
typedef gvertex<gint> vertex_t;
typedef gvertex_pair<gint> vpair_t;
typedef ginclist<gint> graph_t;

template class bcs::breadth_first_traverser<graph_t, std::queue<vertex_t> >;
template class bcs::depth_first_traverser<graph_t>;

struct gtr_action
{
	enum type
	{
		GTR_SOURCE,
		GTR_EXAMINE,
		GTR_DISCOVER,
		GTR_FINISH
	};

	type ty;
	vertex_t u;
	vertex_t v;

	void print() const
	{
		switch (ty)
		{
		case GTR_SOURCE:
			std::printf("source(%d)", v.id);
			break;
		case GTR_EXAMINE:
			std::printf("examine(%d, %d)", u.id, v.id);
			break;
		case GTR_DISCOVER:
			std::printf("discover(%d, %d)", u.id, v.id);
			break;
		case GTR_FINISH:
			std::printf("finish(%d)", v.id);
			break;
		}
	}

	bool operator == (const gtr_action& a) const
	{
		return ty == a.ty && u == a.u && v == a.v;
	}

	bool operator != (const gtr_action& a) const
	{
		return !(operator == (a));
	}

	static gtr_action source(vertex_t v_)
	{
		gtr_action a;
		a.ty = GTR_SOURCE;
		a.u = make_gvertex(gint(-1));
		a.v = v_;
		return a;
	}

	static gtr_action source(gint vi)
	{
		return source(make_gvertex(vi));
	}

	static gtr_action examine(vertex_t u_, vertex_t v_)
	{
		gtr_action a;
		a.ty = GTR_EXAMINE;
		a.u = u_;
		a.v = v_;
		return a;
	}

	static gtr_action examine(gint ui, gint vi)
	{
		return examine(make_gvertex(ui), make_gvertex(vi));
	}

	static gtr_action discover(vertex_t u_, vertex_t v_)
	{
		gtr_action a;
		a.ty = GTR_DISCOVER;
		a.u = u_;
		a.v = v_;
		return a;
	}

	static gtr_action discover(gint ui, gint vi)
	{
		return discover(make_gvertex(ui), make_gvertex(vi));
	}

	static gtr_action finish(vertex_t v_)
	{
		gtr_action a;
		a.ty = GTR_FINISH;
		a.u = make_gvertex(gint(-1));
		a.v = v_;
		return a;
	}

	static gtr_action finish(gint vi)
	{
		return finish(make_gvertex(vi));
	}
};


struct gtr_recording_visitor
{
	std::vector<gtr_action> records;

	void source(vertex_t v)
	{
		records.push_back(gtr_action::source(v));
	}

	bool examine(vertex_t u, vertex_t v, gvisit_status s)
	{
		records.push_back(gtr_action::examine(u, v));
		return true;
	}

	bool discover(vertex_t u, vertex_t v)
	{
		records.push_back(gtr_action::discover(u, v));
		return true;
	}

	bool finish(vertex_t v)
	{
		records.push_back(gtr_action::finish(v));
		return true;
	}

	bool verify_with(const gtr_action *expected, size_t n) const
	{
		if (records.size() == n)
		{
			for (size_t i = 0; i < n; ++i)
			{
				if (records[i] != expected[i]) return false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	void print_records() const
	{
		size_t n = records.size();
		for (size_t i = 0; i < n; ++i)
		{
			const gtr_action& a = records[i];
			a.print();
			printf("\n");
		}
	}

};


TEST( GraphTraversal, BFS )
{
	const gint n = 7;
	const gint m = 9;

	static gint edge_ends[m * 2] = {
			1, 2,
			2, 4,
			1, 3,
			3, 4,
			4, 5,
			5, 7,
			3, 6,
			6, 4,
			4, 1
	};

	graph_t g(n, m, true, (const vpair_t*)edge_ends);
	ASSERT_EQ(g.nvertices(), n);
	ASSERT_EQ(g.nedges(), m);

	static gtr_action expected_actions[] = {
			gtr_action::source(1),
			gtr_action::examine(1, 2),
			gtr_action::discover(1, 2),
			gtr_action::examine(1, 3),
			gtr_action::discover(1, 3),
			gtr_action::finish(1),
			gtr_action::examine(2, 4),
			gtr_action::discover(2, 4),
			gtr_action::finish(2),
			gtr_action::examine(3, 4),
			gtr_action::examine(3, 6),
			gtr_action::discover(3, 6),
			gtr_action::finish(3),
			gtr_action::examine(4, 5),
			gtr_action::discover(4, 5),
			gtr_action::examine(4, 1),
			gtr_action::finish(4),
			gtr_action::examine(6, 4),
			gtr_action::finish(6),
			gtr_action::examine(5, 7),
			gtr_action::discover(5, 7),
			gtr_action::finish(5),
			gtr_action::finish(7)
	};

	size_t na0 = sizeof(expected_actions) / sizeof(gtr_action);

	gtr_recording_visitor visitor;
	vertex_t v0 = make_gvertex((gint)1);
	breadth_first_traverse(g, visitor, v0);

	ASSERT_TRUE(visitor.verify_with(expected_actions, na0));
}



TEST( GraphTraversal, DFS )
{
	const gint n = 7;
	const gint m = 9;

	static gint edge_ends[m * 2] = {
			1, 2,
			2, 4,
			1, 3,
			3, 4,
			4, 5,
			5, 7,
			3, 6,
			6, 4,
			4, 1
	};

	graph_t g(n, m, true, (const vpair_t*)edge_ends);
	ASSERT_EQ(g.nvertices(), n);
	ASSERT_EQ(g.nedges(), m);

	static gtr_action expected_actions[] = {
			gtr_action::source(1),
			gtr_action::examine(1, 2),
			gtr_action::discover(1, 2),
			gtr_action::examine(2, 4),
			gtr_action::discover(2, 4),
			gtr_action::examine(4, 5),
			gtr_action::discover(4, 5),
			gtr_action::examine(5, 7),
			gtr_action::discover(5, 7),
			gtr_action::finish(7),
			gtr_action::finish(5),
			gtr_action::examine(4, 1),
			gtr_action::finish(4),
			gtr_action::finish(2),
			gtr_action::examine(1, 3),
			gtr_action::discover(1, 3),
			gtr_action::examine(3, 4),
			gtr_action::examine(3, 6),
			gtr_action::discover(3, 6),
			gtr_action::examine(6, 4),
			gtr_action::finish(6),
			gtr_action::finish(3),
			gtr_action::finish(1)
	};

	size_t na0 = sizeof(expected_actions) / sizeof(gtr_action);

	gtr_recording_visitor visitor;
	vertex_t v0 = make_gvertex((gint)1);
	depth_first_traverse(g, visitor, v0);

	ASSERT_TRUE(visitor.verify_with(expected_actions, na0));
}


TEST( GraphTraversal, Reachability )
{
	const gint n = 7;
	const gint m = 8;

	static gint edge_ends[m * 2] = {
			1, 2,
			2, 4,
			1, 3,
			3, 4,
			4, 5,
			5, 7,
			3, 6,
			6, 4,
	};

	graph_t g(n, m, true, (const vpair_t*)edge_ends);
	ASSERT_EQ(n, g.nvertices());
	ASSERT_EQ(m, g.nedges());

	EXPECT_EQ(6, count_reachable_vertices(g, make_gvertex(1)));
	EXPECT_EQ(3, count_reachable_vertices(g, make_gvertex(2)));
	EXPECT_EQ(4, count_reachable_vertices(g, make_gvertex(3)));
	EXPECT_EQ(2, count_reachable_vertices(g, make_gvertex(4)));
	EXPECT_EQ(1, count_reachable_vertices(g, make_gvertex(5)));
	EXPECT_EQ(3, count_reachable_vertices(g, make_gvertex(6)));
	EXPECT_EQ(0, count_reachable_vertices(g, make_gvertex(7)));
}


struct cc_action
{
	enum type
	{
		CCA_NEW,
		CCA_ADD,
		CCA_END
	};

	type ty;
	vertex_t v;

	bool equal(const cc_action& r) const
	{
		return ty == r.ty && v == r.v;
	}

	void print() const
	{
		switch (ty)
		{
		case CCA_NEW:
			std::printf("new");
			break;
		case CCA_ADD:
			std::printf("add %d", v.id);
			break;
		case CCA_END:
			std::printf("end");
			break;
		}
	}

	static cc_action newc()
	{
		cc_action a;
		a.ty = CCA_NEW;
		a.v.id = -1;
		return a;
	}

	static cc_action addv(const vertex_t& v)
	{
		cc_action a;
		a.ty = CCA_ADD;
		a.v = v;
		return a;
	}

	static cc_action addv(gint id)
	{
		cc_action a;
		a.ty = CCA_ADD;
		a.v.id = id;
		return a;
	}

	static cc_action endc()
	{
		cc_action a;
		a.ty = CCA_END;
		a.v.id = -1;
		return a;
	}
};


struct cc_recorder
{
	void new_component()
	{
		m_actions.push_back(cc_action::newc());
	}

	void end_component()
	{
		m_actions.push_back(cc_action::endc());
	}

	void add_vertex(const vertex_t& v)
	{
		m_actions.push_back(cc_action::addv(v));
	}

	std::vector<cc_action> m_actions;

	void print_actions() const
	{
		size_t n = m_actions.size();
		for (size_t i = 0; i < n; ++i)
		{
			m_actions[i].print();
			printf("\n");
		}
	}

	bool verify(const cc_action* expected, size_t n0)
	{
		if (m_actions.size() != n0) return false;
		for (size_t i = 0; i < n0; ++i)
		{
			if (!m_actions[i].equal(expected[i])) return false;
		}
		return true;
	}
};


TEST( GraphTraversal, ConnectedComponents )
{
	const gint n = 7;
	const gint m = 7;

	static gint edge_ends[m * 2] = {
			1, 2,
			2, 4,
			1, 3,
			3, 4,
			7, 6,
			6, 5,
			5, 7
	};

	graph_t g(n, m, false, (const vpair_t*)edge_ends);
	ASSERT_EQ(n, g.nvertices());
	ASSERT_EQ(m, g.nedges());

	cc_recorder recorder;
	size_t ncc = find_connected_components(g, recorder);

	ASSERT_EQ(2, ncc);

	cc_action expected[] = {
			cc_action::newc(),
			cc_action::addv(1),
			cc_action::addv(2),
			cc_action::addv(3),
			cc_action::addv(4),
			cc_action::endc(),

			cc_action::newc(),
			cc_action::addv(5),
			cc_action::addv(7),
			cc_action::addv(6),
			cc_action::endc()
	};
	size_t nexpected = sizeof(expected) / sizeof(cc_action);

	ASSERT_TRUE( recorder.verify(expected, nexpected) );
}








