/**
 * @file test_index_selection.cpp
 *
 * The Unit Testing for index_selectors.h
 *
 * @author Dahua Lin
 */

#include "bcs_test_basics.h"
#include <bcslib/array/aindex.h>

#include <functional>

using namespace bcs;
using namespace bcs::test;


template<class IndexSelector>
bool verify_indices(const IndexSelector& S, const index_t *ref, size_t n)
{
	if (S.size() != n) return false;

	for (index_t i = 0; i < (index_t)n; ++i)
	{
		if (S[i] != ref[i]) return false;
	}
	return collection_equal(S.begin(), S.end(), ref, n);
}


TEST( ArrayIndex, Range )
{
	range rg0;

	ASSERT_EQ( rg0.dim(), 0 );
	ASSERT_EQ( rg0.size(), 0 );
	ASSERT_EQ( rg0.begin_index(), 0 );
	ASSERT_EQ( rg0.end_index(), 0 );
	EXPECT_TRUE( rg0.begin() == rg0.end() );
	EXPECT_TRUE( rg0 == rg0 );

	range rg1(2, 5);
	index_t rg1_inds[3] = {2, 3, 4};
	ASSERT_EQ( rg1.dim(), 3 );
	ASSERT_EQ( rg1.size(), 3 );
	ASSERT_EQ( rg1.begin_index(), 2);
	ASSERT_EQ( rg1.end_index(), 5 );
	ASSERT_EQ( rg1.front(), 2 );
	ASSERT_EQ( rg1.back(), 4 );
	EXPECT_TRUE( verify_indices(rg1, rg1_inds, 3) );
	EXPECT_TRUE( rg1 == rg1 );

	EXPECT_TRUE( rg0 != rg1 );

	EXPECT_EQ( rg1, rgn(2, 5) );
	EXPECT_EQ( rg1, rgn_n(2, 3) );

	EXPECT_EQ( indexer_map<range>::get_offset(8, rg1), 2 );
	EXPECT_EQ( indexer_map<range>::get_indexer(8, rg1), id_ind(3) );
	EXPECT_EQ( indexer_map<range>::get_stepped_indexer(8, 2, rg1), step_ind(3, 2) );
}


TEST( ArrayIndex, StepRange )
{
	step_range rg0;

	ASSERT_EQ( rg0.dim(), 0 );
	ASSERT_EQ( rg0.size(), 0 );
	ASSERT_EQ( rg0.step(), 0 );
	ASSERT_EQ( rg0.begin_index(), 0 );
	ASSERT_EQ( rg0.end_index(), 0 );
	ASSERT_TRUE( rg0.begin() == rg0.end() );
	EXPECT_TRUE( rg0 == rg0 );

	step_range rg1 = step_range::from_begin_dim(1, 3, 4);
	index_t rg1_inds[3] = {1, 5, 9};

	ASSERT_EQ( rg1.dim(), 3 );
	ASSERT_EQ( rg1.size(), 3 );
	ASSERT_EQ( rg1.begin_index(), 1 );
	ASSERT_EQ( rg1.end_index(), 13 );
	ASSERT_EQ( rg1.front(), 1 );
	ASSERT_EQ( rg1.back(), 9 );
	EXPECT_TRUE( verify_indices(rg1, rg1_inds, 3) );
	EXPECT_TRUE( rg1 == rg1 );
	EXPECT_EQ( rg1, rgn_n(1, 3, 4) );

	EXPECT_EQ( indexer_map<step_range>::get_offset(12, rg1), 1 );
	EXPECT_EQ( indexer_map<step_range>::get_indexer(12, rg1), step_ind(3, 4) );
	EXPECT_EQ( indexer_map<step_range>::get_stepped_indexer(12, 2, rg1), step_ind(3, 8) );

	step_range rg2 = step_range::from_begin_end(1, 11, 3);
	index_t rg2_inds[4] = {1, 4, 7, 10};

	ASSERT_EQ( rg2.dim(), 4 );
	ASSERT_EQ( rg2.size(), 4 );
	ASSERT_EQ( rg2.begin_index(), 1 );
	ASSERT_EQ( rg2.end_index(), 13 );
	ASSERT_EQ( rg2.front(), 1 );
	ASSERT_EQ( rg2.back(), 10 );
	EXPECT_TRUE( verify_indices(rg2, rg2_inds, 4) );
	EXPECT_TRUE( rg2 == rg2 );
	EXPECT_EQ( rg2, rgn(1, 11, 3) );

	step_range rg3 = step_range::from_begin_end(1, 9, 4);
	index_t rg3_inds[2] = {1, 5};

	ASSERT_EQ( rg3.dim(), 2 );
	ASSERT_EQ( rg3.size(), 2 );
	ASSERT_EQ( rg3.begin_index(), 1 );
	ASSERT_EQ( rg3.end_index(), 9 );
	ASSERT_EQ( rg3.front(), 1 );
	ASSERT_EQ( rg3.back(), 5 );
	EXPECT_TRUE( verify_indices(rg3, rg3_inds, 2) );
	EXPECT_TRUE( rg3 == rg3 );
	EXPECT_EQ( rg3, rgn(1, 9, 4) );

	step_range rg4 = step_range::from_begin_end(9, 0, -3);
	index_t rg4_inds[3] = {9, 6, 3};

	ASSERT_EQ( rg4.dim(), 3 );
	ASSERT_EQ( rg4.size(), 3 );
	ASSERT_EQ( rg4.begin_index(), 9 );
	ASSERT_EQ( rg4.end_index(), 0 );
	ASSERT_EQ( rg4.front(), 9 );
	ASSERT_EQ( rg4.back(), 3 );
	EXPECT_TRUE( verify_indices(rg4, rg4_inds, 3) );
	EXPECT_TRUE( rg4 == rg4 );
	EXPECT_EQ( rg4, rgn(9, 0, -3) );

	EXPECT_EQ( indexer_map<step_range>::get_offset(12, rg4), 9 );
	EXPECT_EQ( indexer_map<step_range>::get_indexer(12, rg4), step_ind(3, -3) );
	EXPECT_EQ( indexer_map<step_range>::get_stepped_indexer(12, 2, rg4), step_ind(3, -6) );

	step_range rg5 = step_range::from_begin_end(1, 4, -1);
	ASSERT_EQ( rg5.dim(), 0 );
	ASSERT_EQ( rg5.size(), 0 );
	ASSERT_TRUE( rg5.begin_index() == rg5.end_index() );
	EXPECT_TRUE( rg5 == rg5 );
	EXPECT_EQ( rg5, rgn(1, 4, -1) );
}


