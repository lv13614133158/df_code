/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/
#ifndef HB_VIO_INTERFACE_H_
#define HB_VIO_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include "hb_camera_data_info.h"
#include "hb_vin_data_info.h"
#include "hb_vpm_data_info.h"
#include "bosch_vio_interface.h"

#define MULTI_FLAG_PATH \
	"/sys/module/hobot_vio_common/parameters/vio_mp_en" /**< vio server multi-process config file path  @NO{S09E06C01U} */

#define OPEN_FLAG_RO (0) /**< file open read only flag  @NO{S09E06C01U} */
#define OPEN_FLAG_RW (2) /**< file open read write flag  @NO{S09E06C01U} */
#define HB_ISP_CTX_ID_0 (0) /**< isp context id 0  @NO{S09E06C01U} */
#define HB_ISP_CTX_ID_1 (1) /**< isp context id 1  @NO{S09E06C01U} */
#define HB_ISP_CTX_ID_2 (2) /**< isp context id 2  @NO{S09E06C01U} */
#define HB_ISP_CTX_ID_3 (3) /**< isp context id 3  @NO{S09E06C01U} */
#define HB_ISP_SW_ID_OFFSET (4) /**< isp software id offset  @NO{S09E06C01U} */

// vio state check
#define HB_DEFAULT (0) /**< vio state default  @NO{S09E06C01U} */
#define HB_VIN_INIT (1) /**< vin state init  @NO{S09E06C01U} */
#define HB_VIN_DEINIT (2) /**< vin state deinit  @NO{S09E06C01U} */
#define HB_VIN_START (3) /**< vin state start  @NO{S09E06C01U} */
#define HB_VIN_STOP (4) /**< vin state stop  @NO{S09E06C01U} */
#define HB_VPM_INIT (5) /**< vpm state init  @NO{S09E06C01U} */
#define HB_VPM_DEINIT (6) /**< vpm state deinit  @NO{S09E06C01U} */
#define HB_VPM_START (7) /**< vpm state start  @NO{S09E06C01U} */
#define HB_VPM_STOP (8) /**< vpm state stop  @NO{S09E06C01U} */

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Select the corresponding vin index from the configuration file to initialize the sensor;通过配置文件选择对应 vin index,初始化 sensor
 *
 * @param[in]
 * uint32_t cfg_index: Cfg of vin in configuration file to be initialized index;需要初始化的vin在配置文件中的cfg_index;
 * range:[0, 2147483647],default:0
 * @param[in]
 * const char *cfg_file:Vin profile absolute path;vin 配置文件绝对路径
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VinInitStatus
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_init(uint32_t cfg_index, const char *cfg_file);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Select the corresponding vin index from the configuration file to de-initialize the sensor;通过配置文件选择对应 vin index,反初始化 sensor;
 *
 * @param[in]
 * uint32_t cfg_index: Config index of vin in the configuration file;vin在配置文件中的cfg_index;
 * range:[0, 2147483647],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VinInitStatus
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_deinit(uint32_t cfg_index);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Start the sensor data flow of the specified software channel; 启动指定软件通道的sensor数据流
 *
 * @param[in]
 * uint32_t port: Indicates the sensor, port and corresponding configuration file port that need to be enabled; 表示需要使能的sensor,port和对应配置文件port_*对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VinInitStatus
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_start(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Stop the sensor data flow of the specified software channel; 关闭指定软件通道的sensor数据流
 *
 * @param[in]
 * uint32_t port: Indicates the sensor, port and corresponding configuration file port that need to be disanabled; 表示需要关闭的sensor,port和对应配置文件port_*对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VinInitStatus
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_stop(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] None
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_start_all(void);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] None
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_stop_all(void);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Reset the corresponding port cam; 复位对应port cam
 *
 * @param[in]
 * uint32_t port: Cam ports to be reset; 需要复位的cam port;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_reset(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_power_on(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_power_off(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get the fps parameter in the configuration file of the corresponding port; 获取对应port的配置文件中fps参数
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] uint32_t *fps:Get the storage address of the frame rate value 取得帧率值的存储地址
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_fps(uint32_t port, uint32_t *fps);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] cam_img_info_t *cam_img_info: camera image information; camera图像数据
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_img(cam_img_info_t *cam_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] cam_img_info_t *cam_img_info: camera image information; camera图像数据
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_free_img(cam_img_info_t *cam_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] cam_img_info_t *cam_img_info: camera image information; camera图像数据
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_clean_img(cam_img_info_t *cam_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get the cim data of the corresponding port; 获取对应port的cim的数据
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file;和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] CAM_DATA_TYPE_E data_type: Set the required info type;
 * data_type parameter description:
 * HB_CAM_RAW_DATA:get cam raw data（raw sensor）
 * HB_CAM_YUV_DATA:get cam yuv data（yuv sensor）
 * HB_CAM_FEEDBACK_RAW_DATA:get feedback raw buff,used by cim feedback
 *
 * @param[in] CAM_DATA_TYPE_E data_type: 设置需要获取的info type;
 * data_type参数说明:
 * HB_CAM_RAW_DATA:获取cam raw 数据（raw sensor）
 * HB_CAM_YUV_DATA:获取cam yuv 数据（yuv sensor）
 * HB_CAM_FEEDBACK_RAW_DATA:获取回灌raw buff,用于cim 回灌
 * @param[out] void * data:Output the data result of the corresponding type 输出对应type的数据结果
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_data(uint32_t port, CAM_DATA_TYPE_E data_type, void *data);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Release the result of hb_cam_get_data of the corresponding port; 释放对应port的hb_cam_get_data 的结果
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] CAM_DATA_TYPE_E data_type: Set the released info type,corresponding to hb_cam_get_data; 设置需要释放的info type,和hb_cam_get_data对应
 * @param[in] void * data:The corresponding data is used with hb_cam_get_data; 对应的数据,和hb_cam_get_data 对应使用
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_free_data(uint32_t port, CAM_DATA_TYPE_E data_type, void *data);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief bypass corresponding sensor port; bypass 对应的sensor port
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] int32_t enable[0, 1]:if enable bypass function for this port; 是否使能bypass对应port;range:[0, 1],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_bypass_enable(uint32_t port, int32_t enable);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Set the frame rate of the corresponding port, and whether to select skip frame; 设置对应port的帧率,是否选择跳帧
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] int32_t skip_frame[0, 1]:if skip frame enable,0-no skip,1-skip; 是否使能跳帧功能,0-不跳帧,1-跳帧;range:[0, 1],default:0
 * @param[in] uint32_t in_fps:sensor input fps; 输入的帧率;range:[1, 480],default:30
 * @param[in] int32_t skip_frame:sensor output fps; 输出的帧率;range:[1, 480],default:30
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_set_fps_ctrl(uint32_t port, uint32_t skip_frame, uint32_t in_fps, uint32_t out_fps);


