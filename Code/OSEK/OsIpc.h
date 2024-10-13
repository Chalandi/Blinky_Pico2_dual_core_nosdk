// *****************************************************************************************************************
// Filename    : OsIpc.c
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
// Description : Inter-process communication header file
// 
// *****************************************************************************************************************

#ifndef __OS_IPC_H__
#define __OS_IPC_H__

//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
#include"Platform_Types.h"
#include"osFifo.h"

//------------------------------------------------------------------------------------------------------------------
// Types definition
//------------------------------------------------------------------------------------------------------------------
typedef struct{
  uint16 const owner;                        /* OS task id owning the mailbox */
  uint16 const res;                          /* OS resource used to protect the mailbox */
  uint16 const evt;                          /* OS event used to notify the owner of a new msg in the mailbox */
  uint16 const spinlock;                     /* OS spinlock used to protect the mailbox in multicore context */
  OsCircularFifoQueueDataType* const pQueue; /* pointer to the circulair fifo queue */
}OsIpcMbxCfgType;


typedef struct{
  uint16 id;    /* Message Id (channel) */
  uint16 size;  /* size of the data pointed by pdata */
  uint8* pdata; /* pointer to the data */
}OsIpcMbxdataType;

typedef enum{
  IPC_NOK = 0,
  IPC_OK
}IpcStatus;

//------------------------------------------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------------------------------------------
#define IPC_DEF_MBX_QUEUE(TaskId, size, ressource, event)   CIRCULAR_FIFO_DEF(TaskId,size); \
               const OsIpcMbxCfgType IpcMbx_##TaskId = {.owner=TaskId, .res=ressource, .evt=event, .pQueue=&Fifo_##TaskId}

//------------------------------------------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------------------------------------------
#define pIPC(Owner) &IpcMbx_##Owner
#define gIPC(Owner) IpcMbx_##Owner

//------------------------------------------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------------------------------------------
IpcStatus OS_IpcSendData(OsIpcMbxCfgType const * const  MsgBox /* Mailbox_ID */, OsIpcMbxdataType const* Msgdata);
IpcStatus OS_IpcReceiveData(OsIpcMbxCfgType const * const  MsgBox, OsIpcMbxdataType const* Msgdata);

#endif // __IPC_H__
