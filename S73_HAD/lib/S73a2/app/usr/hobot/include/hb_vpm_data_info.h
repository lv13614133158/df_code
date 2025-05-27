/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/

#ifndef HB_VPM_DATA_INFO_H_
#define HB_VPM_DATA_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>
#include "hb_gdc_data_info.h"

#define HB_VIO_IPU_DS0_CB_MSG 0x001
#define HB_VIO_IPU_DS1_CB_MSG 0x002
#define HB_VIO_IPU_DS2_CB_MSG 0x004
#define HB_VIO_IPU_DS3_CB_MSG 0x008
#define HB_VIO_IPU_DS4_CB_MSG 0x010
#define HB_VIO_IPU_US_CB_MSG 0x020
#define HB_VIO_PYM_CB_MSG 0x040
#define HB_VIO_DIS_CB_MSG 0x080
#define HB_VIO_PYM_VER2_CB_MSG 0x100

#define HB_VIO_PYM_MAX_LAYER 6u

#define HW_FORMAT_RAW8 0x2A /**< raw8 format 8bit  @NO{S09E06C01U} */
#define HW_FORMAT_RAW10 0x2B /**< raw10 format 10bit  @NO{S09E06C01U}   */
#define HW_FORMAT_RAW12 0x2C /**< raw12 format 12bit  @NO{S09E06C01U}   */
#define HW_FORMAT_RAW14 0x2D /**< raw14 format 14bit   @NO{S09E06C01U}  */
#define HW_FORMAT_RAW16 0x2E /**< raw16 format 16bit   @NO{S09E06C01U}  */
#define HW_FORMAT_RAW20 0x2F /**< raw20 format 20bit  @NO{S09E06C01U}   */

#define HB_VIO_PIPELINE_MAX 24u /**< vio pipeline max count  @NO{S09E06C01U}  */
#define HB_VIO_PIPELINE_MAX_ID (HB_VIO_PIPELINE_MAX - 1u) /**< vio pipeline max id  @NO{S09E06C01U}  */
#define HB_VIO_PYM_MAX_BASE_LAYER 6u /**< pym max layer count   @NO{S09E06C01U} */
#define HB_VIO_PYM_DS_LAYER 6u /**< pym down scaler layer count   @NO{S09E06C01U} */
#define HB_VIO_BUFFER_MAX_PLANES 3u /**< buffer max plane count   @NO{S09E06C01U} */
#define HB_VIO_CIM_BUFF_MAX_NUM (32) /**< cim buffer max buffer count   @NO{S09E06C01U} */
#define HB_VIO_ISP_YUV_BUFF_MAX_NUM (32) /**< isp yuv buffer max count   @NO{S09E06C01U} */
#define HB_VIO_ISP_RAW_BUFF_MAX_NUM (32) /**< isp raw buffer max count  @NO{S09E06C01U}  */
#define HB_VIO_PYM_BUFF_MAX_NUM (64) /**< pym buffer max count  @NO{S09E06C01U}  */
#define HB_VIO_PYM_FB_BUFF_MAX_NUM (8) /**< pym feedback max count   @NO{S09E06C01U} */
#define HB_VIO_GDC_FB_BUFF_MAX_NUM (8) /**< gdc feadback max count  @NO{S09E06C01U}  */
#define HB_VIO_GDC_BUFF_MAX_NUM (8) /**< gdc output buffer max count   @NO{S09E06C01U} */
#define HW_FORMAT_YUV422_8BIT 0x1E /**< yuv 422 format 8bit   @NO{S09E06C01U}  */
#define HW_FORMAT_YUV422_10BIT 0x1F /**< yuv 422 format 10bit   @NO{S09E06C01U} */
#define GDC_FB_BUFFER_MASK 14u /**< gdc alloc feedback buffer flag   @NO{S09E06C01U} */
#define GDC_DATA_BUFFER_MASK 12u /**< gdc alloc output buffer buffer flag   @NO{S09E06C01U} */
#define HW_MAX_VNODE_NAME 20u /**< vio pipeline max vnode name  @NO{S09E06C01U}  */
#define NV_INPUT_PLANE 2u /**<input plane count  @NO{S09E06C01U} */

enum Format {
	HB_RGB,
	HB_YUV422,
	HB_YUV420SP,
	HB_YUV444,
	HB_RAW, //raw8
	HB_RAW10,
	HB_RAW12,
	HB_RAW16,
	HB_RAW24,
	HB_YUV420SP_RAW12, /* yuv420 & raw12 */
	HB_YUV422_RAW12, /* yuv422 & raw12 */
	HB_YUV420SP_RAW16, /* yuv420 & raw16 */
	HB_YUV422_RAW16, /* yuv422 & raw16 */
	HB_IR8,
	HB_DECOMP_RAW, //decomp 24bit
	HB_FORMAT_MAX
};

