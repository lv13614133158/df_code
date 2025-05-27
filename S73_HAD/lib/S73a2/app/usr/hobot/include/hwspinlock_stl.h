/*************************************************************************
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2022-2024, Horizon Robotics Co., Ltd.
 *                    All rights reserved.
 *************************************************************************/
/**
 * @file hwspinlock_stl.h
 *
 * @NO{S17E09C05I}
 * @ASIL{B}
 */
#ifndef __HWSPINLOCK_STL_H_
#define __HWSPINLOCK_STL_H_

#include "diag_lib.h"

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief hwspinlock stl init
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_init(struct user_stl_func *stl_info);

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief hwspinlock stl handle error
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_handle(struct user_stl_func *stl_info);

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief hwspinlock stl deinit
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_deinit(struct user_stl_func *stl_info);

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief force trigger a error for hwspinlock stl
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_inject(struct user_stl_func *stl_info);

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief hwspinlock stl self check
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_selfcheck(struct user_stl_func *stl_info);

/**
 * @NO{S17E09C05I}
 * @ASIL{B}
 * @brief hwspinlock stl clear error
 *
 * @param[in] stl_info: the diagnose stl info
 *
 * @retval 0: success
 * @retval !0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hwspinlock_stl_clear(struct user_stl_func *stl_info);
#endif /*__HWSPINLOCK_STL_H_*/
