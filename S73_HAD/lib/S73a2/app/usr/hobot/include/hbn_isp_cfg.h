/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2019 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef __HBN_ISP_CFG_H__
#define __HBN_ISP_CFG_H__
#include "cJSON.h"
#include "hb_comm_isp.h"
#include <stdint.h>
#ifndef AUTO_ALLOC_ID
#define AUTO_ALLOC_ID -1
#endif

#define MAX_FILE_NAME 100u
#define CALIB_MODE_FROM_LIB 1u
#define CONVERT_ISP_SCHED_MODE_TDMF 0
#define CONVERT_ISP_SCHED_MODE_MANUAL 1
#define CONVERT_ISP_SCHED_MODE_PASS_THRU 2
#define CONVERT_HDR_MODE_LINEAR 0
#define CONVERT_HDR_MODE_NATIVE 1
#define CONVERT_HDR_MODE_2To1_LINE 2
#define CONVERT_HDR_MODE_2To1_FRAME 3
#define CONVERT_HDR_MODE_3To1_LINE 4
#define CONVERT_HDR_MODE_3To1_FRAME 5
#define CONVERT_HDR_MODE_4To1_LINE 6
#define CONVERT_HDR_MODE_4To1_FRAME 7
#define COVERT_AXI_OUTPUT_MODE_DISABLE 0
#define COVERT_AXI_OUTPUT_MODE_RGB888 1
#define COVERT_AXI_OUTPUT_MODE_RAW8 2
#define COVERT_AXI_OUTPUT_MODE_RAW10 3
#define COVERT_AXI_OUTPUT_MODE_RAW12 4
#define COVERT_AXI_OUTPUT_MODE_RAW16 5
#define COVERT_AXI_OUTPUT_MODE_RAW24 6
#define COVERT_AXI_OUTPUT_MODE_YUV444 7
#define COVERT_AXI_OUTPUT_MODE_YUV422 8
#define COVERT_AXI_OUTPUT_MODE_YUV420 9
#define COVERT_AXI_OUTPUT_MODE_IR8 10
#define COVERT_AXI_OUTPUT_MODE_YUV420_RAW12 11
#define COVERT_AXI_OUTPUT_MODE_YUV422_RAW12 12
#define COVERT_AXI_OUTPUT_MODE_YUV420_RAW16 13
#define COVERT_AXI_OUTPUT_MODE_YUV422_RAW16 14

#define ISP_GET_FRAME_TIME_OUT 3000
#define ISP_IMAGE_BUF_COUNT 6

typedef struct isp_cfg_s {
	isp_attr_t isp_attr;
	isp_module_ctrl_u module_ctrl;
	isp_ochn_attr_t ochn_attr;
	isp_ichn_attr_t ichn_attr;
} isp_cfg_t;

#endif
