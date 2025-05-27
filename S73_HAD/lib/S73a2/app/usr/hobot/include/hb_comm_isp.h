/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/

#ifndef HB_COMM_ISP_H_
#define HB_COMM_ISP_H_ /*PRQA S 0603*/

#ifndef _LINUX_KERNEL_MODE /*user space*/
#include <sys/time.h> /*PRQA S 5130*/
#include <stdint.h>
#include <stdbool.h>
#else /*kernel space */
#include <linux/time64.h>
#include <uapi/linux/time.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HB_NULL (void*)(0L)
#define HB_SUCCESS (0)
#define HB_FAILURE (-1)
#define ISP_INVAILD_VALUE (0xFF)
#define HB_VOID void

#define MAX_WIDTH (4096u)
#define MAX_HEIGHT (2160u) /* define new TRM r1p0 */
#define MAX_FRAME_RATE (120u)

/* j6E support 2 isp hw:isp0 and isp1 */
#define ISP_SAFETY_SLOT_NUMS (4u)
#define FIRMWARE_SENSOR_NUMBER (12u)
#define FIRMWARE_CONTEXT_NUMBER (FIRMWARE_SENSOR_NUMBER + ISP_SAFETY_SLOT_NUMS)

#define ISP_HW0 (0u)
#define ISP_HW1 (1u)
#define ISP_IP_MAX (2u)

#define ISP_IP_SENSOR_SLOTS (FIRMWARE_SENSOR_NUMBER) /* value 12: slots of per isp hw, include sensor slots */
#define ISP_IP_SLOTS \
	(FIRMWARE_CONTEXT_NUMBER) /* value 16: slots of per isp hw, include safety slots and
                                                                   sensor slots */
#define ISP_SOC_SLOTS_MAX (ISP_IP_MAX * ISP_IP_SLOTS) /* value 32: toatl slots number of 2 isp hws */
#define ISP_IP_SENSOR_SLOTS_MAX ((uint32_t)ISP_IP_MAX * (uint32_t)ISP_IP_SENSOR_SLOTS) /* value 24: J6E toatl sensor number of 2 isp hws */

#define ISP_MIN_PIPE0 (0u)
#define LEN_ADDR_ISP (0x20000u)

#define ISP_MAX_IMAGE_OUTPUT_PLANE (3u)
#define ISP_AXI_OUTPUT_MAX_PLANES (4u)

#define ISP_AE_ADDR_OFFSET (0x8000u) //hw size 2112bytes,sw used 2096 bytes
#define ISP_AE_5BIN_ADDR_OFFSET (0xd000u) //size 1856bytes
#define ISP_AE_5BIN_LEN (1856u)
#define ISP_AWB_ADDR_OFFSET (ISP_AE_5BIN_ADDR_OFFSET + ISP_AE_5BIN_LEN) //size 1816bytes

/*----------------------------------------------*
 * const defination                             *
 *----------------------------------------------*/
typedef enum {
	HB_FALSE = 0,
	HB_TRUE = 1,
} HB_BOOL;

/*******************************************************************************************
* description:AE 1024-bin histogram statistics
*
* from isp_trm_p162,524 words(32bits), it is 2096 Bytes
*
*   31           15          0
*   --------------------------
*0  |____________|___bin0____|arrary[0]
*1  |____________|___________|
*2  |____________|___________|
*3  |____________|___________|
*   |____________|___________|
*   |____________|___________|
*511|___bin1023__|___________|
*   |            .
*   |            .
*   |            .
*   |________________________|
*   |________________________|
*   |______frame_counter_____|arrary[HISTOGRAM_BUFFER_FRAME_COUNTER_OFFSET]
*523|__________crc___________|
***********************************************************************************************/
/** Size of a single set of histogram data (there are multiple of those in the hardware) */
#define ISP_METERING_HISTOGRAM_BINS (1024)
#define HISTOGRAM_BUFFER_WRODS (524)
#define HISTOGRAM_BUFFER_FRAME_COUNTER_OFFSET (522)
#define HISTOGRAM_BUFFER_SIZE_BYTES (2096)

/******************************************************************
* description:AWB statistics
* from isp_trm_p180,454 words(32bits), it is 1816 Bytes.
*
*   31           15          0
*   --------------------------
*0  |____________|___________|
*1  |____________|___________|
*2  |____________|___________|
*3  |____________|___________|
*   |____________|___________|
*   |____________|___________|
*   |____________|___________|
*   |            .
*   |            .
*   |            .
*   |________________________|
*   |________________________|
*   |______frame_counter_____|
*   |__________crc___________|
*   |___________meta_________|
*   |___________meta_________|
*   |___________meta_________|
*453|___________meta_________|
********************************************************************/
#define AWB_BUFFER_SIZE_BYTES (1816)
#define AWB_STATS_META_SIZE (4) /*words,meta data for statistics */
#define AWB_STATS_SIZE (450) /*words,225 records of 64 bits*/
#define AWB_BUFFER_SIZE_WORDS \
	(AWB_STATS_META_SIZE + AWB_STATS_SIZE) /* words, 454words, AWB_STATS_META_SIZE +
                                                                          AWB_STATS_SIZE */
#define AWB_BUFFER_FRAME_COUNTER_OFFSET 452 /*frame count, it seems that meta is off */



/*******************************************************************************************
* description:pixel_consistency
*
***********************************************************************************************/
/** Size of a single set of pixel_consistency data */
#define CONSISTENCY_SIZE_BYTES (2096u)


typedef enum enum_operation_mode_e { OPT_MODE_AUTO = 0, OPT_MODE_MANUAL = 1, OPT_MODE_BUTT } opt_mode_e;

typedef struct image_size_s {
	uint32_t width;
	uint32_t height;
} image_size_t;

