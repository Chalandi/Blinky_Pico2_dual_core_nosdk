#####################################################################################
# 
# Filename    : OilGen.py
# 
# Author      : Chalandi Amine
#
# Owner       : Chalandi Amine
# 
# Date        : 29.01.2023
# 
# Description : OSEK OIL code generator tool
# 
#####################################################################################

import sys
import re
import os
import subprocess

# Dependencies:
try:
    from jinja2 import Template
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "jinja2"])

try:
    from tabulate import tabulate
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "tabulate"])

try:
    import argparse
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "argparse"])

#import OilCpu            # could be useful in multicore
import OilOs
import OilTasks
import OilEvents
import OilResources
import OilAlarms
import OilInterrupts
import OilGenTemplate
import OilCodeGen

# ANSI color code definition
class Color:
    BLACK     = '\033[30m'
    RED       = '\033[31m'
    GREEN     = '\033[32m'
    YELLOW    = '\033[33m'
    BLUE      = '\033[34m'
    MAGENTA   = '\033[35m'
    CYAN      = '\033[36m'
    WHITE     = '\033[37m'
    UNDERLINE = '\033[4m'
    RESET     = '\033[0m'

# Globals
PrioritiesList = []

# Command-line syntax :  py  <ThisPythonScriptName>  -h

# Get command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument("-i", dest="oil_file", help="Input OSEK OIL file")
parser.add_argument("-gen", dest="gen_folder", help="Generate OSEK TCB data")
parser.add_argument("-info", dest="info", action="store_true", help="Display OSEK OS objects info")
parser.add_argument("-process", dest="process", action="store_true", help="process OSEK OS objects")
parser.add_argument("-template", dest="template_oil_file", help="Create an OSEK OIL template file")
parser.add_argument("-html", dest="html_file", help="Generate HTML report file")
args = parser.parse_args()

# Check args
if (args.oil_file == None) and (args.template_oil_file == None) and (args.html_file == None):
    parser.print_usage()
    quit()

# Check if the input file exists
if (args.oil_file!= None) and (os.path.exists(args.oil_file) == False):
    print(f"The input file \"{args.oil_file}\" does not exist !")
    sys.exit(0)

# Get the OIL file content
if (args.oil_file != None):
    OilFileDescriptor = open(args.oil_file, 'r')
    OilFileContent    = OilFileDescriptor.read()

    # Parse OS
    OilOs.OilOsParser(args, OilFileContent)

    # Parse tasks
    OilTasks.OilTaskParser(args, OilFileContent)

    # Parse events
    OilEvents.OilEventsParser(args, OilFileContent)

    # Parse resources
    OilResources.OilResourcesParser(args, OilFileContent)

    # Parse alarms
    OilAlarms.OilAlarmsParser(args, OilFileContent)

    # Parse interrupts
    OilInterrupts.OilInterruptsParser(args, OilFileContent)

