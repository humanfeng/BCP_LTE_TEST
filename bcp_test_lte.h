/** 
 *   @file  bcp_test_lte.h
 *
 *   @brief  
 *      Header file with data structures and definitions used by LTE tests.
 * 
 *  \par
 *  ============================================================================
*/
#ifndef _BCP_TEST_LTE_H_
#define _BCP_TEST_LTE_H_

/* LTE Test configuration definitions */

#define MAX_CODE_BLOCK_SIZE     6144
#define MAX_BLOCK_INDEX         189

/* LTE Channel types */
#define LTE_PDSCH               0
#define LTE_PDCCH               1
#define LTE_PUSCH_SIC           2
#define LTE_PUSCH               3
#define LTE_PUCCH               4
#define LTE_PDCCHM              5
#define LTE_PUSCH_SIC_HARD      6

typedef struct _BcpTest_LteCBParams
{
    UInt32       numCodeBks;
    UInt32       outputbitsNoFiller;
    UInt32       numCodeBksKp;
	UInt32       numCodeBksKm;
    UInt32       codeBkSizeKp;
	UInt32       codeBkSizeKm;
	UInt16       numFillerBits;
	UInt16       f1Km;
	UInt16       f2Km;
	UInt16       f1Kp;
	UInt16       f2Kp;
} BcpTest_LteCBParams;

typedef struct _BcpTest_RateMatchParams
{
    UInt32      E0;
    UInt32      E1;
    UInt32      Gamma;
	UInt32      NcbKm;
	UInt32      NcbKp;
	UInt32      rvKm;
	UInt32      rvKp;
	UInt32      rvKmCol;
	UInt32      rvKpCol;
	UInt32      NcbKmCol;
	UInt32      NcbKmRow;
	UInt32      NcbKpCol;
	UInt32      NcbKpRow;
} BcpTest_RateMatchParams;

#endif /* _BCP_TEST_LTE_H_ */
