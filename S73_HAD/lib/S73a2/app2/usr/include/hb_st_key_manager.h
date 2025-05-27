/**
 * @file hb_st_key_manager.h
 *
 * @NO{S21E05C02}
 * @ASIL{B}
 */
#ifndef HB_ST_KEY_MANAGER_H
#define HB_ST_KEY_MANAGER_H


#include <sys/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_SECURE_PREFIX				"/storage/secure"	/**< default secure prefix */
#define DEFAULT_SECURE_PREFIX_BAK			"/storage/secure_bak_"	/**< default secure backup prefix */

#ifndef LOG_TAG
#define LOG_TAG "st_log"	/**< ALOGE show */
#endif

#define HBST_OK						0	/**< success return */

#define HBST_ERR_PARAM					-1	/**< error input parameter */
#define HBST_ERR_KEYNAME				-2	/**< illegal file path */
#define HBST_ERR_MALLOC					-3	/**< malloc fail */

#define HBST_ERR_OPEN					-4	/**< open file or object fail */
#define HBST_ERR_FILEOPEN				HBST_ERR_OPEN
#define HBST_ERR_DELETE					-5	/**< delete file or object fail */
#define HBST_ERR_WR					-6	/**< write file or object fail */
#define HBST_ERR_RD					-7	/**< read file or object fail */
#define HBST_ERR_FILERD					HBST_ERR_RD
#define HBST_ERR_NULLOBJ				-8	/**< null object */

#define HBST_ERR_OLDFILE				-9	/**< store fail and recover to old file */
#define HBST_ERR_BADFILE				-10	/**< store fail and file is corrupt */
#define HBST_ERR_ENCRYPT				-11	/**< data encrypt fail */
#define HBST_ERR_VERIFY					-12	/**< data verify fail */

#define HBST_OPENSSL_ERR_CIPHER				-18	/**< openssl cipher fail */
#define HBST_OPENSSL_ERR_HASH				-19	/**< openssl get or check hash fail */

#define HBST_STORE_ERR_BASE				-10000	/**< store base fail */
#define HBST_LOAD_ERR_BASE				-10100	/**< load base fail */
#define HBST_IMPORT_ERR_BASE				-10200	/**< import base fail */
#define HBST_DELETE_ERR_BASE				-10300	/**< delete base fail */
#define HBST_INIT_ERR_BASE				-10400	/**< init base fail */
#define HBST_DEINIT_ERR_BASE				-10500	/**< deinit base fail */
#define HBST_UPDATE_ERR_BASE				-10600	/**< update base fail */

/*hb_st_key_store*/
#define  HBST_STORE_ERR_GENERIC			HBST_STORE_ERR_BASE				/**< store general error */
#define  HBST_STORE_ERR_PARAM			(HBST_STORE_ERR_BASE + HBST_ERR_PARAM)		/**< store param error */
#define  HBST_STORE_ERR_KEYPATH			(HBST_STORE_ERR_BASE + HBST_ERR_KEYNAME)	/**< store path error */
#define  HBST_STORE_ERR_MALLOC			(HBST_STORE_ERR_BASE + HBST_ERR_MALLOC)		/**< store malloc error */
#define  HBST_STORE_ERR_FILEOPEN 		(HBST_STORE_ERR_BASE + HBST_ERR_OPEN)		/**< store open error */
#define  HBST_STORE_ERR_DELFILE			(HBST_STORE_ERR_BASE + HBST_ERR_DELETE)	/**< store delete error */
#define  HBST_STORE_ERR_FILEWR			(HBST_STORE_ERR_BASE + HBST_ERR_WR)		/**< store write error */
#define  HBST_STORE_ERR_FILERD			(HBST_STORE_ERR_BASE + HBST_ERR_RD)		/**< store read error */
#define  HBST_STORE_ERR_FILENULL		(HBST_STORE_ERR_BASE + HBST_ERR_NULLOBJ)	/**< store null object error */
#define  HBST_STORE_ERR_OLDFILE			(HBST_STORE_ERR_BASE + HBST_ERR_OLDFILE)	/**< store back to old error */
#define  HBST_STORE_ERR_BADFILE			(HBST_STORE_ERR_BASE + HBST_ERR_BADFILE)	/**< store file corrupt error */
#define  HBST_STORE_ERR_VERIFY			(HBST_STORE_ERR_BASE + HBST_ERR_VERIFY)		/**< store verify error */
#define  HBST_STORE_ERR_ENCRYPT			(HBST_STORE_ERR_BASE + HBST_ERR_ENCRYPT)	/**< store encrypt error */
#define  HBST_STORE_ERR_FILELCK			(HBST_STORE_ERR_BASE + HBST_ERR_FILELCK)
#define  HBST_STORE_ERR_FILEUNLCK		(HBST_STORE_ERR_BASE + HBST_ERR_FILEUNLCK)

