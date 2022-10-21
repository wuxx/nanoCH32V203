/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0
* Date               : 2020/08/06
* Description        : 
*******************************************************************************/



/******************************************************************************/
/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "RF_PHY.h"
#include "tmos_hw.h"
#include "rfend.h"

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
u8 taskID;
u8 TX_DATA[264] ={1,2,3,4,5,6,7,8,9,0};
u8 RX_DATA[264] ={5,5,5,5,5,5,5,5,5,5};

u32 recv_count;
u32 recv_crc;
u32 recv_data_err;

s8  rssi_val;
s8  rssi_max;
s8  rssi_min;
u16 err_buf[1000];
u32 cnt_tx=0;
u32 time[10];
u16 time_count=0;

#define  AUTO_MODE   FALSE

#define R32_TMR6COUNTER      (*((PUINT32V)(0x4000C268)))

u8 tmp_data;

void RF_2G4StatusCallBack( u8 sta , u8 rsp, u8 *rxBuf )
{
  switch( sta ){
    case TX_MODE_TX_FINISH:
    {
//      TX_DATA[0]++;
      for( int i=0;i<200;i++ )TX_DATA[i]++;
      break;
    }
		
    case TX_MODE_TX_FAIL:
    {
//      PRINT( "#%d\n",RF_Rx( TX_DATA,10,0xFF,0xFF));
      break;
    }
		
		case TX_MODE_RX_DATA:
    {
      if( rsp){
//        if(rsp&1)PRINT("crc error\n");
        recv_crc++;
      }
      else{
//        u8 i;
//
//        PRINT("tx recv,rssi:%d\n",(s8)rxBuf[0]);
//        PRINT("len:%d-",rxBuf[1]);
//        for(i=0;i<rxBuf[1];i++) PRINT("%x ",rxBuf[i+2]);
//        PRINT("\n");
        recv_count++;
      }
      break;
    }
		
		case TX_MODE_RX_TIMEOUT:
		{
//      PRINT( "#%d\n",RF_Rx( TX_DATA,10,0xFF,0xFF));
			break;
		}
		case TX_MODE_HOP_SHUT:
		{
			PRINT("TX_MODE_HOP_SHUT...\n");
			tmos_set_event( taskID , SBP_RF_CHANNEL_HOP_TX_EVT );
			while(1);
			break;
		}
		
    case RX_MODE_RX_DATA:
    {
      time[9] = time[4] - time[3];
      time[4] = (*((PUINT32V)(0x4000C268)));
      (*((PUINT32V)(0x4000C26C))) = time_count;
//      if( time[3]-time[4] > 5000 )
//      {
//        PRINT("t2:%d-%d-%d-%d\n", time[0] - time[1],time[1] - time[2],time[5] - time[6],time[2] - time[3] );
//      }
//      else{
//        PRINT("t1:%d-%d-%d-%d\n", time[0] - time[1],time[1] - time[2],time[5] - time[6],time[2] - time[3] );
//      }
//      __nop();__nop();__nop();__nop();//__nop();//__nop();//__nop();
      if( rsp){
        int i;

        if(recv_crc<1000){
          err_buf[recv_crc] = recv_count;
          recv_crc++;
        }
        if(rsp&1)PRINT("\n----------------crc error\n");
        else PRINT("\n----------------type error\n");
        PRINT("\n----------------------\nlen:%d\n",rxBuf[1]);
        for(i=0;i<rxBuf[1]+6;i++) PRINT("%02x ",rxBuf[i]);
        PRINT("\n");
        for(;i<rxBuf[1]+6+16;i++) PRINT("%02x ",rxBuf[i]);
        PRINT("\n");
      }
      else{
//        if((rxBuf[0]&0xF) == 0X08 || (rxBuf[0]&0xF) == 0x05){
////          PRINT("rx recv,rssi:%d\n",(s8)rxBuf[0]);
//          PRINT("type:%x\n",rxBuf[0]);
//          PRINT("len:%d-",rxBuf[1]);
//          for(int i=0;i<rxBuf[1];i++) PRINT("%x ",rxBuf[i+2]);
//          PRINT("\n");
//        }
//        if( rssi_min > (s8)rxBuf[0] ){
//          rssi_min = rxBuf[0];
//        }
//        if( rssi_max < (s8)rxBuf[0] ){
//          rssi_max = rxBuf[0];
//        }
//        if( rssi_val ){
//          rssi_val = (rssi_val+(s8)rxBuf[0])/2
//        }
//        else{
//          rssi_val = rxBuf[0];
//        }
        if( tmp_data == rxBuf[2] ){
          recv_data_err++;
          for(int i=0;i<rxBuf[1];i++) PRINT("%x ",rxBuf[i+2]);
          PRINT("\n");
        }

        tmp_data = rxBuf[2];
        recv_count++;
        tmos_start_task( taskID , SBP_RF_TEST_RX_COUNT_EVT , 1000 );
      }
#if (AUTO_MODE == FALSE)
      tmos_set_event( taskID , SBP_RF_SET_RX_EVT );
#endif
      time[0] = R32_TMR6COUNTER;
      break;
    }
		
    case RX_MODE_TX_FINISH:
    {
      TX_DATA[0]++;
#if AUTO_MODE
      tmos_set_event( taskID , SBP_RF_SET_RX_EVT );
#endif
      break;
    }
		
    case RX_MODE_TX_FAIL:
		{
      PRINT("RX_MODE_TX_FAIL...\n");
		  tmos_set_event( taskID , SBP_RF_SET_RX_EVT );
			break;
		}
		
		case RX_MODE_HOP_SHUT:
		{
			PRINT("RX_MODE_HOP_SHUT...\n");
			tmos_set_event( taskID , SBP_RF_CHANNEL_HOP_RX_EVT );
			break;
		}
	}

//  PRINT("STA:%x\n",sta);
}


