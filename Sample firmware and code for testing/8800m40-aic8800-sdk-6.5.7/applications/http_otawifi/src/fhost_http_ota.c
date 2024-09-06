  /**
  *******************************************************************************
  *
  * @file fhost_http_ota.c
  *
  *******************************************************************************
  */

#include <string.h>
#include "fhost.h"
#include "wlan_if.h"
#include "lwip/api.h"
#include "flash_api_wifi.h"
#include "aic_ota.h"

// If SOFTAP_MODE_OTA=1, then start ap and http_server to receive a update.bin for OTA.
// If SOFTAP_MODE_OTA=0, then start sta to connect ap and start http_client to connect
// http_server to get a update.bin for OTA.
#define SOFTAP_MODE_OTA 1

static uint8_t http_ota_started = 0;
static uint32_t http_ota_img_len = 0;

/******************************************************************************
 * Application code:
 *****************************************************************************/
static const char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
static const char http_succ_html[] = "<html><body><font size=\"8\">success...</font></body></html>";
static const char http_main_html[] = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>Main</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style type=\"text/css\">.input{display: block; margin-top: 10px;}.btn{width: 120px; height: 35px; background-color: #2188ff; border:0px; color:#ffffff; margin-top:200px; margin-left:135px;}</style></head><body><form action=\"http://192.168.88.1/config\" method=\"get\"><button class=\"btn\" type=\"submit\" formaction=\"http://192.168.88.1/upgrade\">Upgrade</button></form></form></body></html>";
static const char http_upgrade_html[] = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>upgrade</title><style type=\"text/css\">body{ font-size:14px;}input{ vertical-align:middle; margin:0; padding:0}.file-box{ position:relative;width:340px}.txt{ height:22px; border:1px solid #cdcdcd; width:180px;}.btn{ background-color:#FFF; border:1px solid #CDCDCD;height:24px; width:70px;}.file{ position:absolute; top:0; right:80px; height:24px; filter:alpha(opacity:0);opacity: 0;width:260px }</style>"
                                        "<script>"
                                        "function fileSelected() {var file = document.getElementById('fileField').files[0];if (file) {var fileSize = 0;if (file.size > 1024 * 1024)fileSize = (Math.round(file.size * 100 / (1024 * 1024)) / 100).toString() + 'MB'; else fileSize = (Math.round(file.size * 100 / 1024) / 100).toString() + 'KB'; document.getElementById('textfield').value = file.name + '(' + fileSize + ')';var xhr = new XMLHttpRequest();xhr.open(\"POST\", \"http://192.168.88.1/sz\");xhr.setRequestHeader(\"FileSize\", file.size);xhr.send();}}"
                                        "function uploadFile(){var fd = new FormData();var file = document.getElementById('fileField').files[0];fd.append(\"fileInfo\", file);var xhr = new XMLHttpRequest();xhr.upload.addEventListener(\"progress\", uploadProgress, false);xhr.addEventListener(\"load\", uploadComplete, false);xhr.addEventListener(\"error\", uploadFailed, false);xhr.open(\"POST\", \"http://192.168.88.1/ul\");xhr.setRequestHeader(\"FileSize\", file.size);xhr.send(fd);}"
                                        "function uploadProgress(evt){if(evt.lengthComputable){var percentComplete = Math.round(evt.loaded * 100 / evt.total);document.getElementById('progressNumber').innerHTML = percentComplete.toString() + '%';} else {document.getElementById('progressNumber').innerHTML = 'unable to compute';}}"
                                        "function uploadComplete(evt){alert(evt.target.responseText);}"
                                        "function uploadFailed(evt){alert(\"ERROR!\");}"
                                        "</script>"
                                        "</head><body><div class=\"file-box\"><form action=\"\" method=\"\" enctype=\"multipart/form-data\"><input type='text' name='textfield' id='textfield' class='txt' value='File ends with .bin'/><input type='button' class='btn' value='Select...' /><input type=\"file\" name=\"fileField\" class=\"file\" id=\"fileField\" accept=\".bin\" size=\"28\" onchange=\"fileSelected()\" /><input type=\"submit\" name=\"submit\" class=\"btn\" value=\"Upload\" onclick=\"uploadFile()\" /></form></div><div id=\"progressNumber\"></div></body></html>";

