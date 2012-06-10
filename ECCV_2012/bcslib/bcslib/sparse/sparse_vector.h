/**
 * @file sparse_vector.h
 *
 * A class to represent sparse vectors
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_SPARSE_VECTOR_H
#define BCSLIB_SPARSE_VECTOR_H

#include <bcslib/array/array_base.h>

namespace bcs
{
	// forward declarations

	class spvec_pattern_cview;
	class spvec_pattern;

	template<typename T> class spvec_cview;
	template<typename T> class spvec_view;
	template<typename T> class spvec;

	// pattern classes

	class spvec_pattern_cview
	{
	public:
		static const dim_num_t num_dims = 1u;
		typedef size_t size_type;
		typedef index_t index_type;
		typedef array<index_type, num_dims> shape_type;

		template<typename T> friend class spvec;

	public:
		spvec_pattern_cview(size_type n, size_type na, const index_type *inds)
		: m_d0((index_type)n), m_na(na), m_indices(inds)
		{
		}

		dim_num_t ndims() const
		{
			return num_dims;
		}

		size_type nelems() const
		{
			return (size_type)m_d0;
		}

		index_type dim0() const
		{
			return m_d0;
		}

		shape_type shape() const
		{
			return arr_shape(m_d0);
		}

		size_type nactives() const
		{
			return m_na;
		}

		const index_type *active_indices() const
		{
			return m_indices;
		}

		index_type get(size_type i) const
		{
			return m_indices[i];
		}

	protected:
		index_type m_d0;
		size_type m_na;
		const index_type *m_indices;

	}; // end class spvec_pattern_cview


	// sparse vector classes

	class spvec_pattern : public spvec_pattern_cview
	{
	public:
		static const dim_num_t num_dims = 1u;
		typedef size_t size_type;
		typedef index_t index_type;
		typedef array<index_type, num_dims> shape_type;

		typedef block<index_type> block_type;

	public:
		spvec_pattern(size_type n, size_type na, const index_type *inds)
		: spvec_pattern_cview(n, na, 0)
		, m_pblock(new block_type(na, inds))
		{
			this->m_indices = m_pblock->pbase();
		}

		spvec_pattern(const spvec_pattern& src)
		: spvec_pattern_cview(src)
		, m_pblock(src.m_pblock)
		{
		}

		spvec_pattern(const spvec_pattern_cview& src)
		: spvec_pattern_cview(src.nelems(), src.nactives(), 0)
		, m_pblock(new block_type(src.nactives(), src.active_indices()))
		{
			this->m_indices = m_pblock->pbase();
		}

		spvec_pattern(size_type n, block_type *pblk)
		: spvec_pattern_cview(n, pblk->nelems(), pblk->pbase())
		, m_pblock(pblk)
		{
		}

	private:
		shared_ptr<block_type> m_pblock;

	}; // end class spvec_pattern


	template<typename T>
	class spvec_cview
	{
	public:
		BCS_ARRAY_BASIC_TYPEDEFS(1u, T)
		typedef indexed_entry<value_type, index_type> pair_type;

	public:
		spvec_cview(const spvec_pattern_cview& pattern, const value_type *vals)
		: m_pattern(pattern), m_values(const_cast<value_type*>(vals))
		{
		}

		dim_num_t ndims() const
		{
			return num_dims;
		}

		const spvec_pattern_cview& pattern() const
		{
			return m_pattern;
		}

		size_type nelems() const
		{
			return m_pattern.nelems();
		}

		index_type dim0() const
		{
			return m_pattern.dim0();
		}

		shape_type shape() const
		{
			return m_pattern.shape();
		}

		size_type nactives() const
		{
			return m_pattern.nactives();
		}

		const index_type *active_indices() const
		{
			return m_pattern.active_indices();
		}

		const value_type *active_values() const
		{
			return m_values;
		}

		const index_type& active_index(size_type i) const
		{
			return m_pattern.get(i);
		}

		const value_type& active_value(size_type i) const
		{
			return m_values[i];
		}

		pair_type active_pair(size_type i) const
		{
			pair_type pa;
			pa.set(m_values[i], m_pattern.get(i));
			return pa;
		}

		template<typename TIter>
		void export_pairs(TIter dst_it) const
		{
			size_type na = nactives();
			for (size_type i = 0; i < na; ++i)
			{
				*(dst_it++) = active_pair(i);
			}
		}

	protected:
		spvec_pattern_cview m_pattern;
		value_type *m_values;

	}; // end class spvec_cview


	template<typename T>
	class spvec_view : public spvec_cview<T>
	{
	public:
		BCS_ARRAY_BASIC_TYPEDEFS(1u, T)
		typedef indexed_entry<value_type, index_type> pair_type;

	public:
		spvec_view(const spvec_pattern_cview& pattern, value_type *vals)
		: spvec_cview<T>(pattern, vals)
		{
		}

		const value_type *active_values() const
		{
			return this->m_values;
		}

		value_type *active_values()
		{
			return this->m_values;
		}

	}; // end class spvec_view


	template<typename T>
	class spvec : public spvec_view<T>
	{
	public:
		BCS_ARRAY_BASIC_TYPEDEFS(1u, T)
		typedef indexed_entry<value_type, index_type> pair_type;

		typedef block<value_type> value_block_type;
	public:
		explicit spvec(const spvec_pattern& pattern)
		: spvec_view<T>(pattern, 0)
		, m_p_pattern(pattern), m_p_values(new value_block_type(pattern.nactives()))
		{
			this->m_pattern.m_indices = m_p_pattern.active_indices();
			this->m_values = m_p_values->pbase();
		}

		explicit spvec(const spvec_pattern_cview& pattern)
		: spvec_view<T>(pattern, 0)
		, m_p_pattern(pattern), m_p_values(new value_block_type(pattern.nactives()))
		{
			this->m_pattern.m_indices = m_p_pattern.active_indices();
			this->m_values = m_p_values->pbase();
		}

		spvec(const spvec_pattern& pattern, const value_type *src)
		: spvec_view<T>(pattern, 0)
		, m_p_pattern(pattern), m_p_values(new value_block_type(pattern.nactives(), src))
		{
			this->m_pattern.m_indices = m_p_pattern.active_indices();
			this->m_values = m_p_values->pbase();
		}

		spvec(const spvec_pattern_cview& pattern, const value_type *src)
		: spvec_view<T>(pattern, 0)
		, m_p_pattern(pattern), m_p_values(new value_block_type(pattern.nactives(), src))
		{
			this->m_pattern.m_indices = m_p_pattern.active_indices();
			this->m_values = m_p_values->pbase();
		}

		spvec<T> make_copy_shared_pattern() const
		{
			return spvec<T>(m_p_pattern, this->active_values());
		}

	private:
		spvec_pattern m_p_pattern;
		shared_ptr<value_block_type> m_p_values;

	}; // end class spvec_cview


	inline spvec_pattern make_copy(const spvec_pattern_cview& pattern)
	{
		return spvec_pattern(pattern);
	}

	template<typename T>
	inline spvec<T> make_copy(const spvec_cview<T>& src)
	{
		return spvec<T>(src.pattern(), src.active_values());
	}

}

#endif 
