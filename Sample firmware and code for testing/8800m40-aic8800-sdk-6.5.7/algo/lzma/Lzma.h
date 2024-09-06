#ifndef _LZMA_H_
#define _LZMA_H_

#include "7zTypes.h"
EXTERN_C_BEGIN
int lzma_upgrade(const u32 input_addr, const u32 input_len, const u32 output_addr, const u32 output_len);
EXTERN_C_END

#endif


