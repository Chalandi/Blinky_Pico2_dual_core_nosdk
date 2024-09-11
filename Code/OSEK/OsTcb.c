// ******************************************************************************************************
// Filename    : OsTcb.c
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
// Description : Task Control Block definition
// 
// ******************************************************************************************************

#include"OsTcb.h"

/***************************************************/
/*            X Macro System Generation            */
/***************************************************/

#define OS_GEN_DATA_STRUCT
#include"OsGenCfg.h"
#undef OS_GEN_DATA_STRUCT

#define OS_GEN_TCB
#include"OsGenCfg.h"
#undef OS_GEN_TCB

#define OS_GEN_OCB
#include"OsGenCfg.h"
#undef OS_GEN_OCB

