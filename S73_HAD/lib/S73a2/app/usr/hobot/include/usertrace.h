/**
 * @file usertrace.h
 *
 * @NO{S21E10C01I}
 *
 * @ASIL{QM}
 *
 * COPYRIGHT NOTICE
 * Copyright 2023 Horizon Robotics, Inc.
 * All rights reserved.
 * Author: Qianli Zhao <qianli.zhao@horizon.ai>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __USRTRACE_H__
#define __USRTRACE_H__

#include <string>
#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <cstring>

enum trace_flag {
	SYS_SCHED_TRACER = 0x1,
	SYS_NET_TRACER = 0x2,
	SYS_TIMER_TRACER = 0x4,
	SYS_MEM_TRACER = 0x8,
	USER_TRACER  = 0x10,
};

/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief tracer_client class
 */
class tracer_client {
private:
	int mark_fd;
	int clifd;
	std::string ipc_addr;
	std::atomic<bool> inited;
	int recv_fd(int sock_fd);
	int recv_ack(int sock_fd, uint16_t cmd, char *recv_buf);

public:

/* Note: */
/* 1. Multiple save requests at the same time only handle first save request(because both same)*/
/* 2. It is meaningless to save the log immediately after the startup release lock*/
/* 3. re/start/set_mode request will handle after save request finish*/

/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Constructor tracer.
 * @param[in] filepath: socket ipc filepath
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
	tracer_client(const std::string &filepath);

	~tracer_client();
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Init tracer ipc socket.
 *
 * @retval "0": succeed
 * @retval "<0": ipc error
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
	int tracer_init();
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Set current trace mode, and restart trace.
 * @param[in] flags: enable which trace,enum trace_flag combin
 * @param[in] buffer_size_kb: size of per cpu trace buffer, total=buffer_size_kb*core_num
 * @param[in] sync: true:sync mode(default) false:async mode
 *
 * @retval "0": succeed
 * @retval "<0": ipc error
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
	int set_trace_mode(int flags, int buffer_size_kb, bool sync = true);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Restart tracer.
 * @param[in] sync: true:sync mode(default) false:async mode
 *
 * @retval "0": succeed
 * @retval "<0": ipc error
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
	int restart_trace(bool sync = true);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Stop tracer
 * @param[in] sync: true:sync mode(default) false:async mode
 *
 * @retval "0": succeed
 * @retval "<0": ipc error
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
	int stop_trace(bool sync = true);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Stop and save trace log
 * @param[in] target: save target path
 * @param[in] sync: true:sync mode(default) false:async mode
 *
 * @retval "0": succeed
 * @retval "-1": ipc failed
 * @retval "-2": save failed in sync mode
 * @retval "other": error
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
	int save_trace(std::string &target, bool sync = true);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Write the specified message, traceview unrecognized,
 * if tracing_mark_write() failed, may other process has stop the tracer
 * @param[in] buf: specified message
 * @param[in] len: buf len
 *
 * @retval "0": succeed
 * @retval "other": error code
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
	int tracing_mark_write(const char *buf, int len);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Write counter message, if ftrace_mark_counter() failed,
 * may other process has stop the tracer
 * @param[in] msg: specified message, counters with the same msg are grouped
 * @param[in] counter: Counter message
 *
 * @retval "0": succeed
 * @retval "other": error code
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
	int ftrace_mark_counter(const char *msg, long counter);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Write mark begin message, used in pairs with ftrace_mark_end,
 * if ftrace_mark_begin() failed, may other process has stop the tracer
 * @param[in] msg: specified message
 *
 * @retval "0": succeed
 * @retval "other": error code
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
	int ftrace_mark_begin(const char *msg);
/**
 * @NO{S21E10C01I}
 * @ASIL{QM}
 * @brief Write mark end message, used in pairs with ftrace_mark_begin,
 * if ftrace_mark_end() failed, may other process has stop the tracer
 * @param[in] msg: specified message
 *
 * @retval "0": succeed
 * @retval "other": error code
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
	int ftrace_mark_end(const char *msg);
};
#endif /*__USRTRACE_H__*/
