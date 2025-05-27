/***************************************************************************
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 ***************************************************************************/

#ifndef __HBN_VIN_CFG_H__
#define __HBN_VIN_CFG_H__

#define LPWM_CHN_NUM 4u
#define SENSOR_ERR_PIN_NUM 4

#define LPWM_CHN_INVALID 0xffffu

enum vcon_gpio_e {
	/* poc gpios */
	VGPIO_POC_PWREN,
	VGPIO_POC_EN,
	VGPIO_POC_INT,
	VGPIO_POC_ENC0,
	VGPIO_POC_ENC1,
	VGPIO_POC_ENC2,
	VGPIO_POC_ENC3,
	VGPIO_POC_NC,
	/* des gpios */
	VGPIO_DES_PWREN,
	VGPIO_DES_PWDN,
	VGPIO_DES_LOCK,
	VGPIO_DES_ERRB,
	VGPIO_DES_CFG0,
	VGPIO_DES_CFG1,
	VGPIO_DES_ERROR0,
	VGPIO_DES_ERROR1,
	VGPIO_DES_ERROR2,
	VGPIO_DES_ERROR3,
	VGPIO_DES_PWREN2,
	VGPIO_DES_NC,
	/* ser gpios */
	VGPIO_SER_PWREN,
	VGPIO_SER_PWDN,
	VGPIO_SER_LOCK,
	VGPIO_SER_ERRB,
	VGPIO_SER_CFG0,
	VGPIO_SER_CFG1,
	VGPIO_SER_CFG2,
	VGPIO_SER_PWREN2,
	/* oth gpios */
	VGPIO_OTH_0,
	VGPIO_OTH_1,
	VGPIO_OTH_2,
	VGPIO_OTH_3,
	/* local info */
	VGPIO_NUM,
	VGPIO_POC_BASE = VGPIO_POC_PWREN,
	VGPIO_POC_NUM = VGPIO_DES_PWREN - VGPIO_POC_PWREN,
	VGPIO_DES_BASE = VGPIO_DES_PWREN,
	VGPIO_DES_NUM = VGPIO_SER_PWREN - VGPIO_DES_PWREN,
	VGPIO_SER_BASE = VGPIO_SER_PWREN,
	VGPIO_SER_NUM = VGPIO_OTH_0 - VGPIO_SER_PWREN,
	VGPIO_OTH_BASE = VGPIO_OTH_0,
	VGPIO_OTH_NUM = VGPIO_NUM - VGPIO_OTH_0,
};

typedef struct lpwm_chn_attr_s {
	uint32_t enable;
	uint32_t trigger_source;
	uint32_t trigger_mode;
	uint32_t period;
	uint32_t offset;
	uint32_t duty_time;
	uint32_t threshold;
	uint32_t adjust_step;
} lpwm_chn_attr_t; 				// Lpwm channel attribute structure

typedef struct lpwm_attr_s {
	lpwm_chn_attr_t lpwm_chn_attr[LPWM_CHN_NUM];
} lpwm_attr_t;					// Lpwm attribute structure

typedef struct vcon_attr_s {
	int32_t attr_valid;			// Effective configuration of attributes
	int32_t bus_main;			// .Main I2C Main Line Index
	int32_t bus_second;			// .Secondary I2C mainline index
	int32_t gpios[VGPIO_NUM];		// .Gpio index
	int32_t sensor_err[SENSOR_ERR_PIN_NUM];	// sensor err_pin index 4
	int32_t lpwm_chn[LPWM_CHN_NUM];		// lpwm channel index 4.
	int32_t rx_phy_mode; 			// rx phy mode: 0-notuse,1-dphy,2-cphy.
	int32_t rx_phy_index; 			// rx phy index.
	int32_t rx_phy_link; 			// Rx phy mode: 0-notuse,1-csi,2-dsi.
	int32_t tx_phy_mode;
	int32_t tx_phy_index; 			// tx phy index.
	int32_t tx_phy_link; 			// Tx phy link index - composite type usage
	int32_t vcon_type; 			// Vcon type: 0-independent, 1-composite master, 2-composite slave
	int32_t vcon_link; 			// Vcon link index - composite type usage
} vcon_attr_t;					// Vcon attribute structure