/******************************************************************
 description:(1) (x,y) is the starting point.
             (2) width is the xoffset in the horizontal direction.
             (3) height is the yoffset in the vertical direction.
 example:
	(x,y)       width
	 ------------------------->
	 |
	 |
	 |
	 |height
	 |
	 |
	\|/
	 *
********************************************************************/
typedef struct image_rect_s {
	int32_t x;
	int32_t y;
	uint32_t width;
	uint32_t height;
} image_rect_t;

typedef struct crop_cfg_s {
	HB_BOOL enable;
	image_rect_t rect;
} crop_cfg_t;

typedef enum enum_hdr_mode_e {
	HDR_MODE_LINEAR = 0, /* linear mode */
	HDR_MODE_NATIVE, /* hdr mode composited by sensor */

	HDR_MODE_2To1_LINE,
	HDR_MODE_2To1_FRAME,

	HDR_MODE_3To1_LINE,
	HDR_MODE_3To1_FRAME,

	HDR_MODE_4To1_LINE,
	HDR_MODE_4To1_FRAME,

	HDR_MODE_BUTT,
} hdr_mode_e;

typedef enum enum_sched_mode_e {
	SCHED_MODE_TDMF = 0,
	SCHED_MODE_MANUAL = 1,
	SCHED_MODE_PASS_THRU = 2,

	SCHED_MODE_BUTT
} sched_mode_e;

typedef enum enum_isp_work_mode_e {
	ISP_WORK_MODE_NOMAL = 0,
	ISP_WORK_MODE_TPG = 1,
	ISP_WORK_MODE_CIM_TPG = 2,

	ISP_WORK_MODE_BUTT
} isp_work_mode_e;

typedef struct isp_channel_s {
	uint32_t hw_id;
	uint32_t slot_id;
	int32_t ctx_id; /* defined by vpf*/
} isp_channel_t;

typedef struct isp_bind_channel_s {
	uint32_t bind_hw_id;
	uint32_t bind_slot_id;
} isp_bind_channel_t;

typedef struct isp_attach_pipe_s {
	uint32_t hw_id;
	uint32_t slot_id;

	uint32_t ctx_id; /* defined by vpf*/
	uint32_t pipeline_id; /* defined by vpf*/
	uint32_t isp_pipe; /* reseverd, RW[0, 31], can be used by isp driver*/
} isp_attach_pipe_t;

typedef enum enum_isp_output_mode_e {
	ISP_OUTPUT_RAW_LEVEL_SENSOR_DATA = 0, /* the raw data after companded sensor data, it means the unprocessed raw
	                                            data from sensor */
	ISP_OUTPUT_RAW_LEVEL_FRAME_STITCH = 1, /* the raw data after frame stitch */
	ISP_OUTPUT_RAW_LEVEL_GAMMA_FE = 2, /* the raw data after post gamma fe companding curve*/
	ISP_OUTPUT_RAW_LEVEL_TONE_MAPPED = 3, /* the raw data after tone mapped*/
	ISP_OUTPUT_RAW_LEVEL_POST_GAMMA_FE_LUT = 4, /* the raw data after post gamma fe lockup table*/
	ISP_OUTPUT_RAW_LEVEL_POST_SHADING = 5, /* the raw data after post shading*/

	ISP_OUTPUT_RAW_LEVEL_BUTT
} isp_output_raw_level_e;

typedef struct isp_sw_ctrl_s {
	uint32_t ae_stat_buf_en;
	uint32_t awb_stat_buf_en;
	uint32_t ae5bin_stat_buf_en;
	uint32_t ctx_buf_en;
	uint32_t pixel_consistency_en;
} isp_sw_ctrl_t;

typedef enum enum_isp_channel_mode_e {
	ISP_CHANNEL_MODE_NORMAL = 0,
	ISP_CHANNEL_MODE_MASTER = 1,
	ISP_CHANNEL_MODE_SLAVE = 2,

	ISP_CHANNEL_MODE_BUTT
} isp_channel_mode_e;

typedef struct isp_combine_s {
	isp_channel_mode_e isp_channel_mode; /* RW: 0: normal no need combine the different isp channels
                                                    1: master channel when needing combine isp slave channel
                                                    2: slave channel when needing combine isp master channel*/
	isp_bind_channel_t bind_channel; /* RW: if isp_channel_mode = 0, the bind_channel invaild, no need care
                                           if isp_channel_mode = master, the bind_channel is that the slave channel
                                           if isp_channel_mode = slave, the bind_channel is that the master channel*/
} isp_combine_t;

typedef struct isp_attr_s {
	isp_channel_t channel;
	sched_mode_e sched_mode;
	isp_work_mode_e work_mode; /* RW: isp work mode*/
	hdr_mode_e hdr_mode; /* RW; HDR mode select,include hdr mode or linear mode*/
	image_size_t size; /* RW; Range: width:(0, 4096].height(0, 2560];
                                                    Width and height of the image input from the sensor*/
	uint32_t frame_rate; /* RW; Range: (0, 120] U32.0; For frame rate */
	isp_combine_t isp_combine; /* RW; image adjustment method fusion for one camera src+roi or
                                                    double cameras in different isp channels*/
	isp_sw_ctrl_t isp_sw_ctrl;
	uint32_t algo_state;
	uint32_t clear_record;
} isp_attr_t;

/**
 * @struct tag_isp_module_ctrl_reg1_u
 * @brief Define the descriptor of isp mod ctr reg1 struct value.
 * @NO{S08E06C02}
 */
