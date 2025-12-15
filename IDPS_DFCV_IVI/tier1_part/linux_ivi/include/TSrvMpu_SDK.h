/**
 * @file TSrvMpu_SDK.h
 * @brief MPU服务SDK接口头文件 - 提供给第三方SDK使用
 * @version 1.0
 * @date 2025-11-27
 */

#ifndef __MPU_SDK_H__
#define __MPU_SDK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 基本数据类型定义 */
#ifndef u8
typedef unsigned char u8;
#endif

#ifndef u32
typedef unsigned int u32;
#endif

#ifndef BOOL
typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#endif

/* DLL导出宏定义 */
#ifndef YW_DLL_EXPORT
#ifdef _WIN32
#define YW_DLL_EXPORT __declspec(dllexport)
#else
#define YW_DLL_EXPORT __attribute__((visibility("default")))
#endif
#endif

/**
 * @brief 获取设备ID
 * @param pp_Buf [out] 输出缓冲区，用于存储设备ID字符串（以'\0'结尾）
 * @param pp_BufLen [in/out] 输入时表示缓冲区大小，输出时表示实际获取的设备ID长度（包含'\0'）
 * @return BOOL 成功返回TRUE，失败返回FALSE
 * @note
 *   - 调用前需要分配足够大小的缓冲区（建议至少32字节）
 *   - pp_Buf和pp_BufLen不能为NULL
 *   - 设备ID为字符串格式，以'\0'结尾
 */
YW_DLL_EXPORT BOOL Mpu_GetDeviceId(u8 *pp_Buf, u32 *pp_BufLen);

/**
 * @brief 获取车辆识别码（VIN码）
 * @param pp_Buf [out] 输出缓冲区，用于存储车辆识别码字符串（以'\0'结尾）
 * @param pp_BufLen [in/out] 输入时表示缓冲区大小，输出时表示实际获取的识别码长度（不包含'\0'）
 * @return BOOL 成功返回TRUE，失败返回FALSE
 * @note
 *   - 调用前需要分配足够大小的缓冲区（建议至少32字节）
 *   - pp_Buf和pp_BufLen不能为NULL
 *   - 车辆识别码为字符串格式，以'\0'结尾
 */
YW_DLL_EXPORT BOOL Mpu_GetVehicleVin(u8* pp_Buf, u32* pp_BufLen);

/**
 * @brief 获取硬件版本
 * @return u32 硬件版本号
 * @note
 *   - 返回值为设备硬件版本标识
 *   - 不同硬件版本对应不同的版本号
 */
YW_DLL_EXPORT u32 Mpu_GetHWVer(void);

/**
 * @brief 获取软件版本信息
 * @param pp_Ver [out] 输出参数，用于存储软件版本号
 * @param pp_Date [out] 输出参数，用于存储软件日期（格式：Year<<16 | Month<<8 | Day）
 * @return BOOL 成功返回TRUE，失败返回FALSE
 * @note
 *   - pp_Ver和pp_Date不能为NULL
 *   - pp_Date格式说明：
 *     * 高16位：年份（相对于2000年的偏移，例如2025年表示为25）
 *     * 中8位：月份（1-12）
 *     * 低8位：日期（1-31）
 *   - 示例：2025年1月15日 = (25 << 16) | (1 << 8) | 15 = 0x0019010F
 */
YW_DLL_EXPORT BOOL Mpu_GetVersionInfo(u32 *pp_Ver, u32 *pp_Date);

#ifdef __cplusplus
}
#endif

#endif // __MPU_SDK_H__

