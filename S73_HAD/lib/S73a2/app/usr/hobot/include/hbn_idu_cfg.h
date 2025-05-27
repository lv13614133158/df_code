/*
 * hbn_idu_cfg.h
 *
 * Copyright (C) 2020 horizon
 *
 *
 */

#ifndef __HBN_IDU_CFG_H__
#define __HBN_IDU_CFG_H__

#include "cJSON.h"

#define MAX_DISP_NUM (2U)
#define DISP_DEV_MASK (0x11U)
#define PALETTE_SIZE 		(256)
#define PORT_MAX 		(2)
#define NAME_MAX_LENGTH		(16)
#define PIN_CTRL_MAX_NUM	(8)
//coverity[misra_c_2012_rule_5_6_violation:SUPPRESS]
typedef float float32_t;
//coverity[misra_c_2012_rule_5_6_violation:SUPPRESS]
typedef double float64_t;

#define HB_DISP_INVALID_CHN_FMT (10004)
#define HB_DISP_OPEN_DEVICE_FAIL (10005)
#define HB_DISP_CLOSE_DEVICE_FAIL (10006)
#define HB_DISP_NOT_INIT (10000)
#define HB_DISP_INPUT_POINTER_NULL (10001)
#define HB_DISP_GET_OUT_CFG_FAIL (10007)
#define HB_DISP_SET_OUT_CFG_FAIL (10008)
#define HB_DISP_INVALID_PAR_RANGE (10002)
#define HB_DISP_INVALID_CHN_NO (10009)
#define HB_DISP_SET_GAMMA_CFG_FAIL (10010)
#define HB_DISP_SET_UPSCALE_CFG_FAIL (10011)
#define HB_DISP_SET_CHN_CFG_FAIL (10012)
#define HB_DISP_INVALID_DISP_ID (10003)
#define HB_DISP_ALREADY_INIT (10013)
#define HB_DISP_INIT_DEV_FAIL (10014)
#define HB_DISP_PARSER_CFG_FILE_FAIL (10015)
#define HB_DISP_GET_FRAME_SIZE_FAIL (10016)
#define HB_DISP_SET_TIMING_FAIL (10017)
#define HB_DISP_START_FAIL (10018)
#define HB_DISP_STOP_FAIL (10019)
#define HB_DISP_GET_STOP_CNT_FAIL (10020)
#define HB_DISP_GET_START_CNT_FAIL (10021)
#define HB_DISP_LAYER_ON_FAIL (10022)
#define HB_DISP_LAYER_OFF_FAIL (10023)
#define HB_DISP_GET_DISP_DONE_FAIL (10024)
#define HB_DISP_SET_DISP_ADDR_FAIL (10025)
#define HB_DISP_OPEN_CFG_FILE_FAIL (10026)
#define HB_DISP_GET_DEV_INFO_FAIL (10027)
#define HB_DISP_CHECK_DEV_MODE_FAIL (10028)
#define HB_DISP_SET_PIX_CLK_FAIL (10029)
#define HB_DISP_SET_IPI_CLK_FAIL (10030)
#define HB_DISP_INIT_LAYER_CFG_FAIL (10031)
#define HB_DISP_CHN_SIZE_LARGE_THAN_IMAGE_SIZE (10035)
#define HB_DISP_CHN_SIZE_SMALL_THAN_IMAGE_SIZE (10036)
#define HB_DISP_INVALID_BUF_VADDR (10037)
#define HB_DISP_SET_ONE_FRAME_TIME_FAIL (10038)
#define HB_DISP_DLOPEN_LIBRARY_FAIL		(10039)
#define HB_DISP_DEINIT_FAIL			(10040)
#define HB_DISP_GET_FRAME_FAIL (10041)
#define HB_DISP_PUT_FRAME_FAIL (10042)
#define HB_DISP_ONESHOT_TRIG_FAIL (10043)
#define HB_DISP_SUCCESS ((int32_t)0)
#define HB_DISP_FAILED ((int32_t)1)

typedef enum {
	IDU_ICHN1 = 0,
	IDU_ICHN2,
	IDU_ICHN3,
	IDU_ICHN4,
#ifdef CONFIG_HOBOT_CHIP_J6X
	IDU_ICHN5,
	IDU_ICHN6,
#endif
	IDU_ICHN_NUM,
} idu_input_channel_e;

