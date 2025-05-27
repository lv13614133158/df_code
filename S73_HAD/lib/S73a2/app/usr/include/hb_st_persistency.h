/**
 * @file hb_st_persistency.h
 *
 * @NO{S21E05C01}
 * @ASIL{B}
 *
 * Copyright 2022 - 2023, Horizon Robotics
 *
 */

#ifndef HB_ST_PERSISTENCY_H
#define HB_ST_PERSISTENCY_H


#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOG_TAG
#define LOG_TAG "persist_log"							/**< ALOG tag */

#endif

#define FILE_NAME_MAX_LEN 128							/**< file name max length */
#define FILE_NAME_USABLE_MAX_LEN 90

#define HB_PERSIST_OK						0		/**< persist no error */
#define HB_PERSIST_ERROR_NORMAL					(-20000)	/**< persist base error */
#define HB_PERSIST_ERROR_PARAM					(-20001)	/**< persist param error */
#define HB_PERSIST_ERROR_NOACCESS				(-20002)	/**< persist no access error */

#define HB_PERSIST_ERROR_MALLOC					(-20003)	/**< persist malloc error */
#define HB_PERSIST_ERROR_SOCKET					(-20004)	/**< persist socket errop */
#define HB_PERSIST_ERROR_CONNECT				(-20005)	/**< persist connect error */
#define HB_PERSIST_ERROR_BIND					(-20006)	/**< persist bind error */
#define HB_PERSIST_ERROR_LISTEN					(-20007)	/**< persist listen error */
#define HB_PERSIST_ERROR_SEND					(-20008)	/**< persist send error */
#define HB_PERSIST_ERROR_RECV					(-20009)	/**< persist recv error */

#define HB_PERSIST_ERROR_AUTH					(-20010)	/**< persist auth error */
#define HB_PERSIST_ERROR_UNSUPPORTALG				(-20011)	/**< persist unsupoort alg */

#define HB_PERSIST_ERROR_STORE					(-20012)	/**< persist store error */
#define HB_PERSIST_ERROR_LOAD					(-20013)	/**< persist load error */
#define HB_PERSIST_ERROR_DELETE					(-20014)	/**< persist delete error */

#define HB_PERSIST_ERROR_IMPORTKEY				(-20015)	/**< persist import key error */
#define HB_PERSIST_ERROR_CHECKPATH				(-20016)	/**< persist check path error */
#define HB_PERSIST_ERROR_UID					(-20017)
#define HB_PERSIST_WAIT_PAYLOAD					(-20018)

/**
 * @enum persist_cmd_e
 * Define server cmd
 */
typedef enum {
	HB_PERSIST_CMD_CONNECT = 0,	/**< connect cmd */
	HB_PERSIST_CMD_DCONNECT,	/**< disconnect cmd */
	HB_PERSIST_CMD_STORE,		/**< store data cmd */
	HB_PERSIST_CMD_LOAD,		/**< load data cmd */
	HB_PERSIST_CMD_DELETE		/**< delete data cmd */
} persist_cmd_e;

typedef enum {
	PERSIST_CIPHER_ECB_AES_128,
	PERSIST_CIPHER_ECB_AES_192,
	PERSIST_CIPHER_ECB_AES_256,
	PERSIST_CIPHER_CBC_AES_128,
	PERSIST_CIPHER_CBC_AES_192,
	PERSIST_CIPHER_CBC_AES_256,
	PERSIST_CIPHER_CTR_AES_128,
	PERSIST_CIPHER_CTR_AES_192,
	PERSIST_CIPHER_CTR_AES_256
} hb_persist_cipher_type;

typedef enum {
	PERSIST_HASH_SHA1,
	PERSIST_HASH_SHA256,
	PERSIST_HASH_SHA512
} hb_persist_hash_type;

/**
 * @struct st_msg_t
 * @brief Define the msg content transfer between client and server
 * @NO{S21E05C01}
 */
typedef struct {
	/* 客户端进程id,uid,gid */
	pid_t		pid;		/**< Client pid */
	uid_t		uid;		/**< Client uid */
	gid_t		gid;		/**< Client gid */
	char		username[64];
	/* 客户端socket fd */
	int32_t 	client_fd;	/**< client fd */
	/* 分配给客户的id，用于内部唯一识别 */
	int32_t 	client_id;	/**< client id */
	/* 服务端提供的服务对应msg命令字 */
	uint32_t	cmd;		/**< client use command */
	/* 返回值，小于0，表示失败，大于0 表示需要传输的数据长度 */
	int64_t 	ret;		/**< if ret < 0, means fail. if ret > 0 means next transfer length */
	/* 客户端地址 */
	uint64_t	client_addr;	/**< client address */
	/* 选择的加解密类型，参考 hb_persist_cipher_type */
	uint32_t	cipher;		/**< data encrypt used cipher */
	/* 选择的hash类型 参考 hb_persist_hash_type */
	uint32_t	hash;		/**< data degist used hash */
	/* 选择存储方式 */
	uint32_t	secstore;	/**< store way, 0 mean RPMB, 1 mean REE
					 * range:[0,1]; default 0
					 */
	/* 使用什么密钥，0 默认密钥，1     用户导入密钥 */
	uint8_t		keyselect;	/**< crypt use key. 0 mean use default key, 1 mean use user import key
					 * range:[0,1]; default: 0
					 */
	/* 保留字段 */
	uint8_t		reservedchar[3];	/**< reserved space for new function */
	uint32_t	reserved[3];	/**< reserved space for new function */
	/* 文件路径或数据唯一标识 */
	char		filename[FILE_NAME_MAX_LEN];	/**< file name */
}st_msg_t;

