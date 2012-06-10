/**
 * @file basic_mem_alloc.h
 *
 * Basic facilities for memory allocation
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_BASIC_MEM_ALLOC_H_
#define BCSLIB_BASIC_MEM_ALLOC_H_

#include <bcslib/base/basic_defs.h>

// for platform-dependent aligned allocation
#include <stdlib.h>
#if BCS_PLATFORM_INTERFACE == BCS_WINDOWS_INTERFACE
#include <malloc.h>
#endif

#include <limits> // for allocator's max_size method
#include <new> // for std::bad_alloc

#ifndef BCS_DEFAULT_ALIGNMENT
#define BCS_DEFAULT_ALIGNMENT 32
#endif

namespace bcs
{
	/********************************************
	 *
	 *	aligned array on stack
	 *
	 ********************************************/

	template<typename T, size_t N>
	struct aligned_array
	{
		BCS_ALIGN(BCS_DEFAULT_ALIGNMENT) T data[N];

		const T& operator[] (size_t i) const
		{
			return data[i];
		}

		T& operator[] (size_t i)
		{
			return data[i];
		}

		size_t size() const
		{
			return N;
		}

	}; // end struct aligned_array


	/********************************************
	 *
	 *	aligned allocation
	 *
	 ********************************************/

    template<typename T>
    T* aligned_allocate(size_t nelements, size_t alignment)
    {
#if BCS_PLATFORM_INTERFACE == BCS_WINDOWS_INTERFACE
    	T* p = static_cast<T*>(::_aligned_malloc(sizeof(T) * nelements, alignment));
    	if (p == 0)
		{
			throw std::bad_alloc();
		}
		return p;

#elif BCS_PLATFORM_INTERFACE == BCS_POSIX_INTERFACE
		char* p = 0;
		if (::posix_memalign((void**)(&p), alignment, sizeof(T) * nelements) != 0)
		{
			throw std::bad_alloc();
		}
		return static_cast<T*>((void*)p);

#endif
    }

    template<typename T>
    void aligned_deallocate(T *p)
    {
#if BCS_PLATFORM_INTERFACE == BCS_WINDOWS_INTERFACE
    	::_aligned_free(p);
#elif BCS_PLATFORM_INTERFACE == BCS_POSIX_INTERFACE
    	::free(p);
#endif
    }

    template<class Allocator>
    inline typename Allocator::pointer safe_allocate(Allocator& allocator, size_t n)
    {
    	return n > 0 ? allocator.allocate(n) : static_cast<typename Allocator::pointer>(BCS_NULL);
    }

    template<class Allocator>
    inline void safe_deallocate(Allocator& allocator, typename Allocator::pointer p, size_t n)
    {
    	if (p)
    	{
    		allocator.deallocate(p, n);
    	}
    }


    template<typename T>
    class aligned_allocator
    {
    public:
    	static const size_t default_memory_alignment = BCS_DEFAULT_ALIGNMENT;

    	typedef T value_type;
    	typedef T* pointer;
    	typedef T& reference;
    	typedef const T* const_pointer;
    	typedef const T& const_reference;
    	typedef size_t size_type;
    	typedef ptrdiff_t difference_type;

    	template<typename TOther>
    	struct rebind
    	{
    		typedef aligned_allocator<TOther> other;
    	};

    public:
    	aligned_allocator()
    	: m_alignment(default_memory_alignment)
    	{
    	}

    	explicit aligned_allocator(size_t align)
    	: m_alignment(align)
    	{
    	}

    	aligned_allocator(const aligned_allocator& r)
    	: m_alignment(r.alignment())
    	{
    	}

    	template<typename U>
    	aligned_allocator(const aligned_allocator<U>& r)
    	: m_alignment(r.alignment())
    	{
    	}

    	size_t alignment() const
    	{
    		return m_alignment;
    	}


    	pointer address( reference x ) const
    	{
    		return &x;
    	}

    	const_pointer address( const_reference x ) const
    	{
    		return &x;
    	}

    	size_type max_size() const
    	{
    		return std::numeric_limits<size_type>::max() / sizeof(value_type);
    	}

    	pointer allocate(size_type n, const void* hint=0)
    	{
    		return aligned_allocate<value_type>(n, m_alignment);
    	}

    	void deallocate(pointer p, size_type)
    	{
    		aligned_deallocate(p);
    	}

    	void construct (pointer p, const_reference val)
    	{
    		new (p) value_type(val);
    	}

    	void destroy (pointer p)
    	{
    		p->~value_type();
    	}

    private:
    	size_t m_alignment;

    }; // end class aligned_allocator


	/********************************************
	 *
	 *	scoped_buffer
	 *
	 ********************************************/

    /**
     * A very simple & efficient temporary buffer, which
     * can only be used within a local scope.
     */
    template<typename T, class Allocator=aligned_allocator<T> >
    class scoped_buffer : private noncopyable
    {
    public:
		typedef T value_type;
		typedef Allocator allocator_type;

		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::const_reference const_reference;

    public:
    	explicit scoped_buffer(size_type n)
    	: m_allocator()
    	, m_pbase(safe_allocate(m_allocator, n))
    	, m_n(n)
    	{
    	}

    	~scoped_buffer()
    	{
    		safe_deallocate(m_allocator, m_pbase, m_n);
    	}

		size_type nelems() const
		{
			return m_n;
		}

		const_pointer pbase() const
		{
			return m_pbase;
		}

		pointer pbase()
		{
			return m_pbase;
		}

		const_reference operator[] (size_type i) const
		{
			return m_pbase[i];
		}

		reference operator[] (size_type i)
		{
			return m_pbase[i];
		}

		const allocator_type& get_allocator() const
		{
			return m_allocator;
		}

    private:
    	Allocator m_allocator;
    	T *m_pbase;
    	size_t m_n;

    }; // end class scoped_buffer


}

#endif
