/**
 * @file test_basic_algorithms.cpp
 *
 * Unit test of the basic algorithms
 * 
 * @author Dahua Lin
 */


#include "bcs_test_basics.h"

#include <functional>
#include <vector>

#include <bcslib/base/basic_algorithms.h>

using namespace bcs;
using namespace bcs::test;

template<typename T>
struct val_idx
{
	T value;
	index_t index;
};

template<typename T>
val_idx<T> mk_vidx(const T& v, const index_t& i)
{
	val_idx<T> vi;
	vi.value = v;
	vi.index = i;
	return vi;
}

template<typename T>
std::pair<val_idx<T>, val_idx<T> > mk_cpair(const val_idx<T>& lhs, const val_idx<T>& rhs)
{
	return std::pair<val_idx<T>, val_idx<T> >(lhs, rhs);
}

template<typename T>
inline bool operator < (const val_idx<T>& lhs, const val_idx<T>& rhs)
{
	return lhs.value < rhs.value;
}

template<typename T>
inline bool operator > (const val_idx<T>& lhs, const val_idx<T>& rhs)
{
	return lhs.value > rhs.value;
}

template<typename T>
inline bool operator == (const val_idx<T>& lhs, const val_idx<T>& rhs)
{
	return lhs.value == rhs.value && lhs.index == rhs.index;
}

TEST( BasicAlgs, MinAndMaxE2 )
{
	val_idx<double> v1 = mk_vidx(1.0, 1);
	val_idx<double> v2 = mk_vidx(2.0, 2);

	val_idx<double> p1 = mk_vidx(5.0, 1);
	val_idx<double> p2 = mk_vidx(5.0, 2);

	std::greater<val_idx<double> > comp;

	EXPECT_EQ( min(v1, v2), v1 );
	EXPECT_EQ( min(v2, v1), v1 );
	EXPECT_EQ( min(p1, p2), p1 );

	EXPECT_EQ( min(v1, v2, comp), v2 );
	EXPECT_EQ( min(v2, v1, comp), v2 );
	EXPECT_EQ( min(p1, p2, comp), p1 );

	EXPECT_EQ( max(v1, v2), v2 );
	EXPECT_EQ( max(v2, v1), v2 );
	EXPECT_EQ( max(p1, p2), p1 );

	EXPECT_EQ( max(v1, v2, comp), v1 );
	EXPECT_EQ( max(v2, v1, comp), v1 );
	EXPECT_EQ( max(p1, p2, comp), p1 );

	EXPECT_EQ( bcs::minmax(v1, v2), mk_cpair(v1, v2) );
	EXPECT_EQ( bcs::minmax(v2, v1), mk_cpair(v1, v2) );
	EXPECT_EQ( bcs::minmax(p1, p2), mk_cpair(p1, p2) );

	EXPECT_EQ( bcs::minmax(v1, v2, comp), mk_cpair(v2, v1) );
	EXPECT_EQ( bcs::minmax(v2, v1, comp), mk_cpair(v2, v1) );
	EXPECT_EQ( bcs::minmax(p1, p2, comp), mk_cpair(p1, p2) );
}