typedef union tag_isp_module_ctrl_u {
	uint32_t u32Key;
	struct {
		uint32_t bitRsv0 : 2; /* RW;[0-1] */
		uint32_t bitBypassInputFormatter : 1; /* RW;[2] */
		uint32_t bitBypassChannelSwitch : 1; /* RW;[3] */
		uint32_t bitBypassVideoTest : 1; /* RW;[4] */
		uint32_t bitBypassRawFrontend : 1; /* RW;[5] */
		uint32_t bitBypassDefectPixel : 1; /* RW;[6] */
		uint32_t bitRsv1 : 1; /* RW;[7] */
		uint32_t bitBypassGammaFe : 1; /* RW;[8] */
		uint32_t bitBypassGammaFeSq : 1; /* RW;[9] */
		uint32_t bitBypassDigitalGain : 1; /* RW;[10] */
		uint32_t bitBypassFsChannelSwitch : 1; /* RW;[11] */
		uint32_t bitBypassSinter : 1; /* RW;[12] */
		uint32_t bitBypassGammaBe : 1; /* RW;[13] */
		uint32_t bitBypassGammaBeSq : 1; /* RW;[14] */
		uint32_t bitBypassWhiteBlance : 1; /* RW;[15] */
		uint32_t bitBypassRadialShading : 1; /* RW;[16] */
		uint32_t bitBypassMeshShading : 1; /* RW;[17] */
		uint32_t bitBypassIridix : 1; /* RW;[18] */
		uint32_t bitBypassDemosaic : 1; /* RW;[19] */
		uint32_t bitBypassOutFormat : 1; /* RW;[20] */
		uint32_t bitBypassDigitalGainIridix : 1; /* RW;[21] */
		uint32_t bitBypassPositionDigitalGain : 1; /* RW;[22] */
		uint32_t bitRsv2: 1; /* RW;[23] */
		uint32_t bitBypassCrop : 1; /* RW;[24] */
		uint32_t bitRsv3 : 1; /* RW;[25] */
		uint32_t bitBypassCNR : 1; /* RW;[26] */
		uint32_t bitRsv4 : 2; /* RW;[27-28] */
		uint32_t bitBypassCaCorrection : 1; /* RW;[29] */
		uint32_t bitRsv5 : 1; /* RW;[30] */
		uint32_t bitBypassSensorLinear : 1; /* RW;[31] */
	};
} isp_module_ctrl_reg1_u;

/**
 * @struct tag_isp_module_ctrl_reg2_u
 * @brief Define the descriptor of isp mod ctr reg2 struct value.
 * @NO{S08E06C02}
 */
typedef union tag_isp_module_ctrl_reg2_u { /*PRQA S ALL*/
	uint32_t u32Key;
	struct {
		uint32_t bitBypassPFCorrection : 1; /* RW;[0] */
		uint32_t bitBypassColorMatrix : 1; /* RW;[1] */
		uint32_t bitBypassGammaRGBFwdSq : 1; /* RW;[2] */
		uint32_t bitBypassGammaRGBRevSq : 1; /* RW;[3] */
		uint32_t bitBypassCropRCCB : 1; /* RW;[4] */
		uint32_t bitBypassCropPC : 1; /* RW;[5] */
		uint32_t bitRsv0 : 26; /* RW;[6-31] */
	};
} isp_module_ctrl_reg2_u;

/**
 * @struct tag_isp_module_ctrl_u
 * @brief Define the descriptor of isp mod ctr struct value.
 * @NO{S08E06C02}
 */
typedef struct tag_isp_module_ctrl_s { /*PRQA S ALL*/
	isp_module_ctrl_reg1_u isp_module_ctrl_reg1;
	isp_module_ctrl_reg2_u isp_module_ctrl_reg2;
} isp_module_ctrl_u;

/*note: in isp sw, ae meter by Global 1024-bin histogram, ae meter used chanel 1.( Global 1024-bin histogram:1~4).*/
typedef enum enum_isp_ae_stats_level_e {
	ISP_AE_STATS_LEVEL_AFTER_WDR_GAIN = 0,
	ISP_AE_STATS_LEVEL_AFTER_FRAME_STITCH = 1,
	ISP_AE_STATS_LEVEL_AFTER_GAMMA_FE = 2,
	ISP_AE_STATS_LEVEL_AFTER_AFTER_SHADING = 3,

	ISP_AE_STATS_LEVEL_BUTT
} isp_ae_stats_level_e;

/**
 * @enum enum_isp_algo_type_e
 * @brief Define the descriptor of isp algo type
 * @NO{S08E06C02}
 */
typedef enum enum_isp_algo_type_e { ISP_ALGO_AE = 0, ISP_ALGO_AWB = 1, ISP_ALGO_TYPE_BUTT } isp_algo_type_e;

typedef enum enum_isp_awb_stats_level_e {
	ISP_AWB_STATS_LEVEL_BEFOR_CCM = 0,
	ISP_AWB_STATS_LEVEL_AFTER_CCM = 1,

	ISP_AWB_STATS_LEVEL_BUTT
} isp_awb_stats_level_e;

typedef struct isp_module_level_s {
	isp_ae_stats_level_e ae_stats_level; /* RW*/
	isp_awb_stats_level_e awb_stats_level; /* RW*/
} isp_module_level_t;

/**
 * @NO{S08E06C02}
 * @struct isp_algo_info_s
 * @brief Define the descriptor of isp algo struct value.
 */
typedef struct isp_algo_info_s {
	isp_algo_type_e algo_type;
	opt_mode_e opt_mode;
} isp_aglo_info_t;

typedef struct isp_stat_info_s {
	uint32_t buf_idx;
	uint64_t phy_addr;
	void *virt_addr;
	uint64_t timestamp;
	uint32_t frame_id;
} isp_stat_info_t;

/**
 * @struct isp_statistics_s
 * @brief Define the descriptor of isp statistics data
 * @NO{S08E06C02}
 */
typedef struct isp_statistics_s {
	HB_BOOL crc_en; /*RW;api internal crc check enable or disable switch*/

	void *data; /*RO;Pointers to statistics*/
	uint32_t len; /*RO;Length of statistical data, in bytes*/
	uint32_t frame_id; /*RO;The frame_id corresponding to the statistics*/
	uint64_t timestamp; /*RO;Timestamp of statistics*/
	uint32_t buf_idx; /*RO;Only used for release interface, release the corresponding buffer*/
} isp_statistics_t;

typedef struct isp_ae_time_statistics_s {
	isp_stat_info_t stat_info;
	int32_t time_out;
	int32_t ion_share_id;
} isp_ae_time_statistics_t;

