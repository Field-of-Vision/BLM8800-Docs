#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#define CDEV_BUF_MAX    256
#define WLAN_SET_LEN    8
#define APP_NAME        "[APP/fasync] "

#define FASYNC_MSG_1    "3003"      // CUST_CMD_CONNECT_IND
#define FASYNC_MSG_2    "3017"      // CUST_CMD_START_AP_IND
#define FASYNC_MSG_LEN  2

struct rwnx_fasync_info
{
    int mem_status;
    char mem[CDEV_BUF_MAX];
};

struct wlan_settings
{
    unsigned int ip;
    unsigned int gw;
};

unsigned int str2uint(char * const str)
{
    char ch; int i;
    unsigned int value = 0;
    for(i=WLAN_SET_LEN-1; i>=0; i--) {
        ch = *(str + i);
        if('0'<=ch && ch<='9') {
            ch = ch - '0';
        } else if ('A'<=ch && ch<='F') {
            ch = ch - 'A' + 10;
        } else if ('a'<=ch && ch<='f') {
            ch = ch - 'a' + 10;
        }
        value |= (ch & 0xff) << (4 * (WLAN_SET_LEN-1-i));
    }
    return value;
}

char *fasync_msg[FASYNC_MSG_LEN] = {
    FASYNC_MSG_1,
    FASYNC_MSG_2
};

void analy_signal_msg(char *mem)
{
    char buff[64];
    struct wlan_settings wlan;
    // auto wlan-settings
    for (int i=0; i<FASYNC_MSG_LEN; i++) {
        char *ptr = strstr(mem, fasync_msg[i]);
        if (!ptr)
            continue;
        switch (i) {
            case 0:
            case 1:
                // set vnet0 ip
                ptr = strstr(mem, "ip");
                memcpy(buff, ptr+4, WLAN_SET_LEN);
                wlan.ip = str2uint(buff);
                sprintf(buff, "ifconfig vnet0 %d.%d.%d.%d",
                        (unsigned int)((wlan.ip >> 0 )&0xFF), (unsigned int)((wlan.ip >> 8 )&0xFF),
                        (unsigned int)((wlan.ip >> 16)&0xFF), (unsigned int)((wlan.ip >> 24)&0xFF));
                system(buff);

                // set vnet0 gw
                memcpy(buff, ptr+18, WLAN_SET_LEN);
                wlan.gw = str2uint(buff);
                sprintf(buff, "route add default gw %d.%d.%d.%d",
                        (unsigned int)((wlan.gw >> 0 )&0xFF), (unsigned int)((wlan.gw >> 8 )&0xFF),
                        (unsigned int)((wlan.gw >> 16)&0xFF), (unsigned int)((wlan.gw >> 24)&0xFF));
                system(buff);
                system("ifconfig");
                system("route -n");
                break;
            default:
                printf("default setting.\n");
        }
    }
}

int fd;
static void signal_handler(int signum)
{
    int ret = 0;
    char data_buf[sizeof(struct rwnx_fasync_info)];
    struct rwnx_fasync_info *fsy_info = (struct rwnx_fasync_info *)data_buf;
    ret = read(fd, data_buf, sizeof(struct rwnx_fasync_info));
    if(ret < 0) {
        printf(APP_NAME "Read kernel-data fail\n");
    } else {
        printf(APP_NAME "%s\n", fsy_info->mem);
        fsy_info->mem_status = 0;
        ret = write(fd, &fsy_info->mem_status, sizeof(fsy_info->mem_status));
        if (ret < 0)
            printf(APP_NAME "Write kernel-data fail\n");

        analy_signal_msg(fsy_info->mem);
    }
}

int main(int argc, char *argv[])
{
    int flag;
    char *filename = "/dev/aic_cdev";
    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf(APP_NAME "Can't open cdev-file %s\r\n", filename);
        return -1;
    }
    printf(APP_NAME "Open cdev: %s\r\n", filename);

    signal(SIGIO, signal_handler);

    fcntl(fd, F_SETOWN, getpid());
    flag = fcntl(fd, F_GETFD);
    fcntl(fd, F_SETFL, flag|FASYNC);

    while(1)
       sleep(2);
    return 0;
}

