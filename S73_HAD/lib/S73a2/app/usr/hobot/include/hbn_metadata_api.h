/**
 * @file: vio_metadata_api.h
 * @
 * @NO{S09E05C01}
 * @ASIL{B}
 * @Copyright (c) 2023 by horizon, All Rights Reserved.
 */
/***************************************************************************
 *                      COPYRIGHT NOTICE
 *             Copyright 2019 Horizon Robotics, Inc.
 *                     All rights reserved.
 ***************************************************************************/

#ifndef HBN_METADATA_API_H
#define HBN_METADATA_API_H

#include "hbn_vpf_data_info.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

// 0x00.00.00.00===>0x00.00.major.minor
#define METADATA_HEADER_VERSION (0x00000100u)

#define METADATA_ITEM_MAGIC	(0x11223344u)

/**
 * @struct metadata_header_s
 * @brief Define the descriptor of metadata_header.
 * @NO{S09E05C01}
 */
struct metadata_header_s {
	uint16_t version;    // version
	uint8_t header_size; // metadata header size
	uint8_t crc_info;    // reserved crc cfg
	uint32_t crc_data;   // reserved crc data
	uint32_t frame_id;
	union {
		uint32_t offset;
		uint64_t item_offset;
	};
	uint32_t reserved[10]; // reserved
};

struct item_header_s {
	uint32_t magic; // item magic
	uint8_t tag; // module
	uint8_t idx; // id
	uint16_t reserved; // reserved
	uint32_t size; // item_header_size + item_buf_size
};

// cim item idx
#define CIM_ITEM_RGBIR_IDX	(0x0)
struct cim_item_s {
	uint32_t rgbir_index;
};

// isp item idx
#define ISP_ITEM_AE_PARAM_IDX					(0x00)
#define ISP_ITEM_SENSOR_PARAM_IDX				(0x01)
#define ISP_ITEM_AWB_PARAM_IDX					(0x02)
#define ISP_ITEM_IRIDIX_PARAM_IDX				(0x03)
#define ISP_ITEM_GAMMA_PARAM_IDX				(0x04)

// AE_PARAM
struct isp_item_ae_param_s {
	uint32_t ae_exposure;
	uint32_t ae_exposure_ratio;
	uint32_t error_log2;
	uint32_t ae_hist_mean;
	uint32_t ae_hist_median;
	uint32_t ae_hysteresis_weight;
	uint32_t ldr_gain_log2;
	uint32_t ae_ctrl_flag;
	uint32_t m1;
};

// SENSOR_PARAM
struct isp_item_sensor_param_s {
	uint32_t ae_exposure;
	uint32_t again;
	uint32_t dgain;
	uint32_t ispgain;
	uint32_t sys_exposure;
	uint32_t status_info_exp_log2;
	uint32_t cur_lux;
};

// AWB_PARAM
struct isp_item_awb_param_s {
	uint32_t awb_red_gain;
	uint32_t awb_blue_gain;
	int32_t temperature_detected;
};

// IRIDIX_PARAM
struct isp_item_iridix_param_s {
	uint32_t strength_target;
	uint32_t dark_enh;
	uint32_t digital_gain;
	uint32_t contrast;
	uint32_t strength_oscillation_compensation;
	uint32_t bright_pr;
	uint32_t svariance;
};

// GAMMA_PARAM
struct isp_item_gamma_param_s {
	uint32_t gamma_gain;
	uint32_t gamma_offset;
};

int32_t hbn_isp_get_algo_ae_param(void *metadata, struct isp_item_ae_param_s *ae_param);
int32_t hbn_isp_get_algo_awb_param(void *metadata, struct isp_item_awb_param_s *awb_param);
int32_t hbn_isp_get_algo_iridix_param(void *metadata, struct isp_item_iridix_param_s *iridix_param);
int32_t hbn_isp_get_algo_gamma_param(void *metadata, struct isp_item_gamma_param_s *gamma_param);
int32_t hbn_isp_get_sensor_param(void *metadata, struct isp_item_sensor_param_s *sensor_param);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
