/*
 * Copyright (C) 2018-2022 AICSemi Ltd.
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
#include "usb_dev_msc.h"
#include "dbg.h"

#ifdef CFG_TEST_USBD_MSC

/*
 * MACROS
 ****************************************************************************************
 */
#define UART_PRINT              dbg


/*
 * FUNCTIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void usbd_msc_test(void)
{
    UART_PRINT("\nUSBD MSC test start\n");

    aic_usbd_msc_init();

    UART_PRINT("\nUSBD MSC test done\n");
}

#endif /* CFG_TEST_USBD_MSC */
