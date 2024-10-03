
import datetime
import getpass
from tabulate import tabulate

def OsConfigCodeGeneration(args, OilOs,
                                 OilTasks,
                                 OilEvents,
                                 OilResources,
                                 OilAlarms,
                                 OilInterrupts,
                                 OilGenTemplate,
                                 PrioritiesList):

    OsGenCfgHeaderFilePath = args.gen_folder + "/osGenCfg.h"
    OsGenCfgHeaderFile = open(OsGenCfgHeaderFilePath, 'w', encoding='utf-8')
    OsGenCfgHeaderFile.write("\n// **********************************************************************************************************************\n")
    OsGenCfgHeaderFile.write("//                                                  OSEK OS Configuration\n")
    OsGenCfgHeaderFile.write("// **********************************************************************************************************************\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("// **********************************************************************************************************************\n")
    OsGenCfgHeaderFile.write("// Filename        : osGenCfg.h\n")
    OsGenCfgHeaderFile.write("//\n")
    user = getpass.getuser()
    OsGenCfgHeaderFile.write(f"// Author          : {user}\n")
    OsGenCfgHeaderFile.write("//\n")
    OsGenCfgHeaderFile.write(f"// Owner           : {user}\n")
    OsGenCfgHeaderFile.write("//\n")
    OsGenCfgHeaderFile.write("// Generator       : OilGenTool\n")
    OsGenCfgHeaderFile.write("//\n")
    date = datetime.datetime.now().strftime("%d.%m.%Y")
    time = datetime.datetime.now().strftime("%H:%M:%S")
    OsGenCfgHeaderFile.write(f"// Generation Time : {date} {time}\n")
    OsGenCfgHeaderFile.write("//\n")
    OsGenCfgHeaderFile.write("// Description     : Auto-generated OS Configuration file please do not modify it manually !!!\n")
    OsGenCfgHeaderFile.write("//\n")
    OsGenCfgHeaderFile.write("// **********************************************************************************************************************\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("#include \"OsGenMac.h\"\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("//=============================================================================\n")
    OsGenCfgHeaderFile.write("// OS Configuration Summary\n")
    OsGenCfgHeaderFile.write("//=============================================================================\n")
    OsGenCfgHeaderFile.write("/*\n")
    # Display OS info
    OsGenCfgHeaderFile.write("  OS:\n  "+tabulate(OilOs.OsList, headers=["Name", "Properties"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write("\n  Tasks:\n  "+tabulate(OilTasks.OsTasksList, headers=["Task", "Type", "Schedule", "Priority", "Activation", "Autostart", "Stack size", "Wait events mask"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of tasks: {OilTasks.OsTaskTotalNumber}"+"\n")
    OsGenCfgHeaderFile.write("\n  Task's events: "+"\n")
    OsGenCfgHeaderFile.write("  " + tabulate(OilTasks.OsTaskEventL, headers=["Task", "Events"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write("\n  Task's resources: "+"\n")
    OsGenCfgHeaderFile.write("  " + tabulate(OilTasks.OsTaskResourceL, headers=["Task", "Resources"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")

    # Display event info
    OsGenCfgHeaderFile.write("\n  Events:\n  "+tabulate(OilEvents.EventsList, headers=["EVENT", "MASK"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of events: {OilEvents.EventsTotalNumber}"+"\n")

    # Display resources info
    OsGenCfgHeaderFile.write("\n  Resources:\n  "+tabulate(OilResources.ResourcesList, headers=["Resource", "Priority ceiling", "Property", "Mask"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of resources: {OilResources.ResourcesTotalNumber}"+"\n")

    # Display priority scheme
    if ((args.gen_folder != None) or (args.process)):
        OsGenCfgHeaderFile.write("\n  Priority Scheme:\n  "+tabulate(PrioritiesList, headers=["Name", "Priority"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
        OsGenCfgHeaderFile.write(f"  Total levels of priority: {len(PrioritiesList)}"+"\n")

    # Display alarms info
    OsGenCfgHeaderFile.write("\n  Alarms:\n  "+tabulate(OilAlarms.AlarmsList, headers=["Name", "Alarmtime", "Cycletime", "Event", "Task", "Action", "Autostart", "Callback"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of alarms: {OilAlarms.AlarmsTotalNumber}"+"\n")

    # Display interrupts info
    OsGenCfgHeaderFile.write("\n  Interrupts:\n  "+tabulate(OilInterrupts.InterruptsList, headers=["Name", "Category", "Vector", "Prio", "Nesting"], tablefmt='fancy_grid').replace("\n", "\n" + "  ")+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of used interrupts: {OilInterrupts.InterruptsTotalNumber}"+"\n")
    OsGenCfgHeaderFile.write(f"  Total number of CPU interrupts : {OilOs.OsMaxVectorEntries}"+"\n")
    OsGenCfgHeaderFile.write("*/\n")

    # Generate OS configuration
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("//=============================================================================\n")
    OsGenCfgHeaderFile.write("// OS Configuration\n")
    OsGenCfgHeaderFile.write("//=============================================================================\n")
    OsGenCfgHeaderFile.write("OS_CONFIG_BEGIN\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate tasks configuration
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Tasks Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("    OS_TASK_BEGIN\n")
    for i in range(len(OilTasks.OsTasksList)):
        task_name       = OilTasks.OsTasksList[i][0]
        task_prio       = OilTasks.OsTasksList[i][3]
        task_stacksize  = OilTasks.OsTasksList[i][6]
        task_activation = OilTasks.OsTasksList[i][4]
        task_autostart  = "OS_AUTOSTART" if (OilTasks.OsTasksList[i][5] == "TRUE") else "OS_NO_AUTOSTART"
        task_type       = "EXTENDED" if (OilTasks.OsTasksList[i][1] == "AUTO") else "BASIC"
        task_schedule   = "FULL_PREEMPT" if (OilTasks.OsTasksList[i][2] == "FULL") else "NONE_PREEMPT"
        OsGenCfgHeaderFile.write(f"        OS_TASK_DEF({task_name}, {task_prio}, {task_stacksize}, {task_activation}, {task_autostart}, {task_type}, {task_schedule})\n")
    OsGenCfgHeaderFile.write("    OS_TASK_END\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate events configuration
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Events Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("    OS_EVENT_BEGIN\n")
    for i in range(len(OilEvents.EventsList)):
        event_name = OilEvents.EventsList[i][0]
        event_mask = OilEvents.EventsList[i][1]
        OsGenCfgHeaderFile.write(f"        OS_EVENT_DEF({event_name}, {event_mask})\n")
    OsGenCfgHeaderFile.write("    OS_EVENT_END\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate alarms configuration
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Alarms Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("    OS_ALARM_BEGIN\n")
    for i in range(len(OilAlarms.AlarmsList)):
        alarm_name     = OilAlarms.AlarmsList[i][0] if OilAlarms.AlarmsList[i][0] != "-" else "0"
        alarm_action   = OilAlarms.AlarmsList[i][5] if OilAlarms.AlarmsList[i][5] != "-" else "0"
        alarm_event    = OilAlarms.AlarmsList[i][3] if OilAlarms.AlarmsList[i][3] != "-" else "0"
        alarm_task     = OilAlarms.AlarmsList[i][4] if OilAlarms.AlarmsList[i][4] != "-" else "0"
        alarm_callback = OilAlarms.AlarmsList[i][7] if OilAlarms.AlarmsList[i][7] != "-" else "0"
        OsGenCfgHeaderFile.write(f"        OS_ALARM_DEF({alarm_name}, {alarm_action}, {alarm_event}, {alarm_task}, {alarm_callback})\n")
    OsGenCfgHeaderFile.write("    OS_ALARM_END\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate resources configuration
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Resource Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("    OS_RESOURCE_BEGIN\n")
    for i in range(len(OilResources.ResourcesList)):
        res_name = OilResources.ResourcesList[i][0]
        res_prio = OilResources.ResourcesList[i][1]
        res_mask = OilResources.ResourcesList[i][3]
        OsGenCfgHeaderFile.write(f"        OS_RESOURCE_DEF({res_name}, {res_prio}, {res_mask})\n")
    OsGenCfgHeaderFile.write("    OS_RESOURCE_END\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate interrupts configuration
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Interrupts Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("    OS_INTERRUPT_BEGIN\n")
    
    for vector in range(int(OilOs.OsMaxVectorEntries)):
        isVectorExist = False
        VectorDataIdx = 0
        for i in range(len(OilInterrupts.InterruptsList)):
            if(vector == int(OilInterrupts.InterruptsList[i][2])):
                isVectorExist = True
                VectorDataIdx = i
        
        if(isVectorExist):
            int_name   = OilInterrupts.InterruptsList[VectorDataIdx][0]
            int_cat    = OilInterrupts.InterruptsList[VectorDataIdx][1]
            int_vector = OilInterrupts.InterruptsList[VectorDataIdx][2]
            int_prio   = OilInterrupts.InterruptsList[VectorDataIdx][3]
            int_nest   = "NOT_NESTED" if OilInterrupts.InterruptsList[VectorDataIdx][4] == "FALSE" else "NESTED"            
            OsGenCfgHeaderFile.write(f"        OS_INTERRUPT_CAT{int_cat}_DEF({int_name}, {int_prio}, {int_nest})  /* Interrupt vector {vector} */\n")
        else:
            OsGenCfgHeaderFile.write(f"        OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)  /* Interrupt vector {vector} */\n")        
 
    OsGenCfgHeaderFile.write("    OS_INTERRUPT_END\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate hooks defines
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Hooks Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write(f"    #define STARTUPHOOK            {OilOs.OsStartupHook}\n")
    OsGenCfgHeaderFile.write(f"    #define ERRORHOOK              {OilOs.OsErrorHook}\n")
    OsGenCfgHeaderFile.write(f"    #define SHUTDOWNHOOK           {OilOs.OsShutdownHook}\n")
    OsGenCfgHeaderFile.write(f"    #define PRETASKHOOK            {OilOs.OsPreTaskHook}\n")
    OsGenCfgHeaderFile.write(f"    #define POSTTASKHOOK           {OilOs.OsPostTaskHook}\n")
    OsGenCfgHeaderFile.write("\n")

    # Generate OS defines
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Macros\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write(f"    #define OsStackCheck()             {OilOs.OsStackCheck }\n")
    cpu_freq = OilOs.OsCpuFrequency.replace(".", "")
    OsGenCfgHeaderFile.write(f"    #define OsCpuFrequency()           {cpu_freq}\n")
    OsGenCfgHeaderFile.write(f"    #define OsMaxVectorEntries()       {OilOs.OsMaxVectorEntries }\n")
    OsGenCfgHeaderFile.write(f"    #define OsTickTime()               {OilOs.OsTickTime }\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write("  //  Interrupt Mask Configuration\n")
    OsGenCfgHeaderFile.write("  //=============================================================================\n")
    OsGenCfgHeaderFile.write(f"  #define OS_INT_CAT1_LOWEST_PRIO_LEVEL     {OilInterrupts.InterruptCat1LowestPrio}\n")
    OsGenCfgHeaderFile.write("\n")
    OsGenCfgHeaderFile.write("OS_CONFIG_END\n")
    OsGenCfgHeaderFile.close()
