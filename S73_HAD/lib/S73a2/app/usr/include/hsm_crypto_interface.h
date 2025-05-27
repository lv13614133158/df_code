/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/

/**
 * @file hb_crypto.h
 *
 * @NO{S06E02C02I}
 * @ASIL{B}
 */

#ifndef __HSM_CRYPTO_INTERFACE_H__
#define __HSM_CRYPTO_INTERFACE_H__

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define OPTEE_SOFT_LIBRARY_FLAG 0x5a		/**< use optee soft crypto library */

/**
 * @ op_mode
 * Describe CA operation mode
 */
#define EN_MODE_ENCRYPT		0U		/**< encrypt */
#define EN_MODE_DECRYPT		1U		/**< decrypt */
#define EN_MODE_SIGN		2U		/**< sign */
#define EN_MODE_VERIFY		3U		/**< verify */
#define EN_MODE_MAC			4U		/**< hmac/gmac/cmac */
#define EN_MODE_DIGEST		5U		/**< hash */
#define EN_MODE_DERIVE		6U		/**< key exchange */


/**
 * @struct hb_crypto_st
 * Define the descriptor of crypto context
 * @NO{S06E02C02}
 */
struct hb_crypto_st {
	TEEC_Context ctx;  		/**< represents a connection between CA and TEE */
    TEEC_Session sess; 		/**< represents a connection between CA and TA */
	uint32_t algo;
};

/* skcipher */

/**
 * Describe skcipher algo, must be consistent with the skcipher_ta.h
 */
#define TA_ALGO_AES_ECB		0U
#define TA_ALGO_AES_CBC		1U
#define TA_ALGO_AES_CFB		2U
#define TA_ALGO_AES_OFB		3U
#define TA_ALGO_AES_CTR		4U
#define TA_ALGO_AES_XTS		5U
#define TA_ALGO_SM4_ECB		6U
#define TA_ALGO_SM4_CBC		7U
#define TA_ALGO_SM4_CFB		8U
#define TA_ALGO_SM4_OFB		9U
#define TA_ALGO_SM4_CTR		10U
#define TA_ALGO_SM4_XTS		11U

/**
 * @struct hb_skcipher_config
 * Define the skcipher init config
 * @NO{S06E02C02}
 */
typedef struct hb_skcipher_config {
	uint32_t		 	algo;		/**< skcipher algo */
	uint32_t	 		mode;		/**< encrypt or decrypt */
	const uint8_t		*key;		/**< key id, provided by key management module,
									 * when mode is XTS, key = key1+key2
									 */
	const uint8_t		*iv;		/**< IV to be used for cipher operation,
									 * when mode is XTS, tweak is iv
									 */
	uint32_t 	keylen;				/**< key length, when mode is XTS, keylen = sizeof(key_id) * 2 */
	uint32_t 	ivlen;				/**< iv length, be equal with block size */
	uint8_t		reserve[4];			/**< reserved */
} hb_skcipher_config;

/**
 * @brief establish connection between CA and skcipher TA
 *
 * @param[in] context: CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//TEEC_Result hb_skcipher_prepare_tee_session(struct hb_crypto_st *context);

/**
 * @brief free resources and close the connection with TEE
 *
 * @param[in] context: CA crypto context
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
void hb_skcipher_destroy(struct hb_crypto_st *context);

/**
 * @brief allocate TEE resources required for the skcipher operation and init the operation
 *
 * @param[in] context CA crypto context
 * @param[in] cipher_config ciphering init configure
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_skcipher_init(struct hb_crypto_st *context, const hb_skcipher_config *cipher_config);

 /**
 * @brief encrypt or decrypt input data
 *
 * @param[in] context CA crypto context
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_skcipher_update(struct hb_crypto_st *context, const uint8_t *in, size_t inlen, 
                                                    			uint8_t *out, size_t *outlen);


/**
 * @brief finalize the cipher operation
 *
 * @param[in] context CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_skcipher_final(struct hb_crypto_st *context, const uint8_t *in, size_t inlen, 
                                                    			uint8_t *out, size_t *outlen);


/* aead */

/**
 * Describe aead algo
 */
#define TA_ALGO_AES_CCM		0U
#define TA_ALGO_AES_GCM		1U
#define TA_ALGO_SM4_CCM		2U
#define TA_ALGO_SM4_GCM		3U

/**
 * @struct hb_aead_config
 * Define the aead init config
 * @NO{S06E02C02}
 */