/**
 * @enum rotation_e
 * rotation value @NO{S09E06C01U}
 */
enum rotation_e { ROTATION_0 = 0, ROTATION_90 = 90, ROTATION_180 = 180, ROTATION_270 = 270 };

/**
 * @enum VIO_INFO_TYPE_S
 * vio information type @NO{S09E06C01U}
 */
typedef enum VIO_INFO_TYPE_S {
	HB_VIO_CALLBACK_ENABLE = 0,
	HB_VIO_CALLBACK_DISABLE,
	HB_VIO_IPU_SIZE_INFO, //reserve for ipu size setting in dis
	HB_VIO_IPU_US_IMG_INFO,
	HB_VIO_IPU_DS0_IMG_INFO,
	HB_VIO_IPU_DS1_IMG_INFO,
	HB_VIO_IPU_DS2_IMG_INFO,
	HB_VIO_IPU_DS3_IMG_INFO,
	HB_VIO_IPU_DS4_IMG_INFO,
	HB_VIO_PYM_IMG_INFO,
	HB_VIO_ISP_IMG_INFO,
	HB_VIO_PYM_V2_IMG_INFO,
	HB_VIO_PYM_V3_IMG_INFO,
	HB_VIO_INFO_MAX
} VIO_INFO_TYPE_E;

/**
 * @enum VIO_CALLBACK_TYPE
 * vio callback type @NO{S09E06C01U}
 */
typedef enum VIO_CALLBACK_TYPE {
	HB_VIO_IPU_DS0_CALLBACK = 0,
	HB_VIO_IPU_DS1_CALLBACK,
	HB_VIO_IPU_DS2_CALLBACK,
	HB_VIO_IPU_DS3_CALLBACK,
	HB_VIO_IPU_DS4_CALLBACK,
	HB_VIO_IPU_US_CALLBACK,
	HB_VIO_PYM_CALLBACK, // 6
	HB_VIO_DIS_CALLBACK,
	HB_VIO_PYM_V2_CALLBACK,
	HB_VIO_MAX_CALLBACK
} VIO_CALLBACK_TYPE_E;

/**
 * @enum VIO_DATA_TYPE_S
 * vio data type @NO{S09E06C01U}
 */
typedef enum VIO_DATA_TYPE_S {
	HB_VIO_DATA_TYPE_INVALID = -1,
	HB_VIO_IPU_DS0_DATA = 0,
	HB_VIO_IPU_DS1_DATA,
	HB_VIO_IPU_DS2_DATA,
	HB_VIO_IPU_DS3_DATA,
	HB_VIO_IPU_DS4_DATA,
	HB_VIO_IPU_US_DATA, // 5
	HB_VIO_PYM_FEEDBACK_SRC_DATA, // for debug
	HB_VIO_PYM_DATA, //7
	HB_VIO_SIF_FEEDBACK_SRC_DATA,
	HB_VIO_SIF_RAW_DATA,
	HB_VIO_SIF_YUV_DATA, //10
	HB_VIO_ISP_YUV_DATA, // for debug, a process result for raw feedback
	HB_VIO_GDC_DATA,
	HB_VIO_GDC1_DATA,
	HB_VIO_IARWB_DATA,
	HB_VIO_GDC_FEEDBACK_SRC_DATA, //15
	HB_VIO_GDC1_FEEDBACK_SRC_DATA,
	HB_VIO_PYM_LAYER_DATA,
	HB_VIO_MD_DATA,
	HB_VIO_ISP_RAW_DATA,
	HB_VIO_PYM_COMMON_DATA,
	HB_VIO_PYM_DATA_V2, //21
	HB_VIO_PYM_DATA_V3, //22
	HB_VIO_CIM_FEEDBACK_SRC_DATA, //23
	HB_VIO_CIM_RAW_DATA,
	HB_VIO_CIM_YUV_DATA,
	HB_VIO_CIM_ROI_DATA,
	HB_VIO_EMBED_DATA,
	HB_VIO_EMBED_INFO,
	HB_VIO_DATA_TYPE_MAX
} VIO_DATA_TYPE_E;

/**
 * @enum buffer_state
 * buffer state @NO{S09E06C01U}
 */
typedef enum buffer_state {
	BUFFER_AVAILABLE,
	BUFFER_PROCESS,
	BUFFER_DONE,
	BUFFER_REPROCESS,
	BUFFER_USER,
	BUFFER_INVALID
} buffer_state_e;

/**
 * @struct address_info_s
 * @brief Define the descriptor of address information.
 * @NO{S09E06C01U}
 */
