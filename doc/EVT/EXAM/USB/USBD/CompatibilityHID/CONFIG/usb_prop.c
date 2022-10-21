/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_prop.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : All processing related to Virtual Com Port Demo
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"

uint8_t Request = 0;

extern uint8_t HIDTxBuffer[],HIDRxBuffer[];
extern uint8_t Endp2Busy;
uint8_t HIDReportOut[8] = {0};

bool WakeUpEnFlag = FALSE;    /* Remote wake up flag */

DEVICE Device_Table =
{
	EP_NUM,
	1
};

DEVICE_PROP Device_Property =
{
	USBD_init,
	USBD_Reset,
	USBD_Status_In,
	USBD_Status_Out,
	USBD_Data_Setup,
	USBD_NoData_Setup,
	USBD_Get_Interface_Setting,
	USBD_GetDeviceDescriptor,
	USBD_GetConfigDescriptor,
	USBD_GetStringDescriptor,
	0,
	THIS_ENDP0_SIZE                                 
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
	USBD_GetConfiguration,
	USBD_SetConfiguration,
	USBD_GetInterface,
	USBD_SetInterface,
	USBD_GetStatus, 
	USBD_ClearFeature,
	USBD_SetEndPointFeature,
	USBD_SetDeviceFeature,
	USBD_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
	(uint8_t*)USBD_DeviceDescriptor,
	USBD_SIZE_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
	(uint8_t*)USBD_ConfigDescriptor,
	USBD_SIZE_CONFIG_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
	{(uint8_t*)USBD_StringLangID, USBD_SIZE_STRING_LANGID},
	{(uint8_t*)USBD_StringVendor, USBD_SIZE_STRING_VENDOR},
	{(uint8_t*)USBD_StringProduct,USBD_SIZE_STRING_PRODUCT},
	{(uint8_t*)USBD_StringSerial, USBD_SIZE_STRING_SERIAL}
};

ONE_DESCRIPTOR Report_Descriptor[1] =
{
	{(uint8_t*)USBD_HIDRepDesc, USBD_SIZE_HID_DESC},
};

/*******************************************************************************
 * @fn        USBD_SetConfiguration.
 *
 * @brief     Update the device state to configured.
 *
 * @return    None.
 */
void USBD_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    bDeviceState = CONFIGURED;
  }
}

/*******************************************************************************
 * @fn         USBD_SetDeviceAddress.
 *
 * @brief      Update the device state to addressed.
 *
 * @return     None.
 */
void USBD_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}


/*********************************************************************
 * @fn      USBD_SetDeviceFeature.
 *
 * @brief   SetDeviceFeature Routine.
 *
 * @return  none
 */
void USBD_SetDeviceFeature (void)
{

}



/*********************************************************************
 * @fn      USBD_ClearFeature.
 *
 * @brief   ClearFeature Routine.
 *
 * @return  none
 */
void USBD_ClearFeature(void)
{

}





/*********************************************************************
 * @fn      USBD_Status_In.
 *
 * @brief    USBD Status In Routine.
 *
 * @return   None.
 */
void USBD_Status_In(void)
{
 
}

/*******************************************************************************
 * @fn       USBD_Status_Out
 *
 * @brief    USBD Status OUT Routine.
 *
 * @return   None.
 */
void USBD_Status_Out(void)
{
    
}

/*******************************************************************************
 * @fn       USB_init.
 *
 * @brief    init routine.
 * 
 * @return   None.
 */
void USBD_init(void)
{
  uint8_t	i;
    
  pInformation->Current_Configuration = 0;
  PowerOn();
  for (i=0;i<8;i++) _SetENDPOINT(i,_GetENDPOINT(i) & 0x7F7F & EPREG_MASK);//all clear
  _SetISTR((uint16_t)0x00FF);//all clear
  USB_SIL_Init();
  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
 * @fn      USBD_Reset
 *
 * @brief   Virtual_Com_Port Mouse reset routine
 *
 * @return  None.
 */
void USBD_Reset(void)
{
  pInformation->Current_Configuration = 0;
  pInformation->Current_Feature = USBD_ConfigDescriptor[7];
  pInformation->Current_Interface = 0;

  SetBTABLE(BTABLE_ADDRESS);

  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_STALL);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);
  _ClearDTOG_RX(ENDP0);
  _ClearDTOG_TX(ENDP0);

    SetEPType(ENDP2, EP_INTERRUPT);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxAddr(ENDP2, ENDP2_RXADDR);   
    SetEPRxCount(ENDP2, ENDP2_IN_SIZE);
    SetEPRxStatus(ENDP2, EP_RX_VALID);
    SetEPTxStatus(ENDP2, EP_TX_NAK);
    _ClearDTOG_RX(ENDP2);
    _ClearDTOG_TX(ENDP2);

    SetDeviceAddress(0);

    bDeviceState = ATTACHED;
}