typedef struct hb_aead_config {
	uint32_t		 	algo;			/**< aead algo, ccm or gcm */
	uint32_t	 		mode;			/**< encrypt or decrypt */
	uint8_t		*key;					/**< key id, provided by key management module */
	uint8_t		*iv;					/**< IV to be used for cipher operation */
	uint32_t 	keylen;					/**< key length, keylen = sizeof(key_id) */
	uint32_t 	ivlen;					/**< iv length */
	uint32_t 	tag_len;				/**< tag length */
	size_t 		aad_len;				/**< additional authentication data length */
	size_t 		payload_len;			/**< length in bytes of the data */
	uint8_t		reserve[4];				/**< reserved */
} hb_aead_config;

/**
 * @brief establish connection between CA and aead TA
 *
 * @param[in] context: CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//TEEC_Result hb_aead_prepare_tee_session(struct hb_crypto_st *context);

/**
 * @brief free resources and close the connection with TEE
 *
 * @param[in] context: CA crypto context
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
void hb_aead_destroy(struct hb_crypto_st *context);


/**
 * @brief allocate TEE resources required for the skcipher operation and init the operation
 *
 * @param[in] context CA crypto context
 * @param[in] aead_config aead init configure, see struct hb_aead_config
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_aead_init(struct hb_crypto_st *context, const hb_aead_config *aead_config);

/**
 * @brief set authentication data
 *
 * @param[in] context CA crypto context
 * @param[in] aad associated data buffer
 * @param[in] aad_len length of associated data length, must be equal with the length in struct hb_aead_config
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_aead_set_aad(struct hb_crypto_st *context, const uint8_t *aad, size_t aad_len);


/**
 * @brief set tag data, set taglen for encryption and tag can be NULL; set tag and taglen for decryption
 *
 * @param[in] context CA crypto context
 * @param[in] tag tag buffer
 * @param[in] tag_len length of tag length
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_aead_set_tag(struct hb_crypto_st *context, const uint8_t *tag, uint32_t tag_len);


/**
 * @brief get tag data after encryption
 *
 * @param[in] context CA crypto context
 * @param[out] tag tag buffer
 * @param[in] tag_len length of tag length, must be equel to the setted taglen
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_aead_get_tag(struct hb_crypto_st *context, uint8_t *tag, uint32_t tag_len);


/**
* @brief encrypt or decrypt input data
*
* @param[in] context CA crypto context
* @param[in] in input data
* @param[in] inlen length of input data in bytes
* @param[out] out output data
* @param[out] outlen length of returned output data in bytes
*
* @retval TEEC_SUCCESS: success
* @retval others: fail
*
* @compatibility HW: J6
* @compatibility SW: None
*
* @callgraph
* @callergraph
* @design
*/
TEEC_Result hb_aead_update_data(struct hb_crypto_st *context, const uint8_t *in, size_t inlen, 
                                                    uint8_t *out, size_t *outlen);

/**
 * @brief finalize the encrypt operation
 *
 * @param[in] context CA crypto context
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */ 
TEEC_Result hb_aead_encrypt_final(struct hb_crypto_st *context, const uint8_t *in, size_t inlen, 
                                                    uint8_t *out, size_t *outlen);

/**
 * @brief finalize the decrypt operation
 *
 * @param[in] context CA crypto context
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */ 
TEEC_Result hb_aead_decrypt_final(struct hb_crypto_st *context, const uint8_t *in, size_t inlen, 
                                                    uint8_t *out, size_t *outlen);

/* message digest */

/**
 * Describe message digest algo
 */

#define TA_ALGO_SHA224			0U
#define TA_ALGO_SHA256			1U
#define TA_ALGO_SHA384			2U
#define TA_ALGO_SHA512			3U
#define TA_ALGO_SHA3_224		4U
#define TA_ALGO_SHA3_256		5U
#define TA_ALGO_SHA3_384		6U
#define TA_ALGO_SHA3_512		7U
#define TA_ALGO_SM3				8U
#define TA_ALGO_HMAC_SHA224		9U
#define TA_ALGO_HMAC_SHA256		10U
#define TA_ALGO_HMAC_SHA384		11U
#define TA_ALGO_HMAC_SHA512		12U
#define TA_ALGO_HMAC_SHA3_224	13U
#define TA_ALGO_HMAC_SHA3_256	14U
#define TA_ALGO_HMAC_SHA3_384	15U
#define TA_ALGO_HMAC_SHA3_512	16U
#define TA_ALGO_HMAC_SM3		17U
#define TA_ALGO_AES_CMAC		18U
#define TA_ALGO_SM4_CMAC		19U

