/*************************************************************************
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2020-2023, Horizon Robotics Co., Ltd.
 *                    All rights reserved.
 *************************************************************************/
/**
 * @file vdsp_stl.h
 *
 * @NO{S05E06C02I}
 * @ASIL{B}
 */
#ifndef __VDSP_STL_H_
#define __VDSP_STL_H_

#include "diag_lib.h"
#include "diag_lib_id.h"

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl init
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_init(struct user_stl_func *stl_info);

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl handler
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_handle(struct user_stl_func *stl_info);

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl deinit
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_deinit(struct user_stl_func *stl_info);

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl inject callback
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_inject(struct user_stl_func *stl_info);

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl selfcheck callback
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_selfcheck(struct user_stl_func *stl_info);

/**
 * @NO{S05E06C02I}
 * @ASIL{B}
 * @brief vdsp stl clear callback
 *
 * @param[in] stl_info: the vdsp stl func info
 *
 * @retval "= 0": success
 * @retval "< 0": Failure
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
int32_t vdsp_stl_clear(struct user_stl_func *stl_info);
#endif
