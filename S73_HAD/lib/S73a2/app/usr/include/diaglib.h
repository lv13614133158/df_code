/*
 * Horizon Robotics
 *
 *  Copyright (C) 2024 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: zhe01.zhang<zhe01.zhang@horizon.cc>
 *
 *  The diag header file is for external users to use
 */

#ifndef __DIAGLIB_H_
#define __DIAGLIB_H_

#include <stdint.h>
#include "diag_lib.h"

#define EventStaFixed   1               // error recovery
#define EventStaFail    2               // error happened

#define DIAGLIB_SUCC                 0 /* no error */
#define DIAGLIB_EINVAL              -1 /* invalid parameter */
#define DIAGLIB_FCHM_ERR            -2 /* invalid fchm code */
#define DIAGLIB_OPENFD_FAIL         -3 /* open fd failed */
#define DIAGLIB_IOCTL_FAIL          -4 /* ioctl failed */
#define DIAGLIB_PAYLOAD_NULL        -9 /* payload is null */

#define MAX_PAYLOAD_SIZE 16

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Report event
 *
 * @param[in] module_id:(range: 0x0FFF - 0xFFFF)
 * @param[in] event_id: (range: 1 - 0xFFFF)
 * @param[in] event_status; EventStaFixed : error recovery, EventStaFail : error happened
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
int32_t hb_diag_send_event(uint16_t module_id, uint16_t event_id, uint8_t event_status);

/**
 * @NO{S20E02C02}
 * @ASIL{B}
 * @brief Report event with payload
 *
 * @param[in] module_id:(range: 0x0FFF - 0xFFFF)
 * @param[in] event_id: (range: 1 - 0xFFFF)
 * @param[in] event_status; EventStaFixed : error recovery, EventStaFail : error happened
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
int32_t hb_diag_send_event_payload(uint16_t module_id, uint16_t event_id, uint8_t event_status, uint8_t payload[MAX_PAYLOAD_SIZE]);
#endif
