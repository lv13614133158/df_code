/***************************************************************************
* COPYRIGHT NOTICE
* Copyright 2024 Horizon Robotics, Inc.
* All rights reserved.
***************************************************************************/
#ifndef HB_VPS_EX_INTERFACE_H_
#define HB_VPS_EX_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hbn_vpf_interface.h"
#include "hbn_sth_cfg.h"

#define HB_PYM_MAX_DS_NUM 				(6)
#define HB_STH_MAX_SRC_CH 				(4)
#define HB_STH_MAX_ROI					(12)

typedef struct {
	uint32_t startTop; //ROI coordinate Y
	uint32_t startLeft; //ROI coordinate X
	uint32_t regionWidth; //ROI width
	uint32_t regionHeight; //ROI height
	uint32_t wstrideUv;
	uint32_t wstrideY;
	uint32_t vstride;
	uint32_t stepV;
	uint32_t stepH;
	uint32_t outWidth;
	uint32_t outHeight;
	uint32_t phaseYV;
	uint32_t phaseYH;
} PymRoiBox;

typedef struct {
	uint32_t srcInWidth;
	uint32_t srcInHeight;
	uint32_t srcInStrideY;
	uint32_t srcInStrideUv;
	uint8_t blMaxLayerEn;
	uint8_t dsRoiEn;
	uint8_t dsRoiUvBypass;
	uint8_t dsRoiSel[HB_PYM_MAX_DS_NUM];
	uint8_t dsRoiLayer[HB_PYM_MAX_DS_NUM];
	PymRoiBox dsRoiInfo[HB_PYM_MAX_DS_NUM];
} pymChnCtrl;

typedef struct {
	pymChnCtrl chnCtrl;
} pymAttr;

typedef struct {
	uint32_t srcInWidth;
	uint32_t srcInHeight;
	uint32_t srcInStrideY;
} pymRosAttr;

typedef struct {
	struct stitch_base_attr base_attr;
	struct stitch_ch_attr inch_attr[HB_STH_MAX_SRC_CH];
	struct stitch_ch_attr och_attr;
} sthAttr;

hbn_vnode_handle_t pymInit(uint32_t hwId);
int32_t pymDeinit(hbn_vnode_handle_t handle);
int32_t pymProcessImage(hbn_vnode_handle_t handle,
		void *inputBufferY, void *inputBufferUv, pymAttr *pymAttr,
		void *outputBufferY[HB_PYM_MAX_DS_NUM], void *outputBufferUv[HB_PYM_MAX_DS_NUM]);

hbn_vnode_handle_t gdcInit(uint32_t hwId);
int32_t gdcDeinit(hbn_vnode_handle_t handle);
int32_t gdcProcessImage(hbn_vnode_handle_t handle, void *inputBufferY, void *inputBufferUv,
		void *outputBufferY, void *outputBufferUv, gdc_config_t *user_gdc_cfg);

hbn_vnode_handle_t sthInit(uint32_t hwId);
int32_t sthDeinit(hbn_vnode_handle_t handle);
int32_t sthProcessImage(hbn_vnode_handle_t handle, void *inputBufferY[HB_STH_MAX_SRC_CH],
		void *inputBufferUv[HB_STH_MAX_SRC_CH], sthAttr *sth_Attr,
		void *outputBufferY, void *outputBufferUv);

#ifdef __cplusplus
}
#endif

#endif // HB_VPS_EX_INTERFACE_H_
