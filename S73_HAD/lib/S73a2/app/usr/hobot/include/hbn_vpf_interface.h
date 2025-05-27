/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2020 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef __HBN_VPF_INTERFACE_H__
#define __HBN_VPF_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <hb_mem_mgr.h>
#include "hbn_error.h"

hobot_status hbn_vnode_open(hb_vnode_type vnode_type, uint32_t hw_id, int32_t ctx_id, hbn_vnode_handle_t *vnode_fd);
hobot_status hbn_vnode_close(hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vnode_set_attr(hbn_vnode_handle_t vnode_fd, void *attr);
hobot_status hbn_vnode_get_attr(hbn_vnode_handle_t vnode_fd, void *attr);
hobot_status hbn_vnode_set_attr_ex(hbn_vnode_handle_t vnode_fd, void *attr);
hobot_status hbn_vnode_get_attr_ex(hbn_vnode_handle_t vnode_fd, void *attr);
hobot_status hbn_vnode_set_ochn_attr(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, void *attr);
hobot_status hbn_vnode_set_ochn_attr_ex(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, void *attr);
hobot_status hbn_vnode_get_ochn_attr(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, void *attr);
hobot_status hbn_vnode_set_ichn_attr(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id, void *attr);
hobot_status hbn_vnode_set_ichn_attr_ex(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, void *attr);
hobot_status hbn_vnode_get_ichn_attr(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id, void *attr);
hobot_status hbn_vnode_enable_ichn(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id);
hobot_status hbn_vnode_disable_ichn(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id);
hobot_status hbn_vnode_enable_ochn(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id);
hobot_status hbn_vnode_disable_ochn(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id);
hobot_status hbn_vnode_set_ochn_buf_attr(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id,
					 hbn_buf_alloc_attr_t *alloc_attr);
hobot_status hbn_vnode_start(hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vnode_reset(hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vnode_stop(hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vnode_get_fd(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, int32_t *fd);

hobot_status hbn_vnode_getframe(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, uint32_t millisecondTimeout,
				hbn_vnode_image_t *out_img); // block function;
hobot_status hbn_vnode_getframe_cond(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, uint32_t millisecondTimeout,
				     int32_t cond_time, hbn_vnode_image_t *out_img); // block function;
hobot_status hbn_vnode_getframe_group(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, uint32_t millisecondTimeout,
				      hbn_vnode_image_group_t *out_img); // block function;
hobot_status hbn_vnode_getframe_group_cond(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, uint32_t millisecondTimeout,
					   int32_t cond_time, hbn_vnode_image_group_t *out_img); // block function;
hobot_status hbn_vnode_sendframe(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id,
				 hbn_vnode_image_t *img); // 33ms block function
hobot_status hbn_vnode_sendframe_async(hbn_vnode_handle_t vnode_fd, uint32_t ichn_id,
				       hbn_vnode_image_t *img); // no block function
hobot_status hbn_vnode_releaseframe(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, hbn_vnode_image_t *img);
hobot_status hbn_vnode_releaseframe_group(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id,
					  hbn_vnode_image_group_t *img_group);

hobot_status hbn_vflow_create(hbn_vflow_handle_t *vflow_fd);
hobot_status hbn_vflow_destroy(hbn_vflow_handle_t vflow_fd);
hobot_status hbn_vflow_create_cfg(const char *cfg_file, hbn_vflow_handle_t *vflow_fd);
hobot_status hbn_vflow_add_vnode(hbn_vflow_handle_t vflow_fd, hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vflow_del_vnode(hbn_vflow_handle_t vflow_fd, hbn_vnode_handle_t vnode_fd);
hobot_status hbn_vflow_bind_vnode(hbn_vflow_handle_t vflow_fd, hbn_vnode_handle_t src_vnode_fd, uint32_t out_chn,
				  hbn_vnode_handle_t dst_vnode_fd, uint32_t in_chn);
hobot_status hbn_vflow_unbind_vnode(hbn_vflow_handle_t vflow_fd, hbn_vnode_handle_t src_vnode_fd, uint32_t out_chn,
				    hbn_vnode_handle_t dst_vnode_fd, uint32_t in_chn);
hobot_status hbn_vflow_start(hbn_vflow_handle_t vflow_fd);
hobot_status hbn_vflow_stop(hbn_vflow_handle_t vflow_fd);
hobot_status hbn_vflow_pause(hbn_vflow_handle_t vflow_fd);
hobot_status hbn_vflow_resume(hbn_vflow_handle_t vflow_fd);
hobot_status hbn_vflow_get_version(hbn_version_t *version);
hbn_vnode_handle_t hbn_vflow_get_vnode_handle(hbn_vflow_handle_t vflow_fd, hb_vnode_type vnode_type, uint32_t vnode_config_index);

int32_t hbn_gen_gdc_cfg(const param_t *gdc_param, const window_t *windows, uint32_t wnd_num, void **cfg_buf,
			uint64_t *cfg_size);
int32_t hbn_free_gdc_cfg(uint32_t *cfg_buf);

hobot_status hbn_get_codec_channel_idx(hbn_vnode_handle_t vnode_fd, int32_t encoder, int32_t *channel_idx);
hobot_status hbn_vnode_set_output_frame(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, hbn_vnode_image_t *img);
hobot_status hbn_vnode_set_output_groupframe(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id,
	hbn_vnode_image_group_t *img_group);
hobot_status hbn_vnode_sendframe_group(hbn_vnode_handle_t vnode_fd,
	uint32_t ichn_id, hbn_vnode_image_group_t *img_group);
hobot_status hbn_vnode_get_output_groupframe(hbn_vnode_handle_t vnode_fd,
	uint32_t ochn_id, hbn_vnode_image_group_t *img_group);
hobot_status hbn_vnode_get_output_frame(hbn_vnode_handle_t vnode_fd, uint32_t ochn_id, hbn_vnode_image_t *img);
hobot_status hbn_vflow_get_fd(hbn_vflow_handle_t *vflow_fd);
hobot_status hbn_vnode_set_ctrl(hbn_vnode_handle_t vnode_fd, vpf_ext_ctrl_t *ext_ctrl);
hobot_status hbn_vnode_get_ctrl(hbn_vnode_handle_t vnode_fd, vpf_ext_ctrl_t *ext_ctrl);
int32_t vnode_get_mode(hbn_vnode_handle_t vnode_fd);

#ifdef __cplusplus
}
#endif

#endif
