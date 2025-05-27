#ifndef __BOSCH_DESERIALIZER_INTERFACE_H__
#define __BOSCH_DESERIALIZER_INTERFACE_H__

#include "hb_camera_data_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write the data to a register.
 *
 * @param[in]   deviceIndex       Index of the device.
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[in]   dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval  0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_des_set_register_value(uint32_t const deviceIndex,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Read the data from the register.
 *
 * @param[in]   deviceIndex       Index of the device.
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[out]  dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_des_get_register_value(uint32_t const deviceIndex,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Write the data to a register.
 *
 * @param[in]   deviceIndex       Index of the device.
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[in]   dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_poc_set_register_value(uint32_t const deviceIndex,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Read the data from the register.
 *
 * @param[in]   deviceIndex       Index of the device.
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[out]  dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_poc_get_register_value(uint32_t const deviceIndex,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BOSCH_DESERIALIZER_INTERFACE_H__ */