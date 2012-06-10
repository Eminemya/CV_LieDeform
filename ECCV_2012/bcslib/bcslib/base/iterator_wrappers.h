/**
 * @file iterator_wrappers.h
 *
 * Some useful wrapper classes for extending the functionality of iterators
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_ITERATOR_WRAPPERS_H
#define BCSLIB_ITERATOR_WRAPPERS_H

#include <bcslib/base/basic_defs.h>
#include <iterator>


namespace bcs
{
	// Basic wrappers

	/**
	 * The Concept of forward_iterator_implementer
	 * -----------
	 *
	 * typedef of value_type;
	 * typedef of reference;
	 * typedef of pointer;
	 *
	 * - void move_next();
	 * - pointer ptr() const;
	 * - reference ref() const;
	 * - operator ==
	 *
	 * The Concept of bidirectional_iterator_implementer
	 * refines forward_iterator_implementer
	 * -----------
	 *
	 * - void move_prev();
	 *
	 * The Concept of random_access_iterator_implementer
	 * refines bidirectional_iterator_implementer
	 * -----------
	 *
	 * - void move_forward(int n);
	 * - void move_backward(int n);
	 * - ptrdiff_t  *this - rhs;
	 *
	 * - operator <
	 * - operator >
	 *
	 * - reference element_at(int n) const;
	 *
	 */

	template<class Impl>
	class forward_iterator_wrapper
	{
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef typename Impl::value_type value_type;
		typedef typename Impl::pointer pointer;
		typedef typename Impl::reference reference;
		typedef ptrdiff_t difference_type;

	public:
		forward_iterator_wrapper()
		{
		}

		forward_iterator_wrapper(const Impl& impl) : m_impl(impl)
		{
		}

		bool operator == (const forward_iterator_wrapper& rhs) const
		{
			return m_impl == rhs.m_impl;
		}

		bool operator != (const forward_iterator_wrapper& rhs) const
		{
			return !(m_impl == rhs.m_impl);
		}

		reference operator * () const
		{
			return m_impl.ref();
		}

		pointer operator -> () const
		{
			return m_impl.ptr();
		}

		forward_iterator_wrapper& operator ++ ()
		{
			m_impl.move_next();
			return *this;
		}

		forward_iterator_wrapper operator ++ (int)
		{
			Impl cimpl = m_impl;
			m_impl.move_next();
			return cimpl;
		}

	protected:
		Impl m_impl;

	}; // end class forward_iterator_wrapper



	template<class Impl>
	class bidirectional_iterator_wrapper : public forward_iterator_wrapper<Impl>
	{
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename Impl::value_type value_type;
		typedef typename Impl::pointer pointer;
		typedef typename Impl::reference reference;
		typedef ptrdiff_t difference_type;

	public:
		bidirectional_iterator_wrapper()
		{
		}

		bidirectional_iterator_wrapper(const Impl& impl) : forward_iterator_wrapper<Impl>(impl)
		{
		}

		bidirectional_iterator_wrapper& operator -- ()
		{
			this->m_impl.move_prev();
			return *this;
		}

		bidirectional_iterator_wrapper operator -- (int)
		{
			Impl cimpl = this->m_impl;
			this->m_impl.move_prev();
			return cimpl;
		}

	}; // end class bidirectional_iterator_wrapper



	template<class Impl>
	class random_access_iterator_wrapper : public bidirectional_iterator_wrapper<Impl>
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename Impl::value_type value_type;
		typedef typename Impl::pointer pointer;
		typedef typename Impl::reference reference;
		typedef ptrdiff_t difference_type;

	public:
		random_access_iterator_wrapper()
		{
		}

		random_access_iterator_wrapper(const Impl& impl) : bidirectional_iterator_wrapper<Impl>(impl)
		{
		}

		bool operator < (const random_access_iterator_wrapper& rhs) const
		{
			return this->m_impl < rhs.m_impl;
		}

		bool operator <= (const random_access_iterator_wrapper& rhs) const
		{
			return !(this->m_impl > rhs.m_impl);
		}

		bool operator > (const random_access_iterator_wrapper& rhs) const
		{
			return this->impl > rhs.m_impl;
		}

		bool operator >= (const random_access_iterator_wrapper& rhs) const
		{
			return !(this->m_impl < rhs.m_impl);
		}

		random_access_iterator_wrapper operator + (difference_type n) const
		{
			Impl impl(this->m_impl);
			impl.move_forward(n);
			return impl;
		}

		random_access_iterator_wrapper operator - (difference_type n) const
		{
			Impl impl(this->m_impl);
			impl.move_backward(n);
			return impl;
		}

		difference_type operator - (const random_access_iterator_wrapper& rhs) const
		{
			return this->m_impl - rhs.m_impl;
		}

		random_access_iterator_wrapper& operator += (difference_type n)
		{
			this->m_impl.move_forward(n);
			return *this;
		}

		random_access_iterator_wrapper& operator -= (difference_type n)
		{
			this->m_impl.move_backward(n);
			return *this;
		}

		reference operator[] (difference_type n) const
		{
			return this->m_impl.element_at(n);
		}

	}; // end class random_access_iterator_wrapper

	template<class Impl>
	inline random_access_iterator_wrapper<Impl> operator + (
			typename random_access_iterator_wrapper<Impl>::difference_type n,
			const random_access_iterator_wrapper<Impl>& rhs)
	{
		return rhs + n;
	}


}

#endif 
