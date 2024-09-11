// *****************************************************************************
// Filename    : OsTcb.h
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
// Description : Task Control Block definition header file
// 
// *****************************************************************************

#ifndef __TCB_H__
#define __TCB_H__

#include"OsTypes.h"
#include"OsGenPrioTypes.h"

/***************************************************/
/*            X Macro System Generation            */
/***************************************************/
#define OS_GEN_ENUM
#include"OsGenCfg.h"
#undef OS_GEN_ENUM

#define OS_GEN_FUNC_PROTO
#include"OsGenCfg.h"
#undef OS_GEN_FUNC_PROTO


#define RES_SCHEDULER_PRIO (uint32)((sizeof(OsSchedPrioType) * 4ul) - 1ul)


/* OS Configuration Block */
extern volatile Ocb_t OCB_Cfg;


#endif
