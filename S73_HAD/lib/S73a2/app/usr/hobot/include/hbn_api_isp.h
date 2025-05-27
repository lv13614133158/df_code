/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2019 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef __HBN_API_ISP_H__
#define __HBN_API_ISP_H__

#include "hb_comm_isp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern int32_t hbn_isp_set_algo(hbn_vnode_handle_t vnode_fd, isp_algo_type_e algo_type, opt_mode_e opt_mode);
extern int32_t hbn_isp_get_algo(hbn_vnode_handle_t vnode_fd, isp_algo_type_e algo_type, opt_mode_e *opt_mode);
extern int32_t hbn_isp_set_module_control(hbn_vnode_handle_t vnode_fd, isp_module_ctrl_u *mod_ctrl);
extern int32_t hbn_isp_get_module_control(hbn_vnode_handle_t vnode_fd, isp_module_ctrl_u *mod_ctrl);
extern int32_t hbn_isp_get_ae_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *ae_statistics,
					 int32_t time_out);
extern int32_t hbn_isp_release_ae_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *ae_statistics);
extern int32_t hbn_isp_get_awb_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *awb_statistics,
					  int32_t time_out);
extern int32_t hbn_isp_release_awb_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *awb_statistics);
extern int32_t hbn_isp_command(hbn_vnode_handle_t vnode_fd, isp_cmd_api_t *cmd_api);
extern int32_t hbn_isp_set_context(hbn_vnode_handle_t vnode_fd, const isp_context_t *ptx);
extern int32_t hbn_isp_get_context(hbn_vnode_handle_t vnode_fd, isp_context_t *ptx);
extern int32_t hbn_isp_set_ae_info(hbn_vnode_handle_t vnode_fd, ae_info_t *ae_info);
extern int32_t hbn_isp_get_ae_info(hbn_vnode_handle_t vnode_fd, ae_info_t *ae_info);
/*
 * note:
 * awb gain is the actual gain acting on the image. Since floating-point operation is not used,
 * the operation will lose some accuracy.
 * format: rgain  4.8; bgain 4.8
 * If you set rgain/bgain(hb_isp_set_awb_info) and than get rgain/bgain(hb_isp_get_awb_info), there will be errors.
 * The error is less than 2. eg. set rgain = 100, get rgain = 99.
 *
 */
extern int32_t hbn_isp_set_awb_info(hbn_vnode_handle_t vnode_fd, awb_info_t *awb_info);
extern int32_t hbn_isp_get_awb_info(hbn_vnode_handle_t vnode_fd, awb_info_t *awb_info);
extern int32_t hbn_isp_get_version(hbn_vnode_handle_t vnode_fd, char *isp_ver, char *algo_ver, char *calib_ver);
extern int32_t hbn_isp_get_2a_info(hbn_vnode_handle_t vnode_fd, isp_info_t *isp_info, int time_out);

extern int32_t hbn_isp_get_ae5bin_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *isp_ae5bin_stats, int32_t time_out);
extern int32_t hbn_isp_release_ae5bin_statistics(hbn_vnode_handle_t vnode_fd, isp_statistics_t *isp_ae5bin_stats);

extern int32_t hbn_isp_set_hist_thresh_info(hbn_vnode_handle_t vnode_fd, isp_hist_thresh_info_t *isp_hist_thresh_info);
extern int32_t hbn_isp_get_hist_thresh_info(hbn_vnode_handle_t vnode_fd, isp_hist_thresh_info_t *isp_hist_thresh_info);
extern int32_t hbn_isp_get_zone_info(hbn_vnode_handle_t vnode_fd, isp_info_type_e type, isp_zone_info_t *zoneinfo);
/**
 * @NO{S08E06C02}
 * @ASIL{B}
 * @brief get calibration param; 获取calibration 参数
 *
 * @param[in] hbn_vnode_handle_t vnode_fd:vnode fd; vnode设备节点fd值: range: [0, 2147483647], default: 0
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
 * @compatibility None
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int32_t hbn_isp_get_command_range(hbn_vnode_handle_t vnode_fd, uint32_t section, uint32_t command, uint32_t *max, uint32_t *min);

/**
 * @NO{S08E06C02}
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
extern int32_t hbn_isp_get_hardware_range(hbn_vnode_handle_t vnode_fd, const char *name, uint32_t *max, uint32_t *min);
extern int32_t hbn_isp_get_pixel_consistency(hbn_vnode_handle_t vnode_fd, isp_statistics_t *pixel_consistency,
					      int32_t time_out);
extern int32_t hbn_isp_release_pixel_consistency(hbn_vnode_handle_t vnode_fd, isp_statistics_t *pixel_consistency);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
