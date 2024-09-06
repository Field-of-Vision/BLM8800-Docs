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
#include "dbg.h"
#include "console.h"
#include "gpadc_api.h"
#include "gpio_api.h"

#ifdef CFG_TEST_PRESS_BUTTON

/*
 * MACROS
 ****************************************************************************************
 */

#define GPIOB_INDEX             2

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTIONS
 ****************************************************************************************
 */
void gpiob_button_irq_test_handler(int event)
{
    int volt_mv;

    if (GPIOIRQ_CB_EVENT(event) == GPIOIRQ_EVENT_EDGE_FALL) {
        gpadc_samplerate_set(GPADC_SAMPLERATE_MID);
        gpadc_init(GPIOB_INDEX);
        volt_mv = gpadc_read(GPIOB_INDEX);
        dbg("GPADC[%d] voltage is %d mV\n", GPIOB_INDEX, volt_mv);
        gpiob_irq_init(GPIOB_INDEX, GPIOIRQ_TYPE_EDGE_FALL, gpiob_button_irq_test_handler,1);
    } else {
        dbg("irq event: %x\n", event);
    }
}

/**
 ****************************************************************************************
 * @brief test task implementation.
 ****************************************************************************************
 */
void press_button_test(void)
{
    dbg("\nPress button test\n");

    gpiob_irq_init(GPIOB_INDEX, GPIOIRQ_TYPE_EDGE_FALL, gpiob_button_irq_test_handler,1);
}

#endif /* CFG_TEST_PRESS_BUTTON */

