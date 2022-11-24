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
 *Example routine to emulate a simulate USB-CDC Device, USE USART1(PA9/PA10)
 *Recommended to use UART2(PA2) as debug port, you can modify the debug port
 *by modifying the macro definition in debug.h
 *Merged HID devices, using endpoint 4 data downlink to fetch reverse upload;
*/

#include "UART.h"
#include "debug.h"
#include "usb_lib.h"


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
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("USBD SimulateCDC-HID Demo\r\n");
    
    RCC_Configuration( );
    TIM2_Init( );
    UART1_Init( 1, DEF_UARTx_BAUDRATE, DEF_UARTx_STOPBIT, DEF_UARTx_PARITY );
    
	Set_USBConfig(); 
    USB_Init();	    
 	USB_Interrupts_Config();    
 	
	while(1)
	{
        UART1_DataRx_Deal( );
        UART1_DataTx_Deal( );
	}
}







