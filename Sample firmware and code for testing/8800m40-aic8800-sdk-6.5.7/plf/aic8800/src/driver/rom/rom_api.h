#ifndef _ROM_API_H_
#define _ROM_API_H_

#include "chip.h"

/**
 * Macros
 */

#define ROM_APITBL_BASE                 ((unsigned int *)(AIC_ROM_BASE + 0x00000180UL))
#define ROM_FUNC(idx,type)              ((type)ROM_APITBL_BASE[(idx)])

/**
 * APIs
 */

#define ROM_SystemClkSelSet(args...)        ROM_FUNC( 0, void (*)(int tgt, unsigned int sel))(args)
#define ROM_SystemClkDivSet(args...)        ROM_FUNC( 1, void (*)(int tgt, unsigned int div))(args)
#define ROM_FlashChipSizeGet(args...)       ROM_FUNC( 2, unsigned int (*)(void))(args)
#define ROM_FlashChipErase(args...)         ROM_FUNC( 3, void (*)(void))(args)
#define ROM_FlashErase(args...)             ROM_FUNC( 4, int (*)(unsigned int a4k, unsigned int len))(args)
#define ROM_FlashWrite(args...)             ROM_FUNC( 5, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashRead(args...)              ROM_FUNC( 6, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashCacheInvalidAll(args...)   ROM_FUNC( 7, void (*)(void))(args)
#define ROM_FlashCacheInvalidRange(args...) ROM_FUNC( 8, void (*)(unsigned int adr, unsigned int len))(args)
#define ROM_FlashOTPMemoryErase(args...)    ROM_FUNC(11, int (*)(unsigned int adr))(args)
#define ROM_FlashOTPMemoryWrite(args...)    ROM_FUNC(12, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashOTPMemoryRead(args...)     ROM_FUNC(13, int (*)(unsigned int adr, unsigned int len, unsigned int buf))(args)
#define ROM_FlashOTPMemoryLock(args...)     ROM_FUNC(14, unsigned int (*)(unsigned int lck))(args)

#define ROM_FlashCRC32_U02                  ((unsigned int (*)(unsigned char *adr, unsigned int len)) \
                                             ((unsigned int *)0x0000807BUL))
#define ROM_FlashCRC32_U03                  ((unsigned int (*)(unsigned char *adr, unsigned int len)) \
                                             ((unsigned int *)0x000081DFUL))
#define ROM_FlashCRC32_U04                  ((unsigned int (*)(unsigned char *adr, unsigned int len)) \
                                             ROM_APITBL_BASE[31])
#define ROM_FlashCRC32x(v,...)              MCAT(ROM_FlashCRC32_U0, v)(__VA_ARGS__)
#if defined(CFG_BOOT_ROM_VER) && (CFG_BOOT_ROM_VER == 4)
#define ROM_FlashCRC32(...)                 ROM_FlashCRC32x(4, __VA_ARGS__)
#else
#define ROM_FlashCRC32(...)                 ROM_FlashCRC32x(CFG_ROM_VER, __VA_ARGS__)
#endif

#endif /* _ROM_API_H_ */
