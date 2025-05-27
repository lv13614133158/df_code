/*
 * Horizon Robotics
 *
 *  Copyright (C) 2024 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: zhe01.zhang<zhe01.zhang@horizon.cc>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DIAG_LIB_H_
#define __DIAG_LIB_H_
#include <stdint.h>
#include "diag_lib_id.h"

#define MAX_PAYLOAD_SIZE 16
#define MAX_L2_FCHM_ID  23
#define STL_IDTOKEN_SIZE 64

#define DIAGLIB_SUCC                 0 /* no error */
#define DIAGLIB_EINVAL              -1 /* invalid parameter */
#define DIAGLIB_FCHM_ERR            -2 /* invalid fchm code */
#define DIAGLIB_OPENFD_FAIL         -3 /* open fd failed */
#define DIAGLIB_IOCTL_FAIL          -4 /* ioctl failed */
#define DIAGLIB_PAYLOAD_NULL        -9 /* payload is null */

/*
 * stl run permit.
 */
enum stl_run_permit_u {
    STL_RUN_OK = 1,
    STL_RUN_NOT_OK,
};

/*
 * stl location.
 */
enum stl_location_u {
    USER_SPACE_LOC = 1,
    KERNEL_SPACE_LOC,
};

/*
 * error type.
 */
enum error_type_t {
    HW_ERROR = 1,
    SW_ERROR,
};

/*
 * event level.
 */
enum diag_event_level {
    NCF_LEVEL = 1,
    CF_LEVEL,
};

/*
 * event status.
 */
enum diag_event_status {
    EventStaSuccess = 1,        // error fixed
    EventStaFail,               // error happened
};

struct fchm_err {
    uint16_t fchm_id;            /**< fchm_id: l1_fchm errcode */
    uint16_t fchm_err_code;      /**< fchm_err_code: l2_fchm errcode */
    uint32_t fchm_fault_sequence;/**< fchm_fault_sequence: fchm error sequence */
};

#define DIAGLIB_EVENT_PAYLOAD_MAXSIZE 16

typedef int32_t m_fd;

/*
 * @Description: user_stl_func struct
 * @module_id: module id
 * @fchm_info: fchm error code and fchm_id (诊断会将fchm_err_code and fchm_id传入给用户态stl)
 * @stl_init_u: init function pointer
 * @stl_check_u: check function pointer
 * @stl_deinit_u: deinit function pointer
 * @stl_inject_u: inject error function pointer
 * @stl_selfcheck_u: selfcheck function pointer
 * @stl_clear_fusa_sta_u: clear corresponding fusa status
 * @stl_periodic_check_sta_u: periodic_check status
 * @source_id: error source id
 * @err_bit: error bit
 * @private_data: private data
 */
struct user_stl_func {
        uint16_t module_id;
        struct fchm_err fchm_info;
        int32_t (*stl_init_u)(struct user_stl_func*);
        int32_t (*stl_handler_u)(struct user_stl_func*);
        int32_t (*stl_deinit_u)(struct user_stl_func*);
        int32_t (*stl_inject_u)(struct user_stl_func*);
        int32_t (*stl_selfcheck_u)(struct user_stl_func*);
        int32_t (*stl_clear_fusa_sta_u)(struct user_stl_func*);
        int32_t (*stl_periodic_check_sta_u)(struct user_stl_func*);
        uint16_t source_id;
        uint16_t err_bit;
        void *private_data;
};

/*
 * @Description: stllib error definition
 * @module_id: module ID, each module may have several error IDs.
 * @event_id: event ID, each module may have several error IDs.
 * @event_level: error level, three levels.
 * @event_state: event_state, three levels.
 * @fchm_info: fchm error code info.
 * @payload: maybe unused..
 */
typedef struct stllib_err {
    uint16_t module_id;
    uint16_t event_id;
    uint8_t event_level;
    uint8_t event_status;
    struct fchm_err fchm_info;
    uint8_t payload[MAX_PAYLOAD_SIZE];
} stllib_err_t;

/*
 * @Description: stllib error message definition
 * @err: stllib error information
 * @checksum: checksum of error data
 * @dummy: placeholder for future use.
 */
