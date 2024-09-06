#ifndef _AIC1000LITE_I2CM_H_
#define _AIC1000LITE_I2CM_H_

#include "chip.h"

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// AIC1000LITE_SPI_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_AIC1000LITE_I2CM_BASE   0x50015000

typedef volatile struct
{
    __IO uint32_t                          CTRL;                         //0x00000000
    __IO uint32_t                          STATUS;                       //0x00000004
    __IO uint32_t                          TXRX_BUFFER;                  //0x00000008
    __IO uint32_t                          CMD;                          //0x0000000C
    __IO uint32_t                          IRQ_CLR;                      //0x00000010
} HWP_AIC1000LITE_I2CM;

static HWP_AIC1000LITE_I2CM * const aic1000liteI2CM = ((HWP_AIC1000LITE_I2CM *)REG_AIC1000LITE_I2CM_BASE);


//ctrl
#define AIC1000LITE_I2CM_EN                   (1<<0)
#define AIC1000LITE_I2CM_IRQ(n)               (((n)&1)<<8)
#define AIC1000LITE_I2CM_IRQ_MASK             (1<<8)
#define AIC1000LITE_I2CM_CLOCK_PRESCALE(n)    (((n)&0xFFFF)<<16)
#define AIC1000LITE_I2CM_CLOCK_PRESCALE_MASK  (0xFFFF<<16)

//status
#define AIC1000LITE_I2CM_IRQ_CAUSE         (1<<0)
#define AIC1000LITE_I2CM_IRQ_STATUS        (1<<4)
#define AIC1000LITE_I2CM_TIP               (1<<8)
#define AIC1000LITE_I2CM_AL                (1<<12)
#define AIC1000LITE_I2CM_BUSY              (1<<16)
#define AIC1000LITE_I2CM_RXACK             (1<<20)

//rxtx_buffer
#define AIC1000LITE_I2CM_RX_ACK(n)          (((n)&0xFF)<<0)

//cmd
#define AIC1000LITE_I2CM_ACK      (1<<0)
#define AIC1000LITE_I2CM_RD       (1<<4)
#define AIC1000LITE_I2CM_STO      (1<<8)
#define AIC1000LITE_I2CM_RW       (1<<12)
#define AIC1000LITE_I2CM_STA      (1<<16)

//irq clr
#define AIC1000LITE_I2CM_IRQ_CLR  (1<<0)

#endif /* _AIC1000LITE_I2CM_H_ */
