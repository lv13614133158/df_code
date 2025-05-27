/*************************************************************************************
 *                                COPYRIGHT NOTICE
 *                 Copyright (C) 2022 -2024 Horizon Robotics, Inc.
 *                                All rights reserved.
 ************************************************************************************/

/**
 * @file hobot_clock_hal.h
 *
 * @NO{S21E02C04I}
 * @ASIL{B}
 */
#ifndef HOBOT_CLOCK_HAL_H
#define HOBOT_CLOCK_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/types.h>
#include <linux/pps.h>
#include <linux/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define assert_offset       assert_off_tu.tspec
#define clear_offset        clear_off_tu.tspec
#define assert_timestamp        assert_tu.tspec
#define clear_timestamp         clear_tu.tspec

#define CLOCKFD 3
#define FD_TO_CLOCKID(fd)   ((clockid_t) (((~fd) << 3) | CLOCKFD))
#define CLOCKID_TO_FD(clk)	(~((clk) >> 3))

#define NS_PER_SEC 1000000000L
#define US_PER_SEC 1000000L

#define HB_TSYNC_ERR_OPEN_DEV        -1     /* open device faile */
#define HB_TSYNC_ERR_GET_CAP         -2     /* get support feature failed */
#define HB_TSYNC_ERR_GET_PARAM       -3     /* get parameter failed */
#define HB_TSYNC_ERR_SET_PARAM       -4     /* set parameter failed */
#define HB_TSYNC_ERR_UNSUPPORT_ID    -5     /* invalid clock id */
#define HB_TSYNC_ERR_UNSUPPORT_TYPE  -6     /* invalid clock type or clock type is not support this attribute */
#define HB_TSYNC_ERR_FETCH_PPS       -7     /* fetch pps failed */
#define HB_TSYNC_ERR_ENABLE          -8     /* enable failed */
#define HB_TSYNC_ERR_PTR_NULL        -9     /* input parameter error */

struct ntp_fp {
    unsigned int integral;
    unsigned int fractional;
};

union pps_timeu {
    struct timespec tspec;
    struct ntp_fp ntpfp;
    unsigned long longpad[3];
};

struct pps_info {
    unsigned long assert_sequence;
    unsigned long clear_sequence;
    union pps_timeu assert_tu;
    union pps_timeu clear_tu;
    int current_mode;
};

struct pps_params {
    int api_version;
    int mode;
    union pps_timeu assert_off_tu;
    union pps_timeu clear_off_tu;
};

typedef int pps_handle_t;
typedef struct pps_info pps_info_t;
typedef struct pps_params pps_params_t;

/**
 * @enum timesynClockType
 * @Define clock type
 */
enum timesynClockType {
    CLOCK_SYS,
    CLOCK_PHC,
    CLOCK_PCIE,
    CLOCK_EXRTC_32000,
    CLOCK_EXRTC_32768,
    CLOCK_TYPE_RESERVED
};

/**
 * @enum timesyncSnapshotSource
 * @Define clock id
 */
enum timesynClockID {
    CLOCK_SYS_ID,
    CLOCK_PHC0_ID,
    CLOCK_PHC1_ID,
    CLOCK_PCIE0_ID,
    CLOCK_PCIE1_ID,
    CLOCK_EXRTC_32000_ID,
    CLOCK_EXRTC_32768_ID,
    CLOCK_ID_RESERVED
};

/**
 * @enum timesyncSnapshotSource
 * @Define snapshot source type
 */
enum timesyncSnapshotSource {
    SNAPSHOT_SOURCE_RTC,
    SNAPSHOT_SOURCE_GPS_PPS,
    SNAPSHOT_SOURCE_LIDAR,
    SNAPSHOT_SOURCE_AP,
    SNAPSHOT_SOURCE_MCU_ETH,
    SNAPSHOT_SOURCE_RESERVED,
};

/**
 * @struct _timesynClock
 * @Define the information of clock
 */
