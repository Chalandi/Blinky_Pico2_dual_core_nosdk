import sys
import re
import os
from jinja2 import Template
from tabulate import tabulate

# Globals
OsTaskTotalNumber   = 0
OsTasksList         = []
osTaskEvents        = []
osTaskResources     = []

# Globals used for formating data for print function
OsTaskEventPre    = []
OsTaskEventL      = []
OsTaskResourcePre = []
OsTaskResourceL   = []

def OilTaskParser(args, Oilfile):
    
    global OsTaskTotalNumber, OsTasksList
    
    # Search for task names and properties
    task_pattern             = re.compile(r"TASK\s+(\w+)\s*\{([\s\S]*?)\};", re.MULTILINE)
    Task_type_pattern        = re.compile(r"TYPE\s*=\s*(\w+);")
    Task_schedule_pattern    = re.compile(r"SCHEDULE\s*=\s*(\w+);")
    Task_priority_pattern    = re.compile(r"PRIORITY\s*=\s*(\w+);")
    Task_activation_pattern  = re.compile(r"ACTIVATION\s*=\s*(\w+);")
    Task_autostart_pattern   = re.compile(r"AUTOSTART\s*=\s*(\w+);")
    Task_stacksize_pattern   = re.compile(r"StackSize\s*=\s*(\w+);")
    Task_event_pattern       = re.compile(r"EVENT\s*=\s*(\w+);")
    Task_resource_pattern    = re.compile(r"RESOURCE\s*=\s*(\w+);")
    
    # find all tasks pattern
    tasks = task_pattern.findall(Oilfile)

    for task in tasks:
        # Get the task name and the task properties
        Task_name, task_properties = task

        # Count the number of tasks
        OsTaskTotalNumber += 1

        # Search for task properties value
        Task_type_match       = Task_type_pattern.search(task_properties)
        Task_schedule_match   = Task_schedule_pattern.search(task_properties)
        Task_priority_match   = Task_priority_pattern.search(task_properties)
        Task_activation_match = Task_activation_pattern.search(task_properties)
        Task_autostart_match  = Task_autostart_pattern.search(task_properties)
        Task_stacksize_match  = Task_stacksize_pattern.search(task_properties)

        Task_type       = Task_type_match.group(1) if Task_type_match else None
        Task_schedule   = Task_schedule_match.group(1) if Task_schedule_match else None
        Task_priority   = Task_priority_match.group(1) if Task_priority_match else None
        Task_activation = Task_activation_match.group(1) if Task_activation_match else None
        Task_autostart  = Task_autostart_match.group(1) if Task_autostart_match else None
        Task_stacksize  = Task_stacksize_match.group(1) if Task_stacksize_match else None
        
        # Update the tasks list
        #                     0     ,   1      ,    2         ,      3       ,      4         ,       5,            6,           7
        OsTasksList.append([Task_name, Task_type, Task_schedule, Task_priority, Task_activation, Task_autostart, Task_stacksize, 0])

        # Search for task's events
        Task_event_match = Task_event_pattern.findall(task_properties)
        osTaskEvents.append(Task_event_match)

        for OsTaskEvent in osTaskEvents :
            OsTaskEventPre = [Task_name, '\n'.join(OsTaskEvent)]
        OsTaskEventL.append(OsTaskEventPre)         
  
        # Search for task's resources
        Task_resource_match = Task_resource_pattern.findall(task_properties)
        osTaskResources.append(Task_resource_match)

        for OsTaskResource in osTaskResources :
            OsTaskResourcePre = [Task_name, '\n'.join(OsTaskResource)]
        OsTaskResourceL.append(OsTaskResourcePre)  

