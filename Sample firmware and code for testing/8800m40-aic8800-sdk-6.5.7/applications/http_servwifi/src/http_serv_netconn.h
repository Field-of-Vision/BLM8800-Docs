#ifndef _HTTP_SERV_NETCONN_H_
#define _HTTP_SERV_NETCONN_H_

#define HTTP_FATFS_SELECTION        0 // 0:disabled, 1:sdmmc, 2:usb

void http_server_netconn_init(void);
void http_server_netconn_stop(void);

#endif /* _HTTP_SERV_NETCONN_H_ */