/**
 * @struct hb_md_config
 * Define the message digest init config
 * @NO{S06E02C02}
 */
typedef struct hb_md_config {
	uint32_t	 algo;		/**< md algo, hash or hmac or cmac or gmac */
	uint8_t		*key;				/**< key id, provided by key management module , used by hmac, cmac, gmac */
	uint32_t 	keylen;				/**< key length, keylen = sizeof(key_id) */
	uint8_t		reserve[4];			/**< reserved */
} hb_md_config;


/**
 * @brief establish connection between CA and aead TA
 *
 * @param[in] context: CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//TEEC_Result hb_md_prepare_tee_session(struct hb_crypto_st *context);

/**
 * @brief free resources and close the connection with TEE
 *
 * @param[in] context: CA crypto context
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
void hb_md_destroy(struct hb_crypto_st *context);

/**
 * @brief Allocate TEE resources required for the md operation
 *
 * @param[in] context CA crypto context
 * @param[in] md_config mesage init configure, see hb_md_config
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_md_init(struct hb_crypto_st *context, const hb_md_config *md_config);

/**
 * @brief message digest update function
 *
 * @param[in] context CA crypto context
 * @param[in] message holding the data to add to the message digest, must be block aligned
 * @param[in] msg_len buffer length
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_md_update(struct hb_crypto_st *context, const uint8_t *message, size_t msg_len);


/**
 * @brief finalize the message digest operation and output the digest
 *
 * @param[in] context CA crypto context
 * @param[in] message holding the final data to add to the message digest, no need to be block aligned
 * @param[in] msg_len buffer length
 * @param[out] digest filled with the message digest
 * @param[out] digest_len length of returned digest data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_md_final(struct hb_crypto_st *context, const uint8_t *message, size_t msg_len,
														  uint8_t *digest, size_t *digest_len);

/* akcipher */

/**
 * Describe akcipher algo
 */
#define TA_ALGO_RSASSA_PKCS1_V1_5_SHA256		0U
#define TA_ALGO_RSASSA_PKCS1_V1_5_SHA384		1U
#define TA_ALGO_RSASSA_PKCS1_V1_5_SHA512		2U
#define TA_ALGO_RSASSA_PKCS1_PSS_MGF1_SHA256	3U
#define TA_ALGO_RSASSA_PKCS1_PSS_MGF1_SHA384	4U
#define TA_ALGO_RSASSA_PKCS1_PSS_MGF1_SHA512	5U
#define TA_ALGO_RSAES_PKCS1_V1_5				6U
#define TA_ALGO_RSAES_PKCS1_OAEP_MGF1_SHA256	7U
#define TA_ALGO_RSAES_PKCS1_OAEP_MGF1_SHA384	8U
#define TA_ALGO_RSAES_PKCS1_OAEP_MGF1_SHA512	9U
#define TA_ALGO_ECDSA_P256						10U
#define TA_ALGO_ECDSA_P384						11U
#define TA_ALGO_ECDSA_P521						12U
#define TA_ALG_SM2_PKE							13U
#define TA_ALG_SM2_DSA_SM3						14U
#define TA_ALGO_ED25519							15U
#define TA_ALGO_ED448							16U

/**
 * @struct hb_akcipher_config
 * Define the akcipher init config
 * @NO{S06E02C02}
 */
typedef struct hb_akcipher_config {
	uint32_t 			algo;			/**< akcipher algo, include ecc, rsa, sm2, ed25519 */
	uint32_t	 		mode;			/**< operation mode, encrypt or decrypt, sign or verify */
	uint8_t		*key;					/**< key id, provided by key management module */
	uint32_t 	keylen;					/**< key length, keylen = sizeof(key_id) */
	uint8_t		reserve[4];				/**< reserved */
} hb_akcipher_config;


/**
 * @struct rsa_oaep_param_t
 * Define the label for rsa_oaep algo
 * @NO{S06E02C02}
 */
struct rsa_oaep_param_t {
	uint8_t		*label;					/**< label buffer */
	size_t 		label_len;				/**< label length */
};

