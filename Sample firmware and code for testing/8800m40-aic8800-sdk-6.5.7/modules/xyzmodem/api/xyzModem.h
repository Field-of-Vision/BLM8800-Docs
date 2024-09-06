#ifndef _XYZMODEM_H_
#define _XYZMODEM_H_

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/
#include "dbg.h"

/*****************************************************************************/
/* Constant Definitions                                                      */
/*****************************************************************************/
#define xyzModem_xmodem 1
#define xyzModem_ymodem 2
/* Don't define this until the protocol support is in place */
/*#define xyzModem_zmodem 3 */

#define xyzModem_access   -1
#define xyzModem_noZmodem -2
#define xyzModem_timeout  -3
#define xyzModem_eof      -4
#define xyzModem_cancel   -5
#define xyzModem_frame    -6
#define xyzModem_cksum    -7
#define xyzModem_sequence -8
#define xyzModem_ops      -9

#define xyzModem_close 1
#define xyzModem_abort 2
#define xyzModem_testc 3


#ifdef REDBOOT
extern getc_io_funcs_t xyzModem_io;
#else
#define CYGNUM_CALL_IF_SET_COMM_ID_QUERY_CURRENT
#define CYGACC_CALL_IF_SET_CONSOLE_COMM(x)

#define diag_printf(fmt, ...)       dbg(fmt, ##__VA_ARGS__)
#ifdef DEBUG
#define diag_vsprintf vsprintf
#define diag_vprintf vsnprintf
#endif /* DEBUG */

#define CYGACC_CALL_IF_DELAY_US(x) udelay(x)

/*****************************************************************************/
/* Structs                                                                   */
/*****************************************************************************/
typedef void (*xyzmdm_putc_func_t)(char ch);
typedef char (*xyzmdm_getc_func_t)(void);
typedef bool (*xyzmdm_tstc_func_t)(void);

typedef struct {
    xyzmdm_putc_func_t putc;
    xyzmdm_getc_func_t getc;
    xyzmdm_tstc_func_t tstc;
} xyzmdm_ops_t;

typedef struct {
    int   mode;
#ifdef CYGPKG_REDBOOT_NETWORKING
    struct sockaddr_in *server;
#endif
    xyzmdm_ops_t ops;
} connection_info_t;

#endif

/*****************************************************************************/
/* Export Functions                                                          */
/*****************************************************************************/
int  xyzModem_stream_open(connection_info_t *info, int *err);
void xyzModem_stream_close(int *err);
void xyzModem_stream_terminate(bool method);
int  xyzModem_stream_read(char *buf, int size, int *err);
char *xyzModem_error(int err);

#endif /* _XYZMODEM_H_ */
