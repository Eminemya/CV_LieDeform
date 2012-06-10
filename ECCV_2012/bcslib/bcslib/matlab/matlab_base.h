/**
 * @file matlab_base.h
 *
 * The basic definitions for matlab port
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_MATLAB_BASE_H
#define BCSLIB_MATLAB_BASE_H

#include <mex.h>

#include <bcslib/base/basic_defs.h>
#include <string>

namespace bcs { namespace matlab {

	// exception class

	class mexception
	{
	public:
		mexception(const char *id, const char *msg) : m_identifier(id), m_message(msg)
		{
		}

		const char *identifier() const
		{
			return m_identifier.c_str();
		}

		const char *message() const
		{
			return m_message.c_str();
		}

	private:
		std::string m_identifier;
		std::string m_message;
	};


	// type specific stuff

	template<typename T> struct mtype_traits;

	template<>
	struct mtype_traits<double>
	{
		static const bool is_float = true;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxDOUBLE_CLASS;
	};

	template<>
	struct mtype_traits<float>
	{
		static const bool is_float = true;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxSINGLE_CLASS;
	};

	template<>
	struct mtype_traits<int32_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxINT32_CLASS;
	};

	template<>
	struct mtype_traits<uint32_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxUINT32_CLASS;
	};

	template<>
	struct mtype_traits<int16_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxINT16_CLASS;
	};

	template<>
	struct mtype_traits<uint16_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxUINT16_CLASS;
	};

	template<>
	struct mtype_traits<int8_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxINT8_CLASS;
	};

	template<>
	struct mtype_traits<uint8_t>
	{
		static const bool is_float = false;
		static const bool is_numeric = true;
		static const mxClassID class_id = mxUINT8_CLASS;
	};

	template<>
	struct mtype_traits<bool>
	{
		static const bool is_float = false;
		static const bool is_numeric = false;
		static const mxClassID class_id = mxLOGICAL_CLASS;
	};


} }

#endif 
