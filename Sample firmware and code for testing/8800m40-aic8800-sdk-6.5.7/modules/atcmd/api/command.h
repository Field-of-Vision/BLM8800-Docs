/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Most of this code is derived from the U-Boot Command Processor Table.
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
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "cmsis_compiler.h"

#define CONFIG_SYS_MAXARGS  16

#define COMMAND_ERR_TOOMANY_ARGS    -128
#define COMMAND_ERR_UNKNOWN_CMD     -129
#define COMMAND_ERR_ARGS_NUMBER     -130

#ifdef __cplusplus
extern "C" {
#endif
typedef int (*cmd_func_t)(int argc, char * const argv[]);
typedef struct {
    const char *name;       /* Command Name                 */
    const char *usage;      /* Usage message                */
    short      minargs;     /* Minimum number of arguments  */
    short      maxargs;     /* Maximum number of arguments  */
    cmd_func_t cmd;         /* Callback function            */
} cmd_tbl_t;

extern char cmd_echo_en;

/**
 * Call a command function.
 *
 * @param cmdtp     Pointer to the command to execute
 * @param argc      Number of arguments (arg 0 must be the command text)
 * @param argv      Arguments
 * @return 0 if command succeeded, else non-zero
 */
__STATIC_INLINE int command_call(const cmd_tbl_t *cmdtp, int argc, char *const argv[])
{
    return (cmdtp->cmd)(argc, argv);
}

int command_make_argv(char *s, char *argv[]);
const cmd_tbl_t * command_find(const char *cmd, const cmd_tbl_t *cmd_list, int max_cnt);
int command_char2buffer(const char c, char *cmd_buf, char *prompt);
unsigned int command_strtoul(const char *cp, char **endp, unsigned int base);

#ifdef __cplusplus
}
#endif

#endif /* _COMMAND_H_ */
