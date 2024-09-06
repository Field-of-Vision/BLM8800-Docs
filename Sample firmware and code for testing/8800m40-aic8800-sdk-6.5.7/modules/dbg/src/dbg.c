/**
 ****************************************************************************************
 *
 * @file dbg.c
 *
 * @brief Definition of the Debug module environment.
 *
 * Copyright (C) RivieraWaves 2011-2019
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup DEBUG
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "dbg.h"
#include <string.h>

#ifdef CFG_RTOS
#include "rtos_al.h"
#endif

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
/// Debug module environment definition. (moved here for host)
struct debug_env_tag dbg_env = {
    .filter_module = DBG_MOD_ALL,
    .filter_severity = DBG_SEV_IDX_ERR,//DBG_SEV_IDX_VRB,//
};

#if defined(CFG_RTOS) && DBG_MUTEX_ENABLED
extern rtos_mutex dbg_mutex;

void dbg_rtos_init(void)
{
    if (rtos_mutex_create(&dbg_mutex)) {
        dbg("create dbg_mutex err\n");
    }
}
#endif

/// @} end of group
