/**
 * @file test_array1d.cpp
 *
 * The Unit Testing for array1d
 * 
 * @author Dahua Lin
 */


#include "bcs_test_basics.h"
#include <bcslib/array/array1d.h>
#include <bcslib/array/amap.h>

using namespace bcs;
using namespace bcs::test;

// Explicit instantiation for syntax checking

template class bcs::caview1d_ex<double, id_ind>;
template class bcs::caview1d_ex<double, step_ind>;
template class bcs::caview1d_ex<double, rep_ind>;

template class bcs::aview1d_ex<double, id_ind>;
template class bcs::aview1d_ex<double, step_ind>;
template class bcs::aview1d_ex<double, rep_ind>;

template class bcs::caview1d<double>;
template class bcs::aview1d<double>;
template class bcs::array1d<double>;

struct SimpleKey
{
	index_t i;
	index_t index() const { return i; }
};

namespace bcs
{
	template<>
	struct index_convertible<SimpleKey>
	{
		static const bool value = true;
	};
}

template class bcs::caview_map<SimpleKey, double>;
template class bcs::aview_map<SimpleKey, double>;
template class bcs::array_map<SimpleKey, double>;


/************************************************
 *
 *  Inheritance testing
 *
 ************************************************/

// caview1d_ex

#ifdef BCS_USE_STATIC_ASSERT

static_assert( (is_base_of<
		bcs::IConstAView1DBase<bcs::caview1d_ex<double, id_ind>, double>,
		bcs::caview1d_ex<double, id_ind> >::value),
		"caview1d_ex base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IConstRegularAView1D<bcs::caview1d_ex<double, id_ind>, double>,
		bcs::caview1d_ex<double, id_ind> >::value),
		"caview1d_ex base-class assertion failure" );


// aview1d_ex

static_assert( (is_base_of<
		bcs::caview1d_ex<double, id_ind>,
		bcs::aview1d_ex<double, id_ind> >::value),
		"aview1d_ex base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IAView1DBase<bcs::aview1d_ex<double, id_ind>, double>,
		bcs::aview1d_ex<double, id_ind> >::value),
		"aview1d_ex base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IRegularAView1D<bcs::aview1d_ex<double, id_ind>, double>,
		bcs::aview1d_ex<double, id_ind> >::value),
		"aview1d_ex base-class assertion failure" );

// caview1d

static_assert( (is_base_of<
		bcs::IConstAView1DBase<bcs::caview1d<double>, double>,
		bcs::caview1d<double> >::value),
		"caview1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IConstRegularAView1D<bcs::caview1d<double>, double>,
		bcs::caview1d<double> >::value),
		"caview1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IConstContinuousAView1D<bcs::caview1d<double>, double>,
		bcs::caview1d<double> >::value),
		"cview1d base-class assertion failure" );


// aview1d

static_assert( (is_base_of<
		bcs::caview1d<double>,
		bcs::aview1d<double> >::value),
		"aview1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IAView1DBase<bcs::aview1d<double>, double>,
		bcs::aview1d<double> >::value),
		"aview1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IRegularAView1D<bcs::aview1d<double>, double>,
		bcs::aview1d<double> >::value),
		"aview1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IContinuousAView1D<bcs::aview1d<double>, double>,
		bcs::aview1d<double> >::value),
		"aview1d base-class assertion failure" );


// array1d

