// $Header: /DL_Projects/Utils/NewIso7816/Source/dl_type.h 1     4/11/11 15:24 Sean $

// Universal type definition file
// SK. 8/9/2006


#ifndef __DL_TYPE_H
#define __DL_TYPE_H

#define _PACKED_

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


typedef enum TagSbool {SECURE_ILLEGAL=0x0000, SECURE_FALSE=0x5aF0, SECURE_TRUE=0xa05F} sbool;

//#ifndef LOBYTE
//#define MAKEWORD(a, b)      ((u16)(((u8)(a)) | ((u16)((u8)(b))) << 8))
//#define MAKELONG(a, b)      ((u32)(((u16)(a)) | ((u32)((u16)(b))) << 16))
//#define LOBYTE(w)           ((u8)(w))
//#define HIBYTE(w)           ((u8)(((u16)(w) >> 8) & 0xFF))
//#define LOWORD(l)           ((u16)(u32)(l))
//#define HIWORD(l)           ((u16)((((u32)(l)) >> 16) & 0xFFFF))
//#endif // LOBYTE

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef offsetof
#define offsetof(s,m)       ((u16)&(((s *)0)->m))
#endif

#define NULLV   ((pvvoid)0)
#define NULLN   ((pnvoid)0)
#define NULLR   ((prvoid)0)
#define NULLG   ((pgvoid)0)


#define GENERICPOINTER      *     // generic pointer
#define RAMPOINTER          *     // pointer to RAM
#define ROMPOINTER          const *     //            ROM/DATA
#define NVMPOINTER          *     //            NVM/DATA
#define CODEPOINTER         *     //            CODE/FUNCTION


typedef                  void     GENERICPOINTER   pgvoid;
typedef                                            pgvoid   GENERICPOINTER   pgpgvoid;
typedef                                            pgvoid   RAMPOINTER       pvpgvoid;
typedef                                            pgvoid   ROMPOINTER       prpgvoid;
typedef                                            pgvoid   NVMPOINTER       pnpgvoid;
typedef                  void     RAMPOINTER       pvvoid;
typedef                                            pvvoid   GENERICPOINTER   pgpvvoid;
typedef                                            pvvoid   RAMPOINTER       pvpvvoid;
typedef                                            pvvoid   ROMPOINTER       prpvvoid;
typedef                                            pvvoid   NVMPOINTER       pnpvvoid;
typedef                  void     ROMPOINTER       prvoid;
typedef                                            prvoid   GENERICPOINTER   pgprvoid;
typedef                                            prvoid   RAMPOINTER       pvprvoid;
typedef                                            prvoid   ROMPOINTER       prprvoid;
typedef                                            prvoid   NVMPOINTER       pnprvoid;
typedef                  void     NVMPOINTER       pnvoid;
typedef                                            pnvoid   GENERICPOINTER   pgpnvoid;
typedef                                            pnvoid   RAMPOINTER       pvpnvoid;
typedef                                            pnvoid   ROMPOINTER       prpnvoid;
typedef                                            pnvoid   NVMPOINTER       pnpnvoid;

typedef unsigned char    flag;
typedef                  flag     GENERICPOINTER   pgflag;
typedef                                            pgflag   GENERICPOINTER   pgpgflag;
typedef                                            pgflag   RAMPOINTER       pvpgflag;
typedef                                            pgflag   ROMPOINTER       prpgflag;
typedef                                            pgflag   NVMPOINTER       pnpgflag;
typedef                  flag     RAMPOINTER       pvflag;
typedef                                            pvflag   GENERICPOINTER   pgpvflag;
typedef                                            pvflag   RAMPOINTER       pvpvflag;
typedef                                            pvflag   ROMPOINTER       prpvflag;
typedef                                            pvflag   NVMPOINTER       pnpvflag;
typedef                  flag     ROMPOINTER       prflag;
typedef                                            prflag   GENERICPOINTER   pgprflag;
typedef                                            prflag   RAMPOINTER       pvprflag;
typedef                                            prflag   ROMPOINTER       prprflag;
typedef                                            prflag   NVMPOINTER       pnprflag;
typedef                  flag     NVMPOINTER       pnflag;
typedef                                            pnflag   GENERICPOINTER   pgpnflag;
typedef                                            pnflag   RAMPOINTER       pvpnflag;
typedef                                            pnflag   ROMPOINTER       prpnflag;
typedef                                            pnflag   NVMPOINTER       pnpnflag;

typedef signed   char    s8;
typedef                  s8       GENERICPOINTER   pgs8;
typedef                                            pgs8     GENERICPOINTER   pgpgs8;
typedef                                            pgs8     RAMPOINTER       pvpgs8;
typedef                                            pgs8     ROMPOINTER       prpgs8;
typedef                                            pgs8     NVMPOINTER       pnpgs8;
typedef                  s8       RAMPOINTER       pvs8;
typedef                                            pvs8     GENERICPOINTER   pgpvs8;
typedef                                            pvs8     RAMPOINTER       pvpvs8;
typedef                                            pvs8     ROMPOINTER       prpvs8;
typedef                                            pvs8     NVMPOINTER       pnpvs8;
typedef                  s8       ROMPOINTER       prs8;
typedef                                            prs8     GENERICPOINTER   pgprs8;
typedef                                            prs8     RAMPOINTER       pvprs8;
typedef                                            prs8     ROMPOINTER       prprs8;
typedef                                            prs8     NVMPOINTER       pnprs8;
typedef                  s8       NVMPOINTER       pns8;
typedef                                            pns8     GENERICPOINTER   pgpns8;
typedef                                            pns8     RAMPOINTER       pvpns8;
typedef                                            pns8     ROMPOINTER       prpns8;
typedef                                            pns8     NVMPOINTER       pnpns8;

typedef unsigned char    u8;
typedef                  u8       GENERICPOINTER   pgu8;
typedef                                            pgu8     GENERICPOINTER   pgpgu8;
typedef                                            pgu8     RAMPOINTER       pvpgu8;
typedef                                            pgu8     ROMPOINTER       prpgu8;
typedef                                            pgu8     NVMPOINTER       pnpgu8;
typedef                  u8       RAMPOINTER       pvu8;
typedef                                            pvu8     GENERICPOINTER   pgpvu8;
typedef                                            pvu8     RAMPOINTER       pvpvu8;
typedef                                            pvu8     ROMPOINTER       prpvu8;
typedef                                            pvu8     NVMPOINTER       pnpvu8;
typedef                  u8       ROMPOINTER       pru8;
typedef                                            pru8     GENERICPOINTER   pgpru8;
typedef                                            pru8     RAMPOINTER       pvpru8;
typedef                                            pru8     ROMPOINTER       prpru8;
typedef                                            pru8     NVMPOINTER       pnpru8;
typedef                  u8       NVMPOINTER       pnu8;
typedef                                            pnu8     GENERICPOINTER   pgpnu8;
typedef                                            pnu8     RAMPOINTER       pvpnu8;
typedef                                            pnu8     ROMPOINTER       prpnu8;
typedef                                            pnu8     NVMPOINTER       pnpnu8;

typedef signed   short   s16;
typedef                  s16      GENERICPOINTER   pgs16;
typedef                                            pgs16    GENERICPOINTER   pgpgs16;
typedef                                            pgs16    RAMPOINTER       pvpgs16;
typedef                                            pgs16    ROMPOINTER       prpgs16;
typedef                                            pgs16    NVMPOINTER       pnpgs16;
typedef                  s16      RAMPOINTER       pvs16;
typedef                                            pvs16    GENERICPOINTER   pgpvs16;
typedef                                            pvs16    RAMPOINTER       pvpvs16;
typedef                                            pvs16    ROMPOINTER       prpvs16;
typedef                                            pvs16    NVMPOINTER       pnpvs16;
typedef                  s16      ROMPOINTER       prs16;
typedef                                            prs16    GENERICPOINTER   pgprs16;
typedef                                            prs16    RAMPOINTER       pvprs16;
typedef                                            prs16    ROMPOINTER       prprs16;
typedef                                            prs16    NVMPOINTER       pnprs16;
typedef                  s16      NVMPOINTER       pns16;
typedef                                            pns16    GENERICPOINTER   pgpns16;
typedef                                            pns16    RAMPOINTER       pvpns16;
typedef                                            pns16    ROMPOINTER       prpns16;
typedef                                            pns16    NVMPOINTER       pnpns16;

typedef unsigned short   u16;
typedef                  u16      GENERICPOINTER   pgu16;
typedef                                            pgu16    GENERICPOINTER   pgpgu16;
typedef                                            pgu16    RAMPOINTER       pvpgu16;
typedef                                            pgu16    ROMPOINTER       prpgu16;
typedef                                            pgu16    NVMPOINTER       pnpgu16;
typedef                  u16      RAMPOINTER       pvu16;
typedef                                            pvu16    GENERICPOINTER   pgpvu16;
typedef                                            pvu16    RAMPOINTER       pvpvu16;
typedef                                            pvu16    ROMPOINTER       prpvu16;
typedef                                            pvu16    NVMPOINTER       pnpvu16;
typedef                  u16      ROMPOINTER       pru16;
typedef                                            pru16    GENERICPOINTER   pgpru16;
typedef                                            pru16    RAMPOINTER       pvpru16;
typedef                                            pru16    ROMPOINTER       prpru16;
typedef                                            pru16    NVMPOINTER       pnpru16;
typedef                  u16      NVMPOINTER       pnu16;
typedef                                            pnu16    GENERICPOINTER   pgpnu16;
typedef                                            pnu16    RAMPOINTER       pvpnu16;
typedef                                            pnu16    ROMPOINTER       prpnu16;
typedef                                            pnu16    NVMPOINTER       pnpnu16;

typedef signed   long    s32;
typedef                  s32      GENERICPOINTER   pgs32;
typedef                                            pgs32    GENERICPOINTER   pgpgs32;
typedef                                            pgs32    RAMPOINTER       pvpgs32;
typedef                                            pgs32    ROMPOINTER       prpgs32;
typedef                                            pgs32    NVMPOINTER       pnpgs32;
typedef                  s32      RAMPOINTER       pvs32;
typedef                                            pvs32    GENERICPOINTER   pgpvs32;
typedef                                            pvs32    RAMPOINTER       pvpvs32;
typedef                                            pvs32    ROMPOINTER       prpvs32;
typedef                                            pvs32    NVMPOINTER       pnpvs32;
typedef                  s32      ROMPOINTER       prs32;
typedef                                            prs32    GENERICPOINTER   pgprs32;
typedef                                            prs32    RAMPOINTER       pvprs32;
typedef                                            prs32    ROMPOINTER       prprs32;
typedef                                            prs32    NVMPOINTER       pnprs32;
typedef                  s32      NVMPOINTER       pns32;
typedef                                            pns32    GENERICPOINTER   pgpns32;
typedef                                            pns32    RAMPOINTER       pvpns32;
typedef                                            pns32    ROMPOINTER       prpns32;
typedef                                            pns32    NVMPOINTER       pnpns32;

typedef unsigned long    u32;
typedef                  u32      GENERICPOINTER   pgu32;
typedef                                            pgu32    GENERICPOINTER   pgpgu32;
typedef                                            pgu32    RAMPOINTER       pvpgu32;
typedef                                            pgu32    ROMPOINTER       prpgu32;
typedef                                            pgu32    NVMPOINTER       pnpgu32;
typedef                  u32      RAMPOINTER       pvu32;
typedef                                            pvu32    GENERICPOINTER   pgpvu32;
typedef                                            pvu32    RAMPOINTER       pvpvu32;
typedef                                            pvu32    ROMPOINTER       prpvu32;
typedef                                            pvu32    NVMPOINTER       pnpvu32;
typedef                  u32      ROMPOINTER       pru32;
typedef                                            pru32    GENERICPOINTER   pgpru32;
typedef                                            pru32    RAMPOINTER       pvpru32;
typedef                                            pru32    ROMPOINTER       prpru32;
typedef                                            pru32    NVMPOINTER       pnpru32;
typedef                  u32      NVMPOINTER       pnu32;
typedef                                            pnu32    GENERICPOINTER   pgpnu32;
typedef                                            pnu32    RAMPOINTER       pvpnu32;
typedef                                            pnu32    ROMPOINTER       prpnu32;
typedef                                            pnu32    NVMPOINTER       pnpnu32;

// ############################################################
// # Use the following defines to selectively include the     #
// # appropriate pointers to function types.                  #
// ############################################################

typedef flag       (CODEPOINTER pxflag_u16u16u16pgu8)(u16, u16, u16, pgu8);
typedef u16        (CODEPOINTER pxu16_u16u16u16pgu8) (u16, u16, u16, pgu8);

typedef pgu8       (CODEPOINTER pxpgu8_pgu8u16)(pgu8, u16);
typedef u16        (CODEPOINTER pxu16_pgu8u16)(pgu8, u16);
typedef u16        (CODEPOINTER pxu16_pgu8u16u8)(pgu8, u16, u8);
typedef u16        (CODEPOINTER pxu16_pgu8pgu16)(pgu8, pgu16);
typedef void       (CODEPOINTER pxvoid_pvu8pvu8)(pvu8, pvu8);
typedef void       (CODEPOINTER pxvoid_pnu8pvu8)(pnu8, pvu8);
typedef void       (CODEPOINTER pxvoid_pgu8pvu8)(pgu8, pvu8);


#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_void
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgvoid
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvvoid
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prvoid
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnvoid
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_flag
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgflag
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvflag
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prflag
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnflag
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns8
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u8
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru8
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu8
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns16
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru16
#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu16
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru32
//#define __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu32


