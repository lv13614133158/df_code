/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2022 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/

#ifndef HB_API_ISP_H_
#define HB_API_ISP_H_

#include "hb_comm_isp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set 2a manual on/off; 设置算法manual模式
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id：range：[0, 15]，default：0
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_run_algo(uint32_t pipeline_id);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get 2a manual on/off status; 设置算法auto模式
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_pause_algo(uint32_t pipeline_id);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief control isp modual bypass or not; 提供设置ISP子模块bypass与否的接口
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_module_ctrl_u *mod_ctrl: module control value; 设置ISP内部模块运行与否状态
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_module_control(uint32_t pipeline_id, const isp_module_ctrl_u *mod_ctrl);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get isp modual bypass status; 获取设置ISP子模块bypass与否状态的接口
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] isp_module_ctrl_u *mod_ctrl: module control value; 获取ISP内部模块运行与否状态
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_module_control(uint32_t pipeline_id, isp_module_ctrl_u *mod_ctrl);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get ae statistics; 获取当前通路的ae统计数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] int32_t time_out: timeout value; 接口超时时间; range：[0, 2147483647], default:3000
 * @param[out] isp_statistics_t *ae_statistics: ae statistics; ae统计数据
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_ae_statistics(uint32_t pipeline_id, isp_statistics_t *ae_statistics, int32_t time_out);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief relese ae statistics; 释放已获取的当前通路的ae统计数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_statistics_t *ae_statistics: ae statistics; ae统计数据
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_release_ae_statistics(uint32_t pipeline_id, isp_statistics_t *ae_statistics);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get awb statistics; 获取当前通路的awb统计数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] int32_t time_out: timeout value; 接口超时时间; range：[0, 2147483647], default:3000
 * @param[out] isp_statistics_t *awb_statistics: awb statistics; awb统计数据
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_awb_statistics(uint32_t pipeline_id, isp_statistics_t *awb_statistics, int32_t time_out);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief release awb statistics; 释放已获取的当前通路的awb统计数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_statistics_t *awb_statistics: awb statistics; awb统计数据
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_release_awb_statistics(uint32_t pipeline_id, isp_statistics_t *awb_statistics);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set isp command with api and value; 动态设置ISP cmd的对应的参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_cmd_api_t *cmd_api: isp cmd api and data vale; 对应isp提供的cmd的id值和对应的参数
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_command(uint32_t pipeline_id, isp_cmd_api_t *cmd_api);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set isp context value; 动态设置isp ctx数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const isp_context_t *ptx: store context data point; isp ctx数据对应的地址，需外部提前申请好
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_context(uint32_t pipeline_id, const isp_context_t *ptx);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get isp context value; 动态获取isp ctx数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] const isp_context_t *ptx: store context data point; isp ctx数据对应的地址，需外部提前申请好
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_context(uint32_t pipeline_id, isp_context_t *ptx);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set isp ae info value; 设置isp ae相关参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] ae_info_t *ae_info:ae info value; ae info 参数
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_ae_info(uint32_t pipeline_id, const ae_info_t *ae_info);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get isp ae info value; 获取isp ae相关参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] ae_info_t *ae_info:ae info value; ae info参数
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_ae_info(uint32_t pipeline_id, ae_info_t *ae_info);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set isp awb info value; 设置isp awb相关参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] awb_info_t *awb_info: awb info value; awb参数
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_awb_info(uint32_t pipeline_id, const awb_info_t *awb_info);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get isp awb info value; 获取isp awb相关参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] awb_info_t *awb_info: awb info value; awb参数
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_awb_info(uint32_t pipeline_id, awb_info_t *awb_info);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get current isp,2a, calibration version; 获取当前系统的ISP版本，ISP算法版本和较准参数版本
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] char* isp_ver: isp系统软件版本
 * @param[out] char* algo_ver: 2a算法版本
 * @param[out] char* calib_ver: tuning参数的版本号，尺寸必须大于100byte
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_version(uint32_t pipeline_id, char *isp_ver, char *algo_ver, char *calib_ver);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get isp 2a info value; 获取isp 2a相关参数信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] int32_t time_out: timeout value; 接口超时时间; range：[0, 2147483647], default:3000
 * @param[out] isp_info_t *isp_info: isp 2a info; isp 2a统计数据信息
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_2a_info(uint32_t pipeline_id, isp_info_t *isp_info, int time_out);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get ae 5bin statustics value; 获取ae 5bin统计数据
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] isp_ae5bin_stats_t *isp_ae5bin_stats: ae 5bin statistics value; ae5bin统计数据
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_ae5bin_statistics(uint32_t pipeline_id, isp_ae5bin_stats_t *isp_ae5bin_stats);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get zone info value; 获取ae zone区域信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_info_type_e type: isp zone type; isp统计信息的类型
 * @param[out] isp_zone_info_t *zoneinfo:isp zone inof; isp 统计区域范围信息: range: [0, 15], default: 0
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_zone_info(uint32_t pipeline_id, uint8_t type, isp_zone_info_t *zoneinfo);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set histgram thresh info; 设置histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] isp_hist_thresh_info_t *isp_hist_thresh_info: isp hist thresh info; isp hist分区门限参数：range: [0, 255], default: 0
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_hist_thresh_info(uint32_t pipeline_id, isp_hist_thresh_info_t *isp_hist_thresh_info);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get histgram thresh info; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[out] isp_hist_thresh_info_t *isp_hist_thresh_info: isp hist thresh info; isp hist分区门限参数：range: [0, 255], default: 0
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_hist_thresh_info(uint32_t pipeline_id, isp_hist_thresh_info_t *isp_hist_thresh_info);


