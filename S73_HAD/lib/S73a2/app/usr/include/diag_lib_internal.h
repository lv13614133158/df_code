/*
 * Horizon Robotics
 *
 *  Copyright (C) 2020 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: zhe01.zhang<zhe01.zhang@horizon.cc>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DIAG_LIB_INTERNAL_H
#define __DIAG_LIB_INTERNAL_H

#include <linux/netlink.h>
#include <sys/socket.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include "diag_lib.h"
/* ============== Error code definition ============= */

/* ============== structure definition ============= */

#define IOCS_GET_MODULE_ERR_INFO 0x60
#define IOCS_STL_MODULEID_FUNC 0x57
#define IOCS_DYNAMIC_FCHM_FUNC 0x53
#define IOCS_UIO_LOCK 0x52
#define IOCS_ERRCODE_SWITCH 0x51
#define IOCS_ERRCODE_ANS_CORE 0x54
#define IOCS_USER_EVENT_INFO 0x35
#define IOCS_INJECT_ERR_INFO 0x39
#define IOCS_SEND_SWITCH 0x44
#define IOCS_PRINT_SWITCH 0x43
#define IOCS_NCF_COUNT_INFO  0x41
#define IOCS_GET_INJECT_RESULT  0x71
#define IOCS_GET_REGISTER_RESULT  0x42
#define IOCS_GET_SELFCHECK_RESULT  0x61
#define IOCS_SET_ACORE_PWM 0x13
#define IOCS_INFORM_CHECK_STL_RESULT 0x49
#define IOCS_GET_STL_RUN 0x58

#define DIAG_DEFAULT_PERIOD_CHECK_TIME 100 //ms
#define DIAG_DEFAULT_TIME 2000000 //ms
#define TURN_ON_STL_PERIOD_CHECK 1
#define TURN_OFF_STL_PERIOD_CHECK 2

struct diaglib_period_permit {
    uint32_t all_period_permit;
    uint32_t period_time;
    uint16_t module_id;
    uint16_t module_permit;
};
#if 0
/* ============== interfaces definition ============= */
/*
 * @Description: create netlink socket
 * @return: 0 on success, negative value on failure
 */
int32_t diaglib_netlink_init(void);

/*
 * @Description: destroy netlink socket
 * @sockfd: socket file descriptor
 * @return: 0 on success, negative value on failure
 */
int32_t diaglib_netlink_deinit(int32_t sockfd);

/*
 * @Description: recv netlink msg
 * @sockfd: socket file descriptor
 * @return: 0 on success, negative value on failure
 */
int32_t diaglib_netlink_recv_msg(int32_t sockfd);
#endif
/*
 * @Description: create posix message queue
 * @return: mq descriptor on success, system defined error on failure
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t diaglib_mq_create(void);

/*
 * @Description: destroy posix message queue
 * @return: 0 on success, negative value on failure
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t diaglib_mq_destroy(void);

/*
 * @Description: receive message from inject app
 * @stl_info: message buffer pointer to store message to
 * @return: 0 on success, others value on failure
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_receive_inject_err(struct user_stl_func *stl_info);

/*
 * @Description: send message to stl_service
 * @stl_info: message to be send
 * @return: 0 on success, others value on failure
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_send_inject_err(struct user_stl_func *stl_info);

/*
 * @Description: send switch
 * @sendswitch: the switch
 * @return: 0 on success, others value on failure
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t diag_send_switch(int32_t sendswitch);

#define NETLINK_DIAG    23
#define NETLINK_PORT    100
#define NETLINK_GROUP    1
#define MAX_DATA_SIZE    150
#define NET_PAYLOAD_SIZE 128
#define ENV_NETLINK_SIZE 168
#define MAX_PAYLOAD_SIZE 16
#define ENV_PAYLOAD_SIZE 16

/*
 * The structures below shoule be same as corresponding structures in kernel
 * to parse received data from kernel.
 */

/*
 * event status.
 */

/* header part in struct diag_msg */
struct diag_msg_header {
    uint8_t msg_type;
    uint16_t msg_len;
    uint32_t checksum;
};

struct diag_user_msg {
    uint16_t module_id;
    uint16_t event_id;
    uint8_t event_status;
    uint8_t event_level;
    uint16_t fchm_id;
    uint16_t fchm_err_code;
    uint32_t fchm_fault_sequence;
    uint8_t payload[MAX_PAYLOAD_SIZE];
};

/* data part in struct diag_msg */
struct diag_msg_data {
    uint16_t module_id;
    uint16_t event_id;
    uint8_t event_sta;
    uint8_t event_level;
    uint32_t sec;
    uint16_t msec;
    uint8_t payload[ENV_NETLINK_SIZE];
};

/*
 * message received from kernel space
 */
struct diag_msg {
    struct diag_msg_header header;
    struct diag_msg_data data;
};

/*
 * message from netlink: nlmsghdr + data
 */
struct netlink_msg {
    struct nlmsghdr hdr;
    uint8_t data[MAX_DATA_SIZE];
};

struct switch_fchm_info {
    uint16_t fchm_id;
    uint16_t fchm_err_code;
    uint8_t switch_flag;
};

struct core_fchm_info {
    uint16_t fchm_id;
    uint16_t fchm_err_code;
    uint8_t core;
};

#define UIO_LOCK 1
#define UIO_UNLOCK 2

struct uio_lock {
    uint16_t module_id;
    uint16_t lock_flag;
};

struct hb_regmap_info {
    uint16_t module_id;
    uint32_t reg_base;
    uint32_t offset;
    uint32_t mask;
    uint32_t val;
    int16_t ret_status;
};

#define DIAG_LIB_IOC_MAGIC  'd'
#define IOCS_REGMAP_READ       _IOW(DIAG_LIB_IOC_MAGIC, 21, int)
#define IOCS_REGMAP_WRITE      _IOW(DIAG_LIB_IOC_MAGIC, 22, int)
#define IOCS_REGMAP_BIT_WRITE  _IOW(DIAG_LIB_IOC_MAGIC, 23, int)

#define DIAG_TEST_IOC_MAGIC  'd'
#define IOCS_TRANSFER_TEST  _IOW(DIAG_TEST_IOC_MAGIC, 24, int)

#define REGMAP_SUCC 1
#define REGMAP_MODULEID_ERR (-1)
#define REGMAP_ADDR_ERR     (-2)
#define REGMAP_MAP_ERR         (-3)
#define REGMAP_ERR             (-4)

struct diag_test_arg{
    uint8_t send_type;
    uint16_t module_id;
    uint16_t event_id;
    uint32_t event_level;
    uint8_t event_status;
    uint16_t fchm_id;
    uint16_t fchm_err_code;
    uint32_t fchm_fault_sequence;
    uint32_t send_num;
    uint32_t time_interval;
    uint16_t thread_num;
    uint16_t process_num;
};

#endif //__DIAG_LIB_INTERNAL_H
