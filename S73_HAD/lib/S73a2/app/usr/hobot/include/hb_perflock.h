/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/
#ifndef HB_PERFLOCK_H
#define HB_PERFLOCK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NR_CPUS (32)
#define NR_BPUS (32)
#define NR_DMCS (8)

typedef enum {
	PERFLOCK_ID_CPU = 0,
	PERFLOCK_ID_CPU_MAX = PERFLOCK_ID_CPU + NR_CPUS,
	PERFLOCK_ID_CPUHP,
	PERFLOCK_ID_BPU,
	PERFLOCK_ID_BPU_MAX = PERFLOCK_ID_BPU + NR_BPUS,
	PERFLOCK_ID_DMC,
	PERFLOCK_ID_DMC_MAX = PERFLOCK_ID_DMC + NR_DMCS,
	PERFLOCK_ID_MAX,
} perlock_event;

struct perf_lock_event {
	int32_t item;
	int32_t min;
	int32_t max;
};

#define PERFLOCK_TIMEOUT_NONE     (0)

typedef struct hb_pl_req_handle *hb_pl_handle;

/**
 * @NO{S15E02C01I}
 * @ASIL{B}
 * @brief Acquire a perflock for specific time
 * hb_perflock_acq will take a lock to ensure the CPU, BPU etc core
 * running at a high level, it takes an list of predefined interger
 * value to indicate how much CPU resource need to acquire
 *
 * @param[in] events: List of perflock event, it value from enum @perflock_event.
 * @param[in] len: Length of perflock event list.
 * @param[in] timeout: Timeout, in microseconds.
 *
 * @retval NULL: failed
 * @retval otherwise: success
 *
 * @data_read None
 * @data_updated None
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: v1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
hb_pl_handle hb_perflock_acq(struct perf_lock_event events[], int32_t len, int32_t timeout);

/**
 * @NO{S15E02C01I}
 * @ASIL{B}
 * @brief Release a perflock
 * hobot_perflock_rel will release a perflock, if this perflock have
 * expired is activate time, it will do nothing, just to free
 * everything alloced when @hb_perflock_acq. After this function
 * successfully returned, you shouldn't use @handle anymore.
 *
 * @param[in] handle: target perflock handel
 *
 * @retval 0: success
 * @retval otherwise: failed
 *
 * @data_read None
 * @data_updated None
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: v1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_perflock_rel(hb_pl_handle handle);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HB_PERFLOCK_H */
