#include "da230.h"
#include "string.h"
#include "math.h"
#include "reg_i2cm.h"
#include "reg_iomux.h"
#include "aud_proc.h"
#ifdef CFG_RTOS
#include "rtos_al.h"
#endif
#include "lp_ticker_api.h"
#include "sysctrl_api.h"
#if PLF_BT_STACK
#include "co_main.h"
#endif
#if PLF_PMIC
#include "pmic_api.h"
#if PLF_PMIC_VER_FULL
#include "aic1000_i2cm.h"
#endif
#endif

#define DA230_I2C_CLK           (200000)
#define DA230_I2C_ADDR          (0x27)      //7 bits
#define MAX_COUNT  20
#define APP_GSENSOR_FIRST_MS (150)
#define APP_GSENSOR_MS (10)
static TimerHandle_t app_gsensor_timer = NULL;

static short int_data[MAX_COUNT][3] ={0};
static float angle_data[MAX_COUNT]={0};
static int begin_get_data=0;
static int abs_var_i=0;
#define abs(x) ((x) < 0 ? (-(x)) : (x))

#define USE_AIC1000_I2C         0

#define YZ_CROSS_TALK_ENABLE    1

#if YZ_CROSS_TALK_ENABLE
static short yzcross=0;
#endif

int da230_i2c_open ( void )
{
    uint32_t pclk, div, div0, div1;

    pclk = sysctrl_clock_get(SYS_PCLK);
    div = pclk / 4 / DA230_I2C_CLK;
    div0 = div & 0xFFFF;
    div1 = (div >> 16) & 0x3FF;
    AIC_I2CM0->DR[0] = DR_DIV0_0_FILED(div0) | DR_DIV0_1_FILED(div0);
    AIC_I2CM0->DR[1] = DR_DIV1_0_FILED(div1) | DR_DIV1_1_FIELD(div1);
    AIC_I2CM0->SCR   = 0x200;

    #if PLF_HW_FPGA
    // FPGA only
    #if USE_AIC1000_I2C
    hwp_audProc->spdif_userdata_0 &= ~(0x01UL << 0); // AIC1000 I2CM
    #else
    hwp_audProc->spdif_userdata_0 |=  (0x01UL << 0); // AIC8800 I2CM
    #endif
    #endif

    iomux_gpio_config_sel_setf(6, 1); // scl
    iomux_gpio_config_sel_setf(7, 1); // sda
    return 0;
}

/*return value: 0: is ok    other: is failed*/
int da230_register_read( unsigned char addr, unsigned char *data)
{
    unsigned int rdata;

#if USE_AIC1000_I2C
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_ADDR_CFG) , AIC1000_I2CM_I2C_DEVICE_ADDRESS(DA230_I2C_ADDR));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_TX) , AIC1000_I2CM_I2C_TX(addr));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_COUNT) , AIC1000_I2CM_I2C_COUNT(0x1));
    //PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->ADDR_DVD0), AIC1000_I2CM_I2C_LOW_DVD0(0x7f) | AIC1000_I2CM_I2C_HIGH_DVD0(0x7f));
    //PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->ADDR_STA0_DVD),AIC1000_I2CM_I2C_STAO(0x100));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_CTL) , AIC1000_I2CM_I2C_OUT_OPT | AIC1000_I2CM_I2C_START | AIC1000_I2CM_I2C_EN |
                  AIC1000_I2CM_FIFO_AE_LVL(0x1) | AIC1000_I2CM_FIFO_AF_LVL(0x1) | (1<<21));
    //udelay_use(1);
    for (int idx = 0; idx < 0x3FF; idx++) {
        __NOP();
    }
    rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    while((rdata & AIC1000_I2CM_I2C_BUSY) == AIC1000_I2CM_I2C_BUSY)
    {
       rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    }
    //dbg("i2cm byte read start !!!\n");
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_COUNT) , AIC1000_I2CM_I2C_COUNT(0x1));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_CTL) , AIC1000_I2CM_I2C_OUT_OPT | AIC1000_I2CM_I2C_START | AIC1000_I2CM_I2C_EN |
                  AIC1000_I2CM_FIFO_AE_LVL(0x1) | AIC1000_I2CM_FIFO_AF_LVL(0x1) | AIC1000_I2CM_I2C_MODE);

    rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    while((rdata & AIC1000_I2CM_I2C_BUSY) == AIC1000_I2CM_I2C_BUSY)
    {
       rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    }
    rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_RX));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_CTL), 0);
