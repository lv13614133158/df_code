/**
 * @file hb_cgroup.h
 *
 * Horizon Robotics
 *
 * @NO{S21E11C01}
 *
 * @ASIL{QM}
 *
 * COPYRIGHT NOTICE
 * Copyright (C) 2023 Horizon Robotics Inc.
 * All rights reserved.
 * Author: Lianghong Liu <lianghong01.liu@horizon.cc>
 *
 */

#ifndef INCLUDE_HB_CGROUP_H_
#define INCLUDE_HB_CGROUP_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SUBSYS_PATH_MAX 32
#define RELEASE_AGENT_PATH_MAX 64
#define CORES_STR_MAX 64UL

#define CGROUP_LOG(...) do {              \
    printf("[HB_CGROUP][%s:%d] ", __func__, __LINE__);                     \
    printf(__VA_ARGS__);               \
} while(0)

#define CGROUP_MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef enum {
    SUBSYS_CPU_CPUACCT = 0UL,
    SUBSYS_CPUSET,
    SUBSYS_NUM,
} subsys_idx;

struct cgroup_subsys {
    const char  *name;
    const char  *path;
    char         release_agent[SUBSYS_PATH_MAX];
};

typedef enum {
    CGROUP_DATA_TYPE_INT = 0,
    CGROUP_DATA_TYPE_STR,
} cgroup_data_type;

struct cgroup_file_handle {
    char *file_mode;
    cgroup_data_type type;
    int data_int;
    char *data_str;
};

/**
 * @NO{S21E11C01}
 * @ASIL{QM}
 * @brief set cpu limit
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: v1.0.0
 *
 * @param [in] cpu_rate: cpu occupancy rate, 1 ~ 100
 *
 * @retval "= 0": success;
 * @retval "< 0": failure;
 *
 */
int cpu_limit(uint32_t cpu_rate);

/**
 * @NO{S21E11C01}
 * @ASIL{QM}
 * @brief set cpu core
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: v1.0.0
 *
 * @param [in] cores: limit run on which cores, 0 ~ 5 for j6e, 0 ~ 13 for j6p
 *
 * @retval "= 0": success;
 * @retval "< 0": failure;
 *
 */
int cpuset_limit(char* cores);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  // INCLUDE_HB_CGROUP_H_
