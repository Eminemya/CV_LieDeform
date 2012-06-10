/**
 * @file cmath.h
 *
 * Proper inclusion of math functions.
 * 
 * Purposes:
 * 	1. MSVC lacks a great number of std C math functions, need to workarond it.
 * 	2. Make it easier to switch to more efficient math libs in future.
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#include <bcslib/base/basic_defs.h>
#include <cmath>

#ifndef BCSLIB_CMATH_H_
#define BCSLIB_CMATH_H_

namespace bcs
{
	namespace math
	{
		// inclusion C++03 standard ones

		using std::abs;
		using std::sqrt;
		using std::pow;

		using std::exp;
		using std::log;
		using std::log10;
		using std::frexp;
		using std::ldexp;

		using std::floor;
		using std::ceil;
		using std::fmod;

		using std::sin;
		using std::cos;
		using std::tan;
		using std::asin;
		using std::acos;
		using std::atan;
		using std::atan2;

		using std::sinh;
		using std::cosh;
		using std::tanh;

		// BCSLib's extras (for convenience)

		template<typename T>
		inline BCS_ENSURE_INLINE T sqr(T x)
		{
			return x * x;
		}

		template<typename T>
		inline BCS_ENSURE_INLINE T cube(T x)
		{
			return x * x * x;
		}

		template<typename T>
		inline BCS_ENSURE_INLINE T rcp(T x)
		{
			return T(1) / x;
		}

		template<typename T>
		inline BCS_ENSURE_INLINE T rsqrt(T x)
		{
			return T(1) / sqrt(x);
		}

		template<typename T>
		inline BCS_ENSURE_INLINE T clamp(T x, T lb, T ub)
		{
			return x < lb ? lb : (x > ub ? ub : x);
		}

		// Part of the new stuff in C++0x (Unfortunately, many are not available for MSVC yet)

#if BCS_PLATFORM_INTERFACE==BCS_POSIX_INTERFACE

		using ::cbrt;
		using ::copysign;
		using ::hypot;

		using ::exp2;
		using ::log2;
		using ::expm1;
		using ::log1p;

		using ::round;
		using ::trunc;

		using ::asinh;
		using ::acosh;
		using ::atanh;

		using ::erf;
		using ::erfc;
		using ::lgamma;
		using ::tgamma;

		using ::isinf;
		using ::isnan;

		// TODO: implement C99 math for MSVC
#endif


	}
}

#endif