# Generate TCB:
if ((args.gen_folder != None) or (args.process)):
    ##################################################################################################
    # Process the event's mask
    ##################################################################################################
    # steps:
    # 1- Create the initial task's event mask from the hard coded masks in the OIL file.
    # 2- For each task's event mask defined with AUTO in OIL file we assign to it a free mask.
    # 3- Set the new event mask into OilEvents.OilEventsList
    ##################################################################################################
    for taskIdx in range(OilTasks.OsTaskTotalNumber):
        # Create the task event mask from the hard coded event's mask in OIL file
        TaskEventMask    = 0
        CurrentEventMask = 0
        for i in range(len(OilTasks.osTaskEvents[taskIdx])):
            TaskEventMask |= OilEvents.OilEventsGetMask(OilTasks.osTaskEvents[taskIdx][i])
        # For each event from the task's events
        for taskEventList in OilTasks.osTaskEvents:
           if len(taskEventList) > 32:
               print(f"{OilTasks.OsTasksList[taskIdx][0]} has more than 32 events !")
               exit()
           # For each event assigned to the current task check for the OIL defined mask if exist 
           # otherwise pick one from the local generated list
           for taskEventIdx in range(len(taskEventList)):
               # Update the task event mask
               TaskEventMask  = TaskEventMask | CurrentEventMask
               # Get current event's MASK from events list
               CurrentEventMask = OilEvents.OilEventsGetMask(taskEventList[taskEventIdx])
               if(CurrentEventMask == 0):
                  # Assign a new event's mask
                  CurrentEventMask =  OilEvents.OilEventsGenMask(TaskEventMask)
                  OilEvents.OilEventsSetMask(taskEventList[taskEventIdx], CurrentEventMask)

    ##################################################################################################
    # Calculate Task's wait event mask
    ##################################################################################################
    for taskIdx in range(OilTasks.OsTaskTotalNumber):
        TaskWaitEventMask = 0
        for EventMask in range(len(OilTasks.osTaskEvents[taskIdx])):
            TaskWaitEventMask |= OilEvents.OilEventsGetMask(OilTasks.osTaskEvents[taskIdx][EventMask])
        OilTasks.OsTasksList[taskIdx][7] = TaskWaitEventMask

    ##################################################################################################
    # Process the priorities (Priority Ceiling Protocol)
    ##################################################################################################
    # steps:
    # 1- Create list of all tasks and resources with their default priorities
    # 2- Create a room between all tasks priority (offset = Task index * 100)
    # 3- Calculate the priority ceiling of each resource
    # 4- Sort and update all tasks and resources priorities (preparing for using CPU's CLZ instruction)
    # 5- Add "RES_SCHEDULER" on top
    ##################################################################################################
    for TaskIdx in range(OilTasks.OsTaskTotalNumber):
        TaskName = OilTasks.OsTasksList[TaskIdx][0]
        TaskPrio = int(OilTasks.OsTasksList[TaskIdx][3], base=0) + TaskIdx*100
        PrioritiesList.append([TaskName, TaskPrio])

    for ResourceIdx in range(OilResources.ResourcesTotalNumber):
        ResourceName = OilResources.ResourcesList[ResourceIdx][0]
        ResourcePrio = OilResources.ResourcesList[ResourceIdx][1]

        for TaskIdx in range(OilTasks.OsTaskTotalNumber):
            for i in range(len(OilTasks.osTaskResources[TaskIdx])):
                if(ResourceName == OilTasks.osTaskResources[TaskIdx][i]):
                    # Create resource mask
                    OilResources.ResourcesList[ResourceIdx][3] |= (1 << TaskIdx)
                    # Calculate the prio ceiling
                    if(ResourcePrio <  int(OilTasks.OsTasksList[TaskIdx][3], base=0) + TaskIdx*100):
                        OilResources.ResourcesList[ResourceIdx][1] = int(OilTasks.OsTasksList[TaskIdx][3], base=0) + TaskIdx*100 + 1

    for ResourceIdx in range(OilResources.ResourcesTotalNumber):
        ResourceName = OilResources.ResourcesList[ResourceIdx][0]
        ResourcePrio = OilResources.ResourcesList[ResourceIdx][1]
        PrioritiesList.append([ResourceName, ResourcePrio])

    # Sort the priorities and update the tasks and resources priorities
    PrioritiesList.sort(key=lambda x: x[1])
    for idx in range(len(PrioritiesList)):
        PrioritiesList[idx][1] = idx
        
        for ResourceIdx in range(OilResources.ResourcesTotalNumber):
            if(PrioritiesList[idx][0] == OilResources.ResourcesList[ResourceIdx][0]):
                OilResources.ResourcesList[ResourceIdx][1] = str(PrioritiesList[idx][1])

        for TaskIdx in range(OilTasks.OsTaskTotalNumber):
            if(PrioritiesList[idx][0] == OilTasks.OsTasksList[TaskIdx][0]):
                OilTasks.OsTasksList[TaskIdx][3] = str(PrioritiesList[idx][1])

    # Add "RES_SCHEDULER" on top of ResourcesList
    OilResources.ResourcesList.append(["RES_SCHEDULER", PrioritiesList[len(PrioritiesList) - 1][1] + 1, "STANDARD", (1 << OilTasks.OsTaskTotalNumber) - 1])
    OilResources.ResourcesTotalNumber += 1

    # Add "RES_SCHEDULER" on top of PrioritiesList
    PrioritiesList.append([OilResources.ResourcesList[OilResources.ResourcesTotalNumber - 1][0], OilResources.ResourcesList[OilResources.ResourcesTotalNumber - 1][1]])

