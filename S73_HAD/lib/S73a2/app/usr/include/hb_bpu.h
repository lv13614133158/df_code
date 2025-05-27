/*************************************************************************************
 *                                COPYRIGHT NOTICE
 *                 Copyright (C) 2022 -2024 Horizon Robotics, Inc.
 *                                All rights reserved.
 ************************************************************************************/
#ifndef HB_BPU_H
#define HB_BPU_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define BPU_VERSION_MAJOR 2
#define BPU_VERSION_MINOR 1
#define BPU_VERSION_PATCH 2

/**
 * @enum hb_bpu_err_t
 * Describe BPU Error nummber
 */
typedef enum {
	BPU_OK = 0, /**< no error */
	BPU_NO_CORE = -1, /**< no have bpu core */
	BPU_INVAL = -2, /**< Invalid data */
	BPU_NOMEM = -3, /**< no memory */
	BPU_TIMEOUT = -4, /**< timeout error */
	BPU_NODATA = -5, /**< no data error */
	BPU_NOGRP = -6, /**< not inited group */
	BPU_NOTSPT = -7, /**< Not support data */
	BPU_NOPERMISSION = -8, /**< not have permission */
	BPU_BUSY = -9, /**< work too busy  */
	BPU_CANCEL = -10, /**< bpu task has been cancelled */
	BPU_UNKNOW = -11, /**< unknow error */
	BPU_IOCTL = -12, /**< ioctl error */
} hb_bpu_err_t;

/**
 * @enum hb_bpu_core_type_t
 * Describe BPU Core Type
 */
typedef enum {
	CORE_TYPE_UNKNOWN, /**< unknown type */
	CORE_TYPE_4PE, /**< support 4pe type */
	CORE_TYPE_1PE, /**< support 1pe type */
	CORE_TYPE_2PE, /**< support 2pe type */
	CORE_TYPE_ANY, /**< support arbitraryany type */
	CORE_TYPE_INVALID, /**< Invalid type */
} hb_bpu_core_type_t;

/**
 * @enum hb_bpu_core_choose_t
 * Describe BPU Core choose method when multiple core use to process bpu task
 */
typedef enum {
	CHOOSE_BY_CAP = 0, /**< Select the bpu core with the most capacity */
	CHOOSE_BY_EST_LOAD, /**< Select the bpu core with low estimated remaining processing time*/
	CHOOSE_BY_UNKNOWN /**< Unknown method */
} hb_bpu_choose_t;

/**
 * @enum hb_bpu_task_status_t
 * Describe BPU task status types of stages
 */
typedef enum {
	TASK_IDLE = 0, /**< Idle */
	TASK_CONFIG, /**< Configured */
	TASK_BIND, /**< Bind extra memory */
	TASK_CONFIG_BIND, /**< Configured and bind extra memory */
	TASK_PROCESS, /**< Set to process by BPU */
	TASK_DONE, /**< Processed done */
	TASK_ERR, /**< Error occured */
	TASK_INVALID, /**< Invalid status */
	TASK_UNKOWN, /**< Unkown status */
	TASK_ST_NUM /**< Status type Number */
} hb_task_status_t;

/**
 * @enum hb_bpu_task_type_t
 * Describe The type of BPU task
 */
typedef enum {
	TASK_TYPE_SYNC = 0x0000, /**< Sync type, hb_bpu_core_process will block until task process done */
	TASK_TYPE_TRIG_TASK = 0x0001, /**< Trigger task type, when processed done, hb_bpu_task_wait will return */
	TASK_TYPE_TRIG_CORE = 0x0002, /**< Trigger core type, when processed done, hb_bpu_core_wait will return */
	TASK_TYPE_GRAPH = 0x0004, /**< Graph type, task pending process until trigger by dependent condition, when processed done, hb_bpu_core_wait will return*/
} hb_task_type_t;

/**
 * @enum hb_bpu_map_mode_t
 * Describe map mode of bpu map
 */
typedef enum {
	BPU_RD = 0x0001, /**< Read only */
	BPU_WR = 0x0002, /**< Read/Write */
} hb_bpu_map_mode_t;

