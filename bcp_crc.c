/**
 *  \file   bcp_crc.c
 *
 *  \brief   Computes a CRC (Cyclic Redundancy Checking) value for an input buffer
 *
 *
 */

/* XDC types include */
#include <xdc/std.h>

#include "bcp_crc.h"

#ifdef _TMS320C6X
#include "c6x.h"
#elif TMS320C66X /* intrinsics specific */
/* These two lines are requred only for MSVC projects using TMS320C66X define.
   If the problem in intrinsics is fixed, these lines should go away.
*/
volatile uint32_t GPLYA;  /* GMPY Polynomial - A Side */
volatile uint32_t GPLYB;  /* GMPY Polynomial - B Side */
#endif


 *
 */
OUT uint32_t bcp_crcCodecC64pByte(
                    IN uint8_t InputBytes[],
                    IN uint32_t NumInputBits,
                    IN uint32_t CrcPoly,
                    IN uint32_t CrcInitCond,
                    IN uint8_t NumCrcBits )
{
    uint32_t NumBytes;
    uint8_t  NumBitsLeft;
    uint8_t  InputByte;
    uint32_t TmpByte1,TmpByte2;
    uint32_t CrcValue;
    uint32_t ByteCnt;

    NumBytes     = NumInputBits >>3;
    NumBitsLeft = NumInputBits & 7;

    GPLYA = CrcPoly;
    GPLYB = CrcPoly;

    /*   CRC initialization              
    *   bit 0 of CrcInitCond is delay 1 
    *   bit 1 of CrcInitCond is delay 2 
    *   etc                             
    */
    CrcValue = CrcInitCond;

    for ( ByteCnt = 0; ByteCnt < NumBytes; ByteCnt++ )
    {
        InputByte = InputBytes[ByteCnt];

        TmpByte1 = _gmpy(CrcPoly, InputByte);
        TmpByte2 = _gmpy(CrcValue, 1 << 8);

        CrcValue = TmpByte1 ^ TmpByte2;
    }

    /* process the last NumBitsLeft bits */
    if ( NumBitsLeft > 0 )
    {
        InputByte = InputBytes[ByteCnt] >> (8-NumBitsLeft);
        TmpByte1  = _gmpy(CrcPoly, InputByte);
        TmpByte2  = _gmpy(CrcValue, 1 << NumBitsLeft);
        CrcValue  = TmpByte1 ^ TmpByte2;
    }

    CrcValue >>= ( 32 - NumCrcBits );

    return(CrcValue);
} 


OUT uint32_t bcp_crcCodecC64pShort(
                    IN uint8_t InputBytes[],
                    IN uint32_t NumInputBits,
                    IN uint32_t CrcPoly,
                    IN uint32_t CrcInitCond,
                    IN uint8_t NumCrcBits )
{
    uint8_t  Byte_b0, Byte_b1;
    uint32_t Tmp_b0, Tmp_b1, Tmp_crc;
    uint32_t x8_sf;
    uint32_t CrcValue;
    uint32_t NumInputShorts, WordCnt;
    uint32_t NumNonWordBytes;
    uint8_t  NumBitsLeft;
    uint16_t InputWord, *pInputWords;


    /*  assign pointers */
    pInputWords = ( uint16_t * ) &InputBytes[0];

    NumInputShorts  = NumInputBits >>4;
    NumNonWordBytes = (NumInputBits &8) >>3;
    NumBitsLeft     = NumInputBits &7;

    GPLYA = CrcPoly;
    GPLYB = CrcPoly;

    /*   CRC initialization              
    *   bit 0 of CrcInitCond is delay 1 
    *   bit 1 of CrcInitCond is delay 2 
    *   etc                             
    */
    CrcValue = CrcInitCond;

    /*  compute the scale factors */
    x8_sf = _gmpy(CrcPoly, 1 << 8);


#ifdef _TMS320C6X
    #pragma MUST_ITERATE(2, ,);
#endif
    for( WordCnt = 0; WordCnt < NumInputShorts; WordCnt++ )
    {
        #ifdef _LITTLE_ENDIAN
        InputWord = *pInputWords++;
        #else
        InputWord = _swap4(*pInputWords++);
        #endif

        Tmp_crc = _gmpy(CrcValue, 1 << 8);
        Tmp_crc = _gmpy(Tmp_crc, 1 << 8);
        Byte_b0 = InputWord & MAX_UINT8;

        /* compute CRC contribution for the first byte, b0 */
        Tmp_b0 = _gmpy(x8_sf, Byte_b0);

        Byte_b1 = InputWord >> 8;
        /* compute CRC contribution for the second byte, b1 */
        Tmp_b1 = Tmp_b0 ^ _gmpy(CrcPoly, Byte_b1);

        /*  compute CRC contribution from the previous CRC value */
        CrcValue = Tmp_b1 ^ Tmp_crc;
    }

    if( NumNonWordBytes == 1 )
    {
        #ifdef _LITTLE_ENDIAN
        InputWord = *pInputWords++;
        #else
        InputWord = _swap4(*pInputWords++);
        #endif

        Byte_b0 = InputWord & MAX_UINT8;

        Tmp_b0 = _gmpy(CrcPoly, Byte_b0);
        Tmp_crc = _gmpy(CrcValue, 1 << 8);
        CrcValue = Tmp_crc ^ Tmp_b0;

		if( NumBitsLeft > 0 )
		{
			Byte_b1   = InputWord >> (16-NumBitsLeft);
            Tmp_b1    = _gmpy(CrcPoly, Byte_b1);
            Tmp_crc   = _gmpy(CrcValue, 1 << NumBitsLeft);
            CrcValue  = Tmp_crc ^ Tmp_b1;
		}
	}

    else if( NumBitsLeft > 0 )
    {
        #ifdef _BIG_ENDIAN
        InputWord = *pInputWords++;
        #else
        InputWord = _swap4(*pInputWords++);
        #endif

        Byte_b0   = InputWord >> (16-NumBitsLeft);

        Tmp_b0    = _gmpy(CrcPoly, Byte_b0);
        Tmp_crc   = _gmpy(CrcValue, 1 << NumBitsLeft);
        CrcValue  = Tmp_crc ^ Tmp_b0;
	}
    CrcValue >>= ( 32 - NumCrcBits );

    return(CrcValue);
} /* end of bcp_crcCodecC64pShort */