#else  /* USE_AIC1000_I2C */
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(DA230_I2C_ADDR);
    AIC_I2CM0->OR  = addr;
    AIC_I2CM0->LR  = 1;
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_RESTART_BIT ;

    rdata =  AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT)
    {
        rdata = AIC_I2CM0->SR;
        dbg("i2cm byte read status0 =%x!!!\n", rdata);
    }
    dbg("i2cm byte read start !!!\n");
    AIC_I2CM0->LR = 1;
    AIC_I2CM0->CR   = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1) | CR_READ_BIT;

    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT)
    {
        rdata =  AIC_I2CM0->SR;
        dbg("i2cm byte read status1 =%x!!!\n", rdata);
    }
    rdata = AIC_I2CM0->IR;
    AIC_I2CM0->CR  = 0;
#endif /* USE_AIC1000_I2C */
    *data = (unsigned char)(rdata & 0xFF);
    return 0;
}

/*return value: 0: is ok    other: is failed*/
int da230_register_write( unsigned char addr, unsigned char data)
{
    unsigned int rdata;

#if USE_AIC1000_I2C
    //dbg("i2cm byte write start !!!\n");
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_ADDR_CFG), AIC1000_I2CM_I2C_DEVICE_ADDRESS(DA230_I2C_ADDR));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_TX), AIC1000_I2CM_I2C_TX(addr));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_TX), AIC1000_I2CM_I2C_TX(data));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_COUNT), AIC1000_I2CM_I2C_COUNT(0x2));
    //PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->ADDR_DVD0), AIC1000_I2CM_I2C_LOW_DVD0(0x7f) | AIC1000_I2CM_I2C_HIGH_DVD0(0x7f));
    //PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->ADDR_STA0_DVD),AIC1000_I2CM_I2C_STAO(0x100));
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_CTL), AIC1000_I2CM_I2C_OUT_OPT | AIC1000_I2CM_I2C_START | AIC1000_I2CM_I2C_EN | AIC1000_I2CM_FIFO_AE_LVL(0x1) | AIC1000_I2CM_FIFO_AF_LVL(0x1));
    //udelay_use(1);
    for (int idx = 0; idx < 0x3FF; idx++) {
        __NOP();
    }
    rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    while((rdata & AIC1000_I2CM_I2C_BUSY) == AIC1000_I2CM_I2C_BUSY)
    {
        rdata = PMIC_MEM_READ((unsigned int)&(hwp_aic1000I2cm0->I2C_STATUS));
    }
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->I2C_CTL), 0);
    PMIC_MEM_WRITE((unsigned int)&(hwp_aic1000I2cm0->ADDR_RST), AIC1000_I2CM_I2C_RST);
#else  /* USE_AIC1000_I2C */
    //dbg("i2cm byte write start !!!\n");
    AIC_I2CM0->SAR = SAR_SLAVE_ADDR_FILED(DA230_I2C_ADDR);
    AIC_I2CM0->OR  = addr;
    AIC_I2CM0->OR  = data;
    AIC_I2CM0->LR  = 2;
    AIC_I2CM0->CR  = CR_OMO_ENABLE_BIT | CR_START_BIT | CR_ENABLE_BIT | CR_DE_TH_FILED(0x1) | CR_DF_TH_FILED(0x1);

    rdata = AIC_I2CM0->SR;
    while ((rdata & SR_BUSY_BIT) == SR_BUSY_BIT)
    {
        rdata = AIC_I2CM0->SR;
        //dbg("i2cm byte write status =%x!!!\n", rdata);
    }
    AIC_I2CM0->CR  = 0;
    AIC_I2CM0->RR = RR_RST_BIT;
#endif /* USE_AIC1000_I2C */

    return 0;
}


/*return value: 0: is ok    other: is failed*/
int da230_register_read_continuously( unsigned char addr, unsigned char count, unsigned char *data)
{
    int ret = 0;
    int i = 0;

    for (; i < count; i++) {
        da230_register_read(addr+i, data+i);
    }

    return ret;
}


