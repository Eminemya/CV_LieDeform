/**
 * @file test_gview_base.cpp
 *
 * Unit testing of graph view basics
 * 
 * @author Dahua Lin
 */

#include "bcs_test_basics.h"

#include <bcslib/graph/gview_base.h>

using namespace bcs;
using namespace bcs::test;

// Some typedefs

typedef int32_t gint;
typedef gvertex<gint> vertex_t;
typedef gedge<gint> edge_t;
typedef gvertex_pair<gint> vertex_pair;
typedef natural_vertex_iterator<gint> viter;
typedef natural_edge_iterator<gint> eiter;

TEST( GViewBase, VertexAndEdge  )
{
	// vertices

	gint id1 = 3;
	vertex_t v1 = make_gvertex(id1);

	ASSERT_EQ(v1.id, id1);
	ASSERT_EQ(v1.index(), id1 - BCS_GRAPH_ENTITY_IDBASE);

	gint id2 = 5;
	vertex_t v2 = make_gvertex(id2);

	ASSERT_EQ(v2.id, id2);
	ASSERT_EQ(v2.index(), id2 - BCS_GRAPH_ENTITY_IDBASE);

	ASSERT_TRUE(v1 == v1);
	ASSERT_FALSE(v1 != v1);
	ASSERT_FALSE(v1 == v2);
	ASSERT_TRUE(v1 != v2);

	// edges

	edge_t e1 = make_gedge(id1);

	ASSERT_EQ(e1.id, id1);
	ASSERT_EQ(e1.index(), id1 - BCS_GRAPH_ENTITY_IDBASE);

	edge_t e2 = make_gedge(id2);

	ASSERT_EQ(e2.id, id2);
	ASSERT_EQ(e2.index(), id2 - BCS_GRAPH_ENTITY_IDBASE);

	ASSERT_TRUE(e1 == e1);
	ASSERT_FALSE(e1 != e1);
	ASSERT_FALSE(e1 == e2);
	ASSERT_TRUE(e1 != e2);

	// vertex pairs

	vertex_pair p1 = make_vertex_pair(id1, id2);
	vertex_pair p2 = make_vertex_pair(id2, id1);

	ASSERT_EQ(p1.s, v1);
	ASSERT_EQ(p1.t, v2);
	ASSERT_EQ(p2.s, v2);
	ASSERT_EQ(p2.t, v1);

	ASSERT_TRUE(p1 == p1);
	ASSERT_FALSE(p1 != p1);
	ASSERT_FALSE(p1 == p2);
	ASSERT_TRUE(p1 != p2);

	ASSERT_EQ( p1.flip(), p2 );
	ASSERT_EQ( p2.flip(), p1 );

	// incidence

	gint id3 = 10;
	vertex_t v3 = make_gvertex(id3);

	ASSERT_TRUE( is_incident(v1, p1) );
	ASSERT_TRUE( is_incident(v2, p1) );
	ASSERT_TRUE( is_incident(v1, p2) );
	ASSERT_TRUE( is_incident(v2, p2) );

	ASSERT_FALSE( is_incident(v3, p1) );
	ASSERT_FALSE( is_incident(v3, p2) );
}


TEST( GViewBase, NaturalIterators )
{
	gint id1 = 3;

	// vertex iterator

	viter::type vi0 = viter::get_default();
	viter::type vi1 = viter::from_id(id1);

	ASSERT_EQ( vi0->id, BCS_GRAPH_ENTITY_IDBASE );
	ASSERT_EQ( vi1->id, id1 );
	ASSERT_EQ( *vi1, make_gvertex(id1) );

	++vi1;

	ASSERT_EQ( vi1->id, id1+1);
	ASSERT_EQ( *vi1, make_gvertex(id1+1) );

	--vi1;

	ASSERT_EQ( vi1->id, id1);
	ASSERT_EQ( *vi1, make_gvertex(id1) );

	// edge iterator

	eiter::type ei0 = eiter::get_default();
	eiter::type ei1 = eiter::from_id(id1);

	ASSERT_EQ( ei0->id, BCS_GRAPH_ENTITY_IDBASE );
	ASSERT_EQ( ei1->id, id1 );
	ASSERT_EQ( *ei1, make_gedge(id1) );

	++ei1;

	ASSERT_EQ( ei1->id, id1+1);
	ASSERT_EQ( *ei1, make_gedge(id1+1) );

	--ei1;

	ASSERT_EQ( ei1->id, id1);
	ASSERT_EQ( *ei1, make_gedge(id1) );

}



