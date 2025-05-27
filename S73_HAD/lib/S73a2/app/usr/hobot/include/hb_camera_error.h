/***************************************************************************
 *                      COPYRIGHT NOTICE
 *             Copyright 2020 Horizon Robotics, Inc.
 *                     All rights reserved.
 ***************************************************************************/

/**
 * @file hb_camera_error.h
 *
 * @NO{S10E02C01}
 * @ASIL{B}
 */

#ifndef __HB_CAMERA_ERROR_H__
#define __HB_CAMERA_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAMERA_NOVPF
#include "hbn_error.h"

/* camera private error */
#define HBN_STATUS_CAM_PRIV_ERROR(num)		(HBN_STATUS_CAM_EXT_ERROR(128 + (num)))

#ifndef RET_OK
#define RET_OK		HBN_STATUS_SUCESS
#endif
#ifndef RET_ERROR
#define RET_ERROR	HBN_STATUS_CAM_ERR_UNKNOW
#endif

#else /* CAMERA_NOVPF */
/* camera common error */
#define HBN_STATUS_CAM_INVALID_NODE 		(0x10001) // 1
#define HBN_STATUS_CAM_INVALID_NODETYPE 	(0x10002) // 2
#define HBN_STATUS_CAM_INVALID_HWID 		(0x10003) // 3
#define HBN_STATUS_CAM_INVALID_CTXID 		(0x10004) // 4
/* #define HBN_STATUS_CAM_INVALID_OCHNID 	(0x10005) // 5 */
/* #define HBN_STATUS_CAM_INVALID_ICHNID 	(0x10006) // 6 */
/* #define HBN_STATUS_CAM_INVALID_FORMAT 	(0x10007) // 7 */
#define HBN_STATUS_CAM_INVALID_NULL_PTR 	(0x10008) // 8
#define HBN_STATUS_CAM_INVALID_PARAMETER 	(0x10009) // 9
#define HBN_STATUS_CAM_ILLEGAL_ATTR 		(0x1000A) // 10
#define HBN_STATUS_CAM_INVALID_FLOW 		(0x1000B) // 11
#define HBN_STATUS_CAM_FLOW_EXIST 		(0x1000C) // 12
#define HBN_STATUS_CAM_FLOW_UNEXIST 		(0x1000D) // 13
#define HBN_STATUS_CAM_NODE_EXIST 		(0x1000E) // 14
#define HBN_STATUS_CAM_NODE_UNEXIST 		(0x1000F) // 15
#define HBN_STATUS_CAM_NOT_CONFIG 		(0x10010) // 16
/* #define HBN_STATUS_CAM_CHN_NOT_ENABLED 	(0x10011) // 17 */
/* #define HBN_STATUS_CAM_CHN_ALREADY_ENABLED 	(0x10012) // 18 */
#define HBN_STATUS_CAM_ALREADY_BINDED 		(0x10013) // 19
#define HBN_STATUS_CAM_NOT_BINDED 		(0x10014) // 20
#define HBN_STATUS_CAM_TIMEOUT			(0x10015) // 21
#define HBN_STATUS_CAM_NOT_INITIALIZED 		(0x10016) // 22
#define HBN_STATUS_CAM_NOT_SUPPORT 		(0x10017) // 23
#define HBN_STATUS_CAM_NOT_PERM 		(0x10018) // 24
#define HBN_STATUS_CAM_NOMEM			(0x10019) // 25
/* #define HBN_STATUS_CAM_INVALID_VNODE_FD 	(0x1001A) // 26 */
/* #define HBN_STATUS_CAM_INVALID_ICHNID_FD 	(0x1001B) // 27 */
/* #define HBN_STATUS_CAM_INVALID_OCHNID_FD 	(0x1001C) // 28 */
/* #define HBN_STATUS_CAM_OPEN_OCHN_FAIL 	(0x1001D) // 29 */
/* #define HBN_STATUS_CAM_OPEN_ICHN_FAIL 	(0x1001E) // 30 */
#define HBN_STATUS_CAM_JSON_PARSE_FAIL 		(0x1001F) // 31
/* #define HBN_STATUS_CAM_REQ_BUF_FAIL 		(0x10020) // 32 */
/* #define HBN_STATUS_CAM_QUERY_BUF_FAIL 	(0x10021) // 33 */
#define HBN_STATUS_CAM_SET_CONTROL_FAIL 	(0x10022) // 34
#define HBN_STATUS_CAM_GET_CONTROL_FAIL 	(0x10023) // 35
#define HBN_STATUS_CAM_NODE_START_FAIL 		(0x10024) // 36
#define HBN_STATUS_CAM_NODE_STOP_FAIL 		(0x10025) // 37
/* #define HBN_STATUS_CAM_NODE_POLL_ERROR 	(0x10026) // 38 */
/* #define HBN_STATUS_CAM_NODE_POLL_TIMEOUT 	(0x10027) // 39 */
/* #define HBN_STATUS_CAM_NODE_POLL_FRAME_DROP 	(0x10028) // 40 */
/* #define HBN_STATUS_CAM_NODE_POLL_HUP 	(0x10029) // 41 */
#define HBN_STATUS_CAM_NODE_ILLEGAL_EVENT 	(0x1002A) // 42
/* #define HBN_STATUS_CAM_NODE_DEQUE_ERROR 	(0x1002B) // 43 */
/* #define HBN_STATUS_CAM_ILLEGAL_BUF_INDEX 	(0x1002C) // 44 */
/* #define HBN_STATUS_CAM_NODE_QUE_ERROR 	(0x1002D) // 45 */
/* #define HBN_STATUS_CAM_FLUSH_FRAME_ERROR 	(0x1002E) // 46 */
/* #define HBN_STATUS_CAM_INIT_BIND_ERROR 	(0x1002F) // 47 */
/* #define HBN_STATUS_CAM_ADD_NODE_FAIL 	(0x10030) // 48 */
/* #define HBN_STATUS_CAM_WRONG_CONFIG_ID 	(0x10031) // 49 */
/* #define HBN_STATUS_CAM_BIND_NODE_FAIL 	(0x10032) // 50 */
#define HBN_STATUS_CAM_INVALID_VERSION 		(0x10033) // 51
#define HBN_STATUS_CAM_GET_VERSION_ERROR 	(0x10034) // 52
/* #define HBN_STATUS_CAM_MEM_INIT_FAIL 	(0x10035) // 53 */
/* #define HBN_STATUS_CAM_MEM_IMPORT_FAIL 	(0x10036) // 54 */
/* #define HBN_STATUS_CAM_MEM_FREE_FAIL 	(0x10037) // 55 */
/* #define HBN_STATUS_CAM_SYSFS_OPEN_FAIL 	(0x10038) // 56 */
#define HBN_STATUS_CAM_ERR_UNKNOW		(0x10080) // 128

