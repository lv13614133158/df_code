/**
 * @file: hb_videostitch_interface.h
 * @
 * @NO{S09E04C02}
 * @ASIL{B}
 * @Copyright (c) 2023 by horizon, All Rights Reserved.
 */
/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/
#ifndef HB_VIDEOSTITCH_INTERFACE_H_
#define HB_VIDEOSTITCH_INTERFACE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PLANES (3u)
#define FRAME_MAX (4u)
#define ROI_MAX (12u)
#define ROI_W_MAX (2000u)
#define ROI_H_MAX (2000u)
#define DST_W_MAX (3840u)
#define DST_H_MAX (3840u)

//#define HB_VPS_VIDEOSTITCH_NO_ERROR (0)
//#define HB_VPS_VIDEOSTITCH_FD_NOT_INITED (1)
// #define HB_VPS_VIDEOSTITCH_SET_HW_SETTINGS_FAILED (2)
//#define	HB_VPS_VIDEOSTITCH_WAIT_DONE_FAIL (3)
//#define	HB_VPS_VIDEOSTITCH_IOMMU_MAP_FAILED (4)
//#define	HB_VPS_VIDEOSTITCH_NOMEM (5)
// #define HB_VPS_VIDEOSTITCH_CFG_ATTR (6)
// #define HB_VPS_VIDEOSTITCH_WAITE_OUT (7)
// #define HB_VPS_VIDEOSTITCH_ADDRESS_ERR (8)

#define VIDEOSTITCH_ERR_BASE (8000)

#define HB_VPS_VIDEOSTITCH_NO_ERROR 0
#define HB_VPS_VIDEOSTITCH_NODE_OPEN_FAILD (VIDEOSTITCH_ERR_BASE + 1) //初始化失败，节点打开失败
#define HB_VPS_VIDEOSTITCH_OVERFLOW_MAX_CTX (VIDEOSTITCH_ERR_BASE + 2) //初始化失败，进程数超过最大ctx
#define HB_VPS_VIDEOSTITCH_VERSION_MISMATCH (VIDEOSTITCH_ERR_BASE + 3) //初始化失败，版本检查失败
#define HB_VPS_VIDEOSTITCH_INVALID_STATUS (VIDEOSTITCH_ERR_BASE + 4) //调用流程非法
#define HB_VPS_VIDEOSTITCH_NULL_POINTER (VIDEOSTITCH_ERR_BASE + 5) //输入参数空指针
#define HB_VPS_VIDEOSTITCH_INVALID_PARAMETER (VIDEOSTITCH_ERR_BASE + 6) //参数检查不通过
#define HB_VPS_VIDEOSTITCH_INVALID_WORK_MODE (VIDEOSTITCH_ERR_BASE + 7) //工作模式非法
#define HB_VPS_VIDEOSTITCH_SET_CFG_FAILD (VIDEOSTITCH_ERR_BASE + 8) //配置参数失败
#define HB_VPS_VIDEOSTITCH_SEND_SRC_FRAME_FAILD (VIDEOSTITCH_ERR_BASE + 9) //回灌输入buf失败
#define HB_VPS_VIDEOSTITCH_SEND_OUT_FRAME_FAILD (VIDEOSTITCH_ERR_BASE + 10) //回灌输出buf失败
#define HB_VPS_VIDEOSTITCH_GET_RESULT_FAILD (VIDEOSTITCH_ERR_BASE + 11) //获取输出结果失败
#define HB_VPS_VIDEOSTITCH_FREE_OUT_FRAME_FAILD (VIDEOSTITCH_ERR_BASE + 12) //释放buf失败
#define HB_VPS_VIDEOSTITCH_STOP_FAILD (VIDEOSTITCH_ERR_BASE + 13) //deinit 失败, stop ip失败

enum { //enumeration of stitching mode
	MODE_ONLINE = 0, //online mode
	MODE_ALPHA = 1, //alpha mode
	MODE_ALPHA_BETA = 2, //alpha beda mode
	MODE_SRC = 3, //src mode
	MODE_ALPHA_SRC0 = 5 //arpha src0 mode
};

