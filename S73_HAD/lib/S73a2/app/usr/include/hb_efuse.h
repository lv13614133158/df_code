/**
 * @file hb_efuse.h
 *
 * @NO{S06E03C04}
 *
 * @ASIL{B}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 */

#ifndef HOBOT_EFUSE_H
#define HOBOT_EFUSE_H

#include <stdint.h>

/**
 * @def Efuse permission bit map
 */
#define EFUSE_READ_PERM_BIT 0x01 /**< efuse read permission bit */
#define EFUSE_WRITE_PERM_BIT 0x02 /**< efuse write permission bit */
#define EFUSE_LOCK_PERM_BIT 0x04 /**< efuse lock permission bit */
#define EFUSE_NO_PERMISSIONS 0x00 /**< efuse has no permission */

/**
 * @def Efuse Auth data len
 */
#define EFUSE_AUTH_NOUCE_SIZE (32U) /**< efuse auth nouce len */
#define EFUSE_AUTH_IV_SIZE    (12U)    /**< efuse auth iv len */
#define EFUSE_AUTH_GMAC_SIZE  (16U)  /**< efuse auth gmac len */

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief Efuse value read
 *
 * @param[in] bank: efuse bank to read
 * @param[out] value: read value
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
uint32_t hb_efuse_read(const uint32_t bank, uint32_t *value);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief write value to efuse bank
 *
 * @param[in] bank: efuse bank to write
 * @param[in] value: value to write
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
uint32_t hb_efuse_write(const uint32_t bank, const uint32_t value);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief lock efuse bank
 *
 * @param[in] bank:bank to lock
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
uint32_t hb_efuse_lock(const uint32_t bank);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief get bank permission
 *
 * @param[in] bank: efuse bank
 * @param[out] permission: the bank premission
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
uint32_t hb_efuse_get_permissions(const uint32_t bank, uint32_t *permission);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief get lock status
 *
 * @param[in] bank: efuse bank
 * @param[out] status: the lock status of bank
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
uint32_t hb_efuse_get_lock_status(const uint32_t bank, uint32_t *status);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief write host antirollback value with auth data
 *
 * @param[in] anti_num: the antirollback value to be write
 * @param[in] nouce: the nouce data to be verify
 * @param[in] nouce_size: nouce data size
 * @param[in] iv: iv data to be verify
 * @param[in] iv_size: iv data size
 * @param[in] gmac: gmac data to be verify
 * @param[in] gmac_size: gmac data size
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
uint32_t hb_efuse_host_anti_write(const uint32_t anti_num, uint8_t *nouce,
				  uint32_t nouce_size, uint8_t *iv,
				  uint32_t iv_size, uint8_t *gmac,
				  uint32_t gmac_size);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief read host anti rollback value
 *
 * @param[out] anti_num: host anti rollback value
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
uint32_t hb_efuse_host_anti_read(uint32_t *anti_num);

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief destroy efuse key
 *
 * @param[in] nouce: the nouce data to be verify
 * @param[in] nouce_size: nouce data size
 * @param[in] iv: iv data to be verify
 * @param[in] iv_size: iv data size
 * @param[in] gmac: gmac data to be verify
 * @param[in] gmac_size: gmac data size
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
uint32_t hb_efuse_destroy_key(uint8_t *nouce, uint32_t nouce_size,
			    uint8_t *iv, uint32_t iv_size,
			    uint8_t *gmac, uint32_t gmac_size);

uint32_t hb_efuse_hsm_anti_update(void);
uint32_t hb_efuse_hsm_anti_read(uint32_t *anti_num, bool efuse);

uint32_t hb_efuse_set_autodebug_mode(void);
uint32_t hb_efuse_set_normal_mode(void);

/**
 * @ASIL{B}
 * @brief read unique id
 *
 * @param[in] uid_buf: the buf to store unique id
 * @param[in] uid_buf_len: the length of uid_buf, byte
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
uint32_t hb_efuse_get_uid(uint8_t *uid_buf, uint8_t uid_buf_len);

#endif //HOBOT_EFUSE_H
