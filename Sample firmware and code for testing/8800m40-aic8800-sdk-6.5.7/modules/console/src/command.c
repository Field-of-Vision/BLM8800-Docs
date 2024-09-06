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
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "command.h"
#include "console.h"
#include "lnx_list.h"

static const char erase_seq[] = "\b \b";        /* erase sequence       */
static const char   tab_seq[] = "    ";         /* used to expand TABs  */

#define isblank(c)      ((c) == ' ' || (c) == '\t')

#if 0
__STATIC_INLINE int isprint(unsigned char c)
{
    if ((c >= 0x1F) && (c <= 0x7E))
        return 1;
    return 0;
}
#endif

__STATIC_INLINE int isdigit(unsigned char c)
{
    return ((c >= '0') && (c <='9'));
}

__STATIC_INLINE int isxdigit(unsigned char c)
{
    if ((c >= '0') && (c <='9'))
        return 1;
    if ((c >= 'a') && (c <='f'))
        return 1;
    if ((c >= 'A') && (c <='F'))
        return 1;
    return 0;
}

__STATIC_INLINE int islower(unsigned char c)
{
    return ((c >= 'a') && (c <='z'));
}

__STATIC_INLINE int isupper(unsigned char c)
{
    return ((c >= 'A') && (c <='Z'));
}

__STATIC_INLINE unsigned char tolower(unsigned char c)
{
    if (isupper(c))
        c -= 'A'-'a';
    return c;
}

__STATIC_INLINE unsigned char toupper(unsigned char c)
{
    if (islower(c))
        c -= 'a'-'A';
    return c;
}

/* Compare string case non-sensitive */
int aic_strncasecmp(const char *s1, const char *s2, size_t n)
{
    char c1, c2;

    do
    {
        c1 = tolower(*s1++);
        c2 = tolower(*s2++);

    } while((--n > 0) && (c1 == c2) && (c1 != '\0')) ;

    return (c1 - c2);
}

int command_make_argv(char *s, char *argv[])
{
    int argc = 0;

    while (argc < CONFIG_SYS_MAXARGS) {
        /* skip any white space */
        while (isblank(*s)) {
            ++s;
        }

        if (*s == '\0') {       /* end of line, no more args */
            argv[argc] = 0;
            return argc;
        }

        if(*s == '\"') {        /* args with quotation marks */
            s++;                /* the first quotation mark */

            argv[argc++] = s;   /* begin of argument string */

            while(*s && (*s != '\"')) { /* the second quotation mark */
                ++s;
            }
        } else {
            argv[argc++] = s;   /* begin of argument string */

            /* find end of string */
            while(*s && !isblank(*s)) {
                ++s;
            }
        }

        if (*s == '\0') {       /* end of line, no more args */
            argv[argc] = 0;
            return argc;
        }

        *s++ = '\0';         /* terminate current arg */
    }

    console_puts("Too many args, max:" XNSTR(CONFIG_SYS_MAXARGS) "\r\n");

    return argc;
}

const cmd_tbl_t * command_find(const char *cmd_name, const cmd_tbl_t *cmd_list, int max_cnt)
{
    const cmd_tbl_t *cmdtp;
    const cmd_tbl_t *cmdtp_temp = &cmd_list[0];     /* Init value */
    const cmd_tbl_t *cmdtp_end = &cmd_list[max_cnt];/* End value  */
    const char *p;
    unsigned int len;
    int n_found = 0;

    p = strchr(cmd_name, '.');
    len = (p == NULL) ? strlen(cmd_name) : (unsigned int)(p - cmd_name);

    for (cmdtp = &cmd_list[0]; (cmdtp < cmdtp_end) && (cmdtp->name != NULL); cmdtp++) {
        if (aic_strncasecmp(cmd_name, cmdtp->name, len) == 0) {
            if (len == strlen(cmdtp->name))
                return cmdtp;      /* full match */

            cmdtp_temp = cmdtp;    /* abbreviated command ? */
            n_found++;
        }
    }
    if (n_found == 1) {  /* exactly one match */
        return cmdtp_temp;
    }

    return 0;   /* not found or ambiguous command */
}

static char *delete_char(char *buffer, char *p, int *colp, int *np, int plen)
{
    char *s;

    if (*np == 0) {
        return p;
    }

    if (*(--p) == '\t') {           /* will retype the whole line */
        while (*colp > plen) {
            console_puts(erase_seq);
            (*colp)--;
        }
        for (s = buffer; s < p; ++s) {
            if (*s == '\t') {
                console_puts(tab_seq + ((*colp) & 0x07));
                *colp += 8 - ((*colp) & 0x07);
            } else {
                ++(*colp);
                console_putc(*s);
            }
        }
    } else {
        console_puts(erase_seq);
        (*colp)--;
    }
    (*np)--;

    return p;
}

int command_char2buffer(const char c, char *cmd_buf, char *prompt)
{
    static char *p   = NULL;
    static int  n    = 0;   /* buffer index         */
    static int  plen = 0;   /* prompt length        */
    static int  col;        /* output column cnt    */

    if (!p) {
        p = cmd_buf;
    }
    if (prompt) {
        plen = strlen(prompt);
        p = cmd_buf;
        n = 0;
        return 0;
    }
    col = plen;

    /*
     * Special character handling
     */
    switch (c) {
        case '\r':                  /* Enter            */
        case '\n':
            *p = '\0';
            console_puts("\r\n");
            return (p - cmd_buf);

        case '\0':                  /* nul              */
            return -1;

        case 0x03:                  /* ^C - break       */
            cmd_buf[0] = '\0';  /* discard input */
            return 0;

        case 0x15:                  /* ^U - erase line  */
            while (col > plen) {
                console_puts(erase_seq);
                --col;
            }
            p = cmd_buf;
            n = 0;
            return -1;

        case 0x17:                  /* ^W - erase word  */
            p = delete_char(cmd_buf, p, &col, &n, plen);
            while ((n > 0) && (*p != ' ')) {
                p = delete_char(cmd_buf, p, &col, &n, plen);
            }
            return -1;

        case 0x08:                  /* ^H  - backspace  */
        case 0x7F:                  /* DEL - backspace  */
            p = delete_char(cmd_buf, p, &col, &n, plen);
            return -1;

        default:
            /*
             * Must be a normal character then
             */
            if (n < CONFIG_SYS_CBSIZE - 2) {
                if (c == '\t') {    /* expand TABs      */
                    console_puts(tab_seq + (col & 0x07));
                    col += 8 - (col & 0x07);
                } else {
                    ++col;          /* Echo input       */
                    console_putc(c);
                }
                *p++ = c;
                ++n;
            } else {                /* Buffer full      */
                console_putc('\a');
            }
    }

    return -1;
}

unsigned int command_strtoul(const char *cp, char **endp, unsigned int base)
{
    unsigned int result = 0, value, is_neg = 0;

    if (*cp == '0') {
        cp++;
        if ((tolower(*cp) == 'x') && isxdigit(*(cp + 1))) {
            base = 16;
            cp++;
        }
        if (!base) {
            base = 8;
        }
    }
    if (!base) {
        base = 10;
    }
    if (*cp == '-') {
        is_neg = 1;
        cp++;
    }
    while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp - '0' : (islower(*cp)
        ? toupper(*cp) : *cp) - 'A' + 10) < base) {
        result = result * base + value;
        cp++;
    }
    if (is_neg) {
        result = (unsigned int)((int)result * (-1));
    }
    if (endp)
        *endp = (char *)cp;
    return result;
}