typedef struct address_info_s {
	uint16_t width; /**< buffer width  */
	uint16_t height; /**< buffer height  */
	uint16_t stride_size; /**< buffer stride  */
	char *addr[HB_VIO_BUFFER_MAX_PLANES]; /**< buffer virtual address */
	uint64_t paddr[HB_VIO_BUFFER_MAX_PLANES]; /**< buffer physical address */
	int32_t fd[HB_VIO_BUFFER_MAX_PLANES]; /**< ion buf fd */
} address_info_t;

/**
 * @struct image_info_s
 * @brief Define the descriptor of image information.
 * @NO{S09E06C01U}
 */
typedef struct image_info_s {
	uint16_t sensor_id; /**< sensor id */
	uint32_t pipeline_id; /**< pipeline id */
	uint32_t frame_id; /**< frame id */
	uint64_t time_stamp; /**< HW time stamp */
	struct timeval tv; /**< system time of hal get buf */
	int32_t buf_index; /**< buffer index */
	int32_t img_format; /**< image format */
	int32_t fd[HB_VIO_BUFFER_MAX_PLANES]; /**< ion buf fd */
	uint32_t size[HB_VIO_BUFFER_MAX_PLANES]; /**< buffer size per plane */
	uint32_t planeCount; /**< image plane count */
	uint32_t dynamic_flag; /**< dynamic flag */
	uint32_t water_mark_line; /**< water mark line value */
	VIO_DATA_TYPE_E data_type; /**< buffer data type */
	buffer_state_e state; /**< buffer state */
	uint64_t desc; /**< temp description for isp raw feedback */
	struct timeval trig_tv;/**< system time of lpwm trigger */
} image_info_t;

/*
 * buf type  fd[num]                        size[num]                   addr[num]
 *
 * sif buf : fd[0(raw)]                     size[0(raw)]                addr[0(raw)]
 * sif dol2: fd[0(raw),1(raw)]              size[0(raw),1(raw)]         addr[0(raw),1(raw)]
 * sif dol3: fd[0(raw),1(raw),2(raw)]       size[0(raw),1(raw),2(raw)]  addr[0(raw),1(raw),2(raw)]
 * ipu buf : fd[0(y),1(c)]                  size[0(y),1(c)]             addr[0(y),1(c)]
 * pym buf : fd[0(all channel)]             size[0(all output)]         addr[0(y),1(c)] * 24
 * */

/**
 * @struct hb_vio_buffer_s
 * @brief Define the descriptor of vio buffer
 * @NO{S09E06C01U}
 */
typedef struct hb_vio_buffer_s {
	image_info_t img_info; /**< image information struct */
	address_info_t img_addr; /**< image address information struct */
} hb_vio_buffer_t;

//use in j3
typedef struct pym_buffer_s {
	image_info_t pym_img_info;
	address_info_t pym[6];
	address_info_t pym_roi[6][3];
	address_info_t us[6];
	char *addr_whole[HB_VIO_BUFFER_MAX_PLANES];
	uint64_t paddr_whole[HB_VIO_BUFFER_MAX_PLANES];
	uint32_t layer_size[30][HB_VIO_BUFFER_MAX_PLANES];
} pym_buffer_t; //Keep xj3 data struct
//use in j3 j5
typedef struct pym_buffer_common_s {
	image_info_t pym_img_info;
	address_info_t pym[HB_VIO_PYM_MAX_BASE_LAYER]; //only for base layer
} pym_buffer_common_t;
//use in j5
typedef struct pym_buffer_v2_s {
	image_info_t pym_img_info;
	address_info_t src_out;
	address_info_t us_roi;
	address_info_t ds_roi[6];
	address_info_t gs[5];
	address_info_t bl[5];
} pym_buffer_v2_t;

//use in j6

/**
 * @struct pym_buffer_v3_s
 * @brief Define the descriptor of pym v3 buffer.
 * @NO{S09E06C01U}
 */
typedef struct pym_buffer_v3_s {
	image_info_t pym_img_info; /**< pym image information struct */
	address_info_t ds_out[HB_VIO_PYM_DS_LAYER]; /**< pym ds layer struct */
} pym_buffer_v3_t;

/**
 * @struct chn_img_info_s
 * @brief Define the descriptor of image information
 * @NO{S09E06C01U}
 */
typedef struct chn_img_info_s {
	uint16_t width; /**< image width */
	uint16_t height; /**< image height */
	uint16_t format; /**< image format */
	uint16_t buf_count; /**< buffer count */
} chn_img_info_t;

typedef void (*data_cb)(uint32_t pipe_id, uint32_t event, void *data, void *userdata);

#ifdef __cplusplus
}
#endif

#endif //HB_VPM_DATA_INFO_H_