/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set calibration param; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const char *name：param name ; 参数名称；range：无，default：无
 * @param[in] uint32_t param_type: param type ; 参数类比；range：参数类比需查表
 * @param[in] uint32_t param_size：param size ; 参数尺寸；range：每组参数的大学不一样需查表
 * @param[in] uint32_t *ptr: data ptr; 数据指针：range: [1, 65535], default: 1
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_calibration_param(uint32_t pipeline_id, const char *name, uint32_t param_type,
					    uint32_t param_size, void *ptr);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get calibration param; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const char *name：param name ; 参数名称；range：无，default：无
 * @param[in] uint32_t param_type: param type ; 参数类比；range：参数类比需查表
 * @param[in] uint32_t param_size：param size ; 参数尺寸；range：每组参数的大学不一样需查表
 * @param[out] uint32_t *ptr: data ptr; 数据指针：range: [1, 65535], default: 1
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_calibration_param(uint32_t pipeline_id, const char *name, uint32_t param_type,
					    uint32_t param_size, void *ptr);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set command param; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] uint32_t section：section value ; 字段名称；range：无，default：无
 * @param[in] uint32_t command：command value; 命令名字；range：命令有对应的表格查找
 * @param[in] uint32_t *data: data ptr; 数据指针：range: [1, 65535], default: 1
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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

extern int32_t hb_isp_set_command_param(uint32_t pipeline_id, uint32_t section, uint32_t command, uint32_t data);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get command param; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] uint32_t section：section value ; 字段名称；range：无，default：无
 * @param[in] uint32_t command：command value; 命令名字；range：命令有对应的表格查找
 * @param[out] uint32_t *data: data ptr; 数据指针：range: [1, 65535], default: 1
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_command_param(uint32_t pipeline_id, uint32_t section, uint32_t command, uint32_t *data);

/**
 * @NO{S08E06C01}
 * @ASIL{B}
 * @brief get command range; 获取calibration 参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] uint32_t section: api section(not used) ; api section(目前没有实际使用)
 * @param[in] uint32_t command: command value ; command参数
 * @param[out] void *max: ptr max ; command max 数据指针
 * @param[out] void *min: ptr min ; command min 数据指针
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
 *
 * @data_read zone_info
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int32_t hb_isp_get_command_range(uint32_t pipeline_id, uint32_t section, uint32_t command, uint32_t *max, uint32_t *min);


/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief get hardware param; 获取histgram区间门限信息
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const char *name：param name ; 参数名称；range：无，default：无
 * @param[in] uint32_t param_size：param size ; 参数尺寸；range：每组参数的大学不一样需查表
 * @param[out] uint32_t *ptr: data ptr; 数据指针：range: [1, 65535], default: 1
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_get_hardware_param(uint32_t pipeline_id, const char *name, uint32_t param_size, uint32_t *ptr);

/**
 * @NO{S08E06C01I}
 * @ASIL{B}
 * @brief set hardware param; 设置hardware参数
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const char *name：param name ; 参数名称；range：无，default：无
 * @param[in] uint32_t param_size：param size ; 参数尺寸；range：每组参数的大学不一样需查表
 * @param[in] uint32_t *ptr: data ptr; 数据指针：range: [1, 65535], default: 1
 * @param[out] None
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
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
extern int32_t hb_isp_set_hardware_param(uint32_t pipeline_id, const char *name, uint32_t param_size, uint32_t *ptr);

/**
 * @NO{S08E06C01}
 * @ASIL{B}
 * @brief get hardware range; 获取hardware 参数范围
 *
 * @param[in] uint32_t pipeline_id：pipeline id ; 软件通道id；range：[0, 15]，default：0
 * @param[in] const char *name：param name ; 参数名称；range：无，default：无
 * @param[out] void *max: ptr max ; command max 数据指针
 * @param[out] void *min: ptr min ; command min 数据指针
 *
 * @retval zero: Success；成功
 * @retval less than zero: Fail，return error code；失败，返回错误码
 *
 * @data_read zone_info
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int32_t hb_isp_get_hardware_range(uint32_t pipeline_id, const char *name, uint32_t *max, uint32_t *min);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // HB_API_ISP_H_
