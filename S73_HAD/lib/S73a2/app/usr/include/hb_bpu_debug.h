/*************************************************************************************
 *                                COPYRIGHT NOTICE
 *                 Copyright (C) 2022 -2024 Horizon Robotics, Inc.
 *                                All rights reserved.
 ************************************************************************************/
#ifndef HB_BPU_DEBUG_H
#define HB_BPU_DEBUG_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <hb_bpu.h>

void hb_bpu_tasks_info(FILE *fp);
void hb_bpu_cores_info(FILE *fp);
void hb_bpu_models_info(FILE *fp);
void hb_bpu_info_dump(char *path);

/*
 * callback for user debug task status change
 * which will block task flow, only for debug
 */
typedef void (*task_st_cgcb_t)(hb_bpu_task_t task, hb_task_status_t from_st, hb_task_status_t to_st, void *data);

hb_bpu_err_t hb_bpu_task_stcg_register(hb_bpu_task_t task, task_st_cgcb_t cb, void *data);
hb_bpu_err_t hb_bpu_task_stcg_unregister(hb_bpu_task_t task);

#ifdef __cplusplus
}
#endif
#endif
