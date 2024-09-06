/**
 ****************************************************************************************
 *
 * @file   i2cm_api.c
 * @Target AIC8800
 *
 ****************************************************************************************
 */
#include "i2cm_api.h"

#ifdef CFG_RTOS
static rtos_semaphore i2cm0_sem = NULL;
#endif
/**
 ****************************************************************************************
 * @brief init i2cm
 ****************************************************************************************
 */
void i2cm0_init(void)
{
    uint32_t pclk, div, div0, div1;

    // clk en
    cpusysctrl_pclkme_set(CSC_PCLKME_I2CM_EN_BIT);

    pclk = sysctrl_clock_get(SYS_PCLK);
    div = pclk / 4 / I2C_CLK_FREQ;
    div0 = div & 0xFFFF;
    div1 = (div >> 16) & 0x3FF;
    AIC_I2CM0->DR[0] = DR_DIV0_0_FILED(div0) | DR_DIV0_1_FILED(div0);
    AIC_I2CM0->DR[1] = DR_DIV1_0_FILED(div1) | DR_DIV1_1_FIELD(div1);
    AIC_I2CM0->SCR   = 0x200;

    // iomux
    iomux_gpio_config_sel_setf(6, 1); // scl
    iomux_gpio_config_pull_up_setf(6, 1);
    iomux_gpio_config_sel_setf(7, 1); // sda
    iomux_gpio_config_pull_up_setf(7, 1);

#if I2C_INT_MODE
    #ifdef CFG_RTOS
    if (i2cm0_sem == NULL) {
        if (0 != rtos_semaphore_create(&i2cm0_sem, 1, 0)) {
            USER_PRINTF("ERR: i2cm_sem create fail\n");
        }
    }
    #endif

    NVIC_SetVector(I2CM_IRQn, (uint32_t)I2CM_IRQHandler);
    NVIC_SetPriority(I2CM_IRQn, __NVIC_PRIO_LOWEST);
    NVIC_EnableIRQ(I2CM_IRQn);
#endif
}

void i2cm0_deinit(void)
{
    cpusysctrl_pclkme_set(~CSC_PCLKME_I2CM_EN_BIT);
    iomux_gpio_config_sel_setf(6, 0); // scl
    iomux_gpio_config_sel_setf(7, 0); // sda
}

/**
 ****************************************************************************************
 * @brief wait for i2cm operation done
 ****************************************************************************************
 */
#ifdef CFG_RTOS
int i2cm0_wait_op_done(int timeout)
{
    return rtos_semaphore_wait(i2cm0_sem, timeout);
}
#endif

/**
 ****************************************************************************************
 * @brief notify that i2cm operation is done
 ****************************************************************************************
 */
#ifdef CFG_RTOS
int i2cm0_op_done(bool isr)
{
    return rtos_semaphore_signal(i2cm0_sem, isr);
}
#endif

/**
 ****************************************************************************************
 * @brief read device register
 ****************************************************************************************
 */
int i2cm0_dev_reg_read(unsigned char reg_addr, unsigned char *reg_data)
{
    unsigned int rdata;

    AIC_I2CM0->SR &= ~(0x01UL << 1);
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(I2C_DEV_ADDR);
    AIC_I2CM0->OR  = reg_addr;
    AIC_I2CM0->LR  = 1;
#if I2C_INT_MODE
    AIC_I2CM0->CR  = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_RESTART_BIT ;
#else
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_RESTART_BIT ;
#endif

#if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
#else
    rdata =  AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata = AIC_I2CM0->SR;
    }
#endif

    AIC_I2CM0->LR = 1;
#if I2C_INT_MODE
    AIC_I2CM0->CR   = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_READ_BIT;
#else
    AIC_I2CM0->CR   = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_READ_BIT;
#endif

#if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
#else
    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata =  AIC_I2CM0->SR;
    }
#endif

    rdata = AIC_I2CM0->IR;
    AIC_I2CM0->CR  = 0;
    *reg_data = (unsigned char)(rdata & 0xFF);

    return 0;
}

void i2cm0_dev_muti_byte_read(unsigned char reg_addr, unsigned char rev_data[], unsigned char data_len)
{
    if(data_len>16) {
        I2CM_DEBUG_PRINTF("Muti byte limit is 15 byte\n");
        return ;
    }

    unsigned int rdata;
    unsigned char *rev_p;

    // write device addr and reg addr
    AIC_I2CM0->SR &= ~(0x01UL << 1);
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(I2C_DEV_ADDR);
    AIC_I2CM0->OR  = reg_addr;
    AIC_I2CM0->LR  = 1;

    #if I2C_INT_MODE
    AIC_I2CM0->CR  = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_RESTART_BIT ;
    #else
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_RESTART_BIT ;
    #endif

    #if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
    #else
    rdata =  AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata = AIC_I2CM0->SR;
    }
    #endif

    // read reg data
    rev_p = rev_data;
    AIC_I2CM0->LR = data_len;
    #if I2C_INT_MODE
    AIC_I2CM0->CR   = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_READ_BIT;
    #else
    AIC_I2CM0->CR   = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_READ_BIT;
    #endif

    #if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
    #else
    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata =  AIC_I2CM0->SR;
    }
    #endif

    for(int i=0; i<data_len; i++) {
        rdata = AIC_I2CM0->IR;
        *rev_p = (unsigned char)(rdata & 0xFF);
        rev_p++;
    }

    AIC_I2CM0->CR = 0;
    AIC_I2CM0->RR = RR_RST_BIT;
}

/**
 ****************************************************************************************
 * @brief write device register
 ****************************************************************************************
 */
int i2cm0_dev_reg_write(unsigned char reg_addr, unsigned char reg_data)
{
    unsigned int rdata;

    AIC_I2CM0->SR &= ~(0x01UL << 1);
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(I2C_DEV_ADDR);
    AIC_I2CM0->OR  = reg_addr;
    AIC_I2CM0->OR  = reg_data;
    AIC_I2CM0->LR  = 2;
#if I2C_INT_MODE
    AIC_I2CM0->CR  = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1);
#else
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1);
#endif

#if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
#else
    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata = AIC_I2CM0->SR;
    }
#endif

    AIC_I2CM0->CR  = 0;
    AIC_I2CM0->RR = RR_RST_BIT;

    return 0;
}

void i2cm0_dev_muti_byte_write(unsigned char reg_addr, unsigned char reg_data[], unsigned char data_len)
{
    if(data_len>15) {
        I2CM_DEBUG_PRINTF("Muti byte limit is 15 byte\n");
        return ;
    }

    unsigned int rdata;
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(I2C_DEV_ADDR);
    AIC_I2CM0->OR  = reg_addr;

    for(int i=0; i<data_len; i++)
        AIC_I2CM0->OR = reg_data[i];

    AIC_I2CM0->LR = data_len + 1;
    #if I2C_INT_MODE
    AIC_I2CM0->CR  = CR_INT_ENABLE_BIT | CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1);
    #else
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1);
    #endif

    #if I2C_INT_MODE
    i2cm0_wait_op_done(-1);
    #else
    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT) {
        rdata = AIC_I2CM0->SR;
    }
    #endif

    AIC_I2CM0->CR  = 0;
    AIC_I2CM0->RR = RR_RST_BIT;
}

void I2CM_IRQHandler(void)
{
    AIC_I2CM0->SR &= ~SR_INT_BIT;
    #ifdef CFG_RTOS
    i2cm0_op_done(true);
    #endif
}

