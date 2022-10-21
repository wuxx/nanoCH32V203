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
#include "UDisk_LongName.h"
#include "CHRV3UFI.h"

__attribute__ ((aligned(4))) UINT8   buf[ 128 ];  // OUT, must even address
__attribute__ ((aligned(4))) UINT8   MY_DATA_BUF[ DISK_BASE_BUF_LEN ];   /* MY_DATA_BUF指向外部RAM的磁盘数据缓冲区,缓冲区长度为至少一个扇区的长度,用于用户数据缓存*/

/* 检查操作状态,如果错误则显示错误代码并停机 */
void mStopIfError( UINT8 iError )
{
    if ( iError == ERR_SUCCESS )
    {
        return;    /* 操作成功 */
    }
    printf( "Error:%02x\r\n", iError );  /* 显示错误 */
    /* 遇到错误后,应该分析错误码以及CHRV3DiskStatus状态,例如调用CHRV3DiskReady查询当前U盘是否连接,如果U盘已断开那么就重新等待U盘插上再操作,
         建议出错后的处理步骤:
         1、调用一次CHRV3DiskReady,成功则继续操作,例如Open,Read/Write等
         2、如果CHRV3DiskReady不成功,那么强行将从头开始操作 */
    while(1)
    {  }
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
    UINT8  ret, s;
    UINT8  i;
    UINT16 j;
    UINT8  len;

    USART_Printf_Init(115200);
    Delay_Init( );
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("USBFS HOST Test EXAM 11\r\n");

    USBOTG_HostInit(ENABLE);

    ret = CHRV3LibInit();
    if( ret == ERR_SUCCESS )
    {
        printf( "UDisk Lib Init Success\n" );
    }
    else
    {
        printf( "UDisk Lib Init ERR Code %02x\n", ret );
        while(1);
    }

    while(1)
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
            s = USBOTG_HostEnum( buf );
            if ( s == ERR_SUCCESS )
            {
                printf( "Enum Succeed\r\n" );
                Delay_Ms(100);
                // U盘操作流程：USB总线复位、U盘连接、获取设备描述符和设置USB地址、可选的获取配置描述符，之后到达此处，由CH103子程序库继续完成后续工作
                CHRV3DiskStatus = DISK_USB_ADDR;
                for ( i = 0; i != 10; i ++ )
                {
                    printf( "Wait DiskReady\r\n" );
                    s = CHRV3DiskReady( );                                 //等待U盘准备好
                    if ( s == ERR_SUCCESS )
                    {
                        /*==================== 以下演示创建及读取长文件名 ============================*/
                        // 复制长文件名(UNICODE 大端)到LongNameBuf里
                        len = LongName_Len;
                        memcpy( LongNameBuf, LongName, len );
                        // 末尾用两个0表示结束
                        LongNameBuf[len] = 0x00;
                        LongNameBuf[len + 1] = 0x00;
                        // 该长文件名的ANSI编码短文件名(8+3格式)
                        strcpy( mCmdParam.Create.mPathName, "\\长文件名.TXT" );
                        i = CHRV3CreateLongName( );
                        if( i == ERR_SUCCESS )
                            printf( "Created Long Name OK!\r\n" );
                        else
                            printf( "Error Code: %02X\r\n", (UINT16)i );

                        printf( "Get long Name#\r\n" );
                        strcpy( mCmdParam.Open.mPathName, "\\长文件名.TXT" );
                        // 以上需要输入文件名的完整路径
                        i = CHRV3GetLongName( );
                        if( i == ERR_SUCCESS )
                        {
                            // 长文件名收集完成,以UNICODE编码方式(按UNICODE_ENDIAN定义)
                            // 存放在LongNameBuf缓冲里,长文件名最后用两个0结束.
                            // 以下显示缓冲区里所有数据
                            printf( "LongNameBuf: " );
                            for( j=0; j!=LONG_NAME_BUF_LEN; j++ )
                                printf( "%02X ", (UINT16)LongNameBuf[j] );
                            printf( "\r\n" );
                        }
                        else
                            printf( "Error Code: %02X\r\n", (UINT16)i );
                        break;
                    }
                    else
                    {
                        printf("s = %02x\r\n",s);
                        printf("CHRV3DiskStatus:%02x\r\n",CHRV3DiskStatus);
                    }
//                    Delay_Ms( 50 );
                }
            }
            else
            {
                printf( "Enum Failed:%02x\r\n", ret );
            }
        }
    }
}

