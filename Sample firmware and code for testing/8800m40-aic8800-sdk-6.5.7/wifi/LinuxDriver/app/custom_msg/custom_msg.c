#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if.h>
#include <net/if_arp.h> /* for ARPHRD_ETHER */

#define DOWN                0
#define UP                  1
#define MAX_DRV_CMD_SIZE    1536
#define APP_NAME            "[APP/custmsg] "

typedef struct android_wifi_priv_cmd {
    char *buf;
    int used_len;
    int total_len;
} android_wifi_priv_cmd;

int wifi_send_cmd_to_net_interface(const char* if_name, int argC, char *argV[])
{
    struct ifreq ifr;
    int ret = 0, i = 0, sock;
    char buf[MAX_DRV_CMD_SIZE];
    struct android_wifi_priv_cmd priv_cmd;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        printf(APP_NAME "bad sock!\n");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, if_name);

    if (ioctl(sock, SIOCGIFFLAGS, &ifr) != 0) {
        printf(APP_NAME "Could not read interface %s flags: %s\n", if_name, strerror(errno));
        return -1;
    }
    if (!(ifr.ifr_flags & IFF_UP)) {
        printf(APP_NAME "%s is not up!\n",if_name);
        return -1;
    }

    memset(&priv_cmd, 0, sizeof(priv_cmd));
    memset(buf, 0, sizeof(buf));
    for (i = 2; i < argC; i++) {
        strcat(buf, argV[i]);
        if (i < (argC - 1)) {
            strcat(buf, " ");
        }
    }

    priv_cmd.buf = buf;
    priv_cmd.used_len = strlen(buf);
    priv_cmd.total_len = sizeof(buf);
    ifr.ifr_data = (void*)&priv_cmd;

    if ((ret = ioctl(sock, SIOCDEVPRIVATE+2, &ifr)) < 0) {
        printf(APP_NAME "fail to ioctl, ret = %d\n", ret);
        return ret;
    }

    memcpy(&priv_cmd, ifr.ifr_data, sizeof(struct android_wifi_priv_cmd));
    // If don`t need return-result, it`s OK to comment out this printf.
    printf(APP_NAME "%s\n", (char *)&priv_cmd.buf[0]);

    close(sock);
    return ret;
}


int if_updown(const char *ifname, int flag)
{
    int sock, ret;
    struct ifreq ifr;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("fail to create socket !\n");
        return -1;
    }

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);

    if((ret = ioctl(sock, SIOCGIFFLAGS, &ifr) ) == 0) {
        if ( flag == DOWN )
            ifr.ifr_flags &= ~IFF_UP;
        else if ( flag == UP )
            ifr.ifr_flags |= IFF_UP;
    }

    if ((ret = ioctl(sock, SIOCSIFFLAGS, &ifr) ) != 0)
        printf("fail to set ifr-flag !\n");

    close(sock);
    return ret;
}

int wifi_send_cmd_to_net_device(const char* if_name, int argC, char *argV[])
{
    int sock, i;
    struct ifreq ifr;
    char buf[32] = {0};
    char buf_mac[32] = {0};

    if(argC != 9) {
        printf("param error !\n");
        return -1;
    }
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, if_name);
    for(i = 0; i < 6; i++)
        buf_mac[i] = strtol(argV[i+3], NULL, 16);

    // set net_dev mac
    if(if_updown((const char *)if_name, DOWN) != 0) {
        printf("fail to set net-if down !\n");
        return -2;
    }
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -3;
    }
    ifr.ifr_addr.sa_family = ARPHRD_ETHER;
    strncpy(ifr.ifr_name, (const char *)if_name, IFNAMSIZ - 1);
    memcpy((unsigned char *)ifr.ifr_hwaddr.sa_data, buf_mac, 6);
    if ( (ioctl(sock, SIOCSIFHWADDR, &ifr)) != 0 ){
        perror("SIOCSIFHWADDR");
    }
    if(if_updown((const char *)if_name, UP) != 0) {
        printf("fail to set net-if up !\n");
        close(sock);
        return -4;
    }

    // get net_dev mac after setting
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        perror("SIOCGIFHWADDR");
        return -5;
    }
    memcpy(buf, ifr.ifr_hwaddr.sa_data, 6);
    printf("Get net_dev mac: ");
    for (i = 0; i < 6; i++)
        printf("%02x:", buf[i] & 0xff);
    puts("\b ");

    close(sock);
    return 0;
}

char *str_help = "usage: custom_msg vnet0 [mode] <arg1> <arg2> <arg3>\r\n"
                 "---------------------\r\n"
                 ">>>Interact with MCU:\r\n"
                 "custom_msg vnet0 1 ssid password          - connect ap\r\n"
                 "custom_msg vnet0 2                        - disconnect ap\r\n"
                 "custom_msg vnet0 3                        - open ble\r\n"
                 "custom_msg vnet0 4                        - close ble before sleep if used\r\n"
                 "custom_msg vnet0 5                        - enter sleep\r\n"
                 "custom_msg vnet0 6                        - exit sleep\r\n"
                 "custom_msg vnet0 7                        - get mcu mac\r\n"
                 "custom_msg vnet0 8                        - get wlan status\r\n"
                 "custom_msg vnet0 9 ssid password band     - start ap\r\n"
                 "                   -- band = <2.4G/5G>\r\n"
                 "custom_msg vnet0 10                       - change ap mode\r\n"
                 "custom_msg vnet0 11                       - stop ap\r\n"
                 "custom_msg vnet0 12                       - scan wifi\r\n"
                 "custom_msg vnet0 13 /your-path/update.bin - host ctrl OTA\r\n"
                 "------------------------\r\n"
                 ">>>Interact with kernel:\r\n"
                 "sudo custom_msg vnet0 ndev mac_address    - set vnet_dev mac\r\n";


int main(int argC, char *argV[])
{
    if(argC >= 3) {
        if(!strcasecmp(argV[2], "ndev"))
            wifi_send_cmd_to_net_device(argV[1], argC, argV);
        else
            wifi_send_cmd_to_net_interface(argV[1], argC, argV);
    } else {
        printf("%s\n", str_help);
    }
    return 0;
}