/*return value: 0: is ok    other: is failed*/
int da230_register_mask_write(unsigned char addr, unsigned char mask, unsigned char data)
{
    int     res = 0;
    unsigned char      tmp_data=0;

    res = da230_register_read(addr, &tmp_data);
    if (res) {
        return res;
    }

    tmp_data &= ~mask;
    tmp_data |= data & mask;
    res = da230_register_write(addr, tmp_data);

    return res;
}

void da230_delay_ms(unsigned int ms)
{
    #if 0 //#ifdef CFG_RTOS
    rtos_task_suspend(ms);
    #else
    uint32_t delta_us = ms * 1000;
    uint32_t previous_us = lp_ticker_read();
    while ((lp_ticker_read() - previous_us) < delta_us);
    #endif
}




static int gsensor_key_event_process(void)
{

}

static void get_abs_avr(void)
{
    int i;
    float sum_abs=0;
    float yz_plane =0;
    float tanx=0;
    float anglex=0;

    for (i = 0; i < (MAX_COUNT); i++) {
        yz_plane = sqrt(int_data[i][1]*int_data[i][1] +int_data[i][2]*int_data[i][2] );

        if (int_data[i][0] == 0) {
            anglex = 90.0f;
        } else {
            tanx = yz_plane /(float)int_data[i][0];
            anglex = atan(tanx) *180/3.14;
        }

        angle_data[i] = anglex;
        dbg("angle[%d] = %d xyz[%4d][%4d][%4d]\n",i,(int)(angle_data[i]*100),int_data[i][0],int_data[i][1],int_data[i][2]);
    }

    for (i=0; i<(MAX_COUNT-1); i++) {
        sum_abs = sum_abs +abs(angle_data[i] - angle_data[i+1]);
    }

    sum_abs = sum_abs / (MAX_COUNT -1);

    if ((sum_abs*100) >250) {
        dbg("====FAIL sum_abs = %d\n",(int)(sum_abs*100));
        //bt_key_init();
    } else {
        dbg("!!!!!!!!!!!!!!!!ok\n");
        gsensor_key_event_process();
    }
}

static void get_data(short x,short y,short z)
{
    if (1 == begin_get_data) {
        if (abs_var_i< MAX_COUNT) {
            int_data[abs_var_i][0] = x;
            int_data[abs_var_i][1] = y;
            int_data[abs_var_i][2] = z;

            dbg("xyz_dat[%d][%d][%d]",int_data[i][0],int_data[i][1],int_data[i][2]);

            abs_var_i++;
        } else {
            abs_var_i=0;
            begin_get_data =0;

            get_abs_avr();

            //da230_enable_interrupt_temp(1);
        }
    }
}

static void app_gsensor_timehandler(void const *param)
{
    short x=0,y=0,z=0;

    da230_read_data(&x,&y,&z);
    get_data(x,y,z);
    //osTimerStop(app_gsensor_timer);
    dbg("timer10ms begin_get_data =%d\n",begin_get_data);

    if (begin_get_data ==1) {
        rtos_timer_change_period(app_gsensor_timer, APP_GSENSOR_MS, 0);
    }

}

/*return value: 0: is ok    other: is failed*/
int da230_init(void)
{
    int             res = 0;
    unsigned char data=0;
    int i=0;

    da230_register_read(DTA_REG_WHO_AM_I,&data);
    dbg("DA230 ID=%d\n", data);

    if (0x13 != data) {
        for (i = 0; i < 5; i++) {
          da230_register_read(DTA_REG_WHO_AM_I,&data);
          if (0x13 == data) {
              break;
          }

          da230_delay_ms(20);
        }
        if (i == 5) {
           return -1;
        }
    }

    res =  da230_register_mask_write(DTA_REG_SPI_I2C, 0x24, 0x24);

    da230_delay_ms(50);

    res |= da230_register_write(DTA_REG_G_RANGE,0x41);//4G MODE
    res |= da230_register_write(DTA_REG_POWERMODE_BW,0x04);//LOW POWER MDE OSR 1X BW:1.1/10 ODR
    res |= da230_register_write(DTA_REG_ODR_AXIS_DISABLE,0x07);//ENABLE XYZ & SET ODR 62.5Hz

    res |= da230_register_write(DTA_REG_ENGINEERING_MODE,0x83);
    res |= da230_register_write(DTA_REG_ENGINEERING_MODE,0x69);
    res |= da230_register_write(DTA_REG_ENGINEERING_MODE,0xBD);

    res |= da230_register_mask_write(DTA_REG_SENS_COMP, 0x40, 0x00);

#if YZ_CROSS_TALK_ENABLE
    res |= da230_register_read(DTA_REG_CHIP_INFO_SECOND, &data);

    if(data&0x10)
        yzcross = -(data&0x0f);
    else
        yzcross = (data&0x0f);
#endif

    #ifdef CFG_RTOS
    if (app_gsensor_timer == NULL) {
        app_gsensor_timer = rtos_timer_create("gsensor_timer", APP_GSENSOR_FIRST_MS, pdFALSE, NULL,
                                              (TimerCallbackFunction_t)app_gsensor_timehandler);
    }
    #endif
    return res;
}

