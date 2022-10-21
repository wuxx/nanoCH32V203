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
 模拟键鼠例程：
 USBDM(PA11)、USBDP(PA12)。
 本例程演示使用 USBD 模拟键鼠设备，演示了基本的键鼠的按键上传操作。
 串口1接收'A'  ，键盘上传按键A
 串口1接收'Q'  ，键盘上传按键Caplock
 串口1接收'L'  ，鼠标上传鼠标左键
 串口1接收'R'  ，鼠标上传鼠标右键
*/

#include "debug.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_prop.h"
/* Global define */


/* Global Variable */    
extern uint8_t HIDKey[],HIDMouse[];


/*********************************************************************
 * @fn      USART1_Init
 *
 * @brief   USART1 Init.
 *
 * @return  none
 */
void USART1_Init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;
    
	/* USART1 GPIO Init */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 Init */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);  	
	USART_ClearFlag(USART1,USART_IT_RXNE);
}



/*********************************************************************
 * @fn      HIDValueHandle
 *
 * @brief   HID Value Handle Function.
 *
 * @return  none
 */
void HIDValueHandle()
{
	uint8_t value;
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE) != RESET )
	{
		if (WakeUpEnFlag)
		{
			Resume(RESUME_INTERNAL);
		}
		
		value = (uint8_t)USART_ReceiveData(USART1);
		USART_ClearFlag(USART1,USART_IT_RXNE);
		printf( "data:%c\n", (uint8_t)value );
		switch (value)
		{
		case 'L':   								/* Mouse：left button*/
			printf("Mouse:left button\n");
			HIDMouse[0] = 0x01;
			USBD_HID_Mouse_Updata();
			HIDMouse[0] = 0x00;
			USBD_HID_Mouse_Updata();			
			break; 
		case 'R':   								/* Mouse：right button*/
			printf("Mouse:right button\n");
			HIDMouse[0] = 0x02;
			USBD_HID_Mouse_Updata();
			HIDMouse[0] = 0x00;
			USBD_HID_Mouse_Updata();	
			break;
		case 'A':   								/* Keyboard：A*/
			printf("Keyboard:A\n");
			HIDKey[2] = 0x04;
			USBD_HID_Keyboard_Updata();
			HIDKey[2] = 0x00;
			USBD_HID_Keyboard_Updata();	
			break;
		case 'Q':   								/* Keyboard：CAP */
			printf("Keyboard:CAP\n");
			HIDKey[2] = 0x39;
			USBD_HID_Keyboard_Updata();
			HIDKey[2] = 0x00;
			USBD_HID_Keyboard_Updata();	
			break;
		default:
			break;
		}
	}
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init(); 
	USART1_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBD Keyboard&Mouse Demo\r\n");
	Set_USBConfig(); 
    USB_Init();	    
	USB_Port_Set(DISABLE, DISABLE);	
	Delay_Ms(700);
	USB_Port_Set(ENABLE, ENABLE);
 	USB_Interrupts_Config();    
 	
	while(1)
	{
		HIDValueHandle();
	}
}
