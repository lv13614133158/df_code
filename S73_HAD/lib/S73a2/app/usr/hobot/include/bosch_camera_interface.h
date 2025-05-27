/***************************************************************************
 *                      COPYRIGHT NOTICE
 *             Copyright 2024 BOSCH, Inc.
 *                     All rights reserved.
 ***************************************************************************/

/**
 * @file bosch_camera_interface.h
 *
 * @NO{S10E02C01}
 * @ASIL{B}
 */

#ifndef __BOSCH_CAMERA_INTERFACE_H__
#define __BOSCH_CAMERA_INTERFACE_H__

#include "hb_camera_data_config.h"
#include "hb_camera_data_info.h"
#include "hb_camera_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Reads from an EEPROM in the camera module
 *
 * @param[in] cam_fd    The camera module device handle.
 * @param[in] address   The EEPROM address (of type uint32_t) to read from. The valid ranges for this parameter are device-specific.
 * @param[in] length    The length (of type uint32_t) of the buffer, in bytes. Valid ranges are dependent on 'address' and are device specific.
 * @param[out] buffer	A buffer pointer (of type uint8_t) of at least 'length' bytes. Valid range : [non-NULL].
 *
 * @retval E_OK      On success
 * @retval E_NOT_OK  Error codes returned by driver implementations. (Failure)
 *
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int32_t hbn_cam_eeprom_read(camera_handle_t const cam_fd, uint32_t const address, uint32_t const length, uint8_t *const buffer);

/**
 * @NO{S09E06C01I}
 * @ASIL{B}
 * @brief Reads all link status from deserializer
 *
 * @param[in] deserial_index   The deserializer index
 * @param[out] lock_status    Store the deserializer lock status. Field description show below:
 *                             -isLockPinAsserted: Bool value. Set to true if deserializer lock pin asserted.
 *                             -linkEnableMask: Mask for link enable state.
 *                             -lockStatus: For each bit, 0: not locked, 1: locked. [0:3]: Link Lock, [4:7] Video Lock
 * @retval E_OK      On success
 * @retval E_NOT_OK  Error codes returned by driver implementations. (Failure)
 *
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int32_t hbn_des_get_lock_status(uint32_t const deserial_index, void *const lock_status);

/**
 * @brief do POC operation.
 *
 * This function get power switch channel state specified by deserial_idx
 * and stores the result in the `data` structure.
 *
 * @param[in] deserial_index   The deserializer index
 * @param[in] cmd_type command type.
 * @param[out] data Pointer to a structure that stores power switch state result.
 *
 * @return Returns 0 on success; otherwise, returns an error code.
 */
extern int32_t hbn_cam_read_channel_state(uint32_t const deserial_index, uint8_t const cmd_type, void *const data);

/**
 * @brief do POC operation.
 *
 * This function get power swicth voltage and current specified by cam_fd
 * and stores the result in the `data` structure.
 *
 * @param[in] cam_fd The camera fd.
 * @param[in] cmd_type command type.
 * @param[out] data Pointer to a structure that stores channel voltage current.
 *
 * @return Returns 0 on success; otherwise, returns an error code.
 */
extern int32_t hbn_cam_read_voltage_current_value(camera_handle_t const cam_fd, uint8_t const cmd_type, void *const data);


/**
 * @brief read the deserializer errb state.
 *
 * This function read the deserializer errb state by `desIdx
 * and stores the result in the `errbStatus` structure.
 *
 * @param[in] deserial_index The deserializer index. The index has value 0,1,4.
 * @param[out] DesErrbStatus Stores the errb state.The fileds include blow:
 *                              -isErrbAsserted: Bool value. Set to true if deserializer errb asserted.
                                -isRemoteError: Bool value. Set to true if remote serializer error detected.
                                -linkErrorMask: Mask for link error state. Valid range: [0x0000, 0x1111].
 *
 * @return Returns 0 on success; otherwise, returns an error code.
 */
extern int32_t hbn_des_get_errb_status(uint8_t const deserial_index, void *const DesErrbStatus);

