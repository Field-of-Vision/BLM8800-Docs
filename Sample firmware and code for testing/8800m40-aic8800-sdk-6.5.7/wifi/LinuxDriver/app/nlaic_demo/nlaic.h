#ifndef _NLAIC_H_
#define _NLAIC_H_


#define NLAIC_GENL_NAME     "nlaic"
#define NLAIC_GENL_VERSION  0x1


/*
 * Commands sent from userspace
 */

enum {
    NLAIC_CMD_UNSPEC = 0,   /* Reserved */
    NLAIC_CMD_ECHO,         /* user->kernel request/get-response */
    NLAIC_CMD_REPLY,        /* kernel->user event */
    NLAIC_CMD_REGISTER_USERID,  /* user register portid */
    NLAIC_CMD_RAWDATA,          /* tx/rx raw binary data */

    /* add new commands above here */

    /* used to define NUM_NLAIC_CMD & NLAIC_CMD_MAX below */
    __NLAIC_CMD_AFTER_LAST,
    NUM_NLAIC_CMD = __NLAIC_CMD_AFTER_LAST,
    NLAIC_CMD_MAX = __NLAIC_CMD_AFTER_LAST - 1
};


enum {
    NLAIC_ATTR_UNSPEC = 0,
    NLAIC_ATTR_MESG,        /* message string */
    NLAIC_ATTR_WORDVAL,     /* word value */
    NLAIC_ATTR_USERID,      /* userid */
    NLAIC_ATTR_RAWDATA,     /* raw binary data */

    /* add new attributes above here */

    /* used to define NUM_NLAIC_ATTR & NLAIC_ATTR_MAX below */
    __NLAIC_ATTR_AFTER_LAST,
    NUM_NLAIC_ATTR = __NLAIC_ATTR_AFTER_LAST,
    NLAIC_ATTR_MAX = __NLAIC_ATTR_AFTER_LAST - 1
};


#endif /* _NLAIC_H_ */
