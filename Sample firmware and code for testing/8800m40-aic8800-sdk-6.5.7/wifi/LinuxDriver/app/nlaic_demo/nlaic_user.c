#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include <linux/genetlink.h>

#include "nlaic.h"


/*
 * Generic macros for dealing with netlink sockets
 */
#define GENLMSG_DATA(glh)       ((void *)(NLMSG_DATA(glh) + GENL_HDRLEN))
#define GENLMSG_PAYLOAD(glh)    (NLMSG_PAYLOAD(glh, 0) - GENL_HDRLEN)
#define NLA_DATA(na)            ((void *)((char*)(na) + NLA_HDRLEN))
#define NLA_PAYLOAD(len)        (len - NLA_HDRLEN)

#define MAX_MSG_SIZE            (1500 + NLA_HDRLEN)
#define DEBUG                   1

#define PRINTF(fmt, arg...) {   \
    if (DEBUG) {                \
        printf(fmt, ##arg);     \
    }                           \
}

struct msgtemplate {
    struct nlmsghdr n;
    struct genlmsghdr g;
    char buf[MAX_MSG_SIZE];
};


/*
 * Create a raw netlink socket and bind
 */
static int user_create_nl_socket(int protocol)
{
    int fd;
    struct sockaddr_nl local;

    fd = socket(AF_NETLINK, SOCK_RAW, protocol);
    if (fd < 0)
        return -1;

    memset(&local, 0, sizeof(local));
    local.nl_family = AF_NETLINK;
    local.nl_pid = getpid();

    if (bind(fd, (struct sockaddr *) &local, sizeof(local)) < 0)
        goto error;

    return fd;

error:
    close(fd);
    return -1;
}


static int user_send_cmd(int sd, __u16 nlmsg_type, __u32 nlmsg_pid,
         __u8 genl_cmd, __u16 nla_type,
         void *nla_data, int nla_len)
{
    struct nlattr *na;
    struct sockaddr_nl nladdr;
    int r, buflen;
    char *buf;

    struct msgtemplate msg;

    msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
    msg.n.nlmsg_type = nlmsg_type;
    msg.n.nlmsg_flags = NLM_F_REQUEST;
    msg.n.nlmsg_seq = 0;
    msg.n.nlmsg_pid = nlmsg_pid;
    msg.g.cmd = genl_cmd;
    msg.g.version = NLAIC_GENL_VERSION;
    na = (struct nlattr *) GENLMSG_DATA(&msg);
    na->nla_type = nla_type;
    na->nla_len = nla_len + NLA_HDRLEN;
    memcpy(NLA_DATA(na), nla_data, nla_len);
    msg.n.nlmsg_len += NLMSG_ALIGN(na->nla_len);

    buf = (char *) &msg;
    buflen = msg.n.nlmsg_len;
    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;

    while ((r = sendto(sd, buf, buflen, 0, (struct sockaddr *) &nladdr,
               sizeof(nladdr))) < buflen) {
        if (r > 0) {
            buf += r;
            buflen -= r;
        } else if (errno != EAGAIN)
            return -1;
    }

    return 0;
}


/*
 * Probe the controller in genetlink to find the family id
 * for the DEMO_GEN_CTRL family
 */
static int user_get_family_id(int sd)
{
    struct msgtemplate ans;

    char name[100];
    int id = 0, ret;
    struct nlattr *na;
    int rep_len;

    strcpy(name, NLAIC_GENL_NAME);
    ret = user_send_cmd(sd, GENL_ID_CTRL, getpid(), CTRL_CMD_GETFAMILY,
            CTRL_ATTR_FAMILY_NAME, (void *)name, strlen(NLAIC_GENL_NAME)+1);
    if (ret < 0)
        return 0;

    rep_len = recv(sd, &ans, sizeof(ans), 0);
    if (ans.n.nlmsg_type == NLMSG_ERROR || (rep_len < 0) || !NLMSG_OK((&ans.n), rep_len))
        return 0;

    na = (struct nlattr *) GENLMSG_DATA(&ans);
    na = (struct nlattr *) ((char *) na + NLA_ALIGN(na->nla_len));
    if (na->nla_type == CTRL_ATTR_FAMILY_ID) {
        id = *(__u16 *) NLA_DATA(na);
    }

    return id;
}


