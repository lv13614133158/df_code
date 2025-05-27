/*
 * hbre/camsys/libvpf/src/vpf/idu/idu_vnode.h
 *
 * Copyright (C) 2020 horizon
 *
 *
 */

#ifndef IDU_VNODE_H_
#define IDU_VNODE_H_
#include "vpf_inter_interface.h"
#include "hbn_vpf_interface.h"
#include "hbn_idu_cfg_api.h"

//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t idu_vnode_open(vnode_entity_t *vnode);
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
int32_t idu_vnode_close(vnode_entity_t *vnode);
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
hbn_vnode_handle_t idu_vnode_init(void *idu);
//coverity[misra_c_2012_rule_8_5_violation:SUPPRESS], ## violation reason SYSSW_V_8.5_01
hbn_vnode_handle_t idu_vnode_cfg_init(void *root);
#endif //IDU_VNODE_H_