/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Set dynamic lpwm attr value; 动态设置port对应的lpwm 通道的属性值
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t lpwn_chn:lpwn channel id; port对应的lpwn channel 通道
 * @param[in] lpwm_dynamic_t *lpwm_dynamic_attr; lpwm_dynamic_attr通道属性值
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_set_lpwm_ctrl(uint32_t port, uint32_t lpwn_chn, lpwm_dynamic_t *lpwm_dynamic_attr);


/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get corresponding sensor port frame information; 获取对应port的帧信息
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] vio_statinfo *statinfo:address of statinfo;帧信息地址
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_stat_info(uint32_t port, struct vio_statinfo *info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief The frame rate switching interface requires the corresponding support of the sensor library; 帧率切换接口,需sensor库对应支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t fps:Indicates the frame rate to switch; 表示要切换的帧率range;[1, 480],default:30
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_dynamic_switch_fps(uint32_t port, uint32_t fps);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t mode: camera work mode; sersor工作模式;range:[0, 100],default:0
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_dynamic_switch_mode(uint32_t port, uint32_t mode);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t fps:Indicates the frame rate to switch; 表示要切换的帧率range;[1, 480],default:30
 * @param[in] uint32_t resolution:image resolution; 表示要切换的分辨率range;[1, 8294400],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_dynamic_switch(uint32_t port, uint32_t fps, uint32_t resolution);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t entry_num:Mipi host index; mipi host索引;range:[0, 3],default:0
 * @param[in] uint32_t mclk:senosr clock; sensor工作时钟;range:[1, 3000000],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_set_mclk(uint32_t entry_num, uint32_t mclk);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t entry_num:Mipi host index; mipi host索引;range:[0, 3],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_enable_mclk(uint32_t entry_num);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t entry_num:Mipi host index; mipi host索引;range:[0, 3],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_disable_mclk(uint32_t entry_num);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_extern_isp_reset(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_extern_isp_poweroff(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_extern_isp_poweron(uint32_t port);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Access sensor through i2c; 通过i2c访问sensor
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要读取的寄存器地址
 * @param[out] None
 *
 * @retval > 0: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_read(uint32_t port, uint32_t reg_addr);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要读取的寄存器地址
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_read_byte(uint32_t port, uint32_t reg_addr);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Write sensor register through i2c; 通过i2c写入sensor寄存器
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要写入的寄存器地址
 * @param[in] uint16_t value:Indicates the value written;表示写入的值
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_write(uint32_t port, uint32_t reg_addr, uint16_t value);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要写入的寄存器地址
 * @param[in] uint16_t value:Indicates the value written;表示写入的值
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_write_byte(uint32_t port, uint32_t reg_addr, uint8_t value);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t subdev: device; 写入的设备;range:[0, 3000000],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要写入的寄存器地址
 * @param[in] char *buffer:address to access; 表示写入的值
 * @param[in] uint32_t size:Indicates the value written;表示写入的大小
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_block_write(uint32_t port, uint32_t subdev, uint32_t reg_addr, char *buffer, uint32_t size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t subdev: device; 写入的设备;range:[0, 3000000],default:0
 * @param[in] uint32_t reg_addr:i2c address to access; 表示要写入的寄存器地址
 * @param[in] uint32_t size:Indicates the value written;表示写入的大小
 * @param[out] char *buffer:address to access; 表示读取的值
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_i2c_block_read(uint32_t port, uint32_t subdev, uint32_t reg_addr, char *buffer, uint32_t size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t subdev: device; 写入的设备;range:[0, 3000000],default:0
 * @param[in] uint32_t reg_addr:spi address to access; 表示要写入的寄存器地址
 * @param[in] char *buffer:address to access; 表示写入的值
 * @param[in] uint32_t size:Indicates the value written;表示写入的大小
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_spi_block_write(uint32_t port, uint32_t subdev, uint32_t reg_addr, char *buffer, uint32_t size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint32_t subdev: device; 写入的设备;range:[0, 3000000],default:0
 * @param[in] uint32_t reg_addr:spi address to access; 表示要写入的寄存器地址
 * @param[in] uint32_t size:Indicates the value written;表示写入的大小
 * @param[out] char *buffer:address to access; 表示读取的值
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_spi_block_read(uint32_t port, uint32_t subdev, uint32_t reg_addr, char *buffer, uint32_t size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Reset the ipi path operation of the specified mipi, which can be used to switch the specified ipi data path; 复位指定mipi的ipi通路操作,可用于开关指定ipi数据通路
 *
 * @param[in] uint32_t entry_num:Mipi host index; mipi host索引;range:[0, 3],default:0
 * @param[in] uint32_t ipi_index:ipi index inside of Mipi host ; mipi host内ipi索引;range:[0, 3],default:0
 * @param[in] uint32_t enable:Ipi switch status: 0-off, 1-on; ipi开关状态: 0-关, 1-开;range:[0, 1],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_ipi_reset(uint32_t entry_num, uint32_t ipi_index, uint32_t enable);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get sensor information; 获取sensor信息
 *
 * @param[in] uint32_t port:Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] uint8_t type:Type of parameter; 参数的类型
 * @param[out] cam_parameter_t *sp:Gets the address of the parameter;获取的参数的地址
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_sns_info(uint32_t port, cam_parameter_t *sp, uint8_t type);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get sensor information; 获取sensor信息
 *
 * @param[in] uint32_t port:Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[out] camera_staus_t *statinfo:Gets the address of the parameter;获取的参数的地址
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_get_status(uint32_t port, struct cam_statinfo *info);

/**
 * @NO{S09E06C01}
 * @ASIL{B}
 * @brief parse camera embed data;获取sensor信息曝光参数等
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] char* embed_raw: data to be parsed;待解析的数据
 * @param[out] struct embed_data_info_s *embed_info: pared data information;解析好的数据信息
 *
 * @retval zero: Success
 * @retval less than zero: Fail, return error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_parse_embed_data(uint32_t port, char *embed_raw, struct embed_data_info_s *embed_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief set event callback function;设置事件回调函数
 *
 * @param[in] uint32_t port: Corresponding to the port set in the configuration file; 和配置文件中设置的port 相对应;range:[0, 23],default:0
 * @param[in] void (*event_callback)(cam_event_t* fault_info): callback function handler;回调函数指针
 * @param[out] None
 *
 * @retval zero: Success;成功
 * @retval less than zero: Fail, return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_cam_set_event_callback(uint32_t port, void (*event_callback)(cam_event_t *fault_info));

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Initialize all pipelines configured in the configuration file according to the incoming configuration file, including isp&pym&gdc, CIM and mipi configurations; 根据传入的配置文件初始化配置文件所配置的所有pipeline,包括 isp & pym & gdc,CIM和mipi配置
 *
 * @param[in] const char *cfg_file: The absolute path of the vpm configuration file. The path length should not exceed 256 bytes;vpm 配置文件绝对路径,路径长度不要超过256字节.
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VpmInitStatus:vpm init status;vpm初始化状态
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_init(const char *cfg_file);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief De-initialize all initialized pipelines and release the resources of the initialization request; 对初始化的所有pipeline进行反初始化并释放初始化申请的资源.
 *
 * @param[in] None
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VpmInitStatus:vpm init status;vpm初始化状态
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_deinit(void);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable corresponding pipeline; 使能对应pipeline
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VpmInitStatus:vpm init status;vpm初始化状态
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_start_pipeline(uint32_t pipeline_id);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief disable corresponding pipeline; 停止对应pipeline
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VpmInitStatus:vpm init status;vpm初始化状态
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_stop_pipeline(uint32_t pipeline_id);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_CALLBACK_TYPE_E type: callback type;回调类型
 * @param[in] data_cb cb:call back function;回调函数指针
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_set_callbacks(uint32_t pipeline_id, VIO_CALLBACK_TYPE_E type, data_cb cb);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_INFO_TYPE_E info_type:type to set;要设置的参数类型;
 * @param[in] void *info:information to be set;要设置的参数信息
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_set_param(uint32_t pipeline_id, VIO_INFO_TYPE_E info_type, void *info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get the parameters of the corresponding pipeline through info_type; 通过info_type获取对应pipeline的参数。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_INFO_TYPE_E info_type:Parameter type to obtain, type description: HB_VIO_ISP_IMG_INFO, ISP memory information; HB_VIO_PYM_V3_IMG_INFO, PYM memory information
 * @param[in] VIO_INFO_TYPE_E info_type:要获取的参数类型,类型说明:HB_VIO_ISP_IMG_INFO, ISP内存信息;HB_VIO_PYM_V3_IMG_INFO,PYM内存信息
 *
 * @param[out] void *info:Parameters to be obtained; 需要获取的参数。
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_get_param(uint32_t pipeline_id, VIO_INFO_TYPE_E info_type, void *info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Obtain the data of the corresponding pipeline through the corresponding datatype;; 通过对应data_type获取对应pipeline_id的数据;
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_DATA_TYPE_E data_type:需要获取的数据类型;data_type类型说明:
 * HB_VIO_PYM_DATA_V3
 * 获取 pym 处理结果,J6最常用类型;
 * HB_VIO_ISP_YUV_DATA
 * 获取isp输出yuv数据,需要配合配置文件中isp_dma_output_format参数设置;
 * HB_VIO_ISP_RAW_DATA
 * 获取isp输出raw数据,需要配合配置文件中isp_dma_output_format参数设置;
 *
 * @param[in] VIO_DATA_TYPE_E data_type:The type of data to be obtained; data_ Type description:
 * HB_VIO_PYM_DATA_V3
 * Get pym processing results. J6 is the most commonly used type;
 * HB_VIO_ISP_YUV_DATA
 * To obtain the yuv data output by the isp, you need to cooperate with isp_dma_output_format parameter settings in the configuration file;
 * HB_VIO_ISP_RAW_DATA
 * To obtain the raw data output by the isp, you need to cooperate with isp_dma_output_format parameter settings in the configuration file;
 * @param[out] void *data:The data to be obtained, and the data type corresponds to the datatype; 需要获取的数据,数据类型和data_type对应
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_get_data(uint32_t pipeline_id, VIO_DATA_TYPE_E data_type, void *data);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Get the data of the corresponding pipelineid conditionally through the corresponding datatype and the set times parameter; 通过对应data_type以及设置的times参数有条件的获取对应pipeline_id的数据;
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_DATA_TYPE_E data_type:需要获取的数据类型:data_type类型说明:HB_VIO_PYM_DATA_V3:获取 pym 处理结果,J6最常用类型;
 * @param[in] VIO_DATA_TYPE_E data_type:The type of data to be obtained; data_ Type description: HB_VIO_PYM_DATA_V3,Get pym processing results. J6 is the most commonly used type;
 * @param[in] int32_t times:设置需要获取帧的相对时间;
 * times参数说明:
 * times = 0:清空当前缓存帧,等待下一帧;
 * times > 0:查找缓存帧中满足当前时间-time要求的最早帧;
 * times < 0:清空当前缓存帧,等待当前时间 – time之后的那一帧;
 * @param[in] int32_t times:Set the relative time to acquire frames;
 * Time parameter description:
 * times = 0:Clear the current cache frame and wait for the next frame;
 * times > 0:Find the earliest frame in the cache that meets the current time-time requirement;
 * times < 0:Clear the current cache frame and wait for the frame after the current time – time;
 * range:[-1056, 1056],default:0
 * @param[out] void *data:The data to be obtained, and the data type corresponds to the datatype; 需要获取的数据,数据类型和data_type对应
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_get_data_conditional(uint32_t pipeline_id, VIO_DATA_TYPE_E data_type, void *data, int32_t times);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable pym to process the reinjection data of the corresponding pipeline; 使能pym处理对应pipeline的回灌数据.
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * src_img_info:Pym memory to be processed; 需要处理的pym内存;
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_pym(uint32_t pipeline_id, hb_vio_buffer_t *src_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * dst_img_info:ipu memory to be freed; 需要free的ipu内存;
 * @param[out] None
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_free_ipubuf(uint32_t pipeline_id, hb_vio_buffer_t *dst_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Release the isp data corresponding to pipelineid, and hb_vio_get_data is used to obtain the isp data; 释放对应pipeline_id的isp数据,和hb_vio_get_data获取isp数据对应使用.
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * dst_img_info:isp memory to be freed; 需要free的isp内存;
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_free_ispbuf(uint32_t pipeline_id, hb_vio_buffer_t *dst_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Release the pym data corresponding to pipelineid, and hb_vio_get_data is used to obtain the pym data; 释放对应pipeline_id的pym数据,和hb_vio_get_data获取pym数据对应使用.
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] VIO_DATA_TYPE_E data_type:Released data type, type description: HB_VIO_PYM_DATA_V3, J6 most commonly used type;
 * @param[in] VIO_DATA_TYPE_E data_type:释放的数据类型, 类型说明: HB_VIO_PYM_DATA_V3, J6常用;
 * @param[in] void * dst_img_info:pym memory to be freed; 需要free的pym内存;
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_free_pymbuf(uint32_t pipeline_id, VIO_DATA_TYPE_E data_type, void *img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Generate the cfg bin file required for the work of the gdc module; 生成gdc模块的工作所需的cfg bin文件
 *
 * @param[in] param_t *gdc_parm:Corresponding parameters of gdc, including resolution, format, etc; gdc对应参数,包括分辨率,格式等
 * @param[in] window_t *wnds:Gdc internal region parameter; gdc内部区域参数
 * @param[in] uint32_t wnd_num:window number; window 数目;range:[1, 65536],default:1
 * @param[out] cfg_buf:Generated gdc cfg bin, internal allocation; 生成的gdc cfg bin,内部分配
 * @param[out] cfg_size:Size of gdc cfg bin file; gdc cfg bin文件的大小
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_gen_gdc_cfg(param_t *gdc_parm, window_t *wnds, uint32_t wnd_num, void **cfg_buf, uint64_t *cfg_size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Set cfg bin of gdc module; 设置gdc模块的cfg bin
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] cfg_buf:config buffer of gdc cfg bin; gdc cfg bin 的buffer
 * @param[in] cfg_size:size of gdc cfg bin ; gdc cfg bin文件的大小
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_set_gdc_cfg(uint32_t pipeline_id, uint32_t *cfg_buf, uint64_t cfg_size);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Set cfg bin of gdc module; 设置gdc模块的cfg bin
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] cfg_buf:config buffer of gdc cfg bin; gdc cfg bin 的buffer
 * @param[in] cfg_size:size of gdc cfg bin ; gdc cfg bin文件的大小
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_set_gdc_cfg_opt(uint32_t pipeline_id, uint32_t gdc_id, uint32_t *cfg_buf, uint64_t cfg_size); //comp xj3

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Release the buffer of the production gdc module cfg bin; 释放生产gdc模块cfg bin的buffer
 *
 * @param[in] uint32_t* cfg_buf:Buffer of gdc cfg bin; gdc cfg bin的buffer.
 * @param[out] None
 *
 * @retval None
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
void hb_vio_free_gdc_cfg(uint32_t *cfg_buf);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable gdc corresponding to pipelineid to correct the process distortion of src data; 使能对应pipeline_id的gdc,对src数据进程畸变矫正。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * src_img_info:Input image memory needed to process gdc;需要处理gdc的输入图像内存;
 * @param[in] int32_t rotate:Indicates the rotation angle to be processed, and supports an angle of 0,90,180,270;表示需要处理的旋转角度,支持角度0,90,180,270;
 * @param[out]  hb_vio_buffer_t * dst_img_info:Out image memory of gdc after process;需要处理gdc的输出图像内存;
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_gdc(uint32_t pipeline_id, hb_vio_buffer_t *src_img_info, hb_vio_buffer_t *dst_img_info,
		       int32_t rotate);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable gdc corresponding to pipelineid to correct the process distortion of src data; 使能对应pipeline_id的gdc,对src数据进程畸变矫正。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] uint32_t gdc_id:gdc hardware id ; gdc 硬件id;range:[0, 1],default:0
 * @param[in] hb_vio_buffer_t * src_img_info:Input image memory needed to process gdc;需要处理gdc的输入图像内存;
 * @param[in] int32_t rotate:Indicates the rotation angle to be processed, and supports an angle of 0,90,180,270;表示需要处理的旋转角度,支持角度0,90,180,270;
 * @param[out]  hb_vio_buffer_t * dst_img_info:Out image memory of gdc after process;需要处理gdc的输出图像内存;
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_gdc_opt(uint32_t pipeline_id, uint32_t gdc_id, hb_vio_buffer_t *src_img_info,
			   hb_vio_buffer_t *dst_img_info, int32_t rotate);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable gdc corresponding to pipelineid to correct the process distortion of src data; 使能对应pipeline_id的gdc,对src数据进程畸变矫正。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] uint32_t gdc_id:gdc hardware id ; gdc 硬件id;range:[0, 1],default:0
 * @param[in] const gdc_config_t *gdc_cfg:User's gdc configuration ; 用户的gdc配置
 * @param[in] hb_vio_buffer_t * src_img_info:Input image memory needed to process gdc;需要处理gdc的输入图像内存;
 * @param[in] int32_t rotate:Indicates the rotation angle to be processed, and supports an angle of 0,90,180,270;表示需要处理的旋转角度,支持角度0,90,180,270;
 * @param[out]  hb_vio_buffer_t * dst_img_info:Out image memory of gdc after process;需要处理gdc的输出图像内存;
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_gdc_adv(uint32_t pipeline_id, uint32_t gdc_id, const gdc_config_t *gdc_cfg,
			   hb_vio_buffer_t *src_img_info, hb_vio_buffer_t *dst_img_info, int32_t rotate);
/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Enable gdc corresponding to pipelineid to correct the process distortion of src data; 使能对应pipeline_id的gdc,对src数据进程畸变矫正。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] uint32_t gdc_id]:gdc hardware id ; gdc 硬件id;range:[0, 1],default:0
 * @param[in] const gdc_config_t *gdc_cfg:User's gdc configuration ; 用户的gdc配置
 * @param[in] hb_vio_buffer_t * src_img_info:Input image memory needed to process gdc;需要处理gdc的输入图像内存;
 * @param[in] int32_t rotate:Indicates the rotation angle to be processed, and supports an angle of 0,90,180,270;表示需要处理的旋转角度,支持角度0,90,180,270;
 * @param[out]  hb_vio_buffer_t * dst_img_info:Out image memory of gdc after process,allocated by user;需要处理gdc的输出图像内存,用户自行分配;
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_gdc_adv_user(uint32_t pipeline_id, uint32_t gdc_id, const gdc_config_t *gdc_cfg,
				const hb_vio_buffer_t *src_img_info, hb_vio_buffer_t *dst_img_info, int32_t rotate);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Release the gdc data corresponding to pipelineid, and hb_vio_get_data is used to obtain the gdc data; 释放对应pipeline_id的gdc数据,和hb_vio_get_data获取gdc数据对应使用.
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * dst_img_info:gdc memory to be freed; 需要free的gdc内存;
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_free_gdcbuf(uint32_t pipeline_id, hb_vio_buffer_t *dst_img_info);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] hb_vio_buffer_t * raw_img:raw memory to be dump; 需要dump的图像;
 * @param[out] hb_vio_buffer_t * yuv:yuv memory to be dump; 需要dump的图像;
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_raw_dump(uint32_t pipeline_id, hb_vio_buffer_t *raw_img, hb_vio_buffer_t *yuv);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Not support; 不支持
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] hb_vio_buffer_t * feedback_src:feedback_src memory to be feedback; 需要回灌的图像;
 * @param[out] hb_vio_buffer_t * isp_dst_yuv:isp_dst_yuv memory to be feedback; 需要回灌的图像;
 *
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_raw_feedback(uint32_t pipeline_id, hb_vio_buffer_t *feedback_src, hb_vio_buffer_t *isp_dst_yuv);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief After the video system is initialized, hb_vio_get_datag obtain the isp raw reinjection address and reinjection the external RAW image into the acquired address, enabling isp to process the reinjection data.; 视频系统初始化后,通过hb_vio_get_data获取isp raw 回灌地址并将外部RAW图像回灌到获取的地址中,使能isp 对回灌数据进行处理。
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[in] hb_vio_buffer_t * feedback_src:Input image memory needed to process isp;需要处理isp的输入图像内存;
 * @param[in] int32_t timeout: timeout of process ; 处理的容忍时间;range:[0, 2147483647],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated g_VpmInitStatus:vpm init status;vpm初始化状态
 * @compatibility HW: X3/J3/J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_run_raw(uint32_t pipeline_id, hb_vio_buffer_t *feedback_src, int32_t timeout);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Check whether the vpm&vin configuration file parameters are correct; 
 *
 * @param[in] const char* vpm_file: The absolute path of the vpm configuration file
 * @param[in] const char* vin_file: The absolute path of the vin configuration file
 * @param[in] uint32_t cfg_index:  The configure index of vin configuration file
 * @param[out] None
 *
 * @retval zero: Success
 * @retval less than zero: Fail, return error code
 *
 * @data_read None
 * @data_updated g_vpm_cfg;g_vin_cfg
 * @compatibility HW: J5/X5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_vio_cfg_check(const char *vpm_file, const char *vin_file, uint32_t cfg_index);
/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief pause the CIM data flow of the specified software channel; 暂停指定软件通道的CIM数据流
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */

int32_t hb_vio_pause_pipeline(uint32_t pipeline_id);
/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief resume the CIM data flow of the specified software channel; 恢复指定软件通道的CIM数据流
 *
 * @param[in] uint32_t pipeline_id:pipeline id ; 软件通道id;range:[0, 23],default:0
 * @param[out] None
 *
 * @retval E_OK: Success;成功
 * @retval E_NOT_OK: Fail,return error code;失败,返回错误码;range:[-10000,-1]
 *
 * @data_read g_multi_flag:multi process flag;多进程共享处理标志
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */

int32_t hb_vio_resume_pipeline(uint32_t pipeline_id);

#ifdef __cplusplus
}
#endif

#endif // HB_VIO_INTERFACE_H_