#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_void                      // void Fn(arg)
typedef void       (CODEPOINTER pxvoid_void)(void);
typedef void       (CODEPOINTER pxvoid_pgvoid)(pgvoid);
typedef void       (CODEPOINTER pxvoid_pvvoid)(pvvoid);
typedef void       (CODEPOINTER pxvoid_prvoid)(prvoid);
typedef void       (CODEPOINTER pxvoid_pnvoid)(pnvoid);
typedef void       (CODEPOINTER pxvoid_flag)(flag);
typedef void       (CODEPOINTER pxvoid_pgflag)(pgflag);
typedef void       (CODEPOINTER pxvoid_pvflag)(pvflag);
typedef void       (CODEPOINTER pxvoid_prflag)(prflag);
typedef void       (CODEPOINTER pxvoid_pnflag)(pnflag);
typedef void       (CODEPOINTER pxvoid_s8)(s8);
typedef void       (CODEPOINTER pxvoid_pgs8)(pgs8);
typedef void       (CODEPOINTER pxvoid_pvs8)(pvs8);
typedef void       (CODEPOINTER pxvoid_prs8)(prs8);
typedef void       (CODEPOINTER pxvoid_pns8)(pns8);
typedef void       (CODEPOINTER pxvoid_u8)(u8);
typedef void       (CODEPOINTER pxvoid_pgu8)(pgu8);
typedef void       (CODEPOINTER pxvoid_pvu8)(pvu8);
typedef void       (CODEPOINTER pxvoid_pru8)(pru8);
typedef void       (CODEPOINTER pxvoid_pnu8)(pnu8);
typedef void       (CODEPOINTER pxvoid_s16)(s16);
typedef void       (CODEPOINTER pxvoid_pgs16)(pgs16);
typedef void       (CODEPOINTER pxvoid_pvs16)(pvs16);
typedef void       (CODEPOINTER pxvoid_prs16)(prs16);
typedef void       (CODEPOINTER pxvoid_pns16)(pns16);
typedef void       (CODEPOINTER pxvoid_u16)(u16);
typedef void       (CODEPOINTER pxvoid_pgu16)(pgu16);
typedef void       (CODEPOINTER pxvoid_pvu16)(pvu16);
typedef void       (CODEPOINTER pxvoid_pru16)(pru16);
typedef void       (CODEPOINTER pxvoid_pnu16)(pnu16);
typedef void       (CODEPOINTER pxvoid_s32)(s32);
typedef void       (CODEPOINTER pxvoid_pgs32)(pgs32);
typedef void       (CODEPOINTER pxvoid_pvs32)(pvs32);
typedef void       (CODEPOINTER pxvoid_prs32)(prs32);
typedef void       (CODEPOINTER pxvoid_pns32)(pns32);
typedef void       (CODEPOINTER pxvoid_u32)(u32);
typedef void       (CODEPOINTER pxvoid_pgu32)(pgu32);
typedef void       (CODEPOINTER pxvoid_pvu32)(pvu32);
typedef void       (CODEPOINTER pxvoid_pru32)(pru32);
typedef void       (CODEPOINTER pxvoid_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_void

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgvoid                      // pgvoid Fn(arg)
typedef pgvoid     (CODEPOINTER pxpgvoid_void)(void);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgvoid)(pgvoid);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvvoid)(pvvoid);
typedef pgvoid     (CODEPOINTER pxpgvoid_prvoid)(prvoid);
typedef pgvoid     (CODEPOINTER pxpgvoid_pnvoid)(pnvoid);
typedef pgvoid     (CODEPOINTER pxpgvoid_flag)(flag);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgflag)(pgflag);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvflag)(pvflag);
typedef pgvoid     (CODEPOINTER pxpgvoid_prflag)(prflag);
typedef pgvoid     (CODEPOINTER pxpgvoid_pnflag)(pnflag);
typedef pgvoid     (CODEPOINTER pxpgvoid_s8)(s8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgs8)(pgs8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvs8)(pvs8);
typedef pgvoid     (CODEPOINTER pxpgvoid_prs8)(prs8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pns8)(pns8);
typedef pgvoid     (CODEPOINTER pxpgvoid_u8)(u8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgu8)(pgu8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvu8)(pvu8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pru8)(pru8);
typedef pgvoid     (CODEPOINTER pxpgvoid_pnu8)(pnu8);
typedef pgvoid     (CODEPOINTER pxpgvoid_s16)(s16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgs16)(pgs16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvs16)(pvs16);
typedef pgvoid     (CODEPOINTER pxpgvoid_prs16)(prs16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pns16)(pns16);
typedef pgvoid     (CODEPOINTER pxpgvoid_u16)(u16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgu16)(pgu16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvu16)(pvu16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pru16)(pru16);
typedef pgvoid     (CODEPOINTER pxpgvoid_pnu16)(pnu16);
typedef pgvoid     (CODEPOINTER pxpgvoid_s32)(s32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgs32)(pgs32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvs32)(pvs32);
typedef pgvoid     (CODEPOINTER pxpgvoid_prs32)(prs32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pns32)(pns32);
typedef pgvoid     (CODEPOINTER pxpgvoid_u32)(u32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pgu32)(pgu32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pvu32)(pvu32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pru32)(pru32);
typedef pgvoid     (CODEPOINTER pxpgvoid_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgvoid

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvvoid                      // pvvoid Fn(arg)
typedef pvvoid     (CODEPOINTER pxpvvoid_void)(void);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgvoid)(pgvoid);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvvoid)(pvvoid);
typedef pvvoid     (CODEPOINTER pxpvvoid_prvoid)(prvoid);
typedef pvvoid     (CODEPOINTER pxpvvoid_pnvoid)(pnvoid);
typedef pvvoid     (CODEPOINTER pxpvvoid_flag)(flag);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgflag)(pgflag);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvflag)(pvflag);
typedef pvvoid     (CODEPOINTER pxpvvoid_prflag)(prflag);
typedef pvvoid     (CODEPOINTER pxpvvoid_pnflag)(pnflag);
typedef pvvoid     (CODEPOINTER pxpvvoid_s8)(s8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgs8)(pgs8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvs8)(pvs8);
typedef pvvoid     (CODEPOINTER pxpvvoid_prs8)(prs8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pns8)(pns8);
typedef pvvoid     (CODEPOINTER pxpvvoid_u8)(u8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgu8)(pgu8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvu8)(pvu8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pru8)(pru8);
typedef pvvoid     (CODEPOINTER pxpvvoid_pnu8)(pnu8);
typedef pvvoid     (CODEPOINTER pxpvvoid_s16)(s16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgs16)(pgs16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvs16)(pvs16);
typedef pvvoid     (CODEPOINTER pxpvvoid_prs16)(prs16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pns16)(pns16);
typedef pvvoid     (CODEPOINTER pxpvvoid_u16)(u16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgu16)(pgu16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvu16)(pvu16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pru16)(pru16);
typedef pvvoid     (CODEPOINTER pxpvvoid_pnu16)(pnu16);
typedef pvvoid     (CODEPOINTER pxpvvoid_s32)(s32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgs32)(pgs32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvs32)(pvs32);
typedef pvvoid     (CODEPOINTER pxpvvoid_prs32)(prs32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pns32)(pns32);
typedef pvvoid     (CODEPOINTER pxpvvoid_u32)(u32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pgu32)(pgu32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pvu32)(pvu32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pru32)(pru32);
typedef pvvoid     (CODEPOINTER pxpvvoid_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvvoid

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prvoid                      // prvoid Fn(arg)
typedef prvoid     (CODEPOINTER pxprvoid_void)(void);
typedef prvoid     (CODEPOINTER pxprvoid_pgvoid)(pgvoid);
typedef prvoid     (CODEPOINTER pxprvoid_pvvoid)(pvvoid);
typedef prvoid     (CODEPOINTER pxprvoid_prvoid)(prvoid);
typedef prvoid     (CODEPOINTER pxprvoid_pnvoid)(pnvoid);
typedef prvoid     (CODEPOINTER pxprvoid_flag)(flag);
typedef prvoid     (CODEPOINTER pxprvoid_pgflag)(pgflag);
typedef prvoid     (CODEPOINTER pxprvoid_pvflag)(pvflag);
typedef prvoid     (CODEPOINTER pxprvoid_prflag)(prflag);
typedef prvoid     (CODEPOINTER pxprvoid_pnflag)(pnflag);
typedef prvoid     (CODEPOINTER pxprvoid_s8)(s8);
typedef prvoid     (CODEPOINTER pxprvoid_pgs8)(pgs8);
typedef prvoid     (CODEPOINTER pxprvoid_pvs8)(pvs8);
typedef prvoid     (CODEPOINTER pxprvoid_prs8)(prs8);
typedef prvoid     (CODEPOINTER pxprvoid_pns8)(pns8);
typedef prvoid     (CODEPOINTER pxprvoid_u8)(u8);
typedef prvoid     (CODEPOINTER pxprvoid_pgu8)(pgu8);
typedef prvoid     (CODEPOINTER pxprvoid_pvu8)(pvu8);
typedef prvoid     (CODEPOINTER pxprvoid_pru8)(pru8);
typedef prvoid     (CODEPOINTER pxprvoid_pnu8)(pnu8);
typedef prvoid     (CODEPOINTER pxprvoid_s16)(s16);
typedef prvoid     (CODEPOINTER pxprvoid_pgs16)(pgs16);
typedef prvoid     (CODEPOINTER pxprvoid_pvs16)(pvs16);
typedef prvoid     (CODEPOINTER pxprvoid_prs16)(prs16);
typedef prvoid     (CODEPOINTER pxprvoid_pns16)(pns16);
typedef prvoid     (CODEPOINTER pxprvoid_u16)(u16);
typedef prvoid     (CODEPOINTER pxprvoid_pgu16)(pgu16);
typedef prvoid     (CODEPOINTER pxprvoid_pvu16)(pvu16);
typedef prvoid     (CODEPOINTER pxprvoid_pru16)(pru16);
typedef prvoid     (CODEPOINTER pxprvoid_pnu16)(pnu16);
typedef prvoid     (CODEPOINTER pxprvoid_s32)(s32);
typedef prvoid     (CODEPOINTER pxprvoid_pgs32)(pgs32);
typedef prvoid     (CODEPOINTER pxprvoid_pvs32)(pvs32);
typedef prvoid     (CODEPOINTER pxprvoid_prs32)(prs32);
typedef prvoid     (CODEPOINTER pxprvoid_pns32)(pns32);
typedef prvoid     (CODEPOINTER pxprvoid_u32)(u32);
typedef prvoid     (CODEPOINTER pxprvoid_pgu32)(pgu32);
typedef prvoid     (CODEPOINTER pxprvoid_pvu32)(pvu32);
typedef prvoid     (CODEPOINTER pxprvoid_pru32)(pru32);
typedef prvoid     (CODEPOINTER pxprvoid_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prvoid

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnvoid                      // pnvoid Fn(arg)
typedef pnvoid     (CODEPOINTER pxpnvoid_void)(void);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgvoid)(pgvoid);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvvoid)(pvvoid);
typedef pnvoid     (CODEPOINTER pxpnvoid_prvoid)(prvoid);
typedef pnvoid     (CODEPOINTER pxpnvoid_pnvoid)(pnvoid);
typedef pnvoid     (CODEPOINTER pxpnvoid_flag)(flag);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgflag)(pgflag);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvflag)(pvflag);
typedef pnvoid     (CODEPOINTER pxpnvoid_prflag)(prflag);
typedef pnvoid     (CODEPOINTER pxpnvoid_pnflag)(pnflag);
typedef pnvoid     (CODEPOINTER pxpnvoid_s8)(s8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgs8)(pgs8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvs8)(pvs8);
typedef pnvoid     (CODEPOINTER pxpnvoid_prs8)(prs8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pns8)(pns8);
typedef pnvoid     (CODEPOINTER pxpnvoid_u8)(u8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgu8)(pgu8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvu8)(pvu8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pru8)(pru8);
typedef pnvoid     (CODEPOINTER pxpnvoid_pnu8)(pnu8);
typedef pnvoid     (CODEPOINTER pxpnvoid_s16)(s16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgs16)(pgs16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvs16)(pvs16);
typedef pnvoid     (CODEPOINTER pxpnvoid_prs16)(prs16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pns16)(pns16);
typedef pnvoid     (CODEPOINTER pxpnvoid_u16)(u16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgu16)(pgu16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvu16)(pvu16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pru16)(pru16);
typedef pnvoid     (CODEPOINTER pxpnvoid_pnu16)(pnu16);
typedef pnvoid     (CODEPOINTER pxpnvoid_s32)(s32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgs32)(pgs32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvs32)(pvs32);
typedef pnvoid     (CODEPOINTER pxpnvoid_prs32)(prs32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pns32)(pns32);
typedef pnvoid     (CODEPOINTER pxpnvoid_u32)(u32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pgu32)(pgu32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pvu32)(pvu32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pru32)(pru32);
typedef pnvoid     (CODEPOINTER pxpnvoid_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnvoid

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_flag                      // flag Fn(arg)
typedef flag       (CODEPOINTER pxflag_void)(void);
typedef flag       (CODEPOINTER pxflag_pgvoid)(pgvoid);
typedef flag       (CODEPOINTER pxflag_pvvoid)(pvvoid);
typedef flag       (CODEPOINTER pxflag_prvoid)(prvoid);
typedef flag       (CODEPOINTER pxflag_pnvoid)(pnvoid);
typedef flag       (CODEPOINTER pxflag_flag)(flag);
typedef flag       (CODEPOINTER pxflag_pgflag)(pgflag);
typedef flag       (CODEPOINTER pxflag_pvflag)(pvflag);
typedef flag       (CODEPOINTER pxflag_prflag)(prflag);
typedef flag       (CODEPOINTER pxflag_pnflag)(pnflag);
typedef flag       (CODEPOINTER pxflag_s8)(s8);
typedef flag       (CODEPOINTER pxflag_pgs8)(pgs8);
typedef flag       (CODEPOINTER pxflag_pvs8)(pvs8);
typedef flag       (CODEPOINTER pxflag_prs8)(prs8);
typedef flag       (CODEPOINTER pxflag_pns8)(pns8);
typedef flag       (CODEPOINTER pxflag_u8)(u8);
typedef flag       (CODEPOINTER pxflag_pgu8)(pgu8);
typedef flag       (CODEPOINTER pxflag_pvu8)(pvu8);
typedef flag       (CODEPOINTER pxflag_pru8)(pru8);
typedef flag       (CODEPOINTER pxflag_pnu8)(pnu8);
typedef flag       (CODEPOINTER pxflag_s16)(s16);
typedef flag       (CODEPOINTER pxflag_pgs16)(pgs16);
typedef flag       (CODEPOINTER pxflag_pvs16)(pvs16);
typedef flag       (CODEPOINTER pxflag_prs16)(prs16);
typedef flag       (CODEPOINTER pxflag_pns16)(pns16);
typedef flag       (CODEPOINTER pxflag_u16)(u16);
typedef flag       (CODEPOINTER pxflag_pgu16)(pgu16);
typedef flag       (CODEPOINTER pxflag_pvu16)(pvu16);
typedef flag       (CODEPOINTER pxflag_pru16)(pru16);
typedef flag       (CODEPOINTER pxflag_pnu16)(pnu16);
typedef flag       (CODEPOINTER pxflag_s32)(s32);
typedef flag       (CODEPOINTER pxflag_pgs32)(pgs32);
typedef flag       (CODEPOINTER pxflag_pvs32)(pvs32);
typedef flag       (CODEPOINTER pxflag_prs32)(prs32);
typedef flag       (CODEPOINTER pxflag_pns32)(pns32);
typedef flag       (CODEPOINTER pxflag_u32)(u32);
typedef flag       (CODEPOINTER pxflag_pgu32)(pgu32);
typedef flag       (CODEPOINTER pxflag_pvu32)(pvu32);
typedef flag       (CODEPOINTER pxflag_pru32)(pru32);
typedef flag       (CODEPOINTER pxflag_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_flag

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgflag                      // pgflag Fn(arg)
typedef pgflag     (CODEPOINTER pxpgflag_void)(void);
typedef pgflag     (CODEPOINTER pxpgflag_pgvoid)(pgvoid);
typedef pgflag     (CODEPOINTER pxpgflag_pvvoid)(pvvoid);
typedef pgflag     (CODEPOINTER pxpgflag_prvoid)(prvoid);
typedef pgflag     (CODEPOINTER pxpgflag_pnvoid)(pnvoid);
typedef pgflag     (CODEPOINTER pxpgflag_flag)(flag);
typedef pgflag     (CODEPOINTER pxpgflag_pgflag)(pgflag);
typedef pgflag     (CODEPOINTER pxpgflag_pvflag)(pvflag);
typedef pgflag     (CODEPOINTER pxpgflag_prflag)(prflag);
typedef pgflag     (CODEPOINTER pxpgflag_pnflag)(pnflag);
typedef pgflag     (CODEPOINTER pxpgflag_s8)(s8);
typedef pgflag     (CODEPOINTER pxpgflag_pgs8)(pgs8);
typedef pgflag     (CODEPOINTER pxpgflag_pvs8)(pvs8);
typedef pgflag     (CODEPOINTER pxpgflag_prs8)(prs8);
typedef pgflag     (CODEPOINTER pxpgflag_pns8)(pns8);
typedef pgflag     (CODEPOINTER pxpgflag_u8)(u8);
typedef pgflag     (CODEPOINTER pxpgflag_pgu8)(pgu8);
typedef pgflag     (CODEPOINTER pxpgflag_pvu8)(pvu8);
typedef pgflag     (CODEPOINTER pxpgflag_pru8)(pru8);
typedef pgflag     (CODEPOINTER pxpgflag_pnu8)(pnu8);
typedef pgflag     (CODEPOINTER pxpgflag_s16)(s16);
typedef pgflag     (CODEPOINTER pxpgflag_pgs16)(pgs16);
typedef pgflag     (CODEPOINTER pxpgflag_pvs16)(pvs16);
typedef pgflag     (CODEPOINTER pxpgflag_prs16)(prs16);
typedef pgflag     (CODEPOINTER pxpgflag_pns16)(pns16);
typedef pgflag     (CODEPOINTER pxpgflag_u16)(u16);
typedef pgflag     (CODEPOINTER pxpgflag_pgu16)(pgu16);
typedef pgflag     (CODEPOINTER pxpgflag_pvu16)(pvu16);
typedef pgflag     (CODEPOINTER pxpgflag_pru16)(pru16);
typedef pgflag     (CODEPOINTER pxpgflag_pnu16)(pnu16);
typedef pgflag     (CODEPOINTER pxpgflag_s32)(s32);
typedef pgflag     (CODEPOINTER pxpgflag_pgs32)(pgs32);
typedef pgflag     (CODEPOINTER pxpgflag_pvs32)(pvs32);
typedef pgflag     (CODEPOINTER pxpgflag_prs32)(prs32);
typedef pgflag     (CODEPOINTER pxpgflag_pns32)(pns32);
typedef pgflag     (CODEPOINTER pxpgflag_u32)(u32);
typedef pgflag     (CODEPOINTER pxpgflag_pgu32)(pgu32);
typedef pgflag     (CODEPOINTER pxpgflag_pvu32)(pvu32);
typedef pgflag     (CODEPOINTER pxpgflag_pru32)(pru32);
typedef pgflag     (CODEPOINTER pxpgflag_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgflag

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvflag                      // pvflag Fn(arg)
typedef pvflag     (CODEPOINTER pxpvflag_void)(void);
typedef pvflag     (CODEPOINTER pxpvflag_pgvoid)(pgvoid);
typedef pvflag     (CODEPOINTER pxpvflag_pvvoid)(pvvoid);
typedef pvflag     (CODEPOINTER pxpvflag_prvoid)(prvoid);
typedef pvflag     (CODEPOINTER pxpvflag_pnvoid)(pnvoid);
typedef pvflag     (CODEPOINTER pxpvflag_flag)(flag);
typedef pvflag     (CODEPOINTER pxpvflag_pgflag)(pgflag);
typedef pvflag     (CODEPOINTER pxpvflag_pvflag)(pvflag);
typedef pvflag     (CODEPOINTER pxpvflag_prflag)(prflag);
typedef pvflag     (CODEPOINTER pxpvflag_pnflag)(pnflag);
typedef pvflag     (CODEPOINTER pxpvflag_s8)(s8);
typedef pvflag     (CODEPOINTER pxpvflag_pgs8)(pgs8);
typedef pvflag     (CODEPOINTER pxpvflag_pvs8)(pvs8);
typedef pvflag     (CODEPOINTER pxpvflag_prs8)(prs8);
typedef pvflag     (CODEPOINTER pxpvflag_pns8)(pns8);
typedef pvflag     (CODEPOINTER pxpvflag_u8)(u8);
typedef pvflag     (CODEPOINTER pxpvflag_pgu8)(pgu8);
typedef pvflag     (CODEPOINTER pxpvflag_pvu8)(pvu8);
typedef pvflag     (CODEPOINTER pxpvflag_pru8)(pru8);
typedef pvflag     (CODEPOINTER pxpvflag_pnu8)(pnu8);
typedef pvflag     (CODEPOINTER pxpvflag_s16)(s16);
typedef pvflag     (CODEPOINTER pxpvflag_pgs16)(pgs16);
typedef pvflag     (CODEPOINTER pxpvflag_pvs16)(pvs16);
typedef pvflag     (CODEPOINTER pxpvflag_prs16)(prs16);
typedef pvflag     (CODEPOINTER pxpvflag_pns16)(pns16);
typedef pvflag     (CODEPOINTER pxpvflag_u16)(u16);
typedef pvflag     (CODEPOINTER pxpvflag_pgu16)(pgu16);
typedef pvflag     (CODEPOINTER pxpvflag_pvu16)(pvu16);
typedef pvflag     (CODEPOINTER pxpvflag_pru16)(pru16);
typedef pvflag     (CODEPOINTER pxpvflag_pnu16)(pnu16);
typedef pvflag     (CODEPOINTER pxpvflag_s32)(s32);
typedef pvflag     (CODEPOINTER pxpvflag_pgs32)(pgs32);
typedef pvflag     (CODEPOINTER pxpvflag_pvs32)(pvs32);
typedef pvflag     (CODEPOINTER pxpvflag_prs32)(prs32);
typedef pvflag     (CODEPOINTER pxpvflag_pns32)(pns32);
typedef pvflag     (CODEPOINTER pxpvflag_u32)(u32);
typedef pvflag     (CODEPOINTER pxpvflag_pgu32)(pgu32);
typedef pvflag     (CODEPOINTER pxpvflag_pvu32)(pvu32);
typedef pvflag     (CODEPOINTER pxpvflag_pru32)(pru32);
typedef pvflag     (CODEPOINTER pxpvflag_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvflag

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prflag                      // prflag Fn(arg)
typedef prflag     (CODEPOINTER pxprflag_void)(void);
typedef prflag     (CODEPOINTER pxprflag_pgvoid)(pgvoid);
typedef prflag     (CODEPOINTER pxprflag_pvvoid)(pvvoid);
typedef prflag     (CODEPOINTER pxprflag_prvoid)(prvoid);
typedef prflag     (CODEPOINTER pxprflag_pnvoid)(pnvoid);
typedef prflag     (CODEPOINTER pxprflag_flag)(flag);
typedef prflag     (CODEPOINTER pxprflag_pgflag)(pgflag);
typedef prflag     (CODEPOINTER pxprflag_pvflag)(pvflag);
typedef prflag     (CODEPOINTER pxprflag_prflag)(prflag);
typedef prflag     (CODEPOINTER pxprflag_pnflag)(pnflag);
typedef prflag     (CODEPOINTER pxprflag_s8)(s8);
typedef prflag     (CODEPOINTER pxprflag_pgs8)(pgs8);
typedef prflag     (CODEPOINTER pxprflag_pvs8)(pvs8);
typedef prflag     (CODEPOINTER pxprflag_prs8)(prs8);
typedef prflag     (CODEPOINTER pxprflag_pns8)(pns8);
typedef prflag     (CODEPOINTER pxprflag_u8)(u8);
typedef prflag     (CODEPOINTER pxprflag_pgu8)(pgu8);
typedef prflag     (CODEPOINTER pxprflag_pvu8)(pvu8);
typedef prflag     (CODEPOINTER pxprflag_pru8)(pru8);
typedef prflag     (CODEPOINTER pxprflag_pnu8)(pnu8);
typedef prflag     (CODEPOINTER pxprflag_s16)(s16);
typedef prflag     (CODEPOINTER pxprflag_pgs16)(pgs16);
typedef prflag     (CODEPOINTER pxprflag_pvs16)(pvs16);
typedef prflag     (CODEPOINTER pxprflag_prs16)(prs16);
typedef prflag     (CODEPOINTER pxprflag_pns16)(pns16);
typedef prflag     (CODEPOINTER pxprflag_u16)(u16);
typedef prflag     (CODEPOINTER pxprflag_pgu16)(pgu16);
typedef prflag     (CODEPOINTER pxprflag_pvu16)(pvu16);
typedef prflag     (CODEPOINTER pxprflag_pru16)(pru16);
typedef prflag     (CODEPOINTER pxprflag_pnu16)(pnu16);
typedef prflag     (CODEPOINTER pxprflag_s32)(s32);
typedef prflag     (CODEPOINTER pxprflag_pgs32)(pgs32);
typedef prflag     (CODEPOINTER pxprflag_pvs32)(pvs32);
typedef prflag     (CODEPOINTER pxprflag_prs32)(prs32);
typedef prflag     (CODEPOINTER pxprflag_pns32)(pns32);
typedef prflag     (CODEPOINTER pxprflag_u32)(u32);
typedef prflag     (CODEPOINTER pxprflag_pgu32)(pgu32);
typedef prflag     (CODEPOINTER pxprflag_pvu32)(pvu32);
typedef prflag     (CODEPOINTER pxprflag_pru32)(pru32);
typedef prflag     (CODEPOINTER pxprflag_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prflag

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnflag                      // pnflag Fn(arg)
typedef pnflag     (CODEPOINTER pxpnflag_void)(void);
typedef pnflag     (CODEPOINTER pxpnflag_pgvoid)(pgvoid);
typedef pnflag     (CODEPOINTER pxpnflag_pvvoid)(pvvoid);
typedef pnflag     (CODEPOINTER pxpnflag_prvoid)(prvoid);
typedef pnflag     (CODEPOINTER pxpnflag_pnvoid)(pnvoid);
typedef pnflag     (CODEPOINTER pxpnflag_flag)(flag);
typedef pnflag     (CODEPOINTER pxpnflag_pgflag)(pgflag);
typedef pnflag     (CODEPOINTER pxpnflag_pvflag)(pvflag);
typedef pnflag     (CODEPOINTER pxpnflag_prflag)(prflag);
typedef pnflag     (CODEPOINTER pxpnflag_pnflag)(pnflag);
typedef pnflag     (CODEPOINTER pxpnflag_s8)(s8);
typedef pnflag     (CODEPOINTER pxpnflag_pgs8)(pgs8);
typedef pnflag     (CODEPOINTER pxpnflag_pvs8)(pvs8);
typedef pnflag     (CODEPOINTER pxpnflag_prs8)(prs8);
typedef pnflag     (CODEPOINTER pxpnflag_pns8)(pns8);
typedef pnflag     (CODEPOINTER pxpnflag_u8)(u8);
typedef pnflag     (CODEPOINTER pxpnflag_pgu8)(pgu8);
typedef pnflag     (CODEPOINTER pxpnflag_pvu8)(pvu8);
typedef pnflag     (CODEPOINTER pxpnflag_pru8)(pru8);
typedef pnflag     (CODEPOINTER pxpnflag_pnu8)(pnu8);
typedef pnflag     (CODEPOINTER pxpnflag_s16)(s16);
typedef pnflag     (CODEPOINTER pxpnflag_pgs16)(pgs16);
typedef pnflag     (CODEPOINTER pxpnflag_pvs16)(pvs16);
typedef pnflag     (CODEPOINTER pxpnflag_prs16)(prs16);
typedef pnflag     (CODEPOINTER pxpnflag_pns16)(pns16);
typedef pnflag     (CODEPOINTER pxpnflag_u16)(u16);
typedef pnflag     (CODEPOINTER pxpnflag_pgu16)(pgu16);
typedef pnflag     (CODEPOINTER pxpnflag_pvu16)(pvu16);
typedef pnflag     (CODEPOINTER pxpnflag_pru16)(pru16);
typedef pnflag     (CODEPOINTER pxpnflag_pnu16)(pnu16);
typedef pnflag     (CODEPOINTER pxpnflag_s32)(s32);
typedef pnflag     (CODEPOINTER pxpnflag_pgs32)(pgs32);
typedef pnflag     (CODEPOINTER pxpnflag_pvs32)(pvs32);
typedef pnflag     (CODEPOINTER pxpnflag_prs32)(prs32);
typedef pnflag     (CODEPOINTER pxpnflag_pns32)(pns32);
typedef pnflag     (CODEPOINTER pxpnflag_u32)(u32);
typedef pnflag     (CODEPOINTER pxpnflag_pgu32)(pgu32);
typedef pnflag     (CODEPOINTER pxpnflag_pvu32)(pvu32);
typedef pnflag     (CODEPOINTER pxpnflag_pru32)(pru32);
typedef pnflag     (CODEPOINTER pxpnflag_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnflag

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s8                      // s8 Fn(arg)
typedef s8         (CODEPOINTER pxs8_void)(void);
typedef s8         (CODEPOINTER pxs8_pgvoid)(pgvoid);
typedef s8         (CODEPOINTER pxs8_pvvoid)(pvvoid);
typedef s8         (CODEPOINTER pxs8_prvoid)(prvoid);
typedef s8         (CODEPOINTER pxs8_pnvoid)(pnvoid);
typedef s8         (CODEPOINTER pxs8_flag)(flag);
typedef s8         (CODEPOINTER pxs8_pgflag)(pgflag);
typedef s8         (CODEPOINTER pxs8_pvflag)(pvflag);
typedef s8         (CODEPOINTER pxs8_prflag)(prflag);
typedef s8         (CODEPOINTER pxs8_pnflag)(pnflag);
typedef s8         (CODEPOINTER pxs8_s8)(s8);
typedef s8         (CODEPOINTER pxs8_pgs8)(pgs8);
typedef s8         (CODEPOINTER pxs8_pvs8)(pvs8);
typedef s8         (CODEPOINTER pxs8_prs8)(prs8);
typedef s8         (CODEPOINTER pxs8_pns8)(pns8);
typedef s8         (CODEPOINTER pxs8_u8)(u8);
typedef s8         (CODEPOINTER pxs8_pgu8)(pgu8);
typedef s8         (CODEPOINTER pxs8_pvu8)(pvu8);
typedef s8         (CODEPOINTER pxs8_pru8)(pru8);
typedef s8         (CODEPOINTER pxs8_pnu8)(pnu8);
typedef s8         (CODEPOINTER pxs8_s16)(s16);
typedef s8         (CODEPOINTER pxs8_pgs16)(pgs16);
typedef s8         (CODEPOINTER pxs8_pvs16)(pvs16);
typedef s8         (CODEPOINTER pxs8_prs16)(prs16);
typedef s8         (CODEPOINTER pxs8_pns16)(pns16);
typedef s8         (CODEPOINTER pxs8_u16)(u16);
typedef s8         (CODEPOINTER pxs8_pgu16)(pgu16);
typedef s8         (CODEPOINTER pxs8_pvu16)(pvu16);
typedef s8         (CODEPOINTER pxs8_pru16)(pru16);
typedef s8         (CODEPOINTER pxs8_pnu16)(pnu16);
typedef s8         (CODEPOINTER pxs8_s32)(s32);
typedef s8         (CODEPOINTER pxs8_pgs32)(pgs32);
typedef s8         (CODEPOINTER pxs8_pvs32)(pvs32);
typedef s8         (CODEPOINTER pxs8_prs32)(prs32);
typedef s8         (CODEPOINTER pxs8_pns32)(pns32);
typedef s8         (CODEPOINTER pxs8_u32)(u32);
typedef s8         (CODEPOINTER pxs8_pgu32)(pgu32);
typedef s8         (CODEPOINTER pxs8_pvu32)(pvu32);
typedef s8         (CODEPOINTER pxs8_pru32)(pru32);
typedef s8         (CODEPOINTER pxs8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs8                      // pgs8 Fn(arg)
typedef pgs8       (CODEPOINTER pxpgs8_void)(void);
typedef pgs8       (CODEPOINTER pxpgs8_pgvoid)(pgvoid);
typedef pgs8       (CODEPOINTER pxpgs8_pvvoid)(pvvoid);
typedef pgs8       (CODEPOINTER pxpgs8_prvoid)(prvoid);
typedef pgs8       (CODEPOINTER pxpgs8_pnvoid)(pnvoid);
typedef pgs8       (CODEPOINTER pxpgs8_flag)(flag);
typedef pgs8       (CODEPOINTER pxpgs8_pgflag)(pgflag);
typedef pgs8       (CODEPOINTER pxpgs8_pvflag)(pvflag);
typedef pgs8       (CODEPOINTER pxpgs8_prflag)(prflag);
typedef pgs8       (CODEPOINTER pxpgs8_pnflag)(pnflag);
typedef pgs8       (CODEPOINTER pxpgs8_s8)(s8);
typedef pgs8       (CODEPOINTER pxpgs8_pgs8)(pgs8);
typedef pgs8       (CODEPOINTER pxpgs8_pvs8)(pvs8);
typedef pgs8       (CODEPOINTER pxpgs8_prs8)(prs8);
typedef pgs8       (CODEPOINTER pxpgs8_pns8)(pns8);
typedef pgs8       (CODEPOINTER pxpgs8_u8)(u8);
typedef pgs8       (CODEPOINTER pxpgs8_pgu8)(pgu8);
typedef pgs8       (CODEPOINTER pxpgs8_pvu8)(pvu8);
typedef pgs8       (CODEPOINTER pxpgs8_pru8)(pru8);
typedef pgs8       (CODEPOINTER pxpgs8_pnu8)(pnu8);
typedef pgs8       (CODEPOINTER pxpgs8_s16)(s16);
typedef pgs8       (CODEPOINTER pxpgs8_pgs16)(pgs16);
typedef pgs8       (CODEPOINTER pxpgs8_pvs16)(pvs16);
typedef pgs8       (CODEPOINTER pxpgs8_prs16)(prs16);
typedef pgs8       (CODEPOINTER pxpgs8_pns16)(pns16);
typedef pgs8       (CODEPOINTER pxpgs8_u16)(u16);
typedef pgs8       (CODEPOINTER pxpgs8_pgu16)(pgu16);
typedef pgs8       (CODEPOINTER pxpgs8_pvu16)(pvu16);
typedef pgs8       (CODEPOINTER pxpgs8_pru16)(pru16);
typedef pgs8       (CODEPOINTER pxpgs8_pnu16)(pnu16);
typedef pgs8       (CODEPOINTER pxpgs8_s32)(s32);
typedef pgs8       (CODEPOINTER pxpgs8_pgs32)(pgs32);
typedef pgs8       (CODEPOINTER pxpgs8_pvs32)(pvs32);
typedef pgs8       (CODEPOINTER pxpgs8_prs32)(prs32);
typedef pgs8       (CODEPOINTER pxpgs8_pns32)(pns32);
typedef pgs8       (CODEPOINTER pxpgs8_u32)(u32);
typedef pgs8       (CODEPOINTER pxpgs8_pgu32)(pgu32);
typedef pgs8       (CODEPOINTER pxpgs8_pvu32)(pvu32);
typedef pgs8       (CODEPOINTER pxpgs8_pru32)(pru32);
typedef pgs8       (CODEPOINTER pxpgs8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs8                      // pvs8 Fn(arg)
typedef pvs8       (CODEPOINTER pxpvs8_void)(void);
typedef pvs8       (CODEPOINTER pxpvs8_pgvoid)(pgvoid);
typedef pvs8       (CODEPOINTER pxpvs8_pvvoid)(pvvoid);
typedef pvs8       (CODEPOINTER pxpvs8_prvoid)(prvoid);
typedef pvs8       (CODEPOINTER pxpvs8_pnvoid)(pnvoid);
typedef pvs8       (CODEPOINTER pxpvs8_flag)(flag);
typedef pvs8       (CODEPOINTER pxpvs8_pgflag)(pgflag);
typedef pvs8       (CODEPOINTER pxpvs8_pvflag)(pvflag);
typedef pvs8       (CODEPOINTER pxpvs8_prflag)(prflag);
typedef pvs8       (CODEPOINTER pxpvs8_pnflag)(pnflag);
typedef pvs8       (CODEPOINTER pxpvs8_s8)(s8);
typedef pvs8       (CODEPOINTER pxpvs8_pgs8)(pgs8);
typedef pvs8       (CODEPOINTER pxpvs8_pvs8)(pvs8);
typedef pvs8       (CODEPOINTER pxpvs8_prs8)(prs8);
typedef pvs8       (CODEPOINTER pxpvs8_pns8)(pns8);
typedef pvs8       (CODEPOINTER pxpvs8_u8)(u8);
typedef pvs8       (CODEPOINTER pxpvs8_pgu8)(pgu8);
typedef pvs8       (CODEPOINTER pxpvs8_pvu8)(pvu8);
typedef pvs8       (CODEPOINTER pxpvs8_pru8)(pru8);
typedef pvs8       (CODEPOINTER pxpvs8_pnu8)(pnu8);
typedef pvs8       (CODEPOINTER pxpvs8_s16)(s16);
typedef pvs8       (CODEPOINTER pxpvs8_pgs16)(pgs16);
typedef pvs8       (CODEPOINTER pxpvs8_pvs16)(pvs16);
typedef pvs8       (CODEPOINTER pxpvs8_prs16)(prs16);
typedef pvs8       (CODEPOINTER pxpvs8_pns16)(pns16);
typedef pvs8       (CODEPOINTER pxpvs8_u16)(u16);
typedef pvs8       (CODEPOINTER pxpvs8_pgu16)(pgu16);
typedef pvs8       (CODEPOINTER pxpvs8_pvu16)(pvu16);
typedef pvs8       (CODEPOINTER pxpvs8_pru16)(pru16);
typedef pvs8       (CODEPOINTER pxpvs8_pnu16)(pnu16);
typedef pvs8       (CODEPOINTER pxpvs8_s32)(s32);
typedef pvs8       (CODEPOINTER pxpvs8_pgs32)(pgs32);
typedef pvs8       (CODEPOINTER pxpvs8_pvs32)(pvs32);
typedef pvs8       (CODEPOINTER pxpvs8_prs32)(prs32);
typedef pvs8       (CODEPOINTER pxpvs8_pns32)(pns32);
typedef pvs8       (CODEPOINTER pxpvs8_u32)(u32);
typedef pvs8       (CODEPOINTER pxpvs8_pgu32)(pgu32);
typedef pvs8       (CODEPOINTER pxpvs8_pvu32)(pvu32);
typedef pvs8       (CODEPOINTER pxpvs8_pru32)(pru32);
typedef pvs8       (CODEPOINTER pxpvs8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs8                      // prs8 Fn(arg)
typedef prs8       (CODEPOINTER pxprs8_void)(void);
typedef prs8       (CODEPOINTER pxprs8_pgvoid)(pgvoid);
typedef prs8       (CODEPOINTER pxprs8_pvvoid)(pvvoid);
typedef prs8       (CODEPOINTER pxprs8_prvoid)(prvoid);
typedef prs8       (CODEPOINTER pxprs8_pnvoid)(pnvoid);
typedef prs8       (CODEPOINTER pxprs8_flag)(flag);
typedef prs8       (CODEPOINTER pxprs8_pgflag)(pgflag);
typedef prs8       (CODEPOINTER pxprs8_pvflag)(pvflag);
typedef prs8       (CODEPOINTER pxprs8_prflag)(prflag);
typedef prs8       (CODEPOINTER pxprs8_pnflag)(pnflag);
typedef prs8       (CODEPOINTER pxprs8_s8)(s8);
typedef prs8       (CODEPOINTER pxprs8_pgs8)(pgs8);
typedef prs8       (CODEPOINTER pxprs8_pvs8)(pvs8);
typedef prs8       (CODEPOINTER pxprs8_prs8)(prs8);
typedef prs8       (CODEPOINTER pxprs8_pns8)(pns8);
typedef prs8       (CODEPOINTER pxprs8_u8)(u8);
typedef prs8       (CODEPOINTER pxprs8_pgu8)(pgu8);
typedef prs8       (CODEPOINTER pxprs8_pvu8)(pvu8);
typedef prs8       (CODEPOINTER pxprs8_pru8)(pru8);
typedef prs8       (CODEPOINTER pxprs8_pnu8)(pnu8);
typedef prs8       (CODEPOINTER pxprs8_s16)(s16);
typedef prs8       (CODEPOINTER pxprs8_pgs16)(pgs16);
typedef prs8       (CODEPOINTER pxprs8_pvs16)(pvs16);
typedef prs8       (CODEPOINTER pxprs8_prs16)(prs16);
typedef prs8       (CODEPOINTER pxprs8_pns16)(pns16);
typedef prs8       (CODEPOINTER pxprs8_u16)(u16);
typedef prs8       (CODEPOINTER pxprs8_pgu16)(pgu16);
typedef prs8       (CODEPOINTER pxprs8_pvu16)(pvu16);
typedef prs8       (CODEPOINTER pxprs8_pru16)(pru16);
typedef prs8       (CODEPOINTER pxprs8_pnu16)(pnu16);
typedef prs8       (CODEPOINTER pxprs8_s32)(s32);
typedef prs8       (CODEPOINTER pxprs8_pgs32)(pgs32);
typedef prs8       (CODEPOINTER pxprs8_pvs32)(pvs32);
typedef prs8       (CODEPOINTER pxprs8_prs32)(prs32);
typedef prs8       (CODEPOINTER pxprs8_pns32)(pns32);
typedef prs8       (CODEPOINTER pxprs8_u32)(u32);
typedef prs8       (CODEPOINTER pxprs8_pgu32)(pgu32);
typedef prs8       (CODEPOINTER pxprs8_pvu32)(pvu32);
typedef prs8       (CODEPOINTER pxprs8_pru32)(pru32);
typedef prs8       (CODEPOINTER pxprs8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns8                      // pns8 Fn(arg)
typedef pns8       (CODEPOINTER pxpns8_void)(void);
typedef pns8       (CODEPOINTER pxpns8_pgvoid)(pgvoid);
typedef pns8       (CODEPOINTER pxpns8_pvvoid)(pvvoid);
typedef pns8       (CODEPOINTER pxpns8_prvoid)(prvoid);
typedef pns8       (CODEPOINTER pxpns8_pnvoid)(pnvoid);
typedef pns8       (CODEPOINTER pxpns8_flag)(flag);
typedef pns8       (CODEPOINTER pxpns8_pgflag)(pgflag);
typedef pns8       (CODEPOINTER pxpns8_pvflag)(pvflag);
typedef pns8       (CODEPOINTER pxpns8_prflag)(prflag);
typedef pns8       (CODEPOINTER pxpns8_pnflag)(pnflag);
typedef pns8       (CODEPOINTER pxpns8_s8)(s8);
typedef pns8       (CODEPOINTER pxpns8_pgs8)(pgs8);
typedef pns8       (CODEPOINTER pxpns8_pvs8)(pvs8);
typedef pns8       (CODEPOINTER pxpns8_prs8)(prs8);
typedef pns8       (CODEPOINTER pxpns8_pns8)(pns8);
typedef pns8       (CODEPOINTER pxpns8_u8)(u8);
typedef pns8       (CODEPOINTER pxpns8_pgu8)(pgu8);
typedef pns8       (CODEPOINTER pxpns8_pvu8)(pvu8);
typedef pns8       (CODEPOINTER pxpns8_pru8)(pru8);
typedef pns8       (CODEPOINTER pxpns8_pnu8)(pnu8);
typedef pns8       (CODEPOINTER pxpns8_s16)(s16);
typedef pns8       (CODEPOINTER pxpns8_pgs16)(pgs16);
typedef pns8       (CODEPOINTER pxpns8_pvs16)(pvs16);
typedef pns8       (CODEPOINTER pxpns8_prs16)(prs16);
typedef pns8       (CODEPOINTER pxpns8_pns16)(pns16);
typedef pns8       (CODEPOINTER pxpns8_u16)(u16);
typedef pns8       (CODEPOINTER pxpns8_pgu16)(pgu16);
typedef pns8       (CODEPOINTER pxpns8_pvu16)(pvu16);
typedef pns8       (CODEPOINTER pxpns8_pru16)(pru16);
typedef pns8       (CODEPOINTER pxpns8_pnu16)(pnu16);
typedef pns8       (CODEPOINTER pxpns8_s32)(s32);
typedef pns8       (CODEPOINTER pxpns8_pgs32)(pgs32);
typedef pns8       (CODEPOINTER pxpns8_pvs32)(pvs32);
typedef pns8       (CODEPOINTER pxpns8_prs32)(prs32);
typedef pns8       (CODEPOINTER pxpns8_pns32)(pns32);
typedef pns8       (CODEPOINTER pxpns8_u32)(u32);
typedef pns8       (CODEPOINTER pxpns8_pgu32)(pgu32);
typedef pns8       (CODEPOINTER pxpns8_pvu32)(pvu32);
typedef pns8       (CODEPOINTER pxpns8_pru32)(pru32);
typedef pns8       (CODEPOINTER pxpns8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u8                      // u8 Fn(arg)
typedef u8         (CODEPOINTER pxu8_void)(void);
typedef u8         (CODEPOINTER pxu8_pgvoid)(pgvoid);
typedef u8         (CODEPOINTER pxu8_pvvoid)(pvvoid);
typedef u8         (CODEPOINTER pxu8_prvoid)(prvoid);
typedef u8         (CODEPOINTER pxu8_pnvoid)(pnvoid);
typedef u8         (CODEPOINTER pxu8_flag)(flag);
typedef u8         (CODEPOINTER pxu8_pgflag)(pgflag);
typedef u8         (CODEPOINTER pxu8_pvflag)(pvflag);
typedef u8         (CODEPOINTER pxu8_prflag)(prflag);
typedef u8         (CODEPOINTER pxu8_pnflag)(pnflag);
typedef u8         (CODEPOINTER pxu8_s8)(s8);
typedef u8         (CODEPOINTER pxu8_pgs8)(pgs8);
typedef u8         (CODEPOINTER pxu8_pvs8)(pvs8);
typedef u8         (CODEPOINTER pxu8_prs8)(prs8);
typedef u8         (CODEPOINTER pxu8_pns8)(pns8);
typedef u8         (CODEPOINTER pxu8_u8)(u8);
typedef u8         (CODEPOINTER pxu8_pgu8)(pgu8);
typedef u8         (CODEPOINTER pxu8_pvu8)(pvu8);
typedef u8         (CODEPOINTER pxu8_pru8)(pru8);
typedef u8         (CODEPOINTER pxu8_pnu8)(pnu8);
typedef u8         (CODEPOINTER pxu8_s16)(s16);
typedef u8         (CODEPOINTER pxu8_pgs16)(pgs16);
typedef u8         (CODEPOINTER pxu8_pvs16)(pvs16);
typedef u8         (CODEPOINTER pxu8_prs16)(prs16);
typedef u8         (CODEPOINTER pxu8_pns16)(pns16);
typedef u8         (CODEPOINTER pxu8_u16)(u16);
typedef u8         (CODEPOINTER pxu8_pgu16)(pgu16);
typedef u8         (CODEPOINTER pxu8_pvu16)(pvu16);
typedef u8         (CODEPOINTER pxu8_pru16)(pru16);
typedef u8         (CODEPOINTER pxu8_pnu16)(pnu16);
typedef u8         (CODEPOINTER pxu8_s32)(s32);
typedef u8         (CODEPOINTER pxu8_pgs32)(pgs32);
typedef u8         (CODEPOINTER pxu8_pvs32)(pvs32);
typedef u8         (CODEPOINTER pxu8_prs32)(prs32);
typedef u8         (CODEPOINTER pxu8_pns32)(pns32);
typedef u8         (CODEPOINTER pxu8_u32)(u32);
typedef u8         (CODEPOINTER pxu8_pgu32)(pgu32);
typedef u8         (CODEPOINTER pxu8_pvu32)(pvu32);
typedef u8         (CODEPOINTER pxu8_pru32)(pru32);
typedef u8         (CODEPOINTER pxu8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu8                      // pgu8 Fn(arg)
typedef pgu8       (CODEPOINTER pxpgu8_void)(void);
typedef pgu8       (CODEPOINTER pxpgu8_pgvoid)(pgvoid);
typedef pgu8       (CODEPOINTER pxpgu8_pvvoid)(pvvoid);
typedef pgu8       (CODEPOINTER pxpgu8_prvoid)(prvoid);
typedef pgu8       (CODEPOINTER pxpgu8_pnvoid)(pnvoid);
typedef pgu8       (CODEPOINTER pxpgu8_flag)(flag);
typedef pgu8       (CODEPOINTER pxpgu8_pgflag)(pgflag);
typedef pgu8       (CODEPOINTER pxpgu8_pvflag)(pvflag);
typedef pgu8       (CODEPOINTER pxpgu8_prflag)(prflag);
typedef pgu8       (CODEPOINTER pxpgu8_pnflag)(pnflag);
typedef pgu8       (CODEPOINTER pxpgu8_s8)(s8);
typedef pgu8       (CODEPOINTER pxpgu8_pgs8)(pgs8);
typedef pgu8       (CODEPOINTER pxpgu8_pvs8)(pvs8);
typedef pgu8       (CODEPOINTER pxpgu8_prs8)(prs8);
typedef pgu8       (CODEPOINTER pxpgu8_pns8)(pns8);
typedef pgu8       (CODEPOINTER pxpgu8_u8)(u8);
typedef pgu8       (CODEPOINTER pxpgu8_pgu8)(pgu8);
typedef pgu8       (CODEPOINTER pxpgu8_pvu8)(pvu8);
typedef pgu8       (CODEPOINTER pxpgu8_pru8)(pru8);
typedef pgu8       (CODEPOINTER pxpgu8_pnu8)(pnu8);
typedef pgu8       (CODEPOINTER pxpgu8_s16)(s16);
typedef pgu8       (CODEPOINTER pxpgu8_pgs16)(pgs16);
typedef pgu8       (CODEPOINTER pxpgu8_pvs16)(pvs16);
typedef pgu8       (CODEPOINTER pxpgu8_prs16)(prs16);
typedef pgu8       (CODEPOINTER pxpgu8_pns16)(pns16);
typedef pgu8       (CODEPOINTER pxpgu8_u16)(u16);
typedef pgu8       (CODEPOINTER pxpgu8_pgu16)(pgu16);
typedef pgu8       (CODEPOINTER pxpgu8_pvu16)(pvu16);
typedef pgu8       (CODEPOINTER pxpgu8_pru16)(pru16);
typedef pgu8       (CODEPOINTER pxpgu8_pnu16)(pnu16);
typedef pgu8       (CODEPOINTER pxpgu8_s32)(s32);
typedef pgu8       (CODEPOINTER pxpgu8_pgs32)(pgs32);
typedef pgu8       (CODEPOINTER pxpgu8_pvs32)(pvs32);
typedef pgu8       (CODEPOINTER pxpgu8_prs32)(prs32);
typedef pgu8       (CODEPOINTER pxpgu8_pns32)(pns32);
typedef pgu8       (CODEPOINTER pxpgu8_u32)(u32);
typedef pgu8       (CODEPOINTER pxpgu8_pgu32)(pgu32);
typedef pgu8       (CODEPOINTER pxpgu8_pvu32)(pvu32);
typedef pgu8       (CODEPOINTER pxpgu8_pru32)(pru32);
typedef pgu8       (CODEPOINTER pxpgu8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu8                      // pvu8 Fn(arg)
typedef pvu8       (CODEPOINTER pxpvu8_void)(void);
typedef pvu8       (CODEPOINTER pxpvu8_pgvoid)(pgvoid);
typedef pvu8       (CODEPOINTER pxpvu8_pvvoid)(pvvoid);
typedef pvu8       (CODEPOINTER pxpvu8_prvoid)(prvoid);
typedef pvu8       (CODEPOINTER pxpvu8_pnvoid)(pnvoid);
typedef pvu8       (CODEPOINTER pxpvu8_flag)(flag);
typedef pvu8       (CODEPOINTER pxpvu8_pgflag)(pgflag);
typedef pvu8       (CODEPOINTER pxpvu8_pvflag)(pvflag);
typedef pvu8       (CODEPOINTER pxpvu8_prflag)(prflag);
typedef pvu8       (CODEPOINTER pxpvu8_pnflag)(pnflag);
typedef pvu8       (CODEPOINTER pxpvu8_s8)(s8);
typedef pvu8       (CODEPOINTER pxpvu8_pgs8)(pgs8);
typedef pvu8       (CODEPOINTER pxpvu8_pvs8)(pvs8);
typedef pvu8       (CODEPOINTER pxpvu8_prs8)(prs8);
typedef pvu8       (CODEPOINTER pxpvu8_pns8)(pns8);
typedef pvu8       (CODEPOINTER pxpvu8_u8)(u8);
typedef pvu8       (CODEPOINTER pxpvu8_pgu8)(pgu8);
typedef pvu8       (CODEPOINTER pxpvu8_pvu8)(pvu8);
typedef pvu8       (CODEPOINTER pxpvu8_pru8)(pru8);
typedef pvu8       (CODEPOINTER pxpvu8_pnu8)(pnu8);
typedef pvu8       (CODEPOINTER pxpvu8_s16)(s16);
typedef pvu8       (CODEPOINTER pxpvu8_pgs16)(pgs16);
typedef pvu8       (CODEPOINTER pxpvu8_pvs16)(pvs16);
typedef pvu8       (CODEPOINTER pxpvu8_prs16)(prs16);
typedef pvu8       (CODEPOINTER pxpvu8_pns16)(pns16);
typedef pvu8       (CODEPOINTER pxpvu8_u16)(u16);
typedef pvu8       (CODEPOINTER pxpvu8_pgu16)(pgu16);
typedef pvu8       (CODEPOINTER pxpvu8_pvu16)(pvu16);
typedef pvu8       (CODEPOINTER pxpvu8_pru16)(pru16);
typedef pvu8       (CODEPOINTER pxpvu8_pnu16)(pnu16);
typedef pvu8       (CODEPOINTER pxpvu8_s32)(s32);
typedef pvu8       (CODEPOINTER pxpvu8_pgs32)(pgs32);
typedef pvu8       (CODEPOINTER pxpvu8_pvs32)(pvs32);
typedef pvu8       (CODEPOINTER pxpvu8_prs32)(prs32);
typedef pvu8       (CODEPOINTER pxpvu8_pns32)(pns32);
typedef pvu8       (CODEPOINTER pxpvu8_u32)(u32);
typedef pvu8       (CODEPOINTER pxpvu8_pgu32)(pgu32);
typedef pvu8       (CODEPOINTER pxpvu8_pvu32)(pvu32);
typedef pvu8       (CODEPOINTER pxpvu8_pru32)(pru32);
typedef pvu8       (CODEPOINTER pxpvu8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru8                      // pru8 Fn(arg)
typedef pru8       (CODEPOINTER pxpru8_void)(void);
typedef pru8       (CODEPOINTER pxpru8_pgvoid)(pgvoid);
typedef pru8       (CODEPOINTER pxpru8_pvvoid)(pvvoid);
typedef pru8       (CODEPOINTER pxpru8_prvoid)(prvoid);
typedef pru8       (CODEPOINTER pxpru8_pnvoid)(pnvoid);
typedef pru8       (CODEPOINTER pxpru8_flag)(flag);
typedef pru8       (CODEPOINTER pxpru8_pgflag)(pgflag);
typedef pru8       (CODEPOINTER pxpru8_pvflag)(pvflag);
typedef pru8       (CODEPOINTER pxpru8_prflag)(prflag);
typedef pru8       (CODEPOINTER pxpru8_pnflag)(pnflag);
typedef pru8       (CODEPOINTER pxpru8_s8)(s8);
typedef pru8       (CODEPOINTER pxpru8_pgs8)(pgs8);
typedef pru8       (CODEPOINTER pxpru8_pvs8)(pvs8);
typedef pru8       (CODEPOINTER pxpru8_prs8)(prs8);
typedef pru8       (CODEPOINTER pxpru8_pns8)(pns8);
typedef pru8       (CODEPOINTER pxpru8_u8)(u8);
typedef pru8       (CODEPOINTER pxpru8_pgu8)(pgu8);
typedef pru8       (CODEPOINTER pxpru8_pvu8)(pvu8);
typedef pru8       (CODEPOINTER pxpru8_pru8)(pru8);
typedef pru8       (CODEPOINTER pxpru8_pnu8)(pnu8);
typedef pru8       (CODEPOINTER pxpru8_s16)(s16);
typedef pru8       (CODEPOINTER pxpru8_pgs16)(pgs16);
typedef pru8       (CODEPOINTER pxpru8_pvs16)(pvs16);
typedef pru8       (CODEPOINTER pxpru8_prs16)(prs16);
typedef pru8       (CODEPOINTER pxpru8_pns16)(pns16);
typedef pru8       (CODEPOINTER pxpru8_u16)(u16);
typedef pru8       (CODEPOINTER pxpru8_pgu16)(pgu16);
typedef pru8       (CODEPOINTER pxpru8_pvu16)(pvu16);
typedef pru8       (CODEPOINTER pxpru8_pru16)(pru16);
typedef pru8       (CODEPOINTER pxpru8_pnu16)(pnu16);
typedef pru8       (CODEPOINTER pxpru8_s32)(s32);
typedef pru8       (CODEPOINTER pxpru8_pgs32)(pgs32);
typedef pru8       (CODEPOINTER pxpru8_pvs32)(pvs32);
typedef pru8       (CODEPOINTER pxpru8_prs32)(prs32);
typedef pru8       (CODEPOINTER pxpru8_pns32)(pns32);
typedef pru8       (CODEPOINTER pxpru8_u32)(u32);
typedef pru8       (CODEPOINTER pxpru8_pgu32)(pgu32);
typedef pru8       (CODEPOINTER pxpru8_pvu32)(pvu32);
typedef pru8       (CODEPOINTER pxpru8_pru32)(pru32);
typedef pru8       (CODEPOINTER pxpru8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu8                      // pnu8 Fn(arg)
typedef pnu8       (CODEPOINTER pxpnu8_void)(void);
typedef pnu8       (CODEPOINTER pxpnu8_pgvoid)(pgvoid);
typedef pnu8       (CODEPOINTER pxpnu8_pvvoid)(pvvoid);
typedef pnu8       (CODEPOINTER pxpnu8_prvoid)(prvoid);
typedef pnu8       (CODEPOINTER pxpnu8_pnvoid)(pnvoid);
typedef pnu8       (CODEPOINTER pxpnu8_flag)(flag);
typedef pnu8       (CODEPOINTER pxpnu8_pgflag)(pgflag);
typedef pnu8       (CODEPOINTER pxpnu8_pvflag)(pvflag);
typedef pnu8       (CODEPOINTER pxpnu8_prflag)(prflag);
typedef pnu8       (CODEPOINTER pxpnu8_pnflag)(pnflag);
typedef pnu8       (CODEPOINTER pxpnu8_s8)(s8);
typedef pnu8       (CODEPOINTER pxpnu8_pgs8)(pgs8);
typedef pnu8       (CODEPOINTER pxpnu8_pvs8)(pvs8);
typedef pnu8       (CODEPOINTER pxpnu8_prs8)(prs8);
typedef pnu8       (CODEPOINTER pxpnu8_pns8)(pns8);
typedef pnu8       (CODEPOINTER pxpnu8_u8)(u8);
typedef pnu8       (CODEPOINTER pxpnu8_pgu8)(pgu8);
typedef pnu8       (CODEPOINTER pxpnu8_pvu8)(pvu8);
typedef pnu8       (CODEPOINTER pxpnu8_pru8)(pru8);
typedef pnu8       (CODEPOINTER pxpnu8_pnu8)(pnu8);
typedef pnu8       (CODEPOINTER pxpnu8_s16)(s16);
typedef pnu8       (CODEPOINTER pxpnu8_pgs16)(pgs16);
typedef pnu8       (CODEPOINTER pxpnu8_pvs16)(pvs16);
typedef pnu8       (CODEPOINTER pxpnu8_prs16)(prs16);
typedef pnu8       (CODEPOINTER pxpnu8_pns16)(pns16);
typedef pnu8       (CODEPOINTER pxpnu8_u16)(u16);
typedef pnu8       (CODEPOINTER pxpnu8_pgu16)(pgu16);
typedef pnu8       (CODEPOINTER pxpnu8_pvu16)(pvu16);
typedef pnu8       (CODEPOINTER pxpnu8_pru16)(pru16);
typedef pnu8       (CODEPOINTER pxpnu8_pnu16)(pnu16);
typedef pnu8       (CODEPOINTER pxpnu8_s32)(s32);
typedef pnu8       (CODEPOINTER pxpnu8_pgs32)(pgs32);
typedef pnu8       (CODEPOINTER pxpnu8_pvs32)(pvs32);
typedef pnu8       (CODEPOINTER pxpnu8_prs32)(prs32);
typedef pnu8       (CODEPOINTER pxpnu8_pns32)(pns32);
typedef pnu8       (CODEPOINTER pxpnu8_u32)(u32);
typedef pnu8       (CODEPOINTER pxpnu8_pgu32)(pgu32);
typedef pnu8       (CODEPOINTER pxpnu8_pvu32)(pvu32);
typedef pnu8       (CODEPOINTER pxpnu8_pru32)(pru32);
typedef pnu8       (CODEPOINTER pxpnu8_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu8

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s16                      // s16 Fn(arg)
typedef s16        (CODEPOINTER pxs16_void)(void);
typedef s16        (CODEPOINTER pxs16_pgvoid)(pgvoid);
typedef s16        (CODEPOINTER pxs16_pvvoid)(pvvoid);
typedef s16        (CODEPOINTER pxs16_prvoid)(prvoid);
typedef s16        (CODEPOINTER pxs16_pnvoid)(pnvoid);
typedef s16        (CODEPOINTER pxs16_flag)(flag);
typedef s16        (CODEPOINTER pxs16_pgflag)(pgflag);
typedef s16        (CODEPOINTER pxs16_pvflag)(pvflag);
typedef s16        (CODEPOINTER pxs16_prflag)(prflag);
typedef s16        (CODEPOINTER pxs16_pnflag)(pnflag);
typedef s16        (CODEPOINTER pxs16_s8)(s8);
typedef s16        (CODEPOINTER pxs16_pgs8)(pgs8);
typedef s16        (CODEPOINTER pxs16_pvs8)(pvs8);
typedef s16        (CODEPOINTER pxs16_prs8)(prs8);
typedef s16        (CODEPOINTER pxs16_pns8)(pns8);
typedef s16        (CODEPOINTER pxs16_u8)(u8);
typedef s16        (CODEPOINTER pxs16_pgu8)(pgu8);
typedef s16        (CODEPOINTER pxs16_pvu8)(pvu8);
typedef s16        (CODEPOINTER pxs16_pru8)(pru8);
typedef s16        (CODEPOINTER pxs16_pnu8)(pnu8);
typedef s16        (CODEPOINTER pxs16_s16)(s16);
typedef s16        (CODEPOINTER pxs16_pgs16)(pgs16);
typedef s16        (CODEPOINTER pxs16_pvs16)(pvs16);
typedef s16        (CODEPOINTER pxs16_prs16)(prs16);
typedef s16        (CODEPOINTER pxs16_pns16)(pns16);
typedef s16        (CODEPOINTER pxs16_u16)(u16);
typedef s16        (CODEPOINTER pxs16_pgu16)(pgu16);
typedef s16        (CODEPOINTER pxs16_pvu16)(pvu16);
typedef s16        (CODEPOINTER pxs16_pru16)(pru16);
typedef s16        (CODEPOINTER pxs16_pnu16)(pnu16);
typedef s16        (CODEPOINTER pxs16_s32)(s32);
typedef s16        (CODEPOINTER pxs16_pgs32)(pgs32);
typedef s16        (CODEPOINTER pxs16_pvs32)(pvs32);
typedef s16        (CODEPOINTER pxs16_prs32)(prs32);
typedef s16        (CODEPOINTER pxs16_pns32)(pns32);
typedef s16        (CODEPOINTER pxs16_u32)(u32);
typedef s16        (CODEPOINTER pxs16_pgu32)(pgu32);
typedef s16        (CODEPOINTER pxs16_pvu32)(pvu32);
typedef s16        (CODEPOINTER pxs16_pru32)(pru32);
typedef s16        (CODEPOINTER pxs16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs16                      // pgs16 Fn(arg)
typedef pgs16      (CODEPOINTER pxpgs16_void)(void);
typedef pgs16      (CODEPOINTER pxpgs16_pgvoid)(pgvoid);
typedef pgs16      (CODEPOINTER pxpgs16_pvvoid)(pvvoid);
typedef pgs16      (CODEPOINTER pxpgs16_prvoid)(prvoid);
typedef pgs16      (CODEPOINTER pxpgs16_pnvoid)(pnvoid);
typedef pgs16      (CODEPOINTER pxpgs16_flag)(flag);
typedef pgs16      (CODEPOINTER pxpgs16_pgflag)(pgflag);
typedef pgs16      (CODEPOINTER pxpgs16_pvflag)(pvflag);
typedef pgs16      (CODEPOINTER pxpgs16_prflag)(prflag);
typedef pgs16      (CODEPOINTER pxpgs16_pnflag)(pnflag);
typedef pgs16      (CODEPOINTER pxpgs16_s8)(s8);
typedef pgs16      (CODEPOINTER pxpgs16_pgs8)(pgs8);
typedef pgs16      (CODEPOINTER pxpgs16_pvs8)(pvs8);
typedef pgs16      (CODEPOINTER pxpgs16_prs8)(prs8);
typedef pgs16      (CODEPOINTER pxpgs16_pns8)(pns8);
typedef pgs16      (CODEPOINTER pxpgs16_u8)(u8);
typedef pgs16      (CODEPOINTER pxpgs16_pgu8)(pgu8);
typedef pgs16      (CODEPOINTER pxpgs16_pvu8)(pvu8);
typedef pgs16      (CODEPOINTER pxpgs16_pru8)(pru8);
typedef pgs16      (CODEPOINTER pxpgs16_pnu8)(pnu8);
typedef pgs16      (CODEPOINTER pxpgs16_s16)(s16);
typedef pgs16      (CODEPOINTER pxpgs16_pgs16)(pgs16);
typedef pgs16      (CODEPOINTER pxpgs16_pvs16)(pvs16);
typedef pgs16      (CODEPOINTER pxpgs16_prs16)(prs16);
typedef pgs16      (CODEPOINTER pxpgs16_pns16)(pns16);
typedef pgs16      (CODEPOINTER pxpgs16_u16)(u16);
typedef pgs16      (CODEPOINTER pxpgs16_pgu16)(pgu16);
typedef pgs16      (CODEPOINTER pxpgs16_pvu16)(pvu16);
typedef pgs16      (CODEPOINTER pxpgs16_pru16)(pru16);
typedef pgs16      (CODEPOINTER pxpgs16_pnu16)(pnu16);
typedef pgs16      (CODEPOINTER pxpgs16_s32)(s32);
typedef pgs16      (CODEPOINTER pxpgs16_pgs32)(pgs32);
typedef pgs16      (CODEPOINTER pxpgs16_pvs32)(pvs32);
typedef pgs16      (CODEPOINTER pxpgs16_prs32)(prs32);
typedef pgs16      (CODEPOINTER pxpgs16_pns32)(pns32);
typedef pgs16      (CODEPOINTER pxpgs16_u32)(u32);
typedef pgs16      (CODEPOINTER pxpgs16_pgu32)(pgu32);
typedef pgs16      (CODEPOINTER pxpgs16_pvu32)(pvu32);
typedef pgs16      (CODEPOINTER pxpgs16_pru32)(pru32);
typedef pgs16      (CODEPOINTER pxpgs16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs16                      // pvs16 Fn(arg)
typedef pvs16      (CODEPOINTER pxpvs16_void)(void);
typedef pvs16      (CODEPOINTER pxpvs16_pgvoid)(pgvoid);
typedef pvs16      (CODEPOINTER pxpvs16_pvvoid)(pvvoid);
typedef pvs16      (CODEPOINTER pxpvs16_prvoid)(prvoid);
typedef pvs16      (CODEPOINTER pxpvs16_pnvoid)(pnvoid);
typedef pvs16      (CODEPOINTER pxpvs16_flag)(flag);
typedef pvs16      (CODEPOINTER pxpvs16_pgflag)(pgflag);
typedef pvs16      (CODEPOINTER pxpvs16_pvflag)(pvflag);
typedef pvs16      (CODEPOINTER pxpvs16_prflag)(prflag);
typedef pvs16      (CODEPOINTER pxpvs16_pnflag)(pnflag);
typedef pvs16      (CODEPOINTER pxpvs16_s8)(s8);
typedef pvs16      (CODEPOINTER pxpvs16_pgs8)(pgs8);
typedef pvs16      (CODEPOINTER pxpvs16_pvs8)(pvs8);
typedef pvs16      (CODEPOINTER pxpvs16_prs8)(prs8);
typedef pvs16      (CODEPOINTER pxpvs16_pns8)(pns8);
typedef pvs16      (CODEPOINTER pxpvs16_u8)(u8);
typedef pvs16      (CODEPOINTER pxpvs16_pgu8)(pgu8);
typedef pvs16      (CODEPOINTER pxpvs16_pvu8)(pvu8);
typedef pvs16      (CODEPOINTER pxpvs16_pru8)(pru8);
typedef pvs16      (CODEPOINTER pxpvs16_pnu8)(pnu8);
typedef pvs16      (CODEPOINTER pxpvs16_s16)(s16);
typedef pvs16      (CODEPOINTER pxpvs16_pgs16)(pgs16);
typedef pvs16      (CODEPOINTER pxpvs16_pvs16)(pvs16);
typedef pvs16      (CODEPOINTER pxpvs16_prs16)(prs16);
typedef pvs16      (CODEPOINTER pxpvs16_pns16)(pns16);
typedef pvs16      (CODEPOINTER pxpvs16_u16)(u16);
typedef pvs16      (CODEPOINTER pxpvs16_pgu16)(pgu16);
typedef pvs16      (CODEPOINTER pxpvs16_pvu16)(pvu16);
typedef pvs16      (CODEPOINTER pxpvs16_pru16)(pru16);
typedef pvs16      (CODEPOINTER pxpvs16_pnu16)(pnu16);
typedef pvs16      (CODEPOINTER pxpvs16_s32)(s32);
typedef pvs16      (CODEPOINTER pxpvs16_pgs32)(pgs32);
typedef pvs16      (CODEPOINTER pxpvs16_pvs32)(pvs32);
typedef pvs16      (CODEPOINTER pxpvs16_prs32)(prs32);
typedef pvs16      (CODEPOINTER pxpvs16_pns32)(pns32);
typedef pvs16      (CODEPOINTER pxpvs16_u32)(u32);
typedef pvs16      (CODEPOINTER pxpvs16_pgu32)(pgu32);
typedef pvs16      (CODEPOINTER pxpvs16_pvu32)(pvu32);
typedef pvs16      (CODEPOINTER pxpvs16_pru32)(pru32);
typedef pvs16      (CODEPOINTER pxpvs16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs16                      // prs16 Fn(arg)
typedef prs16      (CODEPOINTER pxprs16_void)(void);
typedef prs16      (CODEPOINTER pxprs16_pgvoid)(pgvoid);
typedef prs16      (CODEPOINTER pxprs16_pvvoid)(pvvoid);
typedef prs16      (CODEPOINTER pxprs16_prvoid)(prvoid);
typedef prs16      (CODEPOINTER pxprs16_pnvoid)(pnvoid);
typedef prs16      (CODEPOINTER pxprs16_flag)(flag);
typedef prs16      (CODEPOINTER pxprs16_pgflag)(pgflag);
typedef prs16      (CODEPOINTER pxprs16_pvflag)(pvflag);
typedef prs16      (CODEPOINTER pxprs16_prflag)(prflag);
typedef prs16      (CODEPOINTER pxprs16_pnflag)(pnflag);
typedef prs16      (CODEPOINTER pxprs16_s8)(s8);
typedef prs16      (CODEPOINTER pxprs16_pgs8)(pgs8);
typedef prs16      (CODEPOINTER pxprs16_pvs8)(pvs8);
typedef prs16      (CODEPOINTER pxprs16_prs8)(prs8);
typedef prs16      (CODEPOINTER pxprs16_pns8)(pns8);
typedef prs16      (CODEPOINTER pxprs16_u8)(u8);
typedef prs16      (CODEPOINTER pxprs16_pgu8)(pgu8);
typedef prs16      (CODEPOINTER pxprs16_pvu8)(pvu8);
typedef prs16      (CODEPOINTER pxprs16_pru8)(pru8);
typedef prs16      (CODEPOINTER pxprs16_pnu8)(pnu8);
typedef prs16      (CODEPOINTER pxprs16_s16)(s16);
typedef prs16      (CODEPOINTER pxprs16_pgs16)(pgs16);
typedef prs16      (CODEPOINTER pxprs16_pvs16)(pvs16);
typedef prs16      (CODEPOINTER pxprs16_prs16)(prs16);
typedef prs16      (CODEPOINTER pxprs16_pns16)(pns16);
typedef prs16      (CODEPOINTER pxprs16_u16)(u16);
typedef prs16      (CODEPOINTER pxprs16_pgu16)(pgu16);
typedef prs16      (CODEPOINTER pxprs16_pvu16)(pvu16);
typedef prs16      (CODEPOINTER pxprs16_pru16)(pru16);
typedef prs16      (CODEPOINTER pxprs16_pnu16)(pnu16);
typedef prs16      (CODEPOINTER pxprs16_s32)(s32);
typedef prs16      (CODEPOINTER pxprs16_pgs32)(pgs32);
typedef prs16      (CODEPOINTER pxprs16_pvs32)(pvs32);
typedef prs16      (CODEPOINTER pxprs16_prs32)(prs32);
typedef prs16      (CODEPOINTER pxprs16_pns32)(pns32);
typedef prs16      (CODEPOINTER pxprs16_u32)(u32);
typedef prs16      (CODEPOINTER pxprs16_pgu32)(pgu32);
typedef prs16      (CODEPOINTER pxprs16_pvu32)(pvu32);
typedef prs16      (CODEPOINTER pxprs16_pru32)(pru32);
typedef prs16      (CODEPOINTER pxprs16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns16                      // pns16 Fn(arg)
typedef pns16      (CODEPOINTER pxpns16_void)(void);
typedef pns16      (CODEPOINTER pxpns16_pgvoid)(pgvoid);
typedef pns16      (CODEPOINTER pxpns16_pvvoid)(pvvoid);
typedef pns16      (CODEPOINTER pxpns16_prvoid)(prvoid);
typedef pns16      (CODEPOINTER pxpns16_pnvoid)(pnvoid);
typedef pns16      (CODEPOINTER pxpns16_flag)(flag);
typedef pns16      (CODEPOINTER pxpns16_pgflag)(pgflag);
typedef pns16      (CODEPOINTER pxpns16_pvflag)(pvflag);
typedef pns16      (CODEPOINTER pxpns16_prflag)(prflag);
typedef pns16      (CODEPOINTER pxpns16_pnflag)(pnflag);
typedef pns16      (CODEPOINTER pxpns16_s8)(s8);
typedef pns16      (CODEPOINTER pxpns16_pgs8)(pgs8);
typedef pns16      (CODEPOINTER pxpns16_pvs8)(pvs8);
typedef pns16      (CODEPOINTER pxpns16_prs8)(prs8);
typedef pns16      (CODEPOINTER pxpns16_pns8)(pns8);
typedef pns16      (CODEPOINTER pxpns16_u8)(u8);
typedef pns16      (CODEPOINTER pxpns16_pgu8)(pgu8);
typedef pns16      (CODEPOINTER pxpns16_pvu8)(pvu8);
typedef pns16      (CODEPOINTER pxpns16_pru8)(pru8);
typedef pns16      (CODEPOINTER pxpns16_pnu8)(pnu8);
typedef pns16      (CODEPOINTER pxpns16_s16)(s16);
typedef pns16      (CODEPOINTER pxpns16_pgs16)(pgs16);
typedef pns16      (CODEPOINTER pxpns16_pvs16)(pvs16);
typedef pns16      (CODEPOINTER pxpns16_prs16)(prs16);
typedef pns16      (CODEPOINTER pxpns16_pns16)(pns16);
typedef pns16      (CODEPOINTER pxpns16_u16)(u16);
typedef pns16      (CODEPOINTER pxpns16_pgu16)(pgu16);
typedef pns16      (CODEPOINTER pxpns16_pvu16)(pvu16);
typedef pns16      (CODEPOINTER pxpns16_pru16)(pru16);
typedef pns16      (CODEPOINTER pxpns16_pnu16)(pnu16);
typedef pns16      (CODEPOINTER pxpns16_s32)(s32);
typedef pns16      (CODEPOINTER pxpns16_pgs32)(pgs32);
typedef pns16      (CODEPOINTER pxpns16_pvs32)(pvs32);
typedef pns16      (CODEPOINTER pxpns16_prs32)(prs32);
typedef pns16      (CODEPOINTER pxpns16_pns32)(pns32);
typedef pns16      (CODEPOINTER pxpns16_u32)(u32);
typedef pns16      (CODEPOINTER pxpns16_pgu32)(pgu32);
typedef pns16      (CODEPOINTER pxpns16_pvu32)(pvu32);
typedef pns16      (CODEPOINTER pxpns16_pru32)(pru32);
typedef pns16      (CODEPOINTER pxpns16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u16                      // u16 Fn(arg)
typedef u16        (CODEPOINTER pxu16_void)(void);
typedef u16        (CODEPOINTER pxu16_pgvoid)(pgvoid);
typedef u16        (CODEPOINTER pxu16_pvvoid)(pvvoid);
typedef u16        (CODEPOINTER pxu16_prvoid)(prvoid);
typedef u16        (CODEPOINTER pxu16_pnvoid)(pnvoid);
typedef u16        (CODEPOINTER pxu16_flag)(flag);
typedef u16        (CODEPOINTER pxu16_pgflag)(pgflag);
typedef u16        (CODEPOINTER pxu16_pvflag)(pvflag);
typedef u16        (CODEPOINTER pxu16_prflag)(prflag);
typedef u16        (CODEPOINTER pxu16_pnflag)(pnflag);
typedef u16        (CODEPOINTER pxu16_s8)(s8);
typedef u16        (CODEPOINTER pxu16_pgs8)(pgs8);
typedef u16        (CODEPOINTER pxu16_pvs8)(pvs8);
typedef u16        (CODEPOINTER pxu16_prs8)(prs8);
typedef u16        (CODEPOINTER pxu16_pns8)(pns8);
typedef u16        (CODEPOINTER pxu16_u8)(u8);
typedef u16        (CODEPOINTER pxu16_pgu8)(pgu8);
typedef u16        (CODEPOINTER pxu16_pvu8)(pvu8);
typedef u16        (CODEPOINTER pxu16_pru8)(pru8);
typedef u16        (CODEPOINTER pxu16_pnu8)(pnu8);
typedef u16        (CODEPOINTER pxu16_s16)(s16);
typedef u16        (CODEPOINTER pxu16_pgs16)(pgs16);
typedef u16        (CODEPOINTER pxu16_pvs16)(pvs16);
typedef u16        (CODEPOINTER pxu16_prs16)(prs16);
typedef u16        (CODEPOINTER pxu16_pns16)(pns16);
typedef u16        (CODEPOINTER pxu16_u16)(u16);
typedef u16        (CODEPOINTER pxu16_pgu16)(pgu16);
typedef u16        (CODEPOINTER pxu16_pvu16)(pvu16);
typedef u16        (CODEPOINTER pxu16_pru16)(pru16);
typedef u16        (CODEPOINTER pxu16_pnu16)(pnu16);
typedef u16        (CODEPOINTER pxu16_s32)(s32);
typedef u16        (CODEPOINTER pxu16_pgs32)(pgs32);
typedef u16        (CODEPOINTER pxu16_pvs32)(pvs32);
typedef u16        (CODEPOINTER pxu16_prs32)(prs32);
typedef u16        (CODEPOINTER pxu16_pns32)(pns32);
typedef u16        (CODEPOINTER pxu16_u32)(u32);
typedef u16        (CODEPOINTER pxu16_pgu32)(pgu32);
typedef u16        (CODEPOINTER pxu16_pvu32)(pvu32);
typedef u16        (CODEPOINTER pxu16_pru32)(pru32);
typedef u16        (CODEPOINTER pxu16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu16                      // pgu16 Fn(arg)
typedef pgu16      (CODEPOINTER pxpgu16_void)(void);
typedef pgu16      (CODEPOINTER pxpgu16_pgvoid)(pgvoid);
typedef pgu16      (CODEPOINTER pxpgu16_pvvoid)(pvvoid);
typedef pgu16      (CODEPOINTER pxpgu16_prvoid)(prvoid);
typedef pgu16      (CODEPOINTER pxpgu16_pnvoid)(pnvoid);
typedef pgu16      (CODEPOINTER pxpgu16_flag)(flag);
typedef pgu16      (CODEPOINTER pxpgu16_pgflag)(pgflag);
typedef pgu16      (CODEPOINTER pxpgu16_pvflag)(pvflag);
typedef pgu16      (CODEPOINTER pxpgu16_prflag)(prflag);
typedef pgu16      (CODEPOINTER pxpgu16_pnflag)(pnflag);
typedef pgu16      (CODEPOINTER pxpgu16_s8)(s8);
typedef pgu16      (CODEPOINTER pxpgu16_pgs8)(pgs8);
typedef pgu16      (CODEPOINTER pxpgu16_pvs8)(pvs8);
typedef pgu16      (CODEPOINTER pxpgu16_prs8)(prs8);
typedef pgu16      (CODEPOINTER pxpgu16_pns8)(pns8);
typedef pgu16      (CODEPOINTER pxpgu16_u8)(u8);
typedef pgu16      (CODEPOINTER pxpgu16_pgu8)(pgu8);
typedef pgu16      (CODEPOINTER pxpgu16_pvu8)(pvu8);
typedef pgu16      (CODEPOINTER pxpgu16_pru8)(pru8);
typedef pgu16      (CODEPOINTER pxpgu16_pnu8)(pnu8);
typedef pgu16      (CODEPOINTER pxpgu16_s16)(s16);
typedef pgu16      (CODEPOINTER pxpgu16_pgs16)(pgs16);
typedef pgu16      (CODEPOINTER pxpgu16_pvs16)(pvs16);
typedef pgu16      (CODEPOINTER pxpgu16_prs16)(prs16);
typedef pgu16      (CODEPOINTER pxpgu16_pns16)(pns16);
typedef pgu16      (CODEPOINTER pxpgu16_u16)(u16);
typedef pgu16      (CODEPOINTER pxpgu16_pgu16)(pgu16);
typedef pgu16      (CODEPOINTER pxpgu16_pvu16)(pvu16);
typedef pgu16      (CODEPOINTER pxpgu16_pru16)(pru16);
typedef pgu16      (CODEPOINTER pxpgu16_pnu16)(pnu16);
typedef pgu16      (CODEPOINTER pxpgu16_s32)(s32);
typedef pgu16      (CODEPOINTER pxpgu16_pgs32)(pgs32);
typedef pgu16      (CODEPOINTER pxpgu16_pvs32)(pvs32);
typedef pgu16      (CODEPOINTER pxpgu16_prs32)(prs32);
typedef pgu16      (CODEPOINTER pxpgu16_pns32)(pns32);
typedef pgu16      (CODEPOINTER pxpgu16_u32)(u32);
typedef pgu16      (CODEPOINTER pxpgu16_pgu32)(pgu32);
typedef pgu16      (CODEPOINTER pxpgu16_pvu32)(pvu32);
typedef pgu16      (CODEPOINTER pxpgu16_pru32)(pru32);
typedef pgu16      (CODEPOINTER pxpgu16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu16                      // pvu16 Fn(arg)
typedef pvu16      (CODEPOINTER pxpvu16_void)(void);
typedef pvu16      (CODEPOINTER pxpvu16_pgvoid)(pgvoid);
typedef pvu16      (CODEPOINTER pxpvu16_pvvoid)(pvvoid);
typedef pvu16      (CODEPOINTER pxpvu16_prvoid)(prvoid);
typedef pvu16      (CODEPOINTER pxpvu16_pnvoid)(pnvoid);
typedef pvu16      (CODEPOINTER pxpvu16_flag)(flag);
typedef pvu16      (CODEPOINTER pxpvu16_pgflag)(pgflag);
typedef pvu16      (CODEPOINTER pxpvu16_pvflag)(pvflag);
typedef pvu16      (CODEPOINTER pxpvu16_prflag)(prflag);
typedef pvu16      (CODEPOINTER pxpvu16_pnflag)(pnflag);
typedef pvu16      (CODEPOINTER pxpvu16_s8)(s8);
typedef pvu16      (CODEPOINTER pxpvu16_pgs8)(pgs8);
typedef pvu16      (CODEPOINTER pxpvu16_pvs8)(pvs8);
typedef pvu16      (CODEPOINTER pxpvu16_prs8)(prs8);
typedef pvu16      (CODEPOINTER pxpvu16_pns8)(pns8);
typedef pvu16      (CODEPOINTER pxpvu16_u8)(u8);
typedef pvu16      (CODEPOINTER pxpvu16_pgu8)(pgu8);
typedef pvu16      (CODEPOINTER pxpvu16_pvu8)(pvu8);
typedef pvu16      (CODEPOINTER pxpvu16_pru8)(pru8);
typedef pvu16      (CODEPOINTER pxpvu16_pnu8)(pnu8);
typedef pvu16      (CODEPOINTER pxpvu16_s16)(s16);
typedef pvu16      (CODEPOINTER pxpvu16_pgs16)(pgs16);
typedef pvu16      (CODEPOINTER pxpvu16_pvs16)(pvs16);
typedef pvu16      (CODEPOINTER pxpvu16_prs16)(prs16);
typedef pvu16      (CODEPOINTER pxpvu16_pns16)(pns16);
typedef pvu16      (CODEPOINTER pxpvu16_u16)(u16);
typedef pvu16      (CODEPOINTER pxpvu16_pgu16)(pgu16);
typedef pvu16      (CODEPOINTER pxpvu16_pvu16)(pvu16);
typedef pvu16      (CODEPOINTER pxpvu16_pru16)(pru16);
typedef pvu16      (CODEPOINTER pxpvu16_pnu16)(pnu16);
typedef pvu16      (CODEPOINTER pxpvu16_s32)(s32);
typedef pvu16      (CODEPOINTER pxpvu16_pgs32)(pgs32);
typedef pvu16      (CODEPOINTER pxpvu16_pvs32)(pvs32);
typedef pvu16      (CODEPOINTER pxpvu16_prs32)(prs32);
typedef pvu16      (CODEPOINTER pxpvu16_pns32)(pns32);
typedef pvu16      (CODEPOINTER pxpvu16_u32)(u32);
typedef pvu16      (CODEPOINTER pxpvu16_pgu32)(pgu32);
typedef pvu16      (CODEPOINTER pxpvu16_pvu32)(pvu32);
typedef pvu16      (CODEPOINTER pxpvu16_pru32)(pru32);
typedef pvu16      (CODEPOINTER pxpvu16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru16                      // pru16 Fn(arg)
typedef pru16      (CODEPOINTER pxpru16_void)(void);
typedef pru16      (CODEPOINTER pxpru16_pgvoid)(pgvoid);
typedef pru16      (CODEPOINTER pxpru16_pvvoid)(pvvoid);
typedef pru16      (CODEPOINTER pxpru16_prvoid)(prvoid);
typedef pru16      (CODEPOINTER pxpru16_pnvoid)(pnvoid);
typedef pru16      (CODEPOINTER pxpru16_flag)(flag);
typedef pru16      (CODEPOINTER pxpru16_pgflag)(pgflag);
typedef pru16      (CODEPOINTER pxpru16_pvflag)(pvflag);
typedef pru16      (CODEPOINTER pxpru16_prflag)(prflag);
typedef pru16      (CODEPOINTER pxpru16_pnflag)(pnflag);
typedef pru16      (CODEPOINTER pxpru16_s8)(s8);
typedef pru16      (CODEPOINTER pxpru16_pgs8)(pgs8);
typedef pru16      (CODEPOINTER pxpru16_pvs8)(pvs8);
typedef pru16      (CODEPOINTER pxpru16_prs8)(prs8);
typedef pru16      (CODEPOINTER pxpru16_pns8)(pns8);
typedef pru16      (CODEPOINTER pxpru16_u8)(u8);
typedef pru16      (CODEPOINTER pxpru16_pgu8)(pgu8);
typedef pru16      (CODEPOINTER pxpru16_pvu8)(pvu8);
typedef pru16      (CODEPOINTER pxpru16_pru8)(pru8);
typedef pru16      (CODEPOINTER pxpru16_pnu8)(pnu8);
typedef pru16      (CODEPOINTER pxpru16_s16)(s16);
typedef pru16      (CODEPOINTER pxpru16_pgs16)(pgs16);
typedef pru16      (CODEPOINTER pxpru16_pvs16)(pvs16);
typedef pru16      (CODEPOINTER pxpru16_prs16)(prs16);
typedef pru16      (CODEPOINTER pxpru16_pns16)(pns16);
typedef pru16      (CODEPOINTER pxpru16_u16)(u16);
typedef pru16      (CODEPOINTER pxpru16_pgu16)(pgu16);
typedef pru16      (CODEPOINTER pxpru16_pvu16)(pvu16);
typedef pru16      (CODEPOINTER pxpru16_pru16)(pru16);
typedef pru16      (CODEPOINTER pxpru16_pnu16)(pnu16);
typedef pru16      (CODEPOINTER pxpru16_s32)(s32);
typedef pru16      (CODEPOINTER pxpru16_pgs32)(pgs32);
typedef pru16      (CODEPOINTER pxpru16_pvs32)(pvs32);
typedef pru16      (CODEPOINTER pxpru16_prs32)(prs32);
typedef pru16      (CODEPOINTER pxpru16_pns32)(pns32);
typedef pru16      (CODEPOINTER pxpru16_u32)(u32);
typedef pru16      (CODEPOINTER pxpru16_pgu32)(pgu32);
typedef pru16      (CODEPOINTER pxpru16_pvu32)(pvu32);
typedef pru16      (CODEPOINTER pxpru16_pru32)(pru32);
typedef pru16      (CODEPOINTER pxpru16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu16                      // pnu16 Fn(arg)
typedef pnu16      (CODEPOINTER pxpnu16_void)(void);
typedef pnu16      (CODEPOINTER pxpnu16_pgvoid)(pgvoid);
typedef pnu16      (CODEPOINTER pxpnu16_pvvoid)(pvvoid);
typedef pnu16      (CODEPOINTER pxpnu16_prvoid)(prvoid);
typedef pnu16      (CODEPOINTER pxpnu16_pnvoid)(pnvoid);
typedef pnu16      (CODEPOINTER pxpnu16_flag)(flag);
typedef pnu16      (CODEPOINTER pxpnu16_pgflag)(pgflag);
typedef pnu16      (CODEPOINTER pxpnu16_pvflag)(pvflag);
typedef pnu16      (CODEPOINTER pxpnu16_prflag)(prflag);
typedef pnu16      (CODEPOINTER pxpnu16_pnflag)(pnflag);
typedef pnu16      (CODEPOINTER pxpnu16_s8)(s8);
typedef pnu16      (CODEPOINTER pxpnu16_pgs8)(pgs8);
typedef pnu16      (CODEPOINTER pxpnu16_pvs8)(pvs8);
typedef pnu16      (CODEPOINTER pxpnu16_prs8)(prs8);
typedef pnu16      (CODEPOINTER pxpnu16_pns8)(pns8);
typedef pnu16      (CODEPOINTER pxpnu16_u8)(u8);
typedef pnu16      (CODEPOINTER pxpnu16_pgu8)(pgu8);
typedef pnu16      (CODEPOINTER pxpnu16_pvu8)(pvu8);
typedef pnu16      (CODEPOINTER pxpnu16_pru8)(pru8);
typedef pnu16      (CODEPOINTER pxpnu16_pnu8)(pnu8);
typedef pnu16      (CODEPOINTER pxpnu16_s16)(s16);
typedef pnu16      (CODEPOINTER pxpnu16_pgs16)(pgs16);
typedef pnu16      (CODEPOINTER pxpnu16_pvs16)(pvs16);
typedef pnu16      (CODEPOINTER pxpnu16_prs16)(prs16);
typedef pnu16      (CODEPOINTER pxpnu16_pns16)(pns16);
typedef pnu16      (CODEPOINTER pxpnu16_u16)(u16);
typedef pnu16      (CODEPOINTER pxpnu16_pgu16)(pgu16);
typedef pnu16      (CODEPOINTER pxpnu16_pvu16)(pvu16);
typedef pnu16      (CODEPOINTER pxpnu16_pru16)(pru16);
typedef pnu16      (CODEPOINTER pxpnu16_pnu16)(pnu16);
typedef pnu16      (CODEPOINTER pxpnu16_s32)(s32);
typedef pnu16      (CODEPOINTER pxpnu16_pgs32)(pgs32);
typedef pnu16      (CODEPOINTER pxpnu16_pvs32)(pvs32);
typedef pnu16      (CODEPOINTER pxpnu16_prs32)(prs32);
typedef pnu16      (CODEPOINTER pxpnu16_pns32)(pns32);
typedef pnu16      (CODEPOINTER pxpnu16_u32)(u32);
typedef pnu16      (CODEPOINTER pxpnu16_pgu32)(pgu32);
typedef pnu16      (CODEPOINTER pxpnu16_pvu32)(pvu32);
typedef pnu16      (CODEPOINTER pxpnu16_pru32)(pru32);
typedef pnu16      (CODEPOINTER pxpnu16_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu16

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s32                      // s32 Fn(arg)
typedef s32        (CODEPOINTER pxs32_void)(void);
typedef s32        (CODEPOINTER pxs32_pgvoid)(pgvoid);
typedef s32        (CODEPOINTER pxs32_pvvoid)(pvvoid);
typedef s32        (CODEPOINTER pxs32_prvoid)(prvoid);
typedef s32        (CODEPOINTER pxs32_pnvoid)(pnvoid);
typedef s32        (CODEPOINTER pxs32_flag)(flag);
typedef s32        (CODEPOINTER pxs32_pgflag)(pgflag);
typedef s32        (CODEPOINTER pxs32_pvflag)(pvflag);
typedef s32        (CODEPOINTER pxs32_prflag)(prflag);
typedef s32        (CODEPOINTER pxs32_pnflag)(pnflag);
typedef s32        (CODEPOINTER pxs32_s8)(s8);
typedef s32        (CODEPOINTER pxs32_pgs8)(pgs8);
typedef s32        (CODEPOINTER pxs32_pvs8)(pvs8);
typedef s32        (CODEPOINTER pxs32_prs8)(prs8);
typedef s32        (CODEPOINTER pxs32_pns8)(pns8);
typedef s32        (CODEPOINTER pxs32_u8)(u8);
typedef s32        (CODEPOINTER pxs32_pgu8)(pgu8);
typedef s32        (CODEPOINTER pxs32_pvu8)(pvu8);
typedef s32        (CODEPOINTER pxs32_pru8)(pru8);
typedef s32        (CODEPOINTER pxs32_pnu8)(pnu8);
typedef s32        (CODEPOINTER pxs32_s16)(s16);
typedef s32        (CODEPOINTER pxs32_pgs16)(pgs16);
typedef s32        (CODEPOINTER pxs32_pvs16)(pvs16);
typedef s32        (CODEPOINTER pxs32_prs16)(prs16);
typedef s32        (CODEPOINTER pxs32_pns16)(pns16);
typedef s32        (CODEPOINTER pxs32_u16)(u16);
typedef s32        (CODEPOINTER pxs32_pgu16)(pgu16);
typedef s32        (CODEPOINTER pxs32_pvu16)(pvu16);
typedef s32        (CODEPOINTER pxs32_pru16)(pru16);
typedef s32        (CODEPOINTER pxs32_pnu16)(pnu16);
typedef s32        (CODEPOINTER pxs32_s32)(s32);
typedef s32        (CODEPOINTER pxs32_pgs32)(pgs32);
typedef s32        (CODEPOINTER pxs32_pvs32)(pvs32);
typedef s32        (CODEPOINTER pxs32_prs32)(prs32);
typedef s32        (CODEPOINTER pxs32_pns32)(pns32);
typedef s32        (CODEPOINTER pxs32_u32)(u32);
typedef s32        (CODEPOINTER pxs32_pgu32)(pgu32);
typedef s32        (CODEPOINTER pxs32_pvu32)(pvu32);
typedef s32        (CODEPOINTER pxs32_pru32)(pru32);
typedef s32        (CODEPOINTER pxs32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_s32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs32                      // pgs32 Fn(arg)
typedef pgs32      (CODEPOINTER pxpgs32_void)(void);
typedef pgs32      (CODEPOINTER pxpgs32_pgvoid)(pgvoid);
typedef pgs32      (CODEPOINTER pxpgs32_pvvoid)(pvvoid);
typedef pgs32      (CODEPOINTER pxpgs32_prvoid)(prvoid);
typedef pgs32      (CODEPOINTER pxpgs32_pnvoid)(pnvoid);
typedef pgs32      (CODEPOINTER pxpgs32_flag)(flag);
typedef pgs32      (CODEPOINTER pxpgs32_pgflag)(pgflag);
typedef pgs32      (CODEPOINTER pxpgs32_pvflag)(pvflag);
typedef pgs32      (CODEPOINTER pxpgs32_prflag)(prflag);
typedef pgs32      (CODEPOINTER pxpgs32_pnflag)(pnflag);
typedef pgs32      (CODEPOINTER pxpgs32_s8)(s8);
typedef pgs32      (CODEPOINTER pxpgs32_pgs8)(pgs8);
typedef pgs32      (CODEPOINTER pxpgs32_pvs8)(pvs8);
typedef pgs32      (CODEPOINTER pxpgs32_prs8)(prs8);
typedef pgs32      (CODEPOINTER pxpgs32_pns8)(pns8);
typedef pgs32      (CODEPOINTER pxpgs32_u8)(u8);
typedef pgs32      (CODEPOINTER pxpgs32_pgu8)(pgu8);
typedef pgs32      (CODEPOINTER pxpgs32_pvu8)(pvu8);
typedef pgs32      (CODEPOINTER pxpgs32_pru8)(pru8);
typedef pgs32      (CODEPOINTER pxpgs32_pnu8)(pnu8);
typedef pgs32      (CODEPOINTER pxpgs32_s16)(s16);
typedef pgs32      (CODEPOINTER pxpgs32_pgs16)(pgs16);
typedef pgs32      (CODEPOINTER pxpgs32_pvs16)(pvs16);
typedef pgs32      (CODEPOINTER pxpgs32_prs16)(prs16);
typedef pgs32      (CODEPOINTER pxpgs32_pns16)(pns16);
typedef pgs32      (CODEPOINTER pxpgs32_u16)(u16);
typedef pgs32      (CODEPOINTER pxpgs32_pgu16)(pgu16);
typedef pgs32      (CODEPOINTER pxpgs32_pvu16)(pvu16);
typedef pgs32      (CODEPOINTER pxpgs32_pru16)(pru16);
typedef pgs32      (CODEPOINTER pxpgs32_pnu16)(pnu16);
typedef pgs32      (CODEPOINTER pxpgs32_s32)(s32);
typedef pgs32      (CODEPOINTER pxpgs32_pgs32)(pgs32);
typedef pgs32      (CODEPOINTER pxpgs32_pvs32)(pvs32);
typedef pgs32      (CODEPOINTER pxpgs32_prs32)(prs32);
typedef pgs32      (CODEPOINTER pxpgs32_pns32)(pns32);
typedef pgs32      (CODEPOINTER pxpgs32_u32)(u32);
typedef pgs32      (CODEPOINTER pxpgs32_pgu32)(pgu32);
typedef pgs32      (CODEPOINTER pxpgs32_pvu32)(pvu32);
typedef pgs32      (CODEPOINTER pxpgs32_pru32)(pru32);
typedef pgs32      (CODEPOINTER pxpgs32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgs32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs32                      // pvs32 Fn(arg)
typedef pvs32      (CODEPOINTER pxpvs32_void)(void);
typedef pvs32      (CODEPOINTER pxpvs32_pgvoid)(pgvoid);
typedef pvs32      (CODEPOINTER pxpvs32_pvvoid)(pvvoid);
typedef pvs32      (CODEPOINTER pxpvs32_prvoid)(prvoid);
typedef pvs32      (CODEPOINTER pxpvs32_pnvoid)(pnvoid);
typedef pvs32      (CODEPOINTER pxpvs32_flag)(flag);
typedef pvs32      (CODEPOINTER pxpvs32_pgflag)(pgflag);
typedef pvs32      (CODEPOINTER pxpvs32_pvflag)(pvflag);
typedef pvs32      (CODEPOINTER pxpvs32_prflag)(prflag);
typedef pvs32      (CODEPOINTER pxpvs32_pnflag)(pnflag);
typedef pvs32      (CODEPOINTER pxpvs32_s8)(s8);
typedef pvs32      (CODEPOINTER pxpvs32_pgs8)(pgs8);
typedef pvs32      (CODEPOINTER pxpvs32_pvs8)(pvs8);
typedef pvs32      (CODEPOINTER pxpvs32_prs8)(prs8);
typedef pvs32      (CODEPOINTER pxpvs32_pns8)(pns8);
typedef pvs32      (CODEPOINTER pxpvs32_u8)(u8);
typedef pvs32      (CODEPOINTER pxpvs32_pgu8)(pgu8);
typedef pvs32      (CODEPOINTER pxpvs32_pvu8)(pvu8);
typedef pvs32      (CODEPOINTER pxpvs32_pru8)(pru8);
typedef pvs32      (CODEPOINTER pxpvs32_pnu8)(pnu8);
typedef pvs32      (CODEPOINTER pxpvs32_s16)(s16);
typedef pvs32      (CODEPOINTER pxpvs32_pgs16)(pgs16);
typedef pvs32      (CODEPOINTER pxpvs32_pvs16)(pvs16);
typedef pvs32      (CODEPOINTER pxpvs32_prs16)(prs16);
typedef pvs32      (CODEPOINTER pxpvs32_pns16)(pns16);
typedef pvs32      (CODEPOINTER pxpvs32_u16)(u16);
typedef pvs32      (CODEPOINTER pxpvs32_pgu16)(pgu16);
typedef pvs32      (CODEPOINTER pxpvs32_pvu16)(pvu16);
typedef pvs32      (CODEPOINTER pxpvs32_pru16)(pru16);
typedef pvs32      (CODEPOINTER pxpvs32_pnu16)(pnu16);
typedef pvs32      (CODEPOINTER pxpvs32_s32)(s32);
typedef pvs32      (CODEPOINTER pxpvs32_pgs32)(pgs32);
typedef pvs32      (CODEPOINTER pxpvs32_pvs32)(pvs32);
typedef pvs32      (CODEPOINTER pxpvs32_prs32)(prs32);
typedef pvs32      (CODEPOINTER pxpvs32_pns32)(pns32);
typedef pvs32      (CODEPOINTER pxpvs32_u32)(u32);
typedef pvs32      (CODEPOINTER pxpvs32_pgu32)(pgu32);
typedef pvs32      (CODEPOINTER pxpvs32_pvu32)(pvu32);
typedef pvs32      (CODEPOINTER pxpvs32_pru32)(pru32);
typedef pvs32      (CODEPOINTER pxpvs32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvs32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs32                      // prs32 Fn(arg)
typedef prs32      (CODEPOINTER pxprs32_void)(void);
typedef prs32      (CODEPOINTER pxprs32_pgvoid)(pgvoid);
typedef prs32      (CODEPOINTER pxprs32_pvvoid)(pvvoid);
typedef prs32      (CODEPOINTER pxprs32_prvoid)(prvoid);
typedef prs32      (CODEPOINTER pxprs32_pnvoid)(pnvoid);
typedef prs32      (CODEPOINTER pxprs32_flag)(flag);
typedef prs32      (CODEPOINTER pxprs32_pgflag)(pgflag);
typedef prs32      (CODEPOINTER pxprs32_pvflag)(pvflag);
typedef prs32      (CODEPOINTER pxprs32_prflag)(prflag);
typedef prs32      (CODEPOINTER pxprs32_pnflag)(pnflag);
typedef prs32      (CODEPOINTER pxprs32_s8)(s8);
typedef prs32      (CODEPOINTER pxprs32_pgs8)(pgs8);
typedef prs32      (CODEPOINTER pxprs32_pvs8)(pvs8);
typedef prs32      (CODEPOINTER pxprs32_prs8)(prs8);
typedef prs32      (CODEPOINTER pxprs32_pns8)(pns8);
typedef prs32      (CODEPOINTER pxprs32_u8)(u8);
typedef prs32      (CODEPOINTER pxprs32_pgu8)(pgu8);
typedef prs32      (CODEPOINTER pxprs32_pvu8)(pvu8);
typedef prs32      (CODEPOINTER pxprs32_pru8)(pru8);
typedef prs32      (CODEPOINTER pxprs32_pnu8)(pnu8);
typedef prs32      (CODEPOINTER pxprs32_s16)(s16);
typedef prs32      (CODEPOINTER pxprs32_pgs16)(pgs16);
typedef prs32      (CODEPOINTER pxprs32_pvs16)(pvs16);
typedef prs32      (CODEPOINTER pxprs32_prs16)(prs16);
typedef prs32      (CODEPOINTER pxprs32_pns16)(pns16);
typedef prs32      (CODEPOINTER pxprs32_u16)(u16);
typedef prs32      (CODEPOINTER pxprs32_pgu16)(pgu16);
typedef prs32      (CODEPOINTER pxprs32_pvu16)(pvu16);
typedef prs32      (CODEPOINTER pxprs32_pru16)(pru16);
typedef prs32      (CODEPOINTER pxprs32_pnu16)(pnu16);
typedef prs32      (CODEPOINTER pxprs32_s32)(s32);
typedef prs32      (CODEPOINTER pxprs32_pgs32)(pgs32);
typedef prs32      (CODEPOINTER pxprs32_pvs32)(pvs32);
typedef prs32      (CODEPOINTER pxprs32_prs32)(prs32);
typedef prs32      (CODEPOINTER pxprs32_pns32)(pns32);
typedef prs32      (CODEPOINTER pxprs32_u32)(u32);
typedef prs32      (CODEPOINTER pxprs32_pgu32)(pgu32);
typedef prs32      (CODEPOINTER pxprs32_pvu32)(pvu32);
typedef prs32      (CODEPOINTER pxprs32_pru32)(pru32);
typedef prs32      (CODEPOINTER pxprs32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_prs32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns32                      // pns32 Fn(arg)
typedef pns32      (CODEPOINTER pxpns32_void)(void);
typedef pns32      (CODEPOINTER pxpns32_pgvoid)(pgvoid);
typedef pns32      (CODEPOINTER pxpns32_pvvoid)(pvvoid);
typedef pns32      (CODEPOINTER pxpns32_prvoid)(prvoid);
typedef pns32      (CODEPOINTER pxpns32_pnvoid)(pnvoid);
typedef pns32      (CODEPOINTER pxpns32_flag)(flag);
typedef pns32      (CODEPOINTER pxpns32_pgflag)(pgflag);
typedef pns32      (CODEPOINTER pxpns32_pvflag)(pvflag);
typedef pns32      (CODEPOINTER pxpns32_prflag)(prflag);
typedef pns32      (CODEPOINTER pxpns32_pnflag)(pnflag);
typedef pns32      (CODEPOINTER pxpns32_s8)(s8);
typedef pns32      (CODEPOINTER pxpns32_pgs8)(pgs8);
typedef pns32      (CODEPOINTER pxpns32_pvs8)(pvs8);
typedef pns32      (CODEPOINTER pxpns32_prs8)(prs8);
typedef pns32      (CODEPOINTER pxpns32_pns8)(pns8);
typedef pns32      (CODEPOINTER pxpns32_u8)(u8);
typedef pns32      (CODEPOINTER pxpns32_pgu8)(pgu8);
typedef pns32      (CODEPOINTER pxpns32_pvu8)(pvu8);
typedef pns32      (CODEPOINTER pxpns32_pru8)(pru8);
typedef pns32      (CODEPOINTER pxpns32_pnu8)(pnu8);
typedef pns32      (CODEPOINTER pxpns32_s16)(s16);
typedef pns32      (CODEPOINTER pxpns32_pgs16)(pgs16);
typedef pns32      (CODEPOINTER pxpns32_pvs16)(pvs16);
typedef pns32      (CODEPOINTER pxpns32_prs16)(prs16);
typedef pns32      (CODEPOINTER pxpns32_pns16)(pns16);
typedef pns32      (CODEPOINTER pxpns32_u16)(u16);
typedef pns32      (CODEPOINTER pxpns32_pgu16)(pgu16);
typedef pns32      (CODEPOINTER pxpns32_pvu16)(pvu16);
typedef pns32      (CODEPOINTER pxpns32_pru16)(pru16);
typedef pns32      (CODEPOINTER pxpns32_pnu16)(pnu16);
typedef pns32      (CODEPOINTER pxpns32_s32)(s32);
typedef pns32      (CODEPOINTER pxpns32_pgs32)(pgs32);
typedef pns32      (CODEPOINTER pxpns32_pvs32)(pvs32);
typedef pns32      (CODEPOINTER pxpns32_prs32)(prs32);
typedef pns32      (CODEPOINTER pxpns32_pns32)(pns32);
typedef pns32      (CODEPOINTER pxpns32_u32)(u32);
typedef pns32      (CODEPOINTER pxpns32_pgu32)(pgu32);
typedef pns32      (CODEPOINTER pxpns32_pvu32)(pvu32);
typedef pns32      (CODEPOINTER pxpns32_pru32)(pru32);
typedef pns32      (CODEPOINTER pxpns32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pns32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u32                      // u32 Fn(arg)
typedef u32        (CODEPOINTER pxu32_void)(void);
typedef u32        (CODEPOINTER pxu32_pgvoid)(pgvoid);
typedef u32        (CODEPOINTER pxu32_pvvoid)(pvvoid);
typedef u32        (CODEPOINTER pxu32_prvoid)(prvoid);
typedef u32        (CODEPOINTER pxu32_pnvoid)(pnvoid);
typedef u32        (CODEPOINTER pxu32_flag)(flag);
typedef u32        (CODEPOINTER pxu32_pgflag)(pgflag);
typedef u32        (CODEPOINTER pxu32_pvflag)(pvflag);
typedef u32        (CODEPOINTER pxu32_prflag)(prflag);
typedef u32        (CODEPOINTER pxu32_pnflag)(pnflag);
typedef u32        (CODEPOINTER pxu32_s8)(s8);
typedef u32        (CODEPOINTER pxu32_pgs8)(pgs8);
typedef u32        (CODEPOINTER pxu32_pvs8)(pvs8);
typedef u32        (CODEPOINTER pxu32_prs8)(prs8);
typedef u32        (CODEPOINTER pxu32_pns8)(pns8);
typedef u32        (CODEPOINTER pxu32_u8)(u8);
typedef u32        (CODEPOINTER pxu32_pgu8)(pgu8);
typedef u32        (CODEPOINTER pxu32_pvu8)(pvu8);
typedef u32        (CODEPOINTER pxu32_pru8)(pru8);
typedef u32        (CODEPOINTER pxu32_pnu8)(pnu8);
typedef u32        (CODEPOINTER pxu32_s16)(s16);
typedef u32        (CODEPOINTER pxu32_pgs16)(pgs16);
typedef u32        (CODEPOINTER pxu32_pvs16)(pvs16);
typedef u32        (CODEPOINTER pxu32_prs16)(prs16);
typedef u32        (CODEPOINTER pxu32_pns16)(pns16);
typedef u32        (CODEPOINTER pxu32_u16)(u16);
typedef u32        (CODEPOINTER pxu32_pgu16)(pgu16);
typedef u32        (CODEPOINTER pxu32_pvu16)(pvu16);
typedef u32        (CODEPOINTER pxu32_pru16)(pru16);
typedef u32        (CODEPOINTER pxu32_pnu16)(pnu16);
typedef u32        (CODEPOINTER pxu32_s32)(s32);
typedef u32        (CODEPOINTER pxu32_pgs32)(pgs32);
typedef u32        (CODEPOINTER pxu32_pvs32)(pvs32);
typedef u32        (CODEPOINTER pxu32_prs32)(prs32);
typedef u32        (CODEPOINTER pxu32_pns32)(pns32);
typedef u32        (CODEPOINTER pxu32_u32)(u32);
typedef u32        (CODEPOINTER pxu32_pgu32)(pgu32);
typedef u32        (CODEPOINTER pxu32_pvu32)(pvu32);
typedef u32        (CODEPOINTER pxu32_pru32)(pru32);
typedef u32        (CODEPOINTER pxu32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_u32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu32                      // pgu32 Fn(arg)
typedef pgu32      (CODEPOINTER pxpgu32_void)(void);
typedef pgu32      (CODEPOINTER pxpgu32_pgvoid)(pgvoid);
typedef pgu32      (CODEPOINTER pxpgu32_pvvoid)(pvvoid);
typedef pgu32      (CODEPOINTER pxpgu32_prvoid)(prvoid);
typedef pgu32      (CODEPOINTER pxpgu32_pnvoid)(pnvoid);
typedef pgu32      (CODEPOINTER pxpgu32_flag)(flag);
typedef pgu32      (CODEPOINTER pxpgu32_pgflag)(pgflag);
typedef pgu32      (CODEPOINTER pxpgu32_pvflag)(pvflag);
typedef pgu32      (CODEPOINTER pxpgu32_prflag)(prflag);
typedef pgu32      (CODEPOINTER pxpgu32_pnflag)(pnflag);
typedef pgu32      (CODEPOINTER pxpgu32_s8)(s8);
typedef pgu32      (CODEPOINTER pxpgu32_pgs8)(pgs8);
typedef pgu32      (CODEPOINTER pxpgu32_pvs8)(pvs8);
typedef pgu32      (CODEPOINTER pxpgu32_prs8)(prs8);
typedef pgu32      (CODEPOINTER pxpgu32_pns8)(pns8);
typedef pgu32      (CODEPOINTER pxpgu32_u8)(u8);
typedef pgu32      (CODEPOINTER pxpgu32_pgu8)(pgu8);
typedef pgu32      (CODEPOINTER pxpgu32_pvu8)(pvu8);
typedef pgu32      (CODEPOINTER pxpgu32_pru8)(pru8);
typedef pgu32      (CODEPOINTER pxpgu32_pnu8)(pnu8);
typedef pgu32      (CODEPOINTER pxpgu32_s16)(s16);
typedef pgu32      (CODEPOINTER pxpgu32_pgs16)(pgs16);
typedef pgu32      (CODEPOINTER pxpgu32_pvs16)(pvs16);
typedef pgu32      (CODEPOINTER pxpgu32_prs16)(prs16);
typedef pgu32      (CODEPOINTER pxpgu32_pns16)(pns16);
typedef pgu32      (CODEPOINTER pxpgu32_u16)(u16);
typedef pgu32      (CODEPOINTER pxpgu32_pgu16)(pgu16);
typedef pgu32      (CODEPOINTER pxpgu32_pvu16)(pvu16);
typedef pgu32      (CODEPOINTER pxpgu32_pru16)(pru16);
typedef pgu32      (CODEPOINTER pxpgu32_pnu16)(pnu16);
typedef pgu32      (CODEPOINTER pxpgu32_s32)(s32);
typedef pgu32      (CODEPOINTER pxpgu32_pgs32)(pgs32);
typedef pgu32      (CODEPOINTER pxpgu32_pvs32)(pvs32);
typedef pgu32      (CODEPOINTER pxpgu32_prs32)(prs32);
typedef pgu32      (CODEPOINTER pxpgu32_pns32)(pns32);
typedef pgu32      (CODEPOINTER pxpgu32_u32)(u32);
typedef pgu32      (CODEPOINTER pxpgu32_pgu32)(pgu32);
typedef pgu32      (CODEPOINTER pxpgu32_pvu32)(pvu32);
typedef pgu32      (CODEPOINTER pxpgu32_pru32)(pru32);
typedef pgu32      (CODEPOINTER pxpgu32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pgu32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu32                      // pvu32 Fn(arg)
typedef pvu32      (CODEPOINTER pxpvu32_void)(void);
typedef pvu32      (CODEPOINTER pxpvu32_pgvoid)(pgvoid);
typedef pvu32      (CODEPOINTER pxpvu32_pvvoid)(pvvoid);
typedef pvu32      (CODEPOINTER pxpvu32_prvoid)(prvoid);
typedef pvu32      (CODEPOINTER pxpvu32_pnvoid)(pnvoid);
typedef pvu32      (CODEPOINTER pxpvu32_flag)(flag);
typedef pvu32      (CODEPOINTER pxpvu32_pgflag)(pgflag);
typedef pvu32      (CODEPOINTER pxpvu32_pvflag)(pvflag);
typedef pvu32      (CODEPOINTER pxpvu32_prflag)(prflag);
typedef pvu32      (CODEPOINTER pxpvu32_pnflag)(pnflag);
typedef pvu32      (CODEPOINTER pxpvu32_s8)(s8);
typedef pvu32      (CODEPOINTER pxpvu32_pgs8)(pgs8);
typedef pvu32      (CODEPOINTER pxpvu32_pvs8)(pvs8);
typedef pvu32      (CODEPOINTER pxpvu32_prs8)(prs8);
typedef pvu32      (CODEPOINTER pxpvu32_pns8)(pns8);
typedef pvu32      (CODEPOINTER pxpvu32_u8)(u8);
typedef pvu32      (CODEPOINTER pxpvu32_pgu8)(pgu8);
typedef pvu32      (CODEPOINTER pxpvu32_pvu8)(pvu8);
typedef pvu32      (CODEPOINTER pxpvu32_pru8)(pru8);
typedef pvu32      (CODEPOINTER pxpvu32_pnu8)(pnu8);
typedef pvu32      (CODEPOINTER pxpvu32_s16)(s16);
typedef pvu32      (CODEPOINTER pxpvu32_pgs16)(pgs16);
typedef pvu32      (CODEPOINTER pxpvu32_pvs16)(pvs16);
typedef pvu32      (CODEPOINTER pxpvu32_prs16)(prs16);
typedef pvu32      (CODEPOINTER pxpvu32_pns16)(pns16);
typedef pvu32      (CODEPOINTER pxpvu32_u16)(u16);
typedef pvu32      (CODEPOINTER pxpvu32_pgu16)(pgu16);
typedef pvu32      (CODEPOINTER pxpvu32_pvu16)(pvu16);
typedef pvu32      (CODEPOINTER pxpvu32_pru16)(pru16);
typedef pvu32      (CODEPOINTER pxpvu32_pnu16)(pnu16);
typedef pvu32      (CODEPOINTER pxpvu32_s32)(s32);
typedef pvu32      (CODEPOINTER pxpvu32_pgs32)(pgs32);
typedef pvu32      (CODEPOINTER pxpvu32_pvs32)(pvs32);
typedef pvu32      (CODEPOINTER pxpvu32_prs32)(prs32);
typedef pvu32      (CODEPOINTER pxpvu32_pns32)(pns32);
typedef pvu32      (CODEPOINTER pxpvu32_u32)(u32);
typedef pvu32      (CODEPOINTER pxpvu32_pgu32)(pgu32);
typedef pvu32      (CODEPOINTER pxpvu32_pvu32)(pvu32);
typedef pvu32      (CODEPOINTER pxpvu32_pru32)(pru32);
typedef pvu32      (CODEPOINTER pxpvu32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pvu32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru32                      // pru32 Fn(arg)
typedef pru32      (CODEPOINTER pxpru32_void)(void);
typedef pru32      (CODEPOINTER pxpru32_pgvoid)(pgvoid);
typedef pru32      (CODEPOINTER pxpru32_pvvoid)(pvvoid);
typedef pru32      (CODEPOINTER pxpru32_prvoid)(prvoid);
typedef pru32      (CODEPOINTER pxpru32_pnvoid)(pnvoid);
typedef pru32      (CODEPOINTER pxpru32_flag)(flag);
typedef pru32      (CODEPOINTER pxpru32_pgflag)(pgflag);
typedef pru32      (CODEPOINTER pxpru32_pvflag)(pvflag);
typedef pru32      (CODEPOINTER pxpru32_prflag)(prflag);
typedef pru32      (CODEPOINTER pxpru32_pnflag)(pnflag);
typedef pru32      (CODEPOINTER pxpru32_s8)(s8);
typedef pru32      (CODEPOINTER pxpru32_pgs8)(pgs8);
typedef pru32      (CODEPOINTER pxpru32_pvs8)(pvs8);
typedef pru32      (CODEPOINTER pxpru32_prs8)(prs8);
typedef pru32      (CODEPOINTER pxpru32_pns8)(pns8);
typedef pru32      (CODEPOINTER pxpru32_u8)(u8);
typedef pru32      (CODEPOINTER pxpru32_pgu8)(pgu8);
typedef pru32      (CODEPOINTER pxpru32_pvu8)(pvu8);
typedef pru32      (CODEPOINTER pxpru32_pru8)(pru8);
typedef pru32      (CODEPOINTER pxpru32_pnu8)(pnu8);
typedef pru32      (CODEPOINTER pxpru32_s16)(s16);
typedef pru32      (CODEPOINTER pxpru32_pgs16)(pgs16);
typedef pru32      (CODEPOINTER pxpru32_pvs16)(pvs16);
typedef pru32      (CODEPOINTER pxpru32_prs16)(prs16);
typedef pru32      (CODEPOINTER pxpru32_pns16)(pns16);
typedef pru32      (CODEPOINTER pxpru32_u16)(u16);
typedef pru32      (CODEPOINTER pxpru32_pgu16)(pgu16);
typedef pru32      (CODEPOINTER pxpru32_pvu16)(pvu16);
typedef pru32      (CODEPOINTER pxpru32_pru16)(pru16);
typedef pru32      (CODEPOINTER pxpru32_pnu16)(pnu16);
typedef pru32      (CODEPOINTER pxpru32_s32)(s32);
typedef pru32      (CODEPOINTER pxpru32_pgs32)(pgs32);
typedef pru32      (CODEPOINTER pxpru32_pvs32)(pvs32);
typedef pru32      (CODEPOINTER pxpru32_prs32)(prs32);
typedef pru32      (CODEPOINTER pxpru32_pns32)(pns32);
typedef pru32      (CODEPOINTER pxpru32_u32)(u32);
typedef pru32      (CODEPOINTER pxpru32_pgu32)(pgu32);
typedef pru32      (CODEPOINTER pxpru32_pvu32)(pvu32);
typedef pru32      (CODEPOINTER pxpru32_pru32)(pru32);
typedef pru32      (CODEPOINTER pxpru32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pru32

#ifdef __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu32                      // pnu32 Fn(arg)
typedef pnu32      (CODEPOINTER pxpnu32_void)(void);
typedef pnu32      (CODEPOINTER pxpnu32_pgvoid)(pgvoid);
typedef pnu32      (CODEPOINTER pxpnu32_pvvoid)(pvvoid);
typedef pnu32      (CODEPOINTER pxpnu32_prvoid)(prvoid);
typedef pnu32      (CODEPOINTER pxpnu32_pnvoid)(pnvoid);
typedef pnu32      (CODEPOINTER pxpnu32_flag)(flag);
typedef pnu32      (CODEPOINTER pxpnu32_pgflag)(pgflag);
typedef pnu32      (CODEPOINTER pxpnu32_pvflag)(pvflag);
typedef pnu32      (CODEPOINTER pxpnu32_prflag)(prflag);
typedef pnu32      (CODEPOINTER pxpnu32_pnflag)(pnflag);
typedef pnu32      (CODEPOINTER pxpnu32_s8)(s8);
typedef pnu32      (CODEPOINTER pxpnu32_pgs8)(pgs8);
typedef pnu32      (CODEPOINTER pxpnu32_pvs8)(pvs8);
typedef pnu32      (CODEPOINTER pxpnu32_prs8)(prs8);
typedef pnu32      (CODEPOINTER pxpnu32_pns8)(pns8);
typedef pnu32      (CODEPOINTER pxpnu32_u8)(u8);
typedef pnu32      (CODEPOINTER pxpnu32_pgu8)(pgu8);
typedef pnu32      (CODEPOINTER pxpnu32_pvu8)(pvu8);
typedef pnu32      (CODEPOINTER pxpnu32_pru8)(pru8);
typedef pnu32      (CODEPOINTER pxpnu32_pnu8)(pnu8);
typedef pnu32      (CODEPOINTER pxpnu32_s16)(s16);
typedef pnu32      (CODEPOINTER pxpnu32_pgs16)(pgs16);
typedef pnu32      (CODEPOINTER pxpnu32_pvs16)(pvs16);
typedef pnu32      (CODEPOINTER pxpnu32_prs16)(prs16);
typedef pnu32      (CODEPOINTER pxpnu32_pns16)(pns16);
typedef pnu32      (CODEPOINTER pxpnu32_u16)(u16);
typedef pnu32      (CODEPOINTER pxpnu32_pgu16)(pgu16);
typedef pnu32      (CODEPOINTER pxpnu32_pvu16)(pvu16);
typedef pnu32      (CODEPOINTER pxpnu32_pru16)(pru16);
typedef pnu32      (CODEPOINTER pxpnu32_pnu16)(pnu16);
typedef pnu32      (CODEPOINTER pxpnu32_s32)(s32);
typedef pnu32      (CODEPOINTER pxpnu32_pgs32)(pgs32);
typedef pnu32      (CODEPOINTER pxpnu32_pvs32)(pvs32);
typedef pnu32      (CODEPOINTER pxpnu32_prs32)(prs32);
typedef pnu32      (CODEPOINTER pxpnu32_pns32)(pns32);
typedef pnu32      (CODEPOINTER pxpnu32_u32)(u32);
typedef pnu32      (CODEPOINTER pxpnu32_pgu32)(pgu32);
typedef pnu32      (CODEPOINTER pxpnu32_pvu32)(pvu32);
typedef pnu32      (CODEPOINTER pxpnu32_pru32)(pru32);
typedef pnu32      (CODEPOINTER pxpnu32_pnu32)(pnu32);
#endif // __DL_TYPE_INCLUDE_FUNCTIONS_RETURNING_pnu32


#endif // __DL_TYPE_H

// #############################################################################
// # EOF $Workfile: dl_type.h $