/*return value: 0: is ok    other: is failed*/
int da230_set_enable(char enable)
{
    int res = 0;

    if(enable)
        res = da230_register_write(DTA_REG_POWERMODE_BW,0x04);   //normal
    else
        res = da230_register_write(DTA_REG_POWERMODE_BW,0x84);   //sleep

    return res;
}

/*return value: 0: is ok    other: is failed*/
int da230_open_interrupt(void)
{
    int   res = 0;

    res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x20);//0XB0 FILTER+ S-T + D-T
    res |= da230_register_write(DTA_REG_INTERRUPT_MAPPING1,0x20 );//MAPPINT THE S-T + D-T TO INT1

    res |= da230_register_write(DTA_REG_INT_LATCH,0xcd);//LATCHED 50 MS

    res |= da230_register_write(DTA_REG_TAP_DURATION,0x40 );    //DEFAULT

    res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0xD );//MAPPINT THE S-T + D-T TO INT1

    #if 0
    {
        unsigned char data=0;
        da230_register_read(DTA_REG_INT_PIN_CONFIG,&data);
        if(data == 0)
            res |= da230_register_write(DTA_REG_INT_PIN_CONFIG,0x0F);//INT PIN LOW ACTIVE
        else
            res |= da230_register_write(DTA_REG_INT_PIN_CONFIG,0x0A);//INT PIN HIGH ACTIVE
    }
    #else
    res |= da230_register_write(DTA_REG_INT_PIN_CONFIG,0x00); // push-pull + high active
    //res |= da230_register_write(DTA_REG_INT_PIN_CONFIG,0x0F); // OD + low active
    #endif
    return res;
}

/*return value: 0: is ok    other: is failed*/
int da230_close_interrupt(void)
{
    int   res = 0;

    res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x00 );

    res |= da230_register_write(DTA_REG_INTERRUPT_MAPPING1,0x00 );

    return res;
}

int da230_set_interrupt_level(int level)
{
   int   res = 0;
   dbg("\r\n##set sencetivity=%d\r\n",level);
 // level=5;
   switch(level)
   {
      case 1:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x10);// ENBALE DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x1f );//SET DOUBLE TAP THRESHOLD
      break;

      case 2:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x10);// ENBALE DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x1b );//SET DOUBLE TAP THRESHOLD
      break;

      case 3:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x10);// ENBALE DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x18 );//SET DOUBLE TAP THRESHOLD
      break;

      case 4:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x10);//ENBALE FILTER & DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x12 );//SET DOUBLE TAP THRESHOLD
      break;

      case 5:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x50);//ENBALE FILTER & DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x0d );//SET DOUBLE TAP THRESHOLD
      break;

      case 6:
          res = da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x50);//ENBALE FILTER & DOUBLE TAP
          res |= da230_register_write(DTA_REG_TAP_THRESHOLD,0x08 );//SET DOUBLE TAP THRESHOLD
      break;

      default:
        break;

   }

   res |= da230_register_write(DTA_REG_INTERRUPT_MAPPING1,0x10 );//MAPPINT DOUBLE TAP TO INT1

   res |= da230_register_write(DTA_REG_INT_LATCH,0x0d);//LATCHED 50 MS

   res |= da230_register_write(DTA_REG_TAP_DURATION,0x45 );   //DEFAULT

   return res;
}