#define  HBST_STORE_ERR_CIPHER			(HBST_STORE_ERR_BASE + HBST_OPENSSL_ERR_CIPHER)	/**< store openssl cipher error */
#define  HBST_STORE_ERR_HASH			(HBST_STORE_ERR_BASE + HBST_OPENSSL_ERR_HASH)	/**< store openssl hash error */

/*hb_st_key_info_read/hb_st_skey_read/hb_st_pubkey_read*/
#define  HBST_LOAD_ERR_GENERIC			HBST_LOAD_ERR_BASE				/**< load general error */
#define  HBST_LOAD_ERR_PARAM			(HBST_LOAD_ERR_BASE + HBST_ERR_PARAM)		/**< load param error */
#define  HBST_LOAD_ERR_KEYPATH			(HBST_LOAD_ERR_BASE + HBST_ERR_KEYNAME)		/**< load path error */
#define  HBST_LOAD_ERR_MALLOC			(HBST_LOAD_ERR_BASE + HBST_ERR_MALLOC)		/**< load malloc error */
#define  HBST_LOAD_ERR_FILEOPEN 		(HBST_LOAD_ERR_BASE + HBST_ERR_OPEN)		/**< load open error */
#define  HBST_LOAD_ERR_DELFILE			(HBST_LOAD_ERR_BASE + HBST_ERR_DELETE)		/**< load delete error */
#define  HBST_LOAD_ERR_FILEWR			(HBST_LOAD_ERR_BASE + HBST_ERR_WR)		/**< load write error */
#define  HBST_LOAD_ERR_FILERD			(HBST_LOAD_ERR_BASE + HBST_ERR_RD)		/**< load read error */
#define  HBST_LOAD_ERR_FILENULL			(HBST_LOAD_ERR_BASE + HBST_ERR_NULLOBJ)		/**< load obj error */
#define  HBST_LOAD_ERR_OLDFILE			(HBST_LOAD_ERR_BASE + HBST_ERR_OLDFILE)		/**< load back to old error */
#define  HBST_LOAD_ERR_BADFILE			(HBST_LOAD_ERR_BASE + HBST_ERR_BADFILE)		/**< load file corrupt error */
#define  HBST_LOAD_ERR_VERIFY			(HBST_LOAD_ERR_BASE + HBST_ERR_VERIFY)		/**< load verify error */
#define  HBST_LOAD_ERR_ENCRYPT			(HBST_LOAD_ERR_BASE + HBST_ERR_ENCRYPT)		/**< load encrypt error */
#define  HBST_LOAD_ERR_FILELCK			(HBST_LOAD_ERR_BASE + HBST_ERR_FILELCK)
#define  HBST_LOAD_ERR_FILEUNLCK		(HBST_LOAD_ERR_BASE + HBST_ERR_FILEUNLCK)

#define  HBST_LOAD_ERR_CIPHER			(HBST_LOAD_ERR_BASE + HBST_OPENSSL_ERR_CIPHER)	/**< load openssl cipher error */
#define  HBST_LOAD_ERR_HASH			(HBST_LOAD_ERR_BASE + HBST_OPENSSL_ERR_HASH)	/**< load openssl hash error */

/* hb_st_key_import */
#define  HBST_IMPORT_ERR_GENERIC		HBST_IMPORT_ERR_BASE				/**< import general error */
#define  HBST_IMPORT_ERR_PARAM			(HBST_IMPORT_ERR_BASE + HBST_ERR_PARAM)		/**< import param error */
#define  HBST_IMPORT_ERR_KEYPATH		(HBST_IMPORT_ERR_BASE + HBST_ERR_KEYNAME)	/**< import path error */
#define  HBST_IMPORT_ERR_MALLOC			(HBST_IMPORT_ERR_BASE + HBST_ERR_MALLOC)	/**< import malloc error */
#define  HBST_IMPORT_ERR_FILEOPEN 		(HBST_IMPORT_ERR_BASE + HBST_ERR_OPEN)		/**< import open error */
#define  HBST_IMPORT_ERR_DELFILE		(HBST_IMPORT_ERR_BASE + HBST_ERR_DELETE)	/**< import delete error */
#define  HBST_IMPORT_ERR_FILEWR			(HBST_IMPORT_ERR_BASE + HBST_ERR_WR)		/**< import write error */
#define  HBST_IMPORT_ERR_FILERD			(HBST_IMPORT_ERR_BASE + HBST_ERR_RD)		/**< import read error */
#define  HBST_IMPORT_ERR_FILENULL		(HBST_IMPORT_ERR_BASE + HBST_ERR_NULLOBJ)	/**< import null object error */

