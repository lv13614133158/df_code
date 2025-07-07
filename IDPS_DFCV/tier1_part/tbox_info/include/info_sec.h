#ifndef INFO_SEC_H
#define INFO_SEC_H

#define DCHAR unsigned char
#define D32S int

typedef struct
{
    DCHAR vin[18];                              //!< 车端vin 是17位,最后位填0，作为结束符。
    DCHAR serial_number[32];         //!< 序列号。32位
    DCHAR supplier_code[32];         //!< 供应商代码。32位
    DCHAR hardware_version[32];  //!< 硬件版本号。32位
    DCHAR soft_version[32];            //!< 软件版本。32位
} IDS_TBOX_INFO_T;

// 初始化
int sec_api_init();

/**
 * @brief  ids获取T-BOX参数。
 *
 * @param param [OUT]  IDS_TBOX_INFO_T*  T-BOX参数信息
 * @return D32S     0:Successed, None-0:Failed
 * @note
 */
D32S ids_getTboxParam(IDS_TBOX_INFO_T* param );

/*
* 函数功能：获取位置信息
* 输入：NA
* 输出：longi: 经度信息；lati：纬度信息
* 返回值： 0，失败；1，成功
*/
int ids_GetGnssPointInfo(unsigned int *longi, unsigned int *lati);

#endif
