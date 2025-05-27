/*
 * Horizon Robotics
 *
 *  Copyright (C) 2019 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: leye.wang<leye.wang@horizon.ai>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef INCLUDE_LOGGING_H_
#define INCLUDE_LOGGING_H_

#define ALOG_SUPPORT 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef ALOG_SUPPORT
#include <log.h>
#endif

#include "./ratelimit.h"

#define STRINGIZE_NO_EXPANSION(x) #x
#define STRINGIZE(x) STRINGIZE_NO_EXPANSION(x)
#define HERE __FILE__ ":" STRINGIZE(__LINE__)

#ifndef SUBSYS_NAME
#define SUBSYS_NAME
#endif
#define SUBSYS STRINGIZE(SUBSYS_NAME)

#define L_FATAL "[FATAL][" SUBSYS "][" HERE "] "
#define L_INFO "[INFO][" SUBSYS "][" HERE "] "
#define L_WARNING "[WARNING][" SUBSYS "][" HERE "] "
#define L_ERROR "[ERROR][" SUBSYS "][" HERE "] "
#define L_DEBUG "[DEBUG][" SUBSYS "][" HERE "] "
#define L_VERBOSE "[VERBOSE][" SUBSYS "][" HERE "] "

/* output log by console */
#define CONSOLE_VERBOSE_LEVEL 	15
#define CONSOLE_DEBUG_LEVEL		14
#define CONSOLE_INFO_LEVEL		13
#define CONSOLE_WARNING_LEVEL	12
#define CONSOLE_ERROR_LEVEL		11
#define CONSOLE_FATAL_LEVEL		10

/* output log by ALOG */
#ifdef ALOG_SUPPORT
#define ALOG_VERBOSE_LEVEL		5
#define ALOG_DEBUG_LEVEL		4
#define ALOG_INFO_LEVEL			3
#define ALOG_WARNING_LEVEL		2
#define ALOG_ERROR_LEVEL		1
#define ALOG_FATAL_LEVEL		0
#else
#define ALOG_VERBOSE_LEVEL		CONSOLE_VERBOSE_LEVEL
#define ALOG_DEBUG_LEVEL		CONSOLE_DEBUG_LEVEL
#define ALOG_INFO_LEVEL			CONSOLE_INFO_LEVEL
#define ALOG_WARNING_LEVEL		CONSOLE_WARNING_LEVEL
#define ALOG_ERROR_LEVEL		CONSOLE_ERROR_LEVEL
#define ALOG_FATAL_LEVEL		CONSOLE_FATAL_LEVEL
#endif

#ifndef pr_fmt
#define pr_fmt(fmt)		fmt
#endif

#ifndef here_fmt
#define here_fmt(fmt)		"[%s:%d]" fmt, __func__, __LINE__
#endif

#ifndef ALOGV_TAG
#define ALOGV_TAG(tag, ...) ((void)ALOG(LOG_VERBOSE, tag, __VA_ARGS__))
#endif
#ifndef ALOGD_TAG
#define ALOGD_TAG(tag, ...) ((void)ALOG(LOG_DEBUG, tag, __VA_ARGS__))
#endif
#ifndef ALOGI_TAG
#define ALOGI_TAG(tag, ...) ((void)ALOG(LOG_INFO, tag, __VA_ARGS__))
#endif
#ifndef ALOGW_TAG
#define ALOGW_TAG(tag, ...) ((void)ALOG(LOG_WARN, tag, __VA_ARGS__))
#endif
#ifndef ALOGE_TAG
#define ALOGE_TAG(tag, ...) ((void)ALOG(LOG_ERROR, tag, __VA_ARGS__))
#endif
#ifndef ALOGF_TAG
#define ALOGF_TAG(tag, ...) ((void)ALOG(LOG_FATAL, tag, __VA_ARGS__))
#endif
#ifndef ALOGF
#define ALOGF(...) ((void)ALOG(LOG_FATAL, LOG_TAG, __VA_ARGS__))
#endif

/* get log level from environment variable */
/* we use console debug level in default */
#define LOGLEVEL_ENV	"LOGLEVEL"

#define ADD(x, y)	((x) + (y))
#define COMPARE(x, y)	(x >= y ? true : false)

