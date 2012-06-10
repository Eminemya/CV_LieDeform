/**
 * @file aview_blas.h
 *
 * BLAS functions on array views
 * 
 * @author Dahua Lin
 */

#ifndef AVIEW_BLAS_H_
#define AVIEW_BLAS_H_

#include <bcslib/array/aview1d_base.h>
#include <bcslib/array/aview2d_base.h>
#include <bcslib/extern/blas_select.h>

namespace bcs { namespace blas {


	/**********************************
	 *
	 *  BLAS Level 1
	 *
	 **********************************/

	// ASUM

	template<class Derived>
	inline double asum(const IConstContinuousAView1D<Derived, double>& vec)
	{
		double s = 0;
		int n = (int)vec.nelems();
		if (n > 0)
		{
			int incx = 1;
			s = BCS_DASUM(&n, vec.pbase(), &incx);
		}
		return s;
	}

	template<class Derived>
	inline float asum(const IConstContinuousAView1D<Derived, float>& vec)
	{
		float s = 0;
		int n = (int)vec.nelems();
		if (n > 0)
		{
			int incx = 1;
			s = BCS_SASUM(&n, vec.pbase(), &incx);
		}
		return s;
	}


	// AXPY

	template<class DerivedX, class DerivedY>
	inline void axpy(const IConstContinuousAView1D<DerivedX, double>& x,
			IContinuousAView1D<DerivedY, double>& y, double alpha)
	{
		check_arg(x.nelems() == y.nelems(), "blas::axpy: inconsistent dimensions");
		int n = (int)x.nelems();
		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			BCS_DAXPY(&n, &alpha, x.pbase(), &incx, y.pbase(), &incy);
		}
	}

