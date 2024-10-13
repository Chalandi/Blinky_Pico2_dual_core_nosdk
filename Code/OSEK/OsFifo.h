// *****************************************************************************************************************
// Filename    : OsFifo.h
// 
// OS          : OSEK 2.2.3  
// 
// CC          : ECC1/BCC1
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.12.2017
// 
// Description : Circulair FIFO Library header file
// 
// *****************************************************************************************************************

#ifndef _OS_FIFO_H_
#define _OS_FIFO_H_

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"Platform_Types.h"

//------------------------------------------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------------------------------------------
typedef struct {
  uint32_t        PopPtr;
  uint32_t        PushPtr;
  const uint32_t  size;
  uint8_t*        buf;
}OsCircularFifoQueueDataType;

//------------------------------------------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------------------------------------------
#define CIRCULAR_FIFO_DEF(id,fifosize)    uint8_t buffer_##id##[fifosize]={0};   \
                                          OsCircularFifoQueueDataType Fifo_##id = {0,0,fifosize,buffer_##id}

//------------------------------------------------------------------------------------------------------------------
// Functions Prototypes
//------------------------------------------------------------------------------------------------------------------
uint8_t  osCircularFifoQueue_IsEmpty(OsCircularFifoQueueDataType* pfifo);
uint8_t  osCircularFifoQueue_IsFull(OsCircularFifoQueueDataType* pfifo);
uint32_t osCircularFifoQueue_GetAvailableSize(OsCircularFifoQueueDataType* pfifo);
uint32_t osCircularFifoQueue_GetCurrentConsumption(OsCircularFifoQueueDataType* pfifo);
uint8_t  osCircularFifoQueue_Push(OsCircularFifoQueueDataType* pfifo, uint8_t* data, uint32_t size);
uint8_t  osCircularFifoQueue_Pop(OsCircularFifoQueueDataType* pfifo, uint8_t* data, uint32_t size);
uint8_t  osCircularFifoQueue_ReadCopy(OsCircularFifoQueueDataType* pfifo, uint8_t* data, uint32_t size);

#endif /*_OS_FIFO_H_*/
