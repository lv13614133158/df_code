/*************************************************************************************
 *                                COPYRIGHT NOTICE
 *                 Copyright (C) 2022 -2024 Horizon Robotics, Inc.
 *                                All rights reserved.
 ************************************************************************************/
#ifndef HB_BPU_MEM_H
#define HB_BPU_MEM_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define bpu_addr_t uint64_t /**< bpu mem address type */
#define BPU_NON_CACHEABLE (0) /**< bpu mem no cacheable flag */
#define BPU_CACHEABLE (1) /**< bpu mem cacheable flag */
#define BPU_CONHERENCE (2) /**< bpu mem conherence flag */
#define BPU_RDONLY (0x100U) /**< bpu mem Read only by BPU */
#define BPU_CORE0 (0x10000) /**< bpu core0 flag */
#define BPU_CORE1 (0x20000) /**< bpu core1 flag */
#define BPU_CORE2 (0x40000) /**< bpu core2 flag */
#define ARM_TO_CNN (0) /**< bpu mem copy direction, from cpu mem to bpu mem */
#define CNN_TO_ARM (1) /**< bpu mem copy direction, from bpu mem to cpu mem */
#define CPU_TO_BPU (0) /**< bpu mem copy direction, from cpu mem to bpu mem */
#define BPU_TO_CPU (1) /**< bpu mem copy direction, from bpu mem to cpu mem */
#define BPU_MEM_INVALIDATE (1) /**< Invalid cacheable bpu mem cache */
#define BPU_MEM_CLEAN (2) /**< Flush and clean bpu mem cache */

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief When memory not allocate from bpu mem, external memory range need
 * reigster in bpu mem
 * 
 * @param[in] phy_addr: external memory physical address base
 * @param[in] size: memory range size
 * 
 * @return user can access address
 * @retval =0: failure
 * @retval >0: address
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
bpu_addr_t hb_bpu_mem_register(void *phy_addr, uint64_t size);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Unregister memory which add to bpu mem by register api
 * 
 * @param[in] addr: register api return valid address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
void hb_bpu_mem_unregister(bpu_addr_t addr);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Allocate memory for bpu use
 * 
 * @param[in] size: allocate memory size
 * @param[in] flag: allocate memory flag(cacheable/coherence)
 * 
 * @return user can access address
 * @retval =0: failure
 * @retval >0: address
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
bpu_addr_t hb_bpu_mem_alloc(uint64_t size, uint32_t flag);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Allocate memory for cpu use
 * 
 * @param[in] size: allocate memory size
 * @param[in] flag: allocate memory flag(cacheable/coherence)
 * 
 * @return user can access address
 * @retval =0: failure
 * @retval >0: address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
bpu_addr_t hb_bpu_cpumem_alloc(uint64_t size, uint32_t flag);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Allocate memory for bpu use with label
 * 
 * @param[in] size: allocate memory size
 * @param[in] flag: allocate memory flag(cacheable/coherence)
 * @param[in] label: a string label for memory
 * 
 * @return user can access address
 * @retval =0: failure
 * @retval >0: address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
bpu_addr_t hb_bpu_mem_alloc_with_label(uint64_t size,
		uint32_t flag, const char* label);
/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief  Allocate memory for cpu use with label
 * 
 * @param[in] size: allocate memory size
 * @param[in] flag: allocate memory flag(cacheable/coherence)
 * @param[in] label: a string label for memory
 * 
 * @return user can access address
 * @retval =0: failure
 * @retval >0: address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
bpu_addr_t hb_bpu_cpumem_alloc_with_label(uint64_t size,
		uint32_t flag, const char* label);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Free memory which allocate by alloc api
 * 
 * @param[in] addr: the valid memory address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
void hb_bpu_mem_free(bpu_addr_t addr);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Free memory which allocate by alloc api
 * 
 * @param[in] addr: the valid memory address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
void hb_bpu_cpumem_free(bpu_addr_t addr);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Data copy to support heterogeneous memory
 * 
 * @param[in] dst_addr: target memory range base address
 * @param[in] src_addr: source memory range base address
 * @param[in] size: copy memory size
 * @param[in] direction: cpu->bpu or bpu->cpu
 * 
 * @retval =0: success
 * @retval <0: failure
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_bpu_memcpy(bpu_addr_t dst_addr, bpu_addr_t src_addr,
		uint64_t size, uint32_t direction);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief When memory allocate as cacheable, cache operation need when after write
 * before read
 * 
 * @param[in] addr: cache operation memory range base
 * @param[in] size: cache operation memory range size
 * @param[in] flag: cache invalid or clean
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
void hb_bpu_mem_cache_flush(bpu_addr_t addr, uint64_t size,
		uint32_t flag);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief check the bpu mem cacheable status
 * 
 * @param[in] addr: the address frome bpu mem alloc/register api
 * 
 * @return the cacheable status
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_bpu_mem_is_cacheable(bpu_addr_t addr);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Get the bpu mem address's physical address
 * 
 * @param[in] addr: bpu mem address
 * 
 * @retval =0: invalid bpu mem address
 * @retval !=0: the bpu mem address's physical address
 * 
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
uint64_t hb_bpu_mem_phyaddr(bpu_addr_t addr);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Get the bpu mem address's device iova address
 *
 * @param[in] addr: bpu mem address
 * @param[in] core_index: bpu core index
 *
 * @retval =0: can't find the device iova address of the bpu core
 * @retval !=0: valid iova address
 *
 * @compatibility HW: J6
 * @compatibility SW: 2.1.1
 *
 * @callgraph
 * @callergraph
 * @design
 */
uint64_t hb_bpu_mem_device_iova(bpu_addr_t addr, uint32_t core_index);

/**
 * @NO{S04E01C02I}
 * @ASIL{B}
 * @brief Get the bpu mem address's host iova address
 *
 * @param[in] addr: bpu mem address
 * @param[in] core_index: bpu core index
 *
 * @retval =0: can't find the host iova address of the bpu core
 * @retval !=0: valid iova address
 *
 * @compatibility HW: J6
 * @compatibility SW: 2.1.1
 *
 * @callgraph
 * @callergraph
 * @design
 */
uint64_t hb_bpu_mem_host_iova(bpu_addr_t addr, uint32_t core_index);

#ifdef __cplusplus
}
#endif
#endif
