/**
 * @file arg_check.h
 *
 * Facilities for argument checking
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_ARG_CHECK_H_
#define BCSLIB_ARG_CHECK_H_

#include <bcslib/base/basic_defs.h>
#include <exception>

namespace bcs
{

	class invalid_argument : public std::exception
	{
	public:
		invalid_argument(const char *msg)
		: m_msg(msg)
		{
		}

		virtual const char* what() const throw()
		{
			return m_msg;
		}

	private:
		const char *m_msg;
	};


	// generic argument checking

	inline void check_arg(bool cond)
	{
		if (!cond)
		{
			throw invalid_argument("Invalid argument");
		}
	}

	inline void check_arg(bool cond, const char* message)
	{
		if (!cond)
		{
			throw invalid_argument(message);
		}
	}

}


#endif 
