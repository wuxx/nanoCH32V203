/********************************** (C) COPYRIGHT *******************************
 * File Name          : RTC.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2022/01/18
 * Description        : RTC配置及其初始化
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "HAL.h"

/*********************************************************************
 * CONSTANTS
 */
#define RTC_INIT_TIME_HOUR      0
#define RTC_INIT_TIME_MINUTE    0
#define RTC_INIT_TIME_SECEND    0

/***************************************************
 * Global variables
 */
volatile uint32_t RTCTigFlag;

/*******************************************************************************
 * @fn      RTC_SetTignTime
 *
 * @brief   配置RTC触发时间
 *
 * @param   time    - 触发时间.
 *
 * @return  None.
 */
void RTC_SetTignTime(uint32_t time)
{
    RTC_WaitForLastTask();
    RTC_SetAlarm(time);
    RTC_WaitForLastTask();
    RTCTigFlag = 0;
}


/*******************************************************************************
 * @fn      HAL_Time0Init
 *
 * @brief   系统定时器初始化
 *
 * @param   None.
 *
 * @return  None.
 */
void HAL_TimeInit(void)
{
    uint16_t temp=0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
#if( CLK_OSC32K )
    RCC_LSICmd(ENABLE);
    RCC_LSEConfig(RCC_LSE_OFF);
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#else
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) //检查指定的RCC标志位设置与否,等待低速晶振就绪
    {
        temp++;
        Delay_Ms(10);
    }
    if(temp>=250)
    {
        printf("time error..\n");
    }
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#endif
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForLastTask();
    RTC_WaitForLastTask();
    RTC_SetPrescaler(1);
    RTC_WaitForLastTask();
    RTC_SetCounter(0);
    RTC_WaitForLastTask();
#if( CLK_OSC32K )
    Lib_Calibration_LSI();
#endif
    TMOS_TimerInit( RTC_GetCounter );
}

__attribute__((interrupt("WCH-Interrupt-fast")))
void RTCAlarm_IRQHandler(void)
{
    TMOS_TimerIRQHandler();
    RTCTigFlag = 1;
    EXTI_ClearITPendingBit(EXTI_Line17);
    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_WaitForLastTask();
}

/******************************** endfile @ time ******************************/