int user_check_msg(struct msgtemplate msg, int rep_len)
{
    if (msg.n.nlmsg_type == NLMSG_ERROR || !NLMSG_OK((&msg.n), rep_len)) {
        //PRINTF("nlmsg_type=%d, OK=%d\n",msg.n.nlmsg_type, NLMSG_OK((&msg.n), rep_len));
        struct nlmsgerr *err = NLMSG_DATA(&msg);
        fprintf(stderr, "fatal reply error,  errno %d\n", err->error);
        return -1;
    }

    return 0;
}


void user_check_response(int sd, int num)
{
    int rep_len;
    int len;
    struct nlattr *na;
    struct msgtemplate msg;

    int data;
    unsigned char *byte_ptr;
    int idx;
    char *string;
    while (num--) {
        rep_len = recv(sd, &msg, sizeof(msg), 0);
        //PRINTF("rep_len=%d\n",rep_len);
        if (rep_len < 0 || user_check_msg(msg, rep_len) < 0) {
            fprintf(stderr, "nonfatal reply error: errno %d\n", errno);
            continue;
        }
        PRINTF("received %d bytes\n", rep_len);
        PRINTF("nlmsghdr size=%zu, nlmsg_len=%d, rep_len=%d\n",
               sizeof(struct nlmsghdr), msg.n.nlmsg_len, rep_len);

        rep_len = GENLMSG_PAYLOAD(&msg.n);
        na = (struct nlattr *) GENLMSG_DATA(&msg);
        len = 0;
        PRINTF("rep_len=%d\n", rep_len);

        while (len < rep_len) {
            len += NLA_ALIGN(na->nla_len);
            PRINTF("nla_len=%d, align_len=%d, pl_len=%d\n", na->nla_len, NLA_ALIGN(na->nla_len), NLA_PAYLOAD(na->nla_len));
            switch (na->nla_type) {
            case NLAIC_ATTR_MESG:
                string = (char *) NLA_DATA(na);
                printf("echo reply:%s\n", string);
                break;
            case NLAIC_ATTR_WORDVAL:
                data = *(int *) NLA_DATA(na);
                printf("echo reply:%u\n", data);
                break;
            case NLAIC_ATTR_RAWDATA:
                byte_ptr = (unsigned char *) NLA_DATA(na);
                printf("rx rawdata:\n");
                for (idx = 0; idx < NLA_PAYLOAD(na->nla_len); idx++) {
                    printf(" %02X", byte_ptr[idx]);
                }
                printf("\n");
                break;
            default:
                fprintf(stderr, "Unknown nla_type %d\n", na->nla_type);
            }
            na = (struct nlattr *) (GENLMSG_DATA(&msg) + len);
        }
    }
}

long long int user_gettime_ms(void)
{
    long long int ret;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    ret = (long long int)ts.tv_sec * 1000 + (long long int)ts.tv_nsec / 1000000;
    return ret;
}