/**
 * @struct rsa_pss_param_t
 * Define the saltlen for rsa_pss algo
 * @NO{S06E02C02}
 */
struct rsa_pss_param_t {
	int 	saltlen;				/**< salt length */
};

/**
 * @struct sm2_dsa_param_t
 * Define the sm2_dsa_param_t for sm2 sign algo
 * @NO{S06E02C02}
 */
struct sm2_dsa_param_t {
	uint8_t		*id;				/**< id buffer */
	size_t 		id_len;				/**< id length */
};

/**
 * @struct eddsa_param_t
 * Define the params for ed25519ph, ed25519ctx, ed448ph and ed448ctx
 * @NO{S06E02C02}
 */
struct eddsa_param_t {
	uint8_t 	prehash_flag;		/**< pre hashed or not */
	uint8_t		*ctx;				/**< ctx buffer */
	uint32_t 	ctx_len;			/**< ctx length, 
									 * for ed25519ctx and ed448ctx, length must be in range from 1 to 255,
							         * for ed25519ph and ed448ph, length must be in range from 0 to 255
									 */
};

/**
 * @struct hb_akcipher_params
 * Define the params for akcipher algo
 * @NO{S06E02C02}
 */
struct hb_akcipher_params {
	uint32_t	 			algo;				/**< algo type */
	union {
	    struct rsa_oaep_param_t		rsa_oaep;	/**< rsa_oaep params */
	    struct rsa_pss_param_t		rsa_pss;	/**< rsa_pss params */
	    struct sm2_dsa_param_t		sm2_dsa;	/**< sm2_dsa params */
	    struct eddsa_param_t		eddsa;		/**< eddsa params */
	} param_type;
	uint8_t		reserve[4];						/**< reserved */
};

/**
 * @brief establish connection between CA and aead TA
 *
 * @param[in] context: CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//TEEC_Result hb_akcipher_prepare_tee_session(struct hb_crypto_st *context);

/**
 * @brief free resources and close the connection with TEE
 *
 * @param[in] context: CA crypto context
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
void hb_akcipher_destroy(struct hb_crypto_st *context);


/**
 * @brief Allocate TEE resources required for the akcipher operation and init the opeartion
 *
 * @param[in] context CA crypto context
 * @param[in] akcipher_config akcipher init configure, see struct hb_akcipher_config
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_akcipher_init(struct hb_crypto_st *context, const hb_akcipher_config *akcipher_config);



/**
 * @brief encrypt data with akcipher
 *
 * @param[in] context CA crypto context
 * @param[in] akcipher_param  params for example:
 *			  label [optional] for rsa_oaep
 			  saltlen [optional] for rsa_pss
 			  cipher mode and mac mode [mandatory] for ecies
 			  ph flag and ctx [optional] for eddsa
 			  id [optional] for sm2
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_akcipher_encrypt(struct hb_crypto_st *context,
									   struct hb_akcipher_params *akcipher_param,
									   const uint8_t *in, size_t inlen,
									   uint8_t *out, size_t *outlen);

/**
 * @brief decrypt data with akcipher
 *
 * @param[in] context CA crypto context
 * @param[in] akcipher_param  params for example:
 *			  label [optional] for rsa_oaep
 			  saltlen [optional] for rsa_pss
 			  cipher mode and mac mode [mandatory] for ecies
 			  ph flag and ctx [optional] for eddsa
 			  id [optional] for sm2
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */ 
TEEC_Result hb_akcipher_decrypt(struct hb_crypto_st *context,
									   struct hb_akcipher_params *akcipher_param,
									   const uint8_t *in, size_t inlen,
									   uint8_t *out, size_t *outlen);

