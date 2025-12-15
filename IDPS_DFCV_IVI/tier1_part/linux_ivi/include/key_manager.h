/**
 * @file key_manager.h
 * @brief 密钥管理库头文件
 * @version 1.0 提供基础秘钥存储能力
 * @date 2025.11.11
 */

#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

/*===== 版本信息 =====*/
#define YWKM_VER_MAJOR   1
#define YWKM_VER_MINOR   0

#define MK_VER_CODE(maj,min)    ((uint32_t)(((maj) << 16) | ((min))))
#define YWKM_VER_CODE     MK_VER_CODE(YWKM_VER_MAJOR, YWKM_VER_MINOR)  


/*===== 常量定义 =====*/
#define YWKM_KEY_ID_MAX_LEN         32
#define YWKM_META_DATA_SIZE         128
#define YWKM_KEY_DATA_MAX_LEN       0x10000

#define YWKM_STORE_MAGIC            0x54534D4B   /* "KMST" */

/*===== 错误码定义 =====*/
#define YWKM_SUCCESS                (0)
#define YWKM_ERROR_INVALID_PARAM    (-1)
#define YWKM_ERROR_MEMORY_ALLOC     (-2)
#define YWKM_ERROR_STORAGE_FAILED   (-3)
#define YWKM_ERROR_KEY_NOT_FOUND    (-4)
#define YWKM_ERROR_KEY_EXISTS       (-5)
#define YWKM_ERROR_BUFFER_TOO_SMALL (-6)
#define YWKM_ERROR_NOT_INITIALIZED  (-7)
#define YWKM_ERROR_CRYPTO_FAILED    (-8)
#define YWKM_ERROR_HARDWARE_FAILURE (-9)
#define YWKM_ERROR_PERMISSION_DENIED (-10)
#define YWKM_ERROR_ENCRYPT_FAILED   (-11)
#define YWKM_ERROR_DECRYPT_FAILED   (-12)

#define YWKM_ERROR_COUNT            13

/*===== 密钥用途 =====*/
#define YWKM_PURPOSE_NULL         (0x00000000U)  /* 未指定 */
#define YWKM_PURPOSE_ENCRYPT      (0x00000001U)  /* 加密 */
#define YWKM_PURPOSE_DECRYPT      (0x00000002U)  /* 解密 */
#define YWKM_PURPOSE_SIGN         (0x00000004U)  /* 签名 */
#define YWKM_PURPOSE_VERIFY       (0x00000008U)  /* 验证 */
#define YWKM_PURPOSE_DERIVE       (0x00000010U)  /* 密钥派生 */
#define YWKM_PURPOSE_WRAP         (0x00000020U)  /* 密钥包装 */
#define YWKM_PURPOSE_UNWRAP       (0x00000040U)  /* 密钥解包 */

/* 未指定秘钥 */
#define YWKM_KEY_TYPE_NULL          0x0000
/* 非对称密钥 - RSA (0x1000 - 0x1FFF) */
#define YWKM_KEY_TYPE_RSA_2048      0x1002  /* RSA-2048密钥 */
#define YWKM_KEY_TYPE_RSA_3072      0x1003  /* RSA-3072密钥 */
#define YWKM_KEY_TYPE_RSA_4096      0x1004  /* RSA-4096密钥 */
/* 非对称密钥 - ECC (0x2000 - 0x2FFF) */
#define YWKM_KEY_TYPE_ECC_P256      0x2001  /* ECC P-256密钥 */
#define YWKM_KEY_TYPE_ECC_P384      0x2002  /* ECC P-384密钥 */
#define YWKM_KEY_TYPE_ECC_P521      0x2003  /* ECC P-521密钥 */
#define YWKM_KEY_TYPE_SM2           0x2004  /* 国密SM2密钥 */
/* HMAC密钥 (0x3000 - 0x3FFF) */
#define YWKM_KEY_TYPE_HMAC_SHA256   0x3001  /* HMAC-SHA256密钥 */
#define YWKM_KEY_TYPE_HMAC_SHA384   0x3002  /* HMAC-SHA384密钥 */
#define YWKM_KEY_TYPE_HMAC_SHA512   0x3003  /* HMAC-SHA512密钥 */
#define YWKM_KEY_TYPE_HMAC_SM3      0x3004  /* HMAC-SM3密钥 */
/* 派生密钥 (0x4000 - 0x4FFF) */
#define YWKM_KEY_TYPE_DERIVED       0x4001  /* 派生密钥 */
/* 对称密钥 (0x5001 - 0x5FFF) */
#define YWKM_KEY_TYPE_AES_128       0x5001  /* AES-128对称密钥 */
#define YWKM_KEY_TYPE_AES_192       0x5002  /* AES-192对称密钥 */
#define YWKM_KEY_TYPE_AES_256       0x5003  /* AES-256对称密钥 */
#define YWKM_KEY_TYPE_SM4           0x5004  /* 国密SM4对称密钥 */