#define  HBST_IMPORT_ERR_OLDFILE		(HBST_IMPORT_ERR_BASE + HBST_ERR_OLDFILE)	/**< import back to old error */
#define  HBST_IMPORT_ERR_BADFILE		(HBST_IMPORT_ERR_BASE + HBST_ERR_BADFILE)	/**< import file corrupt error */
#define  HBST_IMPORT_ERR_VERIFY			(HBST_IMPORT_ERR_BASE + HBST_ERR_VERIFY)	/**< import verify error */
#define  HBST_IMPORT_ERR_ENCRYPT		(HBST_IMPORT_ERR_BASE + HBST_ERR_ENCRYPT)	/**< import encrypt error */
#define  HBST_IMPORT_ERR_FILELCK		(HBST_IMPORT_ERR_BASE + HBST_ERR_FILELCK)
#define  HBST_IMPORT_ERR_FILEUNLCK		(HBST_IMPORT_ERR_BASE + HBST_ERR_FILEUNLCK)

/*hb_st_key_delete*/
#define  HBST_DELETE_ERR_GENERIC		HBST_DELETE_ERR_BASE				/**< delete general error */
#define  HBST_DELETE_ERR_PARAM			(HBST_DELETE_ERR_BASE + HBST_ERR_PARAM)		/**< delete param error */
#define  HBST_DELETE_ERR_KEYPATH		(HBST_DELETE_ERR_BASE + HBST_ERR_KEYNAME)	/**< delete path error */
#define  HBST_DELETE_ERR_MALLOC			(HBST_DELETE_ERR_BASE + HBST_ERR_MALLOC)	/**< delete malloc error */
#define  HBST_DELETE_ERR_FILEOPEN 		(HBST_DELETE_ERR_BASE + HBST_ERR_OPEN)		/**< delete open error */
#define  HBST_DELETE_ERR_DELFILE		(HBST_DELETE_ERR_BASE + HBST_ERR_DELETE)	/**< delete error */
#define  HBST_DELETE_ERR_FILEWR			(HBST_DELETE_ERR_BASE + HBST_ERR_WR)		/**< delete write error */
#define  HBST_DELETE_ERR_FILERD			(HBST_DELETE_ERR_BASE + HBST_ERR_RD)		/**< delete read error */
#define  HBST_DELETE_ERR_OLDFILE		(HBST_DELETE_ERR_BASE + HBST_ERR_OLDFILE)	/**< delete back to old error */
#define  HBST_DELETE_ERR_BADFILE		(HBST_DELETE_ERR_BASE + HBST_ERR_BADFILE)	/**< delete file corrupt error */
#define  HBST_DELETE_ERR_VERIFY			(HBST_DELETE_ERR_BASE + HBST_ERR_VERIFY)	/**< delete verify error */
#define  HBST_DELETE_ERR_ENCRYPT		(HBST_DELETE_ERR_BASE + HBST_ERR_ENCRYPT)	/**< delete encrypt error */
/*hb_st_key_init*/
#define HBST_INIT_ERR_GENERIC			HBST_INIT_ERR_BASE				/**< init general error */
#define HBST_INIT_ERR_PARAM			(HBST_INIT_ERR_BASE + HBST_ERR_PARAM)		/**< init param error */
#define HBST_INIT_ERR_CREATDIR			(HBST_INIT_ERR_BASE + HBST_ERR_CREATDIR)
#define HBST_INIT_ERR_OPEN			(HBST_INIT_ERR_BASE + HBST_ERR_OPEN)		/**< init open error */
#define HBST_INIT_ERR_FILERD			(HBST_INIT_ERR_BASE + HBST_ERR_RD)		/**< init read error */
/*hb_st_key_deinit*/
#define HBST_DEINIT_ERR_GENERIC			HBST_DEINIT_ERR_BASE				/**< deinit general error */
#define HBST_DEINIT_ERR_CREATDIR		(HBST_DEINIT_ERR_BASE + HBST_ERR_CREATDIR)

