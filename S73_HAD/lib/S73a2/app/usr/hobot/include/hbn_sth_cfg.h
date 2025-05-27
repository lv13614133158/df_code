/**
 * @file: hbn_sth_cfg.h
 * @
 * @NO{S09E04C02}
 * @ASIL{B}
 * @Copyright (c) 2023 by horizon, All Rights Reserved.
 */
#ifndef __HBN_STH_CFG_H__
#define __HBN_STH_CFG_H__

#define MAX_STH_ROI_NUMS 12u /**< the max number of roi that stitch can frocess*/
#define MAX_STH_FRAME_PLAN 2u

enum sth_working_mode {
	STH_MODE_FB_EXTERNAL_BUF,
	STH_MODE_FB_INTERNAL_BUF,
	STH_MODE_FLOW,
	STH_MODE_INVAIL
};

enum sth_blending_direct { //enumeration of direct
	BLENDING_DIRECT_LT = 0, //left and top direct
	BLENDING_DIRECT_RB = 1, //right and bottom direct
	BLENDING_DIRECT_LB = 2, //left and bottom direct
	BLENDING_DIRECT_RT = 3, //right and top direct
	BLENDING_DIRECT_MAX = 4 //max value of direct
};

//enumeration of stitching mode
enum sth_blending_mode {
	BLENDING_MODE_ONLINE = 0, //online mode
	BLENDING_MODE_ALPHA = 1, //alpha mode
	BLENDING_MODE_ALPHA_BETA = 2, //alpha beda mode
	BLENDING_MODE_SRC = 3, //src copy mode
	BLENDING_MODE_ALPHA_SRC = 5 //arpha src0 mode
};

struct blending_attr {
	uint32_t roi_index; //dst roi index
	uint32_t blending_mode;
	uint32_t direct;
	uint32_t uv_en;
	uint32_t src0_index; // 指明是哪个图像源
	uint32_t src1_index;

	//optional parameters
	uint32_t margin; //0-127
	uint32_t margin_inv;

	uint32_t gain_src0_yuv[3]; //0:y 1:u 2:v
	uint32_t gain_src1_yuv[3];
};

struct roi_info {
	uint32_t roi_index;
	uint32_t roi_x;
	uint32_t roi_y;
	uint32_t roi_w;
	uint32_t roi_h;
};

struct stitch_ch_attr {
	uint32_t width;
	uint32_t height;
	uint32_t strid[MAX_STH_FRAME_PLAN];
	struct roi_info rois[MAX_STH_ROI_NUMS];
};

struct lut_attr {
	int32_t share_id;
	uint64_t vaddr;
	uint64_t offset;
	uint64_t size;
};

struct stitch_base_attr {
	uint32_t mode;
	uint32_t roi_nums;
	uint32_t img_nums;
	struct lut_attr alpha_lut;
	struct lut_attr beta_lut;
	struct blending_attr blending[MAX_STH_ROI_NUMS]; // ROI_MAX_NUMS=12
};

#endif