# Code Generation
if (args.gen_folder != None):
    OilCodeGen.OsConfigCodeGeneration(args,
                                      OilOs,
                                      OilTasks,
                                      OilEvents,
                                      OilResources,
                                      OilAlarms,
                                      OilInterrupts,
                                      OilGenTemplate,
                                      PrioritiesList)

# Generate OIL template
if args.template_oil_file:
    OilGenTemplate.OilGenTemplate(args)

# Display task info
if args.info:
    # Display OS info
    print("\nOS:\n"+tabulate(OilOs.OsList, headers=["Name", "Properties"], tablefmt='fancy_grid'))
    print("Tasks:\n"+tabulate(OilTasks.OsTasksList, headers=["Task", "Type", "Schedule", "Priority", "Activation", "Autostart", "Stack size", "Wait events mask"], tablefmt='fancy_grid'))
    print(f"Total number of tasks: {OilTasks.OsTaskTotalNumber}")
    print("\nTask's events: ")
    print(tabulate(OilTasks.OsTaskEventL, headers=["Task", "Events"], tablefmt='fancy_grid'))
    print("\nTask's resources: ")
    print(tabulate(OilTasks.OsTaskResourceL, headers=["Task", "Resources"], tablefmt='fancy_grid'))

    # Display event info
    print("\nEvents:\n"+tabulate(OilEvents.EventsList, headers=["EVENT", "MASK"], tablefmt='fancy_grid'))
    print(f"Total number of events: {OilEvents.EventsTotalNumber}")

    # Display resources info
    print("\nResources:\n"+tabulate(OilResources.ResourcesList, headers=["Resource", "Priority ceiling", "Property", "Mask"], tablefmt='fancy_grid'))
    print(f"Total number of resources: {OilResources.ResourcesTotalNumber}")

    # Display priority scheme
    if ((args.gen_folder != None) or (args.process)):
        print("\nPriority Scheme:\n"+tabulate(PrioritiesList, headers=["Name", "Priority"], tablefmt='fancy_grid'))
        print(f"Total levels of priority: {len(PrioritiesList)}")

    # Display alarms info
    print("\nAlarms:\n"+tabulate(OilAlarms.AlarmsList, headers=["Name", "Alarmtime", "Cycletime", "Event", "Task", "Action", "Autostart", "Callback"], tablefmt='fancy_grid'))
    print(f"Total number of alarms: {OilAlarms.AlarmsTotalNumber}")

    # Display interrupts info
    print("\nInterrupts:\n"+tabulate(OilInterrupts.InterruptsList, headers=["Name", "Category", "Vector", "Prio", "Nesting"], tablefmt='fancy_grid'))
    print(f"Total number of used interrupts: {OilInterrupts.InterruptsTotalNumber}")
    print(f"Total number of CPU interrupts : {OilOs.OsMaxVectorEntries}")


