/*************************************************************************
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2022-2024, Horizon Robotics Co., Ltd.
 *                    All rights reserved.
 *************************************************************************/

/**
 * @file xpcs_stl.c
 *
 * @NO{S13E02C05U}
 * @ASIL{B}
 */
#ifndef __XPCS_STL_H_
#define __XPCS_STL_H_

#include "diag_lib.h"

/* xpcs inject register */
#define XPCS_SFTY_ERR_INJ			0xe3c4U
#define CSREI					BIT(13)
#define DPPEI					BIT(12)
#define PHYIFTEI				BIT(11)
#define APB3IFTEI				BIT(10)
#define CKOFTEI					BIT(9) /* not used */
#define EEEFTEI					BIT(8)
#define CSRFTEI					BIT(7)
#define RXFTEI					BIT(6)
#define TXFTEI					BIT(5)
#define CKOFPEI					BIT(4) /* not used */
#define EEEFPEI					BIT(3)
#define CSRFPEI					BIT(2)
#define RXFPEI					BIT(1)
#define TXFPEI					BIT(0)

#define XPCS_FSM_DISABLE			0xe3d0U
/* xpcs status */
#define XPCS_SFTY_UE_INTR0			0xe3c0U
#define PSEQ_ERR				BIT(15)
/* 14~13 reserved */
#define DPP_INT					BIT(12)
#define PHY_IFT_INT				BIT(11)
#define APB3_IFT_INT				BIT(10)
#define CKOFT_INT				BIT(9)
#define EEEFT_INT				BIT(8)
#define CSRFT_INT				BIT(7)
#define RXFT_INT				BIT(6)
#define TXFT_INT				BIT(5)
#define CKOFP_INT				BIT(4)
#define EEEFP_INT				BIT(3)
#define CSRFP_INT				BIT(2)
#define RXFP_INT				BIT(1)
#define TXFP_INT				BIT(0)

/* only CSR status, bit0 */
#define XPCS_SFTY_UE_INTR1			0xe3e0U  
#define CSR_INT					BIT(0)

#define XPCS_PARITY_ERR_MASK
#define XPCS_TIMEOUT_ERR_MASK

/* err source id */
/* for test inject */
#define  HOBOT_XPCS_PARITY_ERR_FSM_TX			1U
#define  HOBOT_XPCS_TIMEOUT_ERR_FSM_TX			2U
#define  HOBOT_XPCS_TIMEOUT_ERR_INTERFACE_PHY		3U
#define  HOBOT_XPCS_PARITY_ERR_DPP			4U
#define  HOBOT_XPCS_ERR_CSR				5U
/* for all */
#define  HOBOT_XPCS_PARITY_ERR_FSM_RX			6U
#define  HOBOT_XPCS_TIMEOUT_ERR_FSM_RX			7U
#define  HOBOT_XPCS_PARITY_ERR_FSM_CSR			8U
#define  HOBOT_XPCS_PARITY_ERR_FSM_EEE			9U
#define  HOBOT_XPCS_PARITY_ERR_FSM_CKO			10U	/* only for 6G PHY, not used */
#define  HOBOT_XPCS_TIMEOUT_ERR_FSM_CSR			11U
#define  HOBOT_XPCS_TIMEOUT_ERR_FSM_EEE			12U
#define  HOBOT_XPCS_TIMEOUT_ERR_FSM_CKO			13U	/* only for 6G PHY, not used */
#define  HOBOT_XPCS_TIMEOUT_ERR_INTERFACE_APB		14U

#define MAX_BIT 32U

#define XPCS0_ERRCODE		111
#define XPCS1_ERRCODE		112

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl init
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_init(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl handler
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_handle(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl deinit
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_deinit(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl inject callback
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_inject(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl selfcheck callback
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_selfcheck(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief xpcs stl clear callback
 *
 * @param[in] stl_info: the xpcs stl func info
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
int32_t xpcs_stl_clear(struct user_stl_func *stl_info);
#endif
