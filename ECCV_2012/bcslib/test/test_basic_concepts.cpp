/*
 * @file test_basic_concepts.cpp
 *
 * Syntax checking of some basic concepts
 *
 * @author Dahua Lin
 */


#include <bcslib/base/key_map.h>
#include <bcslib/base/type_traits.h>

#include <vector>
#include <map>

using namespace bcs;

static_assert(is_key_map<std::vector<double> >::value, "vector must be a key_map.");
// static_assert(is_key_map<std::map<char, double> >::value, "vector must be a key_map.");

