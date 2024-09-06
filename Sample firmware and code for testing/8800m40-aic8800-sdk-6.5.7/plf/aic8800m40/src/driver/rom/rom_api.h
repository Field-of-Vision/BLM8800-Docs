#ifndef _ROM_API_H_
#define _ROM_API_H_

#include "chip.h"

/**
 * Macros
 */

#define ROM_APITBL_BASE                 ((unsigned int *)(AIC_ROM_BASE + 0x00000198UL))
#define ROM_FUNC(idx,type)              ((type)ROM_APITBL_BASE[(idx)])

#define ROM_CRC16TBL_BASE               ((unsigned int *)(AIC_ROM_BASE + 0x00000220UL))
#define ROM_CRC32TBL_BASE               ((unsigned int *)(AIC_ROM_BASE + 0x00000420UL))

/**
 * APIs
 */

#define ROM_SystemClkSelSet(args...)        ROM_FUNC( 0, void (*)(int tgt, unsigned int sel))(args)
#define ROM_SystemClkDivSet(args...)        ROM_FUNC( 1, void (*)(int tgt, unsigned int div))(args)
#define ROM_SystemCPUSysRamConfig(args...)  ROM_FUNC( 2, void (*)(unsigned int val))(args)
#define ROM_SystemClkRecover(args...)       ROM_FUNC( 3, void (*)(void))(args)
#define ROM_FlashBootPrepare(args...)       ROM_FUNC( 4, int (*)(void))(args)
#define ROM_PsimInit(args...)               ROM_FUNC( 5, void (*)(void))(args)
#define ROM_PsimRead(args...)               ROM_FUNC( 6, unsigned int (*)(unsigned int adr))(args)
#define ROM_PsimWrite(args...)              ROM_FUNC( 7, void (*)(unsigned int adr, unsigned int dat))(args)
#define ROM_PsimMaskWrite(args...)          ROM_FUNC( 8, void (*)(unsigned int adr, unsigned int dat, unsigned int msk))(args)
#define ROM_FlashInit(args...)              ROM_FUNC( 9, int (*)(void))(args)
#define ROM_FlashCacheInit(args...)         ROM_FUNC(10, int (*)(void))(args)
#define ROM_FlashChipIdGet(args...)         ROM_FUNC(11, unsigned int (*)(void))(args)
#define ROM_FlashChipSizeGet(args...)       ROM_FUNC(12, unsigned int (*)(void))(args)
#define ROM_FlashChipErase(args...)         ROM_FUNC(13, void (*)(void))(args)
#define ROM_FlashErase(args...)             ROM_FUNC(14, int (*)(unsigned int a4k, unsigned int len))(args)
#define ROM_FlashWrite(args...)             ROM_FUNC(15, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashRead(args...)              ROM_FUNC(16, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashCacheInvalidAll(args...)   ROM_FUNC(17, void (*)(void))(args)
#define ROM_FlashCacheInvalidRange(args...) ROM_FUNC(18, void (*)(unsigned int adr, unsigned int len))(args)
#define ROM_FlashOTPMemoryErase(args...)    ROM_FUNC(19, int (*)(unsigned int adr))(args)
#define ROM_FlashOTPMemoryWrite(args...)    ROM_FUNC(20, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashOTPMemoryRead(args...)     ROM_FUNC(21, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashOTPMemoryLock(args...)     ROM_FUNC(22, unsigned int (*)(unsigned int lck))(args)
#define ROM_CRC16Calc(args...)              ROM_FUNC(23, unsigned short (*)(const unsigned char *buf, unsigned int len))(args)
#define ROM_CRC32Calc(args...)              ROM_FUNC(24, unsigned int (*)(const unsigned char *buf, unsigned int len))(args)

#endif /* _ROM_API_H_ */
