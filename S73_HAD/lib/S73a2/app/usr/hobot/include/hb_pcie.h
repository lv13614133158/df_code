/*************************************************************************************
 *                                COPYRIGHT NOTICE
 *                 Copyright (C) 2022 -2024 Horizon Robotics, Inc.
 *                                All rights reserved.
 ************************************************************************************/

/**
 * @file hb_pcie.h
 *
 * @NO{S13E01C15I}
 * @ASIL{B}
 */

#ifndef INCLUDE_HB_PCIE_H_
#define INCLUDE_HB_PCIE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>


/* keep sync with dma_dbg_ts_max in hobot-pcie-uapi.h */
#define DMA_DEBUG_TS_SIZE	7

/* request BAR flag define, keep sync with HOBOT_PCIE_UBAR_FLAG_* */
#define HB_PCIE_BAR_FLAG_SHARED				(0x1u << 0) /**< requested BAR share with multi-process */
#define HB_PCIE_BAR_FLAG_CLEAR				(0x1u << 1) /**< clean the BAR data on first request */


#define HB_PCIE_MEM_FLAG_NONE				(0x0u)  /**< default */
#define HB_PCIE_MEM_FLAG_CACHEABLE			(0x1u << 1) /**< cacheable memory */

#define HB_PCIE_ERR_NONE						0      /**< no error */
#define HB_PCIE_ERR_INTERRUPTTED				-1      /**< operation was interruptted */
#define HB_PCIE_ERR_INVALID_CHAN_ID				-2      /**< invalid channel id */
#define HB_PCIE_ERR_NO_FREE_HANDLE				-3      /**< no more free handle */
#define HB_PCIE_ERR_OUT_OF_MEM					-4      /**< out of memory */
#define HB_PCIE_ERR_OPEN_DEV					-5      /**< open PCIe device fail */
#define HB_PCIE_ERR_VERSION_MISMATCH			-6      /**< library and driver version mismatch */
#define HB_PCIE_ERR_CHAN_ALREADY_ALLOC			-7      /**< channel already in use */
#define HB_PCIE_ERR_MAP_BAR						-8      /**< map BAR fail */
#define HB_PCIE_ERR_INVALID_HANDLE				-9      /**< invalid handle */
#define HB_PCIE_ERR_INVALID_ELEMENTS			-10     /**< invalid DMA elements */
#define HB_PCIE_ERR_INVALID_WEIGHT				-11     /**< invalid DMA weight */
#define HB_PCIE_ERR_STL_NOT_READY				-12     /**< STL(FUSA) not ready */
#define HB_PCIE_ERR_LINK_DOWN					-13     /**< PCIe link down */
#define HB_PCIE_ERR_DMA_XFER_TIMEOUT			-14     /**< DMA transfer timeout */
#define HB_PCIE_ERR_DMA_XFER_ABORTED			-15     /**< DMA transfer aborted */
#define HB_PCIE_ERR_DMA_HANDSHAKE				-16     /**< DMA handshake timeout */
#define HB_PCIE_ERR_RECEIVER_EXIST				-17     /**< receiver already installed */
#define HB_PCIE_ERR_RECEIVER_NOT_EXIST			-18     /**< receiver not installed yet */
#define HB_PCIE_ERR_THREAD_CREATE				-19     /**< start receiver thread fail */
#define HB_PCIE_ERR_THREAD_STOP					-20     /**< stop receiver thread fail */
#define HB_PCIE_ERR_INVALID_BAR_OFFSET			-21     /**< invalid BAR offset for read/write */
#define HB_PCIE_ERR_UNSUPPORT_OPERATION			-22     /**< un-support opeartion */
#define HB_PCIE_ERR_RAISE_IRQ					-23     /**< raise user IRQ fail */
#define HB_PCIE_ERR_INVALID_INT_ID				-24     /**< invalid interrupt ID */
#define HB_PCIE_ERR_HANDLER_EXIST				-25     /**< interrupt handler already installed */
#define HB_PCIE_ERR_HANDLER_NOT_OWN				-26     /**< interrupt handler not owned by requester */
#define HB_PCIE_ERR_HANDLER_NOT_EXIST			-27     /**< interrupt handler not installed yet */
#define HB_PCIE_ERR_INVALID_PARAM				-28     /**< invalid param */
#define HB_PCIE_ERR_NETLINK_CREATE				-29     /**< create netlink socket fail */
#define HB_PCIE_ERR_NETLINK_BIND				-30     /**< bind netlink socket fail */
#define HB_PCIE_ERR_NETLINK_SETOPT				-31     /**< config netlink socket fail */
#define HB_PCIE_ERR_NO_PCI_MEM					-32     /**< no free PCI space available */
#define HB_PCIE_ERR_MAP_PCI_NO_OUTBOUND			-33     /**< no free outbound windows available */
#define HB_PCIE_ERR_UNMAP_PCI_NOT_MAPPED		-34     /**< address of PCI memory not mapped yet */
#define HB_PCIE_ERR_UNMAP_PCI_NOT_OWN			-35     /**< the mapped memory is not owned by requester */
#define HB_PCIE_ERR_DMA_REQUESTED				-36     /**< DMA channel already requested */
#define HB_PCIE_ERR_DMA_NOT_REQUESTED			-37     /**< DMA channel not requested */
#define HB_PCIE_ERR_MAP_SIZE_INVALID			-41     /**< invalid map size */
#define HB_PCIE_ERR_MAP_ADDR_INVALID			-42     /**< invalid map addr */
#define HB_PCIE_ERR_NOT_INIT_BY_RC				-44     /**< device not init by RC */
#define HB_PCIE_ERR_IN_SUSPEND					-45     /**< remote device in suspend status */
#define HB_PCIE_ERR_UNKNOWN						-46     /**< unkown error */
#define HB_PCIE_ERR_INVALID_IOCTL_CMD			-47     /**< invalid ioctl command */
#define HB_PCIE_ERR_MEM_COPY					-48     /**< copy from/to kernel fail */
#define HB_PCIE_ERR_REMOTE_RECV_NOT_EXIST		-49     /**< remote receiver not installed */
#define HB_PCIE_ERR_RECEIVER_NOT_OWN			-50     /**< receiver is not owned by requester */
#define HB_PCIE_ERR_PTHREAD_MUTEX				-51     /**< pthread mutex lock fail */
#define HB_PCIE_ERR_DMA_RECEIVE_FIFO_FULL		-52     /**< DMA receive fifo full */
#define HB_PCIE_ERR_UIQR_HANDSHARE				-53     /**< user interrupt handshake timeout */
#define HB_PCIE_ERR_UIQR_RECEIVE_FIFO_FULL		-54     /**< user interrupt receive fifo full */
#define HB_PCIE_ERR_UNMAP_BAR					-60     /**< unmap BAR fail */
#define HB_PCIE_ERR_REQUEST_BAR					-61     /**< request BAR fail */
#define HB_PCIE_ERR_MMAP						-62     /**< mmap fail */
#define HB_PCIE_ERR_MUNMAP						-63     /**< munmap fail */
#define HB_PCIE_ERR_BAR_NOT_REQUESTED			-64     /**< BAR not requested yet */
#define HB_PCIE_ERR_MAP_PCI_OB_SETUP			-65     /**< setup outbound fail */
#define HB_PCIE_ERR_SEND_EVENT					-66     /**< send ubar request or release event fail */
#define HB_PCIE_ERR_UBAR_REGION_NO_IDX			-67     /**< request ubar fail because of no region idx */
#define HB_PCIE_ERR_UBAR_REQUEST_TIMEOUT		-68     /**< request ubar timeout */
#define HB_PCIE_ERR_UBAR_REGION_NO_MEM			-69     /**< request ubar fail because of no mem */
#define HB_PCIE_ERR_UBAR_REGION_MISMATCH		-70     /**< release ubar fail because of region info mismatch */
#define HB_PCIE_ERR_UBAR_REGION_NOT_REQUESTED	-71     /**< release ubar fail because of ubar not requested */
#define HB_PCIE_ERR_PEER_EP_NOT_EXIST			-72     /**< p2p connetc fail because of peer er not exist */
#define HB_PCIE_ERR_PEER_EP_NOT_INITED			-73     /**< peer EP not inited yet */
#define HB_PCIE_ERR_EP_LPI_NOT_EXIST			-74     /**< ep lpi not exist */
#define HB_PCIE_ERR_UNSHARED_UBAR_REQUESTED		-75     /**< unshared user bar already requested */
#define HB_PCIE_ERR_IOMMU_MAP_FAI				-76     /**< iommu map fail */
#define HB_PCIE_ERR_INVALID_FUNCTION_ID			-77     /**< invalid function id */
#define HB_PCIE_ERR_DMA_NOTIFY_IRQ				-78     /**< the notify IRQ for DMA xfer fail */
#define HB_PCIE_ERR_DMA_CONFIG_REG				-79     /**< config DMA reg in EP fail */
#define HB_PCIE_ERR_INVALID_IOVA				-80     /**< invalid iova */

