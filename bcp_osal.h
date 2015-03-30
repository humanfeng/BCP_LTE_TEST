/**
 *   @file  bcp_osal.h
 *
 *   @brief   
 *      OS Adaptation Layer (OSAL) header file for BCP Test application. 
 *      Contains the BCP OSAL API prototype definitions.
 *
 *
 *  \par
 *  ============================================================================
 *
*/
#ifndef _BCP_OSAL_H_
#define _BCP_OSAL_H_

/* BCP Test application types include */
#include <bcp_types.h>

/* XDC/BIOS include */
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

extern Void*    Osal_biosMalloc (UInt32 num_bytes, Bool bGlobalAddress);
extern Void     Osal_biosFree (Void* dataPtr, UInt32 num_bytes, Bool bGlobalAddress);
extern Void     Osal_biosMultiCoreCsEnter ();
extern Void     Osal_biosMultiCoreCsExit ();
extern Void     Osal_biosInterruptCsEnter ();
extern Void     Osal_biosInterruptCsExit ();
extern Void     Osal_bcpBeginMemAccess (Void* pBlockPtr,UInt32 byteCnt);
extern Void     Osal_bcpEndMemAccess (Void* pBlockPtr,UInt32 byteCnt);
extern Void     Osal_bcpBeginDescMemAccess (Void* hRx, Void* pBlockPtr);

/* Map out all BCP OSAL APIs to BIOS implementations */
#define     Bcp_osalMalloc             Osal_biosMalloc
#define     Bcp_osalFree               Osal_biosFree
#define     Bcp_osalMultiCoreCsEnter   Osal_biosMultiCoreCsEnter
#define     Bcp_osalMultiCoreCsExit    Osal_biosMultiCoreCsExit
#define     Bcp_osalInterruptCsEnter   Osal_biosInterruptCsEnter
#define     Bcp_osalInterruptCsExit    Osal_biosInterruptCsExit
#define     Bcp_osalLog                System_printf
#define     Bcp_osalBeginMemAccess     Osal_bcpBeginMemAccess
#define     Bcp_osalEndMemAccess       Osal_bcpEndMemAccess
#define     Bcp_osalBeginDescMemAccess Osal_bcpBeginDescMemAccess

/* Map out all BCP Semaphore APIs to corresponding BIOS implementations */
#define     Bcp_osalCreateSem()        (Void *) Semaphore_create (0, NULL, NULL)
#define     Bcp_osalDeleteSem(X)       Semaphore_delete (X)
#define     Bcp_osalPendSem(X)         Semaphore_pend (X, BIOS_WAIT_FOREVER)
#define     Bcp_osalPostSem(X)         Semaphore_post (X)

#endif /* _BCP_OSAL_H_ */
