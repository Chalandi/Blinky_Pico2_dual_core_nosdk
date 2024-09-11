// *****************************************************************************************************************
// Filename    : OsGenMac.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.12.2017
// 
// Description : X Macros used to generate the TCB and OCB of the OS
// 
// *****************************************************************************************************************

#ifndef _OS_GEN_MAC_H_
    #define _OS_GEN_MAC_H_
#endif

#ifndef OS_GEN_MAC_FROM_ASM_FILE
    #include"OsTypes.h"
#endif

#ifdef OS_MULTICORE_BEGIN
#undef OS_MULTICORE_BEGIN
#endif

#ifdef OS_MULTICORE_END
#undef OS_MULTICORE_END
#endif

#ifdef OS_CONFIG_BEGIN
#undef OS_CONFIG_BEGIN
#endif

#ifdef OS_TASK_BEGIN
#undef OS_TASK_BEGIN
#endif

#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif

#ifdef OS_TASK_END
#undef OS_TASK_END
#endif

#ifdef OS_EVENT_BEGIN
#undef OS_EVENT_BEGIN
#endif

#ifdef OS_EVENT_DEF
#undef OS_EVENT_DEF
#endif

#ifdef OS_EVENT_END
#undef OS_EVENT_END
#endif

#ifdef OS_ALARM_BEGIN
#undef OS_ALARM_BEGIN
#endif

#ifdef OS_ALARM_DEF
#undef OS_ALARM_DEF
#endif

#ifdef OS_ALARM_AUTO_DEF
#undef OS_ALARM_AUTO_DEF
#endif

#ifdef OS_ALARM_END
#undef OS_ALARM_END
#endif

#ifdef OS_RESOURCE_BEGIN
#undef OS_RESOURCE_BEGIN
#endif

#ifdef OS_RESOURCE_DEF
#undef OS_RESOURCE_DEF
#endif

#ifdef OS_RESOURCE_END
#undef OS_RESOURCE_END
#endif

#ifdef OS_INTERRUPT_BEGIN
#undef OS_INTERRUPT_BEGIN
#endif 

#ifdef OS_INTERRUPT_CAT1_DEF
#undef OS_INTERRUPT_CAT1_DEF
#endif

#ifdef OS_INTERRUPT_CAT2_DEF
#undef OS_INTERRUPT_CAT2_DEF
#endif

#ifdef OS_INTERRUPT_CATx_DEF
#undef OS_INTERRUPT_CATx_DEF
#endif

#ifdef OS_INTERRUPT_END
#undef OS_INTERRUPT_END
#endif

#ifdef OS_FE_INTERRUPT_BEGIN
#undef OS_FE_INTERRUPT_BEGIN
#endif 
        
#ifdef OS_FE_INTERRUPT_CAT2_DEF
#undef OS_FE_INTERRUPT_CAT2_DEF
#endif

#ifdef OS_FE_INTERRUPT_END
#undef OS_FE_INTERRUPT_END
#endif

#ifdef OS_CONFIG_END
#undef OS_CONFIG_END
#endif


#if defined(OS_GEN_ENUM)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN                                                                 typedef enum{
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)       Name,
#define OS_TASK_END                                                                   OS_INVALID_TASK}eTaskId;

#define OS_NUMBER_OF_TASKS   OS_INVALID_TASK
#define OS_INTERNAL_TASK_ID  OS_INVALID_TASK

#define OS_EVENT_BEGIN                                                           typedef enum{
#define OS_EVENT_DEF(Event, Mask)                                                Event = Mask,
#define OS_EVENT_END                                                             OS_INVALID_EVENT}eEventId;

#define OS_NUMBER_OF_EVENTS  OS_INVALID_EVENT

#define OS_ALARM_BEGIN                                                           typedef enum{
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)                            Name,
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)       Name,
#define OS_ALARM_END                                                             OS_INVALID_ALARM}eAlarmId;

#define OS_NUMBER_OF_ALARMS  OS_INVALID_ALARM

#define OS_RESOURCE_BEGIN                                                        typedef enum{
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)                     Name,
#define OS_RESOURCE_END                                                          OS_INVALID_RESOURCE}eResourceId;