	template<class DerivedX, class DerivedY>
	inline void axpy(const IConstContinuousAView1D<DerivedX, float>& x,
			IContinuousAView1D<DerivedY, float>& y, float alpha)
	{
		check_arg(x.nelems() == y.nelems(), "blas::axpy: inconsistent dimensions");
		int n = (int)x.nelems();
		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			BCS_SAXPY(&n, &alpha, x.pbase(), &incx, y.pbase(), &incy);
		}
	}


	// DOT

	template<class DerivedX, class DerivedY>
	inline double dot(const IConstContinuousAView1D<DerivedX, double>& x,
			IConstContinuousAView1D<DerivedY, double>& y)
	{
		check_arg(x.nelems() == y.nelems(), "blas::dot: inconsistent dimensions");
		int n = (int)x.nelems();
		double s = 0;
		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			s = BCS_DDOT(&n, x.pbase(), &incx, y.pbase(), &incy);
		}
		return s;
	}

	template<class DerivedX, class DerivedY>
	inline float dot(const IConstContinuousAView1D<DerivedX, float>& x,
			IConstContinuousAView1D<DerivedY, float>& y)
	{
		check_arg(x.nelems() == y.nelems(), "blas::dot: inconsistent dimensions");
		int n = (int)x.nelems();
		float s = 0;
		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			s = BCS_SDOT(&n, x.pbase(), &incx, y.pbase(), &incy);
		}
		return s;
	}


	// NRM2

	template<class Derived>
	inline double nrm2(const IConstContinuousAView1D<Derived, double>& vec)
	{
		double s = 0;
		int n = (int)vec.nelems();
		if (n > 0)
		{
			int incx = 1;
			s = BCS_DNRM2(&n, vec.pbase(), &incx);
		}
		return s;
	}

	template<class Derived>
	inline float nrm2(const IConstContinuousAView1D<Derived, float>& vec)
	{
		float s = 0;
		int n = (int)vec.nelems();
		if (n > 0)
		{
			int incx = 1;
			s = BCS_SNRM2(&n, vec.pbase(), &incx);
		}
		return s;
	}


	// ROT

	template<class Derived>
	inline void rot(IContinuousAView1D<Derived, double>& x,
			IContinuousAView1D<Derived, double>& y, double c, double s)
	{
		check_arg(x.nelems() == y.nelems(), "blas::rot: inconsistent dimensions");
		int n = (int)x.nelems();

		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			BCS_DROT(&n, x.pbase(), &incx, y.pbase(), &incy, &c, &s);
		}
	}

	template<class Derived>
	inline void rot(IContinuousAView1D<Derived, float>& x,
			IContinuousAView1D<Derived, float>& y, float c, float s)
	{
		check_arg(x.nelems() == y.nelems(), "blas::rot: inconsistent dimensions");
		int n = (int)x.nelems();

		if (n > 0)
		{
			int incx = 1;
			int incy = 1;
			BCS_SROT(&n, x.pbase(), &incx, y.pbase(), &incy, &c, &s);
		}
	}


	/**********************************
	 *
	 *  BLAS Level 2
	 *
	 **********************************/

	inline char check_trans(char trans)
	{
		if (trans == 'N' || trans == 'n') return 'N';
		else if (trans == 'T' || trans == 't') return 'T';
		else throw invalid_argument("blas: invalid character for trans.");
	}

	inline char check_uplo(char uplo)
	{
		if (uplo == 'U' || uplo == 'u') return 'U';
		else if (uplo == 'L' || uplo == 'l') return 'L';
		else throw invalid_argument("blas: invalid character for uplo.");
	}

	// GEMV

	namespace _detail
	{
		template<class DerivedA, class DerivedX, class DerivedY, typename T, typename TOrd>
		inline void check_gemv_dims(
				const IConstBlockAView2D<DerivedA, T, TOrd>& a, char& trans,
				const IConstContinuousAView1D<DerivedX, T>& x,
				const IContinuousAView1D<DerivedY, T>& y, int& m, int &n)
		{
			trans = check_trans(trans);
			m = (int)a.nrows();
			n = (int)a.ncolumns();
			int dx = (int)x.dim0();
			int dy = (int)y.dim0();

			if (trans == 'N')
			{
				check_arg(n == dx && m == dy, "blas::gemv: inconsistent dimensions");
			}
			else // trans == 'T'
			{
				check_arg(n == dy && m == dx, "blas::gemv: inconsistent dimensions");
			}
		}
	}

	template<class DerivedA, class DerivedX, class DerivedY>
	inline void gemv(
			const IConstBlockAView2D<DerivedA, double, column_major_t>& a, char trans,
			const IConstContinuousAView1D<DerivedX, double>& x,
			IContinuousAView1D<DerivedY, double>& y, double alpha, double beta)
	{
		int m, n;
		_detail::check_gemv_dims(a, trans, x, y, m, n);

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DGEMV(&trans, &m, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}

	template<class DerivedA, class DerivedX, class DerivedY>
	inline void gemv(
			const IConstBlockAView2D<DerivedA, float, column_major_t>& a, char trans,
			const IConstContinuousAView1D<DerivedX, float>& x,
			IContinuousAView1D<DerivedY, float>& y, float alpha, float beta)
	{
		int m, n;
		_detail::check_gemv_dims(a, trans, x, y, m, n);

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SGEMV(&trans, &m, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void gemv(
			const IConstBlockAView2D<DerivedA, double, row_major_t>& a, char trans,
			const IConstContinuousAView1D<DerivedX, double>& x,
			IContinuousAView1D<DerivedY, double>& y, double alpha, double beta)
	{
		int m, n;
		_detail::check_gemv_dims(a, trans, x, y, n, m);
		trans = (trans == 'N' ? 'T' : 'N');

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DGEMV(&trans, &m, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void gemv(
			const IConstBlockAView2D<DerivedA, float, row_major_t>& a, char trans,
			const IConstContinuousAView1D<DerivedX, float>& x,
			IContinuousAView1D<DerivedY, float>& y, float alpha, float beta)
	{
		int m, n;
		_detail::check_gemv_dims(a, trans, x, y, n, m);
		trans = (trans == 'N' ? 'T' : 'N');

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SGEMV(&trans, &m, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	// GER

	template<class DerivedA, class DerivedX, class DerivedY>
	inline void ger(IBlockAView2D<DerivedA, double, column_major_t>& a,
			const IConstContinuousAView1D<DerivedX, double>& x,
			const IConstContinuousAView1D<DerivedY, double>& y, double alpha)
	{
		int m = (int)a.nrows();
		int n = (int)a.ncolumns();
		check_arg(m == x.nelems() && n == y.nelems(), "blas::ger: inconsistent dimensions");

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DGER(&m, &n, &alpha, x.pbase(), &incx, y.pbase(), &incy, a.pbase(), &lda);
		}
	}

	template<class DerivedA, class DerivedX, class DerivedY>
	inline void ger(IBlockAView2D<DerivedA, float, column_major_t>& a,
			const IConstContinuousAView1D<DerivedX, float>& x,
			const IConstContinuousAView1D<DerivedY, float>& y, float alpha)
	{
		int m = (int)a.nrows();
		int n = (int)a.ncolumns();
		check_arg(m == x.nelems() && n == y.nelems(), "blas::ger: inconsistent dimensions");

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SGER(&m, &n, &alpha, x.pbase(), &incx, y.pbase(), &incy, a.pbase(), &lda);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void ger(IBlockAView2D<DerivedA, double, row_major_t>& a,
			const IConstContinuousAView1D<DerivedX, double>& x,
			const IConstContinuousAView1D<DerivedY, double>& y, double alpha)
	{
		int n = (int)a.nrows();
		int m = (int)a.ncolumns();
		check_arg(m == y.nelems() && n == x.nelems(), "blas::ger: inconsistent dimensions");

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DGER(&m, &n, &alpha, y.pbase(), &incx, x.pbase(), &incy, a.pbase(), &lda);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void ger(IBlockAView2D<DerivedA, float, row_major_t>& a,
			const IConstContinuousAView1D<DerivedX, float>& x,
			const IConstContinuousAView1D<DerivedY, float>& y, float alpha)
	{
		int n = (int)a.nrows();
		int m = (int)a.ncolumns();
		check_arg(m == y.nelems() && n == x.nelems(), "blas::ger: inconsistent dimensions");

		if (m > 0 && n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SGER(&m, &n, &alpha, y.pbase(), &incx, x.pbase(), &incy, a.pbase(), &lda);
		}
	}


	// SYMV

	namespace _detail
	{
		template<class DerivedA, class DerivedX, class DerivedY, typename T, typename TOrd>
		inline void check_symv_dims(
				const IConstBlockAView2D<DerivedA, T, TOrd>& a,
				const IConstContinuousAView1D<DerivedX, T>& x,
				const IContinuousAView1D<DerivedY, T>& y, int &n)
		{
			int m = (int)a.nrows();
			n = (int)a.ncolumns();

			check_arg(m == n, "blas::symv: a should be a square matrix,");
			check_arg((int)x.nelems() == n, "blas::symv: inconsistent dimensions.");
			check_arg((int)y.nelems() == n, "blas::symv: inconsistent dimensions.");
		}
	}

	template<class DerivedA, class DerivedX, class DerivedY>
	inline void symv(const IConstBlockAView2D<DerivedA, double, column_major_t>& a, char uplo,
			const IConstContinuousAView1D<DerivedX, double>& x,
			IContinuousAView1D<DerivedY, double>& y, double alpha, double beta)
	{
		int n;
		_detail::check_symv_dims(a, x, y, n);
		uplo = check_uplo(uplo);

		if (n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DSYMV(&uplo, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void symv(const IConstBlockAView2D<DerivedA, float, column_major_t>& a, char uplo,
			const IConstContinuousAView1D<DerivedX, float>& x,
			IContinuousAView1D<DerivedY, float>& y, float alpha, float beta)
	{
		int n;
		_detail::check_symv_dims(a, x, y, n);
		uplo = check_uplo(uplo);

		if (n > 0)
		{
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SSYMV(&uplo, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void symv(const IConstBlockAView2D<DerivedA, double, row_major_t>& a, char uplo,
			const IConstContinuousAView1D<DerivedX, double>& x,
			IContinuousAView1D<DerivedY, double>& y, double alpha, double beta)
	{
		int n;
		_detail::check_symv_dims(a, x, y, n);
		uplo = check_uplo(uplo);

		if (n > 0)
		{
			uplo = (uplo == 'U' ? 'L' : 'U');
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_DSYMV(&uplo, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	template<class DerivedA, class DerivedX, class DerivedY>
	inline void symv(const IConstBlockAView2D<DerivedA, float, row_major_t>& a, char uplo,
			const IConstContinuousAView1D<DerivedX, float>& x,
			IContinuousAView1D<DerivedY, float>& y, float alpha, float beta)
	{
		int n;
		_detail::check_symv_dims(a, x, y, n);
		uplo = check_uplo(uplo);

		if (n > 0)
		{
			uplo = (uplo == 'U' ? 'L' : 'U');
			int lda = (int)a.lead_dim();
			int incx = 1;
			int incy = 1;
			BCS_SSYMV(&uplo, &n, &alpha, a.pbase(), &lda, x.pbase(), &incx, &beta, y.pbase(), &incy);
		}
	}


	/**********************************
	 *
	 *  BLAS Level 3
	 *
	 **********************************/

	// GEMM

	namespace _detail
	{
		template<class DerivedA, class DerivedB, class DerivedC, typename T, typename TOrd>
		inline void check_gemm_dims(const IConstBlockAView2D<DerivedA, T, TOrd>& a, char& transa,
				const IConstBlockAView2D<DerivedB, T, TOrd>& b, char& transb,
				const IBlockAView2D<DerivedC, T, TOrd>& c,
				int& m, int& n, int& k)
		{
			transa = check_trans(transa);
			transb = check_trans(transb);

			int ma = (int)a.nrows();
			int na = (int)a.ncolumns();
			int mb = (int)b.nrows();
			int nb = (int)b.ncolumns();
			int mc = (int)c.nrows();
			int nc = (int)c.ncolumns();

			int inner_a, inner_b;
			if (transa == 'N') { m = ma; inner_a = na; }
			else { m = na; inner_a = ma; }
			if (transb == 'N') { n = nb; inner_b = mb;	}
			else { n = mb; inner_b = nb; }

			check_arg(inner_a == inner_b, "blas::gemm: inconsistent dimensions");
			check_arg(m == mc && n == nc, "blas::gemm: inconsistent dimensions");
			k = inner_a;
		}

	}

	template<class DerivedA, class DerivedB, class DerivedC>
	inline void gemm(
			const IConstBlockAView2D<DerivedA, double, column_major_t>& a, char transa,
			const IConstBlockAView2D<DerivedB, double, column_major_t>& b, char transb,
			IBlockAView2D<DerivedC, double, column_major_t>& c, double alpha, double beta)
	{
		int m, n, k;
		_detail::check_gemm_dims(a, transa, b, transb, c, m, n, k);

		if (m > 0 && n > 0 && k > 0)
		{
			int lda = (int)a.lead_dim();
			int ldb = (int)b.lead_dim();
			int ldc = (int)c.lead_dim();

			BCS_DGEMM(&transa, &transb, &m, &n, &k, &alpha, a.pbase(), &lda, b.pbase(), &ldb, &beta, c.pbase(), &ldc);
		}
	}

	template<class DerivedA, class DerivedB, class DerivedC>
	inline void gemm(
			const IConstBlockAView2D<DerivedA, float, column_major_t>& a, char transa,
			const IConstBlockAView2D<DerivedB, float, column_major_t>& b, char transb,
			IBlockAView2D<DerivedC, float, column_major_t>& c, float alpha, float beta)
	{
		int m, n, k;
		_detail::check_gemm_dims(a, transa, b, transb, c, m, n, k);

		if (m > 0 && n > 0 && k > 0)
		{
			int lda = (int)a.lead_dim();
			int ldb = (int)b.lead_dim();
			int ldc = (int)c.lead_dim();

			BCS_SGEMM(&transa, &transb, &m, &n, &k, &alpha, a.pbase(), &lda, b.pbase(), &ldb, &beta, c.pbase(), &ldc);
		}
	}

	template<class DerivedA, class DerivedB, class DerivedC>
	inline void gemm(
			const IConstBlockAView2D<DerivedA, double, row_major_t>& a, char transa,
			const IConstBlockAView2D<DerivedB, double, row_major_t>& b, char transb,
			IBlockAView2D<DerivedC, double, row_major_t>& c, double alpha, double beta)
	{
		int m, n, k;
		_detail::check_gemm_dims(a, transa, b, transb, c, m, n, k);

		if (m > 0 && n > 0 && k > 0)
		{
			int lda = (int)a.lead_dim();
			int ldb = (int)b.lead_dim();
			int ldc = (int)c.lead_dim();

			BCS_DGEMM(&transb, &transa, &n, &m, &k, &alpha, b.pbase(), &ldb, a.pbase(), &lda, &beta, c.pbase(), &ldc);
		}
	}

	template<class DerivedA, class DerivedB, class DerivedC>
	inline void gemm(
			const IConstBlockAView2D<DerivedA, float, row_major_t>& a, char transa,
			const IConstBlockAView2D<DerivedB, float, row_major_t>& b, char transb,
			IBlockAView2D<DerivedC, float, row_major_t>& c, float alpha, float beta)
	{
		int m, n, k;
		_detail::check_gemm_dims(a, transa, b, transb, c, m, n, k);

		if (m > 0 && n > 0 && k > 0)
		{
			int lda = (int)a.lead_dim();
			int ldb = (int)b.lead_dim();
			int ldc = (int)c.lead_dim();

			BCS_SGEMM(&transb, &transa, &n, &m, &k, &alpha, b.pbase(), &ldb, a.pbase(), &lda, &beta, c.pbase(), &ldc);
		}
	}


} }

#endif 
