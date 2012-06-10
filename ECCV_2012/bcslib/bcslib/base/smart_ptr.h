/*
 * @file smart_ptr.h
 *
 * Useful smart pointers from TR1/C++0x and
 * a scoped_ptr class and an alt_var class
 *
 * @author Dahua Lin
 */

#ifndef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_SMART_PTR_H_
#define BCSLIB_SMART_PTR_H_

#include <bcslib/base/basic_defs.h>

#ifdef BCS_USE_C11_STDLIB
#include <memory>
#else
#include <tr1/memory>
#endif

namespace bcs
{
	using BCS_TR1::shared_ptr;
	using BCS_TR1::weak_ptr;


	template<class T>
	class scoped_ptr: noncopyable
	{
	public:
		typedef T element_type;

		explicit scoped_ptr(T *p = 0): _ptr(p) { }

		~scoped_ptr()
		{
			if (_ptr) delete _ptr;
		}

		void reset(T *p = 0)
		{
			if (_ptr) delete _ptr;
			_ptr = p;
		}

		T& operator*() const
		{
			return *_ptr;
		}

		T * operator->() const
		{
			return *_ptr;
		}

		T * get() const
		{
			return _ptr;
		}

		operator bool() const
		{
			return bool(_ptr);
		}

		void swap(scoped_ptr & b)
		{
			T *t = b._ptr;
			b._ptr = _ptr;
			_ptr = t;
		}

	private:
		T *_ptr;
	};

	template<class T>
	inline void swap(scoped_ptr<T> & a, scoped_ptr<T> & b)
	{
		a.swap(b);
	}


	template<class T>
	class alt_cvar
	{
	public:
		typedef T element_type;

	public:
		explicit alt_cvar() : _ptr(0)
		{
		}

		alt_cvar(const T *p, bool takeover)
		: _ptr(p), _sp(takeover ? const_cast<T*>(p) : (T*)(0))
		{
		}

		const T& value() const
		{
			return *_ptr;
		}

		operator bool() const
		{
			return bool(_ptr);
		}

	private:
		T *_ptr;
		shared_ptr<T> _sp;
	};


	template<class T>
	class alt_var
	{
	public:
		typedef T element_type;

	public:
		explicit alt_var() : _ptr(0)
		{
		}

		alt_var(T *p, bool takeover)
		: _ptr(p), _sp(takeover ? p : (T*)(0))
		{
		}

		const T& value() const
		{
			return *_ptr;
		}

		operator bool() const
		{
			return bool(_ptr);
		}

	private:
		T *_ptr;
		shared_ptr<T> _sp;
	};

}

#endif /* SMART_PTR_H_ */