enum { //enumeration of frame index
	PIC_ID_LEFT = 0, //left
	PIC_ID_TOP, //top
	PIC_ID_RIGHT, //right
	PIC_ID_BOTTOM, //bottom
	PIC_ID_ALL, //all frame
	PIC_ID_MAX //max value
};

enum { //enumeration of direct
	DIRECT_LT = 0, //left and top direct
	DIRECT_RB = 1, //right and bottom direct
	DIRECT_LB = 2, //left and bottom direct
	DIRECT_RT = 3, //right and top direct
	DIRECT_MAX = 4 //max value of direct
};

/**
 * @struct buffer_offset_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct buffer_offset_s {
	uint32_t width;
	/**< width of dst image
	 * range:[0, 4096]; default: 0
	 */
	uint32_t height;
	/**< height of dst image
	 * range:[0, 2160]; default: 0
	 */
	uint32_t stride_size;
	/**< stride of dst image
	 * range:[0, ); default: 0
	 */
	uint32_t size[MAX_PLANES];
	/**< size of dst image
	 * range:[0, ); default: 0
	 */
	uint32_t planeCount;
	/**< plane count of dst image
	 * range:[0, 2]; default: 0
	 */
	uint32_t offset[MAX_PLANES];
	/**< y,uv  or raw/ dol2 / dol3
	 * range:[0, ); default: 0
	 */
} buffer_offset_t;

/**
 * @struct src_rect_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct src_rect_s {
	uint32_t src0_idx;
	/**< index of frame which src0 belongs to
	 * range:[0, 3]; default: 0
	 */
	uint32_t src0_x;
	/**< initial x coordinate of src0
	 * range:[0, 4095]; default: 0
	 */
	uint32_t src0_y;
	/**< initial y coordinate of src0
	 * range:[0, 2159]; default: 0
	 */
	uint32_t src0_w;
	/**< width of src0
	 * range:[0, 4096]; default: 0
	 */
	uint32_t src0_h;
	/**< height of src0
	 * range:[0, 2160]; default: 0
	 */

	uint32_t src1_idx;
	/**< index of frame which src1 belongs to
	 * range:[0, 3]; default: 0
	 */

	uint32_t src1_x;
	/**< initial x coordinate of src1
	 * range:[0, 4095]; default: 0
	 */
	uint32_t src1_y;
	/**< initial y coordinate of src1
	 * range:[0, 2159]; default: 0
	 */

	uint32_t src1_w;
	/**< width of src1
	 * range:[0, 4096]; default: 0
	 */
	uint32_t src1_h;
	/**< height of src1
	 * range:[0, 2160]; default: 0
	 */
} src_rect_t;

/**
 * @struct dst_rect_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct dst_rect_s {
	uint32_t dst_xpos;
	/**< initial x coordinate of roi in dst image
	 * range:[0, 4095]; default: 0
	 */
	uint32_t dst_ypos;
	/**< initial y coordinate of roi in dst image
	 * range:[0, 2159]; default: 0
	 */

	uint32_t roi_w;
	/**< width of roi
	 * range:[0, 4096]; default: 0
	 */
	uint32_t roi_h;
	/**< height of roi
	 * range:[0, 2160]; default: 0
	 */

	uint32_t dst_w;
	/**< width of dst image
	 * range:[0, 4096]; default: 0
	 */
	uint32_t dst_h;
	/**< height of dst image
	 * range:[0, 2160]; default: 0
	 */
} dst_rect_t;

/**
 * @struct ctrl_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct ctrl_s {
	uint32_t mode;
	/**< stitching mode
	 * range:[0, 1,2,3,5]; default: 0
	 */
	uint32_t direct;
	/**< online calculation mode direct
	 * range:[0, ); default: 0
	 */
	uint32_t uven;
	/**< dst image plane
	 * range:[0, ); default: 0
	 */
	uint32_t margin;
	/**< margin attribute ,the default value is 10
	 * range:[0, ); default: 0
	 */
	uint32_t margin_inv;
	/**< when margin>0, floor(128*128/margin_inv).when margin==0,margin_inv==128
	 * range:[0, ); default: 0
	 */
} ctrl_t;