typedef struct cim_func_desc {
	uint32_t enable_frame_id;
	uint32_t set_init_frame_id;
	uint32_t enable_pattern;
	uint32_t skip_frame;
	uint32_t input_fps;
	uint32_t output_fps;
	uint32_t skip_nums;
	uint32_t hw_extract_m;
	uint32_t hw_extract_n;
	uint32_t lpwm_trig_sel;
} cim_func_desc_t;

typedef struct cim_input_rdma {
	uint32_t rdma_en;			// enable rdma
	uint32_t stride;			// read stride
	uint32_t pack_mode;
	uint32_t buff_num;
} cim_input_rdma_t;

typedef struct cim_input_tpg {
	uint32_t tpg_en;			// enable tpg
	uint32_t fps;				// fps
} cim_input_tpg_t;

typedef struct cim_attr_s {
	uint32_t mipi_en;			// enable mipi
	uint32_t mipi_rx;
	uint32_t vc_index;			// vx index
	uint32_t ipi_channels;			// DOL2 use
	uint32_t cim_pym_flyby;			// cim online pym  pym_sel Which way to choose
	uint32_t cim_isp_flyby;			// cim online ISP  isp_chx
	uint32_t y_uv_swap;
	cim_input_rdma_t rdma_input;
	cim_input_tpg_t tpg_input;
	cim_func_desc_t func;
} cim_attr_t;

typedef struct vin_node_attr_s {
	cim_attr_t cim_attr;			// Cim attribute
	lpwm_attr_t lpwm_attr;			// Lpwm attribute
	vcon_attr_t vcon_attr;			// Vcon Properties
	uint32_t flow_id;
	uint32_t magicNumber;
} vin_node_attr_t;				// Vin attribute structure

#define MIPIHOST_CHANNEL_NUM (4)
#define MIPIHOST_CHANNEL_0 (0)
#define MIPIHOST_CHANNEL_1 (1)
#define MIPIHOST_CHANNEL_2 (2)
#define MIPIHOST_CHANNEL_3 (3)

typedef struct mipi_host_cfg_s {
	/* type must be: uint16_t */
	uint16_t phy;
	uint16_t lane;
	uint16_t datatype;
	uint16_t fps;
	uint16_t mclk;
	uint16_t mipiclk;
	uint16_t width;
	uint16_t height;
	uint16_t linelenth;
	uint16_t framelenth;
	uint16_t settle;
	uint16_t ppi_pg;
	uint16_t hsaTime;
	uint16_t hbpTime;
	uint16_t hsdTime;
	uint16_t channel_num;
	uint16_t channel_sel[MIPIHOST_CHANNEL_NUM];
} mipi_host_cfg_t;
#define MIPI_HOST_CFG_NUM ((uint32_t)(sizeof(mipi_host_cfg_t) / sizeof(uint16_t)))

#define MIPI_HOST_CFG_STRINGS { \
	"phy", \
	"lane", \
	"datatype", \
	"fps", \
	"mclk", \
	"mipiclk", \
	"width", \
	"height", \
	"linelenth", \
	"framelenth", \
	"settle", \
	"ppi_pg", \
	"hsaTime", \
	"hbpTime", \
	"hsdTime", \
	"channel_num", \
	"channel_sel0", \
	"channel_sel1", \
	"channel_sel2", \
	"channel_sel3", \
}

#define MIPIDEV_CHANNEL_NUM (4)
#define MIPIDEV_CHANNEL_0 (0)
#define MIPIDEV_CHANNEL_1 (1)
#define MIPIDEV_CHANNEL_2 (2)
#define MIPIDEV_CHANNEL_3 (3)

typedef struct mipi_dev_cfg_s {
	/* type must be: uint16_t */
	uint16_t lane;
	uint16_t datatype;
	uint16_t fps;
	uint16_t mclk;
	uint16_t mipiclk;
	uint16_t width;
	uint16_t height;
	uint16_t linelenth;
	uint16_t framelenth;
	uint16_t settle;
	uint16_t vpg;
	uint16_t ipi_lines;
	uint16_t channel_num;
	// uint16_t channel_sel[MIPIDEV_CHANNEL_NUM];
	uint16_t channel_sel[4];
} mipi_dev_cfg_t;
#define MIPI_DEV_CFG_NUM ((uint32_t)(sizeof(mipi_dev_cfg_t) / (uint32_t)sizeof(uint16_t)))