#define OS_NUMBER_OF_RESOURCE  OS_INVALID_RESOURCE

#define OS_INTERRUPT_BEGIN                                                      
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                
#define OS_INTERRUPT_END                                                        

#define OS_NUMBER_OF_ISR

#define OS_FE_INTERRUPT_BEGIN                                                   
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)                                     
#define OS_FE_INTERRUPT_END                                                     

#define OS_NUMBER_OF_FE_ISR

#define OS_CONFIG_END
#define OS_MULTICORE_END

#elif defined(OS_GEN_FUNC_PROTO)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN                                                            
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  TASK(Name);
#define OS_TASK_END                                                              


#define OS_EVENT_BEGIN                                                           
#define OS_EVENT_DEF(Event, Mask)                                                
#define OS_EVENT_END                                                             



#define OS_ALARM_BEGIN                                                           
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END                                                             



#define OS_RESOURCE_BEGIN                                                        
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)                     
#define OS_RESOURCE_END                                                          


#define OS_INTERRUPT_BEGIN                                                      extern const OsInterruptConfigType IsrLookupTable[];
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                extern void IsrFunc(void);
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                extern ISR(IsrFunc);
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                extern void IsrFunc(void);
#define OS_INTERRUPT_END                                                         

#define OS_FE_INTERRUPT_BEGIN                                                   extern const FeIsr_t FeIntLookupTable[];
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)                                     extern ISR(FeIsrFunc);
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_DATA_STRUCT)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  TASK(Name); CREATE_STACK(Name,StackSize); static OsTcbType OsTcb_##Name = {pTASK(Name), Prio, AutoStart, pTSTACK(Name), pBSTACK(Name), pTSTACK(Name), SUSPENDED ,0 ,0 ,0 ,0 , NbOfActiv, 0, TaskType, SchedType};
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)                       ALARMCALLBACK(Callback) __attribute__((weak)); static OsAlarmConfigType OsAlarm_##Name = {0, 0,  Event,task, Action, ALARM_NO_AUTOSTART, ALARM_FREE, 0, 0, 0, pALARMCALLBACK(Callback)};
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)  ALARMCALLBACK(Callback) __attribute__((weak)); static OsAlarmConfigType OsAlarm_##Name = {Increment, Cycle,  Event,task, Action, ALARM_AUTOSTART, ALARM_FREE, 0, 0, 0, pALARMCALLBACK(Callback)};
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...) static uint32 AuthorizedTask_##Name[OS_NUMBER_OF_TASKS] = AuthorizedTasks; static OsResourceConfigType OsResource_##Name = {CeilingPrio, OS_INVALID_TASK, &AuthorizedTask_##Name[0]};
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN                                                       const OsInterruptConfigType IsrLookupTable[] = {
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                 {(pIsrFunc)&IsrFunc, (uint8)Prio, (OsInterruptNestingType)Type},
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                 {pISR(IsrFunc), (uint8)Prio, (OsInterruptNestingType)Type},
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                 {(pIsrFunc)&IsrFunc, (uint8)Prio, (OsInterruptNestingType)Type},
#define OS_INTERRUPT_END                                                         };

#define OS_FE_INTERRUPT_BEGIN                                                    const FeIsr_t FeIntLookupTable[] = {
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)                                      pISR(FeIsrFunc),
#define OS_FE_INTERRUPT_END                                                      }; 

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_TCB)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN                                                                    static const OsTcbType* OsTasksConfig[OS_NUMBER_OF_TASKS] = {
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)     &OsTcb_##Name,
#define OS_TASK_END                                                                      };

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN                                                              static const OsAlarmConfigType* OsAlarmsConfig[OS_NUMBER_OF_ALARMS]={
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)                               &OsAlarm_##Name,
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)          &OsAlarm_##Name,
#define OS_ALARM_END                                                                };

#define OS_RESOURCE_BEGIN                                                           static const OsResourceConfigType* OsResourcesConfig[OS_NUMBER_OF_RESOURCE]={
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)                        &OsResource_##Name,
#define OS_RESOURCE_END                                                             };

