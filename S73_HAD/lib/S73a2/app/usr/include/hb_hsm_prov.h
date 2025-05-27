/**
 * @file hb_hsm_prov.h
 *
 * @NO{S06E11C08}
 *
 * @ASIL{B}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 */
#ifndef HOBOT_HSM_PROV_H
#define HOBOT_HSM_PROV_H

#include <stdint.h>

#define PROV_DEBUG_MODE (0u)
#define PROV_RELEASE_MODE (1u)

#define FW_TYPE_HSMFW (0xD3)
#define FW_TYPE_HSMRCA (0xD4)

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief hsm prove efuse keys interface
 *
 * @retval =0: success
 * @retval !=0: failure
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
int32_t hb_hsm_prov_key(void);
/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief prov hsm fw interface, unuse and reseverd
 *
 * @param[in] type: fw type
 * @param[in] fw_addr: fw addr to be prov
 * @param[in] fw_size: fw size
 *
 * @retval =0: success
 * @retval !=0: failure
 *
 * @data_read None
 * @data_read sample_data_read1: desc for sample_data_read1
 * @data_updated sample_data_updated1: desc for sample_data_updated1
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_hsm_prov_fw(uint32_t type, uint8_t *fw_addr, uint32_t fw_size);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief prov fw finish
 *
 * @retval =0: success
 * @retval !=0: failure
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
int32_t hb_hsm_prov_fw_finish(void);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief set hsm prov mode
 *
 * @param[in] mode: prov mode ,PROV_DEBUG_MODE or PROV_RELEASE_MODE
 *
 * @retval =0: success
 * @retval !=0: failure
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
int32_t hb_hsm_prov_fw_set_mode(uint32_t mode);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief prov disable fake mode
 *
 * @retval =0: success
 * @retval !=0: failure
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
int32_t hb_hsm_prov_disable_fakemode(void);

#endif