TEST( BasicAlgs, MinAndMaxE3 )
{
	val_idx<double> v1 = mk_vidx(1.0, 1);
	val_idx<double> v2 = mk_vidx(2.0, 2);
	val_idx<double> v3 = mk_vidx(3.0, 3);

	val_idx<double> p1 = mk_vidx(5.0, 1);
	val_idx<double> p2 = mk_vidx(5.0, 2);
	val_idx<double> p3 = mk_vidx(5.0, 3);

	std::greater<val_idx<double> > comp;

	EXPECT_EQ( min(v1, v2, v3), v1 );
	EXPECT_EQ( min(v1, v3, v2), v1 );
	EXPECT_EQ( min(v2, v1, v3), v1 );
	EXPECT_EQ( min(v2, v3, v1), v1 );
	EXPECT_EQ( min(v3, v1, v2), v1 );
	EXPECT_EQ( min(v3, v2, v1), v1 );
	EXPECT_EQ( min(p1, p2, p3), p1 );

	EXPECT_EQ( min(v1, v2, v3, comp), v3 );
	EXPECT_EQ( min(v1, v3, v2, comp), v3 );
	EXPECT_EQ( min(v2, v1, v3, comp), v3 );
	EXPECT_EQ( min(v2, v3, v1, comp), v3 );
	EXPECT_EQ( min(v3, v1, v2, comp), v3 );
	EXPECT_EQ( min(v3, v2, v1, comp), v3 );
	EXPECT_EQ( min(p1, p2, p3, comp), p1 );

	EXPECT_EQ( max(v1, v2, v3), v3 );
	EXPECT_EQ( max(v1, v3, v2), v3 );
	EXPECT_EQ( max(v2, v1, v3), v3 );
	EXPECT_EQ( max(v2, v3, v1), v3 );
	EXPECT_EQ( max(v3, v1, v2), v3 );
	EXPECT_EQ( max(v3, v2, v1), v3 );
	EXPECT_EQ( max(p1, p2, p3), p1 );

	EXPECT_EQ( max(v1, v2, v3, comp), v1 );
	EXPECT_EQ( max(v1, v3, v2, comp), v1 );
	EXPECT_EQ( max(v2, v1, v3, comp), v1 );
	EXPECT_EQ( max(v2, v3, v1, comp), v1 );
	EXPECT_EQ( max(v3, v1, v2, comp), v1 );
	EXPECT_EQ( max(v3, v2, v1, comp), v1 );
	EXPECT_EQ( max(p1, p2, p3, comp), p1 );

	EXPECT_EQ( mk_cpair(v1, v3), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v1, v2, v3), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v1, v3, v2), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v2, v1, v3), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v2, v3, v1), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v3, v1, v2), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(v3, v2, v1), mk_cpair(v1, v3) );
	EXPECT_EQ( minmax(p1, p2, p3), mk_cpair(p1, p3) );

	EXPECT_EQ( minmax(v1, v2, v3, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(v1, v3, v2, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(v2, v1, v3, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(v2, v3, v1, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(v3, v1, v2, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(v3, v2, v1, comp), mk_cpair(v3, v1) );
	EXPECT_EQ( minmax(p1, p2, p3, comp), mk_cpair(p1, p3) );
}


TEST( BasicAlgs, MinAndMaxE4 )
{
	val_idx<double> v1 = mk_vidx(1.0, 1);
	val_idx<double> v2 = mk_vidx(2.0, 2);
	val_idx<double> v3 = mk_vidx(3.0, 3);
	val_idx<double> v4 = mk_vidx(4.0, 4);

	val_idx<double> p1 = mk_vidx(5.0, 1);
	val_idx<double> p2 = mk_vidx(5.0, 2);
	val_idx<double> p3 = mk_vidx(5.0, 3);
	val_idx<double> p4 = mk_vidx(5.0, 4);

	std::greater<val_idx<double> > comp;

	// min

	EXPECT_EQ( min(v1, v2, v3, v4), v1 );
	EXPECT_EQ( min(v1, v2, v4, v3), v1 );
	EXPECT_EQ( min(v1, v3, v2, v4), v1 );
	EXPECT_EQ( min(v1, v3, v4, v2), v1 );
	EXPECT_EQ( min(v1, v4, v2, v3), v1 );
	EXPECT_EQ( min(v1, v4, v3, v2), v1 );

	EXPECT_EQ( min(v2, v1, v3, v4), v1 );
	EXPECT_EQ( min(v2, v1, v4, v3), v1 );
	EXPECT_EQ( min(v2, v3, v1, v4), v1 );
	EXPECT_EQ( min(v2, v3, v4, v1), v1 );
	EXPECT_EQ( min(v2, v4, v1, v3), v1 );
	EXPECT_EQ( min(v2, v4, v3, v1), v1 );

	EXPECT_EQ( min(v3, v2, v1, v4), v1 );
	EXPECT_EQ( min(v3, v2, v4, v1), v1 );
	EXPECT_EQ( min(v3, v1, v2, v4), v1 );
	EXPECT_EQ( min(v3, v1, v4, v2), v1 );
	EXPECT_EQ( min(v3, v4, v1, v2), v1 );
	EXPECT_EQ( min(v3, v4, v2, v1), v1 );

	EXPECT_EQ( min(v4, v1, v2, v3), v1 );
	EXPECT_EQ( min(v4, v1, v3, v2), v1 );
	EXPECT_EQ( min(v4, v2, v1, v3), v1 );
	EXPECT_EQ( min(v4, v2, v3, v1), v1 );
	EXPECT_EQ( min(v4, v3, v1, v2), v1 );
	EXPECT_EQ( min(v4, v3, v2, v1), v1 );

	EXPECT_EQ( min(p1, p2, p3, p4), p1 );

	// min (comp)

	EXPECT_EQ( min(v1, v2, v3, v4, comp), v4 );
	EXPECT_EQ( min(v1, v2, v4, v3, comp), v4 );
	EXPECT_EQ( min(v1, v3, v2, v4, comp), v4 );
	EXPECT_EQ( min(v1, v3, v4, v2, comp), v4 );
	EXPECT_EQ( min(v1, v4, v2, v3, comp), v4 );
	EXPECT_EQ( min(v1, v4, v3, v2, comp), v4 );

	EXPECT_EQ( min(v2, v1, v3, v4, comp), v4 );
	EXPECT_EQ( min(v2, v1, v4, v3, comp), v4 );
	EXPECT_EQ( min(v2, v3, v1, v4, comp), v4 );
	EXPECT_EQ( min(v2, v3, v4, v1, comp), v4 );
	EXPECT_EQ( min(v2, v4, v1, v3, comp), v4 );
	EXPECT_EQ( min(v2, v4, v3, v1, comp), v4 );

	EXPECT_EQ( min(v3, v2, v1, v4, comp), v4 );
	EXPECT_EQ( min(v3, v2, v4, v1, comp), v4 );
	EXPECT_EQ( min(v3, v1, v2, v4, comp), v4 );
	EXPECT_EQ( min(v3, v1, v4, v2, comp), v4 );
	EXPECT_EQ( min(v3, v4, v1, v2, comp), v4 );
	EXPECT_EQ( min(v3, v4, v2, v1, comp), v4 );

	EXPECT_EQ( min(v4, v1, v2, v3, comp), v4 );
	EXPECT_EQ( min(v4, v1, v3, v2, comp), v4 );
	EXPECT_EQ( min(v4, v2, v1, v3, comp), v4 );
	EXPECT_EQ( min(v4, v2, v3, v1, comp), v4 );
	EXPECT_EQ( min(v4, v3, v1, v2, comp), v4 );
	EXPECT_EQ( min(v4, v3, v2, v1, comp), v4 );

	EXPECT_EQ( min(p1, p2, p3, p4, comp), p1 );

	// max

	EXPECT_EQ( max(v1, v2, v3, v4), v4 );
	EXPECT_EQ( max(v1, v2, v4, v3), v4 );
	EXPECT_EQ( max(v1, v3, v2, v4), v4 );
	EXPECT_EQ( max(v1, v3, v4, v2), v4 );
	EXPECT_EQ( max(v1, v4, v2, v3), v4 );
	EXPECT_EQ( max(v1, v4, v3, v2), v4 );

	EXPECT_EQ( max(v2, v1, v3, v4), v4 );
	EXPECT_EQ( max(v2, v1, v4, v3), v4 );
	EXPECT_EQ( max(v2, v3, v1, v4), v4 );
	EXPECT_EQ( max(v2, v3, v4, v1), v4 );
	EXPECT_EQ( max(v2, v4, v1, v3), v4 );
	EXPECT_EQ( max(v2, v4, v3, v1), v4 );

	EXPECT_EQ( max(v3, v2, v1, v4), v4 );
	EXPECT_EQ( max(v3, v2, v4, v1), v4 );
	EXPECT_EQ( max(v3, v1, v2, v4), v4 );
	EXPECT_EQ( max(v3, v1, v4, v2), v4 );
	EXPECT_EQ( max(v3, v4, v1, v2), v4 );
	EXPECT_EQ( max(v3, v4, v2, v1), v4 );

	EXPECT_EQ( max(v4, v1, v2, v3), v4 );
	EXPECT_EQ( max(v4, v1, v3, v2), v4 );
	EXPECT_EQ( max(v4, v2, v1, v3), v4 );
	EXPECT_EQ( max(v4, v2, v3, v1), v4 );
	EXPECT_EQ( max(v4, v3, v1, v2), v4 );
	EXPECT_EQ( max(v4, v3, v2, v1), v4 );

	EXPECT_EQ( max(p1, p2, p3, p4), p1 );

	// max (comp)

	EXPECT_EQ( max(v1, v2, v3, v4, comp), v1 );
	EXPECT_EQ( max(v1, v2, v4, v3, comp), v1 );
	EXPECT_EQ( max(v1, v3, v2, v4, comp), v1 );
	EXPECT_EQ( max(v1, v3, v4, v2, comp), v1 );
	EXPECT_EQ( max(v1, v4, v2, v3, comp), v1 );
	EXPECT_EQ( max(v1, v4, v3, v2, comp), v1 );

	EXPECT_EQ( max(v2, v1, v3, v4, comp), v1 );
	EXPECT_EQ( max(v2, v1, v4, v3, comp), v1 );
	EXPECT_EQ( max(v2, v3, v1, v4, comp), v1 );
	EXPECT_EQ( max(v2, v3, v4, v1, comp), v1 );
	EXPECT_EQ( max(v2, v4, v1, v3, comp), v1 );
	EXPECT_EQ( max(v2, v4, v3, v1, comp), v1 );

	EXPECT_EQ( max(v3, v2, v1, v4, comp), v1 );
	EXPECT_EQ( max(v3, v2, v4, v1, comp), v1 );
	EXPECT_EQ( max(v3, v1, v2, v4, comp), v1 );
	EXPECT_EQ( max(v3, v1, v4, v2, comp), v1 );
	EXPECT_EQ( max(v3, v4, v1, v2, comp), v1 );
	EXPECT_EQ( max(v3, v4, v2, v1, comp), v1 );

	EXPECT_EQ( max(v4, v1, v2, v3, comp), v1 );
	EXPECT_EQ( max(v4, v1, v3, v2, comp), v1 );
	EXPECT_EQ( max(v4, v2, v1, v3, comp), v1 );
	EXPECT_EQ( max(v4, v2, v3, v1, comp), v1 );
	EXPECT_EQ( max(v4, v3, v1, v2, comp), v1 );
	EXPECT_EQ( max(v4, v3, v2, v1, comp), v1 );

	EXPECT_EQ( max(p1, p2, p3, p4, comp), p1 );

	// minmax

	EXPECT_EQ( minmax(v1, v2, v3, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v1, v2, v4, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v1, v3, v2, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v1, v3, v4, v2), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v1, v4, v2, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v1, v4, v3, v2), mk_cpair(v1, v4) );

	EXPECT_EQ( minmax(v2, v1, v3, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v2, v1, v4, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v2, v3, v1, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v2, v3, v4, v1), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v2, v4, v1, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v2, v4, v3, v1), mk_cpair(v1, v4) );

	EXPECT_EQ( minmax(v3, v2, v1, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v3, v2, v4, v1), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v3, v1, v2, v4), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v3, v1, v4, v2), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v3, v4, v1, v2), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v3, v4, v2, v1), mk_cpair(v1, v4) );

	EXPECT_EQ( minmax(v4, v1, v2, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v4, v1, v3, v2), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v4, v2, v1, v3), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v4, v2, v3, v1), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v4, v3, v1, v2), mk_cpair(v1, v4) );
	EXPECT_EQ( minmax(v4, v3, v2, v1), mk_cpair(v1, v4) );

	EXPECT_EQ( minmax(p1, p2, p3, p4), mk_cpair(p1, p4) );

	// minmax (comp)

	EXPECT_EQ( minmax(v1, v2, v3, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v1, v2, v4, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v1, v3, v2, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v1, v3, v4, v2, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v1, v4, v2, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v1, v4, v3, v2, comp), mk_cpair(v4, v1) );

	EXPECT_EQ( minmax(v2, v1, v3, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v2, v1, v4, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v2, v3, v1, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v2, v3, v4, v1, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v2, v4, v1, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v2, v4, v3, v1, comp), mk_cpair(v4, v1) );

	EXPECT_EQ( minmax(v3, v2, v1, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v3, v2, v4, v1, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v3, v1, v2, v4, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v3, v1, v4, v2, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v3, v4, v1, v2, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v3, v4, v2, v1, comp), mk_cpair(v4, v1) );

	EXPECT_EQ( minmax(v4, v1, v2, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v4, v1, v3, v2, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v4, v2, v1, v3, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v4, v2, v3, v1, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v4, v3, v1, v2, comp), mk_cpair(v4, v1) );
	EXPECT_EQ( minmax(v4, v3, v2, v1, comp), mk_cpair(v4, v1) );

	EXPECT_EQ( minmax(p1, p2, p3, p4, comp), mk_cpair(p1, p4) );

}