/*******************************************************************************
 * @fn      USBD_GetDeviceDescriptor.
 *
 * @brief   Gets the device descriptor.
 *
 * @param   Length.
 *
 * @return  The address of the device descriptor.
 */
uint8_t *USBD_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
 * @fn       USBD_GetConfigDescriptor.
 *
 * @brief    get the configuration descriptor.
 *
 * @param    Length.
 *
 * @return   The address of the configuration descriptor.
 */
uint8_t *USBD_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
 * @fn        USBD_GetStringDescriptor
 *
 * @brief     Gets the string descriptors according to the needed index
 *
 * @param     Length.
 *
 * @return    The address of the string descriptors.
 */
uint8_t *USBD_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
	
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}

/*********************************************************************
 * @fn      USBD_GetReportDescriptor
 *
 * @brief   Gets the report descriptors according to the needed index
 *
 * @param   Length.
 *
 * @return  The address of the device descriptor.
 */
uint8_t *USBD_GetReportDescriptor(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
  if (wIndex0 > 1)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &Report_Descriptor[wIndex0]);
  }
}

/*********************************************************************
 * @fn      USBD_Get_Interface_Setting.
 *
 * @brief  test the interface and the alternate setting according to the
 *                  supported one.
 *
 * @param  Interface: interface number.
 *                  AlternateSetting: Alternate Setting number.
 *
 * @return USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 1)
  {
    return USB_UNSUPPORT;
  }
	
  return USB_SUCCESS;
}

/*******************************************************************************
 * @fn       USBD_Data_Setup
 *
 * @brief    handle the data class specific requests
 *
 * @param    Request Nb.
 *
 * @return   USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  uint32_t Request_No = pInformation->USBbRequest;
  uint32_t wOffset;
  CopyRoutine = NULL;
  wOffset = 0;


  if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    uint8_t wValue1 = pInformation->USBwValue1;

    if (wValue1 == HID_REPORT_DESCRIPTOR)
    {
      Endp2Busy = FALSE;
      CopyRoutine = USBD_GetReportDescriptor;
      
    }
    if (CopyRoutine)
    {
      pInformation->Ctrl_Info.Usb_wOffset = wOffset;
      pInformation->Ctrl_Info.CopyData = CopyRoutine;
      (*CopyRoutine)(0);
    }
    else
    {
      return USB_UNSUPPORT;
    }

  }
  else if (Request_No == HID_SET_REPORT && (pInformation->USBbmRequestType & REQUEST_TYPE) == CLASS_REQUEST )
  {
    if (Request_No == HID_GET_REPORT)
    {
      
    }
    else if (Request_No == HID_GET_IDLE)
    {

    }
    else if (Request_No == HID_GET_PROTOCOL)
    {

    }  
    else if (Request_No == HID_SET_REPORT)
    {

      pInformation->Ctrl_Info.Usb_wLength = pInformation->USBwLengths.w;
      pInformation->Ctrl_Info.CopyData = HID_SaveReportOut;
      pInformation->ControlState = LAST_OUT_DATA;
    }
    else if (Request_No == HID_SET_IDLE)
    {

    }
    else if (Request_No == HID_SET_PROTOCOL)
    {

    }
    else
    {

    }    
  }
  return USB_SUCCESS;
}

/*******************************************************************************
 * @fn      USBD_NoData_Setup.
 *
 * @brief   handle the no data class specific requests.
 *
 * @param   Request Nb.
 *
 * @return  USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_NoData_Setup(uint8_t RequestNo)
{      
  uint32_t Request_No = pInformation->USBbRequest;
  if (Request_No == HID_GET_REPORT)
  {

  }
  else if (Request_No == HID_GET_IDLE)
  {

  }
  else if (Request_No == HID_GET_PROTOCOL)
  {

  }  
  else if (Request_No == HID_SET_REPORT)
  {

  }
  else if (Request_No == HID_SET_IDLE)
  {

  }
  else if (Request_No == HID_SET_PROTOCOL)
  {

  }
  else
  {

  }                                
  return USB_SUCCESS;
}

/*********************************************************************
 * @fn      USBD_HID_Data_Updata.
 *
 * @brief   HID Data Updata
 *
 * @param   
 *
 * @return  none
 */
__attribute__((optimize("O0"))) void USBD_HID_Data_Updata(void)
{
  while (Endp2Busy);
  UserToPMABufferCopy(HIDTxBuffer, ENDP2_TXADDR, ENDP2_IN_SIZE);
  SetEPTxCount(ENDP2, ENDP2_IN_SIZE);
  SetEPTxValid(ENDP2);
  Endp2Busy = TRUE;
}


/*********************************************************************
 * @fn      HID_SaveReportOut
 *
 * @brief   HID Save Report
 *
 * @param   
 *
 * @return  none
 */
uint8_t *HID_SaveReportOut(uint16_t Length)
{
  return &HIDReportOut[0];
}






