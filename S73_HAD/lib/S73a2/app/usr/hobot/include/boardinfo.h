#ifndef __BOARDINFO_H__
#define __BOARDINFO_H__
#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/* Return Value */
enum hb_binfo_retval {
	HB_BINFO_SUCCESS,
	HB_BINFO_INVALID_PARAM,
	HB_BINFO_SHORT_BUF,
	HB_BINFO_PLAT_NOT_SUPPORT,
};

/*
	key			dst
	soc_gen			J6
	soc_name		J6E
				J6P
				J6M
	chip_id			real chip_id
	hw_name			CVB
				PAC
				Matrix
				EVM
				SLT
	pcie_mode		default
				ep
				rc
	bootdevice_name		mmc0
	soc_uid			real uid
	ddr_type		LPDDR4
				LPDDR4X
				LPDDR5
	ddr_size		real ddr size(MB)
	adc_boardid             hardware adc boardid
	hw_version              board version
*/
/**
 * @brief get board infos

 * @param[in] key: info to get
 * @param[out] dst: buffer to store info
 * @param[in] len: length of dst
 * @return errcode
 *  HB_BINFO_SUCCESS: success
 *  -HB_BINFO_INVALID_PARAM: param error
 *  -HB_BINFO_SHORT_BUF: len is too short
 *  -HB_BINFO_PLAT_NOT_SUPPORT: key is not support in this platform
 */

int32_t hb_get_boardinfo(char* key, void *dst, uint32_t len);

#ifdef __cplusplus
}
#endif
#endif