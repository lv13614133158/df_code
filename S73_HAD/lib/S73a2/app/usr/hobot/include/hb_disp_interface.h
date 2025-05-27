/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/

#ifndef HB_DISP_INTERFACE_H
#define HB_DISP_INTERFACE_H
#include "hbn_idu_cfg.h"
#include "hb_mem_mgr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifndef HB_API
#define HB_API
#endif

#define DEFAULT_CFG_PATH ""

#define MAX_FRAME_WIDTH (3840u)
#define MAX_FRAME_HEIGHT (2160u)
#define MAX_INPUT_WIDTH (2880u)
#define MAX_INPUT_HEIGHT (2160u)
#define MAX_OUTPUT_WIDTH (3840u)
#define MAX_OUTPUT_HEIGHT (2160u)
#define MAX_FRAME_BUF_SIZE (MAX_FRAME_WIDTH * MAX_FRAME_HEIGHT * 4u)

typedef enum {
	DISP_PRI_1 = 0,
	DISP_PRI_2 = 1,
	DISP_PRI_3 = 2,
	DISP_PRI_4 = 3,
	DISP_PRI_5 = 4,
	DISP_PRI_6 = 5,
	DISP_PRI_MAX = 6,
} disp_layer_pri_e;

typedef enum {
	USER_CFG,
	CHANNEL_CFG,
	OVERLAY_CFG,
	SCALE_CFG,
	GAMMA_CFG,
	OUTPUT_CFG,
} config_type_e;

typedef enum {
	OUTPUT_CHANNEL0 = 1,
	OUTPUT_CHANNEL1 = 2,
	OUTPUT_CHANNEL2 = 4,
	OUTPUT_CHANNEL3 = 8,
} output_channel_e;

typedef enum {
	OUTPUT_MIPI = 0,
	OUTPUT_BT1120 = 1,
	OUTPUT_RGB888 = 2,
	OUTPUT_BT656 = 3,
	OUTPUT_IPI = 4,
} output_mode_e;