# Generate HTML report
if args.html_file:
    # generate the HTML code for the table
    html_os_table             = tabulate(OilOs.OsList, headers=["Name", "Properties"], tablefmt='html')
    html_tasks_table          = tabulate(OilTasks.OsTasksList, headers=["Task", "Type", "Schedule", "Priority", "Activation", "Autostart", "Stack size", "Wait events mask"], tablefmt='html')
    html_task_events_table    = tabulate(OilTasks.OsTaskEventL, headers=["Task", "Events"], tablefmt='html')
    html_task_resources_table = tabulate(OilTasks.OsTaskResourceL, headers=["Task", "Resources"], tablefmt='html')
    html_events_table         = tabulate(OilEvents.EventsList, headers=["EVENT", "MASK"], tablefmt='html')
    html_resources_table      = tabulate(OilResources.ResourcesList, headers=["Resource", "Priority ceiling", "Property", "Mask"], tablefmt='html')
    html_alarms_table         = tabulate(OilAlarms.AlarmsList, headers=["Name", "Alarmtime", "Cycletime", "Event", "Task", "Action", "Autostart", "Callback"], tablefmt='html')
    html_interrupts_table     = tabulate(OilInterrupts.InterruptsList, headers=["Name", "Category", "Vector", "Prio", "Nesting"], tablefmt='html')
    # Display priority scheme
    if ((args.gen_folder != None) or (args.process)):
        html_priority_scheme_section = "<p style=\"font-size: 24px;\">Priority Scheme:</p>"
        html_priority_scheme_table   = tabulate(PrioritiesList, headers=["Name", "Priority"], tablefmt='html')
        html_priority_scheme_title   = f" <b> Total levels of priority: {len(PrioritiesList)} </b>"
    else:
        html_priority_scheme_section = ""
        html_priority_scheme_table   = ""
        html_priority_scheme_title   = ""

    # Define the template for the HTML page
    template = Template("""<!DOCTYPE html>
    <html>
        <head>
        <title>OSEK OS Configuration</title>
        <h1 style="color:black;">OSEK OS OBJECTS SUMMARY</h1>
        <meta charset="utf-8" />
        <link rel="icon" type="image/png" href="chip2.png">
        <style>
            body {
               margin: 60px;
            }
            table {
            width: 50%;
            border-collapse: collapse;
            border-style: solid;
            border-width: 2px;
            border-color: black;
            margin-bottom: 30px;
            }
            th{
            border: 1px solid black;
            padding: 8px;
            text-align: left;
            background-color: #4f97d1;
            }
            td {
            border: 1px solid black;
            padding: 8px;
            text-align: left;
            }
            tr:nth-child(even) {
            background-color: #d2e8fa;
            }
        </style>
        </head>
        <body style="font-family:calibri;background-color:white;">
        <p style="font-size: 24px;">OS Objects:</p>
        {{ table1 }}
        <p style="font-size: 24px;">Task Objects:</p>
        {{ table2 }}
        <b> {{str2}} </b>
        <p style="font-size: 24px;">Task's event Objects:</p>
        {{ table3 }}
        <p style="font-size: 24px;">Task' resource Objects:</p>
        {{ table4 }}
        <p style="font-size: 24px;">Event Objects:</p>
        {{ table5 }}
        <b> {{str3}} </b>
        <p style="font-size: 24px;">Resource Objects:</p>
        {{ table6 }}
        <b> {{str4}} </b>
        {{ priority_scheme_section }}
        {{ priority_scheme_table   }}
        {{ priority_scheme_title   }}
        <p style="font-size: 24px;">Alarm Objects:</p>
        {{ table7 }}
        <b> {{str5}} </b>
        <p style="font-size: 24px;">Interrupt Objects:</p>
        {{ table8 }}
        <b> {{str6}} </b>
        </body>
    </html>
    """)
        
    # Substitute the table data into the template to produce the final HTML
    html = template.render(table1=html_os_table,
                           table2=html_tasks_table,
                           str2=f"Total number of tasks: {OilTasks.OsTaskTotalNumber}",
                           table3=html_task_events_table,
                           table4=html_task_resources_table,
                           table5=html_events_table,
                           str3=f"Total number of events: {OilEvents.EventsTotalNumber}",
                           table6=html_resources_table,
                           str4=f"Total number of resources: {OilResources.ResourcesTotalNumber}",
                           table7=html_alarms_table,
                           str5=f"Total number of alarms: {OilAlarms.AlarmsTotalNumber}",
                           table8=html_interrupts_table,
                           str6=f"Total number of used interrupts: {OilInterrupts.InterruptsTotalNumber} and Total number of CPU interrupts : {OilOs.OsMaxVectorEntries}",
                           priority_scheme_section = html_priority_scheme_section,
                           priority_scheme_table   = html_priority_scheme_table,
                           priority_scheme_title   = html_priority_scheme_title
                           )
        
    # Generate HTML report
    HtmlReportFile = open(args.html_file, 'w', encoding='utf-8')
    HtmlReportFile.write(html)
    HtmlReportFile.close()

# Close the oil file
if (args.oil_file!= None):
    OilFileDescriptor.close()