typedef struct _timesynClock {
    enum timesynClockType type; /**< clock type. */
    int32_t fd; /**< File descriptors of clock. */
} timesyncClock;

/**
 * @struct _timesynClock_capability
 * @Define the capability of clock
 */
typedef struct _timesynClock_capability {
    bool get_current_time;
    bool set_current_time;
    bool adj_clock_time;
    bool set_clock_freq;
    bool get_clock_freq;
    bool get_max_clock_freq;
    bool set_clock_snapshot_source;
    bool get_snapshort_time;
    bool generate_pps;
} timesynCapability;

/**
 * @struct _timesyncPPS
 * @Define the information of pps
 */
typedef struct _timesyncPPS {
    pps_handle_t handle; /**< represents a PPS source. */
    int32_t *avail_mode;  /**< PPS allowed mode. */
} timesyncPPS;

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Open clock
 *
 * @param[in] clock_id: clock id 
 *            range: [0, 7]; default: 0
 * @param[out] hb_clock: clock info 
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncOpenClock(enum timesynClockID clock_id, timesyncClock *hb_clock);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Close clock
 *
 * @param[in] hb_clock: clock info 
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncCloseClock(const timesyncClock *hb_clock);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief get clock time
 *
 * @param[in] hb_clock: clock info
 * @param[out] ts: timestamp
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncGetCurrentTime(const timesyncClock *hb_clock, struct timespec *ts);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Set clock time
 *
 * @param[in] hb_clock: clock info
 * @param[in] ts: timestamp
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncSetCurrentTime(const timesyncClock *hb_clock, const struct timespec *ts);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Adjust clock time with step
 *
 * @param[in] hb_clock: clock info
 * @param[in] step: adjust step
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncAdjClockTime(const timesyncClock *hb_clock, int64_t step);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Set clock frequency
 *
 * @param[in] hb_clock: clock info
 * @param[in] freq: frequency
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncSetClockFreq(const timesyncClock *hb_clock, double freq);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Get clock frequency
 *
 * @param[in] hb_clock: clock info
 * @param[out] freq: clock frequency
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncGetClockFreq(const timesyncClock *hb_clock, double *freq);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Get max frequency
 *
 * @param[in] hb_clock: clock info 
 *
 * @retval =0: frequency value
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncGetMaxClockFreq(const timesyncClock *hb_clock);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Set clock snapshort source
 *
 * @param[in] hb_clock: clock info
 * @param[in] pps_source: pps source
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncSetClockSnapshotSource(const timesyncClock *hb_clock, enum timesyncSnapshotSource pps_source);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Get snapshort
 *
 * @param[in] hb_clock: clock info
 * @param[out] snapshort: snapshort time
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncGetClockSnapshotTime(const timesyncClock *hb_clock, struct timespec *snapshot);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Generate pps
 *
 * @param[in] hb_clock: clock info
 * @param[in] enable: enable pps
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncClockGeneratePPS(const timesyncClock *hb_clock, int32_t enable);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Open pps
 *
 * @param[in] path: pps path
 * @param[out] hb_pps: pps info
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncOpenPPS(const char *path, timesyncPPS *hb_pps);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Wait for pps
 *
 * @param[in] hb_pps: pps
 * @param[out] infobuf: pps info
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncFetchPPS(const timesyncPPS *hb_pps, pps_info_t *infobuf);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Close pps
 *
 * @param[in] hb_pps: pps
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncClosePPS(const timesyncPPS *hb_pps);

/**
 * @NO{S21E02C04I}
 * @ASIL{B}
 * @brief Get clock capability
 *
 * @param[in] hb_clock: clock info
 * @param[out] clock_cap: clock capability
 *
 * @retval =0: success
 * @retval <0: failure
 *
 * @compatibility HW: J6
 * @compatibility SW: 0.1.0
 */
extern int32_t timesyncGetClockCapability(const timesyncClock *hb_clock, timesynCapability *clock_cap);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* HOBOT_CLOCK_HAL_H */