/**
 * @struct hb_persist_meta_data
 * @brief Define the context user need to send to client
 * @NO{S21E05C01}
 */
typedef struct {

	/* 保留字段 */
	uint32_t reserved[7];	/**< reserved space for new function */
	uint8_t reservedchar[2];	/**< reserved space for new function */

	/* 选择存储方式 */
	uint8_t secstore;		/**< store way, 0 mean RPMB, 1 mean REE
					 * range:[0,1]; default: 0
					 */

	/* 使用什么密钥，0 默认密钥，1     用户导入密钥 */
	uint8_t keyselect;		/**< crypt use key. 0 mean use default key, 1 mean use user import key
					 * range:[0,1]; default: 0
					 */

	/* 选择的加解密类型，参考 hb_persist_cipher_type */
	uint32_t cipher;		/**< data encrypt used cipher
					 * range:[0,8]; default: 0
					 */

	/* 选择的hash类型 参考 hb_persist_hash_type */
	uint32_t hash;			/**< data degist used hash
					 * range:[1,2]; default: 1
					 */

	/* 输出的数据长度 */
	uint32_t outlen; 		/**< output buffer length
					 * range:[0,); default: 0
					 */

	/* 输出的数据地址 */
	uint8_t *outbuf;		/**< output buffer */

	char path[FILE_NAME_MAX_LEN];	/**< key store name */

	/* 输入的加解密数据的长度 */
	uint32_t datalen;		/**< followed hb_persist_meta_data data size
					 * range:[0,); default: 0
					 */

	/* 输入的加解密数据存放地址 */
	unsigned char payload[0];	/**< followed hb_persist_meta_data data */
} hb_persist_meta_data;


/* 客户进程注册接口，会创建与服务进程的socket链接 */
/**
 * @NO{S21E05C01I}
 * @brief register user in secure storage 注册用户与进程到secure storage服务中
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval fd: opened connect fd to server 注册成功返回fd
 * @retval !=fd: register fail 注册失败
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_persist_register(void);

/**
 * @NO{S21E05C01I}
 * @brief register user in secure storage 注册用户与进程到secure storage服务中
 *
 * @param[in] persistdata: user key information 注册使用的用户key信息
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval fd: opened connect fd to server 注册成功返回fd
 * @retval !=fd: register fail 注册失败
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_persist_register_with_key(hb_persist_meta_data *persistdata);

/**
 * @NO{S21E05C01I}
 * @brief encrypt given data 对于输入的数据进行加密
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] fd: connected fd 与服务端连接的fd
 * @param[in] persistdata: data information and data want to encrypt 需要加密的数据信息
 *
 * @retval HB_PERSIST_OK: encrypt data success 加密成功
 * @retval !=HB_PERSIST_OK: encrypt data fail 加密失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_persist_encrypt_data(int32_t fd, hb_persist_meta_data *persistdata);

/**
 * @NO{S21E05C01I}
 * @brief decrypt given data 解密对应的数据，输出解密结果
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] fd: connected fd 与服务端连接的fd
 * @param[in] persistdata: data information and data want to decrypt 需要解密的数据信息
 *
 * @retval HB_PERSIST_OK: decrypt data success 解密成功
 * @retval !=HB_PERSIST_OK: decrypt data fail 解密失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_persist_decrypt_data(int32_t fd, hb_persist_meta_data *persistdata);

/**
 * @NO{S21E05C01I}
 * @brief delete given name data 从RPMB当中删除指定储存名称的数据
 *
 * @param[in] fd: connected fd 与服务端连接的fd
 * @param[in] file_name: data store name 需要删除的数据储存名称
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval HB_PERSIST_OK: delete data success 删除成功
 * @retval !=HB_PERSIST_OK: delete data fail 删除失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_persist_delete_data(int32_t fd, const char *file_name);

/**
 * @NO{S21E05C01I}
 * @brief delete given name data from given palce 从指定存储位置删除指定储存名称的数据
 *
 * @param[in] fd: connected fd 与服务端连接的fd
 * @param[in] file_name: data store name 需要删除的数据储存名称
 * @param[in] persistdata: data information and data want to delete 需要删除的数据信息
 *
 * @compatibility HW: J6
 *
 * @compatibility SW: 1.1.0
 *
 * @retval HB_PERSIST_OK: delete data success 删除成功
 * @retval !=HB_PERSIST_OK: delete data fail 删除失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_persist_delete_data_full(int32_t fd, const char *file_name, hb_persist_meta_data *persistdata);

/* 客户进程注销接口，会断开与服务进程的socket链接 */
/**
 * @NO{S21E05C01I}
 * @brief unregister data in secure storage 注销对应的fd
 *
 * @compatibility HW: J5/J6
 *
 * @compatibility SW: 1.1.0
 *
 * @param[in] fd: register fd 需要注销的fd
 *
 * @retval HB_PERSIST_OK: unregister success 注销成功
 * @retval !=HB_PERSIST_OK: unregister fail 注销失败
 * @callgraph
 * @callergraph
 * @design
 */
int64_t hb_persist_unregister(int32_t fd);

#ifdef __cplusplus
}
#endif

#endif  //HB_ST_PERSISTENCY_H

