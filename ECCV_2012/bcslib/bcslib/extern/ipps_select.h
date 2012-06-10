/**
 * @file ipps_select.h
 *
 * A selected subset of Intel IPP Signal processing functions
 * 
 * Note: the function declarations used here are extracted from ipps.h
 * in Intel(R) Integrated Performance Primitives Signal Processing.
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef BCSLIB_IPPS_SELECT_H_
#define BCSLIB_IPPS_SELECT_H_

#include <ippversion.h>
#include <ippdefs.h>

#if (IPP_VERSION_MAJOR < 7)
#error The version of Intel IPP is required to be at least 7.0
#endif


#ifdef __cplusplus
extern "C" {
#endif

	/******************************************************
	 *
	 *  Vector Initialization
	 *
	 ******************************************************/

	// ippsCopy

	IPPAPI(IppStatus, ippsCopy_8u,( const Ipp8u* pSrc, Ipp8u* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_16s,( const Ipp16s* pSrc, Ipp16s* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_16sc,( const Ipp16sc* pSrc, Ipp16sc* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_32f,( const Ipp32f* pSrc, Ipp32f* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_32fc,( const Ipp32fc* pSrc, Ipp32fc* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_64f,( const Ipp64f* pSrc, Ipp64f* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_64fc,( const Ipp64fc* pSrc, Ipp64fc* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_32s,( const Ipp32s* pSrc, Ipp32s* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_32sc,( const Ipp32sc* pSrc, Ipp32sc* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_64s,( const Ipp64s* pSrc, Ipp64s* pDst, int len ))
	IPPAPI(IppStatus, ippsCopy_64sc,( const Ipp64sc* pSrc, Ipp64sc* pDst, int len ))

	// ippsZero

	IPPAPI ( IppStatus, ippsZero_8u,( Ipp8u* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_16s,( Ipp16s* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_16sc,( Ipp16sc* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_32f,( Ipp32f* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_32fc,( Ipp32fc* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_64f,( Ipp64f* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_64fc,( Ipp64fc* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_32s,( Ipp32s* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_32sc,( Ipp32sc* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_64s,( Ipp64s* pDst, int len ))
	IPPAPI ( IppStatus, ippsZero_64sc,( Ipp64sc* pDst, int len ))

	// ippsSet

	IPPAPI ( IppStatus, ippsSet_8u,( Ipp8u val, Ipp8u* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_16s,( Ipp16s val, Ipp16s* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_16sc,( Ipp16sc val, Ipp16sc* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_32s,( Ipp32s val, Ipp32s* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_32sc,( Ipp32sc val, Ipp32sc* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_32f,( Ipp32f val, Ipp32f* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_32fc,( Ipp32fc val, Ipp32fc* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_64s,( Ipp64s val, Ipp64s* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_64sc,( Ipp64sc val, Ipp64sc* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_64f,( Ipp64f val, Ipp64f* pDst, int len ))
	IPPAPI ( IppStatus, ippsSet_64fc,( Ipp64fc val, Ipp64fc* pDst, int len ))


	/******************************************************
	 *
	 *  Arithmetic and Elementary Functions
	 *
	 ******************************************************/


	// ippsAdd, Sub, Mul, Div

	IPPAPI(IppStatus, ippsAddC_32f,     (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsAddC_32fc,    (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsSubC_32f,     (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsSubC_32fc,    (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_32f,  (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_32fc, (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsMulC_32f,     (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsMulC_32fc,    (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsDivC_32f,     (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsDivC_32fc,    (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst, int len))

	IPPAPI(IppStatus, ippsAddC_64f,     (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsAddC_64fc,    (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsSubC_64f,     (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsSubC_64fc,    (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_64f,  (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_64fc, (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsMulC_64f,     (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsMulC_64fc,    (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsDivC_64f,     (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsDivC_64fc,    (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst, int len))

	IPPAPI(IppStatus, ippsAddC_32f_I,     (Ipp32f  val, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsAddC_32fc_I,    (Ipp32fc val, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubC_32f_I,     (Ipp32f  val, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubC_32fc_I,    (Ipp32fc val, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_32f_I,  (Ipp32f  val, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_32fc_I, (Ipp32fc val, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMulC_32f_I,     (Ipp32f  val, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsMulC_32fc_I,    (Ipp32fc val, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsDivC_32f_I,     (Ipp32f  val, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsDivC_32fc_I,    (Ipp32fc val, Ipp32fc* pSrcDst, int len))

	IPPAPI(IppStatus, ippsAddC_64f_I,     (Ipp64f  val, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsAddC_64fc_I,    (Ipp64fc val, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubC_64f_I,     (Ipp64f  val, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubC_64fc_I,    (Ipp64fc val, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_64f_I,  (Ipp64f  val, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSubCRev_64fc_I, (Ipp64fc val, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMulC_64f_I,     (Ipp64f  val, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsMulC_64fc_I,    (Ipp64fc val, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsDivC_64f_I,     (Ipp64f  val, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsDivC_64fc_I,    (Ipp64fc val, Ipp64fc* pSrcDst, int len))

	IPPAPI(IppStatus, ippsAdd_32f,    (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsAdd_32fc,   (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsSub_32f,    (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsSub_32fc,   (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsMul_32f,    (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsMul_32fc,   (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsDiv_32f,    (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsDiv_32fc,   (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst, int len))

	IPPAPI(IppStatus, ippsAdd_64f,    (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsAdd_64fc,   (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsSub_64f,    (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsSub_64fc,   (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsMul_64f,    (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsMul_64fc,   (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst, int len))
	IPPAPI(IppStatus, ippsDiv_64f,    (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsDiv_64fc,   (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst, int len))

	IPPAPI(IppStatus, ippsAdd_32f_I,  (const Ipp32f*  pSrc, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsAdd_32fc_I, (const Ipp32fc* pSrc, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSub_32f_I,  (const Ipp32f*  pSrc, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSub_32fc_I, (const Ipp32fc* pSrc, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMul_32f_I,  (const Ipp32f*  pSrc, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsMul_32fc_I, (const Ipp32fc* pSrc, Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsDiv_32f_I,  (const Ipp32f*  pSrc, Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsDiv_32fc_I, (const Ipp32fc* pSrc, Ipp32fc* pSrcDst, int len))

	IPPAPI(IppStatus, ippsAdd_64f_I,  (const Ipp64f*  pSrc, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsAdd_64fc_I, (const Ipp64fc* pSrc, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSub_64f_I,  (const Ipp64f*  pSrc, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSub_64fc_I, (const Ipp64fc* pSrc, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMul_64f_I,  (const Ipp64f*  pSrc, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsMul_64fc_I, (const Ipp64fc* pSrc, Ipp64fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsDiv_64f_I,  (const Ipp64f*  pSrc, Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsDiv_64fc_I, (const Ipp64fc* pSrc, Ipp64fc* pSrcDst, int len))

	// ippsSqr and ippsSqrt

	IPPAPI(IppStatus, ippsSqr_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsSqr_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsSqr_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsSqr_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))

	IPPAPI(IppStatus, ippsSqr_32f_I,  (Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqr_32fc_I, (Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqr_64f_I,  (Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqr_64fc_I, (Ipp64fc* pSrcDst, int len))

	IPPAPI(IppStatus, ippsSqrt_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int len))
	IPPAPI(IppStatus, ippsSqrt_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
	IPPAPI(IppStatus, ippsSqrt_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int len))
	IPPAPI(IppStatus, ippsSqrt_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))

	IPPAPI(IppStatus, ippsSqrt_32f_I,  (Ipp32f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqrt_32fc_I, (Ipp32fc* pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqrt_64f_I,  (Ipp64f*  pSrcDst, int len))
	IPPAPI(IppStatus, ippsSqrt_64fc_I, (Ipp64fc* pSrcDst, int len))

	// ippsAbs and ippsMagnitude

	IPPAPI(IppStatus, ippsAbs_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len))
	IPPAPI(IppStatus, ippsAbs_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int len))

	IPPAPI(IppStatus, ippsAbs_32f_I, (Ipp32f* pSrcDst, int len))
	IPPAPI(IppStatus, ippsAbs_64f_I, (Ipp64f* pSrcDst, int len))

	IPPAPI(IppStatus, ippsMagnitude_32fc, (const Ipp32fc* pSrc, Ipp32f* pDst, int len))
	IPPAPI(IppStatus, ippsMagnitude_64fc, (const Ipp64fc* pSrc, Ipp64f* pDst, int len))

	IPPAPI(IppStatus, ippsMagnitude_32f, (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDst, int len))
	IPPAPI(IppStatus, ippsMagnitude_64f, (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDst, int len))


	// ippsExp, ippsLn

	IPPAPI(IppStatus, ippsExp_32f,   (const Ipp32f* pSrc, Ipp32f* pDst, int len))
	IPPAPI(IppStatus, ippsExp_64f,   (const Ipp64f* pSrc, Ipp64f* pDst, int len))

	IPPAPI(IppStatus, ippsExp_32f_I, (Ipp32f* pSrcDst, int len))
	IPPAPI(IppStatus, ippsExp_64f_I, (Ipp64f* pSrcDst, int len))

	IPPAPI(IppStatus, ippsLn_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len))
	IPPAPI(IppStatus, ippsLn_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int len))

	IPPAPI(IppStatus, ippsLn_32f_I, (Ipp32f* pSrcDst, int len))
	IPPAPI(IppStatus, ippsLn_64f_I, (Ipp64f* pSrcDst, int len))

	// ippsMinEvery and ippsMaxEvery

	IPPAPI(IppStatus, ippsMinEvery_32f, (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, Ipp32u len))
	IPPAPI(IppStatus, ippsMaxEvery_32f, (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, Ipp32u len))
	IPPAPI(IppStatus, ippsMinEvery_64f, (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, Ipp32u len))
	IPPAPI(IppStatus, ippsMaxEvery_64f, (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, Ipp32u len))

	IPPAPI(IppStatus, ippsMinEvery_32f_I, (const Ipp32f* pSrc, Ipp32f* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMaxEvery_32f_I, (const Ipp32f* pSrc, Ipp32f* pSrcDst, int len))
	IPPAPI(IppStatus, ippsMinEvery_64f_I, (const Ipp64f* pSrc, Ipp64f* pSrcDst, Ipp32u len))
	IPPAPI(IppStatus, ippsMaxEvery_64f_I, (const Ipp64f* pSrc, Ipp64f* pSrcDst, Ipp32u len))


	// ippsThreshold

	IPPAPI(IppStatus,ippsThreshold_LT_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_LT_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int len, Ipp64f level))
	IPPAPI(IppStatus,ippsThreshold_LT_32f_I, (Ipp32f* pSrcDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_LT_64f_I, (Ipp64f* pSrcDst, int len, Ipp64f level))

	IPPAPI(IppStatus,ippsThreshold_GT_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_GT_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int len, Ipp64f level))
	IPPAPI(IppStatus,ippsThreshold_GT_32f_I, (Ipp32f* pSrcDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_GT_64f_I, (Ipp64f* pSrcDst, int len, Ipp64f level))

	IPPAPI(IppStatus,ippsThreshold_LTAbs_32f, (const Ipp32f* pSrc, Ipp32f *pDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_LTAbs_64f, (const Ipp64f* pSrc, Ipp64f *pDst, int len, Ipp64f level))
	IPPAPI(IppStatus,ippsThreshold_LTAbs_32f_I, (Ipp32f *pSrcDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_LTAbs_64f_I, (Ipp64f *pSrcDst, int len, Ipp64f level))

	IPPAPI(IppStatus,ippsThreshold_GTAbs_32f, (const Ipp32f* pSrc, Ipp32f *pDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_GTAbs_64f, (const Ipp64f* pSrc, Ipp64f *pDst, int len, Ipp64f level))
	IPPAPI(IppStatus,ippsThreshold_GTAbs_32f_I, (Ipp32f *pSrcDst, int len, Ipp32f level))
	IPPAPI(IppStatus,ippsThreshold_GTAbs_64f_I, (Ipp64f *pSrcDst, int len, Ipp64f level))


	/******************************************************
	 *
	 *  Vector Statistics Functions
	 *
	 ******************************************************/

	// ippsSum

	IPPAPI(IppStatus, ippsSum_32f,  (const Ipp32f*  pSrc,int len, Ipp32f*  pSum, IppHintAlgorithm hint))
	IPPAPI(IppStatus, ippsSum_32fc, (const Ipp32fc* pSrc,int len, Ipp32fc* pSum, IppHintAlgorithm hint))
	IPPAPI(IppStatus, ippsSum_64f,  (const Ipp64f*  pSrc,int len, Ipp64f*  pSum))
	IPPAPI(IppStatus, ippsSum_64fc, (const Ipp64fc* pSrc,int len, Ipp64fc* pSum))

	// ippsMean

	IPPAPI(IppStatus,ippsMean_32f,  (const Ipp32f*  pSrc,int len, Ipp32f*  pMean, IppHintAlgorithm hint))
	IPPAPI(IppStatus,ippsMean_32fc, (const Ipp32fc* pSrc,int len, Ipp32fc* pMean, IppHintAlgorithm hint))
	IPPAPI(IppStatus,ippsMean_64f,  (const Ipp64f*  pSrc,int len, Ipp64f*  pMean))
	IPPAPI(IppStatus,ippsMean_64fc, (const Ipp64fc* pSrc,int len, Ipp64fc* pMean))

	// ippsSumLn

	IPPAPI(IppStatus, ippsSumLn_32f, (const Ipp32f* pSrc, int len, Ipp32f* pSum))
	IPPAPI(IppStatus, ippsSumLn_64f, (const Ipp64f* pSrc, int len, Ipp64f* pSum))

	// ippsMax

	IPPAPI(IppStatus,ippsMax_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMax))
	IPPAPI(IppStatus,ippsMax_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMax))

	// ippsMin

	IPPAPI(IppStatus,ippsMin_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin))
	IPPAPI(IppStatus,ippsMin_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin))

	// ippsMaxIndx

	IPPAPI(IppStatus, ippsMaxIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMax, int* pIndx))
	IPPAPI(IppStatus, ippsMaxIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMax, int* pIndx))

	// ippsMinIdx

	IPPAPI(IppStatus, ippsMinIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin, int* pIndx))
	IPPAPI(IppStatus, ippsMinIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pIndx))

	// ippsMinMax

	IPPAPI(IppStatus, ippsMinMax_64f,(const Ipp64f* pSrc, int len, Ipp64f* pMin, Ipp64f* pMax))
	IPPAPI(IppStatus, ippsMinMax_32f,(const Ipp32f* pSrc, int len, Ipp32f* pMin, Ipp32f* pMax))

	// ippsDotProd

	IPPAPI(IppStatus, ippsDotProd_32f,     (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp32f*  pDp))
	IPPAPI(IppStatus, ippsDotProd_32fc,    (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp32fc* pDp))
	IPPAPI(IppStatus, ippsDotProd_32f32fc, (const Ipp32f*  pSrc1, const Ipp32fc* pSrc2, int len, Ipp32fc* pDp))

	IPPAPI(IppStatus, ippsDotProd_64f,     (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, int len, Ipp64f* pDp))
	IPPAPI(IppStatus, ippsDotProd_64fc,    (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64fc* pDp))
	IPPAPI(IppStatus, ippsDotProd_64f64fc, (const Ipp64f*  pSrc1, const Ipp64fc* pSrc2, int len, Ipp64fc* pDp))

	// ippsNorm

	IPPAPI(IppStatus, ippsNorm_Inf_32f, (const Ipp32f* pSrc, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNorm_Inf_64f, (const Ipp64f* pSrc, int len, Ipp64f* pNorm))

	IPPAPI(IppStatus, ippsNorm_L1_32f,  (const Ipp32f* pSrc, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNorm_L1_64f,  (const Ipp64f* pSrc, int len, Ipp64f* pNorm))

	IPPAPI(IppStatus, ippsNorm_L2_32f,  (const Ipp32f* pSrc, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNorm_L2_64f,  (const Ipp64f* pSrc, int len, Ipp64f* pNorm))

	// ippsNormDiff

	IPPAPI(IppStatus, ippsNormDiff_Inf_32f, (const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNormDiff_Inf_64f, (const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm))

	IPPAPI(IppStatus, ippsNormDiff_L1_32f,  (const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNormDiff_L1_64f,  (const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm))

	IPPAPI(IppStatus, ippsNormDiff_L2_32f,  (const Ipp32f* pSrc1, const Ipp32f* pSrc2, int len, Ipp32f* pNorm))
	IPPAPI(IppStatus, ippsNormDiff_L2_64f,  (const Ipp64f* pSrc1, const Ipp64f* pSrc2, int len, Ipp64f* pNorm))


#ifdef __cplusplus
}  // end extern "C"
#endif

#endif 