TEST( ArrayIndex, RepRange )
{
	rep_range rs0;
	ASSERT_EQ( rs0.index(), 0 );
	ASSERT_EQ( rs0.size(), 0 );
	ASSERT_TRUE( rs0.begin() == rs0.end() );
	EXPECT_TRUE( rs0 == rs0 );

	rep_range rs1(2, 5);
	index_t rs1_inds[5] = {2, 2, 2, 2, 2};

	ASSERT_EQ( rs1.size(), 5 );
	ASSERT_EQ( rs1.dim(), 5 );
	ASSERT_EQ( rs1.index(), 2 );
	ASSERT_TRUE( verify_indices(rs1, rs1_inds, 5) );
	ASSERT_TRUE( rs1 == rs1 );
	EXPECT_TRUE( rs1 == rep(2, 5) );

	EXPECT_EQ( indexer_map<rep_range>::get_offset(12, rs1), 2 );
	EXPECT_EQ( indexer_map<rep_range>::get_indexer(12, rs1), rep_ind(5) );
	EXPECT_EQ( indexer_map<rep_range>::get_stepped_indexer(12, 2, rs1), rep_ind(5) );

	EXPECT_TRUE( rs1 != rs0 );
}


TEST( ArrayIndex, Whole )
{
	EXPECT_TRUE( verify_indices(rgn(0, whole()), BCS_NULL, 0) );
	index_t w1[5] = {0, 1, 2, 3, 4};
	EXPECT_TRUE( verify_indices(rgn(5, whole()), w1, 5) );

	EXPECT_EQ( indexer_map<whole>::get_offset(8, whole()), 0 );
	EXPECT_EQ( indexer_map<whole>::get_indexer(8, whole()), id_ind(8) );
	EXPECT_EQ( indexer_map<whole>::get_stepped_indexer(8, 2, whole()), step_ind(8, 2) );
}


TEST( ArrayIndex, RepWhole )
{
	EXPECT_TRUE( verify_indices(rgn(0, rev_whole()), BCS_NULL, 0) );
	index_t rw1[5] = {4, 3, 2, 1, 0};
	EXPECT_TRUE( verify_indices(rgn(5, rev_whole()), rw1, 5) );

	EXPECT_EQ( indexer_map<rev_whole>::get_offset(8, rev_whole()), 7 );
	EXPECT_EQ( indexer_map<rev_whole>::get_indexer(8, rev_whole()), step_ind(8, -1) );
	EXPECT_EQ( indexer_map<rev_whole>::get_stepped_indexer(8, 2, rev_whole()), step_ind(8, -2) );
}


