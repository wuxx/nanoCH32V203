/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 

/*
 *@Note
 模拟HID兼容设备，支持中断上下传，支持控制端点上下传，支持全速传输。
     - PA0低电平发送HIDTxBuffer中的数据。
     - OUT数据保存到HIDRxBuffer中并打印输出。
 注：本例程需与上位机软件配合演示。

*/

#include "debug.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_prop.h"
/* Global define */


/* Global Variable */    
extern uint8_t HIDTxBuffer[],HIDRxBuffer[];

/*********************************************************************
 * @fn      GPIO_Key_Init
 *
 * @brief   GPIO Key Init : PA0
 *
 * @return  none
 */
void GPIO_Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{   
    uint8_t i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init(); 
    USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBD CompatibilityHID Demo\r\n");
	GPIO_Key_Init();
	Set_USBConfig(); 
    USB_Init();	    
	USB_Port_Set(DISABLE, DISABLE);	
	Delay_Ms(700);
	USB_Port_Set(ENABLE, ENABLE);
 	USB_Interrupts_Config();    
 	
    for(i = 0;i< ENDP2_IN_SIZE;i++) HIDTxBuffer[i] = i;
    
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
            USBD_HID_Data_Updata();
		}
        Delay_Ms(100);
	}
}







