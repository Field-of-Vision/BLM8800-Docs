#ifndef _REG_TRNG_H_
#define _REG_TRNG_H_

#include "chip.h"

typedef struct
{
  __IO uint32_t                    trng_en;                      //0x00000000
  __IO uint32_t                    trng_status;                  //0x00000004
  __IO uint32_t                    trng_data;                    //0x00000008
  __IO uint32_t Reserved_0000000C;              //0x0000000C
  __IO uint32_t                    trng_div_dly;                 //0x00000010
  __IO uint32_t                    trng_sel;                     //0x00000014
} AIC_TRNG_TypeDef;

static AIC_TRNG_TypeDef * const AIC_TRNG = ((AIC_TRNG_TypeDef *)AIC_TRNG_BASE);

//trng_en
#define TRNG_STRNGENQ                   (1<<2)
#define TRNG_STRNGENQ_POS               (2)
#define TRNG_STRNGIEQ                   (1<<3)
#define TRNG_STRNGIEQ_POS               (3)
#define TRNG_STRNGEEQ                   (1<<4)
#define TRNG_STRNGEEQ_POS               (4)

//trng_status
#define TRNG_SDRDYQ                     (1<<0)
#define TRNG_SDRDYQ_POS                 (0)
#define TRNG_SSECSQ                     (1<<2)
#define TRNG_SSECSQ_POS                 (2)
#define TRNG_SSEISQ                     (1<<6)
#define TRNG_SSEISQ_POS                 (6)

//trng_data
#define TRNG_SDRQ(n)                    (((n)&0xFFFFFFFF)<<0)
#define TRNG_SDRQ_LSB                   (0)
#define TRNG_SDRQ_MASK                  (0xFFFFFFFF<<0)

//trng_div_dly
#define TRNG_SDIVNUMQ(n)                (((n)&0xFF)<<0)
#define TRNG_SDIVNUMQ_LSB               (0)
#define TRNG_SDIVNUMQ_MASK              (0xFF<<0)
#define TRNG_SDIVHIGHQ(n)               (((n)&0xFF)<<8)
#define TRNG_SDIVHIGHQ_LSB              (8)
#define TRNG_SDIVHIGHQ_MASK             (0xFF<<8)
#define TRNG_SDLYNUMQ(n)                (((n)&0xFF)<<16)
#define TRNG_SDLYNUMQ_LSB               (16)
#define TRNG_SDLYNUMQ_MASK              (0xFF<<16)

//trng_sel
#define TRNG_STRNGSEL0Q(n)              (((n)&0xFF)<<0)
#define TRNG_STRNGSEL0Q_LSB             (0)
#define TRNG_STRNGSEL0Q_MASK            (0xFF<<0)
#define TRNG_STRNGSEL1Q(n)              (((n)&0xFF)<<8)
#define TRNG_STRNGSEL1Q_LSB             (8)
#define TRNG_STRNGSEL1Q_MASK            (0xFF<<8)
#define TRNG_SLFSRGEN0Q(n)              (((n)&0xFF)<<16)
#define TRNG_SLFSRGEN0Q_LSB             (16)
#define TRNG_SLFSRGEN0Q_MASK            (0xFF<<16)
#define TRNG_SLFSRGEN1Q(n)              (((n)&0xFF)<<24)
#define TRNG_SLFSRGEN1Q_LSB             (24)
#define TRNG_SLFSRGEN1Q_MASK            (0xFF<<24)

#endif /* _REG_TRNG_H_ */