typedef enum {
	OCHN_MIPI_CSI_DEV = 0,
	OCHN_MIPI_DSI,
	OCHN_WRITEBACK,
	OCHN_NUM,
} idu_output_type_e;

typedef enum interface_type_e {
	MIPI_DPHY,
	HDMI,
	OPEN_LDI,
	FPD_LINK,
} interface_type_e;

typedef enum board_type_e {
	NONE_BOARD,
	SERDES,
	DSI2HDMI,
	PANEL,
	DSI2IPI,
} board_type_e;

enum pin_ctrl_purpose_e {
	PIN_CTRL_FOR_INIT,
	PIN_CTRL_FOR_DEINIT,
	PIN_CTRL_PURP_MAX,
};

enum work_state_e {
	WORK_STATE_INIT = 1,
	WORK_STATE_DEINIT,
	WORK_STATE_START,
	WORK_STATE_STOP,
	WORK_STATE_ERROR,
	WORK_STATE_MAX,
};

enum color_coding_e {
	COLOR_CODE_16BIT_CONFIG1,
	COLOR_CODE_16BIT_CONFIG2,
	COLOR_CODE_16BIT_CONFIG3,
	COLOR_CODE_18BIT_CONFIG1,
	COLOR_CODE_18BIT_CONFIG2,
	COLOR_CODE_24BIT,
	COLOR_CODE_20BIT_YCC422_LOOSELY,
	COLOR_CODE_24BIT_YCC422,
	COLOR_CODE_16BIT_YCC422,
	COLOR_CODE_30BIT,
	COLOR_CODE_36BIT,
	COLOR_CODE_12BIT_YCC420,
	COLOR_CODE_DSC24,
	COLOR_CODE_MAX
};

enum cmd_type_e {
	DCS_CMD,
	GENERIC_CMD,
};

typedef enum {
	DISPLAY_EXT_GET_DONE_FLAG = 0x1000U,
	DISPLAY_EXT_GET_WAIT_VSYNC = 0x1001U,
	DISPLAY_EXT_GET_CAPTURE_CRC = 0x1002U,
} disp_ext_command_e;

typedef enum {
	DISPLAY_EXT_SET_ONESHOT_TRIG = 0x2000U,
	DISPLAY_EXT_SET_OUTPUT_CFG,
	DISPLAY_EXT_SET_OUTPUT_DYNAMIC_CFG,
	DISPLAY_EXT_SET_TIMING_CFG,
	DISPLAY_EXT_SET_GAMMA_CFG,
} disp_ext_set_command;

typedef struct type_ppcon1_cfg_s {
	uint32_t dithering_flag;
	uint32_t dithering_en;
	uint32_t gamma_en;
	uint32_t hue_en;
	uint32_t sat_en;
	uint32_t con_en;
	uint32_t bright_en;
	uint32_t theta_sign;
	uint32_t contrast;
} ppcon1_cfg_t;

typedef struct type_ppcon2_cfg_s {
	uint32_t theta_abs; //ppcon2
	uint32_t saturation;
	uint32_t off_contrast;
	uint32_t off_bright;
	float gamma_value;
} ppcon2_cfg_t;

typedef struct gamma_reg_bits_s {
	uint32_t part_a : 8;
	uint32_t part_b : 8;
	uint32_t part_c : 8;
	uint32_t part_d : 8;
} gamma_reg_bits_t;

typedef union gamma_para_s {
	uint32_t value;
	struct gamma_reg_bits_s bit;
} gama_para_t;

typedef struct disp_timing_s {
	uint32_t hbp;
	uint32_t hfp;
	uint32_t hs;
	uint32_t vbp;
	uint32_t vfp;
	uint32_t vs;
	uint32_t vfp_cnt;
	uint32_t pix_rate;
} disp_timing_t;

typedef struct csi_dev_channel_cfg_s {
	uint16_t enable;
	uint16_t lanes; //lanes mode
	uint16_t fps; //mode to fps
	uint32_t datatype; //format to csi dt
	uint32_t bpp; //format to bpp
	uint16_t mipiclk; //
	uint16_t width; //w
	uint16_t height; //h
	uint16_t linelenth; //htotal
	uint16_t framelenth; //vtotal
	uint16_t settle; //
	uint16_t vpg; //
	uint16_t ipi_lines; //vstart+1
	uint16_t channel_num; //ipi channel
	// uint8_t channel_sel[MIPI_CSI_DEV_CHANNEL_NUM]; // vc
	uint8_t lpclk_mode; //
	uint8_t vpg_mode; //
	uint8_t vpg_hsyncpkt_en; //
} csi_dev_channel_cfg_t;

