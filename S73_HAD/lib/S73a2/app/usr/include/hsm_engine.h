/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/

/**
 * @file hsm_engine.h
 *
 * @NO{S06E02C02I}
 * @ASIL{B}
 */

#ifndef __HSM_ENGINE_H__
#define __HSM_ENGINE_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include <openssl/obj_mac.h>
#include <openssl/ossl_typ.h>

extern const char *engine_hsm_id;

/**
 * @def user role of SM2 key exchange
 */
#define SM2_INITIATOR        0		/**< initiator role of SM2 key exchange */
#define SM2_RESPONDER        1		/**< responder role of SM2 key exchange */

#define EVP_PKEY_CTRL_SET_ROLE                          (EVP_PKEY_ALG_CTRL + 100)
#define EVP_PKEY_CTRL_SET_OWN_EPH_KEY					(EVP_PKEY_ALG_CTRL + 101)
#define EVP_PKEY_CTRL_SET_PEER_EPH_KEY                	(EVP_PKEY_ALG_CTRL + 102)
#define EVP_PKEY_CTRL_SET_INITIATOR_ID                  (EVP_PKEY_ALG_CTRL + 103)
#define EVP_PKEY_CTRL_SET_RESPONDER_ID                  (EVP_PKEY_ALG_CTRL + 104)


#define EVP_PKEY_CTX_set_sm2_derive_role(ctx, len) \
        EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_SM2, \
                                EVP_PKEY_OP_DERIVE, \
                                EVP_PKEY_CTRL_SET_ROLE, len, NULL)
                                
#define EVP_PKEY_CTX_set_sm2_derive_own_eph_keyid(ctx, key, key_len) \
        EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_SM2, EVP_PKEY_OP_DERIVE, \
                                EVP_PKEY_CTRL_SET_OWN_EPH_KEY, (int)key_len, (void*)(key))
                                
#define EVP_PKEY_CTX_set_sm2_derive_peer_eph_keyid(ctx, key, key_len) \
		EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_SM2, EVP_PKEY_OP_DERIVE, \
								EVP_PKEY_CTRL_SET_PEER_EPH_KEY, (int)key_len, (void*)(key))

#define EVP_PKEY_CTX_set_sm2_derive_initiator_id(ctx, id, id_len) \
        EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_SM2, EVP_PKEY_OP_DERIVE, \
                                EVP_PKEY_CTRL_SET_INITIATOR_ID, (int)id_len, (void*)(id))
                                
#define EVP_PKEY_CTX_set_sm2_derive_responder_id(ctx, id, id_len) \
        EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_SM2, EVP_PKEY_OP_DERIVE, \
                                EVP_PKEY_CTRL_SET_RESPONDER_ID, (int)id_len, (void*)(id))

#define EVP_PKEY_CTRL_SET_EDDSA_PH_FLAG             (EVP_PKEY_ALG_CTRL + 110)
#define EVP_PKEY_CTRL_SET_EDDSA_CONTEXT				(EVP_PKEY_ALG_CTRL + 111)

#define EVP_PKEY_CTX_set_eddsa_ph_flag(ctx, len) \
        EVP_PKEY_CTX_ctrl(ctx, -1, EVP_PKEY_OP_TYPE_SIG, \
                               EVP_PKEY_CTRL_SET_EDDSA_PH_FLAG, len, NULL)

#define EVP_PKEY_CTX_set_eddsa_context(ctx, context, context_len) \
        EVP_PKEY_CTX_ctrl(ctx, -1, EVP_PKEY_OP_TYPE_SIG, \
                               EVP_PKEY_CTRL_SET_EDDSA_CONTEXT, (int)context_len, (void*)(context))

#define SN_sm4_gcm              "SM4-GCM"
#define LN_sm4_gcm              "sm4-gcm"
#define NID_sm4_gcm             1195
#define OBJ_sm4_gcm             OBJ_sm_scheme,104L,8L

#define SN_sm4_ccm              "SM4-CCM"
#define LN_sm4_ccm              "sm4-ccm"
#define NID_sm4_ccm             1196
#define OBJ_sm4_ccm             OBJ_sm_scheme,104L,9L

#define SN_sm4_xts              "SM4-XTS"
#define LN_sm4_xts              "sm4-xts"
#define NID_sm4_xts             1197
#define OBJ_sm4_xts             OBJ_sm_scheme,104L,10L

/**
 * @brief define sm4 xts mode used by openssl 
 *
 *
 * @retval EVP_CIPHER pointer
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
const EVP_CIPHER *EVP_sm4_xts(void);

/**
 * @brief define sm4 gcm mode used by openssl 
 *
 *
 * @retval EVP_CIPHER pointer
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
const EVP_CIPHER *EVP_sm4_gcm(void);

/**
 * @brief define sm4 ccm mode used by openssl 
 *
 *
 * @retval EVP_CIPHER pointer
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
const EVP_CIPHER *EVP_sm4_ccm(void);

/**
 * @brief static load hsm engine 
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
void ENGINE_load_hsmEngine(void);

#ifdef __cplusplus
}
#endif

#endif /* __HSM_ENGINE_H__ */

