/********************************** (C) COPYRIGHT *******************************
* File Name          : RingMem.h
* Author             : Hikari
* Version            : V1.4
* Date               : 2019/12/20
* Description        :

*******************************************************************************/

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

#ifndef RINGMEM_H
#define RINGMEM_H

#ifndef SUCCESS
  #define SUCCESS    0
#endif
#ifndef ENABLE
  #define ENABLE    1
#endif
#ifndef DISABLE
  #define DISABLE    0
#endif

/*********************************************************************
 * TYPEDEFS
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16;
typedef unsigned long  uint32_t;
typedef int (*RingMemProtection_t)(uint8_t enable);

//缓冲区结构体
typedef struct
{
    uint8_t volatile *pData;       //缓冲区首地址
    uint8_t volatile *pWrite;      //写指针
    uint8_t volatile *pRead;       //读指针
    uint8_t volatile *pEnd;        //缓冲区末地址
    uint32_t volatile RemanentLen; //剩余空间大小
    uint32_t volatile CurrentLen;  //已用空间大小
    uint32_t volatile MaxLen;      //总空间大小
} RingMemParm_t;

/*********************************************************************
 * Global Variables
 */

/*********************************************************************
 * FUNCTIONS
 */

extern void RingMemInit(RingMemParm_t *Parm, uint8_t *StartAddr, uint32_t MaxLen, RingMemProtection_t Protection);

extern uint8_t RingMemWrite(RingMemParm_t *Parm, uint8_t *pData, uint32_t len);

extern uint8_t RingMemRead(RingMemParm_t *Parm, uint8_t *pData, uint32_t len);

extern uint8_t RingMemCopy(RingMemParm_t *Parm, uint8_t *pData, uint32_t len);

extern uint8_t RingMemDelete(RingMemParm_t *Parm, uint32_t len);

extern uint8_t RingAddInStart(RingMemParm_t *Parm, uint8_t *pData, uint32_t len);

extern uint8_t RingReturnSingleData(RingMemParm_t *Parm, uint32_t Num);
/*********************************************************************
*********************************************************************/

#endif
