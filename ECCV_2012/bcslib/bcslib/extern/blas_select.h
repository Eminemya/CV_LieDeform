/**
 * @file blas_select.h
 *
 * A selected subset of BLAS function declarations
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_BLAS_SELECT_H_
#define BCSLIB_BLAS_SELECT_H_

// function name macros

// BLAS Level 1

#define BCS_SASUM   sasum
#define BCS_SAXPY   saxpy
#define BCS_SDOT    sdot
#define BCS_SNRM2   snrm2
#define BCS_SROT    srot

#define BCS_DASUM   dasum
#define BCS_DAXPY   daxpy
#define BCS_DDOT    ddot
#define BCS_DNRM2   dnrm2
#define BCS_DROT    drot

// BLAS Level 2

#define BCS_SGEMV	sgemv
#define BCS_SGER	sger
#define BCS_SSYMV	ssymv

#define BCS_DGEMV	dgemv
#define BCS_DGER	dger
#define BCS_DSYMV	dsymv

// BLAS Level 3

#define BCS_SGEMM	sgemm
#define BCS_SSYMM	ssymm

#define BCS_DGEMM	dgemm
#define BCS_DSYMM	dsymm

extern "C"
{
	// BLAS Level 1

	float   BCS_SASUM(const int *n, const float *x, const int *incx);
	void    BCS_SAXPY(const int *n, const float *alpha, const float *x, const int *incx, float *y, const int *incy);
	float   BCS_SDOT(const int *n, const float *x, const int *incx, const float *y, const int *incy);
	float   BCS_SNRM2(const int *n, const float *x, const int *incx);
	void    BCS_SROT(const int *n, float *x, const int *incx, float *y, const int *incy, const float *c, const float *s);

	double  BCS_DASUM(const int *n, const double *x, const int *incx);
	void    BCS_DAXPY(const int *n, const double *alpha, const double *x, const int *incx, double *y, const int *incy);
	double  BCS_DDOT(const int *n, const double *x, const int *incx, const double *y, const int *incy);
	double  BCS_DNRM2(const int *n, const double *x, const int *incx);
	void    BCS_DROT(const int *n, double *x, const int *incx, double *y, const int *incy, const double *c, const double *s);

	// BLAS Level 2

	void BCS_SGEMV(const char *trans, const int *m, const int *n, const float *alpha,
	           	   const float *a, const int *lda, const float *x, const int *incx,
	           	   const float *beta, float *y, const int *incy);

	void BCS_SGER(const int *m, const int *n, const float *alpha, const float *x, const int *incx,
	          	  const float *y, const int *incy, float *a, const int *lda);

	void BCS_SSYMV(const char *uplo, const int *n, const float *alpha, const float *a, const int *lda,
	           	   const float *x, const int *incx, const float *beta, float *y, const int *incy);

	void BCS_DGEMV(const char *trans, const int *m, const int *n, const double *alpha,
	           	   const double *a, const int *lda, const double *x, const int *incx,
	           	   const double *beta, double *y, const int *incy);

	void BCS_DGER(const int *m, const int *n, const double *alpha, const double *x, const int *incx,
	          	  const double *y, const int *incy, double *a, const int *lda);

	void BCS_DSYMV(const char *uplo, const int *n, const double *alpha, const double *a, const int *lda,
	           	   const double *x, const int *incx, const double *beta, double *y, const int *incy);


	// BLAS Level 3

	void BCS_SGEMM(const char *transa, const char *transb, const int *m, const int *n, const int *k,
	           	   const float *alpha, const float *a, const int *lda, const float *b, const int *ldb,
	           	   const float *beta, float *c, const int *ldc);

	void BCS_SSYMM(const char *side, const char *uplo, const int *m, const int *n,
	           	   const float *alpha, const float *a, const int *lda, const float *b, const int *ldb,
	           	   const float *beta, float *c, const int *ldc);

	void BCS_DGEMM(const char *transa, const char *transb, const int *m, const int *n, const int *k,
	           	   const double *alpha, const double *a, const int *lda, const double *b, const int *ldb,
	           	   const double *beta, double *c, const int *ldc);

	void BCS_DSYMM(const char *side, const char *uplo, const int *m, const int *n,
	           	   const double *alpha, const double *a, const int *lda, const double *b, const int *ldb,
	           	   const double *beta, double *c, const int *ldc);
}

#endif 
