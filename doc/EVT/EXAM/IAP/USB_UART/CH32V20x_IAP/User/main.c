/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
用于IAP实验例程：
可支持串口与USB进行FLASH烧录
注：
1. 用IAP下载工具，实现下载 PA0悬空(默认上拉输入)
2. 在下载完APP后，PA0接地（低电平输入），按复位键即可运行APP程序。
3. 例程需安装CH372驱动。
 
*/

#include "debug.h"
#include "ch32v20x_usbotg_device.h"
#include "iap.h"
#include "usb_istr.h"
#include "usb_desc.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    if (PA0_Check() == 0) {

         printf("jump APP\r\n");

         NVIC_EnableIRQ(Software_IRQn);

         NVIC_SetPendingIRQ(Software_IRQn);

         while(1);
     }
    Set_USBConfig();
    USB_Init();
    USB_Port_Set(DISABLE, DISABLE);
    Delay_Ms(700);
    USB_Port_Set(ENABLE, ENABLE);
    USB_Interrupts_Config();

	USBOTG_Init( );
	USART1_CFG(57600);
    while(1)
    {
        EP2_RecData_Deal();
        if( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET){
            UART_Rx_Deal();
        }
        EP2_RecData_Deal();
    }
}
