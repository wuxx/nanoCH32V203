/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_endp.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : Endpoint routines
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define IN_FRAME_INTERVAL             5


uint8_t HIDKey[ENDP1_IN_SIZE] = {0};
uint8_t HIDMouse[ENDP2_IN_SIZE] = {0};

volatile u8 Endp1Busy,Endp2Busy;
u16 USB_Rx_Cnt=0; 


/*******************************************************************************
 * @fn        EP2_IN_Callback
 *
 * @brief     Endpoint 2 IN.
 *
 * @param     None.
 *
 * @return    None.
 */
void EP1_IN_Callback (void)
{ 
	Endp1Busy = FALSE;
}

/*******************************************************************************
 * @fn        EP2_OUT_Callback
 *
 * @brief     Endpoint 2 IN.
 *
 * @return    None.
 */
void EP1_OUT_Callback(void)
{
											
}


/*********************************************************************
 * @fn      EP2_IN_Callback
 *
 * @brief  Endpoint 2 IN.
 *
 * @return  none
 */
void EP2_IN_Callback (void)
{ 
	Endp2Busy = FALSE;
}

/*********************************************************************
 * @fn      EP2_OUT_Callback
 *
 * @brief  Endpoint 2 IN.
 *
 * @return  none
 */
void EP2_OUT_Callback(void)
{
													
}

/*******************************************************************************
 * @fn       SOF_Callback
 *
 * @brief    SOF call back.
 *
 * @return   None.
 */
void SOF_Callback(void)
{
	static uint32_t FrameCount = 0;

	if(bDeviceState == CONFIGURED)
	{
		if (FrameCount++ == IN_FRAME_INTERVAL)
		{		
			FrameCount = 0;
			//Handle_USBAsynchXfer();
		}
	}  
}