/*hb_st_key_update*/
#define HBST_UPDATE_ERR_GENERIC 		HBST_UPDATE_ERR_BASE				/**< update general error */
#define HBST_UPDATE_ERR_PARAM 			(HBST_ERR_PARAM + HBST_UPDATE_ERR_BASE)		/**< update param error */
#define HBST_UPDATE_ERR_MALLOC			(HBST_UPDATE_ERR_BASE + HBST_ERR_MALLOC)	/**< update malloc error */

/* Storage is provided by the Rich Execution Environment (REE) */
#define SECURE_STORAGE_PRIVATE_REE		1u
/* Storage is the Replay Protected Memory Block partition of an eMMC device */
#define SECURE_STORAGE_PRIVATE_RPMB		0u

#define HB_MAX_PATH_LEN 128u

#define HB_INVALID_KEY_ID      (-1)

//coverity[misra_c_2012_rule_5_6_violation:SUPPRESS]
typedef int64_t key_serial_t;

#define TEE_TYPE_CMAC_AES TEE_TYPE_AES
/**
 * @enum hb_key_type
 * List of key type
 */
typedef enum {
TEE_TYPE_HMAC_SHA224            =   0xA0000003,
TEE_TYPE_HMAC_SHA256            =   0xA0000004,
TEE_TYPE_HMAC_SHA384            =   0xA0000005,
TEE_TYPE_HMAC_SHA512            =   0xA0000006,
TEE_TYPE_HMAC_SM3               =   0xA0000007,
TEE_TYPE_AES			= 0xA0000010,	/**< AES key	 */
TEE_TYPE_SM4			= 0xA0000014,
TEE_TYPE_RSA_PUBLIC_KEY		= 0xA0000030,	/**< RSA public key, used in RSA2048  pkcs1.5 */
TEE_TYPE_RSA_KEYPAIR		= 0xA1000030,	/**< RSA key pair */
TEE_TYPE_ECDSA_PUBLIC_KEY	= 0xA0000041,	/**< ECDSA public key */
TEE_TYPE_ECDSA_KEYPAIR		= 0xA1000041,	/**< ECDSA key pair */
TEE_TYPE_ED25519_PUBLIC_KEY	= 0xA0000043,	/**< ED25519 public key */
TEE_TYPE_ED25519_KEYPAIR	= 0xA1000043,	/**< ED25519 key pair */
TEE_TYPE_X25519_PUBLIC_KEY	= 0xA0000044,	/**< X25519 public key */
TEE_TYPE_X25519_KEYPAIR 	= 0xA1000044,	/**< X25519 key pair */
TEE_TYPE_STDATA			= 0xA00000C0,	/**< store data */
TEE_TYPE_SM2_DSA_PUBLIC_KEY	= 0xA0000045,
TEE_TYPE_SM2_DSA_KEYPAIR	= 0xA1000045,
TEE_TYPE_SM2_KEP_PUBLIC_KEY	= 0xA0000046,
TEE_TYPE_SM2_KEP_KEYPAIR	= 0xA1000046,
TEE_TYPE_SM2_PKE_PUBLIC_KEY        = 0xA0000047,
TEE_TYPE_SM2_PKE_KEYPAIR      = 0xA1000047,
TEE_TYPE_SM9_DSA_PUBLIC_KEY   = 0xA000004a,
TEE_TYPE_SM9_DSA_KEYPAIR      = 0xA100004a,
TEE_TYPE_SM9_KEP_PUBLIC_KEY   = 0xA000004b,
TEE_TYPE_SM9_KEP_KEYPAIR      = 0xA100004b,
TEE_TYPE_SM9_PKE_PUBLIC_KEY   = 0xA000004c,
TEE_TYPE_SM9_PKE_KEYPAIR      = 0xA100004c,
TEE_TYPE_SM9_TEM_KEP_PUBLIC_KEY    = 0xA000004d,
TEE_TYPE_SM9_TEM_KEP_KEYPAIR       = 0xA100004d,

TEE_TYPE_GENERIC_SECRET       = 0xA0000000,
TEE_TYPE_ED448_PUBLIC_KEY     = 0xA0000048,
TEE_TYPE_ED448_KEYPAIR        = 0xA1000048,
TEE_TYPE_X448_PUBLIC_KEY      = 0xA0000049,
TEE_TYPE_X448_KEYPAIR         = 0xA1000049,
TEE_TYPE_FDE_DERIVE_KEY       = 0xA00000EE,	/**< keytype for fde derive */

TEE_TYPE_HMAC_SHA3_224             = 0xA0000008,
TEE_TYPE_HMAC_SHA3_256             = 0xA0000009,
TEE_TYPE_HMAC_SHA3_384             = 0xA000000A,
TEE_TYPE_HMAC_SHA3_512             = 0xA000000B,
} hb_key_type;

