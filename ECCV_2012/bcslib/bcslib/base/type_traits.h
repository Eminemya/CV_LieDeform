/*
 * @file type_traits.h
 *
 * Import of useful type traits
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_TYPE_TRAITS_H_
#define BCSLIB_TYPE_TRAITS_H_

#include <bcslib/base/basic_defs.h>

#ifdef BCS_USE_C11_STDLIB
#include <type_traits>
#else
#include <tr1/type_traits>
#endif

namespace bcs
{
	using BCS_TR1::is_void;
	using BCS_TR1::is_integral;
	using BCS_TR1::is_floating_point;
	using BCS_TR1::is_array;
	using BCS_TR1::is_pointer;
	using BCS_TR1::is_reference;
	using BCS_TR1::is_member_function_pointer;
	using BCS_TR1::is_member_object_pointer;
	using BCS_TR1::is_enum;
	using BCS_TR1::is_union;
	using BCS_TR1::is_class;
	using BCS_TR1::is_function;

	using BCS_TR1::is_arithmetic;
	using BCS_TR1::is_fundamental;
	using BCS_TR1::is_object;
	using BCS_TR1::is_scalar;
	using BCS_TR1::is_compound;
	using BCS_TR1::is_member_pointer;

	using BCS_TR1::is_signed;
	using BCS_TR1::is_unsigned;

	using BCS_TR1::is_const;
	using BCS_TR1::is_volatile;
	using BCS_TR1::is_pod;
	using BCS_TR1::is_empty;
	using BCS_TR1::is_polymorphic;
	using BCS_TR1::is_abstract;

	using BCS_TR1::is_same;
	using BCS_TR1::is_base_of;

	using BCS_TR1::remove_const;
	using BCS_TR1::remove_volatile;
	using BCS_TR1::remove_cv;
	using BCS_TR1::remove_pointer;
	using BCS_TR1::remove_reference;

	using BCS_TR1::add_const;
	using BCS_TR1::add_volatile;
	using BCS_TR1::add_cv;

	using BCS_TR1::alignment_of;
}

#endif /* TYPE_TRAITS_H_ */
