/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/

/**
 * @file tee_engine.h
 *
 * @NO{S06E02C02I}
 * @ASIL{B}
 */

#ifndef __TEE_ENGINE_H__
#define __TEE_ENGINE_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include <openssl/obj_mac.h>
#include <openssl/ossl_typ.h>

extern const char *engine_tee_id;

/**
 * @brief static load tee engine 
 *
 *
 * @retval None
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
void ENGINE_load_teeEngine(void);

#ifdef __cplusplus
}
#endif

#endif /* __TEE_ENGINE_H__ */