#define MIPI_DEV_CFG_STRINGS { \
	"lane", \
	"datatype", \
	"fps", \
	"mclk", \
	"mipiclk", \
	"width", \
	"height", \
	"linelenth", \
	"framelenth", \
	"settle", \
	"vpg", \
	"ipi_lines", \
	"channel_num", \
	"channel_sel0", \
	"channel_sel1", \
	"channel_sel2", \
	"channel_sel3", \
}

typedef struct mipi_attr_s {
	int32_t attr_valid;
	int32_t attach;				// attach操作类型.
	int32_t rx_enable;			// RX设备使能
	int32_t tx_enable;			// TX设备使能.
	int32_t tx_index;

	struct mipi_host_cfg_s rx_attr;		// RX设备属性.
	struct mipi_dev_cfg_s tx_attr;		// TX设备属性.
} mipi_attr_t;					// mipi属性结构体.

typedef struct mipi_host_param_s {
	/* type must be: uint32_t */
	uint32_t nocheck;
	uint32_t notimeout;
	uint32_t wait_ms;
	uint32_t dbg_value;
	uint32_t adv_value;
	uint32_t need_stop_check;
	uint32_t stop_check_instart;
	uint32_t cut_through;
	uint32_t mem_flush;
	uint32_t data_ids_1;
	uint32_t data_ids_2;
	uint32_t data_ids_vc1;
	uint32_t data_ids_vc2;
	uint32_t ipi_16bit;
	uint32_t ipi_force;
	uint32_t ipi_limit;
	uint32_t ipi_overst;
	uint32_t pkt2pkt_time;
	uint32_t snrclk_en;
	uint32_t snrclk_freq;
	uint32_t vcext_en;
	uint32_t error_diag;
	uint32_t ipi1_dt;
	uint32_t ipi2_dt;
	uint32_t ipi3_dt;
	uint32_t ipi4_dt;
	uint32_t cfg_nocheck;
	uint32_t drop_func;
	uint32_t drop_mask;
	uint32_t irq_cnt;
	uint32_t irq_debug;
	uint32_t stl_dbg;
	uint32_t stl_mask;
	uint32_t stl_pile;
	uint32_t stl_ovif;
	uint32_t stl_stif;
	uint32_t fatal_ap;
} mipi_host_param_t;
#define MIPI_HOST_PARAMS_NUM ((int32_t)sizeof(struct mipi_host_param_s) / (int32_t)sizeof(uint32_t))

#define MIPI_HOST_PARAM_STRINGS { \
	"nocheck", \
	"notimeout", \
	"wait_ms", \
	"dbg_value", \
	"adv_value", \
	"need_stop_check", \
	"stop_check_instart", \
	"cut_through", \
	"mem_flush", \
	"data_ids_1", \
	"data_ids_2", \
	"data_ids_vc1", \
	"data_ids_vc2", \
	"ipi_16bit", \
	"ipi_force", \
	"ipi_limit", \
	"ipi_overst", \
	"pkt2pkt_time", \
	"snrclk_en", \
	"snrclk_freq", \
	"vcext_en", \
	"error_diag", \
	"ipi1_dt", \
	"ipi2_dt", \
	"ipi3_dt", \
	"ipi4_dt", \
	"cfg_nocheck", \
	"drop_func", \
	"drop_mask", \
	"irq_cnt", \
	"irq_debug", \
	"stl_dbg", \
	"stl_mask", \
	"stl_pile", \
	"stl_ovif", \
	"stl_stif", \
	"fatal_ap", \
}