uint16 RF_ProcessEvent( uint8 task_id, uint16 events )
{
  if ( events & SYS_EVENT_MSG )
  {
    uint8 *pMsg;

    if ( (pMsg = tmos_msg_receive( task_id )) != NULL )
    {
      // Release the TMOS message
      tmos_msg_deallocate( pMsg );
    }
    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }
  if( events & SBP_RF_START_DEVICE_EVT ){
    PRINT("rf 2.4g tx\n");
    cnt_tx = 0;
    tmos_set_event( taskID , SBP_RF_PERIODIC_EVT );
    return events^SBP_RF_START_DEVICE_EVT;
  }
  if( events & SBP_RF_PERIODIC_EVT ){
		RF_Tx( TX_DATA,151,0xFF, 0xFF);
//    return events;
		cnt_tx++;
		if( cnt_tx < 100 ){
      tmos_start_task( taskID , SBP_RF_PERIODIC_EVT , 16 );
		}
		else{
      tmos_start_task( taskID , SBP_RF_START_DEVICE_EVT , 1600 );
      PRINT("%d\t%d\t%d\t%d\t%d\t%d\n",recv_count,recv_data_err,recv_crc,rssi_min,rssi_val,rssi_max);
      recv_count =0;recv_crc=0;rssi_val=0;rssi_max=0x80;rssi_min=0;recv_data_err=0;
		}
    return events^SBP_RF_PERIODIC_EVT;
  }
  if ( events & SBP_RF_SET_RX_EVT ){
//    PRINT("rf 2.4g Rx\n");
//    recv_count =0;recv_crc=0;rssi_val=0;rssi_max=0x80;rssi_min=0;
    tmos_start_task( taskID , SBP_RF_TEST_RX_COUNT_EVT , 80 );
//    time[1] = (*((PUINT32V)(0x4000C268)));
//    RF_Shut();
//    time[2] = (*((PUINT32V)(0x4000C268)));
    RF_Rx( RX_DATA,10,0xFF,0xFF );
//    time[3] = (*((PUINT32V)(0x4000C268)));
//    if( time[0] - time[1] > 1000 ){
//      PRINT("timeout:%x\n",time[0]-time[1]);
//    }
//    PRINT("lle:%x\n",(*((PUINT32V)(0x4000C250))) );
    return events^SBP_RF_SET_RX_EVT;
  }
  if( events & SBP_RF_CHANNEL_HOP_TX_EVT ){
    PRINT("\n------------- hop tx...\n");
		if( RF_FrequencyHoppingTx( 0 ) ){
			tmos_start_task( taskID , SBP_RF_CHANNEL_HOP_TX_EVT ,100 );
		}
		else{
			tmos_set_event( taskID , SBP_RF_START_DEVICE_EVT );
			PRINT("set tx\n");
		}
    return events^SBP_RF_CHANNEL_HOP_TX_EVT;
  }
	if( events & SBP_RF_CHANNEL_HOP_RX_EVT ){
		PRINT("hop rx...%X\n",RF_FrequencyHoppingRx( 0 ));
		RF_Rx( RX_DATA,10,0xF8,0xF8 );
    return events^SBP_RF_CHANNEL_HOP_RX_EVT;
	}
	if( events & SBP_RF_TEST_RX_COUNT_EVT ){
    PRINT( "%d\t%d\t%d\t%d\t%d\t%d\n",recv_count, recv_data_err,recv_crc,time_count,time[9],rssi_max );
    PRINT(" bb recv:%4d err:%4d\n", (*((PUINT32V)(0x4000C140))), (*((PUINT32V)(0x4000C144))) );
    (*((PUINT32V)(0x4000C100))) |= (1<<31);
//    for( int i=0;i<=0x68;i+=4 ){
//      PRINT( "addr:%x-%x\n", i,(*((PUINT32V)(0x4000C100+i))) );
//    }
//    DBG_PRINT("rf reg def:\r\n");
//    for(int i=0;i<13;i++){
//      DBG_PRINT("addr:%2x---%08x...\n",0xA0+(i*4),(*((u32 *)(0x4000D000+0xA0+i*4))) );
//    }
//    DBG_PRINT("\r\n----------------------------\r\n");

//    for(u16 i=0;i<recv_crc;i++ ){
//      PRINT("%d ",err_buf[i]);
//    }
//    PRINT("\n");
    recv_count =0;recv_crc=0;rssi_val=0;rssi_max=0x80;rssi_min=0;recv_data_err=0;
    time_count++;if(time_count>2000)time_count = 1900;
    tmos_start_task( taskID, SBP_RF_TEST_RX_COUNT_EVT, 8000 );
    return events^SBP_RF_TEST_RX_COUNT_EVT;
	}
  return 0;
}
#define RF_EXTEND_CHANNEL_2483          (0xE3)
#define RF_EXTEND_CHANNEL_2484          (0xE4)
#define RF_EXTEND_CHANNEL_2485          (0xE5)
#define RF_EXTEND_CHANNEL_2486          (0xE6)
#define RF_EXTEND_CHANNEL_2487          (0xE7)
#define RF_EXTEND_CHANNEL_2488          (0xE8)
#define RF_EXTEND_CHANNEL_2489          (0xE9)
#define RF_EXTEND_CHANNEL_2490          (0xEA)


