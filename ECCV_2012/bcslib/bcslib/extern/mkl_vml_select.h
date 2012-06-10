/**
 * @file mkl_vml_select.h
 *
 * A selected subset of MKL-VML functions
 * 
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_MKL_VML_SELECT_H_
#define BCSLIB_MKL_VML_SELECT_H_

#include <mkl_types.h>

#define _Vml_Api(rtype,name,arg) rtype name arg;

#ifdef __cplusplus
extern "C" {
#endif

	// Abs

	_Vml_Api(void,vsAbs,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAbs,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAbs,(const MKL_INT n,  const MKL_Complex8  a[], float  r[]))
	_Vml_Api(void,vzAbs,(const MKL_INT n,  const MKL_Complex16 a[], double r[]))

	// Sqr

	_Vml_Api(void,vsSqr,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdSqr,(const MKL_INT n,  const double a[], double r[]))

	// Sqrt

	_Vml_Api(void,vsSqrt,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdSqrt,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcSqrt,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzSqrt,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Inv

	_Vml_Api(void,vsInv,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdInv,(const MKL_INT n,  const double a[], double r[]))

	// InvSqrt

	_Vml_Api(void,vsInvSqrt,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdInvSqrt,(const MKL_INT n,  const double a[], double r[]))

	// Pow

	_Vml_Api(void,vsPow,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
	_Vml_Api(void,vdPow,(const MKL_INT n,  const double a[], const double b[], double r[]))
	_Vml_Api(void,vcPow,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
	_Vml_Api(void,vzPow,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

	// Powx

	_Vml_Api(void,vsPowx,(const MKL_INT n,  const float  a[], const float   b, float  r[]))
	_Vml_Api(void,vdPowx,(const MKL_INT n,  const double a[], const double  b, double r[]))
	_Vml_Api(void,vcPowx,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8   b, MKL_Complex8  r[]))
	_Vml_Api(void,vzPowx,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16  b, MKL_Complex16 r[]))


	// Exp

	_Vml_Api(void,vsExp,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdExp,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcExp,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzExp,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Expm1

	_Vml_Api(void,vsExpm1,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdExpm1,(const MKL_INT n,  const double a[], double r[]))

	// Ln

	_Vml_Api(void,vsLn,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdLn,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcLn,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzLn,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Log10

	_Vml_Api(void,vsLog10,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdLog10,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcLog10,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzLog10,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Log1p

	_Vml_Api(void,vsLog1p,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdLog1p,(const MKL_INT n,  const double a[], double r[]))



	// Ceil

	_Vml_Api(void,vsCeil,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdCeil,(const MKL_INT n,  const double a[], double r[]))

	// Floor

	_Vml_Api(void,vsFloor,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdFloor,(const MKL_INT n,  const double a[], double r[]))

	// Modf

	_Vml_Api(void,vsModf,(const MKL_INT n,  const float  a[], float  r1[], float  r2[]))
	_Vml_Api(void,vdModf,(const MKL_INT n,  const double a[], double r1[], double r2[]))

	// Round

	_Vml_Api(void,vsRound,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdRound,(const MKL_INT n,  const double a[], double r[]))

	// Trunc

	_Vml_Api(void,vsTrunc,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdTrunc,(const MKL_INT n,  const double a[], double r[]))


	// Sin

	_Vml_Api(void,vsSin,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdSin,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcSin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzSin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Cos

	_Vml_Api(void,vsCos,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdCos,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcCos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzCos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Tan

	_Vml_Api(void,vsTan,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdTan,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcTan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzTan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// SinCos

	_Vml_Api(void,vsSinCos,(const MKL_INT n,  const float  a[], float  r1[], float  r2[]))
	_Vml_Api(void,vdSinCos,(const MKL_INT n,  const double a[], double r1[], double r2[]))


	// Sinh

	_Vml_Api(void,vsSinh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdSinh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcSinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzSinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Cosh

	_Vml_Api(void,vsCosh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdCosh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcCosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzCosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Tanh

	_Vml_Api(void,vsTanh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdTanh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcTanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzTanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Asin

	_Vml_Api(void,vsAsin,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAsin,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAsin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAsin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Acos

	_Vml_Api(void,vsAcos,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAcos,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAcos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAcos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Atan

	_Vml_Api(void,vsAtan,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAtan,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAtan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAtan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Atan2

	_Vml_Api(void,vsAtan2,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
	_Vml_Api(void,vdAtan2,(const MKL_INT n,  const double a[], const double b[], double r[]))

	// Asinh

	_Vml_Api(void,vsAsinh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAsinh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAsinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAsinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Acosh

	_Vml_Api(void,vsAcosh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAcosh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAcosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAcosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Atanh

	_Vml_Api(void,vsAtanh,(const MKL_INT n,  const float  a[], float  r[]))
	_Vml_Api(void,vdAtanh,(const MKL_INT n,  const double a[], double r[]))
	_Vml_Api(void,vcAtanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
	_Vml_Api(void,vzAtanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

	// Hypot

	_Vml_Api(void,vsHypot,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
	_Vml_Api(void,vdHypot,(const MKL_INT n,  const double a[], const double b[], double r[]))

#ifdef __cplusplus
}  // end extern "C"
#endif


#endif 
