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
   模拟自定义USB设备（CH372设备）例程：
 USBDM(PA11)、USBDP(PA12)。
   本例程演示使用 USBD 模拟自定义设备 CH372，和上位机通信，默认端点1/2批量，下传一包取反上传。
   注：本例程需与上位机软件配合演示。

*/

#include "debug.h"


#include "debug.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

/* Global define */


/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 usbstatus=0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    printf("USBD Device Test\r\n");

    Set_USBConfig();
    USB_Init();

    USB_Port_Set(DISABLE, DISABLE);
    Delay_Ms(700);
    USB_Port_Set(ENABLE, ENABLE);
    USB_Interrupts_Config();


    while(1)
    {
        if(usbstatus!=bDeviceState)
        {
            usbstatus=bDeviceState;

            if(usbstatus==CONFIGURED)
            {
                printf("USB Connected\r\n");
            }
            else
            {
                printf("USB disConnected\r\n");
            }
        }
    }
}