typedef struct isp_ae5bin_time_statistics_s {
	isp_stat_info_t stat_info;
	int32_t time_out;
	int32_t ion_share_id;
} isp_ae5bin_time_statistics_t;

typedef struct isp_awb_time_statistics_s {
	isp_stat_info_t stat_info;
	int32_t time_out;
	int32_t ion_share_id;
} isp_awb_time_statistics_t;

typedef struct isp_pixel_consistency_time_s {
	isp_stat_info_t stat_info;
	int32_t time_out;
	int32_t ion_share_id;
} isp_pixel_consistency_time_t;


typedef enum enum_isp_log_level_e {
	ISP_LOG_LEVEL_DEBUG = 0,
	ISP_LOG_LEVEL_INFO,
	ISP_LOG_LEVEL_NOTICE,
	ISP_LOG_LEVEL_WARNING,
	ISP_LOG_LEVEL_ERROR,
	ISP_LOG_LEVEL_CRIT,
	ISP_LOG_LEVEL_ALERT,
	ISP_LOG_LEVEL_EMERG,
	ISP_LOG_LEVEL_NOTHING,

	ISP_LOG_LEVEL_BUTT
} isp_log_level_e;

typedef struct isp_plane_info_s {
	uint64_t phy_addr;
	void *virt_addr;
	uint32_t offset;
	int32_t ion_share_id;
} isp_plane_info_t;

typedef struct isp_reg_s {
	uint32_t addr; /* RW, Physical address.*/
	uint32_t value; /* RW*/
} isp_reg_t;

typedef enum tag_isp_axi_output_mode_e {
	AXI_OUTPUT_MODE_DISABLE = 0,
	AXI_OUTPUT_MODE_RGB888 = 1,
	AXI_OUTPUT_MODE_RAW8 = 2,
	AXI_OUTPUT_MODE_RAW10 = 3,
	AXI_OUTPUT_MODE_RAW12 = 4,
	AXI_OUTPUT_MODE_RAW16 = 5,
	AXI_OUTPUT_MODE_RAW24 = 6,
	AXI_OUTPUT_MODE_YUV444 = 7,
	AXI_OUTPUT_MODE_YUV422 = 8, /* yuv422 */
	AXI_OUTPUT_MODE_YUV420 = 9, /* yuv420 */
	AXI_OUTPUT_MODE_IR8 = 10,
	AXI_OUTPUT_MODE_YUV420_RAW12 = 11, /* yuv420 & raw12 */
	AXI_OUTPUT_MODE_YUV422_RAW12 = 12, /* yuv422 & raw12 */
	AXI_OUTPUT_MODE_YUV420_RAW16 = 13, /* yuv420 & raw16 */
	AXI_OUTPUT_MODE_YUV422_RAW16 = 14, /* yuv422 & raw16 */

	AXI_OUTPUT_MODE_BUTT
} isp_axi_output_mode_e;

typedef enum tag_isp_stream_output_mode_e {
	STREAM_OUTPUT_MODE_DISABLE = 0, /* disable stream output */
	STREAM_OUTPUT_MODE_ENABLE = 1, /* enable stream output */
	STREAM_OUTPUT_MODE_BUTT
} isp_stream_output_mode_e;

/******************************************************************************************************************
note:
(1) If stream_output_mode is set to STREAM_OUTPUT_MODE_ENABLE,
axi_output_mode cannot be set to AXI_OUTPUT_MODE_YUV420, otherwise the return parameter is invalid,
But the RAW output of axi_output_mode is unaffected.
(2) AXI_output_mode is not affected if stream_output_mode_disable STREAM_OUTPUT_MODE_DISABLE is
    set by stream_output_mode.
******************************************************************************************************************/

typedef struct isp_ochn_attr_s {
	isp_stream_output_mode_e stream_output_mode; /* RW, STREAM_OUTPUT_MODE_DISABLE can be used to disable.*/
	isp_axi_output_mode_e axi_output_mode; /* RW, AXI_OUTPUT_MODE_DISABLE can be used to disable.*/

	crop_cfg_t output_crop_cfg; /* RW; Range: crop window <= input_crop_cfg.rect;
                                                    position of the cropping window, image width, and image height */

	isp_output_raw_level_e output_raw_level;
	uint32_t out_buf_noinvalid;
	uint32_t out_buf_noncached;
	uint32_t buf_num;
} isp_ochn_attr_t;

typedef struct isp_ichn_attr_s {
	crop_cfg_t input_crop_cfg; /* RW; Range: crop window <= size;
                                                    Only support input0 ~ input3, Start position of the cropping window,
                                                    image width, and image height */

	uint32_t in_buf_noclean;
	uint32_t in_buf_noncached;
} isp_ichn_attr_t;

typedef struct isp_timeval_s {
	uint64_t tv_sec;
	uint64_t tv_usec;
} isp_timeval_t;

typedef struct isp_frame_info_s {
	isp_axi_output_mode_e pixel_format; /* RO, pixel fomat, for example AXI_OUTPUT_MODE_YUV422(yuv422),
											AXI_OUTPUT_MODE_YUV420(yuv420) AXI_OUTPUT_MODE_RAW8/10/12/16/24 and so on.*/
	uint32_t num_planes; /* RO, number of planes, the max value is 4.*/
	isp_plane_info_t plane_info[ISP_AXI_OUTPUT_MAX_PLANES]; /* RO*/
	image_size_t size; /* RO, (width,height)*/
	uint32_t stride; /* RO*/
	uint32_t frame_count; /* RO*/
	isp_timeval_t tv; /* RO*/
	uint32_t index; /* RO*/
	uint32_t pipeline_id; /* RO*/
	uint64_t desc;
	uint64_t timestamps; /*RO;Timestamp of statistics*/
	uint32_t buf_nocached; /* RO*/
} isp_frame_info_t;

typedef struct isp_frame_info_time_t {
	isp_frame_info_t frame_info;
	int32_t time_out;
} isp_frame_info_time_t;