/**
 * @struct src_gain_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct src_gain_s {
	uint32_t src0_gain_y;
	/**< gain of y src0
	 * range:[0, ); default: 0
	 */
	uint32_t src1_gain_y;
	/**< gain of y src1
	 * range:[0, ); default: 0
	 */

	uint32_t src0_gain_u;
	/**< gain of u src0
	 * range:[0, ); default: 0
	 */
	uint32_t src1_gain_u;
	/**< gain of u src1
	 * range:[0, ); default: 0
	 */

	uint32_t src0_gain_v;
	/**< gain of v src0
	 * range:[0, ); default: 0
	 */
	uint32_t src1_gain_v;
	/**< gain of v src1
	 * range:[0, ); default: 0
	 */
} src_gain_t;

/**
 * @struct roi_cfg_t
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct roi_cfg_s {
	//coverity[misra_c_2012_rule_5_8_violation:SUPPRESS], ## violation reason SYSSW_V_5.8_02
	uint32_t index;
	/**< index of roi
	 * range:[0, 12]; default: 0
	 */
	src_rect_t src_rect;
	/**< src_rect_t data structure
	 * range:[0, ); default: 0
	 */
	dst_rect_t dst_rect;
	/**< dst_rect_t data structure
	 * range:[0, ); default: 0
	 */
	ctrl_t ctrl;
	/**< ctrl_t data structure
	 * range:[0, ); default: 0
	 */
	src_gain_t src_gain;
	/**< src_gain_t data structure
	 * range:[0, ); default: 0
	 */
} roi_cfg_t;

/**
 * @struct result_addr_s
 * @brief
 * @NO{S09E04C02}
 */
typedef struct result_addr_s {	//abandoned structure
	uint32_t planeCount;
	/**< plane count of dst image
	 * range:[0, ); default: 0
	 */
	uint32_t size[MAX_PLANES];
	/**< size of dst image
	 * range:[0, ); default: 0
	 */
	char *virt_img[MAX_PLANES];
	/**< virtual addrass of dst image
	 * range:[0, ); default: 0
	 */
	uint64_t pa_img[MAX_PLANES];
	/**< physical addrass of dst image
	 * range:[0, ); default: 0
	 */
} result_addr_t;

/**
 * @struct cgp_addr_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct cgp_addr_s {
	uint32_t size;
	/**< size of config package
	 * range:[0, ); default: 0
	 */
	char *virt_cgp;
	/**< virtual addrass of config package
	 * range:[0, ); default: 0
	 */
	uint64_t pa_cgp;
	/**< physical addrass of config package
	 * range:[0, ); default: 0
	 */
} cgp_addr_t;

/**
 * @struct lut_table_addr_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct lut_table_addr_s {
	uint32_t size;
	/**< size of look-up-table
	 * range:[0, ); default: 0
	 */
	char *lut_parameter;
	/**< virtual addrass of look-up-table
	 * range:[0, ); default: 0
	 */
	uint64_t pa_lut;
	/**< physical addrass of look-up-table
	 * range:[0, ); default: 0
	 */
} lut_table_addr_t;

/**
 * @struct lut_table_s
 * @brief 
 * @NO{S09E04C02}
 */
typedef struct lut_table_s {
	lut_table_addr_t alpha_lut_table;
	/**< alpha lut_table_addr_s data structure
	 * range:[0, ); default: 0
	 */
	lut_table_addr_t beta_lut_table;
	/**< beta lut_table_addr_s data structure
	 * range:[0, ); default: 0
	 */
} lut_table_t;

typedef struct frame_s {
	uint32_t pic_id;
	uint32_t buf_index; /**< buffer index */
	/**< frame id
	 * range:[0, ); default: 0
	 */
	uint32_t height;
	/**< height of frame
	 * range:[0, 2160]; default: 0
	 */
	uint32_t width;
	/**< width of frame
	 * range:[0, 4096]; default: 0
	 */
	uint32_t y_stride;
	/**< y_stride of frame
	 * range:[0, ); default: 0
	 */
	uint32_t uv_stride;
	/**< uv_stride of frame
	 * range:[0, ); default: 0
	 */
	uint64_t phy_y_addr;
	/**< physical y addrass of frame
	 * range:[0, ); default: 0
	 */
	uint64_t phy_uv_addr;
	/**< physical uv addrass of frame
	 * range:[0, ); default: 0
	 */
	char *virt_y_addr;
	/**< virtual y addrass of frame
	 * range:[0, ); default: 0
	 */
	char *virt_uv_addr;
	/**< virtual uv addrass of frame
	 * range:[0, ); default: 0
	 */
	uint32_t y_size;
	/**< y size of frame
	 * range:[0, ); default: 0
	 */
	uint32_t uv_size;
	/**< uv size of frame
	 * range:[0, ); default: 0
	 */
} frame_t;