#define OS_INTERRUPT_BEGIN
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                      
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                      
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                      
#define OS_INTERRUPT_END

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

//Globals in OsTcb.c
#if(OS_INTERRUPT_ENABLED == 1)
  const unsigned int osNbrOfInterrupts = sizeof(IsrLookupTable)/sizeof(OsInterruptConfigType);
#else
  const unsigned int osNbrOfInterrupts = 0;
#endif

#if(OS_FE_INTERRUPT_ENABLED == 1)
  const unsigned int osNbrOfExceptions = sizeof(FeIntLookupTable) / sizeof(FeIsr_t);
#else
  const unsigned int osNbrOfExceptions = 0;
#endif

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_OCB)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN                                                           volatile Ocb_t OCB_Cfg = { 

#define OS_TASK_BEGIN                                                             (OsTcbType**)&OsTasksConfig[0],
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN                                                            (OsAlarmConfigType**)&OsAlarmsConfig[0],
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN                                                         (OsResourceConfigType**)&OsResourcesConfig[0],
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)                     
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                    
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                    
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                    
#define OS_INTERRUPT_END

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END                                                             0,0,OS_INVALID_TASK,0,0,0,0,0,0,0,0,{0}};

#elif defined(OS_GEN_LINKER_SCRIPT)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_END

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_VECTORED_IVT)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN                                                       osVectoredIVT:

#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                 j IsrFunc
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                 j OsCat2IsrWrapper
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                 j IsrFunc
#define OS_INTERRUPT_END                                                         .size osInternalVectorTable, .-osInternalVectorTable

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_LOOKUP_IVT)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN                                                       osLookupIVT:

#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)                                 .word IsrFunc
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)                                 .word OsCat2IsrWrapper
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)                                 .word IsrFunc
#define OS_INTERRUPT_END                                                         

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END

#elif defined(OS_GEN_NOT)

#define OS_MULTICORE_BEGIN
#define OS_CONFIG_BEGIN

#define OS_TASK_BEGIN
#define OS_TASK_DEF(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)  
#define OS_TASK_END

#define OS_EVENT_BEGIN
#define OS_EVENT_DEF(Event, Mask)
#define OS_EVENT_END

#define OS_ALARM_BEGIN
#define OS_ALARM_DEF(Name,Action,Event,task,Callback)
#define OS_ALARM_AUTO_DEF(Name,Increment,Cycle,Action,Event,task,Callback)
#define OS_ALARM_END

#define OS_RESOURCE_BEGIN
#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...)
#define OS_RESOURCE_END

#define OS_INTERRUPT_BEGIN
#define OS_INTERRUPT_CAT1_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_CAT2_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_CATx_DEF(IsrFunc,Prio,Type)
#define OS_INTERRUPT_END

#define OS_FE_INTERRUPT_BEGIN
#define OS_FE_INTERRUPT_CAT2_DEF(FeIsrFunc)
#define OS_FE_INTERRUPT_END  

#define OS_MULTICORE_END
#define OS_CONFIG_END

#else
#error "OS generation error: Wrong way to include OsGenMac.h"
#endif


#ifdef OS_GEN_ENUM
#undef OS_GEN_ENUM
#endif

#ifdef OS_GEN_FUNC_PROTO
#undef OS_GEN_FUNC_PROTO
#endif

#ifdef OS_GEN_DATA_STRUCT
#undef OS_GEN_DATA_STRUCT
#endif

#ifdef OS_GEN_LINKER_SCRIPT
#undef OS_GEN_LINKER_SCRIPT
#endif

#ifdef OS_GEN_TCB
#undef OS_GEN_TCB
#endif

#ifdef OS_GEN_OCB
#undef OS_GEN_OCB
#endif

#ifdef OS_GEN_NOT
#undef OS_GEN_NOT
#endif

#ifdef OS_GEN_VECTORED_IVT
#undef OS_GEN_VECTORED_IVT
#endif

#ifdef OS_GEN_LOOKUP_IVT
#undef OS_GEN_LOOKUP_IVT
#endif