typedef struct mipi_dev_param_s {
	/* type must be: uint32_t */
	uint32_t nocheck;
	uint32_t notimeout;
	uint32_t wait_ms;
	uint32_t dbg_value;
	uint32_t power_instart;
	uint32_t hsync_pkt;
	uint32_t init_retry;
	uint32_t ipi_force;
	uint32_t ipi_limit;
	uint32_t error_diag;
	uint32_t ipi1_dt;
	uint32_t ipi2_dt;
	uint32_t ipi3_dt;
	uint32_t ipi4_dt;
	uint32_t cfg_nocheck;
	uint32_t irq_cnt;
	uint32_t irq_debug;
	uint32_t stl_dbg;
	uint32_t stl_mask;
	uint32_t stl_pile;
	uint32_t fatal_ap;
	uint32_t txout_param_valid;
	uint32_t txout_freq_mode;
	uint32_t txout_freq_autolarge_enbale;
	uint32_t txout_freq_gain_precent;
	uint32_t txout_freq_force;
} mipi_dev_param_t;
#define MIPI_DEV_PARAMS_NUM ((uint32_t)(sizeof(struct mipi_dev_param_s) / sizeof(uint32_t)))

#define MIPI_DEV_PARAM_STRINGS { \
	"nocheck", \
	"notimeout", \
	"wait_ms", \
	"dbg_value", \
	"power_instart", \
	"hsync_pkt", \
	"init_retry", \
	"ipi_force", \
	"ipi_limit", \
	"error_diag", \
	"ipi1_dt", \
	"ipi2_dt", \
	"ipi3_dt", \
	"ipi4_dt", \
	"cfg_nocheck", \
	"irq_cnt", \
	"irq_debug", \
	"stl_dbg", \
	"stl_mask", \
	"stl_pile", \
	"fatal_ap", \
	"txout_param_valid", \
	"txout_freq_mode", \
	"txout_freq_autolarge_enbale", \
	"txout_freq_gain_precent", \
	"txout_freq_force", \
}

typedef struct mipi_attr_ex_s {
	int32_t attr_valid;
	int32_t reserved;
	uint64_t rx_ex_mask;			// RX增强属性掩码.
	uint64_t tx_ex_mask;			// TX增强属性掩码.

	struct mipi_host_param_s rx_attr_ex;	// RX增强属性;
	struct mipi_dev_param_s tx_attr_ex;	// TX增强属性;
} mipi_attr_ex_t;

typedef struct vcon_inter_attr_s {
	int32_t attr_valid;
	int32_t flow_id;			// vflow id,VIN_NODE赋值
	int32_t ctx_id;				// vctx id VIN_NODE赋值.
	int32_t attach;				// attach操作类型
	int32_t deserial_attach;		// 是否连上deserial
	int32_t deserial_index;			// 所连deserial索引
	int32_t deserial_link;			// 所连deserial上link.
	int32_t sensor_attach;			// 是否连上sensor.
	int32_t sensor_index;			// 所连sensor索引.
	int32_t tx_attach;			// 是否使用tx
	int32_t tx_index;			// 所用tx索引
} vcon_inter_attr_t;				// vcon内部属性结构体.

typedef struct vin_inter_attr_s {
	mipi_attr_t mipi_inter_attr;
	vcon_inter_attr_t vcon_inter_attr;
} vin_inter_attr_t;

typedef enum cim_skip_type_s {
	CIM_DISABLE_SKIP,
	CIM_IN_RATIO_SKIP,
	CIM_FIRST_FRAMES_SKIP,
	CIM_HW_SKIP,
	CIM_SOFT_SYNC_SKIP,
	CIM_INVALID_SKIP,
} cim_skip_type_e;

typedef struct dynamic_fps_s {
	cim_skip_type_e
	skip_mode; 				// 0: Turn off frame skipping 1. Hardware performs frame skipping proportionally 2. Hardware continuously loses the previous few frames 3. Enable hardware frame extract
	unsigned int in_fps;			// Input frame rate
	unsigned int
	out_fps;				// Output frame rate when skip_ When mode=2, this field needs to be configured, which means how many frames are lost in front of it
	uint32_t skip_nums;
	uint32_t hw_extract_m;
	uint32_t hw_extract_n;
} dynamic_fps_t;

typedef struct lpwm_dynamic_fps_s {
	uint32_t lpwn_chn;			// These values need to be changed when the frame rate changes
	uint32_t period;
	uint32_t offset;
	uint32_t duty_time;
	uint32_t trigger_source;
	uint32_t trigger_mode;
} lpwm_dynamic_fps_t;

typedef struct cim_static_attr_s {
	uint32_t water_level_mark;		// Water level interruption
} cim_static_attr_t;				// Abstraction of CIM extended attributes

