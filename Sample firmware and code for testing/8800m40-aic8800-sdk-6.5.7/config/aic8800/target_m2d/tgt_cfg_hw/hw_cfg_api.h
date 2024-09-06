/*
 * Copyright (C) 2018-2021 AICSemi Ltd.
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

#ifndef _HW_CFG_API_H_
#define _HW_CFG_API_H_
#if PLF_M2D_BLE
void m2d_wakeup_trigger(void);
#endif
void hw_cfg_init(void);

#endif /* _HW_CFG_API_H_ */