void dbg_long_buf(char *buf, u16_t len)
{
    char dbgbuf[257], *ptr;
    uint32_t number = len >> 8;
    uint32_t remain = len & 0xff;

    ptr = buf;
    dbg("buf: ");
    for (int i=0; i<number; i++) {
        memset(dbgbuf, 0, 257);
        memcpy(dbgbuf, ptr, 256);
        ptr += 256;
        dbg("%s", dbgbuf);
    }
    if(remain != 0) {
        memset(dbgbuf, 0, 257);
        memcpy(dbgbuf, ptr, remain);
        dbg("%s", dbgbuf);
    }
    dbg("\n");
}

char *aic_strstr(char* src, char* sub, int len)
{
    char *bp;
    char *sp;
    if(src==NULL || NULL==sub) {
        return src;
    }
    for(int i = 0; i < len; i++) {
        bp=src;
        sp=sub;
        do
        {
            if(!*sp)
                return src;
        }while(*bp++ == *sp++);
        src += 1;
    }
    return NULL;
}

void http_server_ota(void)
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
        dbg("accept = %d\n",err);
        if (err == ERR_OK) {
            struct netbuf *inbuf;
            char *buf;
            u16_t buflen;
            if (netconn_recv(newconn, &inbuf) == ERR_OK) {
                netbuf_data(inbuf, (void**)&buf, &buflen);
                buf[buflen] = '\0';
                dbg("buflen=%d\n", buflen);
                if (buflen > 256)
                    dbg_long_buf(buf, buflen);
                else
                    dbg("buf: %s\n", buf);

                if (buflen>=5 &&
                    buf[0]=='G' &&
                    buf[1]=='E' &&
                    buf[2]=='T' &&
                    buf[3]==' ' &&
                    buf[4]=='/' ) {
                    char *uri = buf + 5;
                    //char *pat;
                    uart_puts(buf);
                    if(strstr(uri, "upgrade?")) {
                        /* Send the HTML header */
                        netconn_write(newconn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
                        dbg("upgrade size %d\r\n", sizeof(http_upgrade_html));
                        /* Send our upgrade page */
                        netconn_write(newconn, http_upgrade_html, 1024, NETCONN_NOCOPY);
                        netconn_write(newconn, &http_upgrade_html[1024], 1024, NETCONN_NOCOPY);
                        netconn_write(newconn, &http_upgrade_html[2048], sizeof(http_upgrade_html)-2048-1, NETCONN_NOCOPY);
                    }
                    else {
                        /* Send the HTML header */
                        netconn_write(newconn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);

                        /* Send our Main page */
                        netconn_write(newconn, http_main_html, sizeof(http_main_html)-1, NETCONN_NOCOPY);
                    }
                }else if(buflen>=6 &&
                    buf[0]=='P' &&
                    buf[1]=='O' &&
                    buf[2]=='S' &&
                    buf[3]=='T' &&
                    buf[4]==' ' &&
                    buf[5]=='/') {
                    uart_puts(buf);
                    char *uri = buf + 6;
                    char *pat;
                    if (strstr(uri, "sz")) {
                        uri += 7;
                        pat = strstr(uri, "FileSize: ");
                        if (pat) {
                            char *len_str = pat + 10;
                            int len = atoi(len_str);
                            uint32_t ota_addr;
                            http_ota_img_len = len;
                            #ifndef CFG_LZMA_APP
                            ota_addr = OTA_ADDR + OTA_INFO_SIZE;
                            #else
                            ota_addr = OTA_ADDR;
                            #endif
                            ota_start(ota_addr, http_ota_img_len);
                            http_ota_started = 1;
                        }
                    }
                    if ((strstr(uri, "ul")) && http_ota_started) {
                        static uint32_t rx_len = 0;
                        struct netbuf *inbuf1;
                        while(netconn_recv(newconn, &inbuf1) == ERR_OK) {
                            netbuf_data(inbuf1, (void**)&buf, &buflen);
                            char *pat = buf;
                            char *start_str = "------WebKitFormBoundary1AKB5w7cgCzATuDh";
                            //char *end_str = "\r\n------WebKitFormBoundary";
                            char *common_str = "------WebKitFormBoundary";
                            uint16_t temp_size = strlen(start_str);
                            //dbg("OTA buflen %d\r\n", buflen);
                            if ((buflen > temp_size) && \
                                ((pat = aic_strstr(buf, common_str, buflen)) &&
                                (((buf[temp_size] == '\r') && (buf[temp_size+1] == '\n'))  ||
                                ((pat[temp_size] == '\r') && (pat[temp_size+1] == '\n'))))) {
                                uart_puts(pat);
                                pat = strstr(buf + temp_size, "\r\n\r\n");
                                if(pat) { // first boundary
                                    pat += 4;
                                    dbg("buf %x %x\r\n", buf, pat);
                                    ota_write((const uint8_t *)pat, (buflen-(pat-buf)));
                                    rx_len += (buflen-(pat-buf));
                                } else { // last boundary
                                    #if 0
                                    pat = aic_strstr(buf, end_str, buflen);
                                    dbg("last buf %x %x\r\n", buf,  pat);
                                    ota_write((const uint8_t *)buf, (pat-buf));
                                    rx_len += (pat-buf);
                                    #else
                                    u16_t wr_len = ((rx_len + buflen) > http_ota_img_len) ? (http_ota_img_len - rx_len) : buflen;
                                    ota_write((const uint8_t *)buf, wr_len);
                                    rx_len += wr_len;
                                    #endif
                                }
                            } else {
                                u16_t wr_len = ((rx_len + buflen) > http_ota_img_len) ? (http_ota_img_len - rx_len) : buflen;
                                ota_write((const uint8_t *)buf, wr_len);
                                rx_len += wr_len;
                            }
                            netbuf_delete(inbuf1);

                            //dbg("rx_len %d, img_len %d\r\n", rx_len, http_ota_img_len);
                            if (rx_len == http_ota_img_len) {
                                ota_end();
                                dbg("OTA data receive over!\r\n");
                                netconn_write(newconn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
                                /* Send our HTML page */
                                netconn_write(newconn, http_succ_html, sizeof(http_succ_html)-1, NETCONN_NOCOPY);
                                info_got = 1;
                                break;
                            }
                        }
                        rx_len = 0;
                        http_ota_started = 0;
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
    } while (!info_got);
    netconn_close(conn);
    netconn_delete(conn);
}


#define SERVER_IP           "192.168.124.2"   //http server ip
#define SERVER_PORT         80
#define HTTP_VERSION        "HTTP/1.1"
#define CONNECTION_TYPE     "Connection: close\r\n"

int http_client_ota(void)
{
    struct netconn *newconn;
    err_t err;
    int info_got = 0;
    char send_buffer[1024];
    char *path = "/host_wb_update.bin";   //file-path in server

    ip_addr_t server_ip;
    if (ipaddr_aton(SERVER_IP, &server_ip) == 0) {
        dbg("Failed to transfer ipaddr.\n");
        return -1;
    }

    newconn = netconn_new(NETCONN_TCP);
    if (newconn == NULL) {
        dbg("Failed to allocate socket.\n");
        return -1;
    }

    err = netconn_connect(newconn, &server_ip, SERVER_PORT);
    if (err != ERR_OK) {
        dbg("Failed to connect.\n");
        goto exit2;
    }

    dbg_snprintf(send_buffer,sizeof(send_buffer),
                "GET %s %s\r\nHost: %s\r\n\%s\r\n",
                path, HTTP_VERSION,
                SERVER_IP,
                CONNECTION_TYPE);
    dbg("http_request_init:\n%s\r\n", send_buffer);

    err = netconn_write(newconn, send_buffer, strlen(send_buffer), NETCONN_NOCOPY);
    if (err != ERR_OK) {
        dbg("Failed to send request.\n");
        goto exit1;
    }

    do {
        struct netbuf *inbuf;
        char *buf;
        u16_t buflen;
        if (netconn_recv(newconn, &inbuf) == ERR_OK) {
            netbuf_data(inbuf, (void**)&buf, &buflen);
            buf[buflen] = '\0';
            dbg("buflen=%d\n", buflen);
            if (buflen > 256)
                dbg_long_buf(buf, buflen);
            else
                dbg("buf: %s\n", buf);

            static uint32_t rx_len = 0;
            char *uri = buf;
            char *pat1;
            pat1 = strstr(uri, "Content-Length: ");
            if (pat1) {
                char *len_str = pat1 + 16;
                uint32_t ota_addr;
                http_ota_img_len = atoi(len_str);
                dbg("FileSize: %d\n", http_ota_img_len);
                #ifndef CFG_LZMA_APP
                ota_addr = OTA_ADDR + OTA_INFO_SIZE;
                #else
                ota_addr = OTA_ADDR;
                #endif
                ota_start(ota_addr, http_ota_img_len);
                char *pat = buf;
                char *start_str = "Connection: Keep-Alive";
                uint16_t temp_size = strlen(start_str);
                if((pat = aic_strstr(buf, start_str, buflen)) &&
                    (((buf[temp_size] == '\r') && (buf[temp_size+1] == '\n')) ||
                    ((pat[temp_size] == '\r') && (pat[temp_size+1] == '\n')))) {
                    pat = strstr(buf + temp_size, "\r\n\r\n");
                    if(pat) {
                        pat += 4;
                        dbg("buf %x %x\r\n", buf, pat);
                        ota_write((const uint8_t *)pat, (buflen-(pat-buf)));
                        rx_len += (buflen-(pat-buf));
                    }
                }
                http_ota_started = 1;
            }

            if (http_ota_started) {
                struct netbuf *inbuf1;
                while(netconn_recv(newconn, &inbuf1) == ERR_OK) {
                    netbuf_data(inbuf1, (void**)&buf, &buflen);
                    //dbg("buflen=%d\n", buflen);
                    //dbg("buf: %s\n", buf);
                    u16_t wr_len = ((rx_len + buflen) > http_ota_img_len) ? (http_ota_img_len - rx_len) : buflen;
                    ota_write((const uint8_t *)buf, wr_len);
                    rx_len += wr_len;

                    netbuf_delete(inbuf1);
                    //dbg("rx_len %d, img_len %d\r\n", rx_len, http_ota_img_len);
                    if (rx_len == http_ota_img_len) {
                        ota_end();
                        dbg("OTA data receive over!\r\n");
                        info_got = 1;
                        break;
                    }
                }
                rx_len = 0;
                http_ota_started = 0;
            }
            /* Delete the buffer */
            netbuf_delete(inbuf);
        }
    }while(!info_got);

exit1:
    netconn_close(newconn);
exit2:
    netconn_delete(newconn);
    return 0;
}

/*
 * Entry point of this example application
 */
static RTOS_TASK_FCT(fhost_http_ota_task)
{
    do {
        #if SOFTAP_MODE_OTA
        int ret;
        char *ssid = "SSID", *pw = "password";
        ret = wlan_start_ap(0, (uint8_t *)ssid, (uint8_t *)pw);
        if (ret) {
            dbg("AP start err: %d\n", ret);
            break;
        }
        dbg("AP started.\r\n");

        http_server_ota();
        wlan_stop_ap();

        #else
        int ret = 0;
        char *ssid = "SSID", *pw = "SSID";
        ret = wlan_start_sta((uint8_t *)ssid, (uint8_t *)pw, 0);
        if (ret) {
            dbg("Connect to AP fail %d\r\n", ret);
            break;
        }
        dbg("Connect to AP.\r\n");

        http_client_ota();
        wlan_disconnect_sta(0);
        #endif
    } while (0);

    rtos_task_delete(NULL);
}

/*
 * fhost_application_init: Must initialize the minimum for the application to
 *                         start.
 * In this example only create a new task with the entry point set to the
 * 'fhost_example_task'. The rest on the initialization will be done in this
 * function.
 */
int fhost_application_init(void)
{
    if (rtos_task_create(fhost_http_ota_task, "HTTP OTA task", APPLICATION_TASK,
                         1024, NULL, RTOS_TASK_PRIORITY(1), NULL))
        return 1;

    return 0;
}