typedef struct dsi_channel_cfg_s {
	uint16_t enable;
	uint16_t lanes;
	uint32_t mipiclk;     /* units: Mbps*/
	uint32_t pixel_clock; /* units: khz*/
	uint16_t eotp_rx_en;
	uint16_t eotp_tx_en;
	uint16_t cntmode;

	uint16_t channel;
	uint16_t cmd_channel;
	uint16_t color_coding;
	uint8_t hsync_low;    /* 1: configures the dpihsync pin as active low*/
	uint8_t vsync_low;    /* 1: configures the dpivsync pin as active low*/
	uint8_t dataen_low;   /* 1: configures the dpidataen pin as active low*/

	uint16_t video_mode;
	uint16_t vpg;
	uint16_t width;
	uint16_t height;
	uint32_t hbp;   /* pixels*/
	uint32_t hsa;   /* pixels*/
	uint32_t hline; /* pixels*/
	uint32_t vfp;   /* lines*/
	uint32_t vbp;   /* lines*/
	uint32_t vsa;   /* lines*/
} dsi_channel_cfg_t;

typedef struct writeback_channel_cfg_s {
	uint32_t enable;
	uint32_t point;
	uint32_t format;
	uint32_t external_buf;
	uint32_t paddr[3];
} writeback_channel_cfg_t;

typedef struct upscaling_cfg_s {
	uint32_t enable;
	uint32_t layer_no;
	uint32_t src_width;
	uint32_t src_height;
	uint32_t tgt_width;
	uint32_t tgt_height;
} upscaling_cfg_t;

typedef struct gamma_cfg_s {
	gama_para_t gamma_xr[4];
	gama_para_t gamma_xg[4];
	gama_para_t gamma_xb[4];
	gama_para_t gamma_yr[4];
	gama_para_t gamma_yg[4];
	gama_para_t gamma_yb[4];
	gama_para_t gamma_y16rgb;
} gamma_cfg_t;

typedef struct output_bg_color_s {
	uint32_t mode;
	uint32_t bgcolor;
} output_bg_color;

typedef struct output_dynamic_cfg_s {
	uint32_t      bgmode;
	uint32_t      bgcolor;
	uint32_t      bt601_709_sel;
	ppcon1_cfg_t  ppcon1;
	ppcon2_cfg_t  ppcon2;
	gamma_cfg_t   gamma_cfg;
} output_dynamic_cfg_t;

typedef struct output_cfg_s {
	uint32_t      enable;
	uint32_t      out_sel;
	uint32_t      width;
	uint32_t      height;
	uint32_t      bgmode;
	uint32_t      bgcolor;
	uint32_t      out_format;
	uint32_t      oneshot_en;
	uint32_t      bt601_709_sel;
	uint32_t      montior_enable;
	uint32_t      montior_frame_cnt;
	ppcon1_cfg_t  ppcon1;
	ppcon2_cfg_t  ppcon2;
	gamma_cfg_t gamma_cfg;
	disp_timing_t timing;
	struct csi_dev_channel_cfg_s csi_tx_cfg;
	struct dsi_channel_cfg_s dsi_cfg;
	struct writeback_channel_cfg_s wb_cfg;
} output_cfg_t;

typedef struct channel_base_cfg_s {
	uint32_t channel;
	uint32_t enable;
	uint32_t pri;
	uint32_t width;
	uint32_t height;
	uint32_t xposition;
	uint32_t yposition;
	uint32_t format;
	uint32_t alpha;
#ifdef CONFIG_HOBOT_CHIP_J6X
	uint32_t keycolor_low;
	uint32_t keycolor_hig;
#elif CONFIG_HOBOT_CHIP_J5
	uint32_t keycolor;
#endif
	uint32_t alpha_sel;
	uint32_t ov_en;
	uint32_t ov_mode;
	uint32_t alpha_en;
	uint32_t global_alpha;
	uint32_t crop_x;
	uint32_t crop_y;
	uint32_t crop_width;
	uint32_t crop_height;
	uint32_t rotation;
#ifdef CONFIG_HOBOT_CHIP_J6X
	uint32_t up_scaling_enable;
	uint32_t dst_width;
	uint32_t dst_height;
#endif

	uint32_t argb_endian_sel;
	uint32_t rgb565_convert_sel;
	uint32_t palette[PALETTE_SIZE];
} channel_base_cfg_t;