#define common_print(level, log_level, log_priority, tag, fmt, ...)       \
       do {    \
               int loglevel = get_loglevel();  \
               if (loglevel >= CONSOLE_FATAL_LEVEL && loglevel <= CONSOLE_VERBOSE_LEVEL && \
				COMPARE(loglevel, ADD(log_level, CONSOLE_FATAL_LEVEL))) {             \
                       (void)fprintf(stdout, "[" log_priority "][" tag "]" here_fmt(fmt), ##__VA_ARGS__);              \
                       (void)fprintf(stdout, "\n");    \
               }	\
               if  (loglevel >= ALOG_FATAL_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL && \
				COMPARE(loglevel, log_level)) {    \
                       ALOG(level, tag, here_fmt(fmt), ##__VA_ARGS__); \
               }       \
       } while (0);     \

static inline int get_loglevel(void)
{
	const char *loglevel_env = NULL;
	int loglevel_value = CONSOLE_ERROR_LEVEL;

	loglevel_env = getenv(LOGLEVEL_ENV);
	if (loglevel_env != NULL) {
		loglevel_value = atoi(loglevel_env);
		/* loglevel value should in the configuration area */
		if (((loglevel_value >= CONSOLE_FATAL_LEVEL) &&
					(loglevel_value <= CONSOLE_VERBOSE_LEVEL)) ||
				((loglevel_value >= ALOG_FATAL_LEVEL) &&
				 (loglevel_value <= ALOG_VERBOSE_LEVEL)))
			return loglevel_value;
	}

	/* default log level */
	loglevel_value = CONSOLE_ERROR_LEVEL;

	return loglevel_value;
}

#if defined DYNDBG_LOG

#define LOGLEVEL_VERBOSE ALOG_VERBOSE_LEVEL
#define LOGLEVEL_DEBUG ALOG_DEBUG_LEVEL
#define LOGLEVEL_INFO ALOG_INFO_LEVEL
#define LOGLEVEL_WARN ALOG_WARNING_LEVEL
#define LOGLEVEL_ERROR ALOG_ERROR_LEVEL
#define LOGLEVEL_FATAL ALOG_FATAL_LEVEL


#define DYNDBG_LOG_CXT_LEVEL_BITS (8u)
#define DYNDBG_LOG_CXT_FLAGS_BITS (16u)
#define DYNDBG_LOG_CXT_CTRL_FLAGS_OFFSET (DYNDBG_LOG_CXT_LEVEL_BITS+8u)

#if !defined DYNDBG_LOG_SINK_DEFAULT
#define DYNDBG_LOG_SINK_DEFAULT (0u)  /* 0:alog, 1:con to match flag *_en bit offset */
#endif

/* give user a chance to define the default flags of a module */
#if !defined DYNDBG_LOG_CTRL_FLAGS
#define DYNDBG_LOG_CTRL_FLAGS (0x11u)
#endif

#define DYNDBG_LOG_CTRL_FLAGS_DEFAULT                                \
    ((1u << (DYNDBG_LOG_CXT_LEVEL_BITS+DYNDBG_LOG_SINK_DEFAULT))     \
     | (DYNDBG_LOG_CTRL_FLAGS << DYNDBG_LOG_CXT_CTRL_FLAGS_OFFSET))  \

union dyndbg_log_cxt_flags {
    uint32_t all;
    struct {  /* le byte order */
        int8_t level_bit;
        uint8_t alog_en:1;  /* output to alog */
        uint8_t con_en:1;  /* output to console */
        uint8_t reserved0:6;
        union {
            uint16_t flag_bits:DYNDBG_LOG_CXT_FLAGS_BITS;
            struct {
                uint16_t m:1;  /* module name */
                uint16_t file:1;  /* filename */
                uint16_t func:1;  /* function */
                uint16_t line:1;  /* line number */
                uint16_t lvlchar:1;  /* level char */
                uint16_t pid:1;  /* pid */
                uint16_t tid:1;  /* tid */
                uint16_t p:1;  /* debug print */
                uint16_t ts:1;  /* timestamp */
                uint16_t ts_mono:1;  /* mono timestamp */
                uint16_t color:1;  /* ansi color */
            };
        };
    };
};

struct dyndbg_log_cxt {
    const char *module;
    const char *file;
    const char *func;
    const char *format;
    uint32_t line;
    union dyndbg_log_cxt_flags flags;
};

struct dyndbg_log_module_entry {
    struct dyndbg_log_module_entry *next;
    const char *module_name;
    struct dyndbg_log_cxt *start, *stop;
};

#if defined __cplusplus
extern "C" {
#endif
    int dyndbg_log_precheck(struct dyndbg_log_cxt *lc);
    void dyndbg_log_to_con(int level, struct dyndbg_log_cxt *lc, const char *fmt, ...);
    void dyndbg_log_register_module(struct dyndbg_log_module_entry *entry);
    void dyndbg_log_unregister_module(struct dyndbg_log_module_entry *entry);

    extern struct dyndbg_log_cxt __start_dyndbg_log_cxt_ffl;
    extern struct dyndbg_log_cxt __stop_dyndbg_log_cxt_ffl;

#if defined __cplusplus
}
#endif

#define dyndbg_log_to_alog_default(lc, level, lvlchar, tag, fmt, ...)   \
    ALOG##lvlchar(fmt, ##__VA_ARGS__)
#define dyndbg_log_to_alog_with_tag(lc, level, lvlchar, tag, fmt, ...)  \
    ALOG##lvlchar##_TAG(tag, here_fmt(fmt), ##__VA_ARGS__)

#ifndef AT_SEC
#define AT_SEC(s) __attribute__((used, section(#s)))
#endif

#define pr_common(type, level, lvlchar, tag, fmt, ...)                  \
    do {                                                                \
        static AT_SEC(dyndbg_log_cxt_ffl) struct dyndbg_log_cxt lc = {  \
            .file = __FILE__,                                           \
            .func = __func__,                                           \
            .line = __LINE__,                                           \
            .format = fmt,                                              \
            .flags = {(uint8_t)(level)|DYNDBG_LOG_CTRL_FLAGS_DEFAULT}   \
        };                                                              \
        if (0 != dyndbg_log_precheck(&lc)) {                            \
            break;                                                      \
        }                                                               \
        int lvl = lc.flags.level_bit;                                   \
        if (lc.flags.con_en) {                                          \
            dyndbg_log_to_con(lvl, &lc, fmt, ##__VA_ARGS__);            \
        }                                                               \
        if (lc.flags.alog_en) {                                         \
            dyndbg_log_to_alog##type(lc, lvl, lvlchar, tag, fmt, ##__VA_ARGS__); \
        }                                                               \
    } while (0)                                                         \

#define pr_verbose(fmt, ...) pr_common(_default, LOGLEVEL_VERBOSE, V, _, fmt, ##__VA_ARGS__)
#define pr_debug(fmt, ...) pr_common(_default, LOGLEVEL_DEBUG, D, _, fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...) pr_common(_default, LOGLEVEL_INFO, I, _, fmt, ##__VA_ARGS__)
#define pr_warn(fmt, ...) pr_common(_default, LOGLEVEL_WARN, W, _, fmt, ##__VA_ARGS__)
#define pr_err(fmt, ...) pr_common(_default, LOGLEVEL_ERROR, E, _, fmt, ##__VA_ARGS__)
#define pr_fatal(fmt, ...) pr_common(_default, LOGLEVEL_FATAL, F, _, fmt, ##__VA_ARGS__)

#define pr_verbose_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_VERBOSE, V, tag, fmt, ##__VA_ARGS__)
#define pr_debug_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_DEBUG, D, tag, fmt, ##__VA_ARGS__)
#define pr_info_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_INFO, I, tag, fmt, ##__VA_ARGS__)
#define pr_warn_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_WARN, W, tag, fmt, ##__VA_ARGS__)
#define pr_err_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_ERROR, E, tag, fmt, ##__VA_ARGS__)
#define pr_fatal_with_tag(tag, fmt, ...) pr_common(_with_tag, LOGLEVEL_FATAL, F, tag, fmt, ##__VA_ARGS__)

#define DYNDBG_CONCAT_VAR_(x, y) x##y
#define DYNDBG_CONCAT_VAR(x, y) DYNDBG_CONCAT_VAR_(x, y)
#define DYNDBG_UNIQUE_VAR(unique_prefix) DYNDBG_CONCAT_VAR(unique_prefix, __LINE__)

#define DYNDBG_MODULE_DECLARE(name)                                     \
    static struct dyndbg_log_module_entry                               \
    DYNDBG_UNIQUE_VAR(log_module_e) = {                                 \
        .module_name = #name,                                           \
        .start = &__start_dyndbg_log_cxt_ffl,                           \
        .stop = &__stop_dyndbg_log_cxt_ffl,                             \
    };                                                                  \
    __attribute__((used, constructor(101)))                             \
    static void DYNDBG_CONCAT_VAR(dyndbg_log_init_, DYNDBG_UNIQUE_VAR(name))(void) { \
        dyndbg_log_register_module(&DYNDBG_UNIQUE_VAR(log_module_e));   \
    }                                                                   \
    __attribute__((used, destructor(101)))                              \
    static void DYNDBG_CONCAT_VAR(dyndbg_log_deinit_, DYNDBG_UNIQUE_VAR(name))(void) { \
        dyndbg_log_unregister_module(&DYNDBG_UNIQUE_VAR(log_module_e)); \
    }                                                                   \

#else  /* !DYNDBG_LOG */

#define DYNDBG_MODULE_DECLARE(module_name)

/* pr_info defintion */
#ifdef ALOG_SUPPORT
#define pr_info(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_INFO_LEVEL)		\
				(void)fprintf(stdout, L_INFO "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel >= ALOG_INFO_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL)	\
				ALOGI(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_info_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_INFO_LEVEL) {\
				(void)fprintf(stdout, "[INFO][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  ( loglevel >= ALOG_INFO_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL ) {\
				ALOGI_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);		\
			}	\
	} while (0);
#else
#define pr_info(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_INFO_LEVEL)		\
				(void)fprintf(stdout, L_INFO "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_info_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_INFO_LEVEL)		\
				(void)fprintf(stdout, L_INFO "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

/* pr_warn defintion */
#ifdef ALOG_SUPPORT
#define pr_warn(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_WARNING_LEVEL)		\
				(void)fprintf(stdout, L_WARNING "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel >= ALOG_WARNING_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL)	\
				ALOGW(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_warn_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_WARNING_LEVEL) {		\
				(void)fprintf(stdout, "[WARNING][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  (loglevel >= ALOG_WARNING_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL) { \
				ALOGW_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);		\
			}	\
	} while (0);
#else
#define pr_warn(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_WARNING_LEVEL)		\
				(void)fprintf(stdout, L_WARNING "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_warn_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_WARNING_LEVEL)		\
				(void)fprintf(stdout, L_WARNING "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

/* pr_err defintion */
#ifdef ALOG_SUPPORT
#define pr_err(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_ERROR_LEVEL)		\
				(void)fprintf(stdout, L_ERROR "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel >= ALOG_ERROR_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL)	\
				ALOGE(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_err_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_ERROR_LEVEL) {		\
				(void)fprintf(stdout, "[ERROR][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  (loglevel >= ALOG_ERROR_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL) {	\
				ALOGE_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);	\
			}	\
	} while (0);
#else
#define pr_err(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_ERROR_LEVEL)		\
				(void)fprintf(stdout, L_ERROR "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_err_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_ERROR_LEVEL)		\
				(void)fprintf(stdout, L_ERROR "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

/* pr_debug defintion */
#ifdef ALOG_SUPPORT
#define pr_debug(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_DEBUG_LEVEL)		\
				(void)fprintf(stdout, L_DEBUG "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel >= ALOG_DEBUG_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL)	\
				ALOGD(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_debug_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_DEBUG_LEVEL) {		\
				(void)fprintf(stdout, "[DEBUG][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  (loglevel >= ALOG_DEBUG_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL) {	\
				ALOGD_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);		\
			}	\
	} while (0);
#else
#define pr_debug(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_DEBUG_LEVEL)		\
				(void)fprintf(stdout, L_DEBUG "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_debug_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_DEBUG_LEVEL)		\
				(void)fprintf(stdout, L_DEBUG "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

/* pr_verbose defintion */
#ifdef ALOG_SUPPORT
#define pr_verbose(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_VERBOSE_LEVEL)		\
				(void)fprintf(stdout, L_VERBOSE "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel == ALOG_VERBOSE_LEVEL)		\
				ALOGV(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_verbose_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_VERBOSE_LEVEL) {		\
				(void)fprintf(stdout, "[VERBOSE][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  (loglevel == ALOG_VERBOSE_LEVEL) {	\
				ALOGV_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);		\
			}	\
	} while (0);
#else
#define pr_verbose(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_VERBOSE_LEVEL)		\
				(void)fprintf(stdout, L_VERBOSE "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_verbose_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_VERBOSE_LEVEL)		\
				(void)fprintf(stdout, L_VERBOSE "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

/* pr_fatal defintion */
#ifdef ALOG_SUPPORT
#define pr_fatal(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_FATAL_LEVEL)		\
				(void)fprintf(stdout, L_FATAL "" pr_fmt(fmt), ##__VA_ARGS__);		\
			if (loglevel >= ALOG_FATAL_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL)	\
				ALOGF(fmt, ##__VA_ARGS__);		\
	} while (0);
#define pr_fatal_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_FATAL_LEVEL) {		\
				(void)fprintf(stdout, "[FATAL][" tag "]" here_fmt(fmt), ##__VA_ARGS__);		\
				(void)fprintf(stdout, "\n");	\
			}	\
			if  (loglevel >= ALOG_FATAL_LEVEL && loglevel <= ALOG_VERBOSE_LEVEL) {	\
				ALOGF_TAG(tag, here_fmt(fmt), ##__VA_ARGS__);		\
			}	\
	} while (0);
#else
#define pr_fatal(fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_FATAL_LEVEL)		\
				(void)fprintf(stdout, L_FATAL "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#define pr_fatal_with_tag(tag, fmt, ...)				\
	do {								\
			int loglevel = get_loglevel();		\
			if (loglevel >= CONSOLE_FATAL_LEVEL)		\
				(void)fprintf(stdout, L_FATAL "" pr_fmt(fmt), ##__VA_ARGS__);		\
	} while (0);
#endif

#endif  /* DYNDBG_LOG end */

#define pr_common_ratelimit(level, log_level, log_priority, tag, fmt, ...)				\
	do {															\
		static struct ratelimit __attribute__((unused)) rs = {  \
			.burst = RATELIMIT_BUSRT,                          \
			.interval = RATELIMIT_INTERVAL,                   \
		};	\
		if (ratelimit(&rs, tag, __FILE__, __func__, __LINE__)) {	\
			common_print(level, log_level, log_priority, tag, fmt, ##__VA_ARGS__);		\
		}	\
	} while (0);													\

#define pr_err_ratelimit(tag, fmt, ...)   \
	pr_common_ratelimit(LOG_ERROR, ALOG_ERROR_LEVEL, L_ERROR, tag, fmt, ##__VA_ARGS__)
#define pr_info_ratelimit(tag, fmt, ...)  \
	pr_common_ratelimit(LOG_INFO, ALOG_INFO_LEVEL, L_INFO, tag, fmt, ##__VA_ARGS__)
#define pr_warn_ratelimit(tag, fmt, ...)  \
	pr_common_ratelimit(LOG_WARN, ALOG_WARNING_LEVEL, L_WARNING, tag, fmt, ##__VA_ARGS__)
#define pr_debug_ratelimit(tag, fmt, ...) \
	pr_common_ratelimit(LOG_DEBUG, ALOG_DEBUG_LEVEL, L_DEBUG, tag, fmt, ##__VA_ARGS__)
#define pr_fatal_ratelimit(tag, fmt, ...) \
	pr_common_ratelimit(LOG_FATAL, ALOG_FATAL_LEVEL, L_FATAL, tag, fmt, ##__VA_ARGS__)
#define pr_verbose_ratelimit(tag, fmt, ...) \
	pr_common_ratelimit(LOG_VERBOSE, ALOG_VERBOSE_LEVEL, L_VERBOSE, tag, fmt, ##__VA_ARGS__)

#define pr_common_once(level, log_level, log_priority, tag, fmt, ...)				\
	do {															\
		static bool print_once = false;	\
		if (!print_once) {	\
			print_once = true;	\
			common_print(level, log_level, log_priority, tag, fmt, ##__VA_ARGS__);		\
		}	\
	} while (0);													\

#define pr_err_once(tag, fmt, ...)   \
	pr_common_once(LOG_ERROR, ALOG_ERROR_LEVEL, L_ERROR, tag, fmt, ##__VA_ARGS__)
#define pr_info_once(tag, fmt, ...)  \
	pr_common_once(LOG_INFO, ALOG_INFO_LEVEL, L_INFO, tag, fmt, ##__VA_ARGS__)
#define pr_warn_once(tag, fmt, ...)  \
	pr_common_once(LOG_WARN, ALOG_WARNING_LEVEL, L_WARNING, tag, fmt, ##__VA_ARGS__)
#define pr_debug_once(tag, fmt, ...) \
	pr_common_once(LOG_DEBUG, ALOG_DEBUG_LEVEL, L_DEBUG, tag, fmt, ##__VA_ARGS__)
#define pr_fatal_once(tag, fmt, ...) \
	pr_common_once(LOG_FATAL, ALOG_FATAL_LEVEL, L_FATAL, tag, fmt, ##__VA_ARGS__)
#define pr_verbose_once(tag, fmt, ...) \
	pr_common_once(LOG_VERBOSE, ALOG_VERBOSE_LEVEL, L_VERBOSE, tag, fmt, ##__VA_ARGS__)

#endif /* INCLUDE_LOGGING_H_ */