typedef enum vin_attr_ex_type_s {
	VIN_STATIC_CIM_ATTR,
	VIN_STATIC_MIPI_ATTR,
	VIN_DYNAMIC_FPS_CTRL,
	VIN_DYNAMIC_LPWM_TRIGGER_SOURCE,
	VIN_DYNAMIC_LPWM_FPS,
	VIN_DYNAMIC_IPI_RESET,
	VIN_DYNAMIC_BYPASS_ENABLE,
	VIN_ATTR_EX_INVALID,
} vin_attr_ex_type_e;

typedef struct vin_attr_ex_s {
	vin_attr_ex_type_e	ex_attr_type;		// Extended Attribute Type
	cim_static_attr_t	cim_static_attr;	// Cim Extension Properties
	mipi_attr_ex_t		mipi_ex_attr;		// Mipi extension attributes
	dynamic_fps_t		fps_ctrl;		// Skip Frame attribute
	lpwm_dynamic_fps_t	dynamic_fps_attr;	// Lpwm dynamic attribute, switching frame rate
	uint32_t		ipi_reset;		// mipi ipi reset
	uint32_t		bypass_enable;		// bypass enable
} vin_attr_ex_t;

typedef struct vin_emb_attr_s {
	uint32_t embeded_dependence;			// Is the emb and frame data together
	uint32_t embeded_width;				// Width of EMB data
	uint32_t embeded_height;			// High EMB data
} vin_emb_attr_t;					// Abstract of Rawds functionality

typedef struct vin_rawds_attr_s {
	uint32_t rawds_mode;
} vin_rawds_attr_t; //

struct vin_roi_attr_s {
	uint32_t roi_x;					// Starting point coordinate X
	uint32_t roi_y;					// Starting point coordinate Y
	uint32_t roi_width;				// Width of roi output
	uint32_t roi_height;				// High roi output
};

typedef enum vin_ochn_attr_type_s {
	VIN_BASIC_ATTR,
	VIN_EMB_ATTR,
	VIN_ROI_ATTR,
	VIN_RAWDS_ATTR,
	VIN_DYNAMIC_INVALID,
} vin_ochn_attr_type_e;

typedef struct vin_basic_attr_s {
	uint32_t pack_mode;				// Mode of writing DDR
	uint32_t wstride;
	uint32_t vstride;
	uint32_t format;				// DDR Write Format
} vin_basic_attr_t;					// Basic configuration of ochn

typedef enum _vin_ochn_type_e {
	VIN_MAIN_FRAME,
	VIN_ONLINE,
	VIN_FRAME_TOGHER,
	VIN_EMB,
	VIN_ROI,
	VIN_TYPE_INVALID,
} vin_ochn_type_e;

typedef struct vin_ochn_attr_s {
	uint32_t		ddr_en;			// wr enable
	uint32_t		roi_en;			// roi enable
	uint32_t		emb_en;			// emb enable
	uint32_t		rawds_en;		// rawds enable
	uint32_t		pingpong_ring;
	vin_ochn_attr_type_e	ochn_attr_type;		// Attribute Type
	vin_basic_attr_t	vin_basic_attr;		// Basic Attribute Type
	vin_rawds_attr_t	rawds_attr;		// rawds Attribute
	struct vin_roi_attr_s	roi_attr;		// ROI Attribute Public definition
	vin_emb_attr_t		emb_attr;		// emb Attribute
	uint32_t		magicNumber;
} vin_ochn_attr_t;

typedef struct vin_ochn_buff_attr_s {
	uint32_t buffers_num;
	int64_t flags;
} vin_ochn_buff_attr_t;

typedef struct vin_ichn_attr_s {
	uint32_t format;
	uint32_t width;
	uint32_t height;
} vin_ichn_attr_t;

typedef struct vin_attr_s {
	vin_node_attr_t vin_node_attr;
	vin_attr_ex_t vin_attr_ex;
	vin_ochn_attr_t vin_ochn_attr[VIN_TYPE_INVALID];
	vin_ichn_attr_t vin_ichn_attr;
	vin_ochn_buff_attr_t vin_ochn_buff_attr[VIN_TYPE_INVALID];
	uint32_t magicNumber;
} vin_attr_t;


#endif //__HBN_VIN_CFG_H__