typedef enum {
	DISP_OUTPUT_CFG = 0,
	DISP_CHANNEL_CFG,
	DISP_SET_VIDEO_ADDR,
	GET_DISP_DONE,
	DISP_SET_TIMING,
	DISP_GAMMA_CFG,
	DISP_SCALE_CFG,
	SET_PIXEL_CLK,
	SET_IPI_CLK,
	SET_ONE_FRAME_TIME,
	DISP_MAX_TYPE_NUM,
} disp_attr_type_e;

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Initialize a display device instance
 *
 * @param [in] disp_id display device id
 * @param [in] cfg_file path of the config json file
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read display config json file
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_init_dev_cfg(uint32_t disp_id, const char *cfg_file);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Initialize all display device
 *
 * @param [in] cfg_file path of the config json file
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read display config json file
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_init_cfg(const char *cfg_file);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Close all display device
 *
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_close(void);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Close a display device instance
 *
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_close_id(uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Start all display device
 *
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_start(void);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Start a display device instance
 *
 * @param [in] NA
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_start_id(uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Stop all display device
 *
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_stop(void);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Stop a display device instance
 *
 * @param [in] NA
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_stop_id(uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Enable a layer of all display device
 *
 * @param [in] layer_number the number of layer
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_layer_on(uint32_t layer_number);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Enable a layer of a display device instance
 *
 * @param [in] layer_number layer id
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_layer_on_id(uint32_t layer_number, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Close a layer of all display device
 *
 * @param [in] layer_number layer id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_layer_off(uint32_t layer_number);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Close a layer of a display device instance
 *
 * @param [in] layer_number layer id
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_layer_off_id(uint32_t layer_number, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set video buffer address
 *
 * @param [in] addr0_y the y address of the image to be displayed in DISP layer 0
 * @param [in] addr0_c the uv address of the image to be displayed in DISP layer 0
 * @param [in] addr1_y the y address of the image to be displayed in DISP layer 1
 * @param [in] addr1_c the uv address of the image to be displayed in DISP layer 1
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_video_bufaddr(uint32_t layer_no, void *addr_y, void *addr_c);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set video buffer address to a display device instance
 *
 * @param [in] addr0_y the y address of the image to be displayed in DISP layer 0
 * @param [in] addr0_c the uv address of the image to be displayed in DISP layer 0
 * @param [in] addr1_y the y address of the image to be displayed in DISP layer 1
 * @param [in] addr1_c the uv address of the image to be displayed in DISP layer 1
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_video_bufaddr_id(uint32_t disp_id, uint32_t layer_no, void *addr_y, void *addr_c);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set video buffer address
 *
 * @param [in] layer_no display layer id
 * @param [in] width width of the layer
 * @param [in] height height of the layer
 * @param [in] x_pos x position of the layer
 * @param [in] y_pos y position of the layer
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_layer_cfg(uint32_t layer_no, uint32_t width,
				     uint32_t height, uint32_t x_pos,
				     uint32_t y_pos);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set video buffer address for a display device instance
 *
 * @param [in] layer_no display layer id
 * @param [in] width width of the layer
 * @param [in] height height of the layer
 * @param [in] x_pos x position of the layer
 * @param [in] y_pos y position of the layer
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_layer_cfg_id(uint32_t layer_no, uint32_t width,
					uint32_t height, uint32_t x_pos,
					uint32_t y_pos, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set display timing
 *
 * @param [in] user_timing the timing parameter user want to set
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_timing(disp_timing_t *user_timing);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set display timing for a display device instance
 *
 * @param [in] user_timing the timing parameter user want to set
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_timing_id(disp_timing_t *user_timing,
				     uint32_t	    disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get gamma config value
 *
 * @param [out] gamma_val input gamma value pointer, store result
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_gamma_cfg(float32_t *gamma_val);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get gamma config value for a display device instance
 *
 * @param [out] gamma_val input gamma value pointer, store result
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_gamma_cfg_id(float32_t *gamma_val, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set gamma config for a display device instance
 *
 * @param [in] gamma_user gamma value user want to set
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_gamma_cfg(float32_t gamma_user);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set gamma config
 *
 * @param [in] gamma_user gamma value user want to set
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_gamma_cfg_id(float32_t gamma_user, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set output dynamic config
 *
 * @param [in] dynamic_cfg output dynamic value user want to set
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_output_dynamic_cfg_id(output_dynamic_cfg_t *dynamic_cfg, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get ouput config
 *
 * @param [out] cfg the output config parameters struct that user gets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_output_cfg(output_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get ouput config of a display device instance
 *
 * @param [out] cfg the output config parameters struct that user gets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_output_cfg_id(output_cfg_t *cfg, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set ouput config
 *
 * @param [in] cfg the output config parameters struct that user sets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_output_cfg(output_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set ouput config of a display device instance
 *
 * @param [in] cfg the output config parameters struct that user sets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_output_cfg_id(output_cfg_t *cfg,
					 uint32_t	     disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get upscale config
 *
 * @param [out] cfg the up scale config parameters struct that user gets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_upscaling_cfg(upscaling_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get upscale config of a display device instance
 *
 * @param [out] cfg the up scale config parameters struct that user gets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_upscaling_cfg_id(upscaling_cfg_t *cfg,
					    uint32_t	     disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set upscale config of a display device instance
 *
 * @param [in] cfg the up scale config parameters struct that user Sets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_upscaling_cfg(const upscaling_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set upscale config of a display device instance
 *
 * @param [in] cfg the up scale config parameters struct that user Sets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_upscaling_cfg_id(const upscaling_cfg_t *cfg,
					    uint32_t		   disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get channel config parameters
 *
 * @param [in] chn the layer number user want to get
 * @param [out] cfg the up scale config parameters struct that user Sets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_channel_cfg(uint32_t chn, channel_base_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Get channel config parameters of a display device instance
 *
 * @param [in] chn the layer number user want to get
 * @param [out] cfg the channel config parameters struct that user Gets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_channel_cfg_id(uint32_t chn, channel_base_cfg_t *cfg,
					  uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set channel config parameters of a display device instance
 *
 * @param [in] chn the layer number user want to set
 * @param [in] cfg the up scale config parameters struct that user sets
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_channel_cfg(uint32_t			 chn,
				       channel_base_cfg_t *cfg);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief Set channel config parameters of a display device instance
 *
 * @param [in] chn the layer number user want to set
 * @param [in] cfg the up scale config parameters struct that user sets
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_channel_cfg_id(uint32_t		    chn,
					  channel_base_cfg_t *cfg,
					  uint32_t		    disp_id);
/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user config up-scale
 *
 * @param [in] src_w width of the source graphic
 * @param [in] src_h height of the source graphic
 * @param [in] tag_w width of the target graphic
 * @param [in] tag_h height of the target graphic
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_out_upscale(uint32_t src_w, uint32_t src_h,
				   uint32_t tag_w, uint32_t tag_h);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user config up-scale for a display device instance
 *
 * @param [in] src_w width of the source graphic
 * @param [in] src_h height of the source graphic
 * @param [in] tag_w width of the target graphic
 * @param [in] tag_h height of the target graphic
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_out_upscale_id(uint32_t src_w, uint32_t src_h,
				      uint32_t tag_w, uint32_t tag_h,
				      uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user get the display done flag
 *
 *
 * @retval 0:not done;1:done
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_display_done(void);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user get the display done flag for a display device instance
 *
 * @param [in] disp_id display device id
 *
 * @retval 0:not done;1:done
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_display_done_id(uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user check whether the graphic size matches the channel
 *
 * @param [in] graphic_size the graphic size
 * @param [in] disp_layer_no layer number of DISP
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_check_video_bufaddr_valid(size_t	  graphic_size,
						 uint32_t disp_layer_no);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user check whether the graphic size matches the channel
 *
 * @param [in] graphic_size the graphic size
 * @param [in] disp_layer_no layer number of DISP
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_check_video_bufaddr_valid_id(size_t   graphic_size,
						    uint32_t disp_layer_no,
						    uint32_t  disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user get layer buffer read done flag
 *
 * @param [in] layer layer id
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_video_display_done_id(uint32_t layer, uint32_t disp_id);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user get layer buffer read done flag
 *
 * @param [in] layer layer id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_video_display_done(uint32_t layer);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user wait display vsync flag
 *
 * @param [in] disp_id display device id
 * @param [in] rel_seq user request vsync count
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_disp_done_sync_id(uint32_t disp_id, uint64_t rel_seq);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user get capture buffer
 *
 * @param [in] disp_id display device id
 * @param [in] timeout wait timeout(ms)
 * @param [out] out_buf user import graphic buffer
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_get_capture_buf_id(uint32_t disp_id, uint32_t timeout, struct hb_mem_graphic_buf_t *out_buf);


/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user release capture buffer
 *
 * @param [in] disp_id display device id
 * @param [out] out_buf user import graphic buffer
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_release_capture_buf_id(uint32_t disp_id, struct hb_mem_graphic_buf_t *out_buf);

/**
 * @NO{S12E02C04I}
 * @ASIL{B}
 * @brief user trigger display control oneshot output
 *
 * @param [in] disp_id display device id
 *
 * @retval "= 0" success
 * @retval <0 failed
 *
 * @callgraph
 * @callergraph
 * @data_read NULL
 * @data_updated NULL
 * @compatibility HW: J6
 * @compatibility SW: 0.0.1
 * @design
 */
HB_API int32_t hb_disp_set_disp_oneshot_trigger_id(uint32_t disp_id);

HB_API int32_t hb_disp_get_display_capture_crc_id(uint32_t disp_id, uint32_t *crc);

#ifdef __cplusplus
}
#endif
#endif