void user_recv_loop(int sd)
{
    int rep_len, last_len = 0;
    int len;
    struct nlattr *na;
    struct msgtemplate msg;

    unsigned char *byte_ptr;
    int idx;
    int rawdata_cnt = 0;
    unsigned char rawdata_seq = 0;
    int trans_end_flag = 0;
    long long int dbg_start_ms = 0;

    while (1) {
        rep_len = recv(sd, &msg, sizeof(msg), 0);
        if (rep_len < 0 || user_check_msg(msg, rep_len) < 0) {
            fprintf(stderr, "errno %d, rep_len=%d\n", errno, rep_len);
            continue;
        }
        if (rep_len != last_len) {
            PRINTF("new recv_len: %d\n", rep_len);
            last_len = rep_len;
        }

        rep_len = GENLMSG_PAYLOAD(&msg.n);
        na = (struct nlattr *) GENLMSG_DATA(&msg);
        len = 0;

        while (len < rep_len) {
            len += NLA_ALIGN(na->nla_len);
            if (na->nla_type == NLAIC_ATTR_RAWDATA) {
                byte_ptr = (unsigned char *) NLA_DATA(na);
                rawdata_cnt++;
                if ((unsigned char)(rawdata_seq + 1) != byte_ptr[0]) {
                    printf("last_seq=%d cur_seq=%d cnt=%d\n", rawdata_seq, byte_ptr[0], rawdata_cnt);
                }
                rawdata_seq = byte_ptr[0];
                if (byte_ptr[1] == (unsigned char)'S') {
                    dbg_start_ms = user_gettime_ms();
                    printf("[%lld] start\n", dbg_start_ms);
                } else if (byte_ptr[1] == (unsigned char)'E') { // trans end flag
                    trans_end_flag = 1;
                }
                #if 0
                for (idx = 0; idx < NLA_PAYLOAD(na->nla_len); idx++) {
                    printf(" %02X", byte_ptr[idx]);
                }
                printf("\n");
                #endif
            } else {
                fprintf(stderr, "Unexpected nla_type %d\n", na->nla_type);
            }
            na = (struct nlattr *) (GENLMSG_DATA(&msg) + len);
        }
        if (trans_end_flag) {
            long long int dbg_end_ms = user_gettime_ms();
            printf("[%lld] trans end, seq=%d, cnt=%d, cost=%lldms\n", dbg_end_ms, rawdata_seq, rawdata_cnt, (dbg_end_ms - dbg_start_ms));
            break;
        }
    }
}

void user_print_usage(char *cmd)
{
    printf("invalid input! usage: %s case <args...>\n", cmd);
    printf("  req-resp case : %s 0 <char msg> <uint data> <bytes byte_ptr>\n", cmd);
    printf("  perf recv case: %s 1\n", cmd);
    printf("  perf send case: %s 2 <uint block_size> <uint block_count>\n", cmd);
}

void a2b_hex(unsigned char *out, char *in, int len)
{
    unsigned int  i = 0;
    unsigned char hi = 0;
    unsigned char lo = 0;
    while (i < len) {
        if (in[i] <= '9') {
            hi = in[i] - '0';
        } else if (in[i] <= 'F') {
            hi = in[i] - 'A' + 0x0A;
        } else if (in[i] <= 'f') {
            hi = in[i] - 'a' + 0x0A;
        }
        i++;
        if (in[i] <= '9') {
            lo = in[i] - '0';
        } else if (in[i] <= 'F') {
            lo = in[i] - 'A' + 0x0A;
        } else if (in[i] <= 'f') {
            lo = in[i] - 'a' + 0x0A;
        }
        i++;
        out[i / 2 - 1] = ((hi & 0x0F) << 4) | (lo & 0x0F);
    }
}

