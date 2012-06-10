/**
 * @file aview1d_base.h
 *
 * The basic concepts for 1D array views
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_AVIEW1D_BASE_H
#define BCSLIB_AVIEW1D_BASE_H

#include <bcslib/array/aview_base.h>
#include <bcslib/array/aindex.h>

namespace bcs
{

	template<class Derived, typename T>
	class IConstAView1DBase
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived);

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().ndims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}
	};


	template<class Derived, typename T>
	class IAView1DBase
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived);

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().ndims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}
	};



	template<class Derived, typename T>
	class IConstRegularAView1D : public IConstAView1DBase<Derived, T>
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived);

		// base interfaces

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().ndims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}

		// new interfaces

		BCS_ENSURE_INLINE const_reference operator() (index_type i) const
		{
			return derived().operator()(i);
		}
	};


	template<class Derived, typename T>
	class IRegularAView1D : public IAView1DBase<Derived, T>
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived);

		// base interfaces

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().ndims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}

		// new interfaces

		BCS_ENSURE_INLINE const_reference operator() (index_type i) const
		{
			return derived().operator()(i);
		}

		BCS_ENSURE_INLINE reference operator() (index_type i)
		{
			return derived().operator()(i);
		}
	};


	template<class Derived, typename T>
	class IConstContinuousAView1D : public IConstRegularAView1D<Derived, T>
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived)

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().dims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}

		// new interfaces

		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return derived().pbase();
		}

		BCS_ENSURE_INLINE const_reference operator[](index_type i) const
		{
			return derived().operator[](i);
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i) const
		{
			return derived().operator()(i);
		}

	};


	template<class Derived, typename T>
	class IContinuousAView1D : public IRegularAView1D<Derived, T>
	{
	public:
		BCS_AVIEW_INTERFACE_DEFS(Derived)

		BCS_ENSURE_INLINE dim_num_t ndims() const
		{
			return derived().ndims();
		}

		BCS_ENSURE_INLINE size_type size() const
		{
			return derived().size();
		}

		BCS_ENSURE_INLINE index_type nelems() const
		{
			return derived().nelems();
		}

		BCS_ENSURE_INLINE bool is_empty() const
		{
			return derived().is_empty();
		}

		BCS_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		BCS_ENSURE_INLINE index_type dim0() const
		{
			return derived().dim0();
		}

		// new interfaces

		BCS_ENSURE_INLINE const_pointer pbase() const
		{
			return derived().pbase();
		}

		BCS_ENSURE_INLINE pointer pbase()
		{
			return derived().pbase();
		}

		BCS_ENSURE_INLINE const_reference operator[](index_type i) const
		{
			return derived().operator[](i);
		}

		BCS_ENSURE_INLINE reference operator[](index_type i)
		{
			return derived().operator[](i);
		}

		BCS_ENSURE_INLINE const_reference operator() (index_type i) const
		{
			return derived().operator()(i);
		}

		BCS_ENSURE_INLINE reference operator() (index_type i)
		{
			return derived().operator()(i);
		}

	};


	// convenient generic functions

	template<class LDerived, typename LT, class RDerived, typename RT>
	inline bool is_same_shape(const IConstAView1DBase<LDerived, LT>& lhs, const IConstAView1DBase<RDerived, RT>& rhs)
	{
		return lhs.dim0() == rhs.dim0();
	}


}

#endif 