/* 保留段 (0x6000 - 0xFFFF) 用于未来扩展 */

/*===== 密钥读取格式 =====*/
#define YWKM_KEY_FORMAT_NULL        0x0000  /* 非标准格式 或 未指定 */
#define YWKM_KEY_FORMAT_RAW         0x0001  /* 原始二进制格式 */
#define YWKM_KEY_FORMAT_BASE64      0x0004  /* Base64编码格式 */
#define YWKM_KEY_FORMAT_STRING      0x0005  /* 可读字符串格式 */
#define YWKM_KEY_FORMAT_PEM         0x0002  /* PEM文件格式 */
#define YWKM_KEY_FORMAT_DER         0x0003  /* DER文件格式 */

/*===== 存储方案 =====*/
typedef enum {
    YWKM_STORAGE_FILE = 0,
    YWKM_STORAGE_TEE  = 1,
} ywkm_storage_type_t;

/*===== 统一的密钥元数据 =====*/
#pragma pack(push, 1) /** 按照1字节紧凑对齐 */
typedef struct {
    uint32_t key_type;              /* 密钥类型 */
    uint32_t key_format;            /* 密钥格式 */
    uint32_t purpose_flags;         /* 密钥用途标志位 */
    uint8_t reserved[52];           /* 保留字段，用于未来扩展 */
} ywkm_key_attr_t;

typedef struct {
    char key_id[YWKM_KEY_ID_MAX_LEN];        /* 密钥标识符 */
    uint32_t key_size;              /* 密钥数据长度（字节） */
    ywkm_key_attr_t key_attr;       /* 秘钥属性 */
    uint8_t reserved[28];           /* 保留字段，用于未来扩展 */
} ywkm_key_metadata_t;
#pragma pack(pop) /** 恢复原本对齐状态 */

/** 编译期检查 */
static_assert(
    sizeof(ywkm_key_attr_t) == 64,
    "sizeof(ywkm_key_attr_t) != 64"
);

static_assert(
    sizeof(ywkm_key_metadata_t) == YWKM_META_DATA_SIZE,
    "sizeof(ywkm_key_metadata_t) != YWKM_META_DATA_SIZE"
);

/*===== 日志级别 =====*/
typedef enum {
    YWKM_LOG_ERROR = 0,
    YWKM_LOG_WARN  = 1,
    YWKM_LOG_INFO  = 2,
    YWKM_LOG_DEBUG = 3
} ywkm_log_level_t;

/*===== 日志回调函数类型 =====*/
typedef void (*ywkm_log_callback_t)(const char* message);

void ywkm_set_log_callback(ywkm_log_callback_t callback);
void ywkm_set_log_level(ywkm_log_level_t level);

/**
 * @brief 存储密钥到密钥管理系统
 * 该函数用于将密钥数据及其属性存储到密钥管理系统中。函数会验证输入参数的合法性，
 * 并将密钥数据安全地存储到配置的存储后端。
 * @param key_id 密钥标识符，用于唯一标识该密钥，最大长度为YWKM_KEY_ID_MAX_LEN
 * @param key_data 密钥数据的指针，不能为NULL
 * @param key_size 密钥数据的大小，不能超过YWKM_KEY_DATA_MAX_LEN
 * @param attr 密钥属性指针，包含密钥类型、格式、用途等信息
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 存储成功
 * @retval YWKM_ERROR_INVALID_PARAM 参数无效
 * @retval YWKM_ERROR_MEMORY_ALLOC 内存分配失败
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端操作失败
 * @retval YWKM_ERROR_KEY_EXISTS 密钥已存在
 * @retval YWKM_ERROR_PERMISSION_DENIED 权限不足
 */
int ywkm_store_key(const char* key_id, const uint8_t* key_data, uint32_t key_size, ywkm_key_attr_t *attr);

