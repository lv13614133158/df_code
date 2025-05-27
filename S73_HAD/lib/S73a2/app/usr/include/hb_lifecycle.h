/**
 * @file hobot_lifecycle.h
 *
 * @NO{S06E03C04}
 *
 * @ASIL{B}
 *
 */

#ifndef HOBOT_LIFECYCLE_H
#define HOBOT_LIFECYCLE_H

#include <stdint.h>


/**
 * @def lifecycle state
 */
enum lifecycle_state {
	LIFECYCLE_ATE = 0,
	LIFECYCLE_HKP,
	LIFECYCLE_RKG,
	LIFECYCLE_HIP,
	LIFECYCLE_OHP,
	LIFECYCLE_IFD,
	LIFECYCLE_RMA,
	LIFECYCLE_RIP
};

/**
 * @def lifecycle Auth data len
 */
#define LIFECYCLE_AUTH_NOUCE_SIZE (32U) /**< lifecycle auth nouce len */
#define LIFECYCLE_AUTH_IV_SIZE   (12U) /**< lifecycle auth iv len */
#define LIFECYCLE_AUTH_GMAC_SIZE (16U) /**< lifecycle auth gmac len */

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief read lifecycle state
 *
 * @param[out] state:lifecycle state
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
uint32_t hb_lifecycle_read(uint32_t *state);


uint32_t hb_debugctrl_read(uint32_t *state);
/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief write lifecycle, only can write to LIFECYCLE_OHP
 *
 * @param[in] state: lifecycle state to be write
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
uint32_t hb_lifecycle_write(const uint32_t state);

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief  write lifecycle
 *
 * @param[in] state: state to be write
 * @param[in] nouce: the nouce data to be verify
 * @param[in] nouce_size: nouce data size
 * @param[in] iv: iv data to be verify
 * @param[in] iv_size: iv data size
 * @param[in] gmac: gmac data to be verify
 * @param[in] gmac_size: gmac data size
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
uint32_t hb_lifecycle_auth_write(const uint32_t state, uint8_t *nouce,
				 uint32_t nouce_size, uint8_t *iv,
				 uint32_t iv_size, uint8_t *gmac,
				 uint32_t gmac_size);

#endif //HOBOT_LIFECYCLE_H
