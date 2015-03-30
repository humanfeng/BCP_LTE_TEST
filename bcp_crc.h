/**
 *  \file   bcp_crc.h
 *
 *  \brief   Header file for bcp_crc.c
 *
 *
 */
#ifndef _bcp_CRC_H
#define _bcp_CRC_H

#include "bcp_crc_common.h"

extern OUT uint32_t bcp_crcCodecC64pByte(
                    IN uint8_t  InputBytes[],
                    IN uint32_t NumInputBits,
                    IN uint32_t CrcPoly,
                    IN uint32_t CrcInitCond,
                    IN uint8_t  NumCrcBits);

extern OUT uint32_t bcp_crcCodecC64pShort(
                    IN uint8_t  InputBytes[],
                    IN uint32_t NumInputBits,
                    IN uint32_t CrcPoly,
                    IN uint32_t CrcInitCond,
                    IN uint8_t  NumCrcBits);

#endif

