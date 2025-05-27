/*
 * Horizon Robotics
 *
 *  Copyright (C) 2020 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: huipeng.xu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __GMAC_STL_H_
#define __GMAC_STL_H_

#include "diag_lib.h"

/* All the non-Reserved bits are cleared on read */
#define MAC_DPP_FSM_INT_STATUS		0x00000140
#define DCPES				BIT(28)
#define MRWCPES				BIT(27)
#define MTFCPES				BIT(26)
#define MTBUPES				BIT(25)
#define FSMPES				BIT(24)
/* 17-23 reserved */
#define MSTTES				BIT(16)
/* 13-15 reserved */
#define PTES				BIT(12)
#define ATES				BIT(11)
#define CTES				BIT(10)
#define RTES				BIT(9)
#define TTES				BIT(8)
/* 6,7 reserved */
#define ARPES				BIT(5)
#define MTSPES				BIT(4)
#define MPES				BIT(3)
#define RDPES				BIT(2)
#define TPES				BIT(1)
/* 0 reserved */

#define MAC_FSM_CONTROL			0x00000148
#define MAC_FSM_CONTROL_MASK		0x1F1F1F00 /* all inject bit */
/* 29-31 reserved */
#define PLGRNML					BIT(28)
#define ALGRNML					BIT(27)
#define CLGRNML					BIT(26)
#define RLGRNML					BIT(25)
#define TLGRNML					BIT(24)
/* 21-23 reserved */
#define PPEIN					BIT(20)
#define APEIN					BIT(19)
#define CPEIN					BIT(18)
#define RPEIN					BIT(17)
#define TPEIN					BIT(16)
/* 13-15 reserved */
#define PTEIN					BIT(12)
#define ATEIN					BIT(11)
#define CTEIN					BIT(10)
#define RTEIN					BIT(9)
#define TTEIN					BIT(8)
/* 2-7 reserved */
#define PRTYEN					BIT(1)
#define TMOUTEN					BIT(0)

#define MTL_DBG_CTL				0x00000c08
#define MTL_DBG_CTL_MASK	(0x7U << 16U)
#define EIEC					BIT(18)
#define EIAEE					BIT(17)
#define EIEE					BIT(16)

#define MTL_EST_GCL_CONTROL 	0x00000c80
#define MTL_EST_MASK		(0x7U << 21U)
#define ESTEIEC					BIT(23)
#define ESTEIAEE				BIT(22)
#define ESTEIEE					BIT(21)

#define BLEI					0x6

/* for test stl inject */
/* Memory Errors */
#define HOBOT_GMAC_ERR_ECC_TSO_1BIT			1U
/* Parity Errors in DPP */
#define HOBOT_GMAC_ERR_DPP_MTFC				2U
/* Parity Errors in FSM */
#define HOBOT_GMAC_PARITY_ERR_FSM_RX			3U
/* Timeout Errors in FSM */
#define HOBOT_GMAC_TIMEOUT_ERR_FSM_RX			4U
/* Timeout Errors in interface */
#define HOBOT_GMAC_TIMEOUT_ERR_FSM_APP			5U

/* for RD */
/* Parity Errors in FSM */
#define HOBOT_GMAC_PARITY_ERR_FSM_PTP			6U
#define HOBOT_GMAC_PARITY_ERR_FSM_APP			7U
#define HOBOT_GMAC_PARITY_ERR_FSM_CSR			8U
#define HOBOT_GMAC_PARITY_ERR_FSM_TX			9U
/* Timeout Errors in FSM */
#define HOBOT_GMAC_TIMEOUT_ERR_FSM_PTP			10U
#define HOBOT_GMAC_TIMEOUT_ERR_FSM_CSR			11U
#define HOBOT_GMAC_TIMEOUT_ERR_FSM_TX			12U
/* Parity Errors in DPP */
#define HOBOT_GMAC_ERR_DPP_RWC				13U
#define HOBOT_GMAC_ERR_DPP_MTBU				14U
#define HOBOT_GMAC_ERR_DPP_RX_INTERFACE			15U
#define HOBOT_GMAC_ERR_DPP_TX_FIFO_STATUS		16U
#define HOBOT_GMAC_ERR_DPP_TX_FIFO_DATA			17U
#define HOBOT_GMAC_ERR_DPP_DMA_DESC			18U
#define HOBOT_GMAC_ERR_DPP_DMA_TSO			19U
#define HOBOT_GMAC_ERR_ECC_EST_1BIT			20U
#define HOBOT_GMAC_ERR_ECC_EST_2BIT			21U
#define HOBOT_GMAC_ERR_ECC_TSO_2BIT			22U



