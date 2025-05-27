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

#ifndef __HB_CRYPTO_H__
#define __HB_CRYPTO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

#define HB_CRYPTO_VERSION_MAJOR 1	/**< major number of hb_crypto lib version*/
#define HB_CRYPTO_VERSION_MINOR 0	/**< minor number of hb_crypto lib version*/
#define HB_CRYPTO_VERSION_PATCH 0	/**< patch number of hb_crypto lib version*/

#define TA_ALGO_AES_GMAC		0x100U
#define TA_ALGO_SM4_GMAC		0x101U

#define TA_ALGO_ECIES_P256		0x100U
#define TA_ALGO_ECIES_P384		0x101U
#define TA_ALGO_ECIES_P521		0x102U

#define TA_ALGO_SM9_PKE			0x100U
#define TA_ALGO_SM9_DSA			0x101U
#define TA_ALGO_SM9_KEP			0x102U

/**
 * @struct hb_crypto_st
 * Define the descriptor of crypto context
 * @NO{S06E02C02}
 */
struct hb_crypto_st {
	TEEC_Context ctx;  		/**< represents a connection between CA and TEE */
    TEEC_Session sess; 		/**< represents a connection between CA and TA */
};

/**
 * @enum op_mode
 * Describe CA operation mode
 */
enum op_mode {
	EN_MODE_ENCRYPT = 0,	/**< encrypt */
	EN_MODE_DECRYPT = 1,	/**< decrypt */
	EN_MODE_SIGN = 2,		/**< sign */
	EN_MODE_VERIFY = 3,		/**< verify */
	EN_MODE_MAC = 4,		/**< hmac、gmac、cmac */
	EN_MODE_DIGEST = 5,		/**< hash */
	EN_MODE_DERIVE = 6		/**< key exchange */
};

/**
 * @enum md_algo
 * Describe message digest algo, must be consistent with the md_ta.h
 */
enum hash_algo {
	TA_ALGO_SHA224 = 0,
	TA_ALGO_SHA256,
	TA_ALGO_SHA384,
	TA_ALGO_SHA512,
	TA_ALGO_SHA3_224,
	TA_ALGO_SHA3_256,
	TA_ALGO_SHA3_384,
	TA_ALGO_SHA3_512,
	TA_ALGO_SM3,
};

/**
 * @struct hb_gmac_config
 * Define the gmac init config
 * @NO{S06E02C02}
 */
typedef struct hb_gmac_config {
	uint32_t		algo;		/**< gmac algo, TA_ALGO_AES_GMAC/TA_ALGO_SM4_GMAC */
	uint8_t			*key;		/**< key id, provided by key management module */
	uint8_t			*iv;		/**< IV data */
	uint32_t 		keylen;		/**< key length, keylen = sizeof(key_id) */
	uint32_t 		ivlen;		/**< iv length, only support 12 */
	uint8_t			reserve[4];	/**< reserved */
} hb_gmac_config;

/**
 * @struct ecies_param_t
 * Define the ecies params specified by ANSI X9.63 standard
 * @NO{S06E02C02}
 */
struct ecies_param_t {
	enum hash_algo 	kdf_hash_mode;			/**< ecies kdf hash mode */
	enum hash_algo 	hmac_hash_mode;			/**< ecies mac hash mode */
	uint8_t			*kdf_share_info_data;	/**< share info data used by kdf */
	uint8_t			*hmac_share_info_data;	/**< share info data used by hmac */
	size_t			kdf_share_info_len;		/**< kdf share info data length, range: [0, 1024] */
	size_t			hmac_share_info_len;	/**< hmac share info data length, range: [0, 1024] */
	size_t			hmac_key_len;			/**< hmac key length, range: [10, 128] */
};

/**
 * @struct hb_ecies_config
 * Define the ecies init config
 * @NO{S06E02C02}
 */
typedef struct hb_ecies_config {
	uint32_t 		algo;			/**< ecies algo, include TA_ALGO_ECIES_P256/TA_ALGO_ECIES_P384/TA_ALGO_ECIES_P521 */
	enum op_mode 	mode;			/**< operation mode, encrypt or decrypt */
	uint8_t			*key;			/**< key id, provided by key management module */
	uint32_t 		keylen;			/**< key length, keylen = sizeof(key_id) */
	struct ecies_param_t	ecies_param;	/**< ecies encrypt/decrypt params, follow ANSI X9.63 standard */
	uint8_t		reserve[4];			/**< reserved */
} hb_ecies_config;


/**
 * @def user role of SM9 key exchange
 */
#define SM9_INITIATOR        0		/**< initiator role of SM9 key exchange */
#define SM9_RESPONDER        1		/**< responder role of SM9 key exchange */

/**
 * @struct hb_sm9_config
 * Define the sm9 init config
 * @NO{S06E02C02}
 */
typedef struct hb_sm9_config {
	uint32_t 			algo;				/**< sm9 algo */
	enum op_mode 		mode;				/**< operation mode, encrypt or decrypt, sign or verify, derive */
	uint8_t				*master_key;		/**< master key id, provided by key management module */
	uint8_t				*id;				/**< id buffer, for sm9 encrypt/sign/derive */
	uint32_t 			master_keylen;		/**< master key length, keylen = sizeof(key_id) */
	size_t 				id_len;				/**< id length, range: [1, 8192) */
	uint8_t				reserve[4];			/**< reserved */
} hb_sm9_config;

