/**
 * @file block.h
 *
 * The block class and relevant classes
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_BLOCK_H_
#define BCSLIB_BLOCK_H_

#include <bcslib/base/basic_mem.h>
#include <bcslib/base/smart_ptr.h>

namespace bcs
{
	// forward declarations

    template<typename T, class Allocator> class const_block;
    template<typename T, class Allocator> class block;


    /********************************************
     *
     *   block implementation details
     *
     ********************************************/

	namespace _detail
	{
    	template<typename T, typename Allocator>
    	class block_impl
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
    		block_impl(pointer p, size_type n)
    		: m_allocator()
    		, m_base(p), m_n(n), m_own(false)
    		{
    		}

    		explicit block_impl(size_type n)
    		: m_allocator()
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			default_construct_elements(m_base, n);
    		}

    		block_impl(size_type n, const allocator_type& allocator)
    		: m_allocator(allocator)
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			default_construct_elements(m_base, n);
    		}

    		block_impl(size_type n, const_reference v)
    		: m_allocator()
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			if (n > 0) copy_construct_elements(v, m_base, n);
    		}

    		block_impl(size_type n, const_reference v, const allocator_type& allocator)
    		: m_allocator(allocator)
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			if (n > 0) copy_construct_elements(v, m_base, n);
    		}

    		block_impl(size_type n, const_pointer src)
    		: m_allocator()
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			if (n > 0) copy_construct_elements(src, m_base, n);
    		}

    		block_impl(size_type n, const_pointer src, const allocator_type& allocator)
    		: m_allocator(allocator)
    		, m_base(safe_allocate(m_allocator, n)), m_n(n), m_own(true)
    		{
    			if (n > 0) copy_construct_elements(src, m_base, n);
    		}

    		~block_impl()
    		{
    			if (m_own)
    			{
    				destruct_elements(m_base, m_n);
    				safe_deallocate(m_allocator, m_base, m_n);
    			}
    		}

    		void release()
    		{
    			if (m_own)
    			{
    				safe_deallocate(m_allocator, m_base, m_n);
    			}

    			m_base = BCS_NULL;
    			m_n = 0;
    			m_own = false;
    		}

    		block_impl(const block_impl& r)
    		: m_allocator(r.m_allocator)
    		, m_base(r.m_own ? safe_allocate(m_allocator, r.m_n) : r.m_base)
    		, m_n(r.m_n)
    		, m_own(r.m_own)
    		{
    			if (m_own && r.m_n > 0) copy_construct_elements(r.m_base, m_base, r.m_n);
    		}

    		void swap(block_impl& r)
    		{
    			using std::swap;

    			swap(m_allocator, r.m_allocator);
    			swap(m_base, r.m_base);
    			swap(m_n, r.m_n);
    			swap(m_own, r.m_own);
    		}

    		void operator = (const block_impl& r)
    		{
    			if (this !=  &r)
    			{
    				block_impl tmp(r);
    				swap(tmp);
    			}
    		}

    	public:
    		size_type nelems() const
    		{
    			return m_n;
    		}

    		const_pointer pbase() const
    		{
    			return m_base;
    		}

    		pointer pbase()
    		{
    			return m_base;
    		}

    		const_reference get(size_type i) const
    		{
    			return m_base[i];
    		}

    		reference get(size_type i)
    		{
    			return m_base[i];
    		}

    		const allocator_type& get_allocator() const
    		{
    			return m_allocator;
    		}

    		bool own_memory() const
    		{
    			return m_own;
    		}

    	private:
    		allocator_type m_allocator;
    		pointer m_base;
    		size_type m_n;
    		bool m_own;

    	}; // end class block_impl
	}


	/********************************************
	 *
	 *	const_block and block
	 *
	 ********************************************/

    // different ways of input memory

    template<typename T>
    class cref_blk_t
    {
    public:
    	cref_blk_t(const T* base, size_t n)
    	: m_base(base), m_n(n)
    	{
    	}

		size_t nelems() const
		{
			return m_n;
		}

		const T* pbase() const
		{
			return m_base;
		}

		const T* pend() const
		{
			return m_base + m_n;
		}

    private:
    	const T *m_base;
    	size_t m_n;
    };


    template<typename T>
    class ref_blk_t
    {
    public:
    	ref_blk_t(T* base, size_t n)
    	: m_base(base), m_n(n)
    	{
    	}

		size_t nelems() const
		{
			return m_n;
		}

		T* pbase() const
		{
			return m_base;
		}

		T* pend() const
		{
			return m_base + m_n;
		}

    private:
    	T *m_base;
    	size_t m_n;
    };


    template<typename T>
    class copy_blk_t
    {
    public:
    	copy_blk_t(const T* base, size_t n)
    	: m_base(base), m_n(n)
    	{
    	}

		size_t nelems() const
		{
			return m_n;
		}

		const T* pbase() const
		{
			return m_base;
		}

		const T* pend() const
		{
			return m_base + m_n;
		}

    private:
    	const T *m_base;
    	size_t m_n;
    };


    template<typename T, typename Allocator=aligned_allocator<T> >
	class const_block
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
		explicit const_block(const cref_blk_t<value_type>& src)
		: m_impl(const_cast<pointer>(src.pbase()), src.nelems())
		{
		}

		const_block(const size_type& n, const_reference v)
		: m_impl(n, v)
		{
		}

		const_block(const size_type& n, const_reference v, const allocator_type& allocator)
		: m_impl(n, v, allocator)
		{
		}

		explicit const_block(const copy_blk_t<value_type>& src)
		: m_impl(src.nelems(), src.pbase())
		{
		}

		const_block(const copy_blk_t<value_type>& src, const allocator_type& allocator)
		: m_impl(src.nelems(), src.pbase(), allocator)
		{
		}


		const_block(const const_block& r)
		: m_impl(r.m_impl)
		{
		}

		const_block& operator = (const const_block& r)
		{
			m_impl = r.m_impl;
			return *this;
		}

		void swap(const_block& r)
		{
			m_impl.swap(r.m_impl);
		}

	public:
		size_type nelems() const
		{
			return m_impl.nelems();
		}

		bool own_memory() const
		{
			return m_impl.own_memory();
		}

		const allocator_type& get_allocator() const
		{
			return m_impl.get_allocator();
		}

		const_pointer pbase() const
		{
			return m_impl.pbase();
		}

		const_pointer pend() const
		{
			return m_impl.pbase() + m_impl.nelems();
		}

		const_reference operator[](size_type i) const
		{
			return m_impl.get(i);
		}

	private:
		_detail::block_impl<T, Allocator> m_impl;

	}; // end class const_block


    template<typename T, typename Allocator=aligned_allocator<T> >
	class block
	{
    	friend class const_block<T, Allocator>;

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
		explicit block(const ref_blk_t<value_type>& src)
		: m_impl(src.pbase(), src.nelems())
		{
		}

		explicit block(const size_type& n)
		: m_impl(n)
		{
		}

		block(const size_type& n, const allocator_type& allocator)
		: m_impl(n, allocator)
		{
		}

		block(const size_type& n, const_reference v)
		: m_impl(n, v)
		{
		}

		block(const size_type& n, const_reference v, const allocator_type& allocator)
		: m_impl(n, v, allocator)
		{
		}

		explicit block(const copy_blk_t<value_type>& src)
		: m_impl(src.nelems(), src.pbase())
		{
		}

		block(const copy_blk_t<value_type>& src, const allocator_type& allocator)
		: m_impl(src.nelems(), src.pbase(), allocator)
		{
		}

		block(const block& r)
		: m_impl(r.m_impl)
		{
		}

		block& operator = (const block& r)
		{
			m_impl = r.m_impl;
			return *this;
		}

		void swap(block& r)
		{
			m_impl.swap(r.m_impl);
		}

	public:
		size_type nelems() const
		{
			return m_impl.nelems();
		}

		bool own_memory() const
		{
			return m_impl.own_memory();
		}

		const allocator_type& get_allocator() const
		{
			return m_impl.get_allocator();
		}

		const_pointer pbase() const
		{
			return m_impl.pbase();
		}

		pointer pbase()
		{
			return m_impl.pbase();
		}

		const_pointer pend() const
		{
			return m_impl.pbase() + m_impl.nelems();
		}

		pointer pend()
		{
			return m_impl.pbase() + m_impl.nelems();
		}

		const_reference operator[](size_type i) const
		{
			return m_impl.get(i);
		}

		reference operator[](size_type i)
		{
			return m_impl.get(i);
		}

	private:
		_detail::block_impl<T, Allocator> m_impl;

	}; // end class block

	// specialize swap for const_block and block

	template<typename T, class Allocator>
	inline void swap(bcs::const_block<T, Allocator>& lhs, bcs::const_block<T, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}

	template<typename T, class Allocator>
	inline void swap(bcs::block<T, Allocator>& lhs, bcs::block<T, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}


	// convenient routines

    template<typename T>
    inline cref_blk_t<T> cref_blk(const T *p, size_t n)
    {
    	return cref_blk_t<T>(p, n);
    }

    template<typename T, class Allocator>
    inline cref_blk_t<T> cref_blk(const const_block<T, Allocator>& blk)
    {
    	return cref_blk_t<T>(blk.pbase(), blk.nelems());
    }

    template<typename T, class Allocator>
    inline cref_blk_t<T> cref_blk(const block<T, Allocator>& blk)
    {
    	return cref_blk_t<T>(blk.pbase(), blk.nelems());
    }

    template<typename T>
    inline ref_blk_t<T> ref_blk(T *p, size_t n)
    {
    	return ref_blk_t<T>(p, n);
    }

    template<typename T, class Allocator>
    inline ref_blk_t<T> ref_blk(block<T, Allocator>& blk)
    {
    	return ref_blk_t<T>(blk.pbase(), blk.nelems());
    }


    template<typename T>
    inline copy_blk_t<T> copy_blk(const T *p, size_t n)
    {
    	return copy_blk_t<T>(p, n);
    }

    template<typename T, class Allocator>
    inline copy_blk_t<T> copy_blk(const const_block<T, Allocator>& blk)
    {
    	return copy_blk_t<T>(blk.pbase(), blk.nelems());
    }

    template<typename T, class Allocator>
    inline copy_blk_t<T> copy_blk(const block<T, Allocator>& blk)
    {
    	return copy_blk_t<T>(blk.pbase(), blk.nelems());
    }


    /**********************************************
     *
     *  shared block
     *
     **********************************************/

    template<typename T, class Allocator=aligned_allocator<T> >
    class shared_block
    {
    public:
    	typedef block<T, Allocator> block_type;

    	explicit shared_block(size_t n)
    	: m_sp_block(new block_type(n))
    	{
    	}

    	shared_block(size_t n, const T& v)
    	: m_sp_block(new block_type(n, v))
    	{
    	}

    	shared_block(size_t n, const T *src)
    	: m_sp_block(new block_type(copy_blk(src, n)))
    	{
    	}

    public:
    	size_t nelems() const
    	{
    		return m_sp_block->nelems();
    	}

    	T* pbase()
    	{
    		return m_sp_block->pbase();
    	}

    	const T* pbase() const
    	{
    		return m_sp_block->pbase();
    	}

    	T* pend()
    	{
    		return pbase() + nelems();
    	}

    	const T* pend() const
    	{
    		return pbase() + nelems();
    	}

    	const T& operator[] (size_t i) const
    	{
    		return pbase()[i];
    	}

    	T& operator[] (size_t i)
    	{
    		return pbase()[i];
    	}

    public:
    	void swap(shared_block& r)
    	{
    		m_sp_block.swap(r.m_sp_block);
    	}

    	bool is_unique() const
    	{
    		return m_sp_block.unique();
    	}

    	void make_unique()
    	{
    		if (!is_unique())
    		{
    			m_sp_block.reset(new block_type(*m_sp_block));
    		}
    	}

    	shared_block deep_copy() const
    	{
    		return shared_block(nelems(), pbase());
    	}

    private:
    	shared_ptr<block_type> m_sp_block;

    }; // end class sharable_storage_base

}

#endif 