TEST( BasicAlgs, ZipAndExtract )
{
	const int N = 5;
	int a1[N] = {2, 3, 4, 5, 6};
	int a2[N] = {8, 7, 6, 5, 4};

	pair<int, int> pairs[N];
	pair<int, int> pairs_ref[N] = {
			make_pair(2, 8),
			make_pair(3, 7),
			make_pair(4, 6),
			make_pair(5, 5),
			make_pair(6, 4)
	};

	zip_copy(a1, a1 + N, a2, pairs);

	EXPECT_TRUE( collection_equal(pairs, pairs+N, pairs_ref, N) );

	int b1[N] = {0, 0, 0, 0, 0};
	int b2[N] = {0, 0, 0, 0, 0};

	dispatch_copy(pairs, pairs+N, b1, b2);

	EXPECT_TRUE( collection_equal(b1, b1+N, a1, N) );
	EXPECT_TRUE( collection_equal(b2, b2+N, b2, N) );
}


TEST( BasicAlgs, SimpleSort )
{
	int x = 0, y = 0, z = 0, w = 0;

	// two
	x = 1; y = 2;
	simple_sort(x, y);
	EXPECT_TRUE( x == 1 && y == 2 );

	x = 2; y = 1;
	simple_sort(x, y);
	EXPECT_TRUE( x == 1 && y == 2 );

	// three
	x = 1; y = 2; z = 3;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	x = 1; y = 3; z = 2;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	x = 2; y = 1; z = 3;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	x = 2; y = 3; z = 1;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	x = 3; y = 1; z = 2;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	x = 3; y = 2; z = 1;
	simple_sort(x, y, z);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 );

	// four

	x = 1; y = 2; z = 3; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 1; y = 2; z = 4; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 1; y = 3; z = 2; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 1; y = 3; z = 4; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 1; y = 4; z = 2; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 1; y = 4; z = 3; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 1; z = 3; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 1; z = 4; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 3; z = 1; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 3; z = 4; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 4; z = 1; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 2; y = 4; z = 3; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 1; z = 2; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 1; z = 4; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 2; z = 1; w = 4;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 2; z = 4; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 4; z = 1; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 3; y = 4; z = 2; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 1; z = 2; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 1; z = 3; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 2; z = 1; w = 3;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 2; z = 3; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 3; z = 1; w = 2;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);

	x = 4; y = 3; z = 2; w = 1;
	simple_sort(x, y, z, w);
	EXPECT_TRUE( x == 1 && y == 2 && z == 3 && w == 4);
}


