/**
 * @file hobot_hsm_update.h
 *
 * @NO{S06E03C04}
 *
 * @ASIL{B}
 *
 */

#ifndef HOBOT_HSM_UPDATE_H
#define HOBOT_HSM_UPDATE_H

#include <stdint.h>

/*hsm auth nouce size*/
#define NOUCE_SIZE 32
/*hsm nouce signature size*/
#define SIGNATURE_SIZE 64

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief hsm fw update init interface
 *
 * @param[in] fw_type: update fw type
 * @param[in] cert_addr: update auth cert addr
 * @param[in] cert_size: update auth cert size
 * @param[in] hsm_fw_addr: update hsm fw addr
 * @param[in] hsm_fw_size: update hsm fw size
 * @param[out] nouce: nouce data need to be signed
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
int32_t hb_hsm_fw_init(uint32_t fw_type, uint8_t *cert_addr, uint32_t cert_size,
		       uint8_t *hsm_fw_addr, uint32_t hsm_fw_size,
		       uint8_t *nouce);

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief verift auth data
 *
 * @param[in] fw_type: update fw type
 * @param[in] signature: the signature of nouce
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
int32_t hb_hsm_fw_auth(uint32_t fw_type, uint8_t *signature);

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief
 *
 * @param[in] fw_type: hsm fw type
 * @param[in] fw_buf: hsm fw buf
 * @param[in] fw_size: hsm fw size
 *
 * @retval =0: success
 * @retval <0: failure
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
int32_t hb_hsm_fw_recrypt(uint32_t fw_type, uint8_t *fw_buf, uint32_t fw_size);

#endif //HOBOT_HSM_UPDATE_H
