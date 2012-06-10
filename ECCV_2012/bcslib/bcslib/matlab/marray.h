/**
 * @file marray.h
 *
 * A light-weight wrapper of MATLAB mxArray
 * 
 * @author Dahua Lin
 */

#ifndef BCSLIB_MARRAY_H
#define BCSLIB_MARRAY_H

#include <bcslib/matlab/matlab_base.h>

namespace bcs { namespace matlab {

	class const_marray
	{
	public:
		const_marray(const mxArray *pa)
		: m_pa(const_cast<mxArray*>(pa))
		{
		}

		const mxArray *mx_ptr() const
		{
			return m_pa;
		}

		// size info

		index_t ndims() const
		{
			return (index_t)mxGetNumberOfDimensions(m_pa);
		}

		index_t nrows() const
		{
			return (index_t)mxGetM(m_pa);
		}

		index_t ncolumns() const
		{
			return (index_t)mxGetN(m_pa);
		}

		void get_dims(index_t *dims) const
		{
			index_t nd = ndims();
			const mwSize *ret = mxGetDimensions(m_pa);

			for (index_t i = 0; i < nd; ++i)
			{
				dims[i] = (index_t)ret[i];
			}
		}

		index_t element_size() const
		{
			return (index_t)mxGetElementSize(m_pa);
		}

		index_t nelems() const
		{
			return (index_t)mxGetNumberOfElements(m_pa);
		}

		bool is_empty() const
		{
			return mxIsEmpty(m_pa);
		}

		bool is_scalar() const
		{
			return nelems() == 1;
		}

		bool is_pair() const
		{
			return nelems() == 2;
		}

		bool is_vector() const
		{
			return ndims() == 2 && (nrows() == 1 || ncolumns() == 1);
		}

		bool is_matrix() const
		{
			return ndims() <= 2;
		}

		// type info

		mxClassID class_id() const
		{
			return mxGetClassID(m_pa);
		}

		const char *class_name() const
		{
			return mxGetClassName(m_pa);
		}

		bool is_class(const char* classname) const
		{
			return mxIsClass(m_pa, classname);
		}

		bool is_double() const
		{
			return mxIsDouble(m_pa);
		}

		bool is_single() const
		{
			return mxIsSingle(m_pa);
		}

		bool is_int32() const
		{
			return mxIsInt32(m_pa);
		}

		bool is_uint32() const
		{
			return mxIsUint32(m_pa);
		}

		bool is_int16() const
		{
			return mxIsInt16(m_pa);
		}

		bool is_uint16() const
		{
			return mxIsUint16(m_pa);
		}

		bool is_int8() const
		{
			return mxIsInt8(m_pa);
		}

		bool is_uint8() const
		{
			return mxIsUint8(m_pa);
		}

		bool is_logical() const
		{
			return mxIsLogical(m_pa);
		}

		bool is_numeric() const
		{
			return mxIsNumeric(m_pa);
		}

		bool is_float() const
		{
			return is_double() || is_single();
		}

		bool is_sparse() const
		{
			return mxIsSparse(m_pa);
		}

		bool is_complex() const
		{
			return mxIsComplex(m_pa);
		}

		bool is_cell() const
		{
			return mxIsCell(m_pa);
		}

		bool is_struct() const
		{
			return mxIsStruct(m_pa);
		}


		// data access

		template<typename T>
		const T* data() const
		{
			return (const T*)mxGetData(m_pa);
		}

		template<typename T>
		const T *real_data() const
		{
			return (const T*)mxGetData(m_pa);
		}

		template<typename T>
		const T *imag_data() const
		{
			return (const T*)mxGetImagData(m_pa);
		}

		template<typename T>
		T get_scalar() const
		{
			return *(data<T>());
		}


		// string related

		bool get_cstring(char *str, size_t buflen) const
		{
			return mxGetString(m_pa, str, (mwSize)buflen) == 0;
		}

		std::string to_string() const
		{
			char *sz = mxArrayToString(m_pa);
			std::string str(sz);
			mxFree(sz);
			return str;
		}


		// struct related