/**
 * @enum enum_isp_cmd_type_e
 * @brief Define the descriptor of isp cmd type enum
 * @NO{S08E06C02}
 */
typedef enum enum_isp_cmd_type_e {
	ISP_CMD_TYPE_TSELFTEST = 0,
	ISP_CMD_TYPE_TGENERAL = 1,
	ISP_CMD_TYPE_TSENSOR = 2,
	ISP_CMD_TYPE_TSYSTEM = 3,

	ISP_CMD_TYPE_TIMAGE = 4,
	ISP_CMD_TYPE_TALGORITHMS = 5,
	ISP_CMD_TYPE_TREGISTERS = 6,
	ISP_CMD_TYPE_TSTATUS = 7,
	ISP_CMD_TYPE_TISP_MODULES = 8,

	ISP_CMD_TYPE_BUTT
} isp_cmd_type_e;

/**
 * @enum enum_isp_cmd_e
 * @brief Define the descriptor of isp cmd enum
 * @NO{S08E06C02}
 */
typedef enum enum_isp_cmd_e {
	ISP_CMD_FW_REVISION = 0x00000000,
	ISP_CMD_CONTEXT_NUMBER = 0x00000001,
	ISP_CMD_ACTIVE_CONTEXT = 0x00000002,
	ISP_CMD_SENSOR_SUPPORTED_PRESETS = 0x00000003,
	ISP_CMD_SENSOR_PRESET = 0x00000004,
	ISP_CMD_SENSOR_WDR_MODE = 0x00000005,
	ISP_CMD_SENSOR_STREAMING = 0x00000006,
	ISP_CMD_SENSOR_LOCKED_EXPOSURE_RATIO = 0x00000007,
	ISP_CMD_SENSOR_EXPOSURES = 0x00000008,
	ISP_CMD_SENSOR_FPS = 0x00000009,
	ISP_CMD_SENSOR_WIDTH = 0x0000000A,
	ISP_CMD_SENSOR_HEIGHT = 0x0000000B,
	ISP_CMD_SENSOR_INFO_PRESET = 0x0000000C,
	ISP_CMD_SENSOR_INFO_WDR_MODE = 0x0000000D,
	ISP_CMD_SENSOR_INFO_FPS = 0x0000000E,
	ISP_CMD_SENSOR_INFO_WIDTH = 0x0000000F,
	ISP_CMD_SENSOR_INFO_HEIGHT = 0x00000010,
	ISP_CMD_SENSOR_INFO_EXPOSURES = 0x00000011,
	ISP_CMD_SENSOR_INFO_CHANNELS = 0x00000012,
	ISP_CMD_SENSOR_INFO_DATA_WIDTH = 0x00000013,
	ISP_CMD_SENSOR_INTEGRATION_TIME_MIN = 0x00000014,
	ISP_CMD_SENSOR_INTEGRATION_TIME_LIMIT = 0x00000015,
	ISP_CMD_SYSTEM_LOGGER_LEVEL = 0x00000016,
	ISP_CMD_SYSTEM_LOGGER_MASK = 0x00000017,
	ISP_CMD_MCFE_USECASE = 0x00000018,
	ISP_CMD_CONTEXT_STATE = 0x00000019,
	ISP_CMD_CMD_INTERFACE_MODE = 0x0000001A,
	ISP_CMD_V4L2_INTERFACE_MODE = 0x0000001B,
	ISP_CMD_M2M_PROCESS_REQUEST = 0x0000001C,
	ISP_CMD_BUFFER_DATA_TYPE = 0x0000001D,
	ISP_CMD_TEST_PATTERN_ENABLE_ID = 0x0000001E,
	ISP_CMD_TEST_PATTERN_MODE_ID = 0x0000001F,
	ISP_CMD_SYSTEM_FREEZE_FIRMWARE = 0x00000020,
	ISP_CMD_SYSTEM_MANUAL_EXPOSURE = 0x00000021,
	ISP_CMD_SYSTEM_MANUAL_MAX_INTEGRATION_TIME = 0x00000022,
	ISP_CMD_SYSTEM_MANUAL_EXPOSURE_RATIO = 0x00000023,
	ISP_CMD_SYSTEM_MANUAL_INTEGRATION_TIME = 0x00000024,
	ISP_CMD_SYSTEM_MANUAL_SENSOR_ANALOG_GAIN = 0x00000025,
	ISP_CMD_SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN = 0x00000026,
	ISP_CMD_SYSTEM_MANUAL_ISP_DIGITAL_GAIN = 0x00000027,
	ISP_CMD_SYSTEM_MANUAL_IRIDIX_DIGITAL_GAIN = 0x00000028,
	ISP_CMD_SYSTEM_MANUAL_DIRECTIONAL_SHARPENING = 0x00000029,
	ISP_CMD_SYSTEM_MANUAL_UN_DIRECTIONAL_SHARPENING = 0x0000002A,
	ISP_CMD_SYSTEM_MANUAL_AWB = 0x0000002B,
	ISP_CMD_SYSTEM_AUTO_LEVEL_ENABLE = 0x0000002C,
	ISP_CMD_SYSTEM_ANTIFLICKER_ENABLE = 0x0000002D,
	ISP_CMD_SYSTEM_MANUAL_SATURATION = 0x0000002E,
	ISP_CMD_SYSTEM_EXPOSURE = 0x0000002F,
	ISP_CMD_SYSTEM_INTEGRATION_TIME_PRECISION = 0x00000030,
	ISP_CMD_SYSTEM_EXPOSURE_RATIO = 0x00000031,
	ISP_CMD_SYSTEM_MAX_EXPOSURE_RATIO = 0x00000032,
	ISP_CMD_SYSTEM_INTEGRATION_TIME = 0x00000033,
	ISP_CMD_SYSTEM_LONG_INTEGRATION_TIME = 0x00000034,
	ISP_CMD_SYSTEM_MIDDLE2_INTEGRATION_TIME = 0x00000035,
	ISP_CMD_SYSTEM_MIDDLE_INTEGRATION_TIME = 0x00000036,
	ISP_CMD_SYSTEM_SHORT_INTEGRATION_TIME = 0x00000037,
	ISP_CMD_SYSTEM_MAX_INTEGRATION_TIME = 0x00000038,
	ISP_CMD_SYSTEM_SENSOR_EXPOSURE_RATIO = 0x00000039,
	ISP_CMD_SYSTEM_SENSOR_ANALOG_GAIN = 0x0000003A,
	ISP_CMD_SYSTEM_MAX_SENSOR_ANALOG_GAIN = 0x0000003B,
	ISP_CMD_SYSTEM_SENSOR_DIGITAL_GAIN = 0x0000003C,
	ISP_CMD_SYSTEM_MAX_SENSOR_DIGITAL_GAIN = 0x0000003D,
	ISP_CMD_SYSTEM_ISP_DIGITAL_GAIN = 0x0000003E,
	ISP_CMD_SYSTEM_MAX_ISP_DIGITAL_GAIN = 0x0000003F,
	ISP_CMD_SYSTEM_DIRECTIONAL_SHARPENING_TARGET = 0x00000040,
	ISP_CMD_SYSTEM_UN_DIRECTIONAL_SHARPENING_TARGET = 0x00000041,
	ISP_CMD_SYSTEM_IRIDIX_STRENGTH_TARGET = 0x00000042,
	ISP_CMD_SYSTEM_MAXIMUM_IRIDIX_STRENGTH = 0x00000043,
	ISP_CMD_SYSTEM_MINIMUM_IRIDIX_STRENGTH = 0x00000044,
	ISP_CMD_SYSTEM_IRIDIX_DIGITAL_GAIN = 0x00000045,
	ISP_CMD_SYSTEM_SINTER_THRESHOLD_TARGET = 0x00000046,
	ISP_CMD_SYSTEM_AWB_RED_GAIN = 0x00000047,
	ISP_CMD_SYSTEM_AWB_BLUE_GAIN = 0x00000048,
	ISP_CMD_SYSTEM_AWB_CCT = 0x00000049,
	ISP_CMD_SYSTEM_SATURATION_TARGET = 0x0000004A,
	ISP_CMD_SYSTEM_ANTI_FLICKER_FREQUENCY = 0x0000004B,
	ISP_CMD_IMAGE_RAW_SCALER_ENABLE_ID = 0x0000004C,
	ISP_CMD_IMAGE_RAW_SCALER_WIDTH_ID = 0x0000004D,
	ISP_CMD_IMAGE_RAW_SCALER_HEIGHT_ID = 0x0000004E,
	ISP_CMD_IMAGE_RGB_SCALER_ENABLE_ID = 0x0000004F,
	ISP_CMD_IMAGE_RGB_SCALER_WIDTH_ID = 0x00000050,
	ISP_CMD_IMAGE_RGB_SCALER_HEIGHT_ID = 0x00000051,
	ISP_CMD_IMAGE_CROP_ENABLE_ID = 0x00000052,
	ISP_CMD_IMAGE_CROP_WIDTH_ID = 0x00000053,
	ISP_CMD_IMAGE_CROP_HEIGHT_ID = 0x00000054,
	ISP_CMD_IMAGE_CROP_XOFFSET_ID = 0x00000055,
	ISP_CMD_IMAGE_CROP_YOFFSET_ID = 0x00000056,
	ISP_CMD_OUTPUT_AXI1_FORMAT_ID = 0x00000057,
	ISP_CMD_OUTPUT_AXI2_FORMAT_ID = 0x00000058,
	ISP_CMD_OUTPUT_AXI3_FORMAT_ID = 0x00000059,
	ISP_CMD_OUTPUT_FORMAT_MANUAL_AXI_CFG_APPLY_ID = 0x0000005A,
	ISP_CMD_OUTPUT_AXI_MODE_ID = 0x0000005B,
	ISP_CMD_OUTPUT_STREAMING1_FORMAT_ID = 0x0000005C,
	ISP_CMD_OUTPUT_STREAMING2_FORMAT_ID = 0x0000005D,
	ISP_CMD_OUTPUT_STREAMING3_FORMAT_ID = 0x0000005E,
	ISP_CMD_OUTPUT_FORMAT_MANUAL_STREAMING_CFG_APPLY_ID = 0x0000005F,
	ISP_CMD_OUTPUT_STREAMING_MODE_ID = 0x00000060,
	ISP_CMD_REGISTERS_ADDRESS_ID = 0x00000061,
	ISP_CMD_REGISTERS_SIZE_ID = 0x00000062,
	ISP_CMD_REGISTERS_SOURCE_ID = 0x00000063,
	ISP_CMD_REGISTERS_VALUE_ID = 0x00000064,
	ISP_CMD_STATUS_INFO_EXPOSURE_LOG2_ID = 0x00000065,
	ISP_CMD_STATUS_INFO_LDR_GAIN_LOG2_ID = 0x00000066,
	ISP_CMD_STATUS_INFO_IRIDIX_CONTRAST = 0x00000067,
	ISP_CMD_STATUS_INFO_AE_HIST_MEAN = 0x00000068,
	ISP_CMD_STATUS_INFO_GAIN_ONES_ID = 0x00000069,
	ISP_CMD_STATUS_INFO_GAIN_LOG2_ID = 0x0000006A,
	ISP_CMD_STATUS_INFO_AWB_MIX_LIGHT_CONTRAST = 0x0000006B,
	ISP_CMD_ISP_MODULES_MANUAL_IRIDIX = 0x0000006C,
	ISP_CMD_ISP_MODULES_MANUAL_SINTER = 0x0000006D,
	ISP_CMD_ISP_MODULES_MANUAL_FRAME_STITCH = 0x0000006E,
	ISP_CMD_ISP_MODULES_MANUAL_RAW_FRONTEND = 0x0000006F,
	ISP_CMD_ISP_MODULES_MANUAL_BLACK_LEVEL = 0x00000070,
	ISP_CMD_ISP_MODULES_MANUAL_SHADING = 0x00000071,
	ISP_CMD_ISP_MODULES_MANUAL_DEMOSAIC = 0x00000072,
	ISP_CMD_MODULES_MANUAL_CNR = 0x00000073,
	ISP_CMD_MODULES_FORCE_BIST_MISMATCH = 0x00000074,
	ISP_CMD_ACTIVE_HARDWARE = 0x00000075,
	ISP_CMD_MSENSOR_MAX_AGAIN = 0x00000076,
	ISP_CMD_MSENSOR_MAX_DGAIN = 0x00000077,
	ISP_CMD_MSENSOR_MIN_INTERTIME = 0x00000078,
	ISP_CMD_MSENSOR_MAX_INTERTIME = 0x00000079,
	ISP_CMD_MSENSOR_MAX_LONGTIME = 0x0000007A,
	ISP_CMD_MSENSOR_LIMIT_INTERTIME = 0x0000007B,
	ISP_CMD_MSENSOR_LINES_PER_SECOND = 0x0000007C,
	ISP_CMD_AE_EXPOSURE_ID = 0x0000007D,
	ISP_CMD_SYSTEM_LUX_ID = 0x0000007E,
	ISP_CMD_SYSTEM_MIN_INTEGRATION_TIME = 0x0000007F,
	ISP_CMD_SYSTEM_AWB_RED_GAIN_ACTUAL = 0x00000080,
	ISP_CMD_SYSTEM_AWB_BLUE_GAIN_ACTUAL = 0x00000081,
	ISP_CMD_SYSTEM_MIN_SENSOR_ANALOG_GAIN_PARAM = 0x00000082,
	ISP_CMD_SYSTEM_MIN_SENSOR_DIGITAL_GAIN_PARAM = 0x00000083,
	ISP_CMD_CLEAR_RECORD = 0x00000084,
	ISP_CMD_CONTEXT_MASK = 0x00000085,
	ISP_CMD_OSD_ACTIVE = 0x00000086,
	ISP_CMD_STATUS_INFO_AE_HIST_MEDIAN = 0x00000087,
	ISP_CMD_STATUS_INFO_AE_HYSTERESIS_WEIGHT = 0x00000088,

	ISP_CMD_BUTT
} isp_cmd_e;

