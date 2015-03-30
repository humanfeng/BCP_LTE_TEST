#ifndef _BCP_CRC_COMMON_H
#define _BCP_CRC_COMMON_H

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#if defined (_TMS320C6X)
#define INLINE static inline
#define RESTRICT restrict
#endif

#define MAX_UINT8 0xff

/****************************************************************************
 * Refer to spec bcp_crc_MicroArch_v1.0.0_20101130.doc                      *
 ****************************************************************************/
/* The cyclic generator polynomial for CRC-8.
 * x^8+x^7++x^4+x^3+x+1
 * x^7...x^0: 1001 1011
 */
#define POLYNOMIAL_CRC8     (0x9B000000)

/* The cyclic generator polynomial for CRC-12.
 * x^12+x^11+x^3+x^2+x+1
 * x^11...x^0: 1000 0000 1111
 */
#define POLYNOMIAL_CRC12    (0x80F00000)

/* The cyclic generator polynomial for CRC-16.
 * x^16+x^12+x^5+1
 * x^15...x^0: 1000 0000 0010 0001
 */
#define POLYNOMIAL_CRC16    (0x10210000)

/* The cyclic generator polynomial for CRC-16W.
 * x^16+x^15+x^2+1
 * x^15...x^0: 1000 0000 0000 0101
 */
#define POLYNOMIAL_CRC16W   (0x80050000)

/* The cyclic generator polynomial for CRC-24A.
 * x^24+x^23+x^18+x^17+x^14+x^11+x^10+x^7+x^6+x^5+x^4+x^3+x+1
 * x^23...x^0: 1000 0110 0100 1100 1111 1011
 */
#define POLYNOMIAL_CRC24A   (0x864CFB00)

/* The cyclic generator polynomial for CRC-24B.
 * x^24+x^23+x^6+x^5+x+1
 * x^23...x^0: 1000 0000 0000 0000 0110 0011
 */
#define POLYNOMIAL_CRC24B   (0x80006300)

#endif
