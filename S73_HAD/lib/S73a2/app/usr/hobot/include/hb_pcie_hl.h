/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2023 - 2023 Horizon Robotics, Inc.
 *                   All rights reserved.
 ***/

/**
 * @file hb_pcie_hl.h
 *
 * @NO{S13E01C16}
 * @ASIL{D}
 */
#ifndef _INCLUDE_HB_PCIE_HL_H_
#define _INCLUDE_HB_PCIE_HL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define HB_PCIE_HL_CONFIG_FILE	"HB_PCIE_HL_CONFIG_FILE"


typedef void* pcieHandler;
typedef void (*recvDataCallBack)(pcieHandler ph, uint32_t size, void *privateData);

typedef enum {
	ERR_NONE = 0,
	ERR_PARAMETER_INVALID,			/* invalid paramter */
	ERR_HANDLER_INVALID,			/* invalid handler */
	ERR_CONFIG_FILE_NOT_EXIST,		/* config file not exist */
	ERR_CONFIG_FILE_INVALID,		/* config file content has error */
	ERR_CHIP_ID_INVALID,			/* invalid Chip ID */
	ERR_CHIP_NOT_FOUND,				/* Chip not found in config */
	ERR_CHIP_NOT_READY,				/* Chip not ready in PCI bus */
	ERR_OUT_OF_MEM,					/* No free memory */
	ERR_BAR_REQUEST_FAIL,			/* request BAR resource fail */
	ERR_DMA_REQUEST_FAIL,			/* request DMA resource fail */
	ERR_TOPIC_NOT_AVAILABLE,		/* topic in using */
	ERR_TOPIC_ID_INVALID,			/* invalid topic ID */
	ERR_RECV_HANDLER_INSTALL_FAIL,	/* register receive callback function fail */
	ERR_INNERBUF_NOT_READY,			/* inner buffer not ready */
	ERR_IOMMU_MAP_FAIL,				/* IOMMU MAP fail */
	ERR_MMAP_FAIL,					/* MMAP fail */
	ERR_OPERATION_INVALID,			/* invalid operation */
	ERR_FEATURE_NOT_SUPPORT,		/* feature not support */
	ERR_SUBSCRIBE_NOT_EXIST,		/* subscriber not exist */
	ERR_RECV_BUF_NOT_READY,			/* receive buffer not alloced or registered */
	ERR_RECV_BUF_IN_BUSY,			/* receive buffer in using */
	ERR_MUTEX_INIT_FAIL,			/* mutex init fail */
	ERR_MUTEX_LOCK_FAIL,			/* mutex lock fail */
	ERR_MUTEX_UNLOCK_FAIL,			/* mutex unlock fail */
	ERR_DMA_XFER_FAIL,				/* DMA transfer fail */
	ERR_INTERRUPT_TRIGGER_FAIL,		/* trigger interrupt fail */
	ERR_USER_BUFFER_REGISTERED,		/* User buffer already resistered */
	ERR_INNER_BUFFER_ALLOCED,		/* Inner buffer already alloced */
	ERR_BUFFER_NOT_AVAILABLE,		/* Inner or User buffer not ready */
	ERR_SEND_SIZE_INVALID,			/* invalid send size */
	ERR_PTHREAD_OPERATION_FAIL,		/* pthread operation fail */
	ERR_IOMMU_UNMAP_FAIL,			/* IOMMU UNMAP fail */
	ERR_INNERBUF_CACHE_FAIL,		/* inner buffer cache clean or invalid fail */
} pcieErrCode;


/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief inititial the topic resource
 *
 * @param[out] ph: pcie handler
 * @param[in] chipID: the chip which publish to or subscribe from
 * @param[in] topicID: topic ID
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 *
 * @Note
 *  the priority of config file choosen:
 *    1. environment variable: HB_PCIE_HL_CONFIG_FILE
 *    2. auto detect from system information
 */
pcieErrCode pcieInit(pcieHandler *ph, uint8_t chipID, uint8_t topicID);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief free the requested resource
 *
 * @param[in] ph: pcie handler
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 */
pcieErrCode pcieDeInit(pcieHandler ph);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Get the max size of support topic
 *
 * @param[in] ph: pcie handler
 * @param[out] maxTopic: supported topic size
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 *
 * @Note
 *  topic start from 0
 */
pcieErrCode pcieGetMaxTopicSize(pcieHandler ph, uint8_t *topicSize);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Set in Publish mode
 *
 * @param[in] ph: pcie handler
 * @param[in] weight: the priority of DMA transmission, range: 1-31
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 *
 * @Note
 *  DMA controller uses a weighted round robin (WRR) arbitration scheme to select the
 *  next channel to be serviced, the bandwidth for all transmission is shared in time and 
 *  is controlled by a weighted round-robin arbiter.
 */
pcieErrCode pciePublish(pcieHandler ph, uint8_t weight);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Set in Subscribe mode
 *
 * @param[in] ph: pcie handler
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 */
pcieErrCode pcieSubscribe(pcieHandler ph);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Get the max size of inner buffer
 *
 * @param[in] ph: pcie handler
 * @param[out] size: max buffer size
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 */
pcieErrCode pcieGetMaxInnerBufSize(pcieHandler ph, uint32_t *size);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Alloc inner buffer for send buffer in publish mode or receive buffer in subscriber mode
 *
 * @param[in] ph: pcie handler
 * @param[in] size: buffer size
 * @param[out] virtualAddr: alloced buffer virtual address
 * @param[out] physAddr: alloced buffer physics address
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 */
pcieErrCode pcieAllocInnerBuf(pcieHandler ph, uint32_t size, void **virtualAddr, uint64_t *physAddr);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief Use the buffer from User for sending or receiving
 *
 * @param[in] ph: pcie handler
 * @param[in] physAddr: buffer physics address
 * @param[in] size: buffer size
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 */
pcieErrCode pcieRegisterUserBuf(pcieHandler ph, uint64_t physAddr, uint32_t size);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief start receiving data from publisher
 *
 * @param[in] ph: pcie handler
 * @param[in] fun: recevied data callback function
 * @param[in] funData: callback function private data
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 *
 * @Note
 *  During callback function running, the receive buffer stay in busy status,
 *  and the busy become in idle status once the callback function exit.
 */
pcieErrCode pcieStartRecv(pcieHandler ph, recvDataCallBack fun, void *funData);

/**
 * @NO{S13E01C16I}
 * @ASIL{B}
 * @brief send data to subscriber
 *
 * @param[in] ph: pcie handler
 * @param[in] size: send data size
 *
 * @retval =0: success
 * @retval >0: failure
 *
 * @compatibility HW: J5/J6
 * @compatibility SW: 0.1.0
 *
 * @Note
 *  Pushlisher can not send data while receive buffer in busy status.
 */
pcieErrCode pcieSendData(pcieHandler ph, uint32_t size);


#ifdef __cplusplus
}
#endif
#endif // _INCLUDE_HB_PCIE_HL_H_