TEST( BasicAlgs, TupleSort )
{
	const int N = 5;
	pair<int, int> pairs[N] = {
			make_pair(8, 5),
			make_pair(7, 9),
			make_pair(3, 4),
			make_pair(9, 6),
			make_pair(1, 3)
	};

	pair<int, int> pairs_a0[N] = {
			make_pair(1, 3),
			make_pair(3, 4),
			make_pair(7, 9),
			make_pair(8, 5),
			make_pair(9, 6)
	};

	pair<int, int> pairs_d0[N] = {
			make_pair(9, 6),
			make_pair(8, 5),
			make_pair(7, 9),
			make_pair(3, 4),
			make_pair(1, 3)
	};

	pair<int, int> rpairs[N];

	bcs::copy_n(pairs, N, rpairs);
	sort_pairs_by_key(rpairs, rpairs+N);
	EXPECT_TRUE( collection_equal(rpairs, rpairs+N, pairs_a0, N) );

	bcs::copy_n(pairs, N, rpairs);
	sort_pairs_by_key(rpairs, rpairs+N, std::greater<int>());
	EXPECT_TRUE( collection_equal(rpairs, rpairs+N, pairs_d0, N) );

}


struct my_inplace_plus
{
	void operator() (int& s, int& a)
	{
		s += a;
	}
};


TEST( BasicAlgs, Cumulation )
{
	int a[5] = {1, 2, 3, 4, 5};

	int s = 10;
	cumulate(s, a, a+5, my_inplace_plus());
	EXPECT_EQ(s, 25);

	cumulate_n(s, a, 3, my_inplace_plus());
	EXPECT_EQ(s, 31);
}

