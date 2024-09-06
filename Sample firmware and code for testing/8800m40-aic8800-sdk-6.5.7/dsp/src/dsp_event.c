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
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "co_math.h"
#include "dsp_event.h"
#include "dbg_assert.h"
#include "dbg.h"
#include "ll.h"

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Format of an event callback function
typedef void (*p_callback_t)(void);


/*
 * STRUCTURES DEFINTIONS
 ****************************************************************************************
 */

/// DSP EVENT environment structure
struct dsp_event_env_tag
{
    /// Event field
    uint32_t event_field;

    /// Callback table
    p_callback_t callback[DSP_EVENT_MAX];
};


/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/// DSP EVENT environment
static struct dsp_event_env_tag dsp_event_env;


/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */


/*
 * EXPORTED FUNCTION DEFINITIONS
 ****************************************************************************************
 */


void dsp_event_init(void)
{
    memset(&dsp_event_env, 0, sizeof(dsp_event_env));
}

uint8_t dsp_event_callback_set(uint8_t event_type, void (*p_callback)(void))
{
    uint8_t status = DSP_EVENT_CAPA_EXCEEDED;

    ASSERT_INFO((event_type < DSP_EVENT_MAX) && (p_callback != NULL), event_type, p_callback);

    if(event_type < DSP_EVENT_MAX)
    {
        // Store callback
        dsp_event_env.callback[event_type] = p_callback;

        // Status OK
        status = DSP_EVENT_OK;
    }

    return (status);
}

void dsp_event_set(uint8_t event_type)
{
    ASSERT_INFO((event_type < DSP_EVENT_MAX), event_type, 0);

    GLOBAL_INT_DISABLE();

    if(event_type < DSP_EVENT_MAX)
    {
        // Set the event in the bit field
        dsp_event_env.event_field |= (1 << event_type);
    }

    GLOBAL_INT_RESTORE();
}

void dsp_event_clear(uint8_t event_type)
{
    ASSERT_INFO((event_type < DSP_EVENT_MAX), event_type, 0);

    GLOBAL_INT_DISABLE();

    if(event_type < DSP_EVENT_MAX)
    {
        // Set the event in the bit field
        dsp_event_env.event_field &= ~(1 << event_type);
    }

    GLOBAL_INT_RESTORE();
}

uint8_t dsp_event_get(uint8_t event_type)
{
    uint8_t state = 0;

    ASSERT_INFO((event_type < DSP_EVENT_MAX), event_type, 0);

    GLOBAL_INT_DISABLE();

    if(event_type < DSP_EVENT_MAX)
    {
        // Get the event in the bit field
        state = (dsp_event_env.event_field >> event_type) & (0x1);
    }

    GLOBAL_INT_RESTORE();

    return state;
}

uint32_t dsp_event_get_all(void)
{
    return dsp_event_env.event_field;
}

void dsp_event_flush(void)
{
    dsp_event_env.event_field = 0;
}

void dsp_event_schedule(void)
{
    uint8_t hdl;

    // Get the volatile value
    uint32_t field = dsp_event_env.event_field;

    while (field) // Compiler is assumed to optimize with loop inversion
    {
        // Find highest priority event set
        hdl = 32 - (uint8_t) co_clz(field) - 1;

        // Sanity check
        ASSERT_INFO(hdl < DSP_EVENT_MAX, hdl, field);

        if(dsp_event_env.callback[hdl] != NULL)
        {
            // Execute corresponding handler
            (dsp_event_env.callback[hdl])();
        }
        else
        {
            ASSERT_ERR(0);
        }

        // Update the volatile value
        field = dsp_event_env.event_field;
    }
}
