/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2020 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef __HBN_VPF_DATA_INFO_H__
#define __HBN_VPF_DATA_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <hb_mem_mgr.h>
#include "hb_gdc_data_info.h"

#define HBN_VFLOW_PIPELINE_MAX 24u
#define HBN_VIO_BUFFER_MAX_PLANES 4u
#define HBN_METADATA_SIZE (4 * 1024) //4KB

#define HBN_LAYER_MAXIMUM 6u
#define HBN_PIPELINE_BIND_MAX 16u /**< vio pipeline max bind count  @NO{S09E05C02U}  */
#ifdef J6_CAMSYS
#define HBN_GETFRAME_TIMEOUT 4000
#else
#define HBN_GETFRAME_TIMEOUT 1000 //1000ms for dvb
#endif
#define HBN_MAX_VNODE_CONFIG 8u

typedef int64_t hbn_vnode_handle_t;
typedef int64_t hbn_vflow_handle_t;

// module type
typedef enum hb_vnode_type_e {
	HB_CAM = 1, // CAMERA type for hbn error.
	HB_VIN_V0 = 2, // XJ3
	HB_ISP_V0, // XJ3
	HB_IPU_V0, // XJ3
	HB_PYM_V0, // XJ3
	HB_GDC, // XJ3/J5/J6
	HB_VIN_V1, // J5
	HB_ISP_V1, // J5
	HB_PYM_V1, // J5
	HB_STITCH, // J5/J6
	HB_LKOF, // J5
	HB_VIN, // J6
	HB_ISP, // J6
	HB_YNR, // J6
	HB_PYM, // J6
	HB_IDU, // XJ3/J5/J6
	HB_VPU, // XJ3/J5/J6
	HB_JPU, // XJ3/J5/J6
	HB_CODEC, // XJ3/J5/J6
	HB_VIN_RB, // X5
	HB_ISP_RB, // X5
	HB_VSE, // X5
	HB_N2D, // X5
	HB_VNODE_TYPE_MAX
} hb_vnode_type;

typedef struct hbn_frame_info_s {
	uint32_t frame_id;
	uint64_t timestamps;
	struct timeval tv;
	struct timeval trig_tv;
	uint32_t frame_done;
	int32_t bufferindex;
} hbn_frame_info_t;

typedef struct hbn_buf_alloc_attr_s {
	int64_t flags;
	uint32_t buffers_num;
	uint32_t is_contig;
} hbn_buf_alloc_attr_t;

typedef struct hbn_vnode_image_s {
	hbn_frame_info_t info;
	hb_mem_graphic_buf_t buffer;
	void *metadata;
} hbn_vnode_image_t;

typedef struct hbn_vnode_image_group_s {
	hbn_frame_info_t info;
	hb_mem_graphic_buf_group_t buf_group;
	void *metadata;
} hbn_vnode_image_group_t;

typedef struct hbn_version_s {
	uint32_t major;
	uint32_t minor;
} hbn_version_t;

typedef int32_t hobot_status;

typedef struct vpf_ext_ctrl_t {
	uint32_t id;
	void *arg;
} vpf_ext_ctrl_t;

typedef enum vpf_bind_mode_e {
	BIND_NONE,
	BIND_OTF_INPUT,
	BIND_OTF_OUTPUT,
	BIND_M2M_INPUT,
	BIND_M2M_OUTPUT,
} vpf_bind_mode_t;


#ifdef __cplusplus
}
#endif

#endif
