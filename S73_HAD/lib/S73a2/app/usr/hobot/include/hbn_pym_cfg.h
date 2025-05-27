/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2019 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/

#ifndef __HBN_PYM_CFG_H__
#define __HBN_PYM_CFG_H__

#define MAX_DS_NUM (6u)
#define MAX_PRE_INT (8u)

#define PYM_AUTO_MODE 0u
#define PYM_MANUAL_MODE 1u
#define PYM_OTF_MODE 2u
#define PYM_M2M_MODE 3u

enum pym_layer_sel {
	PYM_SRC_SEL,
	PYM_BL_SEL,
	PYM_CFG_SEL_MAX,
};

typedef struct {
	uint32_t start_top; //ROI coordinate Y
	uint32_t start_left; //ROI coordinate X
	uint32_t region_width; //ROI width
	uint32_t region_height; //ROI height
	uint32_t wstride_uv; //
	uint32_t wstride_y; //
	uint32_t vstride;
	uint32_t step_v;
	uint32_t step_h;
	uint32_t out_width;
	uint32_t out_height;
	uint32_t phase_y_v;
	uint32_t phase_y_h;
} roi_box_t;

typedef struct {
	uint32_t pixel_num_before_sol;
	uint32_t invalid_head_lines;
	uint32_t src_in_width;
	uint32_t src_in_height;
	uint32_t src_in_stride_y;
	uint32_t src_in_stride_uv;
	uint32_t suffix_hb_val;
	uint32_t prefix_hb_val;
	uint32_t suffix_vb_val;
	uint32_t prefix_vb_val;
	uint8_t bl_max_layer_en;
	uint8_t ds_roi_en;
	uint8_t ds_roi_uv_bypass;
	uint8_t ds_roi_sel[MAX_DS_NUM];
	uint8_t ds_roi_layer[MAX_DS_NUM];
	roi_box_t ds_roi_info[MAX_DS_NUM];
	uint32_t pre_int_set_y[MAX_PRE_INT];
	uint32_t pre_int_set_uv[MAX_PRE_INT];
} chn_ctrl_t;

typedef struct {
	uint8_t hw_id;
	uint8_t pym_mode;
	uint8_t slot_id;
	uint8_t axi_burst_len;
	uint8_t in_linebuff_watermark;
	uint8_t out_buf_noinvalid;
	uint8_t out_buf_noncached;
	uint8_t in_buf_noclean;
	uint8_t in_buf_noncached;
	uint8_t buf_consecutive;
	uint8_t pingpong_ring;
	uint32_t output_buf_num;
	uint32_t timeout;
	uint32_t threshold_time;
	int32_t layer_num_trans_next;
	int32_t layer_num_share_prev;
	chn_ctrl_t chn_ctrl;
	uint32_t fb_buf_num;
	uint32_t reserved[6];
	uint32_t magicNumber;
} pym_cfg_t;

#endif //__HBN_PYM_CFG_H__
