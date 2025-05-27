/*
 * Horizon Robotics
 *
 *  Copyright (C) 2023 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: Qianli Zhao <qianli.zhao@horizon.ai>
 *
 */
#ifndef __DUMPER_CLIENT_H__
#define __DUMPER_CLIENT_H__
#include <string>

class stackdump {
private:
	int clifd;
	std::string ipc_addr;
	static stackdump *instance;
	int signal_init(void);
	int recv_ack(int sock_fd, uint16_t cmd, char *recv_buf);
	stackdump(const std::string &ipc);
	~stackdump();

public:
/*
 * Singleton Constructor
 */
	static stackdump *get_instance();
/*
 * Crash stackdump save path, only used in signal handler
*/
	std::string dp;
/*
 * stackdump_request, send request to dump_server, only used in signal handler
*/
	int stackdump_request(int sk, struct dumper_frame *df);
/*
 * connect_dumper - connect to dump_server, only used in signal handler
*/
	int connect_dumper(void);

/*
 * stackdump_init - Stackdump init function, hack signal handler
 * crash_path: crash dump save path
 * Return: 0 success, other error code
*/
	int stackdump_init(const std::string &crash_path);
/*
 * stackdump_process_stat - Request dump_server dump process stat
 * The function returns immediately after successful IPC and does not wait for the dump finish
 * dump_path: process dump save path
 * Return: 0 success, other error code
*/
	int stackdump_process_stat(const std::string &dump_path);
/*
 * stackdump_thread_stat - Request dump_server dump thread stat
 * The function returns immediately after successful IPC and does not wait for the dump finish
 * dump_path: thread dump save path
 * Return: 0 success, other error code
*/
	int stackdump_thread_stat(const std::string &dump_path);
};

#endif /* __DUMPER_CLIENT_H__ */