/**
 * @brief generate the signature for the hashed message
 *
 * @param[in] context CA crypto context
 * @param[in] akcipher_param  params for example:
 *			  label [optional] for rsa_oaep
 			  saltlen [optional] for rsa_pss
 			  cipher mode and mac mode [mandatory] for ecies
 			  ph flag and ctx [optional] for eddsa
 			  id [optional] for sm2
 * @param[in] data message data
 * @param[in] data_len length of message data in bytes
 * @param[out] sig signature data
 * @param[out] sig_len length of returned signature data in bytes
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_akcipher_sign(struct hb_crypto_st *context, 
								  struct hb_akcipher_params *akcipher_param, 
								  const uint8_t *data, size_t data_len, 
								  uint8_t *sig, size_t *sig_len);

/**
 * @brief verify a signature of the hased message is valid or not
 *
 * @param[in] context CA crypto context
 * @param[in] akcipher_param  params for example:
 *			  label [optional] for rsa_oaep
 			  saltlen [optional] for rsa_pss
 			  cipher mode and mac mode [mandatory] for ecies
 			  ph flag and ctx [optional] for eddsa
 			  id [optional] for sm2
 * @param[in] data message data
 * @param[in] data_len length of message data in bytes
 * @param[in] sig signature data
 * @param[in] sig_len length of signature data in bytes
 * @param[out] result 0: signature is valid; others: signature is invalid
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_akcipher_verify(struct hb_crypto_st *context,
									 struct hb_akcipher_params *akcipher_param, 
									 const uint8_t *data, size_t data_len, 
									 const uint8_t *sig, size_t sig_len);

/* kpp */

/**
 * @ kpp_algo
 * Describe kpp algo, must be consistent with the kpp_ta.h
 */
#define TA_ALGO_ECDH_P256		0U
#define TA_ALGO_ECDH_P384		1U
#define TA_ALGO_ECDH_P521		2U
#define TA_ALG_SM2_KEP			3U
#define TA_ALG_X25519			4U
#define TA_ALGO_X448			5U

/**
 * @def user role of SM2 key exchange
 */
#define SM2_INITIATOR        0		/**< initiator role of SM2 key exchange */
#define SM2_RESPONDER        1		/**< responder role of SM2 key exchange */

struct hb_sm2_kep_param {
	int 		role;
	uint8_t		*peer_eph_key;					/**< key id, provided by key management module */
	uint32_t 	peer_eph_keylen;					/**< key length, keylen = sizeof(key_id) */
	uint8_t 	*initiatorid;
	size_t 		initiatoridlen;
	uint8_t 	*responderid;
	size_t 		responderidlen;
	uint8_t		reserve[4];				/**< reserved */
} ;

/**
 * @struct hb_kpp_config
 * Define the kpp init config
 * @NO{S06E02C02}
 */
typedef struct hb_kpp_config {
	uint32_t	 	algo;			/**< kpp algo, include sm2, ecdh, x25519 */
	uint8_t		*own_key;				/**< own key id, provided by key management module */
	uint32_t	own_keylen;				/**< own ephemeral key id, provided by key management module */	
	uint8_t		*own_eph_key;			/**< key id, provided by key management module */
	uint32_t 	own_eph_keylen;			/**< key length, keylen = sizeof(key_id) */
	uint8_t		no_hsm_flag;			/**< reserved */
} hb_kpp_config;

/**
 * @brief establish connection between CA and aead TA
 *
 * @param[in] context: CA crypto context
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
//TEEC_Result hb_kpp_prepare_tee_session(struct hb_crypto_st *context);

/**
 * @brief free resources and close the connection with TEE
 *
 * @param[in] context: CA crypto context
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
void hb_kpp_destroy(struct hb_crypto_st *context);

/**
 * @brief Allocate TEE resources required for the kpp operation and init the opperation
 *
 * @param[in] context CA crypto context
 * @param[in] kpp_config kpp init configure, see struct hb_kpp_config
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
TEEC_Result hb_kpp_init(struct hb_crypto_st *context, const hb_kpp_config *kpp_config);

/**
 * @brief set identity params for SM2_KEP 
 *
 * @param[in] context CA crypto context
 * @param[in] initiatorid initiator identity
 * @param[in] initiatoridlen initiator identity length
 * @param[in] responderid reponseder identity
 * @param[in] responderidlen reponseder identity length
 * @param[in] role role of API user, SM2_INITIATOR or SM2_RESPONDER
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */ 
TEEC_Result hb_kpp_sm2_set_param(struct hb_crypto_st *context, 
										const struct hb_sm2_kep_param *param);


/**
 * @brief compute the shared secret as defined by the algorithm
 *
 * @param[in] context CA crypto context
 * @param[out] derivedKeyid key handle of the generated key
 *
 * @retval TEEC_SUCCESS: success
 * @retval others: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */  
TEEC_Result hb_kpp_derive_key(struct hb_crypto_st *context, const uint8_t *peer_key, uint32_t peer_keylen,
									uint8_t *derive_key, uint32_t *derive_key_len);

#ifdef __cplusplus
}
#endif

#endif /* __HSM_CRYPTO_INTERFACE_H__ */
