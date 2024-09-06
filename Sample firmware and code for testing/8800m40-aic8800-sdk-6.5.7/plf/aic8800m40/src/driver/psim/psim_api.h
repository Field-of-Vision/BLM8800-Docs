/**
 ****************************************************************************************
 *
 * @file psim_api.h
 *
 * @brief PSIM API functions
 *
 ****************************************************************************************
 */

#ifndef _PSIM_API_H_
#define _PSIM_API_H_

#define IS_PMIC_REG_VALID(addr)     (((unsigned int)(addr) >> 20) == (AIC_PMIC_REG_BASE  >> 20)) // 0x70000000 ~ 0x700FFFFF
#define IS_AUD1K_REG_VALID(addr)    (((unsigned int)(addr) >> 20) == (AIC_AUD1K_REG_BASE >> 20)) // 0x50000000 ~ 0x500FFFFF

#define IS_PMIC_MEM_ADDR(addr)      (IS_PMIC_REG_VALID(addr) || IS_AUD1K_REG_VALID(addr))

void psim_init(void);
unsigned int psim_read(unsigned int addr);
void psim_write(unsigned int addr, unsigned int data);
void psim_mask_write(unsigned int addr, unsigned int data, unsigned int mask);

#endif /* _PSIM_API_H_ */