/**
 * @struct frameinfo_s
 * @brief
 * @NO{S09E04C02}
 */
typedef struct frameinfo_s {	//abandoned structure
	uint32_t frame_num;
	//PIC_ID_LEFT-L,PIC_ID_TOP-LT,PIC_ID_RIGHT-LTR,PIC_ID_BOTTOM-LTRB,PIC_ID_ALL-ALL
	int32_t frame_ready; //ready count of frame
	frame_t frame[FRAME_MAX]; //0-left,1-top,2-right,3-bottom
} frameinfo_t;

typedef struct sth_mode_ctrl_s {
	uint32_t working_mode;
	uint32_t obuf_num;
} sth_mode_ctrl_t;

enum sth_working_status { STH_FREE, STH_INITED, STH_CONFED, STH_PROCESSING, STH_DEINITED, STH_STATUS_INVAIL };

#define STITCH_MODE_EXTERNAL_BUF 0u
#define STITCH_MODE_INTERNAL_BUF 1u
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief Init videostitch module; 初始化stitch模块
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 * @param[out] None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_init(void);
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief Deinit videostitch module; 去初始化stitch模块
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 * @param[out] None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_deinit(void);
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief Calculate outbuf size; 计算输出图像的size大小
 * @param[in] width: width of dst; 输出图像的宽
 * @param[in] height: height of dst; 输出图像的高
 * @param[out] *buf_offset: pointer of buffer_offset_t struct; 存储输出frame size大小的结构体
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_calc_outbuf_size(uint32_t width, uint32_t height, buffer_offset_t *buf_offset);
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief Calculate configure package size; 计算配置字所需内存大小
 * @param[in] roi_num: number of roi; roi的数量
 * @param[out] *size: size of configure package
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 * @param[out] None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_cgp_size(uint32_t roi_num, uint32_t *size);

/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief set stitch process configure; 设置stitch的配置参数
 *
 * @param[in] mode_ctrl: working mode attribute; 工作模式属性参数
 * @param[in] roi_num: number of roi; roi数量
 * @param[in] *roi_cfg: pointer of roi_cfg_t struct; 指向roi配置相关结构体的指针
 * @param[in] *blending_lut: pointer of lut_table_t struct; 指向lut表结构体的指针
 * @param[in] *cgp_addr: pointer of cgp_addr_t struct; 指向配置字地址结构体的指针
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 * @param[out] None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_set_cfg(sth_mode_ctrl_t mode_ctrl, uint32_t roi_num, const roi_cfg_t *roi_cfg,
			       const lut_table_t *blending_lut, const cgp_addr_t *cgp_addr);
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief tiger videostitch to process frame; 触发一次拼接处理
 *
 * @param[in] src_frame_num: the num of input frame;输入图像数量
 * @param[in] *src_frames: pointer of input frame_t struct;指向输入frame相关的结构体的指针
 * @param[in] *dst_frame: pointer of output frame_t struct;指向输出frame相关的结构体的指针
 * @retval "= 0": success; 成功
 * @retval "< 0": failure; 失败
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
*/
int32_t hb_videostitch_blending_process(uint32_t src_frame_num, const frame_t *src_frames, frame_t *dst_frame);
/**
 * @NO{S09E04C02I}
 * @ASIL{B}
 * @brief release frame buff when using vpf internal buf; 当使用内部buf时，释放输出buf
 * @param[in] *out_img: point to out frameinfo_t instance; 指向输出buf的指针
 * @retval "= 0": success
 * @retval "< 0": failure
 * @param[out] None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_videostitch_releaseframe(frame_t *dst_frame);

#ifdef __cplusplus
}
#endif

#endif // HB_VIDEOSTITCH_INTERFACE_H_