/**
 * @enum enum_isp_cmd_dir_e
 * @brief Define the descriptor of isp cmd dir get/set
 * @NO{S08E06C02}
 */
typedef enum enum_isp_cmd_dir_e {
	ISP_CMD_DIR_SET = 0,
	ISP_CMD_DIR_GET = 1,

	ISP_CMD_DIR_BUTT
} isp_cmd_dir_e;

/**
 * @struct isp_cmd_api_s
 * @brief Define the descriptor of isp cmd api value
 * @NO{S08E06C02}
 */
typedef struct isp_cmd_api_s {
	isp_cmd_type_e cmd_type; /* RW cmd_type */
	isp_cmd_e cmd; /* RW cmd */
	uint32_t set_value; /* RW,set_value Range [0, 0xffffffff];*/
	isp_cmd_dir_e dir; /* RW dir */
	uint32_t ret_value; /* RW, ret_value Range [0, 0xffffffff];*/
} isp_cmd_api_t;

typedef enum enum_isp_calib_lut_type_e {
	ISP_LUT_CHAR = 1,
	ISP_LUT_SHORT = 2,
	ISP_LUT_INT = 4,
} isp_calib_lut_type_e;

typedef struct isp_calib_lut_s {
	uint32_t id; /* mode should low than CALIBRATION_TOTAL_SIZE */
	isp_cmd_dir_e dir; /* RW */
	isp_calib_lut_type_e width; /* calibration lut data type, char/short/int */
	uint32_t size; /* size = rows * cols */
	void *ptr; /* max needed bytes by the user malloc */
	uint32_t len; /* get the len of lut info */
} isp_calib_lut_t;

