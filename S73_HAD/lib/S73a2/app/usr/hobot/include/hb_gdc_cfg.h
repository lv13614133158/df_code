/**
 * @file: hb_gdc_cfg.h
 * @
 * @NO{S090E03C02}
 * @ASIL{B}
 * @Copyright (c) 2023 by horizon, All Rights Reserved.
 */
#ifndef __HB_GDC_CFG_H__
#define __HB_GDC_CFG_H__

#define GDC_MAX_INPUT_PLANE (3u)

/**
 * @struct gdc_config_s
 * @brief gdc config parameters.
 * @NO{S09E06C01U}
 */
typedef struct gdc_config {
	/**
         * @var vpf_gdc_config::config_addr
         * gdc config address parameters.
         * range:N/A; default: N/A
         */
	uint64_t config_addr;
	/**
         * @var vpf_gdc_config::config_size
         * gdc config size in 32bit parameters.
         * range:N/A; default: N/A
         */
	uint32_t config_size;
	/**
         * @var vpf_gdc_config::input_width
         * gdc input width resolution parameters.
         * range:N/A; default: N/A
         */
	uint32_t input_width;
	/**
         * @var vpf_gdc_config::input_height
         * gdc input height resolution parameters.
         * range:N/A; default: N/A
         */
	uint32_t input_height;
	/**
         * @var vpf_gdc_config::input_stride
         * gdc input stride (pixel) parameters.
         * range:N/A; default: N/A
         */
	uint32_t input_stride;
	/**
         * @var vpf_gdc_config::output_width
         * gdc output width resolution parameters.
         * range:N/A; default: N/A
         */
	uint32_t output_width;
	/**
         * @var vpf_gdc_config::output_height
         * gdc output height resolution parameters.
         * range:N/A; default: N/A
         */
	uint32_t output_height;
	/**
         * @var vpf_gdc_config::output_stride
         * gdc output stride (pixel) parameters.
         * range:N/A; default: N/A
         */
	uint32_t output_stride;
	/**
         * @var vpf_gdc_config::div_width
         * use in dividing UV dimensions parameters.
         * range:N/A; default: N/A
         */
	uint8_t div_width;
	/**
         * @var vpf_gdc_config::div_height
         * use in dividing UV dimensions parameters.
         * range:N/A; default: N/A
         */
	uint8_t div_height;
	/**
         * @var vpf_gdc_config::total_planes
         * total planes parameters.
         * range:N/A; default: N/A
         */
	uint32_t total_planes;
	/**
         * @var vpf_gdc_config::sequential_mode
         * sequential processing parameters.
         * range:N/A; default: N/A
         */
	uint8_t sequential_mode;
} gdc_config_t;

/**
 * @struct gdc_settings
 * @brief Define the descriptor of gdc total setting.
 * @NO{S09E06C01U}
 */
typedef struct gdc_settings {
	gdc_config_t gdc_config; /**< array of gdc configuration and sizes. */
	int32_t binary_ion_id; /* share id for config binary physical addr; */
	uint64_t binary_offset; /* config binary physical addr offset */
	uint32_t reserved[8]; /**< reserved use */
	uint32_t magicNumber; /**< magic number */
} gdc_settings_t;

#endif