typedef struct {uint64_t opaque;} hb_bpu_core_t; /**< the bpu core  */
typedef struct {uint64_t opaque;} hb_bpu_task_t; /**< the bpu task */
typedef struct {uint64_t base; uint64_t size;} hb_bpu_map_t; /**< the bpu map */

typedef int32_t (*hb_bpu_task_cb_t)(hb_bpu_task_t task, hb_task_status_t st, void *data);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief For user to get bpu library version
 * 
 * @param[out] major: major version value pointer
 * @param[out] minor: minor version value pointer
 * @param[out] patch: patch version value pointer
 * 
 * @retval BPU_OK: success
 * @retval BPU_INVAL: invalid parameter
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_version(uint32_t *major, uint32_t *minor, uint32_t *patch);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the BPU core device number in system
 * 
 * @return detect bpu core device number
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
uint32_t hb_bpu_core_num(void);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu core device type and firmware version
 * 
 * @param[in] core_index: bpu core device index
 * @param[out] version: firmware version value pointer, when set NULL
 * 						no information return
 * 
 * @return bpu core deivce type(reference hb_bpu_core_type)
 
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_core_type_t hb_bpu_core_type(uint32_t core_index, uint64_t *version);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the left estimate processing time which tasks in bpu core buffer fifo
 * 
 * @param[in] core_index: bpu core index
 * @param[in] prio: the priority
 * @param[out] time: the return time value(us) pointer, should not be NULL
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_est_load(uint32_t core_index, uint32_t prio, uint64_t *time);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the left capacity of bpu core fifo which to buffer the to
 * 			be processsed tasks
 * 
 * @param[in] core_index: bpu core index
 * @param[out] cap: the capacity value pointer, should not be NULL
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_cap(uint32_t core_index, uint32_t *cap);
/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set one group use bpu proportion for limit special group's tasks
 * 			group 0 default proportion=100, not need set to init
 * 
 * @param[in] group: group value
 * @param[in] prop: bpu use proportion, max 100, if set 0, delete the group
 * 					record from bpu software
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_set_group_proportion(uint32_t group, uint32_t prop);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Allocate a bpu task instance and return the bpu task handle to user
 * 
 * @param[out] task: the space pointer to assign the bpu task handle, should not be NULL
 * @param[in] type: task type, reference hb_task_type_t
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_alloc(hb_bpu_task_t *task, hb_task_type_t type);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Free the bpu task instance which allocate by hb_bpu_task_alloc
 * 
 * @param[in] task: the valid bpu task handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_free(hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Use the bpu module information to config the bpu task, module information
 * 			from hbdk runtime
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] hbdk_task: the task data pointer which from hbdk runtime
 * @param[in] hbdk_task_num: the task data number which from hbdk runtime
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_config(hb_bpu_task_t task, void* hbdk_task, uint32_t hbdk_task_num);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Use the bpu module information to config the bpu task, module
 * 			information from hbdk runtime; if hbdk task create from
 * 			bpu mem, zero copy task data
 *
 * @param[in] task: the valid bpu task handle
 * @param[in] hbdk_task: the task data pointer which from hbdk runtime
 * @param[in] hbdk_task_size: the task data size which from hbdk runtime
 *
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.1.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_pt_config(hb_bpu_task_t task, void* hbdk_task, uint32_t hbdk_task_size);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set an user id to bind with the bpu task, if not set, default 0,
 * 			TASK_TYPE_GRAPH type bpu task can't set id by user
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] id: user id which want to bind
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_set_id(hb_bpu_task_t task, uint64_t id);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the user id which set by hb_bpu_task_set_id, if TASK_TYPE_GRAPH task,
 * 			the user id value from frame id (vps subsys trigger) or source bpu task
 * 			(non-TASK_TYPE_GRAPH bpu task trigger)
 * 
 * @param[in] task: the valid bpu task handle
 * @param[out] id: user id value pointer to assign the value
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_get_id(hb_bpu_task_t task, uint64_t *id);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set the bpu task priority
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] prio: priority, Typical 0:lowest 1:middle 2:highest
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_set_prio(hb_bpu_task_t task, uint32_t prio);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Bind a callback function when task done or error, when
 * 		task_cb function return > 0, the hb_bpu_core_wait or
 * 		hb_bpu_task_wait not need to run. TASK_TYPE_SYNC type
 * 		task not support set callback.
 *
 * @param[in] task: the valid bpu task handle
 * @param[in] task_cb: the callback function
 * @param[in] data: the data which use as callback praram
 *
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_set_cb(hb_bpu_task_t task, hb_bpu_task_cb_t task_cb, void *data);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Bind the bpu task to a group, bpu task default bind group 0,
 * 			if not 0 group, must use hb_bpu_set_group_proporition
 * 			set > 0 proporition
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] group: group id
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_set_group(hb_bpu_task_t task, uint32_t group);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Bind an extend memory for bpu task, which will be transfer to bpu firmware
 * 			bpu runtime can use the memory to transfer extra info
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] extra_data: memory range(need alloc from hbmem, and mapped on right bpu core)
 * @param[in] extra_data_size: memory range size
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_bind(hb_bpu_task_t task, void *extra_data, uint32_t extra_data_size);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Unbind the extend memory of bpu task which bind before
 * 
 * @param[in] task: the valid bpu task handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_unbind(hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set an alias name for the bpu task, if not set, default task name is "T%d"
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] name: name string, max len is 16
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_set_alias(hb_bpu_task_t task, char *name);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the alias name of the bpu task, default task name is "T%d"
 * 
 * @param[in] task: the valid bpu task handle
 * @param[out] name: name string pointer, to put the return value
 * @param[in] len: max len of name pointer parameter can assign
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_get_alias(hb_bpu_task_t task, char *name, uint8_t len);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief To Cancel the buffered bpu task, the api will sync until
 * 			cancel done, After cancel, the bpu task status will change
 * 			to TASK_CONFIG_BIND/TASK_CONFIG
 * 
 * @param[in] task: the valid bpu task handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_cancel(hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu core index which bpu task assigned
 * 
 * @param[in] task: the valid bpu task handle
 * 
 * @return the bpu core index, if not has been assigned, return BPU_NO_CORE
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_bpu_task_assigned_core(hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu task status
 * 
 * @param[in] task: the valid bpu task handle
 * 
 * @return the bpu task status, reference hb_task_status_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_task_status_t hb_bpu_task_status(hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu task type which set by hb_bpu_task_alloc
 * 
 * @param[in] task: the valid bpu task handle
 * @param[out] type: type pointer to assign value, reference hb_task_type_t
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_type(hb_bpu_task_t task, hb_task_type_t *type);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Use to wait TASK_TYPE_TRIG_TASK bpu task process done or cancelled
 * 
 * @param[in] task: the valid bpu task handle
 * @param[in] timeout: wait timeout(ms), if <0, block until return of cancelled
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_task_wait(hb_bpu_task_t task, int32_t timeout);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Map memory range to bpu core for bpu core dev use, and return bpu map handle
 * 
 * @param[out] map: bpu map handle pointer to assign return value
 * @param[in] core: valid bpu core handle
 * @param[in] addr: to map memory range base, should align PAGE(0x1000) size
 * @param[in] size: to map memory range size
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_map(hb_bpu_map_t *map, hb_bpu_core_t core, uint64_t addr, uint64_t size);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Unmap bpu map which from hb_bpu_map
 * 
 * @param[in] map: valid bpu map handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_unmap(hb_bpu_map_t map);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set the bpu map access mode for one bpu core dev
 * 
 * @param[in] map: valid bpu map handle
 * @param[in] core_index: the bpu core dev index which want to set mode
 * @param[in] mode: reference hb_bpu_map_mode_t
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_map_mode_set(hb_bpu_map_t map, uint32_t core_index, uint32_t mode);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu map access mode of the bpu core dev
 * 
 * @param[in] map: valid bpu map handle
 * @param[in] core_index: the bpu core dev index which want to set mode
 * @param[in] mode: value pointer reference hb_bpu_map_mode_t
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_map_mode_get(hb_bpu_map_t map, uint32_t core_index, uint32_t *mode);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Create a bpu core instance, open the bpu core dev and return
 * 			it's handle for user to process bpu task
 * 
 * @param[out] core: bpu core handle pointer use to assign return value
 * @param[in] core_mask: the bitmask which bpu core dev use
 *		 					(as index 0 -> 0x1; index 1-> 0x2, index 0&1->0x3...)
 * @param[out] method: when bpu core dev number > 1, how to choose the real
 * 							process task core, reference hb_bpu_choose_t
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_open(hb_bpu_core_t *core, uint32_t core_mask, hb_bpu_choose_t method);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Close and relase the bpu core which Open by hb_bpu_core_open
 * 
 * @param[in] core: valid bpu core handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_close(hb_bpu_core_t core);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set a bpu task to bpu core for process, when bpu task type is TASK_TYPE_SYNC
 * 			API block until task is process done or cancelled
 * 
 * @param[in] core: valid bpu core handle
 * @param[in] task: valid bpu task handle
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_process(hb_bpu_core_t core, hb_bpu_task_t task);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief wait bpu task process done which type is TASK_TYPE_TRIG_CORE/TASK_TYPE_GRAPH
 * 			and set to the bpu core to process, bpu tasks return one by one based
 * 			on the process done time
 * 
 * @param[in] core: the valid bpu core handle
 * @param[in] task: bpu task handle pointer to assign return, should not be null
 * @param[in] timeout: wait timeout(ms), if <0, block until have bpu task process done
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_core_wait(hb_bpu_core_t core, hb_bpu_task_t *task, int32_t timeout);

#define BPU_POWER_OFF    (0) /**< Power off status */
#define BPU_POWER_ON    (1) /**< Power on status */
#define BPU_CLK_OFF      (0) /**< Clock off status */
#define BPU_CLK_ON      (1) /**< Clock on status */

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set bpu core dev power status
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] status: BPU_POWER_OFF/BPU_POWER_ON
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_set_power(uint32_t core_index, uint32_t status);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get bpu core dev power status
 * 
 * @param[in] core_index: bpu core dev index
 * @param[out] status: value pointer to assign BPU_POWER_OFF or BPU_POWER_ON
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J5/J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_get_power(uint32_t core_index, uint32_t *status);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Set bpu core dev clock value
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] val: BPU_CLK_OFF to close clock; BPU_CLK_ON to open clock;
 * 					other value to open clock and change clock frequency
 * 					to the value, the value must be available frequency
 * 					point
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_set_clk(uint32_t core_index, uint64_t val);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get bpu core dev clock value
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] val: value pointer to assign clock frequency value
 * 					BPU_CLK_OFF: clock not enable
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J5/J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_get_clk(uint32_t core_index, uint64_t *val);