/**
 * @brief read the sensor、serializer、 PMIC errb state.
 *
 * This function read the deserializer errb state by `desIdx
 * and stores the result in the `errbStatus` structure.
 *
 * @param[in] cam_fd The camera fd.
 * @param[out] CamErrbStatus Stores the errb state.The fileds include blow:
                                -isSnrErrbAsserted：Bool value. Sensor errb asserted
                                -isSerErrbAsserted: Bool value. Serializer errb asserted
                                -isPoCErrbAsserted: Bool value. PMIC errb asserted
 *
 * @return Returns 0 on success; otherwise, returns an error code.
 */
extern int32_t hbn_cam_get_errb_status(camera_handle_t const cam_fd, void *const CamErrbStatus);


/**
 * @brief Write the data to a register.
 *
 * @param[in]   camera_handle     The handle of the camera module.
 * @param[in]   componentId       The camera module component index
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[in]   dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_cam_set_register_value(camera_handle_t const camera_handle,
                           uint16_t const componentId,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Read the data from the register.
 *
 * @param[in]   camera_handle     The handle of the camera module
 * @param[in]   componentId       The camera module component index
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[out]  dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_cam_get_register_value(camera_handle_t const camera_handle,
                           uint16_t const componentId,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Read the data from the idu serializer register.
 *
 * @param[in]   componentId       The camera module component index
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[out]  dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_cam_get_idu_serializer_register(uint16_t const componentId,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief write the data from the idu serializer register.
 *
 * @param[in]   componentId       The camera module component index
 * @param[in]   registerNum       The register number. Valid range: [0U, 0xFFFFU].
 * @param[in]   dataLength        Length of @a dataBuff, in bytes. Valid range: [0U, UINT16_MAX].
 * @param[out]  dataBuff          Pointer to an 8-bit buffer. Valid value: [non-NULL].
 *
 * @retval 0 on success; otherwise, returns an error code.
 */
extern int32_t
hbn_cam_set_idu_serializer_register(uint16_t const componentId,
                           uint16_t const registerAddr,
                           uint16_t const dataLength,
                           uint8_t *const dataBuffer);

/**
 * @brief Gets generic module error information
 *
 * This method queries the drivers for detailed error information and populates a provided buffer
 * for module devices (sensor, serializer) associated with the index.
 * The contents, size written, and order are determined by each driver.
 *
 * It is expected that the provided buffers are the correct size for the driver-provided errors.
 *
 * A flag is provided indicating whether sensor, serializer, or both errors should be read.
 * If not read, the errorInfo may be null for that device.
 *
 * @param[in] cam_fd                    The camera fd.
 * @param[out] serializerErrorInfo      Buffer to populate
 *                                      with serializer error information
 *                                      and the size of data written.
 *                                      Zero size means that no valid data was written.
 * @param[out] sensorErrorInfo          Buffer to populate
 *                                      with sensor error information
 *                                      and the size of data written.
 *                                      Zero size means that no valid data was written.
 * @param[in]  errorsToRead             Flag indicating which errors to read -
 *                                      sensor, serializer, or both.
 *
 * @return Returns 0 on success; otherwise, returns an error code.
 */
int32_t hbn_cam_get_module_error_info(camera_handle_t const cam_fd,
                                     void *const serializerErrorInfo,
                                     void *const sensorErrorInfo,
                                     uint8_t const errorsToRead);


/**
 * @brief Get generic deserializer error information
 * This method queries the driver for detailed error information and populates a provided buffer
 * for the deserializer associated with the device index.
 * The contents, size written, and order are determined by the driver.
 *
 * @param[in]  Index                    Index of the device associated with the
 *                                      deserializer to retrieve information from.
 * @param[out] deserializerErrorInfo    ErrorDetails buffer to populate
 *                                      with error information
 *                                      and the size of data written.
 *                                      Zero size means that no valid data was written.
 * @param[out] isRemoteError            uint8_t to store remote (serializer) error state.
 * @param[out] linkErrorMask            uint8_t to store link mask for link error state
 *                                      (1 in index position indicates error;
 *                                      all 0 means no link error detected).
 */
int32_t hbn_des_get_error_info(uint32_t const index,
                              void *const deserializerErrorInfo,
                              void *const isRemoteError,
                              void *const linkErrorMask);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BOSCH_CAMERA_INTERFACE_H__ */
