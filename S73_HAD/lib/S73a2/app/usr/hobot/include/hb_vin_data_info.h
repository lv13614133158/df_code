/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/

#ifndef HB_VIN_DATA_INFO_H_
#define HB_VIN_DATA_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>

typedef struct img_addr_info_s {
	uint16_t width;
	uint16_t height;
	uint16_t stride;
	uint64_t y_paddr;
	uint64_t c_paddr;
	uint64_t y_vaddr;
	uint64_t c_vaddr;
} img_addr_info_t;

typedef struct cam_img_info_s {
	int32_t g_id;
	int32_t slot_id;
	int32_t cam_id;
	int32_t frame_id;
	int64_t timestamp;
	img_addr_info_t img_addr;
} cam_img_info_t;

typedef enum CAM_DATA_TYPE_S {
	HB_CAM_RAW_DATA = 0,
	HB_CAM_YUV_DATA = 1,
	HB_CAM_EMB_DATA = 2,
	HB_CAM_EMB_INFO = 3,
	HB_CAM_ROI_DATA = 4,
	HB_CAM_MAX = 5,
} CAM_DATA_TYPE_E;

#define STAT_NUM 16u
#define VIN_MAX_CONFIG_INDEX 0u
#define MAX_DELAY_FRAMES 100u

struct statinfo {
	uint32_t framid;
	uint64_t g_tv_sec;
	uint64_t g_tv_usec;
};

typedef struct lpwm_dynamic_s {
	uint32_t period;
	uint32_t offset;
	uint32_t duty_time;
	uint32_t trigger_source;
	uint32_t trigger_mode;
} lpwm_dynamic_t;


struct vio_statinfo {
	struct statinfo stat[MAX_DELAY_FRAMES][STAT_NUM];
};

#ifdef __cplusplus
}
#endif

#endif // HB_VIN_DATA_INFO_H_
