/**
 * @file test_disjoint_sets.cpp
 *
 * Unit testing of disjoint sets
 *
 * @author Dahua Lin
 */


#include "bcs_test_basics.h"
#include <bcslib/data_structs/disjoint_sets.h>
#include <cstdlib>

using namespace bcs;
using namespace bcs::test;

// explicit instantiation for syntax checking

struct dse
{
	index_t i;

	dse() : i(0) { }

	dse(index_t i_) : i(i_) { }

	index_t index() const
	{
		return i;
	}
};

namespace bcs
{
	template<>
	struct index_convertible<dse>
	{
		static const bool value = true;
	};
}

template class bcs::disjoint_set_forest<dse>;


TEST( DisjointSetForest, Init )
{
	disjoint_set_forest<dse> s0(0);

	ASSERT_EQ(s0.size(), 0);
	ASSERT_EQ(s0.ncomponents(), 0);

	disjoint_set_forest<dse> s1(1);

	ASSERT_EQ(s1.size(), 1);
	ASSERT_EQ(s1.parent_index(0), 0);
	ASSERT_EQ(s1.rank(0), 0);
	ASSERT_EQ(s1.ncomponents(), 1);

	index_t n = 10;
	disjoint_set_forest<dse> s2(n);

	ASSERT_EQ(s2.size(), n);
	ASSERT_EQ(s2.ncomponents(), n);

	for (index_t i = 0; i < n; ++i)
	{
		dse x(i);
		ASSERT_EQ(s2.index(x), i);
		ASSERT_EQ(s2.parent_index(x), i);
		ASSERT_EQ(s2.rank(x), 0);
	}
}


