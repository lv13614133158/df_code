/*
 *	  J6X veerpom mapping
 *
 *    COPYRIGHT NOTICE
 *    Copyright 2024 Horizon Robotics, Inc.
 *    All rights reserved.
 *
 *    qiang.wang@horizon.cc
 */
#ifndef _VEEPROM_H_
#define _VEEPROM_H_


/* define copy from include/veeprom.h in uboot */
#define VEEPROM_START_SECTOR (0)
#define VEEPROM_END_SECTOR (0)

#define VEEPROMBAK_ETH0_MACADDR_OFFSET  2
#define VEEPROMBAK_ETH0_MACADDR_SIZE    6

#define VEEPROMBAK_ETH1_MACADDR_OFFSET  8
#define VEEPROMBAK_ETH1_MACADDR_SIZE    6

#define VEEPROMBAK_ETH0_IPADDR_OFFSET   17
#define VEEPROMBAK_ETH0_IPADDR_SIZE     4
#define VEEPROMBAK_ETH0_IPMASK_OFFSET   21
#define VEEPROMBAK_ETH0_IPMASK_SIZE     4
#define VEEPROMBAK_ETH0_IPGATE_OFFSET   25
#define VEEPROMBAK_ETH0_IPGATE_SIZE     4

#define VEEPROMBAK_ETH1_IPADDR_OFFSET   29
#define VEEPROMBAK_ETH1_IPADDR_SIZE     4
#define VEEPROMBAK_ETH1_IPMASK_OFFSET   33
#define VEEPROMBAK_ETH1_IPMASK_SIZE     4
#define VEEPROMBAK_ETH1_IPGATE_OFFSET   37
#define VEEPROMBAK_ETH1_IPGATE_SIZE     4
/* next avilable veeprom bank is 41B */


/* Notice max veeprom bank is 1024B */
#define VEEPROM_MAX_SIZE			1024

#define SYNC_TO_VEEPROM  0
#define SYNC_TO_EEPROM   1
#define SYNC_NO          2

/* boot mode */
#define PIN_2NDBOOT_SEL(x,y)		((((x) & 0x1) << 1) | ((y) & 0x1))
#define PIN_2ND_UFS         0x0
#define PIN_2ND_EMMC        0x1

int veeprom_init(void);

void veeprom_exit(void);

int veeprom_read(int offset, char *buf, int size);

int veeprom_write(int offset, const char *buf, int size);

void set_partition_sel(char* partition);

#endif