typedef struct stllib_err_msg {
    stllib_err_t err;
    uint64_t checksum;
    uint32_t dummy;
} stllib_err_msg_t;

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief report hardware(with FCHM error) event 
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event id
 * @param[in] event_level: NCF_LEVEL=1, CF_LEVEL=2
 * @param[in] event_status: EventStaSuccess=1, EventStaFail=2
 * @param[in] fchm_info: struct fchm_info
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_send_hardware_event(uint16_t module_id, uint16_t event_id, uint8_t event_level, uint8_t event_status, struct fchm_err *err);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief report hardware(with FCHM error) event with payload 
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event id
 * @param[in] event_level: NCF_LEVEL=1, CF_LEVEL=2
 * @param[in] event_status: EventStaSuccess=1, EventStaFail=2
 * @param[in] fchm_info: struct fchm_info
 * @param[in] payload: Users can carry information with payload[16]
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_send_hardware_event_payload(uint16_t module_id, uint16_t event_id, uint8_t event_level, uint8_t event_status, struct fchm_err *err, uint8_t payload[MAX_PAYLOAD_SIZE]);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief report software(without FCHM Error) event
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event id
 * @param[in] event_level: NCF_LEVEL=1, CF_LEVEL=2
 * @param[in] event_status: EventStaSuccess=1, EventStaFail=2
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_send_software_event(uint16_t module_id, uint16_t event_id, uint8_t event_level, uint8_t event_status);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief report software(without FCHM error) event with payload
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event id
 * @param[in] event_level: NCF_LEVEL=1, CF_LEVEL=2
 * @param[in] event_status: EventStaSuccess=1, EventStaFail=2
 * @param[in] payload: Users can carry information with payload[16]
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_send_software_event_payload(uint16_t module_id, uint16_t event_id, uint8_t event_level, uint8_t event_status, uint8_t payload[MAX_PAYLOAD_SIZE]);

enum fchm_turn_sta {
    TURN_ON_DETECTION = 1,
    TURN_OFF_DETECTION,
};

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Switch fchm_err_code detection
 *
 * @param[in] fchm_id: fchm id with l1_fchm
 * @param[in] fchm_err_code: fchm error code with l2_fchm
 * @param[in] on_off_flag: FCHM_INT_ON = 1, FCHM_INT_OFF = 2
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_set_fchm_error_switch(uint16_t fchm_id, uint16_t fchm_err_code, enum fchm_turn_sta on_off_flag);

enum fchm_answer_core {
    ACORE_ANS = 0,
    RCORE_ANS,
};
/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Switch fchm_err_code detection
 *
 * @param[in] fchm_id: fchm id with l1_fchm
 * @param[in] fchm_err_code: fchm error code with l2_fchm
 * @param[in] core: enum fchm_ans_core
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_set_fchm_answer_core(uint16_t fchm_id, uint16_t fchm_err_code, uint8_t ans_core);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Lock stl_uio
 *
 * @param[in] module_id: module id
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_stl_uio_lock(uint16_t module_id);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Unlock stl_uio
 *
 * @param[in] module_id: module id
 * @param[out] None
 *
 * @retval 0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_stl_uio_unlock(uint16_t module_id);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Regmap read
 *
 * @param[in] module_id: module id
 * @param[in] offset: offset addr
 * @param[out] None
 *
 * @retval >= 0: mean the value of sysreg!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_regmap_read(uint16_t module_id, uint32_t offset);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Regmap write
 *
 * @param[in] module_id: module id
 * @param[in] offset: offset addr
 * @param[in] val: the value of write
 * @param[out] None
 *
 * @retval =0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_regmap_write(uint16_t module_id, uint32_t offset, uint32_t val);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Regmap write
 *
 * @param[in] module_id: module id
 * @param[in] offset: offset addr
 * @param[in] mask: mask bit
 * @param[in] val: the value of write
 * @param[out] None
 *
 * @retval =0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_regmap_write_bits(uint16_t module_id, uint32_t offset, uint32_t mask, uint32_t val);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Report event for J5
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event_id
 * @param[in] event_level: enum diag_event_level
 * @param[in] event_status: enum diag_event_status
 * @param[in] fchm_id: l2_fchm num
 * @param[in] fchm_err_code: error code
 * @param[in] fchm_fault_sequence: errcode sequence
 * @param[in] flags: None
 * @param[out] None
 *
 * @retval =0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_diaglib_report_event(uint16_t module_id, uint16_t event_id, enum diag_event_level event_level, enum diag_event_status event_status,
    uint16_t fchm_id, uint16_t fchm_err_code, uint16_t fchm_fault_sequence, uint8_t flags);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Report event with payload for J5
 *
 * @param[in] module_id: module id
 * @param[in] event_id: event_id
 * @param[in] event_level: enum diag_event_level
 * @param[in] event_status: enum diag_event_status
 * @param[in] fchm_id: l2_fchm num
 * @param[in] fchm_err_code: error code
 * @param[in] fchm_fault_sequence: errcode sequence
 * @param[in] flags: None
 * @param[in] payload: payload info
 * @param[out] None
 *
 * @retval =0: mean succ!
 * @retval <0: mean fail!
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t hb_diaglib_report_event_with_payload(uint16_t module_id, uint16_t event_id, enum diag_event_level event_level, enum diag_event_status event_status,
    uint16_t fchm_id, uint16_t fchm_err_code, uint16_t fchm_fault_sequence, uint8_t flags, uint8_t payload[DIAGLIB_EVENT_PAYLOAD_MAXSIZE]);
#endif
