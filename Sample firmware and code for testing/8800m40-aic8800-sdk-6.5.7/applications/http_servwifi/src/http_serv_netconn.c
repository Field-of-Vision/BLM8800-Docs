#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"

#include "http_serv_netconn.h"

#if LWIP_NETCONN

#if HTTP_FATFS_SELECTION
#include "ff.h"
#include <string.h>
#if   HTTP_FATFS_SELECTION == 1
#define FATFS_DRIVE_ID      "SD:"
#elif HTTP_FATFS_SELECTION == 2
#define FATFS_DRIVE_ID      "USB:"
#endif
#endif

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG         LWIP_DBG_OFF
#endif

int http_server_stopped = 0;

#if !HTTP_FATFS_SELECTION
static const char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
static const char http_index_html[] = "<html><head><title>Congrats!</title></head><body><h1>Welcome to our lwIP HTTP server!</h1><p>This is a small test page, served by httpserver-netconn.</body></html>";

#else
static const char http_badreq_hdr[] = "HTTP/1.1 400 Bad Request\r\nContent-type: text\r\nConnection: Close\r\n\r\n";
char http_header[1024] = "";
char http_buffer[4096] = "0123456789abcd\r\n";

const char * get_uri_type(const char *ext)
{
    const char *type_tbl[][2] = {
        {".txt",  "plain/text"},
        {".htm",  "text/html"},
        {".html", "text/html"},
        {".css",  "text/css"},
        {".js",   "text/javascript"},
        {".pdf",  "application/pdf"},
        {".gif",  "image/gif"},
        {".jpg",  "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".ico",  "image/x-icon"},
        {".png",  "image/png"},
        {".zip",  "image/zip"},
        {".gz",   "image/gz"},
        {".tar",  "image/tar"}
    };
    int idx;
    for(idx = 0; idx < (sizeof(type_tbl) / sizeof(type_tbl[0])); idx++) {
        if(strcmp(type_tbl[idx][0], ext) == 0) {
            break;
        }
    }
    if (idx >= (sizeof(type_tbl) / sizeof(type_tbl[0]))) {
        idx = 0;
    }
    return type_tbl[idx][1];
}

void get_uri_content(char *uri, struct netconn *conn)
{
    char fileName[128];
    char dirName[128];
    char *lstchr = strrchr(uri, '\0') - 1;
    FILINFO fi;
    int res;
    do {
        if('/' == *lstchr) {
            DIR d;
            dbg("Open dir " FATFS_DRIVE_ID "%s\n", uri);
            *lstchr = 0;
            dbg_snprintf(fileName, sizeof(fileName), FATFS_DRIVE_ID "%s", uri);
            dbg("dir: %s\n",fileName);
            res = f_opendir(&d, fileName);
            if (res) {
                dbg("Fail to open dir " FATFS_DRIVE_ID "%s\n", uri);
            }
            dbg_snprintf(http_buffer, sizeof(http_buffer), "<html><head><title>Directory Listing</title></head><body><h1>%s Directory Listing</h1><ul>", uri);
            while (1) {
                DIR sub_d;
                char *dir_str = "";
                res = f_readdir(&d, &fi);
                if ((res != FR_OK) || (fi.fname[0] == 0)) {
                    break;
                }
                dbg_snprintf(dirName, sizeof(dirName), "%s/%s", fileName, fi.fname);
                dbg("subdir/file: %s\n",dirName);
                res = f_opendir(&sub_d, dirName);
                if (res != FR_NO_PATH) {
                    dir_str = "/";
                    f_closedir(&sub_d);
                }
                dbg_snprintf(http_header, sizeof(http_header), "<li><a href=\"./%s%s\">%s</a></li>", fi.fname, dir_str, fi.fname);
                strcat(http_buffer, http_header);
            }
            f_closedir(&d);
            dbg("dir closed\n");
            strcat(http_buffer, "</ul></body></html>");
            dbg_snprintf(http_header, sizeof(http_header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\nConnection: Close\r\n\r\n", strlen(http_buffer));
            netconn_write(conn, http_header, strlen(http_header), NETCONN_NOCOPY);
            netconn_write(conn, http_buffer, strlen(http_buffer), NETCONN_NOCOPY);
            return;
        } else {
            FIL fh;
            unsigned int cnt;
            char *ext_str = strrchr(uri, '.');
            dbg_snprintf(fileName, sizeof(fileName), FATFS_DRIVE_ID "%s", uri);
            res = f_stat(fileName, &fi);
            if (res == FR_NO_FILE) {
                dbg("%s not exist\r\n", fileName);
                dbg_snprintf(http_buffer, sizeof(http_buffer), "<html><head><title>File Not Found</title></head><body><h1>404</h1><h2>File \"%s\" is not found.</h2></body></html>", uri);
                dbg_snprintf(http_header, sizeof(http_header), "HTTP/1.1 404 Not Found \r\nContent-Length: %ld\r\nContent-Type: text/html\r\nConnection: Close\r\n\r\n", strlen(http_buffer));
            } else if (res) {
                dbg("Fail to stat %s, res=%d\r\n", fileName, res);
                break;
            }
            dbg("open file: %s\n", fileName);
            res = f_open(&fh, fileName, FA_READ);
            if (res) {
                dbg("Fail to open %s, res=%d\r\n", fileName, res);
                break;
            }
            dbg("file size:%d, fptr:%d\n",f_size(&fh),f_tell(&fh));
            dbg_snprintf(http_header, sizeof(http_header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: %s\r\nConnection: Close\r\n\r\n", f_size(&fh), get_uri_type(ext_str));
            netconn_write(conn, http_header, strlen(http_header), NETCONN_NOCOPY);
            dbg("http_header: %s\n",http_header);
            do {
                res = f_read(&fh, http_buffer, 1024, &cnt);
                dbg("read file cnt:%d\n",cnt);
                if (res) {
                    dbg("Fail to read, res=%d, cnt=%d\r\n", res, cnt);
                    break;
                }
                netconn_write(conn, http_buffer, cnt, NETCONN_COPY);
            } while (f_tell(&fh) < f_size(&fh));
            f_close(&fh);
            dbg("file closed\n");
            return;
        }
    } while (0);
    strcpy(http_header, http_badreq_hdr);
    strcpy(http_buffer, "NULL");
    netconn_write(conn, http_header, strlen(http_header), NETCONN_NOCOPY);
    netconn_write(conn, http_buffer, strlen(http_buffer), NETCONN_NOCOPY);
}
#endif

/** Serve one HTTP connection accepted in the http thread */
static void
http_server_netconn_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  err_t err;

  /* Read the data from the port, blocking if nothing yet there.
   We assume the request (the part we care about) is in one netbuf */
  err = netconn_recv(conn, &inbuf);

  if (err == ERR_OK) {
    netbuf_data(inbuf, (void**)&buf, &buflen);

    #if HTTP_FATFS_SELECTION
    if (buflen >= 5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' ) {
        char *uri = buf + 4;
        char *eou = strstr(uri, " ");
        buf[buflen] = '\0';
        dbg("buf=%p,len=%d,[226:229]=%02X %02X %02X %02X\r\n\r\n",buf,buflen,buf[226],buf[227],buf[228],buf[229]);
        uart_puts(buf);
        if (eou) {
            *eou = '\0';
            get_uri_content(uri, conn);
        } else {
            netconn_write(conn, http_badreq_hdr, sizeof(http_badreq_hdr)-1, NETCONN_NOCOPY);
            netconn_write(conn, http_buffer, strlen(http_buffer), NETCONN_NOCOPY);
        }
    }
    #else
    /* Is this an HTTP GET command? (only check the first 5 chars, since
    there are other formats for GET, and we're keeping it very simple )*/
    if (buflen>=5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' &&
        buf[4]=='/' ) {

      /* Send the HTML header
             * subtract 1 from the size, since we dont send the \0 in the string
             * NETCONN_NOCOPY: our data is const static, so no need to copy it
       */
      netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);

      /* Send our HTML page */
      netconn_write(conn, http_index_html, sizeof(http_index_html)-1, NETCONN_NOCOPY);
    }
    #endif
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);

  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}

/** The main function, never returns! */
static void
http_server_netconn_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err;
  LWIP_UNUSED_ARG(arg);

  #if HTTP_FATFS_SELECTION
  char *fsid = FATFS_DRIVE_ID "/";
  FATFS fs;

  dbg("mount: %s\r\n",fsid);
  err = f_mount(&fs, fsid, 0);
  if (err) {
      dbg("Fail to mount, err=%d\r\n", err);
  }
  #endif

  /* Create a new TCP connection handle */
  /* Bind to port 80 (HTTP) with default IP address */
#if LWIP_IPV6
  conn = netconn_new(NETCONN_TCP_IPV6);
  netconn_bind(conn, IP6_ADDR_ANY, 80);
#else /* LWIP_IPV6 */
  conn = netconn_new(NETCONN_TCP);
  netconn_bind(conn, IP_ADDR_ANY, 80);
#endif /* LWIP_IPV6 */
  LWIP_ERROR("http_server: invalid conn", (conn != NULL), return;);

  /* Put the connection into LISTEN state */
  netconn_listen(conn);

  do {
    err = netconn_accept(conn, &newconn);
    if (err == ERR_OK) {
      http_server_netconn_serve(newconn);
      netconn_delete(newconn);
    }
    if (http_server_stopped) {
        err = ERR_ABRT;
    }
  } while(err == ERR_OK);
  LWIP_DEBUGF(HTTPD_DEBUG,
    ("http_server_netconn_thread: netconn_accept received error %d, shutting down",
    err));
  netconn_close(conn);
  netconn_delete(conn);
  #if HTTP_FATFS_SELECTION
  dbg("unmount: %s\r\n",fsid);
  err = f_mount(NULL, fsid, 0);
  if (err) {
      dbg("Fail to unmount, err=%d\r\n", err);
  }
  #endif
  rtos_task_delete(NULL);
}

/** Initialize the HTTP server (start its thread) */
void
http_server_netconn_init(void)
{
  sys_thread_new("http_server_netconn", http_server_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
/** Stop the HTTP server */
void http_server_netconn_stop(void)
{
    http_server_stopped = 1;
}

#endif /* LWIP_NETCONN*/