/**
 * @struct hb_user_id
 * @brief Record the information about user
 * @NO{S21E05C02}
 */
typedef struct {
uid_t uid;	/**< user id of user */
gid_t gid;	/**< group id of user */
} hb_user_id;

/**
 * @struct hb_key_meta_data
 * @brief Record key information
 * @NO{S21E05C02}
 */
typedef struct {
	uint32_t	version;	/**< key version */
	/* 暂未使用 */
	//coverity[misra_c_2012_rule_5_8_violation:SUPPRESS], ## violation reason SYSSW_V_5.8_02
	uint32_t	index;		/**< key index */
	hb_user_id	usergroup;	/**< user and group information */

	/*
	用于判断key的来源：
	key_src=0表示客户原生的key(非在设备上新生成).
	key_src=1表示客户新生成的key(在设备上新生成).
	接口未使用
	*/
	uint32_t	key_src;	/**< key source if is create in the device
					* range:[0,1]; default:0
					*/
	/*
	import接口关注，其他不管
	bit0=1:导出时使用cloud_pub_key加密
	bit0=0:导出时不使用cloud_pub_key加密.
	举例：只有Reset_AES_key 置1；
	*/
	uint32_t	export_type;	/**< key export type
					* range:[0,1]; default:0
					*/
	/* 密钥存储的类型：
	bit0=1:key被设备kek加密过, 适用于tee新生成的私钥.
	bit0=0:key未被设备kek加密过;适用于tee新生成的公钥.
	bit1=1:key被一级密钥(rsa)加密过，适用于二级密钥(aes). 使用security_pri_key(rsa2048私钥)解密.
	bit1=0:key未被一级密钥加密过，适用于tee新生成公私钥和客户原生且非二级密钥.
	bit2=1:key被二级密钥(aes)加密过,适用于客户原生密钥.使用二级kek AesKey解密.
	bit2=0:key未被二级密钥加密过，适用于tee新生公私钥.
	bit3=1:使用客户公钥servicePub验证签名.
	bit3=0:不使用客户公钥servicePub验证签名.
	bit4=1:使用客户根公钥root_pub_key验证签名.
	bit4=0:不使用客户根公钥root_pub_key验证签名.


	举例：
	1 从RPMB读出后，注入二级公钥明文servicePub及签名servicePubSign进入tee : key_st_type=0x10=0b10000，需要使用根公钥验证明文签名.
	2 从RPMB读出后，注入二级kek密文encryptedAesKey及二级kek明文签名aesKeySign进入tee :key_st_type= 0xa = 0b1010，需要使用security_pri_key(rsa2048私钥)解密，使用客户公钥验证明文签名.
	3 从RPMB读出后，注入CMAC_AES_Key:key_st_type=0xc=0b1100，需要tee使用二级 KEK解密，使用客户公钥验证明文签名.
	4 从RPMB读出后，注入IOT密钥：key_st_type=0xc=0b1100，需要tee使用二级 KEK解密，使用客户公钥验证明文签名.
	5 从RPMB读出后，注入TEE新生密钥Encrypt_AES_Key：key_st_type==0x1=0b0001，需要tee使用J5 KEK解密
	6 从RPMB读出后，注入TEE新生密钥Reset_AES_Key：key_st_type==0x1=0b0001,需要tee使用J5 KEK解密
	*/
	uint32_t	key_st_type;	/**< key store type, need to decrypt by which key
					* range:[0,31]; default:0
					*/

	/* 密钥类型:见hb_key_type  */
	uint32_t	key_type;	/**< key type */

	union {
		struct {
			uint32_t	data_type;	/**< Data type of the key, data_type=1: data is sensitive data, data_type=0: data is key
							 * range:[0,1]; default: 0
							 */

			uint32_t	keyid;		/**< this key or data decrypt need keyid
							 * range:[0,); default: 0
							 */

			/* 选择的加解密类型，参考 hb_persist_cipher_type */
			uint32_t	cipher;		/**< data encrypt used cipher
							 * range:[0,8]; default: 0
							 */

			/* 选择的hash类型 参考 hb_persist_hash_type */
			uint32_t	hash;		/**< data degist used hash
							 * range:[1,2]; default: 1
							 */
		};
		uint32_t reserved[4];	/* reserved[0] 0表示密钥存储，1表示文件存储 文件存储时，reserved[1] keyid reserved[2] 文件cipher类型 reserved[3] 文件digest类型 */
	};

	/*
	存储方式
	0: rpmb存储
	1: REE FS存储
	*/
	uint8_t		store_mode;	/**< store mode, RPMB or REE FS
					 * range:[0,1]; default: 0
					 */
	uint8_t		key_workspace;	/**< key work in OPTEE or HSM, 0 is HSM, 1 is OPTEE. Only supports importing 25519 and symmetric keys into Optee.
					 * range:[0,1]; default: 0 */
	uint8_t		reservedchar[2];/**< reserved bits */
	uint32_t	reserved2[3];	/**< reserved bits */

	/* 密钥keysize大小，单位bit,如rsa2048：keysize=2048 */
	uint32_t	keysize;	/**< key size
					 * range:[0:); default: 4096
					 */

	/* 元数据长度 */
	uint32_t	keydata_len;	/**< data length in payload
					 * range:[0,); default: 0
					 */

	/* 摘要数据长度：如果没有摘要数据则为0 */
	uint64_t	digest_len;	/**< digest length
					 * range:[0,); default: 0
					 */

	/* 密钥内容+摘要数据内容：rpmb上数据形如: --hb_key_meta_data | keydata | digest； 传二进制数据；
	非对称密钥格式：真正实现时决定ned 、pem or DER？*/
	unsigned char payload[0];	/**< data head */
} hb_key_meta_data;