static_assert( (is_base_of<
		bcs::IConstAView1DBase<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IConstRegularAView1D<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IConstContinuousAView1D<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IAView1DBase<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IRegularAView1D<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure" );

static_assert( (is_base_of<
		bcs::IContinuousAView1D<bcs::array1d<double>, double>,
		bcs::array1d<double> >::value),
		"array1d base-class assertion failure");

#endif


/************************************************
 *
 *  Auxiliary functions
 *
 ************************************************/

template<class Derived, typename T>
bool array_integrity_test(const bcs::IConstRegularAView1D<Derived, T>& a)
{
	index_t n = a.dim0();

	if (a.ndims() != 1) return false;
	if (a.nelems() != n) return false;
	if (a.size() != (size_t)n) return false;
	if (a.shape() != arr_shape(n)) return false;
	if (a.is_empty() != (a.nelems() == 0)) return false;

	return true;
}

template<class Derived, typename T>
bool cont_array_integrity_test(const bcs::IConstContinuousAView1D<Derived, T>& a)
{
	if (!array_integrity_test(a)) return false;

	index_t n = a.dim0();
	if (!a.is_empty())
	{
		if (a.pbase() != &(a[0])) return false;
	}

	for (index_t i = 0; i < n; ++i)
	{
		if (&(a(i)) != &(a[i])) return false;
		if (a(i) != a[i]) return false;
	}

	return true;
}

template<class Derived, typename T>
bool elemwise_operation_test(bcs::IRegularAView1D<Derived, T>& a)
{
	index_t n = a.nelems();
	block<T> blk(a.size());
	const T *b = blk.pbase();

	Derived& ad = a.derived();

	// export
	export_to(ad, blk.pbase());

	for (index_t i = 0; i < n; ++i)
	{
		if (b[i] != a(i)) return false;
	}

	// fill
	T v = T(123);
	fill(ad, v);

	for (index_t i = 0; i < n; ++i)
	{
		if (a(i) != v) return false;
	}

	// import
	import_from(ad, blk.pbase());

	for (index_t i = 0; i < n; ++i)
	{
		if (a(i) != b[i]) return false;
	}

	return true;
}


/************************************************
 *
 *  Test cases
 *
 ************************************************/

TEST( Array1D, Aview1D )
{
	double src1[5] = {3, 4, 5, 1, 2};
	index_t n1 = 5;

	aview1d<double> a1(src1, n1);

	ASSERT_EQ(a1.dim0(), n1);
	ASSERT_TRUE( cont_array_integrity_test(a1) );
	ASSERT_TRUE( array_equal(a1, src1, n1) );
	ASSERT_TRUE( elemwise_operation_test(a1) );

	aview1d<double> a2(a1);

	ASSERT_EQ(a2.dim0(), n1);
	ASSERT_TRUE( cont_array_integrity_test(a2) );
	ASSERT_TRUE( array_equal(a2, src1, n1) );

	ASSERT_EQ( a1.pbase(), a2.pbase() );
	ASSERT_TRUE( cont_array_integrity_test(a2) );
	ASSERT_TRUE( array_equal(a2, src1, n1) );
	ASSERT_TRUE( elemwise_operation_test(a2) );
}

TEST( Array1D, Array1D )
{
	double src1[5] = {3, 4, 5, 1, 2};
	index_t n1 = 5;

	double v2 = 7;
	double src2[6] = {7, 7, 7, 7, 7, 7};
	index_t n2 = 6;

	array1d<double> a0(0);

	ASSERT_EQ(a0.dim0(), 0);
	ASSERT_TRUE( a0.is_unique() );
	ASSERT_TRUE( cont_array_integrity_test(a0) );

	array1d<double> a1(n1);

	for (int i = 0; i < n1; ++i) a1(i) = src1[i];

	ASSERT_EQ(a1.dim0(), n1);
	ASSERT_TRUE( a1.is_unique() );
	ASSERT_TRUE( cont_array_integrity_test(a1) );
	ASSERT_TRUE( array_equal(a1, src1, n1) );

	array1d<double> a2(n2, v2);

	ASSERT_EQ(a2.dim0(), n2);
	ASSERT_TRUE( a2.is_unique() );
	ASSERT_TRUE( cont_array_integrity_test(a2) );
	ASSERT_TRUE( array_equal(a2, src2, n2) );
	ASSERT_TRUE( elemwise_operation_test(a2) );

	array1d<double> a3(n1, src1);

	ASSERT_EQ(a3.dim0(), n1);
	ASSERT_TRUE( a3.is_unique() );
	ASSERT_TRUE( cont_array_integrity_test(a3) );
	ASSERT_TRUE( array_equal(a3, src1, n1) );
	ASSERT_TRUE( elemwise_operation_test(a3) );

	array1d<double> a4(a3);

	ASSERT_EQ(a4.dim0(), n1);
	ASSERT_FALSE( a3.is_unique() );
	ASSERT_FALSE( a4.is_unique() );
	ASSERT_EQ( a4.pbase(), a3.pbase() );

	ASSERT_TRUE( cont_array_integrity_test(a3) );
	ASSERT_TRUE( array_equal(a3, src1, n1) );

	ASSERT_TRUE( cont_array_integrity_test(a4) );
	ASSERT_TRUE( array_equal(a4, src1, n1) );
	ASSERT_TRUE( elemwise_operation_test(a4) );

	a4.make_unique();

	ASSERT_NE( a4.pbase(), a3.pbase() );
	ASSERT_TRUE( a3.is_unique() );
	ASSERT_TRUE( a4.is_unique() );

	ASSERT_EQ(a3.dim0(), n1);
	ASSERT_EQ(a4.dim0(), n1);

	ASSERT_TRUE( cont_array_integrity_test(a3) );
	ASSERT_TRUE( array_equal(a3, src1, n1) );

	ASSERT_TRUE( cont_array_integrity_test(a4) );
	ASSERT_TRUE( array_equal(a4, src1, n1) );

	array1d<double> a5 = a1.deep_copy();

	ASSERT_NE( a1.pbase(), a5.pbase() );
	ASSERT_TRUE( a1.is_unique() );
	ASSERT_TRUE( a5.is_unique() );

	ASSERT_EQ(a1.dim0(), n1);
	ASSERT_EQ(a5.dim0(), n1);

	ASSERT_TRUE( cont_array_integrity_test(a1) );
	ASSERT_TRUE( array_equal(a1, src1, n1) );

	ASSERT_TRUE( cont_array_integrity_test(a5) );
	ASSERT_TRUE( array_equal(a5, src1, n1) );
	ASSERT_TRUE( elemwise_operation_test(a5) );
}


TEST( Array1D, Array1DClone )
{
	double src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	aview1d<double> view1(src, 5);
	array1d<double> a1 = clone_array(view1);

	ASSERT_TRUE( array_integrity_test(a1) );
	ASSERT_NE( a1.pbase(), view1.pbase() );
	ASSERT_TRUE( array_equal(a1, src, 5) );
	ASSERT_TRUE( elemwise_operation_test(a1) );

	aview1d_ex<double, step_ind> view2(src, step_ind(3, 2));
	array1d<double> a2 = clone_array(view2);

	ASSERT_TRUE( array_integrity_test(a2) );
	double r2[3] = {1, 3, 5};
	ASSERT_TRUE( array_equal(a2, r2, 3) );
	ASSERT_TRUE( elemwise_operation_test(a2) );
}



TEST( Array1D, Aview1DEx_IdInd )
{
	double src1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	aview1d_ex<double, id_ind> a0(src1, id_ind(0));

	ASSERT_TRUE( a0.nelems() == 0 );
	ASSERT_TRUE( array_integrity_test(a0) );

	aview1d_ex<double, id_ind> a1(src1, id_ind(3));
	double r1[] = {1, 2, 3};
	index_t n1 = 3;

	ASSERT_EQ( a1.dim0(), n1 );
	ASSERT_TRUE( array_integrity_test(a1) );
	ASSERT_TRUE( array1d_equal(a1, make_caview1d(r1, n1)) );
	ASSERT_TRUE( elemwise_operation_test(a1) );
}



TEST( Array1D, Aview1DEx_StepInd )
{
	double src1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	aview1d_ex<double, step_ind> a0(src1, step_ind(0, 2));

	ASSERT_TRUE( a0.nelems() == 0 );
	ASSERT_TRUE( array_integrity_test(a0) );

	aview1d_ex<double, step_ind> a1(src1, step_ind(3, 1));
	double r1[] = {1, 2, 3};
	index_t n1 = 3;

	ASSERT_EQ( a1.dim0(), n1 );
	ASSERT_TRUE( array_integrity_test(a1) );
	ASSERT_TRUE( array1d_equal(a1, make_caview1d(r1, n1)) );
	ASSERT_TRUE( elemwise_operation_test(a1) );

	aview1d_ex<double, step_ind> a2(src1, step_ind(4, 2));
	double r2[] = {1, 3, 5, 7};
	index_t n2 = 4;

	ASSERT_EQ( a2.dim0(), n2 );
	ASSERT_TRUE( array_integrity_test(a2) );
	ASSERT_TRUE( array1d_equal(a2, make_caview1d(r2, n2)) );
	ASSERT_TRUE( elemwise_operation_test(a2) );

	aview1d_ex<double, step_ind> a3(src1 + 7, step_ind(3, -2));
	double r3[] = {8, 6, 4};
	index_t n3 = 3;

	ASSERT_EQ( a3.dim0(), n3 );
	ASSERT_TRUE( array_integrity_test(a3) );
	ASSERT_TRUE( array1d_equal(a3, make_caview1d(r3, n3)) );
	ASSERT_TRUE( elemwise_operation_test(a3) );
}


TEST( Array1D, Aview1DEx_RepInd )
{
	double v = 2;

	aview1d_ex<double, rep_ind> a0(&v, rep_ind(0));

	ASSERT_TRUE( a0.nelems() == 0 );
	ASSERT_TRUE( array_integrity_test(a0) );

	aview1d_ex<double, rep_ind> a1(&v, rep_ind(5));
	double r1[5] = {2, 2, 2, 2, 2};
	index_t n1 = 5;

	ASSERT_TRUE( array_integrity_test(a1) );
	ASSERT_TRUE( array1d_equal(a1, make_caview1d(r1, n1)) );
	ASSERT_TRUE( elemwise_operation_test(a1) );

}


TEST( Array1D, SubView )
{
	double src[16];
	for (int i = 0; i < 16; ++i) src[i] = i;  // 0, 1, 2, ..., 15

	aview1d<double> a1(src, 8);

	double r1a[] = {0, 1, 2, 3, 4, 5, 6, 7};
	EXPECT_TRUE( array1d_equal(a1.V(whole()), make_aview1d(r1a, 8)) );

	double r1b[] = {1, 2, 3, 4, 5};
	EXPECT_TRUE( array1d_equal(a1.V(rgn(1, 6)), make_aview1d(r1b, 5)) );

	double r1c[] = {1, 3, 5};
	EXPECT_TRUE( array1d_equal(a1.V(rgn(1, 7, 2)), make_aview1d(r1c, 3)) );

	double r1d[] = {2, 3, 4, 5, 6};
	EXPECT_TRUE( array1d_equal(a1.V(rgn(2, a1.dim0() - 1)), make_aview1d(r1d, 5)) );

	double r1e[] = {1, 3, 5, 7};
	EXPECT_TRUE( array1d_equal(a1.V(rgn(1, a1.dim0(), 2)), make_aview1d(r1e, 4)) );

	double r1f[] = {7, 6, 5, 4, 3, 2, 1, 0};
	EXPECT_TRUE( array1d_equal(a1.V(rev_whole()),  make_aview1d(r1f, 8)) );

	double r1r[] = {2, 2, 2, 2, 2};
	EXPECT_TRUE( array1d_equal(a1.V(rep(2, 5)), make_aview1d(r1r, 5)) );

}


TEST( Array1D, ViewCopy )
{
	const index_t N = 5;

	double a0_buf[N] = {2, 4, 5, 7, 8};
	double a1_buf[N] = {0, 0, 0, 0, 0};
	double e2_buf[2 * N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double e3_buf[2 * N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double a4_buf[N] = {0, 0, 0, 0, 0};

	aview1d<double> a0(a0_buf, N);
	aview1d<double> a1(a1_buf, N);
	aview1d_ex<double, step_ind> e2(e2_buf, step_ind(N, 2));
	aview1d_ex<double, step_ind> e3(e3_buf, step_ind(N, 2));
	aview1d<double> a4(a4_buf, N);

	copy(a0, a1);
	ASSERT_TRUE( array1d_equal(a1, make_aview1d(a0_buf, N)) );

	copy(a1, e2);
	ASSERT_TRUE( array1d_equal(e2, make_aview1d(a0_buf, N)) );

	copy(e2, e3);
	ASSERT_TRUE( array1d_equal(e3, make_aview1d(a0_buf, N)) );

	copy(e3, a4);
	ASSERT_TRUE( array1d_equal(a4, make_aview1d(a0_buf, N)) );
}


TEST( Array1D, SubArraySelection )
{
	const index_t N = 10;
	double src[N] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	bool msk[N] = {false, false, true, false, true, false, false, true, false, true};
	const index_t n = 4;

	caview1d<double> a0(src, N);
	caview1d<bool> b0(msk, N);

	index_t I0r[n] = {2, 4, 7, 9};
	array1d<index_t> I0 = find(b0);

	ASSERT_EQ( I0.dim0(), n );
	ASSERT_TRUE( array_equal(I0, I0r, n) );

	double sr[n] = {30, 50, 80, 100};
	array1d<double> s = select_elems(a0, I0);
	ASSERT_EQ( s.dim0(), n );
	ASSERT_TRUE( array_equal(s, sr, n) );

	array1d<double> sf = select_elems(a0, find(b0));
	ASSERT_EQ( sf.dim0(), n );
	ASSERT_TRUE( array_equal(sf, sr, n));

	bool msk1[] = {false, false, false, false, false, false, false, false, false, false};
	caview1d<bool> b1(msk1, N);

	array1d<index_t> I1 = find(b1);
	array1d<double> s1 = select_elems(a0, I1);

	ASSERT_EQ( I1.nelems(), 0 );
	ASSERT_EQ( s1.nelems(), 0 );
}




