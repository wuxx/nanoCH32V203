/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_usbotg_host.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : USBOTG full speed host operation function.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "ch32vf20x_usbotg_host.h"
#include "Desc_Analysis.h"

__attribute__ ((aligned(4))) const UINT8  SetupGetDevDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_DEVICE, 0x00, 0x00, sizeof( USB_DEV_DESCR ), 0x00 };
__attribute__ ((aligned(4))) const UINT8  SetupGetCfgDescr[] = { USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_CONFIG, 0x00, 0x00, 0x04, 0x00 };
__attribute__ ((aligned(4))) const UINT8  SetupSetUsbAddr[] = { USB_REQ_TYP_OUT, USB_SET_ADDRESS, USB_DEVICE_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__ ((aligned(4))) const UINT8  SetupSetUsbConfig[] = { USB_REQ_TYP_OUT, USB_SET_CONFIGURATION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__ ((aligned(4))) const UINT8  SetupSetUsbInterface[] = { USB_REQ_RECIP_INTERF, USB_SET_INTERFACE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__ ((aligned(4))) const UINT8  SetupClrEndpStall[] = { USB_REQ_TYP_OUT | USB_REQ_RECIP_ENDP, USB_CLEAR_FEATURE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__ ((aligned(4))) const UINT8  HIDSetReport[] = { USB_REQ_TYP_CLASS | USB_REQ_RECIP_INTERF, HID_SET_REPORT, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00 };
__attribute__ ((aligned(4))) const UINT8  HIDGetReport[] = { USB_REQ_TYP_CLASS | USB_REQ_RECIP_INTERF, HID_GET_REPORT, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00 };

__attribute__ ((aligned(16))) UINT8 endpRXbuff[64+64];
__attribute__ ((aligned(16))) UINT8 endpTXbuff[64+64];

#define pSetupReq    ((PUSB_SETUP_REQ)endpTXbuff)

UINT8 UsbDevEndp0Size=0;
PUSBHS_HOST pOTGHost;
UINT8 FoundNewDev=0;
UINT8 DeviceDescriptor[ 18 ];
UINT8 ConfigDescriptor[ 512 ];

/*********************************************************************
 * @fn      USBOTG_RCC_Init
 *
 * @brief   Initializes the usbotg clock configuration.
 *
 * @return  none
 */
void OTG_RCC_Init(void)
{
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div3);
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_OTG_FS, ENABLE );
}
/*********************************************************************
 * @fn      USBOTG_HostInit
 *
 * @brief   USB OTG host mode  initialized.
 *
 * @param   stus - ENABLE or DISABLE
 *
 * @return  none
 */
void USBOTG_HostInit(FunctionalState stus)
{
    if(stus==ENABLE)
    {
        OTG_RCC_Init();
        USBOTG_FS->BASE_CTRL=USBHD_UC_HOST_MODE;                  //host mode
        USBHD_UHOST_CTRL=0;
        USBOTG_FS->DEV_ADDR=0;
        USBHD_UH_EP_MOD=USBHD_UH_EP_TX_EN|USBHD_UH_EP_RX_EN;      //host tx&rx enable

        USBHD_UH_RX_DMA= (UINT32)&endpRXbuff[0];                  //host rx DMA address
        USBHD_UH_TX_DMA = (UINT32)&endpTXbuff[0];                 //host tx DMA address

        USBHD_UH_RX_CTRL=0;
        USBHD_UH_TX_CTRL=0;
        USBOTG_FS->BASE_CTRL=USBHD_UC_HOST_MODE|USBHD_UC_INT_BUSY|USBHD_UC_DMA_EN;

        USBOTG_FS->INT_FG=0xff;

        DisableRootHubPort();
        USBOTG_FS->INT_EN=USBHD_UIE_TRANSFER|USBHD_UIE_DETECT;
        FoundNewDev = 0;
    }

}

/*********************************************************************
 * @fn      DisableRootHubPort
 *
 * @brief   disable root hub.
 *
 * @return  none
 */
void DisableRootHubPort(void)
{
#ifdef  FOR_ROOT_UDISK_ONLY
    CH103DiskStatus = DISK_DISCONNECT;

#endif

#ifndef DISK_BASE_BUF_LEN
    pOTGHost->DeviceStatus = ROOT_DEV_DISCONNECT;
    pOTGHost->DeviceAddress = 0x00;
#endif
}


/*********************************************************************
 * @fn      AnalyzeRootHub
 *
 * @brief   Analyze root hub state.
 *
 * @return  s - Error state
 */
UINT8 AnalyzeRootHub(void)
{
    UINT8   s;

    s = ERR_SUCCESS;

    if ( USBOTG_FS->MIS_ST & USBHD_UMS_DEV_ATTACH ) {

#ifdef DISK_BASE_BUF_LEN
        if ( CH103DiskStatus == DISK_DISCONNECT

#else
        if ( pOTGHost->DeviceStatus == ROOT_DEV_DISCONNECT

#endif
                || ( USBHD_UHOST_CTRL & USBHD_UH_PORT_EN ) == 0x00 ) {
                DisableRootHubPort( );

#ifdef DISK_BASE_BUF_LEN
                CH103DiskStatus = DISK_CONNECT;

#else
        pOTGHost->DeviceSpeed = USBOTG_FS->MIS_ST & USBHD_UMS_DM_LEVEL ? 0 : 1;
        pOTGHost->DeviceStatus = ROOT_DEV_CONNECTED;

#endif
        s = ERR_USB_CONNECT;
     }
  }

#ifdef DISK_BASE_BUF_LEN
  else if ( CH103DiskStatus >= DISK_CONNECT ) {

#else
  else if ( pOTGHost->DeviceStatus >= ROOT_DEV_CONNECTED ) {

#endif
        DisableRootHubPort( );
        if ( s == ERR_SUCCESS ) s = ERR_USB_DISCON;
  }

    return( s );
}
/*********************************************************************
 * @fn      SetHostUsbAddr
 *
 * @brief   Set USB host address.
 *
 * @param   addr - set device address
 *
 * @return  none
 */
void SetHostUsbAddr( UINT8 addr )
{
    USBOTG_FS->DEV_ADDR = (USBOTG_FS->DEV_ADDR&USBHD_UDA_GP_BIT) | (addr&USBHD_USB_ADDR_MASK);
}

#ifndef FOR_ROOT_UDISK_ONLY
/*********************************************************************
 * @fn      SetUsbSpeed
 *
 * @brief   Set USB speed.
 *
 * @param   FullSpeed - USB speed.
 *
 * @return  none
 */
void SetUsbSpeed( UINT8 FullSpeed )
{
    if ( FullSpeed )
    {
        USBOTG_FS->BASE_CTRL &= ~ USBHD_UC_LOW_SPEED;
        USBHD_UH_SETUP &= ~ USBHD_UH_PRE_PID_EN;
    }
    else
    {
        USBOTG_FS->BASE_CTRL |= USBHD_UC_LOW_SPEED;
    }
}
#endif

/*********************************************************************
 * @fn      ResetRootHubPort
 *
 * @brief   Reset root hub.
 *
 * @return  none
 */
void ResetRootHubPort( void )
{
    UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;
    SetHostUsbAddr( 0x00 );
    USBHD_UHOST_CTRL &= ~USBHD_UH_PORT_EN;
    SetUsbSpeed( 1 );
    USBHD_UHOST_CTRL = (USBHD_UHOST_CTRL & ~USBHD_UH_LOW_SPEED) | USBHD_UH_BUS_RESET;
    Delay_Ms( 50 );
    USBHD_UHOST_CTRL = USBHD_UHOST_CTRL & ~ USBHD_UH_BUS_RESET;
    Delay_Us( 250 );
    USBOTG_FS->INT_FG = USBHD_UIF_DETECT;
}

/*********************************************************************
 * @fn      EnableRootHubPort
 *
 * @brief   Enable root hub.
 *
 * @return  Error state
 */
UINT8 EnableRootHubPort(void)
{
#ifdef DISK_BASE_BUF_LEN
  if ( CH103DiskStatus < DISK_CONNECT ) CH103DiskStatus = DISK_CONNECT;

#else
  if ( pOTGHost->DeviceStatus < ROOT_DEV_CONNECTED ) pOTGHost->DeviceStatus = ROOT_DEV_CONNECTED;

#endif
  if ( USBOTG_FS->MIS_ST & USBHD_UMS_DEV_ATTACH ) {
#ifndef DISK_BASE_BUF_LEN
    if ( ( USBHD_UHOST_CTRL & USBHD_UH_PORT_EN ) == 0x00 ) {
           pOTGHost->DeviceSpeed = (USBOTG_FS->MIS_ST & USBHD_UMS_DM_LEVEL) ? 0 : 1;
            if ( pOTGHost->DeviceSpeed == 0 ) USBHD_UHOST_CTRL |= USBHD_UD_LOW_SPEED;
    }
#endif
    USBHD_UHOST_CTRL |= USBHD_UD_PORT_EN;
    USBHD_UH_SETUP|=USBHD_UH_SOF_EN;
    return( ERR_SUCCESS );
  }

  return( ERR_USB_DISCON );
}

/*********************************************************************
 * @fn      WaitUSB_Interrupt
 *
 * @brief   Wait USB Interrput.
 *
 * @return  Error state
 */
UINT8 WaitUSB_Interrupt( void )
{
    UINT16  i;

    for ( i = 30000; i != 0 && ((USBOTG_FS->INT_FG) & USBHD_UIF_TRANSFER) == 0; i -- ){;}
    return( ((USBOTG_FS->INT_FG)&USBHD_UIF_TRANSFER)  ? ERR_SUCCESS : ERR_USB_UNKNOWN );
}

/*********************************************************************
 * @fn      USBHostTransact
 *
 * @brief   USB host transport transaction.
 *
 * @param   endp_pid - endpoint(bit3:bit0) and PID(bit7:bit4).
 *          tog - bit3-data auto toggle. bit2-data toggle. bit0-synchronous transmission.
 *          timeout - timeout times.
 *
 * @return  Error state
 */
UINT8 USBHostTransact( UINT8 endp_pid, UINT8 tog, UINT32 timeout )
{
    UINT8   TransRetry;
    UINT8   s, r;
    UINT32  i;

    USBHD_UH_TX_CTRL = USBHD_UH_RX_CTRL = tog;
    TransRetry = 0;

    do {
        USBHD_UH_EP_PID = endp_pid;
        USBOTG_FS->INT_FG = USBHD_UIF_TRANSFER;
        for ( i = WAIT_USB_TOUT_200US; i != 0 && ((USBOTG_FS->INT_FG) & USBHD_UIF_TRANSFER) == 0 ; i -- )//
        {
            Delay_Us( 1 );
        }

        USBHD_UH_EP_PID = 0x00;
        if ( (USBOTG_FS->INT_FG & USBHD_UIF_TRANSFER) == 0 )
        {
            return( ERR_USB_UNKNOWN );
        }

        if (  USBOTG_FS->INT_FG & USBHD_UIF_DETECT ) {
            USBOTG_FS->INT_FG = USBHD_UIF_DETECT;
            s = AnalyzeRootHub( );

            if ( s == ERR_USB_CONNECT )             FoundNewDev = 1;

#ifdef DISK_BASE_BUF_LEN

            if ( CH103DiskStatus == DISK_DISCONNECT ) return( ERR_USB_DISCON );
            if ( CH103DiskStatus == DISK_CONNECT ) return( ERR_USB_CONNECT );

#else
            if ( pOTGHost->DeviceStatus == ROOT_DEV_DISCONNECT ) return( ERR_USB_DISCON );
            if ( pOTGHost->DeviceStatus == ROOT_DEV_CONNECTED ) return( ERR_USB_CONNECT );

#endif
            Delay_Us( 200 );
        }

        if ( USBOTG_FS->INT_FG & USBHD_UIF_TRANSFER )
        {
            if ( USBOTG_FS->INT_ST & USBHD_UIS_TOG_OK ) return( ERR_SUCCESS );
            r = USBOTG_FS->INT_ST & MASK_UIS_H_RES;
            if ( r == USB_PID_STALL ) return( r | ERR_USB_TRANSFER );    //2e

            if ( r == USB_PID_NAK )
            {
                if ( timeout == 0 ) return( r | ERR_USB_TRANSFER );     //2a
                if ( timeout < 0xFFFF ) timeout --;
                -- TransRetry;
            }
            else switch ( endp_pid >> 4 ) {
                case USB_PID_SETUP:

                case USB_PID_OUT:
                    if ( r ) return( r | ERR_USB_TRANSFER );          //21
                    break;

                case USB_PID_IN:                           //2b
                    if ( (r == USB_PID_DATA0) && (r == USB_PID_DATA1) ) {
                    }
                    else if ( r ) return( r | ERR_USB_TRANSFER );
                    break;
                default:
                    return( ERR_USB_UNKNOWN );
            }
        }
        else {
            USBOTG_FS->INT_FG = 0xFF;
        }
        Delay_Us( 15 );
    } while ( ++ TransRetry < 3 );

    return( ERR_USB_TRANSFER );
}

/*********************************************************************
 * @fn      HostCtrlTransfer
 *
 * @brief   Host control transport.
 *
 * @param   DataBuf - Receive or send data buffer.
 *          RetLen - Data length.
 *
 * @return  Error state
 */
UINT8 HostCtrlTransfer( PUINT8 DataBuf, PUINT8 RetLen )
{
    UINT16  RemLen  = 0;
    UINT8   s, RxLen;
    PUINT8  pBuf;
    PUINT8   pLen;

    pBuf = DataBuf;
    pLen = RetLen;
    Delay_Us( 200 );
    if ( pLen ) *pLen = 0;

    USBHD_UH_TX_LEN = sizeof( USB_SETUP_REQ );
    s = USBHostTransact( USB_PID_SETUP << 4 | 0x00, 0x00, 200000 );
    if ( s != ERR_SUCCESS )
    {
         return( s );
    }
    USBHD_UH_RX_CTRL = USBHD_UH_TX_CTRL = USBHD_UH_R_TOG | USBHD_UH_R_AUTO_TOG | USBHD_UH_T_TOG | USBHD_UH_T_AUTO_TOG;
    USBHD_UH_TX_LEN = 0x01;
    RemLen = pSetupReq -> wLength;

    if ( RemLen && pBuf )
    {
        if ( pSetupReq -> bRequestType & USB_REQ_TYP_IN )
        {
            while ( RemLen )
            {
                Delay_Us( 200 );
                USBHD_UH_RX_DMA=(UINT32)pBuf+*pLen;
                s = USBHostTransact( USB_PID_IN << 4 | 0x00, USBHD_UH_RX_CTRL, 200000/20 );
                if ( s != ERR_SUCCESS )         return( s );
                RxLen = USBOTG_FS->RX_LEN < RemLen ? USBOTG_FS->RX_LEN : RemLen;
                RemLen -= RxLen;
                if ( pLen ) *pLen += RxLen;

//                for ( RxCnt = 0; RxCnt != RxLen; RxCnt ++ )
//                {
//                    *pBuf = pHOST_RX_RAM_Addr[ RxCnt ];
//                    pBuf ++;
//                }

                if ( USBOTG_FS->RX_LEN == 0 || ( USBOTG_FS->RX_LEN & ( UsbDevEndp0Size - 1 ) ) ) break;
            }
            USBHD_UH_TX_LEN = 0x00;
        }
        else
        {
            while ( RemLen )
            {
                Delay_Us( 200 );
                USBHD_UH_TX_DMA = (UINT32)pBuf + *pLen;
                R8_UH_TX_LEN = RemLen >= UsbDevEndp0Size ? UsbDevEndp0Size : RemLen;
//                for ( TxCnt = 0; TxCnt != R8_UH_TX_LEN; TxCnt ++ )
//                {
//                    pHOST_TX_RAM_Addr[ TxCnt ] = *pBuf;
//                    pBuf ++;
//                }

                s = USBHostTransact( USB_PID_OUT << 4 | 0x00, R8_UH_TX_CTRL, 200000/20 );
                if ( s != ERR_SUCCESS ) return( s );
                RemLen -= USBHD_UH_TX_LEN;
                if ( pLen ) *pLen += USBHD_UH_TX_LEN;
            }
        }
    }

    Delay_Us( 200 );
    s = USBHostTransact( ( USBHD_UH_TX_LEN ? USB_PID_IN << 4 | 0x00: USB_PID_OUT << 4 | 0x00 ), USBHD_UH_T_TOG | USBHD_UH_R_TOG, 200000/20 );
    if ( s != ERR_SUCCESS )         return( s );
    if ( USBHD_UH_TX_LEN == 0 )        return( ERR_SUCCESS );
    if ( USBOTG_FS->RX_LEN == 0 )       return( ERR_SUCCESS );

    return( ERR_USB_BUF_OVER );
}
/*********************************************************************
 * @fn      CopySetupReqPkg
 *
 * @brief   Copy setup request package.
 *
 * @param   pReqPkt - setup request package address.
 *
 * @return  none
 */
void CopySetupReqPkg( const UINT8 *pReqPkt )
{
    UINT8 i;
    printf("setup:");
    for ( i = 0; i != sizeof( USB_SETUP_REQ ); i ++ )
    {
        ((PUINT8)pSetupReq)[ i ] = *pReqPkt;
        printf("%02x ",((PUINT8)pSetupReq)[ i ]);
        pReqPkt++;
    }
    printf("\n");
}

/*********************************************************************
 * @fn      CtrlGetDeviceDescr
 *
 * @brief   Get device descrptor
 *
 * @param   DataBuf - Data buffer.
 *
 * @return  Error state
 */
UINT8 CtrlGetDeviceDescr( PUINT8 DataBuf )
{
    UINT8   s;
    UINT8  len;

    UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;
    CopySetupReqPkg( SetupGetDevDescr );
    s = HostCtrlTransfer( DataBuf, &len );

    if ( s != ERR_SUCCESS )
    {
        printf("error:%02x\n",s);
        return( s );
    }
    UsbDevEndp0Size = ( (PUSB_DEV_DESCR)DataBuf ) -> bMaxPacketSize0;
  if ( len < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength ) return( ERR_USB_BUF_OVER );
    return( ERR_SUCCESS );
}

/*********************************************************************
 * @fn      CtrlGetConfigDescr
 *
 * @brief   Get configration descrptor.
 *
 * @param   DataBuf - Data buffer.
 *
 * @return  Error state
 */
UINT8 CtrlGetConfigDescr( PUINT8 DataBuf )
{
    UINT8   s;
    UINT8  len;

    CopySetupReqPkg( SetupGetCfgDescr );
    s = HostCtrlTransfer( DataBuf, &len );
    if ( s != ERR_SUCCESS ) return( s );
    if ( len < ( (PUSB_SETUP_REQ)SetupGetCfgDescr ) -> wLength ) return( ERR_USB_BUF_OVER );

    len = ( (PUSB_CFG_DESCR)DataBuf ) -> wTotalLength;
    CopySetupReqPkg( SetupGetCfgDescr );
    pSetupReq ->wLength = len;
    s = HostCtrlTransfer( DataBuf, &len );
    if ( s != ERR_SUCCESS ) return( s );

    return( ERR_SUCCESS );
}

/*********************************************************************
 * @fn      CtrlSetUsbAddress
 *
 * @brief   Set USB device address.
 *
 * @param   addr - Device address.
 *
 * @return  Error state
 */
UINT8 CtrlSetUsbAddress( UINT8 addr )
{
    UINT8   s;

    CopySetupReqPkg( SetupSetUsbAddr );
    pSetupReq -> wValue = addr;
    s = HostCtrlTransfer( NULL, NULL );
    if ( s != ERR_SUCCESS ) return( s );
    SetHostUsbAddr( addr );
    Delay_Ms( 10 );

    return( ERR_SUCCESS );
}


/*********************************************************************
 * @fn      CtrlSetUsbConfig
 *
 * @brief   Set usb configration.
 *
 * @param   cfg - Configration Value.
 *
 * @return  none
 */
UINT8 CtrlSetUsbConfig( UINT8 cfg )
{
    CopySetupReqPkg( SetupSetUsbConfig );
    pSetupReq -> wValue = cfg;
    return( HostCtrlTransfer( NULL, NULL ) );
}
/*********************************************************************
 * @fn      CtrlClearEndpStall
 *
 * @brief   Clear endpoint STALL.
 *
 * @param   endp - Endpoint address.
 *
 * @return  none
 */
UINT8 CtrlClearEndpStall( UINT8 endp )
{
    CopySetupReqPkg( SetupClrEndpStall );
    pSetupReq -> wIndex = endp;
    return( HostCtrlTransfer( NULL, NULL ) );
}

/*********************************************************************
 * @fn      CtrlSetUsbIntercace
 *
 * @brief   Set USB Interface configration.
 *
 * @param   cfg - Configration value.
 *
 * @return  Error state
 */
UINT8 CtrlSetUsbIntercace( UINT8 cfg )
{
    CopySetupReqPkg( SetupSetUsbInterface );
    pSetupReq -> wValue = cfg;
    return( HostCtrlTransfer( NULL, NULL ) );
}


/*********************************************************************
 * @fn      USBOTG_HostEnum
 *
 * @brief   host enumerated device.
 *
 * @return  Error state
 */
UINT8 USBOTG_HostEnum(UINT8 *buf)
{
    UINT8   i, s;
    UINT16  desclen;
    UINT8   setlen;

    /* Reset */
    ResetRootHubPort( );
    for ( i = 0, s = 0; i < 100; i ++ )
    {
        Delay_Ms( 1 );
        if ( EnableRootHubPort( ) == ERR_SUCCESS )
        {
                i = 0;
                s ++;
                if ( s > 100 ) break;
        }
    }

    /* Set Speed */
    if ( i )
    {
        DisableRootHubPort( );
        return( ERR_USB_DISCON );
    }
    SetUsbSpeed( pOTGHost->DeviceSpeed );
    HostCtl[ 0 ].DeviceSpeed = pOTGHost->DeviceSpeed;

    /* Set Device Address */
    s = CtrlSetUsbAddress( ((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue );
    if(s !=ERR_SUCCESS)
    {
       printf("set error\n");
    }

    /* Get Device Descriptor */
    s = CtrlGetDeviceDescr( buf );
    if(s !=ERR_SUCCESS)
    {
       printf("get error\n");
    }
    else
    {
        /* 存储设备描述符 */
        memcpy( DeviceDescriptor, buf, buf[0] );
    }

    /* Get Configure Descriptor */
    s = CtrlGetConfigDescr( buf );
    if(s !=ERR_SUCCESS)
    {
       printf("get configuration descriptor error\n");
    }
    else
    {
        /* 存储配置描述符 */
        desclen = (UINT16)(buf[3]<<8) + (UINT16)buf[2];
        memcpy( ConfigDescriptor, buf, desclen );
        pOTGHost->DeviceCongValue = ConfigDescriptor[5];
    }

    /* Set Configure */
    s = CtrlSetUsbConfig( pOTGHost->DeviceCongValue );  //设置配置
    if(s !=ERR_SUCCESS)
    {
       printf("set configuration error\n");
    }

#if 1
    /* SetReport */
    CopySetupReqPkg( HIDSetReport );
    USBOTG_H_FS->HOST_TX_DMA = (UINT32)&endpTXbuff[0];                  //host rx DMA address;
    USBOTG_H_FS->HOST_TX_LEN = 8;
    buf[0] = 0x01;
    s = HostCtrlTransfer( buf, &setlen );
    if ( s != ERR_SUCCESS )
    {
        printf("HID set report error\n");
    }
#endif

    return( s );
}


/*********************************************************************
 * @fn      HubSetPortFeature
 *
 * @brief   设置HUB端口特性
 *
 * @param   HubPortIndex - HUB端口
 *          FeatureSelt - HUB端口特性
 *
 * @return  Error state
 */
UINT8   HubSetPortFeature( UINT8 HubPortIndex, UINT8 FeatureSelt )
{
    pSetupReq -> bRequestType = HUB_SET_PORT_FEATURE;
    pSetupReq -> bRequest = HUB_SET_FEATURE;
    pSetupReq -> wValue = 0x0000|FeatureSelt;
    pSetupReq -> wIndex = 0x0000|HubPortIndex;
    pSetupReq -> wLength = 0x0000;
    return( HostCtrlTransfer( NULL, NULL ) );
}

/*********************************************************************
 * @fn      HubClearPortFeature
 *
 * @brief   清除HUB端口特性
 *
 * @param   HubPortIndex - HUB端口
 *          FeatureSelt - HUB端口特性
 *
 * @return  Error state
 */
UINT8   HubClearPortFeature( UINT8 HubPortIndex, UINT8 FeatureSelt )
{
    pSetupReq -> bRequestType = HUB_CLEAR_PORT_FEATURE;
    pSetupReq -> bRequest = HUB_CLEAR_FEATURE;
    pSetupReq -> wValue = 0x0000|FeatureSelt;
    pSetupReq -> wIndex = 0x0000|HubPortIndex;
    pSetupReq -> wLength = 0x0000;
    return( HostCtrlTransfer( NULL, NULL ) );
}
