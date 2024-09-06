#ifndef _REG_WDT_H_
#define _REG_WDT_H_

#include "chip.h"

typedef volatile struct
{
  __IO uint32_t LOAD;                       //0x00000000
  __IO uint32_t VALUE;                      //0x00000004
  __IO uint32_t CTRL;                       //0x00000008
  __O  uint32_t INT_CLR;                    //0x0000000C
  __I  uint32_t INT_RAW;                    //0x00000010
  __IO uint32_t INT_MASK;                   //0x00000014
  __I  uint32_t RESERVED0[762];
  __IO uint32_t LOCK;                       //0x00000C00
} AIC_WDT_TypeDef;

static AIC_WDT_TypeDef * const AIC_WDT0 = ((AIC_WDT_TypeDef *)AIC_WDT0_BASE);
static AIC_WDT_TypeDef * const AIC_WDT1 = ((AIC_WDT_TypeDef *)AIC_WDT1_BASE);
static AIC_WDT_TypeDef * const AIC_WDT2 = ((AIC_WDT_TypeDef *)AIC_WDT2_BASE);
static AIC_WDT_TypeDef * const AIC_WDT4 = ((AIC_WDT_TypeDef *)AIC_WDT4_BASE);

//WDG_LOAD_VAL
#define WDG_WDG_LOAD_VAL(n)             (((n)&0xFFFFFFFF)<<0)
#define WDG_WDG_LOAD_VAL_LSB            (0)
#define WDG_WDG_LOAD_VAL_MASK           (0xFFFFFFFF<<0)

//WDG_CNT
#define WDG_WDG_CNT(n)                  (((n)&0xFFFFFFFF)<<0)
#define WDG_WDG_CNT_LSB                 (0)
#define WDG_WDG_CNT_MASK                (0xFFFFFFFF<<0)

//WDG_CTRL
#define WDG_WDG_IRQ_EN                  (1<<0)
#define WDG_WDG_IRQ_EN_POS              (0)
#define WDG_WDG_RUN                     (1<<1)
#define WDG_WDG_RUN_POS                 (1)

//WDG_INT_CLR
#define WDG_WDG_INT_CLR                 (1<<0)
#define WDG_WDG_INT_CLR_POS             (0)

//WDG_INT_RAW
#define WDG_WDG_INT_RAW                 (1<<0)
#define WDG_WDG_INT_RAW_POS             (0)
#define WDG_WDG_LD_BUSY                 (1<<4)
#define WDG_WDG_LD_BUSY_POS             (4)

//WDG_INT_MASK
#define WDG_WDG_INT_MASK                (1<<0)
#define WDG_WDG_INT_MASK_POS            (0)

//WDG_LOCK
#define WDG_WDG_LOCK(n)                 (((n)&0xFFFF)<<0)
#define WDG_WDG_LOCK_LSB                (0)
#define WDG_WDG_LOCK_MASK               (0xFFFF<<0)

#endif /* _REG_WDT_H_ */
