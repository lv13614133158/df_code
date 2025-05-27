/***
 *                     COPYRIGHT NOTICE
 *            Copyright (C) 2019 -2023, Horizon Robotics Co., Ltd.
 *                   All rights reserved.
 ***/
#ifndef DRIVERS_WATCHDOG_HB_WDT_IOCTL_H_
#define DRIVERS_WATCHDOG_HB_WDT_IOCTL_H_
/**
 * @def  WDT_MAGIC_NUM
 *  ioctl magic num
 */
#define WDT_MAGIC_NUM 		((unsigned int)('W'))
/**
 * @def  HB_WDT_START
 *  ioctl cmd to start
 */
#define HB_WDT_START		_IO(WDT_MAGIC_NUM, 1U)
/**
 * @def  HB_WDT_STOP
 *  ioctl cmd to stop
 */
#define HB_WDT_STOP		_IO(WDT_MAGIC_NUM, 2U)
/**
 * @def  HB_WDT_RESTART
 *  ioctl cmd to restart
 */
#define HB_WDT_RESTART		_IO(WDT_MAGIC_NUM, 3U)
/**
 * @def  HB_WDT_GETSTATUS
 *  ioctl cmd to get status
 */
#define HB_WDT_GETSTATUS	_IO(WDT_MAGIC_NUM, 4U)
/**
 * @def  HB_WDT_SETTIMEOUT
 *  ioctl cmd to set timeout
 */
#define HB_WDT_SETTIMEOUT	_IO(WDT_MAGIC_NUM, 5U)
/**
 * @def  HB_WDT_GETTIMEOUT
 *  ioctl cmd to get timeout
 */
#define HB_WDT_GETTIMEOUT	_IO(WDT_MAGIC_NUM, 6U)
/**
 * @def  HB_WDT_GETTIMELEFT
 *  ioctl cmd to get timeleft
 */
#define HB_WDT_GETTIMELEFT	_IO(WDT_MAGIC_NUM, 7U)
/**
 * @def  HB_WDT_SETMODE
 *  ioctl cmd to set mode
 */
#define HB_WDT_SETMODE		_IO(WDT_MAGIC_NUM, 8U)
/**
 * @def  HB_WDT_GETMODE
 *  ioctl cmd to get mode
 */
#define HB_WDT_GETMODE		_IO(WDT_MAGIC_NUM, 9U)
/**
 * @def  HB_WDT_PAUSE
 *  ioctl cmd to pause
 */
#define HB_WDT_PAUSE		_IO(WDT_MAGIC_NUM, 10U)
/**
 * @def  HB_WDT_PROCEED
 *  ioctl cmd to proceed
 */
#define HB_WDT_PROCEED		_IO(WDT_MAGIC_NUM, 11U)
#endif
