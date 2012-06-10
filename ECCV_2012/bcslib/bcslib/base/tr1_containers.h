/**
 * @file tr1_containers.h
 *
 * Import of useful container types in TR1/C++11
 *
 * 	- array
 * 	- tuple
 * 	- hash maps and sets
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_TR1_CONTAINERS_H_
#define BCSLIB_TR1_CONTAINERS_H_

#include <bcslib/base/config.h>

#ifdef BCS_USE_C11_STDLIB
#include <tuple>
#include <array>
#include <unordered_map>
#include <unordered_set>
#else
#include <tr1/tuple>
#include <tr1/array>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#endif

namespace bcs
{
	// tuple & array

	using BCS_TR1::tuple;
	using BCS_TR1::array;

	// hash container

	using BCS_TR1::unordered_map;
	using BCS_TR1::unordered_multimap;
	using BCS_TR1::unordered_set;
	using BCS_TR1::unordered_multiset;

	using BCS_TR1::hash;
}


#endif