//coverity[misra_c_2012_rule_5_7_violation:SUPPRESS], ## violation reason SYSSW_V_5.7_01
struct hobot_km_base_info {
	int64_t key_id; /**< key id from hsm */
	uint8_t  desc_str[HB_MAX_PATH_LEN];	/**< key name string */
	uint32_t key_size; /**< key length in bit */
	uint32_t key_type; /**< key type */
	uint32_t curve_type; /**< ecc curve type */
};

/**
 * @NO{S21E05C02I}
 * @brief key create 自动创建key
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] type: key type key的类型
 * @param[in] description: key description key的名称
 * @param[in] payload: secure key add option key导入的参数
 * @param[in] plen: option len payload的长度
 * @param[in] ringid: keyring id
 *
 * @return key_id: key create success key的创建成功，返回keyid, errno: fail key的创建失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_add(const char *type,
	const char *description,
	const void *payload,
	size_t plen,
	key_serial_t ringid);

/**
 * @NO{S21E05C02I}
 * @brief key read 读取key的内容
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] id: key id 需要读取的key的id
 * @param[out] buffer: key infomation 读取出的key信息
 * @param[in] buflen: buffer len 供读取出的key信息存放的空间大小
 *
 * @return length: read length or read need length 读取出来的数据长度或需要的空间大小, errno: fail 读取失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_skey_read(key_serial_t id, char *buffer, size_t buflen);

/**
 * @NO{S21E05C02I}
 * @brief pubkey key read 公钥读取
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] id: key id 读取的公钥的key id
 * @param[out] buffer: key infomation 读取出的key信息
 * @param[in] buflen: buffer len 供读取出的key信息存放的空间大小
 *
 * @return length: read length or read need length 读取出来的数据长度或需要的空间大小, errno: fail 读取失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_pubkey_read(key_serial_t id, char *buffer, size_t buflen);

/**
 * @NO{S21E05C02I}
 * @brief key update 密钥更新
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] id: update keyid 需要更新的密钥
 * @param[in] payload: secure key update option 密钥更新配置
 * @param[in] plen: option len 配置长度
 *
 * @data_updated s_ctx_secsav: include secsav context and session
 *
 * @return HBST_OK: key create success, errno: fail
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_update(key_serial_t id, const void *payload, size_t plen);

/**
 * @NO{S21E05C02I}
 * @brief special key read 特殊的key读取方式
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] id: key id 需要读取的key id
 * @param[out] buffer: key infomation 读出的数据存放的地址
 * @param[in] buflen: buffer len 读出的数据存放空间的大小
 * @param[in] cmd: special read cmd 特殊读取的指令
 *
 * @data_updated s_ctx_secsav: include secsav context and session 包含secsav TA使用的context与session
 *
 * @return length: read length or read need length 读取出来的数据长度或需要的空间大小, errno: fail 读取失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_spec_read(key_serial_t id, char *buffer, size_t buflen, unsigned char cmd);

/**
 * @NO{S21E05C02I}
 * @brief key search 搜索对应的keyid
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] ringid: key ring id
 * @param[in] type: key type key的类型
 * @param[in] description: key name key的名称
 * @param[in] destringid: key destringid 目标ring id
 *
 * @return keyid: searched key id 搜索到的key id
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_search(key_serial_t ringid, const char *type, const char *description, key_serial_t destringid);

/**
 * @NO{S21E05C02I}
 * @brief invalidate key 作废key
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] id: key id 需要作废的key id
 *
 * @retval HBST_OK: invalidate success 成功使key无效
 * @retval !=HBST_OK: invalidate fail 使key无效失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_invalidate(key_serial_t id);

/**
 * @NO{S21E05C02I}
 * @brief delete all keys 使所有key注销
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval HBST_OK: invalidate success 成功使key无效
 * @retval !=HBST_OK: invalidate fail 使key无效失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_clear_all(void);

/**
 * @NO{S21E05C02I}
 * @brief show key list 输出所有key信息
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval HBST_OK: show key list success 成功读取密钥信息
 * @retval !=HBST_OK: show key list fail 读取密钥信息失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_show(struct hobot_km_base_info *key_list, uint32_t *key_list_size);

/**
 * @NO{S21E05C02I}
 * @brief input key encrypt and store 对于输入的key进行加密并储存
 *
 * @param[in] key_name: The key name to store key 储存key所使用的名称
 * @param[in] key_data: key information and data key保存的信息以及key的数据
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_read s_backupfile_flag: if store file have backup 标志是否使用备份保存
 * @data_updated s_file_lock: file lock 读写文件所使用的锁
 * @data_read s_completeinit_flag: complete init flag 标识是否初始化完成
 *
 * @retval HBST_OK: store success 加密并储存成功
 * @retval !=HBST_OK: store fail 加密并储存失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_store(const char *key_name, hb_key_meta_data *key_data);

/**
 * @NO{S21E05C02I}
 * @brief read key information 读取key储存信息
 *
 * @param[in] key_name: The name to read data 读取的key储存用的名称
 * @param[in] key_data: read key information 读取的key的信息
 * @param[out] key_data: read key information 读取的key的信息
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_read s_backupfile_flag: if store file have backup 标志是否使用备份保存
 * @data_updated s_file_lock: file lock 读写文件所使用的锁
 * @data_read s_completeinit_flag: complete init flag 标志初始化是否完成
 *
 * @retval HBST_OK: key information read success 成功读取key的信息
 * @retval !=HBST_OK: key information read fail 读取kei的信息失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_info_read (const char *key_name, hb_key_meta_data *key_data);

/**
 * @NO{S21E05C02I}
 * @brief import key from name or key data 从储存名称或者key内容中导入key
 *
 * @param[in] key_name: The name to import key key储存时所使用的名称
 * @param[in] key_data: import key data 导入的key的信息与数据
 * @param[in] description: key description key导入后使用的名称
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_read s_ctx_secsav: secsav context 包含secsav TA所使用的context与session
 * @data_read s_backupfile_flag: if store file have backup  标志储存时是否使用备份
 * @data_updated s_file_lock: file lock 读写文件时所使用的锁
 * @data_read s_completeinit_flag: complete init flag 标志初始化是否完成
 *
 * @retval keyid: key import success 导入key成功，返回keyid
 * @retval !=keyid: key import fail 导入key失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_keydesc_import(const char *key_name, hb_key_meta_data *key_data, const char *description);

/**
 * @NO{S21E05C02I}
 * @brief import key from name or key data 从储存名称或者key内容中导入key
 *
 * @param[in] key_name: The name to import key key储存时所使用的名称
 * @param[in] key_data: import key data 导入的key的信息与数据
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval keyid: key import success 导入key成功，返回keyid
 * @retval !=keyid: key import fail 导入key失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_import(const char *key_name, hb_key_meta_data *key_data);

/**
 * @NO{S21E05C02I}
 * @brief delete data with given data name 删除储存的数据
 *
 * @param[in] data_name: data name 储存数据所使用的名称
 * @param[in] key_data: data information 数据的信息
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_updated s_file_lock: file lock 读写文件使用的锁
 * @data_read s_backupfile_flag: if store file have backup 标志是否使用备份
 * @data_read s_completeinit_flag: complete init flag 标志是否初始化完成
 *
 * @retval HBST_OK: delete data success 删除数据成功
 * @retval !=HBST_OK: delete data fail 删除数据失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_data_delete(const char *data_name, hb_key_meta_data *key_data);

/**
 * @NO{S21E05C02I}
 * @brief delete data with given key name 删除储存的key
 *
 * @param[in] key_name: key name 储存key所使用的名称
 * @param[in] key_data: key information key的信息
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval HBST_OK: delete data success 删除key成功
 * @retval !=HBST_OK: delete data fail 删除key失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_delete(const char *key_name, hb_key_meta_data *key_data);

/**
 * @NO{S21E05C02I}
 * @brief encrypt data and store data 加密数据并且进行储存
 *
 * @param[in] data_name: data store file name 数据储存使用的名称
 * @param[in] file_data: data information 数据储存的信息与内容
 * @param[out] outbuf: output data 加密后的输出数据
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_read s_file_lock: file lock 读写文件使用的锁
 * @data_read s_backupfile_flag: if store file have backup 标志是否使用备份
 * @data_read s_completeinit_flag: complete init flag 标志是否初始化完成
 *
 * @retval >=0: store data success,return data length or success
 		储存数据成功，返回加密数据长度，或者成功标记
 * @retval <0: store data fail 储存数据失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_file_store(const char *data_name, hb_key_meta_data *file_data, unsigned char **outbuf);

/**
 * @NO{S21E05C02I}
 * @brief load data and decrypt data 读取并且解密数据
 *
 * @param[in] data_name: data load file name 需要进行读取的数据名称
 * @param[in] file_data: data information 读取的数据信息与内容
 * @param[out] outbuf: output data 解密后的输出数据，附带hb_key_meta_data的头
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_read s_file_lock: file lock 读写文件使用的锁
 * @data_read s_backupfile_flag: if store file have backup 标志是否使用备份
 * @data_read s_completeinit_flag: complete init flag 标志是否初始化完成
 *
 * @retval HBST_OK: load data success 读取数据成功
 * @retval !=HBST_OK: load data fail 读取数据失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_file_load(const char *data_name, hb_key_meta_data *file_data, unsigned char **outbuf);

/**
 * @NO{S21E05C02I}
 * @brief init secure storage and init global variable 初始化secure storage所用的TA并且初始化全局变量
 *
 * @param[in] main_prefix: main storage prefix 主要储存使用的前缀
 * @param[in] backup_prefix: backup storage prefix 备份储存使用的前缀
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_updated s_backupfile_flag: if store file have backup 标识是否使用备份
 * @data_updated s_file_lock: file lock 读写文件使用的锁
 * @data_updated s_sercuremainprefix: main prefix 主要储存的前缀
 * @data_updated s_sercurebackupprefix: backup prefix 备份储存的前缀
 * @data_updated s_completeinit_flag: complete init flag 标识是否初始化完成
 * @data_updated s_ctx_secstor: include secstor context and session 记录secstor TA所用的context与session
 * @data_updated s_ctx_secsav: include secsav context and session 记录secsav TA所用的context与session
 *
 * @retval HBST_OK: init success 成功初始化
 * @retval !=HBST_OK: init fail 初始化失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_init(const char *main_prefix, const char *backup_prefix);

/**
 * @NO{S21E05C02I}
 * @brief deinit secure storage and deinit global variable 反初始化secure storage所用的TA并且反初始化全局变量
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @data_updated s_file_lock: file lock 读写文件使用的锁
 * @data_updated s_completeinit_flag: complete init flag 标识是否初始化完成
 * @data_updated s_ctx_secstor: include secstor context and session 记录secstor TA所用的context与session
 * @data_updated s_ctx_secsav: include secsav context and session 记录secsav TA所用的context与session
 *
 * @retval true: deinit success 成功反初始化
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_st_key_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  //HB_ST_KEY_MANAGER_H

