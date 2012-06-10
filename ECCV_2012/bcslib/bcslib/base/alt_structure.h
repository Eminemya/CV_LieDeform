/*
 * @file alt_structure.h
 *
 * Support of alterative structure
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_ALT_STRUCTURE_H_
#define BCSLIB_ALT_STRUCTURE_H_

namespace bcs
{

	template<typename T>
	class alt_structure
	{
	public:
		typedef T value_type;

		alt_structure(T& v) : _ptr(&v)
		{
		}

		bool has_value() const
		{
			return bool(_ptr);
		}



	private:
		T *_ptr;


	}; // end class alt_structure


}

#endif