		index_t nfields() const
		{
			return (index_t)mxGetNumberOfFields(m_pa);
		}

		const char* field_name(int fieldnum) const
		{
			return mxGetFieldNameByNumber(m_pa, fieldnum);
		}

		int field_number(const char *fieldname) const
		{
			return mxGetFieldNumber(m_pa, fieldname);
		}

		const_marray get_field(int i, const char *fieldname) const
		{
			return mxGetField(m_pa, i, fieldname);
		}

		const_marray get_field(int i, int fieldnum) const
		{
			return mxGetFieldByNumber(m_pa, i, fieldnum);
		}


		// cell related

		index_t ncells() const
		{
			return nelems();
		}

		const_marray get_cell(int i) const
		{
			return mxGetCell(m_pa, i);
		}

		// object related

		const_marray get_property(int i, const char *propertyname) const
		{
			return mxGetProperty(m_pa, i, propertyname);
		}


	protected:
		mxArray *m_pa;

	}; // end class const_marray


	class marray : public const_marray
	{
	public:
		marray() : const_marray(0) { }

		marray(mxArray *pa) : const_marray(pa)
		{
		}

		const mxArray *mx_ptr() const
		{
			return m_pa;
		}

		mxArray *mx_ptr()
		{
			return m_pa;
		}

		// data access

		template<typename T>
		const T* data() const
		{
			return (const T*)mxGetData(m_pa);
		}

		template<typename T>
		T* data()
		{
			return (T*)mxGetData(m_pa);
		}

		template<typename T>
		const T *real_data() const
		{
			return (const T*)mxGetData(m_pa);
		}

		template<typename T>
		T *real_data()
		{
			return (const T*)mxGetData(m_pa);
		}

		template<typename T>
		const T *imag_data() const
		{
			return (const T*)mxGetImagData(m_pa);
		}

		template<typename T>
		T *imag_data()
		{
			return (const T*)mxGetImagData(m_pa);
		}

		// struct access

		void set_field(int i, const char *fieldname, marray a)
		{
			mxSetField(this->m_pa, i, fieldname, a.mx_ptr());
		}

		void set_field(int i, int fieldnum, marray a)
		{
			mxSetFieldByNumber(this->m_pa, i, fieldnum, a.mx_ptr());
		}

		// cell access

		void set_cell(int i, marray a)
		{
			mxSetCell(this->m_pa, i, a.mx_ptr());
		}


	}; // end class marray


	// functions for creating matlab arrays

	template<typename T>
	inline marray create_marray(index_t m, index_t n)
	{
		return mxCreateNumericMatrix((mwSize)m, (mwSize)n,
				mtype_traits<T>::class_id, mxREAL);
	}

	template<>
	inline marray create_marray<bool>(index_t m, index_t n)
	{
		return mxCreateLogicalMatrix((mwSize)m, (mwSize)n);
	}

	inline marray create_mchar_array(index_t m, index_t n)
	{
		mwSize dims[2];
		dims[0] = (mwSize)m;
		dims[1] = (mwSize)n;

		return mxCreateCharArray(2, dims);
	}

	inline marray create_mstring(const char *sz)
	{
		return mxCreateString(sz);
	}

	inline marray create_mstring(std::string& str)
	{
		return mxCreateString(str.c_str());
	}


	template<typename T>
	inline marray create_mscalar(T x)
	{
		marray mA = create_marray<T>(1, 1);
		*(mA.data<T>()) = x;
		return mA;
	}

	inline marray create_mstruct(index_t nfields, const char **fieldnames)
	{
		return mxCreateStructMatrix(1, 1, (int)nfields, fieldnames);
	}

	inline marray create_mstruct_array(index_t m, index_t n, index_t nfields, const char **fieldnames)
	{
		return mxCreateStructMatrix((mwSize)m, (mwSize)n, (int)nfields, fieldnames);
	}

	inline marray create_mcell_array(index_t m, index_t n)
	{
		return mxCreateCellMatrix((mwSize)m, (mwSize)n);
	}

	inline marray duplicate(const_marray a)
	{
		return mxDuplicateArray(a.mx_ptr());
	}

} }

#endif 