#define BPU_HIGHEST_FRQ  0 /**< Highest frequency level */

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get bpu core dev support clock frequency point level number
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] level_num: value pointer to assign clock frequency point number
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_frq_level_num(uint32_t core_index, int32_t *level_num);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get bpu core dev clock frequency point level
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] level: frequency point level, 0: highest; -n: decrease in turn
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: XJ3/J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_set_frq_level(uint32_t core_index, int32_t level);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get now bpu core dev clock frequency point level
 * 
 * @param[in] core_index: bpu core dev index
 * @param[in] level: value ponter to assign frequency point level
 * 					0: highest; -n: decrease in turn
 * 
 * @retval =BPU_OK: success
 * @retval !=BPU_OK: failure, reference hb_bpu_err_t
 * @compatibility HW: J6
 * @compatibility SW: 2.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_bpu_err_t hb_bpu_get_frq_level(uint32_t core_index, int32_t *level);

/**
 * @NO{S04E01C01I}
 * @ASIL{B}
 * @brief Get the bpu firmware feature data
 *
 * @param[out] feature_buf: the buffer to store return feature data
 * @param[in] size: the max buffer size to return feature data
 *
 * @return the real size of feature data
 * @compatibility HW: J6
 * @compatibility SW: 2.1.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
uint32_t hb_bpu_fw_get_feature(void *feature_buf, uint32_t size);

#ifdef __cplusplus
}
#endif
#endif