/**
 * @struct ecies_param_t
 * Define the cipher mode and mac mode for ecies
 * @NO{S06E02C02}
 */
typedef struct sm9_kep_param_t {
	int 			role;				/**< api user role, SM9_INITIATOR/SM9_RESPONDER */
	uint8_t			*own_eph_key;		/**< own ephemeral key id, provided by key management module */
	uint8_t			*peer_eph_key;		/**< peer ephemeral key id, provided by key management module */
	uint32_t 		own_eph_keylen;		/**< own ephemeral key length, keylen = sizeof(key_id) */
	uint32_t 		peer_eph_keylen;	/**< peer ephemeral key length, keylen = sizeof(key_id) */
	uint8_t 		*peer_id;			/**< peer id buffer */
	size_t 			peer_idlen;			/**< peer id length, range: [1, 8192) */
} sm9_kep_param;

/**
 * @brief genearte gmac data
 *
 * @param[in] gmac_config gamc init config, see struct hb_gmac_config
 * @param[in] message data buffer
 * @param[in] message data length, range: [0, 16384]
 * @param[out] mac gamc buffer
 * @param[out] mac_len gamc buffer length, range: [16, )
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
TEEC_Result hb_crypto_gmac_generate(hb_gmac_config *gmac_config,
											uint8_t *message, size_t msg_len,
											uint8_t *mac, size_t *mac_len);

/**
 * @brief encrypt data with ecies
 *
 * @param[in] ecies_config ecies init config, see hb_ecies_config
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes, range: [1, 16384]
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes, depenon on curve and hmac type
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
TEEC_Result hb_crypto_ecies_encrypt(hb_ecies_config *ecies_config,
									   		uint8_t *in, size_t inlen,
									   		uint8_t *out, size_t *outlen);

/**
 * @brief decrypt data with ecies
 *
 * @param[in] ecies_config ecies init config, see hb_ecies_config
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes, depenon on curve and hmac type, max input len is 16581
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes, depenon on curve and hmac type
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
TEEC_Result hb_crypto_ecies_decrypt(hb_ecies_config *ecies_config,
									   		uint8_t *in, size_t inlen,
									   		uint8_t *out, size_t *outlen);



/**
 * @brief Allocate TA resources required for the SM9 operation and init the operation
 *
 * @param[in] context CA crypto context
 * @param[in] sm9_config init configure, see struct hb_sm9_config
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
TEEC_Result hb_crypto_sm9_init(struct hb_crypto_st *context, hb_sm9_config *sm9_config);

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
void hb_crypto_sm9_destroy(struct hb_crypto_st *context);

/**
 * @brief encrypt data with sm9
 *
 * @param[in] context CA crypto context
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes, range: [1, 16384]
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes, range: [inlen+96, ]
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
TEEC_Result hb_crypto_sm9_encrypt(struct hb_crypto_st *context, uint8_t *in, size_t inlen, 
                                                		   uint8_t *out, size_t *outlen);

/**
 * @brief decrypt data with sm9
 *
 * @param[in] context CA crypto context
 * @param[in] in input data
 * @param[in] inlen length of input data in bytes, range: [97, 16480]
 * @param[out] out output data
 * @param[out] outlen length of returned output data in bytes, range: [inlen-96, ]
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
TEEC_Result hb_crypto_sm9_decrypt(struct hb_crypto_st *context, uint8_t *in, size_t inlen, 
                                                			uint8_t *out, size_t *outlen);
 
/**
 * @brief generate the signature for the message
 *
 * @param[in] context CA crypto context
 * @param[in] data message data
 * @param[in] data_len length of message data in bytes, range: [1, 1024]
 * @param[out] sig signature data
 * @param[out] sig_len length of returned signature data in bytes, range: [97, ]
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
TEEC_Result hb_crypto_sm9_sign(struct hb_crypto_st *context, uint8_t *data, size_t data_len, 
                                                uint8_t *sig, size_t *sig_len);

/**
 * @brief verify a signature of the message is valid or not
 *
 * @param[in] context CA crypto context
 * @param[in] data message data
 * @param[in] data_len length of message data in bytes, range: [1, 1024]
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
TEEC_Result hb_crypto_sm9_verify(struct hb_crypto_st *context, uint8_t *data, size_t data_len, 
                                          uint8_t *sig, size_t sig_len, uint8_t *result);

/**
 * @brief compute the shared secret by sm9 definition
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
extern TEEC_Result hb_crypto_sm9_keyexchange(struct hb_crypto_st *context, sm9_kep_param *params,
									 			uint8_t *out_keyid_data, uint32_t *out_keyid_len);
/**
 * @brief read trng data from HSM
 * 
 * @NO{S06E03C04I}
 * @ASIL{B}
 * 
 * @param[out] buf: read buffer
 * @param[in] len: length to read
 *
 * @retval 0: success
 * @retval -1: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: None
 *
 * @callgraph
 * @callergraph
 * @design
 */
extern int hb_get_hwrng(void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __HB_CRYPTO_H__ */