/**
 * @brief 从密钥管理系统加载密钥
 * 该函数根据密钥标识符从密钥管理系统中加载密钥数据。调用者需要提供足够大的缓冲区
 * 来存储密钥数据，建议先调用ywkm_get_key_metadata获取密钥大小。
 * @param key_id 要加载的密钥标识符
 * @param key_data 输出参数，用于存储加载的密钥数据，不能为NULL
 * @param key_size 输入输出参数，输入时表示缓冲区大小，输出时返回实际密钥大小
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 加载成功
 * @retval YWKM_ERROR_INVALID_PARAM 参数无效
 * @retval YWKM_ERROR_KEY_NOT_FOUND 密钥不存在
 * @retval YWKM_ERROR_BUFFER_TOO_SMALL 提供的缓冲区太小
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端操作失败
 * @retval YWKM_ERROR_PERMISSION_DENIED 权限不足
 * @retval YWKM_ERROR_DECRYPT_FAILED 密钥解密失败
 */
int ywkm_load_key(const char* key_id, uint8_t* key_data, uint32_t* key_size);

/**
 * @brief 从密钥管理系统中删除指定的密钥
 * 该函数会从存储后端永久删除指定的密钥及其元数据。此操作不可逆，
 * 执行前应确保密钥不再需要。
 * @param key_id 要删除的密钥标识符
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 删除成功
 * @retval YWKM_ERROR_INVALID_PARAM 参数无效
 * @retval YWKM_ERROR_KEY_NOT_FOUND 密钥不存在
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端操作失败
 * @retval YWKM_ERROR_PERMISSION_DENIED 权限不足
 */
int ywkm_delete_key(const char* key_id);

/**
 * @brief 检查指定的密钥是否存在
 * 该函数检查密钥管理系统中是否存在指定的密钥标识符，不返回密钥数据本身。
 * @param key_id 要检查的密钥标识符
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 密钥存在
 * @retval YWKM_ERROR_KEY_NOT_FOUND 密钥不存在
 * @retval YWKM_ERROR_INVALID_PARAM 参数无效
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端操作失败
 */
int ywkm_key_exists(const char* key_id);

/**
 * @brief 获取指定密钥的元数据信息
 * 该函数返回指定密钥的元数据信息，包括密钥大小、类型、格式、用途等，
 * 但不返回实际的密钥数据。
 * @param key_id 要查询的密钥标识符
 * @param metadata 输出参数，用于存储获取的密钥元数据，不能为NULL
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 获取成功
 * @retval YWKM_ERROR_INVALID_PARAM 参数无效
 * @retval YWKM_ERROR_KEY_NOT_FOUND 密钥不存在
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端操作失败
 * @retval YWKM_ERROR_PERMISSION_DENIED 权限不足
 */
int ywkm_get_key_metadata(const char* key_id, ywkm_key_metadata_t* metadata);

/**
 * @brief 安全擦除内存中的数据
 * 该函数使用安全的方式擦除内存中的数据，防止敏感信息通过内存残留被恢复。
 * 通常用于清理包含密钥等敏感数据的内存区域。
 * @param data 要擦除的数据指针
 * @param size 要擦除的数据大小
 * @return void
 */
void ywkm_secure_erase(void* data, size_t size);

/**
 * @brief 获取错误码对应的描述字符串
 * 该函数将错误码转换为人类可读的描述字符串，便于调试和日志记录。
 * @param error_code 错误码，通常是API函数的返回值
 * @return const char* 错误描述字符串
 * @retval "Success" YWKM_SUCCESS
 * @retval "Unknown error" 其他未定义错误码
 */
const char* ywkm_get_error_string(int error_code);

/**
 * @brief 清理密钥管理系统资源
 * 该函数用于清理密钥管理系统占用的资源，包括关闭存储后端连接、
 * 释放内部缓冲区等。在程序退出前调用此函数可以确保资源正确释放。
 * @return int 执行结果状态码
 * @retval YWKM_SUCCESS 清理成功
 * @retval YWKM_ERROR_STORAGE_FAILED 存储后端清理失败
 */
int ywkm_cleanup(void);

/**
 * @brief ywkm_load_key 兼容接口
 * 该函数用于将密钥数据及其属性存储到密钥管理系统中。函数会验证输入参数的合法性，
 * 并将密钥数据安全地存储到配置的存储后端。
 * @param keyName 密钥标识符，用于唯一标识该密钥，最大长度为YWKM_KEY_ID_MAX_LEN
 * @param szKey 密钥数据的指针，不能为NULL
 * @param keySize szKey 缓冲区大小
 * @return int 执行结果状态码，正数为输出长度，负数为错误码 同 ywkm_load_key
 */
int ywGetMainKey(unsigned char *keyName, unsigned char *szKey, int keySize);

#ifdef __cplusplus
}
#endif

#endif /* KEY_MANAGER_H */