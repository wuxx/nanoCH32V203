/********************************** (C) COPYRIGHT *******************************
 * File Name          : Internal_Flash.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : header file for Internal_Flash.c
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef USER_INTERNAL__FLASH_C_
#define USER_INTERNAL__FLASH_C_

//#define IFLASH_UDISK_SIZE       32768               // UDisk Size = 32K
//#define IFLASH_UDISK_SIZE       40960               // UDisk Size = 40K
#define IFLASH_UDISK_SIZE       49152               // UDisk Size = 48K

#if (IFLASH_UDISK_SIZE == 32768)
    #define IFLASH_UDISK_START_ADDR   0x8000
#elif ( IFLASH_UDISK_SIZE == 40960 )
    #define IFLASH_UDISK_START_ADDR   0x6000
#elif ( IFLASH_UDISK_SIZE == 49152 )
    #define IFLASH_UDISK_START_ADDR   0x4000
#endif

#define IFLASH_UDISK_END_ADDR     0xFFFF
#define INTERNAL_FLASH_PAGE_SIZE  256

extern void IFlash_Prog_512(uint32_t address,uint32_t *pbuf);

#endif /* USER_INTERNAL__FLASH_C_ */
