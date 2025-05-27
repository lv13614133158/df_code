/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2019 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef __HB_ISP_INTERNAL_H__
#define __HB_ISP_INTERNAL_H__

#include "hb_comm_isp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

//coverity[misra_c_2012_rule_1_1_violation:SUPPRESS], ## violation reason SYSSW_V_1.1_01
typedef int64_t hbn_vnode_handle_t;

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t set_isp_pipe(uint32_t pipeline_id, hbn_vnode_handle_t p_isp_fd);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t clear_isp_pipe(uint32_t pipeline_id, hbn_vnode_handle_t p_isp_fd);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t hb_isp_write_reg(uint32_t pipeline_id, const isp_reg_t *isp_reg);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t hb_isp_read_reg(uint32_t pipeline_id, isp_reg_t *isp_reg);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t hb_isp_set_raw_select(uint32_t isp_pipe, uint32_t raw_select);

extern int32_t hbn_isp_set_calibration_param(hbn_vnode_handle_t vnode_fd, const char *name, uint32_t param_type,
					     uint32_t param_size, void *ptr);
extern int32_t hbn_isp_get_calibration_param(hbn_vnode_handle_t vnode_fd, const char *name, uint32_t param_type,
					     uint32_t param_size, void *ptr);
extern int32_t hbn_isp_set_command_param(hbn_vnode_handle_t vnode_fd, uint32_t section, uint32_t command,
					 uint32_t data);
extern int32_t hbn_isp_get_command_param(hbn_vnode_handle_t vnode_fd, uint32_t section, uint32_t command,
					 uint32_t *data);
extern int32_t hbn_isp_get_hardware_param(hbn_vnode_handle_t vnode_fd, const char *name, uint32_t param_size,
					  uint32_t *ptr);
extern int32_t hbn_isp_set_hardware_param(hbn_vnode_handle_t vnode_fd, const char *name, uint32_t param_size,
					  uint32_t *ptr);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t get_isp_pipe(uint32_t pipeline_id, hbn_vnode_handle_t *p_isp_fd);

//coverity[misra_c_2012_rule_8_6_violation:SUPPRESS], ## violation reason SYSSW_V_8.6_01
extern int32_t get_ynr_fd_by_pipe(uint32_t pipeline_id, hbn_vnode_handle_t *p_ynr_fd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
