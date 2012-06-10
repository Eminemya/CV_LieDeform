/**
 * @file transpose2d.h
 *
 * Implementation of 2D transposition
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_TRANSPOSE2D_H_
#define BCSLIB_TRANSPOSE2D_H_

#define BCS_TRANSPOSITION_BLOCK_BYTES 1024

namespace bcs
{

	/**
	 * Transpose the matrix in source to destination (using direct assignment)
	 *
	 * Note: This is out-of-place transposition, and there
	 * should be no overlap between src and dst
	 *
	 * The source have m slices, each of length n,
	 * The result have n slices, each of length m.
	 */
	template<typename T>
	inline void direct_transpose_matrix(const T *src, T *dst, size_t m, size_t n)
	{
		for (size_t i = 0; i < m; ++i)
		{
			T *pd = dst + i;
			for (size_t j = 0; j < n; ++j, pd += m)
			{
				*pd = *(src++);
			}
		}
	}


	template<typename T>
	inline void direct_transpose_sqmatrix_inplace(T *a, size_t n)
	{
		using std::swap;

		for (size_t i = 1; i < n; ++i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				swap(a[i * n + j], a[j * n + i]);
			}
		}
	}


	namespace _detail
	{
		template<typename T>
		inline void _tr_process_block(const T *src, T *dst, T *cache, size_t m, size_t n,
				size_t bdim, size_t bi, size_t bj,
				size_t bm, size_t bn, size_t bu)
		{
			size_t ii = bi * bdim;
			size_t jj = bj * bdim;

			const T *ps = src + (ii * n + jj);
			T *pd = dst + (jj * m + ii);

			// copy source block [bm x bn] to cache [bu x bu]
			T *c = cache;
			for (size_t i = 0; i < bm; ++i, ps += n, c += bu)
			{
				for (size_t j = 0; j < bn; ++j)
				{
					c[j] = ps[j];
				}
			}

			// within-cache transpose
			direct_transpose_sqmatrix_inplace(cache, bu);

			// copy transposed cache [bu x bu] to destination block [bn x bm]
			c = cache;
			for (size_t i = 0; i < bn; ++i, c += bu, pd += m)
			{
				for (size_t j = 0; j < bm; ++j)
				{
					pd[j] = c[j];
				}
			}
		}

	}



	template<typename T>
	void blockwise_transpose_matrix(const T *src, T *dst, size_t m, size_t n, size_t bdim, T *cache)
	{
		size_t n_br = m / bdim;
		size_t n_bc = n / bdim;

		size_t rm = m - n_br * bdim;
		size_t rn = n - n_bc * bdim;

		// deal with main blocks [bdim x bdim]

		for (size_t bi = 0; bi < n_br; ++bi)
		{
			for (size_t bj = 0; bj < n_bc; ++bj)
			{
				_detail::_tr_process_block(src, dst, cache, m, n, bdim, bi, bj, bdim, bdim, bdim);
			}
		}

		// deal with right-edge blocks [bdim x rn]

		if (rn > 0)
		{
			for (size_t bi = 0; bi < n_br; ++bi)
			{
				_detail::_tr_process_block(src, dst, cache, m, n, bdim, bi, n_bc, bdim, rn, bdim);
			}
		}

		// deal with bottom-edge blocks [rm x bdim]

		if (rm > 0)
		{
			for (size_t bj = 0; bj < n_bc; ++bj)
			{
				_detail::_tr_process_block(src, dst, cache, m, n, bdim, n_br, bj, rm, bdim, bdim);
			}
		}

		// deal with block at bottom-right [rm x rn]

		size_t rbu = rm > rn ? rm : rn;
		if (rbu > 0)
		{
			_detail::_tr_process_block(src, dst, cache, m, n, bdim, n_br, n_bc, rm, rn, rbu);
		}
	}

}

#endif
