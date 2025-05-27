/**
 * @file hb_host_prov.h
 *
 * @NO{S06E11C08}
 *
 * @ASIL{B}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 */
#ifndef HOBOT_HOST_PROV_H
#define HOBOT_HOST_PROV_H

#include <stdint.h>

#define PROV_DEBUG_MODE (0u)
#define PROV_RELEASE_MODE (1u)

#define CHIPMODE_NORMAL_MODE (0u)
#define CHIPMODE_OSCCA_MODE (1u)

#define PROV_EFUSEMAP_PACK_BANKNUM (68u)

#define HOSTPROV_LOCK_AND_MASK_IS_NULL (0u)
#define HOSTPROV_LOCK_AND_MASK_NOT_NULL (1u)

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief host prov efuse map in hsm
 *
 * @param[in] efusemap: efuse map data ptr
 * @param[in] efusemap_size: efuse map size
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
int32_t hb_host_prov_efusemap(uint32_t *efusemap, uint32_t efusemap_size);
/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief host prov efuse map finish
 *
 * @param[in] efusemap: efuse map data ptr
 * @param[in] efusemap_size: efuse map size
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
int32_t hb_host_prov_finish(uint32_t *efusemap, uint32_t efusemap_size);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief
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
int32_t hb_host_prov_fw_set_mode(uint32_t mode);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief get chip mode
 *
 * @param[out] mode:chip mode ,1 for normal, 0 or oscca
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
int32_t hb_host_prov_get_chipmode(uint32_t *mode);

/**
 * @NO{S06E11C08}
 * @ASIL{B}
 * @brief get prov status
 *
 * @param[out] provsta:chip mode ,1 for normal, 0 or oscca
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
int32_t hb_host_prov_get_provsta(uint32_t *provsta);

#endif