typedef struct isp_reg_mask_s {
	uint32_t addr;
	uint8_t s;
	uint8_t e;
	uint32_t value;
} isp_reg_mask_t;

typedef struct isp_lut_reg_s {
	void *ptr;
	isp_cmd_dir_e dir;
	uint32_t elem;
} isp_lut_reg_t;

/**
 * @struct isp_context_s
 * @brief Define the descriptor of isp context value
 * @NO{S08E06C02}
 */
typedef struct isp_context_s {
	uint32_t frame_id; /* frame id */
	uint64_t timestamp; /* timestamp */
	uint16_t crc16; /* crc16 value */
	void *ptr; /* max needed 128KB(LEN_ADDR_ISP) bytes by the user malloc */
	uint32_t len; /* get the len of registers bytes in fact */
} isp_context_t;

/**
 * @struct isp_context_info_s
 * @brief Define the descriptor of isp context with buffer data
 * @NO{S08E06C02}
 */
typedef struct isp_context_info_s {
	isp_context_t isp_context; /* isp_context value */
	uint64_t isp_base; /* isp_base address */
	int32_t ion_share_id; /* ion share id */
	uint32_t offset; /* size offset */
} isp_context_info_t;

typedef struct isp_linear_int_time_s {
	uint32_t integration_time;
} isp_linear_int_time_t;

typedef struct isp_hdr_int_time_s {
	uint32_t l_integration_time;
	uint32_t m_integration_time;
	uint32_t s_integration_time;
} isp_hdr_int_time_t;

typedef struct isp_iris_s {
	uint32_t reserved;
} isp_iris_t;

typedef struct isp_manual_exposure_s {
	hdr_mode_e hdr_mode; /* RO*/
	isp_linear_int_time_t linear_int_time; /* RO, the integration time, only active in linear mode */
	isp_hdr_int_time_t hdr_int_time; /* RO, the integration time, only active in hdr mode */
	uint32_t sensor_again; /* RO*/
	uint32_t sensor_dgain; /* RO*/
	uint32_t isp_dgain; /* RO*/
	isp_iris_t iris; /* RO, no used.*/
} isp_manual_exposure_t;