#define MTL_ECC_CONTROL			0x00000cc0
#define DSCEE				BIT(5)
#define TSOEE				BIT(4)
#define MRXPEE				BIT(3)
#define MESTEE				BIT(2)
#define MRXEE				BIT(1)
#define MTXEE				BIT(0)

#define MTL_ECC_INT_ENABLE		0x00000cc8
#define ECEIE				BIT(8)
#define RXCEIE				BIT(4)
#define TXCEIE				BIT(0)
#define MTL_ECC_INT_STATUS		0x00000ccc
#define EUES				BIT(10)
#define EAMS				BIT(9)
#define ECES				BIT(8)
#define RXUES				BIT(6)
#define RXAMS				BIT(5)
#define RXCES				BIT(4)
#define TXUES				BIT(2)
#define TXAMS				BIT(1)
#define TXCES				BIT(0)

#define DMA_ECC_INT_ENABLE		0x00001084
#define TCEIE				BIT(0)
#define DMA_ECC_INT_STATUS		0x00001088
#define TUES				BIT(2)
#define TAMS				BIT(1)
#define TCES				BIT(0)

#define MTL_DPP_CONTROL			0x00000ce0
#define MTL_DPP_CONTROL_MASK	0x1E3E0 /* all inject bit */
#define IPEDC				BIT(16)
#define IPEMRWC				BIT(15)
#define IPEMTFC				BIT(14)
#define IPEMTBU				BIT(13)
/* 10-12 reserved */
#define IPERID				BIT(9)
#define IPEMTS				BIT(8)
#define IPEMTF				BIT(7)
#define IPETRD				BIT(6)
#define IPETH				BIT(5)
/* 2-4 reserved */
#define EPSI				BIT(2)
#define OPE				BIT(1)
#define EDPP				BIT(0)

#define MTL_DPP_ECC_EIC			0xce4

#define MAC_FSM_ACT_TIMER		0x0000014c
#define NTMRMD(x) 			(((x)&0xfU) << 16U)
#define TMR(x) 				((x)&0x3ffU)
#define NTMRMD_64MS			4U

#define MTL_SAFETY_INT_STATUS		0x00000cc4
#define MCSIS				BIT(31)
#define MEUIS				BIT(1)
#define MECIS				BIT(0)

#define DMA_SAFETY_INT_STATUS		0x00001080
#define MSUIS				BIT(29)
#define MSCIS				BIT(28)
#define DEUIS				BIT(1)
#define DECIS				BIT(0)

#define GMAC_SAFETY_ENABLE		1
#define GMAC_SAFETY_DISABLED		0

#define GMAC0_CE_ERRCODE		95
#define GMAC0_UCE_ERRCODE		96
#define GMAC1_CE_ERRCODE		97
#define GMAC1_UCE_ERRCODE		98

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl init
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_init(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl handler
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_handle(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl deinit
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_deinit(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl inject callback
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_inject(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl selfcheck callback
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_selfcheck(struct user_stl_func *stl_info);

/**
 * @NO{S13E02C05I}
 * @ASIL{B}
 * @brief gmac stl clear callback
 *
 * @param[in] stl_info: the gmac stl func info
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
int32_t gmac_stl_clear(struct user_stl_func *stl_info);

#endif
