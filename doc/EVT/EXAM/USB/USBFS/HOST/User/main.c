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
  USBFS设备的简易枚举过程例程：
  OTG_FS_DM(PA11)、OTG_FS_DP(PA12)。

*/
#include "debug.h"
#include "stdio.h"
#include "string.h"
#include "ch32vf20x_usbotg_host.h"

#define IN_TRANSFER      0
#define OUT_TRANSFER     0
#define ISOIN_TRANSFER   0
#define ISOUT_TRANSFER   0

UINT16  RecvLen;
UINT32  packnum;
__attribute__ ((aligned(16))) UINT8 ComParebuff[64];
extern PUSBHS_HOST pOTGHost;
void GPIOInit(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

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
    UINT8 s;
    UINT8 flg=1;
    USART_Printf_Init(115200);
    Delay_Init();
    printf("SystemClk:%d\r\n",SystemCoreClock);
    memset(ComParebuff,0xff,64);
    GPIOInit();
    USBOTG_HostInit(ENABLE);
    pOTGHost=(PUSBHS_HOST)ComParebuff;
    while(1)
    {
        while(flg)
        {
            s = ERR_SUCCESS;
            if ( USBOTG_FS->INT_FG & USBHD_UIF_DETECT )
            {
                USBOTG_FS->INT_FG = USBHD_UIF_DETECT ;

                s = AnalyzeRootHub( );
                if ( s == ERR_USB_CONNECT )
                {
                    printf( "New Device In\r\n" );
                    FoundNewDev = 1;

                }
                if( s == ERR_USB_DISCON )
                {
                    printf( "Device Out\r\n" );
                }
            }

            if ( FoundNewDev || s == ERR_USB_CONNECT )
            {
                FoundNewDev = 0;
                Delay_Ms( 200 );
                s = USBOTG_HostEnum();
                if ( s == ERR_SUCCESS )
                {
                    printf( "Device Enum Succeed\r\n" );
                    flg=0;
                }
                else printf( "Device Enum Failed\r\n" );
            }
        }

#if IN_TRANSFER
        if( USBOTG_FS->MIS_ST & USBHD_UMS_SOF_ACT)
        {
            USBOTG_FS->MIS_ST = USBHD_UMS_SOF_ACT;
            USBHD_UH_RX_DMA = (UINT32)&endpRXbuff[0];
            RecvLen=USBHostTransact(USB_PID_IN<<4|USBOTG_EP1,0,20000000);
            packnum++;
            if(packnum>200000)
            {
                printf("success!\n");
                break;
            }
        }

#endif
#if OUT_TRANSFER

       if(  USBOTG_FS->MIS_ST&USBHD_UMS_SOF_ACT)
       {
           USBOTG_FS->MIS_ST=USBHD_UMS_SOF_ACT;

            USBHD_UH_TX_DMA=(UINT32)&ComParebuff[0];
            USBHD_UH_TX_LEN=64;
            s=USBHostTransact(USB_PID_OUT<<4|USBOTG_EP1,0,2000000);;
            packnum++;
            if(packnum>200000)
            {
                printf("success!\n");
                break;
            }
       }
#endif

    }
    while(1);
}