/* camera extern error */
#define HBN_STATUS_CAM_MOD_DLOPEN_ERROR		(0x10081) // 129
#define HBN_STATUS_CAM_MOD_CHECK_ERROR		(0x10082) // 130
#define HBN_STATUS_CAM_MOD_VERSION_ERROR	(0x10083) // 131
#define HBN_STATUS_CAM_VCON_ATTR_ERROR		(0x10084) // 132
#define HBN_STATUS_CAM_CSI_ATTR_ERROR		(0x10085) // 133
#define HBN_STATUS_CAM_SENSOR_DEV_ERROR		(0x10086) // 134
#define HBN_STATUS_CAM_DESERIAL_DEV_ERROR	(0x10087) // 135
#define HBN_STATUS_CAM_SENSOR_OP_ERROR		(0x10088) // 136
#define HBN_STATUS_CAM_CALIB_OP_ERROR		(0x10089) // 137
#define HBN_STATUS_CAM_DESERIAL_OP_ERROR	(0x1008A) // 138
#define HBN_STATUS_CAM_POC_OP_ERROR		(0x1008B) // 139
#define HBN_STATUS_CAM_TXSER_OP_ERROR		(0x1008C) // 140
#define HBN_STATUS_CAM_VIN_ATTACH_ERROR		(0x1008D) // 141
#define HBN_STATUS_CAM_I2C_OP_ERROR		(0x1008E) // 142
#define HBN_STATUS_CAM_GPIO_OP_ERROR		(0x1008F) // 143

/* camera private error */
#define HBN_STATUS_CAM_PRIV_ERROR(num)		(0x10100 + (num)) // 256+num

#ifndef RET_OK
#define RET_OK		0
#endif
#ifndef RET_ERROR
#define RET_ERROR	HBN_STATUS_CAM_ERR_UNKNOW
#endif

#endif /* CAMERA_NOVPF */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HB_CAMERA_ERROR_H__ */