typedef struct layer_ctrl_s {
	uint32_t layer_no;
	uint32_t enable;
	uint32_t width;
	uint32_t height;
	uint32_t pos_x;
	uint32_t pos_y;
} layer_ctrl_t;

typedef struct pin_ctrl_s {
	int32_t	gpio_pin;
	int32_t	gpio_level;
	int32_t	power_delay;
} pin_ctrl_t;

typedef struct pin_ctrl_info_s {
	int32_t			pin_ctrl_num;
	pin_ctrl_t		pin_ctrl[PIN_CTRL_MAX_NUM];
} pin_ctrl_info_t;

typedef struct serial_info_s {
	char			serial_name[10];
	int32_t			serial_addr; /*7-bit slave addr*/
	int32_t			bus_num;
	int32_t			work_mode;
	pin_ctrl_info_t		pin_ctrl_info[PIN_CTRL_PURP_MAX];
	enum work_state_e	init_state;
	void			*port_info[PORT_MAX];
} serial_info_t;

typedef struct deserial_info_s {
	char			deserial_name[20];
	int32_t			deserial_addr; /*7-bit slave addr*/
	int32_t			deserial_alias; /*7-bit slave addr*/
	int32_t			bus_num;
	int32_t			tx_port;
	pin_ctrl_info_t		pin_ctrl_info[PIN_CTRL_PURP_MAX];
	enum work_state_e	init_state;
	void			*port_info;
} deserial_info_t;

typedef struct dsi2hdmi_info_s {
	char			*dsi2hdmi_name;
	int32_t			dsi2hdmi_addr;
	int32_t			bus_num;
	pin_ctrl_info_t	pin_ctrl_info[PIN_CTRL_PURP_MAX];
	enum work_state_e	init_state;
	void			*port_info;
} dsi2hdmi_info_t;

typedef struct panel_info_s {
	char			*panel_name;
	enum			cmd_type_e cmd_type;
	pin_ctrl_info_t		pin_ctrl_info[PIN_CTRL_PURP_MAX];
	enum work_state_e	init_state;
	void			*panel_ops;
	void			*panel_fd;
	void			*port_info;
} panel_info_t;

typedef struct port_info_s {
	int32_t				width;
	int32_t				height;
	char				format[NAME_MAX_LENGTH];
	int32_t				fps;
	struct dsi_channel_cfg_s	dsi_cfg;
	int32_t				deserial_id;
	serial_info_t			*serial_info;
	deserial_info_t			*deserial_info;
	panel_info_t			*panel_info;
	dsi2hdmi_info_t			*dsi2hdmi_info;
	void				*adapter_ops;
	void				*adapter_fd;
} port_info_t;

typedef struct board_info_s {
	int32_t				dsi_id;
	uint32_t			bus_num;
	uint32_t 			port_num;
	board_type_e			type;
	enum interface_type_e		interface_type;
	port_info_t			port_info[PORT_MAX];
	serial_info_t			serial_info;
	deserial_info_t			deserial_info[PORT_MAX];
	panel_info_t			panel_info;
	dsi2hdmi_info_t			dsi2hdmi_info;
} board_info_t;

typedef struct disp_cfg_s {
	uint32_t ctx_id;
	uint32_t disp_id;
	channel_base_cfg_t channel_base_cfg[IDU_ICHN_NUM];
	output_cfg_t	   output_cfg;
	board_info_t	   board_info;
} disp_cfg_t;

typedef enum {
	DISP_DYNAMIC_UPSCALE = 0,
	DISP_DYNAMIC_TIMING,
	DISP_DYNAMIC_GAMMA,
	DISP_DYNAMIC_LAYERCTRL,
	DISP_DYNAMIC_LAYERCFG,
	DISP_DYNAMIC_OUTPUT,
	DISP_DYNAMIC_CHANNEL,
	DISP_DYNAMIC_NUM,
} disp_dynamic_type_e;

typedef struct disp_dynamic_cfg_s {
	uint32_t disp_id;
	disp_dynamic_type_e type;
	struct upscaling_cfg_s upscale_cfg;
	struct disp_timing_s timing_cfg;
	struct gamma_cfg_s gamma_cfg;
	struct layer_ctrl_s layer_ctrl;
	struct channel_base_cfg_s channel_cfg;
	struct output_cfg_s output_cfg;
} disp_dynamic_cfg_t;


#endif //__HBN_IDU_CFG_H__
