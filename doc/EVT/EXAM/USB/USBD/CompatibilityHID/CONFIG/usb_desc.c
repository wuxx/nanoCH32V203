/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : Descriptors for Virtual Com Port Demo.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 
#include "usb_lib.h"
#include "usb_desc.h"

/* USB Device Descriptors */
const uint8_t  USBD_DeviceDescriptor[] = { 
	0x12,0x01,0x00,0x01,0x00,0x00,0x00,THIS_ENDP0_SIZE,
    0x86,0x1A,0xE1,0xE1,0x00,0x00,0x01,0x02,
    0x00,0x01   
};

/* USB Configration Descriptors */
const uint8_t  USBD_ConfigDescriptor[] = { 
    
    0x09,0x02,0x29,0x00,0x01,0x01,0x04,0x80,0x23,               /* Configration Descriptor */
    0x09,0x04,0x00,0x00,0x02,0x03,0x00,0x00,0x05,               /* Interface Descriptor */
    0x09,0x21,0x00,0x01,0x00,0x01,0x22,0x22,0x00,               /* HID Class Descriptor */
    0x07,0x05,0x82,0x03,ENDP2_IN_SIZE,0x00,0x01,                /* Endpoint Descriptor */
    0x07,0x05,0x02,0x03,ENDP2_OUT_SIZE,0x00,0x01,               /* Endpoint Descriptor */
    
};

/* USB String Descriptors */
const uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID] = {
	USBD_SIZE_STRING_LANGID,
	USB_STRING_DESCRIPTOR_TYPE,
	0x09,
	0x04 
};

/* USB Device String Vendor */
const uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR] = {
	USBD_SIZE_STRING_VENDOR,    
	USB_STRING_DESCRIPTOR_TYPE,           
	'W', 0, 'C', 0, 'H', 0, 
};

/* USB Device String Product */
const uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT] = {
	USBD_SIZE_STRING_PRODUCT,         
	USB_STRING_DESCRIPTOR_TYPE,        
	'C', 0, 'H', 0, '3', 0, '2', 0, ' ', 0, 'C', 0, 'o', 0,
	'm', 0, 'p', 0, 'a', 0, 't', 0, 'i', 0, 'b', 0, 'i', 0, 'l', 0,
	'i', 0, 't', 0, 'y', 0, 'H', 0, 'I', 0, 'D', 0,


};

/* USB Device String Serial */
uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL] = {
	USBD_SIZE_STRING_SERIAL,          
	USB_STRING_DESCRIPTOR_TYPE,                   
	'W', 0, 'C', 0, 'H', 0, '3', 0, '2', 0
};

/* HID Report Descriptor */
const uint8_t USBD_HIDRepDesc[] =
{
    0x06, 0x00,0xff,
    0x09, 0x01,
    0xa1, 0x01,                                                   
    0x09, 0x02,                                                   /* Usage Page */
    0x15, 0x00,                                                   /* Logical  Minimun */
    0x26, 0x00,0xff,                                              /* Logical  Maximun */
    0x75, 0x08,                                                   /* Report Size */
    0x95, 0x40,                                                   /* Report Counet */
    0x81, 0x06,                                                   /* Input */
    0x09, 0x02,                                                   /* Usage Page */
    0x15, 0x00,                                                   /* Logical  Minimun */
    0x26, 0x00,0xff,                                              /* Logical  Maximun */
    0x75, 0x08,                                                   /* Report Size */
    0x95, 0x40,                                                   /* Report Counet */
    0x91, 0x06,                                                   /* Output */
    0xC0
};





