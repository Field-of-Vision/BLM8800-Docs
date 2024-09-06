/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pmic_api.h"
#include "gpio_api.h"
#include "sysctrl_api.h"
#include "dbg.h"
#include "rtos_al.h"

#if (!PLF_PMIC_VER_LITE)
#error "not support"
#endif

#ifdef CFG_TEST_GPIOB_I2CM
/* max clk: 400k */
void gpiob_i2cm_init(unsigned  int freq_Hz) {
    unsigned int prescale = 26000000 / 2 / (5 * freq_Hz) -1;

    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[6]),AIC1000LITE_IOMUX_PAD_GPIO_6_SEL_FUN_I2CM_SCL_SEL);
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteIomux->GPCFG[7]),AIC1000LITE_IOMUX_PAD_GPIO_7_SEL_FUN_I2CM_SDA_SEL);

    //.hclk divider，26M
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteSysctrl->hclk_div), (AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_DENOM(0x0) | AIC1000LITE_SYS_CTRL_CFG_HCLK_DIV_UPDATE));

    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CTRL), AIC1000LITE_I2CM_EN | AIC1000LITE_I2CM_IRQ_MASK | AIC1000LITE_I2CM_CLOCK_PRESCALE(prescale));
}

static void wait_tip_down (void)
{
    int tmp;
    tmp = PMIC_MEM_READ((unsigned int)(&aic1000liteI2CM->STATUS));
    while (tmp != 0x0) {
        tmp = PMIC_MEM_READ((unsigned int)(&aic1000liteI2CM->STATUS));
        tmp = tmp & 0x100 ;
    }
}

void gpiob_i2cm_write_byte(unsigned char dev_addr,unsigned char waddr,unsigned char wdata) {
    //Write tx buffer with CORRECT address
    //write address and start
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), (dev_addr << 1)); //write slave address
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x11000); //CMD: WR STA
    //hwp_i2cMaster1->TXRX_BUFFER=0x20 ;  //write CORRECT slave address
    //hwp_i2cMaster1->CMD = 0x11000 ;  //CMD: WR STA
    wait_tip_down();

    //TX data
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), waddr); //write slave address
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x01000); //CMD: WR STA
    //hwp_i2cMaster1->TXRX_BUFFER=addr;//0x07  ;  //write memory address
    //hwp_i2cMaster1->CMD = 0x01000;        //CMD : WR to slave
    wait_tip_down();

    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), wdata); //write slave data
    //hwp_i2cMaster1->TXRX_BUFFER=0x5a;//Buffer
    wait_tip_down();

    //write stop
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x1100); //CMD: WR STA
    //hwp_i2cMaster1->CMD = 0x1100 ;  //CMD stop
    wait_tip_down();

    dbg("I2C Write [0x%02x] =0x%x\n",waddr,wdata);
}

unsigned int gpiob_i2cm_read_byte(unsigned char dev_addr,unsigned char raddr) {
    volatile unsigned int rdata_tmp;

    //write_reg32(BASE_SYS_I2C0+ 0x0, 0x00270001);    // at_CTRL : rd_num is 1
    //write_reg32(BASE_SYS_I2C0+ 0x0, 0x00270101);    // at_CTRL
    //hwp_i2cMaster1->CTRL = I2C_MASTER_EN  | I2C_MASTER_CLOCK_PRESCALE(0x18F); //100K
    //Write rx buffer
    //read address and start
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), (dev_addr << 1)); //write slave address
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x11000); //CMD: WR STA
    //hwp_i2cMaster1->TXRX_BUFFER=0x20 ;  //write slave address
    //hwp_i2cMaster1->CMD = 0x11000 ;  //CMD: WR STA
    wait_tip_down();
    //RX data
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), raddr); //write slave address
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x01000); //CMD: WR STA
    //hwp_i2cMaster1->TXRX_BUFFER=addr;//0x07  ;  //write memory address
    //hwp_i2cMaster1->CMD = 0x01000;        //CMD : WR
    wait_tip_down();

    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER), ((dev_addr << 1) | 0x1)); //write slave address
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x11000); //CMD: WR STA
    //hwp_i2cMaster1->TXRX_BUFFER=0x21 ;  //write slave address and RW=1
    //hwp_i2cMaster1->CMD = 0x00011000 ;  //CMD: RD STA
    wait_tip_down();

    //write stop
    PMIC_MEM_WRITE((unsigned int)(&aic1000liteI2CM->CMD), 0x111); //CMD: WR STA
    //hwp_i2cMaster1->CMD = 0x111 ;  //CMD:ACK STOP
    wait_tip_down();

    rdata_tmp =  PMIC_MEM_READ((unsigned int)(&aic1000liteI2CM->TXRX_BUFFER));
    //rdata_tmp=   hwp_i2cMaster1->TXRX_BUFFER ;

    return rdata_tmp;
}

void gpiob_i2cm_test(void)
{
    int i =0;
    uint8_t dev_addr;
    unsigned int value;
    unsigned char tx_data[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xf0};

    gpiob_i2cm_init(400000);

    dev_addr = 0x3C;
    for(i=2;i<17;i++){
        gpiob_i2cm_write_byte(dev_addr, i, tx_data[i-2]);
    }

    for(i=2;i<17;i++){
        value = gpiob_i2cm_read_byte(dev_addr, i);
        dbg("I2C Read [0x%02x] = 0x%x\n",i,value);
    }
}
#endif /* CFG_TEST_GPIOB_I2CM */

