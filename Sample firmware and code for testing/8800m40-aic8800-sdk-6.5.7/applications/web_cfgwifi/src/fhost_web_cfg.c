 /**
 *******************************************************************************
 *
 * @file fhost_web_cfg.c
 *
 *******************************************************************************
 */

#include "fhost.h"
#include "wlan_if.h"
#include "lwip/api.h"

/******************************************************************************
 * Application code:
 *****************************************************************************/
rtos_task_handle web_cfg_task_handle = NULL;
static const char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
static const char http_info_html[] = "<!DOCTYPE html><html><head><title>Web Cfg</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>"
    "<style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #2188ff; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style>"
    "<body><form method=\"GET\" action=\"connect\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\"></label><label class=\"input\"><span>Password</span><input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\"></body></html>";
static const char http_succ_html[] = "<html><body><font size=\"8\">Connecting...</font></body></html>";
void web_cfg_get_info(char *new_ssid, char *new_pw)
{
    struct netconn *conn, *newconn;
    err_t err;
    int info_got = 0;
    /* Create a new TCP connection handle */
    /* Bind to port 80 (HTTP) with default IP address */
    conn = netconn_new(NETCONN_TCP);
    netconn_bind(conn, IP_ADDR_ANY, 80);
    /* Put the connection into LISTEN state */
    netconn_listen(conn);
    do {
        err = netconn_accept(conn, &newconn);
        if (err == ERR_OK) {
            struct netbuf *inbuf;
            char *buf;
            u16_t buflen;
            err_t err;
            err = netconn_recv(newconn, &inbuf);
            if (err == ERR_OK) {
                netbuf_data(inbuf, (void**)&buf, &buflen);
                //dbg("buflen=%d\n",buflen);
                buf[buflen] = '\0';
                if (buflen>=5 &&
                    buf[0]=='G' &&
                    buf[1]=='E' &&
                    buf[2]=='T' &&
                    buf[3]==' ' &&
                    buf[4]=='/' ) {
                    char *uri = buf + 5;
                    char *pat;
                    //uart_puts(buf);
                    pat = strstr(uri, "connect?");
                    if (pat) {
                        uri += 8;
                        pat = strstr(uri, "ssid=");
                        if (pat) {
                            char *sos = pat + 5;
                            char *eos = strstr(sos, "&");
                            int len = eos - sos;
                            //dbg("ssid len=%d\r\n",len);
                            strncpy(new_ssid, sos, len);
                            new_ssid[len] = '\0';
                        }
                        pat = strstr(uri, "pass=");
                        if (pat) {
                            char *sop = pat + 5;
                            char *eop = strstr(sop, "&");
                            int len = eop - sop;
                            //dbg("pw len=%d\r\n",len);
                            strncpy(new_pw, sop, len);
                            new_pw[len] = '\0';
                        }
                        info_got = 1;
                        /* Send the HTML header */
                        netconn_write(newconn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
                        /* Send our HTML page */
                        netconn_write(newconn, http_succ_html, sizeof(http_succ_html)-1, NETCONN_NOCOPY);
                    } else {
                        /* Send the HTML header */
                        netconn_write(newconn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
                        /* Send our HTML page */
                        netconn_write(newconn, http_info_html, sizeof(http_info_html)-1, NETCONN_NOCOPY);
                    }
                } else {
                    uart_puts("unsupported:\r\n");
                    uart_puts(buf);
                }
            }
            /* Close the connection (server closes in HTTP) */
            netconn_close(newconn);
            /* Delete the buffer */
            netbuf_delete(inbuf);
            /* Delete the connection */
            netconn_delete(newconn);
        }
    } while ((err == ERR_OK) && !info_got);
    netconn_close(conn);
    netconn_delete(conn);
}

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(fhost_web_cfg_task)
{
    do {
        int ret;
        char *ssid = "MySSID", *pw = "password";
        char new_ssid[32], new_pw[32];
        ret = wlan_start_ap(0, (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }
        dbg("AP started\r\n");
        web_cfg_get_info(new_ssid, new_pw);
        wlan_stop_ap();
        dbg("get info: ssid=%s, pw=%s\r\n", new_ssid, new_pw);
        rtos_task_suspend(1000);
        ret = wlan_start_sta((uint8_t *)new_ssid, (uint8_t *)new_pw, 0);
        if (ret) {
            dbg("STA connect fail: %d\r\n", ret);
            break;
        }
        wlan_connected = 1;
        dbg("STA connected\r\n");
    } while (0);
    rtos_task_delete(NULL);
}

/******************************************************************************
 * Fhost FW interfaces:
 * These are the functions required by the fhost FW that are specific to the
 * final application.
 *****************************************************************************/
/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_task_create(fhost_web_cfg_task, "Web cfg task", APPLICATION_TASK,
                         512, NULL, RTOS_TASK_PRIORITY(1), &web_cfg_task_handle))
        return 1;

    return 0;
}
