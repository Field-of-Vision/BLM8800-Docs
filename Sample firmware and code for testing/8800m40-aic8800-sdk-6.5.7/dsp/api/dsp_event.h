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
#ifndef _DSP_EVENT_H_
#define _DSP_EVENT_H_

#include <stdint.h>

enum DSP_EVENT_TYPE {
    DSP_EVENT_DATA = 0,
    DSP_EVENT_MSG,
    DSP_EVENT_MAX
};

enum DSP_EVENT_STATUS
{
    DSP_EVENT_OK = 0,
    DSP_EVENT_FAIL,
    DSP_EVENT_UNKNOWN,
    DSP_EVENT_CAPA_EXCEEDED,
    DSP_EVENT_ALREADY_EXISTS,
};

/**
 ****************************************************************************************
 * @brief Initialize DSP event module.
 ****************************************************************************************
 */
void dsp_event_init(void);

/**
 ****************************************************************************************
 * @brief Register an event callback.
 *
 * @param[in]  event_type       Event type.
 * @param[in]  p_callback       Pointer to callback function.
 *
 * @return                      Status
 ****************************************************************************************
 */
uint8_t dsp_event_callback_set(uint8_t event_type, void (*p_callback)(void));

/**
 ****************************************************************************************
 * @brief Set an event
 *
 * This primitive sets one event. It will trigger the call to the corresponding event
 * handler in the next scheduling call.
 *
 * @param[in]  event_type      Event to be set.
 ****************************************************************************************
 */
void dsp_event_set(uint8_t event_type);

/**
 ****************************************************************************************
 * @brief Clear an event
 *
 * @param[in]  event_type      Event to be cleared.
 ****************************************************************************************
 */
void dsp_event_clear(uint8_t event_type);

/**
 ****************************************************************************************
 * @brief Get the status of an event
 *
 * @param[in]  event_type      Event to get.
 *
 * @return                     Event status (0: not set / 1: set)
 ****************************************************************************************
 */
uint8_t dsp_event_get(uint8_t event_type);

/**
 ****************************************************************************************
 * @brief Get all event status
 *
 * @return                     Events bit field
 ****************************************************************************************
 */
uint32_t dsp_event_get_all(void);

/**
 ****************************************************************************************
 * @brief Flush all pending events.
 ****************************************************************************************
 */
void dsp_event_flush(void);

/**
 ****************************************************************************************
 * @brief Event scheduler entry point.
 *
 * This primitive is the entry point of Kernel event scheduling.
 ****************************************************************************************
 */
void dsp_event_schedule(void);

#endif /* _DSP_EVENT_H_ */