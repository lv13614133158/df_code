/**
 * @file: hbn_ynr_cfg.h
 * @
 * @NO{S090E01C01I}
 * @ASIL{B}
 * @Copyright (c) 2023 by horizon, All Rights Reserved.
 */
#ifndef __HBN_YNR_CFG_H__
#define __HBN_YNR_CFG_H__

#include <stdint.h>
#define MAX_YNR_ICH 8
#define YNR_ALLOC_BUFFER_NUM 5

/**
 * @struct hobot_ynr_init_config
 * @brief YNR initialization parameters.
 * @NO{S09E01C02}
 */
struct hobot_ynr_init_config {
	/**
     * @var hobot_ynr_init_config::link_mode
     * online or offline.
     * range:N/A; default: N/A
     */
	uint32_t link_mode;
	/**
     * @var hobot_ynr_init_config::ynr_hbnk_min
     * ynr hbnk minimum for output and offline interface.
     * range:N/A; default: N/A
     */
	uint32_t ynr_hbnk_min;
	/**
     * @var hobot_ynr_init_config::ynr_vbnk_min
     * ynr vbnk minimum for offline interface.
     * range:N/A; default: N/A
     */
	uint32_t ynr_vbnk_min;
	/**
     * @var hobot_ynr_init_config::ynr_time_out_cfg
     * ynr time out counter configuration.
     * range:N/A; default: N/A
     */
	uint32_t ynr_time_out_cfg;
	/**
      * @var hobot_ynr_init_config::slot_id
      * isp slot_id.
      * range:N/A; default: N/A
      */
	uint32_t slot_id;
};

/**
 * @struct hobot_ynr_channel_input_config
 * @brief YNR channel initialization input parameters.
 * @NO{S09E01C02}
 */
struct hobot_ynr_channel_input_config {
	/**
     * @var hobot_ynr_channel_input_config::ch_img_width
     * image width, should be a multiple of 2, and valid range is from 8 to 4096.
     * range:N/A; default: N/A
     */
	uint32_t ch_img_width;
	/**
     * @var hobot_ynr_channel_input_config::ch_img_height
     * image height, should be a multiple of 2, and valid range is from 8 to 4096.
     * range:N/A; default: N/A
     */
	uint32_t ch_img_height;
};

/**
 * @struct hobot_ynr_channel_output_config
 * @brief YNR channel initialization output parameters.
 * @NO{S09E01C02}
 */
struct hobot_ynr_channel_output_config {
	/**
     * @var hobot_ynr_channel_output_config::ch_nr3d_pix_out_dma_byps
     * 1: bypass ynr3d pixel base output to AXI bus, 0: disable.
     * range:[0, 1]; default: N/A
     */
	uint32_t ch_nr3d_pix_out_dma_byps;
	/**
     * @var hobot_ynr_channel_output_config::ch_nr3d_debug_en
     * 3DNR debug switch.
     * range:[0, 1]; default: N/A
     */
	uint32_t ch_nr3d_debug_en;
};

/**
 * @struct hobot_ynr_channel_config
 * @brief All parameters of ynr channel configuration.
 * @NO{S09E01C02}
 */
typedef struct hobot_ynr_channel_config {
	/**
      * @var hobot_ynr_channel_config::hw_id
      * hardware id.
      * range:N/A; default: N/A
      */
	uint32_t hw_id;
	/**
     * @var hobot_ynr_channel_config::link_mode
     * online or offline.
     * range:N/A; default: N/A
     */
	uint32_t link_mode;

	/**
      * @var hobot_ynr_channel_config::slot_id
      * isp slot_id.
      * range:N/A; default: N/A
      */
	uint32_t slot_id;
	/**
     * @var hobot_ynr_channel_config::ch_img_width
     * image width, should be a multiple of 2, and valid range is from 8 to 4096.
     * range:N/A; default: N/A
     */
	uint32_t ch_img_width;
	/**
     * @var hobot_ynr_channel_config::ch_img_height
     * image height, should be a multiple of 2, and valid range is from 8 to 4096.
     * range:N/A; default: N/A
     */
	uint32_t ch_img_height;
	/**
     * @var hobot_ynr_channel_config::ch_nr3d_pix_out_dma_byps
     * 1: bypass ynr3d pixel base output to AXI bus, 0: disable.
     * range:[0, 1]; default: N/A
     */
	uint32_t nr2d_en;
	/**
     * @var hobot_ynr_channel_config::ch_nr3d_debug_en
     * 3DNR debug switch.
     * range:[0, 1]; default: N/A
     */
     uint32_t nr3d_en;

     uint32_t debug_en;
} ynr_info_t;

#endif