/*return value: 0: is ok    other: is failed*/
int da230_reset(void)
{
    int   res = 0;

    res = da230_register_write(0x00,0x24);

    return res;
}

void da230_enable_interrupt_temp(char en)
{
    if (en ==1) {
      da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x90 );
    } else {
        da230_register_write(DTA_REG_INTERRUPT_SETTINGS1,0x00 );
    }
}

/*return value: 0: is ok    other: is failed*/
int da230_read_data(short *x, short *y, short *z)
{
    unsigned char    tmp_data[6] = {0},i=0;

    for(i=0;i<6;i++) {
        da230_register_read(DTA_REG_ACC_X_LSB+i,&tmp_data[i]);
    }

    *x = ((short)(tmp_data[1] << 8 | tmp_data[0]))>> 3;
    *y = ((short)(tmp_data[3] << 8 | tmp_data[2]))>> 3;
    *z = ((short)(tmp_data[5] << 8 | tmp_data[4]))>> 3;

    //dbg("xyz %d %d %d\r\n",*x,*y,*z);

    return 0;
}

/*return value: 0: is ok    other: is failed*/
/*type: 0: D-T ; 1: S-T;*/
int da230_parse_interrupt_type(void)
{
    //int   res = 0;
    //unsigned char data=0;

    //res = da230_register_read(DTA_REG_MOTION_FLAG,&data);

    // if(data == 0x10)
    {
        dbg("===========================\r\n");
        begin_get_data =1;
        abs_var_i = 0;
        memset(int_data,0,MAX_COUNT*3*2);
        // da230_enable_interrupt_temp(0);

        if (app_gsensor_timer != NULL) {
            rtos_timer_change_period_isr(app_gsensor_timer, APP_GSENSOR_FIRST_MS); // called in GPIO isr
        }
    }
    return 0;
}


int da230_get_chip_id(void)
{
    int             res = 0;
    unsigned char data=0;

    res = da230_register_read(DTA_REG_WHO_AM_I,&data);
    if(res != 0)
        return 0;

    return data;
}

void da230_standby_mode(void)
{
    da230_register_write(DTA_REG_POWERMODE_BW,0x84);//SUSPEND MODE
    dbg("da230 off\r\n");
}

void da230_normal_mode(void)
{
    da230_register_write(DTA_REG_POWERMODE_BW,0x04);//NORMAL MODE
    dbg("da230 on\r\n");
}


void da230_open_interrupt_test(void)
{
    /*

    da230_register_write(DTA_REG_INT_PIN_CONFIG,0x00 ); //set interrupt 1 level 0
    da230_delay_ms(10);
    da230_register_write(DTA_REG_INT_PIN_CONFIG,0x01 ); //set interrupt 1 level 1
    da230_delay_ms(10);
      */


    int  res = 0;

    res = da230_register_write(DTA_REG_INT_LATCH,0x0d);//LATCHED 50 MS

    res |= da230_register_write(DTA_REG_INTERRUPT_MAPPING2,0x04);//mapping fifo interrupt to int1

    res |= da230_register_write(DTA_REG_FIFO_CTRL,0x40);//set fifo normal mode

    res |= da230_register_write(DTA_REG_INTERRUPT_SETTINGS0,0x04);//enable fifo full interrupt
    //*/
    //return res;

}

int da230_read_data_test(short *x, short *y, short *z)
{
    unsigned char    tmp_data[6] = {0},i=0;

    for(i=0;i<6;i++) {
        da230_register_read(DTA_REG_ACC_X_LSB+i,&tmp_data[i]);
    }

    *x = ((short)(tmp_data[1] << 8 | tmp_data[0]))>> 3;
    *y = ((short)(tmp_data[3] << 8 | tmp_data[2]))>> 3;
    *z = ((short)(tmp_data[5] << 8 | tmp_data[4]))>> 3;

#if YZ_CROSS_TALK_ENABLE
    if(yzcross)
        *y=*y-(*z)*yzcross/100;
#endif

    *x = (*x)*1000/1024;
    *y = (*y)*1000/1024;
    *z = (*z)*1000/1024;

    da230_delay_ms(10);
    return 1;
}