TEST( DisjointSetForest, JoinAndCompress )
{
	disjoint_set_forest<dse> s(16);
	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 16);

	for (index_t i = 0; i < 16; ++i)
	{
		dse x(i);
		ASSERT_EQ( s.trace_root(x), i );
	}

	// join [0, (1)], [2, (3)], ..., [14, (15)]

	for (index_t i = 0; i < 8; ++i)
	{
		s.join(dse(2*i), dse(2*i+1));
	}

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 8);

	for (index_t i = 0; i < 16; ++i)
	{
		dse x(i);

		if (i % 2 == 0)
		{
			ASSERT_EQ( s.parent_index(x), i+1 );
			ASSERT_EQ( s.rank(x), 0 );
			ASSERT_EQ( s.trace_root(x), i+1 );
		}
		else
		{
			ASSERT_EQ( s.parent_index(x), i );
			ASSERT_EQ( s.rank(x), 1 );
			ASSERT_EQ( s.trace_root(x), i );
		}
	}

	// join [0, (1)] - [2, (3)] => [0, 1, 2, (3)]

	s.join(0, 2);

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 7);
	ASSERT_EQ(s.rank(1), 1);
	ASSERT_EQ(s.rank(3), 2 );

	ASSERT_EQ( s.parent_index(0), 3 );
	ASSERT_EQ( s.parent_index(1), 3 );
	ASSERT_EQ( s.parent_index(2), 3 );
	ASSERT_EQ( s.parent_index(3), 3 );

	ASSERT_EQ( s.trace_root(0), 3 );
	ASSERT_EQ( s.trace_root(1), 3 );
	ASSERT_EQ( s.trace_root(2), 3 );
	ASSERT_EQ( s.trace_root(3), 3 );

	// join [0, 1, 2, (3)] - [4, (5)] => [0, 1, 2, (3), 4, 5]

	s.join(1, 5);

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 6);
	ASSERT_EQ(s.rank(3), 2 );
	ASSERT_EQ(s.rank(5), 1);

	ASSERT_EQ( s.parent_index(0), 3 );
	ASSERT_EQ( s.parent_index(1), 3 );
	ASSERT_EQ( s.parent_index(2), 3 );
	ASSERT_EQ( s.parent_index(3), 3 );
	ASSERT_EQ( s.parent_index(4), 5 );
	ASSERT_EQ( s.parent_index(5), 3 );

	ASSERT_EQ( s.trace_root(0), 3 );
	ASSERT_EQ( s.trace_root(1), 3 );
	ASSERT_EQ( s.trace_root(2), 3 );
	ASSERT_EQ( s.trace_root(3), 3 );
	ASSERT_EQ( s.trace_root(4), 3 );
	ASSERT_EQ( s.trace_root(5), 3 );

	// join [6, (7)], [0, 1, 2, (3), 4, 5] => [0, 1, 2, (3), 4, 5, 6, 7]

	s.join(7, 2);

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 5);
	ASSERT_EQ(s.rank(7), 1);
	ASSERT_EQ(s.rank(3), 2 );

	ASSERT_EQ( s.parent_index(0), 3 );
	ASSERT_EQ( s.parent_index(1), 3 );
	ASSERT_EQ( s.parent_index(2), 3 );
	ASSERT_EQ( s.parent_index(3), 3 );
	ASSERT_EQ( s.parent_index(4), 5 );
	ASSERT_EQ( s.parent_index(5), 3 );
	ASSERT_EQ( s.parent_index(6), 7 );
	ASSERT_EQ( s.parent_index(7), 3 );

	ASSERT_EQ( s.trace_root(0), 3 );
	ASSERT_EQ( s.trace_root(1), 3 );
	ASSERT_EQ( s.trace_root(2), 3 );
	ASSERT_EQ( s.trace_root(3), 3 );
	ASSERT_EQ( s.trace_root(4), 3 );
	ASSERT_EQ( s.trace_root(5), 3 );
	ASSERT_EQ( s.trace_root(6), 3 );
	ASSERT_EQ( s.trace_root(7), 3 );

	// join [8, (9)], [10, (11)] => [8, 9, 10, (11)]

	s.join(9, 11);

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 4);
	ASSERT_EQ(s.rank(9), 1);
	ASSERT_EQ(s.rank(11), 2 );

	ASSERT_EQ( s.parent_index(8), 9 );
	ASSERT_EQ( s.parent_index(9), 11 );
	ASSERT_EQ( s.parent_index(10), 11 );
	ASSERT_EQ( s.parent_index(11), 11 );

	ASSERT_EQ( s.trace_root(8), 11 );
	ASSERT_EQ( s.trace_root(9), 11 );
	ASSERT_EQ( s.trace_root(10), 11 );
	ASSERT_EQ( s.trace_root(11), 11 );

	// join [0, 1, 2, (3), 4, 5, 6, 7] - [8, 9, 10, (11)] => [0, ..., (11)]

	s.join(3, 8);

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 3);
	ASSERT_EQ(s.rank(3), 2);
	ASSERT_EQ(s.rank(11), 3);

	ASSERT_EQ( s.parent_index(0), 3 );
	ASSERT_EQ( s.parent_index(1), 3 );
	ASSERT_EQ( s.parent_index(2), 3 );
	ASSERT_EQ( s.parent_index(3), 11 );
	ASSERT_EQ( s.parent_index(4), 5 );
	ASSERT_EQ( s.parent_index(5), 3 );
	ASSERT_EQ( s.parent_index(6), 7 );
	ASSERT_EQ( s.parent_index(7), 3 );
	ASSERT_EQ( s.parent_index(8), 11 );
	ASSERT_EQ( s.parent_index(9), 11 );
	ASSERT_EQ( s.parent_index(10), 11 );
	ASSERT_EQ( s.parent_index(11), 11 );

	ASSERT_EQ( s.trace_root(0), 11 );
	ASSERT_EQ( s.trace_root(1), 11 );
	ASSERT_EQ( s.trace_root(2), 11 );
	ASSERT_EQ( s.trace_root(3), 11 );
	ASSERT_EQ( s.trace_root(4), 11 );
	ASSERT_EQ( s.trace_root(5), 11 );
	ASSERT_EQ( s.trace_root(6), 11 );
	ASSERT_EQ( s.trace_root(7), 11 );
	ASSERT_EQ( s.trace_root(8), 11 );
	ASSERT_EQ( s.trace_root(9), 11 );
	ASSERT_EQ( s.trace_root(10), 11 );
	ASSERT_EQ( s.trace_root(11), 11 );

	// compress-all

	s.compress_all();

	ASSERT_EQ(s.size(), 16);
	ASSERT_EQ(s.ncomponents(), 3);

	ASSERT_TRUE( s.rank(0) == 0 && s.parent_index(0) == 11 && s.trace_root(0) == 11 );
	ASSERT_TRUE( s.rank(1) == 0 && s.parent_index(1) == 11 && s.trace_root(1) == 11 );
	ASSERT_TRUE( s.rank(2) == 0 && s.parent_index(2) == 11 && s.trace_root(2) == 11 );
	ASSERT_TRUE( s.rank(3) == 0 && s.parent_index(3) == 11 && s.trace_root(3) == 11 );
	ASSERT_TRUE( s.rank(4) == 0 && s.parent_index(4) == 11 && s.trace_root(4) == 11 );
	ASSERT_TRUE( s.rank(5) == 0 && s.parent_index(5) == 11 && s.trace_root(5) == 11 );
	ASSERT_TRUE( s.rank(6) == 0 && s.parent_index(6) == 11 && s.trace_root(6) == 11 );
	ASSERT_TRUE( s.rank(7) == 0 && s.parent_index(7) == 11 && s.trace_root(7) == 11 );
	ASSERT_TRUE( s.rank(8) == 0 && s.parent_index(8) == 11 && s.trace_root(8) == 11 );
	ASSERT_TRUE( s.rank(9) == 0 && s.parent_index(9) == 11 && s.trace_root(9) == 11 );
	ASSERT_TRUE( s.rank(10) == 0 && s.parent_index(10) == 11 && s.trace_root(10) == 11 );
	ASSERT_TRUE( s.rank(11) == 1 && s.parent_index(11) == 11 && s.trace_root(11) == 11 );

	ASSERT_TRUE( s.rank(12) == 0 && s.parent_index(12) == 13 && s.trace_root(12) == 13 );
	ASSERT_TRUE( s.rank(13) == 1 && s.parent_index(13) == 13 && s.trace_root(13) == 13 );

	ASSERT_TRUE( s.rank(14) == 0 && s.parent_index(14) == 15 && s.trace_root(14) == 15 );
	ASSERT_TRUE( s.rank(15) == 1 && s.parent_index(15) == 15 && s.trace_root(15) == 15 );
}


