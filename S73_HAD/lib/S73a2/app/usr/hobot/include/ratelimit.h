/*
 * Horizon Robotics
 *
 *  Copyright (C) 2023 Horizon Robotics Inc.
 *  All rights reserved.
 */
#include <pthread.h>

#ifndef INCLUDE_RATELIMIT_H_
#define INCLUDE_RATELIMIT_H_

#define RATELIMIT_INTERVAL 5
#define RATELIMIT_BUSRT    10

#ifdef __cplusplus
extern "C" {
#endif

struct ratelimit {
	pthread_mutex_t mutex;
	int32_t burst;
	int32_t interval;
	int32_t printed;
	int32_t missed;
	int64_t begin;
	int32_t flag;
};

#define ALOG_RATELIMIT_INIT(name, burst_number, interval_in_millisecond) { \
	.burst = burst_number,  \
	.interval = interval_in_millisecond,  \
}

#define DEFINE_ALOG_RATELIMIT(name, burst_number, interval_in_millisecond) \
	static struct ratelimit rs =  \
		ALOG_RATELIMIT_INIT(name, burst_number, interval_in_millisecond);  \

extern int ratelimit(struct ratelimit *rs, const char *tag, const char *file, const char *func, int32_t line);
extern int log_time_duration(int64_t ts);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_RATELIMIT_H_ */