typedef union { /*PRQA S ALL*/
	struct {
		uint32_t roi_y2 : 8; /* [7..0]  */
		uint32_t roi_x2 : 8; /* [15..8]  */
		uint32_t roi_y1 : 8; /* [23..16]  */
		uint32_t roi_x1 : 8; /* [31..24]  */
	} bits;

	uint32_t roi;
} isp_roi_u;

typedef struct isp_ae_statistics_attr_s {
	isp_roi_u ae_roi; /* RW, Range (x1,y1) =([0, 255]. [0,255]), (x2,y2) =([0, 255]. [0,255])
	                      Select which zones are used to gather AE statistics. The region of interest is defined as a
	                      rectangle with top-left coordinates (AE_ROI_X1, AE_ROI_Y1) and bottom-right
	                      coordinates (AE_ROI_X2, AE_ROI_Y2), with (0,0) defined as the top-left of the image and
	                      (255,255) as the bottom right of the image*/

	int8_t ae_compensation; /* RW, Range [0, 0xff] s8.0;
	                                value of 128 is no compensation. Values below 128 are negative and values
	                                above 128 are positive. A step of 4 corresponds to a 0.5 dB gain */
} isp_ae_statistics_attr_t;

typedef struct isp_exposure_info_s {
	uint32_t log2_exposure_value; /*RO, Range [0,0xffffffff];the current exposure value in log2 s16.16 format*/
} isp_exposure_info_t;

typedef struct isp_awb_statistics_attr_s {
	isp_roi_u awb_roi; /* RW, Range (x1,y1) =([0, 255]. [0,255]), (x2,y2) =([0, 255]. [0,255])
	                      Select which zones are used to gather AWB statistics. The region of interest is defined as a
	                      rectangle with top-left coordinates (AWB_ROI_X1, AWB_ROI_Y1) and bottom-right
	                      coordinates (AWB_ROI_X2, AWB_ROI_Y2), with (0,0) defined as the top-left of the image
	                      and (255,255) as the bottom right of the image.*/
} isp_awb_statistics_attr_t;

/******************************************************************
*again,dgain,ispgain range is [0,255]
*ae_exposure  RW, Range [0, OxFFFF,FFFF]
*sys_exposure RW, Range [0, 0x7FFF,FFFF]
*cur_lux, statue_exp_log is read only
*******************************************************************/
/**
 * @struct ae_info_s
 * @brief Define the descriptor of isp ae info data
 * @NO{S08E06C02}
 */
typedef struct ae_info_s {
	uint32_t ae_exposure; /* ae_exposure value range:[[0, OxFFFF]; default: FFFF */
	uint32_t again; /* again value range:[0,255]; default: 0 */
	uint32_t dgain; /* dgain value* range:[0,255]; default: 0 */
	uint32_t ispgain; /* ispgain value range:[0,255]; default: 0 */
	uint32_t sys_exposure; /* sys_exposure value * range:[[0, OxFFFF]; default: FFFF */
	uint32_t status_info_exp_log2; /* status_info_exp_log2 value */
	uint32_t cur_lux; /* cur_lux value */
} ae_info_t;

/**
 * @struct awb_info_s
 * @brief Define the descriptor of isp awb info data
 * @NO{S08E06C02}
 */
typedef struct awb_info_s {
	uint32_t rgain; /* RW, Range [0, 4095] */
	uint32_t bgain; /* RW, Range [0, 4095] */
	uint32_t cct; /* RW, Range [0, 4095] */
} awb_info_t;

/**
 * @struct isp_info_s
 * @brief Define the descriptor of isp info data
 * @NO{S08E06C02}
 */
typedef struct isp_info_s {
	uint32_t frame_id;
	uint64_t timestamp;
	ae_info_t ae_info;
	awb_info_t awb_info;
	isp_context_t isp_context;
	void *ae_ptr;
	void *ae_5bin_ptr;
	void *lumvar_ptr;
	void *awb_ptr;
	void *af_ptr;
} isp_info_t;

/**
 * @struct isp_info_time_s
 * @brief Define the descriptor of isp info and isp context data
 * @NO{S08E06C02}
 */
typedef struct isp_info_time_s {
	isp_info_t isp_info;
	isp_context_info_t isp_context_info;
	int32_t time_out;
} isp_info_time_t;

/**
 * @struct isp_ae5bin_stats_s
 * @brief Define the descriptor of isp ae 5bin stat info
 * @NO{S08E06C02}
 */
typedef struct isp_ae5bin_stats_s {
	uint32_t len;
	uint32_t frame_id;
	uint64_t timestamp;
	void *ae_5bin_ptr;
} isp_ae5bin_stats_t;

/**
 * @struct isp_zone_info_s
 * @brief Define the descriptor of isp zone info
 * @NO{S08E06C02}
 */
typedef struct isp_zone_info_s {
	uint8_t h;
	uint8_t v;
} isp_zone_info_t;

/**
 * @struct isp_hist_thresh_info_s
 * @brief Define the descriptor of isp hist threash info
 * @NO{S08E06C02}
 */
typedef struct isp_hist_thresh_info_s {
	uint16_t hist_01;
	uint16_t hist_12;
	uint16_t hist_34;
	uint16_t hist_45;
} isp_hist_thresh_info_t;

/**
 * @enum enum_isp_info_type_e
 * @brief Define the descriptor of isp info type
 * @NO{S08E06C02}
 */
typedef enum enum_isp_info_type_e {
	ISP_CTX = 0,
	ISP_AE,
	ISP_AWB,
	ISP_AF,
	ISP_AE_5BIN,
	ISP_LUMVAR,
	ISP_AE_INFO,
	ISP_AWB_INFO,
	ISP_TYPE_MAX
} isp_info_type_e;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // HB_COMM_ISP_H_
