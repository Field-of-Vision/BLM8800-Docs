#include "hw_cfg.h"
#include <string.h>
#include <stdint.h>
#include "gpio_api.h"
#include "plf.h"
#if PLF_KEY_MODULE
#include "key.h"
#endif

void hw_cfg_init(void)
{
#if PLF_KEY_MODULE
    key_open();
#endif
}
