/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/

/**
 * @file hb_rpmsg_interface.h
 *
 * @NO{S17E09C01I}
 * @ASIL{B}
 */

#ifndef HB_RPMSG_INTERFACE_H
#define HB_RPMSG_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>

/* transfer features */
#define RPMSG_F_BLOCK      (1 << 0)
#define RPMSG_F_NONBLOCK   (0)
#define RPMSG_F_CRC_CHECK  (1 << 1)

/* error code */
#define RPMSG_ERR_INVALID_ARG           (-1)
#define RPMSG_ERR_INVALID_SERVER        (-2)
#define RPMSG_ERR_OUT_OF_RES            (-3)
#define RPMSG_ERR_KER_USR_TRANS         (-4)
#define RPMSG_ERR_SEND_BUF_OVERSIZE     (-5)
#define RPMSG_ERR_NO_MEM                (-6)
#define RPMSG_ERR_TIMEOUT               (-7)
#define RPMSG_ERR_SIGNAL_STOP           (-8)
#define RPMSG_ERR_RECV_BUF_OVERFLOW     (-9)
#define RPMSG_ERR_NOT_START_SERVER      (-10)
#define RPMSG_ERR_CRC_CHECK             (-11)
#define RPMSG_ERR_DRV_VERSION           (-12)
#define RPMSG_ERR_UNKNOWN_ERR           (-13)

struct rpmsg_handle;

/**
 * @NO{S17E09C01I}
 * @brief establish connection with communication service
 *
 * @param[in] server_name: communication service name
 * @param[in] flags: transfer features, such as block or nonblock
 * @param[in] timeout: timeout in block transfer mode in milliseconds
 * @param[out] handle: communication handle
 *
 * @retval "0": success
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_connect_server(const char *server_name, int32_t flags, int32_t timeout,
struct rpmsg_handle **handle);


/**
 * @NO{S17E09C01I}
 * @brief abolish connection with communication service specified by handle
 *
 * @param[in] handle: communicatin handle want to disconnect
 *
 * @retval "0": success
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_disconnect_server(struct rpmsg_handle *handle);

/**
 * @NO{S17E09C01I}
 * @brief send frame on specific communication service
 *
 * @param[in] handle: communication handle want to send
 * @param[in] buf: contain frame data want to send
 * @param[in] len: data length want to send
 *
 * @retval ">0": the number of bytes sent
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_send(const struct rpmsg_handle *handle, const char *buf, int32_t len);


/**
 * @NO{S17E09C01I}
 * @brief receive frame on specific communication service
 *
 * @param[in] handle: communication handle want to recv
 * @param[in] buf: contain received data
 * @param[in] len: received data length
 *
 * @retval ">0": the number of bytes received
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_recv(const struct rpmsg_handle *handle, char *buf, int32_t len);

/**
 * @NO{S17E09C01I}
 * @brief send frame on specific communication service with timeout mechanism
 *
 * @param[in] handle: communication handle want to send
 * @param[in] buf: contain frame data want to send
 * @param[in] len: data length want to send
 * @param[in] timeout: timeout in block transfer mode in milliseconds
 *
 * @retval ">0": the number of bytes sent
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_send_timeout(const struct rpmsg_handle *handle, const char *buf, int32_t len, int32_t timeout);

/**
 * @NO{S17E09C01I}
 * @brief receive frame on specific communication service with timeout mechanism
 *
 * @param[in] handle: communication handle want to recv
 * @param[in] buf: contain received data
 * @param[in] len: received data length
 * @param[in] timeout: timeout in block transfer mode in milliseconds
 *
 * @retval ">0": the number of bytes received
 * @retval "<0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_recv_timeout(const struct rpmsg_handle *handle, char *buf, int32_t len, int32_t timeout);

/**
 * @NO{S17E09C01I}
 * @brief return string type error message according to error_code
 *
 * @param[in] error_code: communication handle want to recv
 * @param[in] buf: error code return from rpmsg lib API
 *
 * @return string type error message
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J5/J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
const char *hb_rpmsg_error_message(int32_t error_code);

/**
 * @NO{S17E09C01I}
 * @brief get the version of rpmsg library
 *
 * @param[in] major: major version number
 * @param[in] minor: minor version number
 * @param[in] patch: patch version number
 *
 * @retval "0": success
 * @retval "!0": error code
 *
 * @data_read None
 * @data_updated None
 * @compatibility HW: J6
 * @compatibility SW: 1.0.0
 *
 * @callgraph
 * @callergraph
 * @design
 */
int32_t hb_rpmsg_get_version(uint32_t *major, uint32_t *minor, uint32_t *patch);

#ifdef __cplusplus
}
#endif

#endif /*HB_RPMSG_INTERFACE_H*/