int main(int argc, char* argv[])
{
    int nl_fd;
    int nl_family_id;
    int my_pid;
    int ret;
    int test_case;

    unsigned char *byte_ptr;
    int data, size;
    char *string;

    if (argc < 2) {
        user_print_usage(argv[0]);
        return 0;
    }
    test_case = atoi(argv[1]);
    if (test_case == 0) {
        printf("request-response test\n");
        if (argc < 5) {
            user_print_usage(argv[0]);
            return 0;
        }
    } else if (test_case == 1) {
        printf("perf recv test\n");
    } else if (test_case == 2) {
        printf("perf send test\n");
        if (argc < 4) {
            user_print_usage(argv[0]);
            return 0;
        }
    } else {
        printf("unsupported test case: %d\n", test_case);
        return 0;
    }

    nl_fd = user_create_nl_socket(NETLINK_GENERIC);
    if (nl_fd < 0) {
        fprintf(stderr, "failed to create netlink socket\n");
        return 0;
    }

    nl_family_id = user_get_family_id(nl_fd);
    if (!nl_family_id) {
        fprintf(stderr, "Error getting family id, errno %d\n", errno);
        goto out;
    }
    PRINTF("family id %d\n", nl_family_id);

    my_pid = getpid();

    if (test_case == 0) {
        string = argv[2];
        data = atoi(argv[3]);
        size = (strlen(argv[4]) + 1) / 2;
        byte_ptr = malloc(size);
        if (!byte_ptr) {
            PRINTF("malloc fail\n");
            goto out;
        }
        a2b_hex(byte_ptr, argv[4], size * 2);
        /*PRINTF("size=%d, bytes:\n", size);
        int idx;
        for (idx=0;idx<size;idx++) {
            PRINTF(" %02X", byte_ptr[idx]);
        }
        PRINTF("\n");*/

        ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_ECHO,
                NLAIC_ATTR_MESG, string, strlen(string) + 1);
        if (ret < 0) {
            fprintf(stderr, "failed to send echo cmd\n");
            goto out;
        }

        ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_ECHO,
                NLAIC_ATTR_WORDVAL, &data, sizeof(data));
        if (ret < 0) {
            fprintf(stderr, "failed to send echo cmd\n");
            goto out;
        }

        ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_REGISTER_USERID,
                NLAIC_ATTR_USERID, &my_pid, sizeof(my_pid));
        if (ret < 0) {
            fprintf(stderr, "failed to reg userid\n");
            goto out;
        }

        ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_RAWDATA,
                NLAIC_ATTR_RAWDATA, byte_ptr, size);
        if (ret < 0) {
            fprintf(stderr, "failed to send rawdata\n");
            goto out;
        }

        user_check_response(nl_fd, argc-2);
    } else if ((test_case == 1) || (test_case == 2)) {
        ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_REGISTER_USERID,
                NLAIC_ATTR_USERID, &my_pid, sizeof(my_pid));
        if (ret < 0) {
            fprintf(stderr, "failed to reg userid\n");
            goto out;
        }

        if (test_case == 1) {
            user_recv_loop(nl_fd);
        } else if (test_case == 2) {
            unsigned int block_size = atoi(argv[2]);
            unsigned int block_count = atoi(argv[3]);
            unsigned char *txbuff = NULL;
            long long int dbg_start_ms = 0, dbg_end_ms = 0, dbg_cost_ms = 1, total_size, speed;
            int idx;
            txbuff = malloc(block_size);
            if (txbuff == NULL) {
                printf("buf alloc failed\n");
                goto out;
            }
            for (idx = 2; idx < block_size; idx++) {
                txbuff[idx] = idx & 0xFF;
            }
            txbuff[0] = 0x80; // 1st byte as seq_no
            txbuff[1] = 'S';  // 2nd byte as trans flag (start flag)
            dbg_start_ms = user_gettime_ms();
            printf("[%lld] start, block_size=%d, block_count=%d\n", dbg_start_ms, block_size, block_count);
            total_size = block_size * block_count;
            for (idx = 0; idx < block_count; idx++) {
                if (idx == 1) {
                    txbuff[1] = 'I'; // in progress flag
                }
                if (idx == (block_count - 1)) {
                    txbuff[1] = 'E'; // end flag
                }
                ret = user_send_cmd(nl_fd, nl_family_id, my_pid, NLAIC_CMD_RAWDATA,
                        NLAIC_ATTR_RAWDATA, txbuff, block_size);
                if (ret < 0) {
                    fprintf(stderr, "failed to send rawdata, ret=%d\n", ret);
                    goto send_end;
                }
                txbuff[0]++;
            }
send_end:
            dbg_end_ms = user_gettime_ms();
            if (dbg_end_ms - dbg_start_ms) {
                dbg_cost_ms = dbg_end_ms - dbg_start_ms;
            }
            speed = total_size * 1000 / 1024 / dbg_cost_ms;
            printf("[%lld] end, sent %d blocks, cost=%lldms\n", dbg_end_ms, idx, dbg_cost_ms);
            printf("totalsize=%lldBytes, speed=%lldKB/s\n", total_size, speed);
        }
    }

out:
    close(nl_fd);
    return 0;
}

