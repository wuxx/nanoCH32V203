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

/* Private variables */
uint8_t  USB_Rx_Buffer_1[USBD_DATA_SIZE];
uint8_t  USB_Rx_Buffer_2[USBD_DATA_SIZE];
uint16_t USB_Rx_Cnt_1 = 0;
uint16_t USB_Rx_Cnt_2 = 0;

/*******************************************************************************
 * @fn        EP1_IN_Callback
 *
 * @brief     Endpoint 1 IN.
 *
 * @param     None.
 *
 * @return    None.
 */
void EP1_IN_Callback (void)
{
    UserToPMABufferCopy(USB_Rx_Buffer_1, ENDP1_TXADDR, USB_Rx_Cnt_1);
    SetEPTxCount(ENDP1, USB_Rx_Cnt_1);
    SetEPTxValid(ENDP1);
}

/*******************************************************************************
 * @fn        EP1_OUT_Callback
 *
 * @brief     Endpoint 1 IN.
 *
 * @return    None.
 */
void EP1_OUT_Callback(void)
{
    uint8_t i;

    USB_Rx_Cnt_1 = USB_SIL_Read(EP1_OUT, USB_Rx_Buffer_1);

    for(i=0;i<USB_Rx_Cnt_1;i++)
    {
        USB_Rx_Buffer_1[i] = ~USB_Rx_Buffer_1[i];
    }

    EP1_IN_Callback( );
    SetEPRxValid(ENDP1);
}

/*******************************************************************************
 * @fn        EP2_IN_Callback
 *
 * @brief     Endpoint 2 IN.
 *
 * @param     None.
 *
 * @return    None.
 */
void EP2_IN_Callback (void)
{ 
	UserToPMABufferCopy(USB_Rx_Buffer_2, ENDP2_TXADDR, USB_Rx_Cnt_2);
	SetEPTxCount(ENDP2, USB_Rx_Cnt_2);
	SetEPTxValid(ENDP2);   
}

/*******************************************************************************
 * @fn        EP2_OUT_Callback
 *
 * @brief     Endpoint 2 IN.
 *
 * @return    None.
 */
void EP2_OUT_Callback(void)
{
	uint8_t i; 
	
	USB_Rx_Cnt_2 = USB_SIL_Read(EP2_OUT, USB_Rx_Buffer_2);
	
    for(i=0;i<USB_Rx_Cnt_2;i++)
	{
        USB_Rx_Buffer_2[i] = ~USB_Rx_Buffer_2[i];
	}
	
    EP2_IN_Callback( );
	SetEPRxValid(ENDP2);													
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