/**
 * @struct element
 * @brief the element of dma transfer.
 * @NO{S13E01C15}
 * notice: keep sync with struct dma_element in hobot-pcie-upai.h
 */
//coverity[misra_c_2012_rule_5_7_violation:SUPPRESS] ## violation reason SYSSW_V_5.7_01
struct element {
	uint64_t size; /**< transfer size, available range: 2 ~ 0xFFFFFFFF */
	uint64_t dest; /**< destitation physics address */
	uint64_t src;  /**< source physics address */
};


/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Request and initialize device resource and return the handle id
 *
 * @param[in] cd_id: controller id of device on ep side or domain id of device on rc side
 *                   range: [0, 1]; default: 0
 * @param[in] bus_id: The bus id of device
 *                   range: [0, 255]; default: NA
 *
 * @retval >=0: success
 * @retval <0: fail
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_init(uint32_t cd_id, uint32_t bus_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief pcie deint, Release the resource requested by the funciton "hb_pcie_init"
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 * 			             range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_deinit(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get domain/bus id, only availabe on EP side
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[out] domain: The domain id of device
 *            range: [0, 1]; default: 0
 * @param[out] bus: The bus id of device
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_get_bus_info(int32_t handle_id, uint32_t *domain, uint32_t *bus);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get the version of the libhbpcie
 *
 * @param[out] major: major id
 * @param[out] minor: minor id
 * @param[out] patch: patch id
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_get_version(uint32_t *major, uint32_t *minor, uint32_t *patch);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get err info based on err number
 *
 * @param[in] err_num: err number
 * @param[in] errbuf_size: max size of err buf
 * @param[out] err_buf: err info
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_strerror(int32_t err_num, char *err_buf, int32_t errbuf_size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get error string
 *
 * @param[in] err_num: err number
 *
 * @retval error string
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
const char *hb_pcie_errstr(int32_t err_num);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief request dma channel
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 *                       range: [0, 31]; default: 0
 * @param[in] channel_id: dma channel id
 *                        range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_request_dma(int32_t handle_id, int32_t channel_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief release dma with the specified handle id
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 *                       range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_release_dma(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Write data to remote memory via DMA
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 * 						 range: [0, 31]; default: 0
 * @param[in] eles: the elements for DMA transfer
 * @param[in] ele_nr: the number of the elements
 *                    range: [1, 8]; default: 1
 * @param[in] weight: the weight of the dma
 * 		              range: [1, 31]; default: 1
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_dma_write(int32_t handle_id, const struct element *eles,
							int32_t ele_nr, int32_t weight);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Write data to remote memory via DMA if remote receiver installed
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 * 						 range: [0, 31]; default: 0
 * @param[in] eles: the elements for DMA transfer
 * @param[in] ele_nr: the number of the elements
 *                    range: [1, 8]; default: 1
 * @param[in] weight: the weight of the dma
 * 		              range: [1, 31]; default: 1
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_dma_write_strict(int32_t handle_id, const struct element *eles,
									int32_t ele_nr, int32_t weight);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Read data from remote memory via DMA
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *                       range: [0, 31]; default: 0
 * @param[in] eles: the elements for DMA transfer
 * @param[in] ele_nr: the number of the elements
 *                    range: [1, 8]; default: 1
 * @param[in] weight: the weight of the dma
 * 		              range: [1, 31]; default: 1
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_dma_read(int32_t handle_id, const struct element *eles,
							int32_t ele_nr, int32_t weight);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Install DMA data receive callback function
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] receiver: the callback function
 * @param[in] data: user pointer can be used in callback function
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_install_receiver(int32_t handle_id,
		void (*receiver)(int32_t channel_id, const struct element *eles, int32_t ele_nr, void *data), void *data);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Un-install DMA data receive callback function
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_uninstall_receiver(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief check whether the channel's remote recevier installed
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 * 						 range: [0, 31]; default: 0
 * @param[in] channel_id: channel id
 * 					      range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_remote_recevier_installed(int32_t handle_id, int32_t channel_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief specify the transmission id for DMA time statistics(debug purpose)
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] id: transmission id
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_dbg_dma_write_set_id(int32_t handle_id, uint64_t id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief get DMA time statistics(debug purpose)
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] id: transmission id
 * @param[in] times: times information
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_dbg_dma_write_get_times(int32_t handle_id, uint64_t *id, struct timespec **times);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Request BAR region before read/write
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] name: the name of request bar region
 * @param[in] size: the size of request bar region
 * @param[in] flag: user bar attribute flag;
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_bar_request(int32_t handle_id, const char *name, uint64_t size, uint32_t flag);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Release BAR region.
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *                       range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_bar_release(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief get ubar addr info
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[out] iova: iommu address
 * @param[out] pa: physics address
 * @param[out] va: Virtual address
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_get_bar_addr(int32_t handle_id, uint64_t *iova, uint64_t *pa, void **va);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief get ubar addr info about peer ep
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[out] iova: iommu address
 * @param[out] pa: physics address
 * @param[out] va: Virtual address
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_get_bar_addr(int32_t handle_id, uint64_t *iova, uint64_t *pa, void **va);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Read data from BAR
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] offset: the offset of bar operation
 * @param[in] size: size of bar operation
 * @param[out] buf: store the read data
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_bar_read(int32_t handle_id, uint64_t offset, void *buf, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief write data to BAR
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] offset: the offset of bar operation
 * @param[in] buf: data to be write
 * @param[in] size: size of bar operation
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_bar_write(int32_t handle_id, uint64_t offset, const void *buf, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Map pci addr to EP local address, only availabe on EP side
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] size: map size
 * @param[in] pci_phys: pci phys addr
 * @param[out] local_pa: the mmaped EP local physics address
 * @param[out] local_va: the mmaped EP local Virtual address
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_map_pci(int32_t handle_id, uint64_t pci_phys, uint64_t *local_pa, void **local_va, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Unmap RC memory in EP local address, only availabe on EP side
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] local_va: the mmaped EP local Virtual address
 * @param[in] local_pa: the mmaped EP local physics address
 * @param[in] size: unmap size
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_unmap_pci(int32_t handle_id, uint64_t local_pa, void *local_va, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get the total size of interrupts
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval >=0: total size of interrupts
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_get_max_interrupt_num(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Send interrupt to peer device
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] id: interrupt ID, start from 0, the max value can be get from hb_pcie_get_max_interrupt_num
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_trigger_interrupt(int32_t handle_id, int32_t id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Install the interrupt handler.
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] id: interrupt ID, start from 0, the max value can be get from hb_pcie_get_max_interrupt_num
 *            range: [0, 31]; default: 0
 * @param[in] handler: callback function once get interrupt
 * @param[in] data: user pointer can be used in callback function
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_install_interrupt_handler(int32_t handle_id, int32_t id,
									void (*handler)(int32_t id, void *data), void *data);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Un-install the interrupt handler
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_uninstall_interrupt_handler(int32_t handle_id);

/**
 * @NO{S13E01C15U}
 * @ASIL{B}
 * @brief device init function in p2p mode, get resource of peer ep
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] domain_id: domain id of peer ep
 * @param[in] bus_id: bus id of peer ep
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 * 
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_pcie_p2p_connect(int32_t handle_id, uint32_t domain_id, uint32_t bus_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief pcie deint in p2p mode, Release the resource
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 * 			             range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_disconnect(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{D}
 * @brief Request BAR of peer EP in P2P mode
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] name: the name of request bar region
 * @param[in] size: the size of request bar region
 * @param[in] flag: user bar attribute flag
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_bar_request(int32_t handle_id, const char *name, uint64_t size, uint32_t flag);

/**
 * @NO{S13E01C15I}
 * @ASIL{D}
 * @brief release bar region in P2P mode
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_bar_release(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief EP Read data from BAR of peer EP device
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 * 			             range: [0, 31]; default: 0
 *
 * @param[in] offset: the offset of bar operation
 * @param[in] size: size of bar operation
 * @param[out] buf: store the read data
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_bar_read(int32_t handle_id, uint64_t offset, void *buf, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief EP write data to BAR of peer EP device
 *
 * @param[in] handle: handle id, handle return from hb_pcie_init
 *						range: [0, 31]; default: 0
 * @param[in] offset: the offset of bar operation
 * @param[in] buf: data to be write
 * @param[in] size: size of bar operation
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_bar_write(int32_t handle_id, uint64_t offset, const void *buf, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief EP read data to BAR of peer EP device by dma mode
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 *						range: [0, 31]; default: 0
 * @param[in] offset: the offset of bar operation
 * @param[in] local_iova: local iova address
 * @param[in] size: size of bar operation
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_dma_bar_read(int32_t handle_id, uint64_t local_iova, uint64_t offset, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief EP write data to BAR of peer EP device by dma mode
 *
 * @param[in] handle_id: handle id, handle return from hb_pcie_init
 *						range: [0, 31]; default: 0
 * @param[in] offset: the offset of bar operation
 * @param[in] local_iova: local iova address
 * @param[in] size: size of bar operation
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_dma_bar_write(int32_t handle_id, uint64_t local_iova, uint64_t offset, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Get the total size of interrupts in p2p mode
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval >=0: total size of interrupts
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_get_max_interrupt_num(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Send interrupt to peer EP in p2p mode
 *
 * @param[in] handle_id: handle return from hb_p2p_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] id: interrupt ID, start from 0, the max value can be get from hb_pcie_p2p_get_max_interrupt_num
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_trigger_interrupt(int32_t handle_id, int32_t id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Install the interrupt handler about peer EP device in p2p mode
 *
 * @param[in] handle_id: handle return from hb_pcie_p2p_init
 *            range: [0, 31]; default: 0
 * @param[in] id: interrupt ID, start from 0, the max value can be get from hb_pcie_p2p_get_max_interrupt_num
 *            range: [0, 31]; default: 0
 * @param[in] handler: callback function once get interrupt
 * @param[in] data: user pointer can be used in callback function
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_install_interrupt_handler(int32_t handle_id, int32_t id,
							void (*handler)(int32_t id, void *data), void *data);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief uninstall the interrupt handler in p2p mode
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_p2p_uninstall_interrupt_handler(int32_t handle_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Alloc memory and get phy/iova/va addr
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] flag: alloc flag
 * @param[in] size: alloc size
 * @param[out] pa: the physics address of alloced mem
 * @param[out] iova: the iova of alloced mem
 * @param[out] va: the virtual address of alloced mem
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_mem_alloc(int32_t handle_id, uint64_t size, uint64_t flag,
                               uint64_t *pa, uint64_t *iova, void **va);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief free mem alloc by hb_pcie_mem_alloc
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] size: size of the memory
 * @param[in] iova: the iova of alloced mem
 * @param[in] va: the virtual address of alloced mem
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_mem_free(int32_t handle_id, uint64_t size, uint64_t iova, void *va);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief invalid memory cache
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] iova: iova address of the memory
 * @param[in] size: size of the memory
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_pcie_mem_cache_invaid(int32_t handle_id, uint64_t iova, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief clean memory cache
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] iova: iova address of the memory
 * @param[in] size: size of the memory
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_pcie_mem_cache_clean(int32_t handle_id, uint64_t iova, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief Map local phy to iova by iommu
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] pa: the mmaped EP local physics address
 * @param[in] size: map size
 * @param[out] iova: mapped by the iommu
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_iommu_map(int32_t handle_id, uint64_t pa, uint64_t *iova, uint64_t size);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief UnMap local memory which map by iommu
 *
 * @param[in] handle_id: handle return from hb_pcie_init
 *            range: [0, 31]; default: 0
 * @param[in] iova: mapped by the iommu
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_iommu_unmap(int32_t handle_id, uint64_t iova);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief enable PCIe ptm func.
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_ptm_enable(int32_t ctrl_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief disable PCIe ptm func.
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_ptm_disable(int32_t ctrl_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief turn on pps
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_pps_enable(int32_t ctrl_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief turn off pps
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_pps_disable(int32_t ctrl_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief get local time
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 * @param[in] local_time: local time
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_get_local(int32_t ctrl_id, struct timespec *local_time);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief set local time, only availabe on RC side
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 * @param[in] local_time: local time
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_set_local(int32_t ctrl_id, struct timespec *local_time);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief sync time by snapshot time
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 * @param[in] source_time: source snapshot time
 * @param[in] pcie_time: pcie snapshot time
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_sync(int32_t ctrl_id, struct timespec *source_time, struct timespec *pcie_time);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief get pcie snopshot time
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 * @param[in] snapshot_time: pcie snapshot time
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_get_snapshot(int32_t ctrl_id, struct timespec *snapshot_time);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief set pps source
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 * @param[in] source: source id of pps
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_set_pps_source(int32_t ctrl_id, int32_t source);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief turn off pcie snapshot function
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_snapshot_off(int32_t ctrl_id);

/**
 * @NO{S13E01C15I}
 * @ASIL{B}
 * @brief turn on pcie snapshot function
 *
 * @param[in] ctrl_id: The Controller id of device
 *                   range: [0, 1]; default: 0
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
int32_t hb_pcie_time_snapshot_on(int32_t ctrl_id);

#ifdef __cplusplus
}
#endif
#endif // INCLUDE_HB_PCIE_H_