void RF_Init( void )
{
  u8 s;
  rfConfig_t rfConfig;
  
  for( int i=0;i<255;i++ ) TX_DATA[i] = 0x55;
  taskID = TMOS_ProcessEventRegister( RF_ProcessEvent );
	tmos_memset( &rfConfig,0,sizeof(rfConfig_t) );
//  rfConfig.accessAddress = 0x8E89BED6;
  rfConfig.accessAddress = 0x71764129;
  rfConfig.CRCInit = 0x555555;
  rfConfig.Frequency = 2406000; // kHz
  rfConfig.Channel = 17;
  rfConfig.ChannelMap = (1<<5);
  if( AUTO_MODE ){
    rfConfig.LLEMode = LLE_MODE_AUTO|LLE_MODE_PHY_2M;
  }
 // rfConfig.LLEMode |= LLE_MODE_NON_RSSI|LLE_MODE_EX_CHANNEL;
  rfConfig.rfStatusCB = RF_2G4StatusCallBack;
  s = RF_Config( &rfConfig );
  PRINT("rf 2.4g init:%d\n",s);
  if( (R32_PB_PIN&(1<<15)) == 0 ){ // RX mode
    PRINT("RX mode...\n");
    tmos_set_event( taskID , SBP_RF_SET_RX_EVT );
//		tmos_set_event( taskID , SBP_RF_CHANNEL_HOP_RX_EVT );
	}
	else{ // TX mode
		PRINT("TX mode...\n");
    tmos_set_event( taskID , SBP_RF_START_DEVICE_EVT );
//		tmos_set_event( taskID , SBP_RF_CHANNEL_HOP_TX_EVT );
	}
}

/******************************** endfile @ main ******************************/
