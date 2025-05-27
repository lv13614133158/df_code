/**
 * @file hobot_autosense.h
 *
 * @NO{S06E03C04}
 *
 * @ASIL{B}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 */

#ifndef HOBOT_AUTOSENSE_H
#define HOBOT_AUTOSENSE_H

#include <stdint.h>

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief read autosense value
 *
 * @param[in] bank: autosense bank
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
uint32_t hb_autosense_read(const uint32_t bank, uint32_t *value);

/**
 * @NO{S06E03C04}
 * @ASIL{B}
 * @brief Write value to autosense bank
 *
 * @param[in] bank: Write bank
 * @param[in] value: Write value
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
uint32_t hb_autosense_debug_write(const uint32_t bank, const uint32_t value);
uint32_t hb_autosense_keep_reset(void);
#endif /*HOBOT_AUTOSENSE_H*/
