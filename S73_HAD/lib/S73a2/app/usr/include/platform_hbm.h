/**
 * @file platform_hbm.h
 *
 * @NO{S06E03C07}
 *
 * @ASIL{B}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 */

#ifndef LIBLOAD_HBM_INCLUDE_PLATFORM_HBM_H_
#define LIBLOAD_HBM_INCLUDE_PLATFORM_HBM_H_
#include <stdint.h>

/* ============== define definition ============== */
#ifndef bpu_addr_t
#define bpu_addr_t uint64_t
#endif
/* ============== struct definition ============== */

/*
 * @Description: hbm information
 * @fd: flash fd stored hbm file
 * @offset: hbm file offset of fd
 * @inst_addr: instruct data in secure address;
 * @par_addr: parameter data in secure address;
 */
typedef struct platform_hbm_info {
	int32_t	   fd;
	uint32_t   offset;
	bpu_addr_t inst_addr;
	bpu_addr_t par_addr;
} platform_hbm_info_t;

/* ============== interface definition ============== */

/**
 * @NO{S06E03C07}
 * @ASIL{B}
 * @brief get hbm information
 *
 * @param[in] platform_hbm: platform hbm information
 * @param[in] hbm_name:hbm file name
 *
 * @retval =0: success
 * @retval !=0: failure
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t platform_hbm_info_get(platform_hbm_info_t *platform_hbm,
			      char		  *hbm_name);

/**
 * @NO{S06E03C07}
 * @ASIL{B}
 * @brief get number of hbm file in flash
 *
 * @retval =0: success
 * @retval !=0: failure
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t platform_get_hbm_number();

/**
 * @NO{S06E03C07}
 * @ASIL{B}
 * @brief get hbm name stored in flash
 *
 * @param[in] index: hbm index,MAX is (platform_get_hbm_number() - 1)
 * @param[out] hbm_name: hbm name buffer,malloc by caller
 *
 * @retval =0: success
 * @retval !=0: failure
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
char *platform_get_hbm_name(unsigned int hbm_index, char *hbm_name);

/**
 * @NO{S06E03C07}
 * @ASIL{B}
 * @brief pet hbm information
 *
 * @param[in] platform_hbm:platform hbm information
 *
 * @retval =0: success
 * @retval !=0: failure
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t platform_hbm_info_put(platform_hbm_info_t *platform_hbm);

#endif // LIBLOAD_HBM_INCLUDE_PLATFORM_HBM_H_
