/***
 * aic_host_cfg.h
 */

#ifndef AIC_HOST_CFG_H
#define AIC_HOST_CFG_H
#include <stdbool.h>

typedef struct {
    bool support_sniff;
    bool multiple_phone;
    bool support_aon;
    bool support_sleep;
    unsigned char rom_version;
    bool tws_plus;
    bool ssp_mode;
}aic_host_cfg_t;

aic_host_cfg_t* Aic_Host_Cfg(void);

#endif /* AIC_HOST_CFG_H */
