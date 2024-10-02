import sys
import re
import os
from jinja2 import Template
from tabulate import tabulate

# Globals
ResourcesTotalNumber = 0
ResourcesList = []


def OilResourcesParser(args, Oilfile):
    
    global ResourcesTotalNumber

    # Search for resource names and properties
    resource_pattern      = re.compile(r"RESOURCE\s+(\w+)\s*\{([\s\S]*?)\};", re.MULTILINE)
    resource_prop_pattern = re.compile(r"RESOURCEPROPERTY\s*=\s*(\w+);")
    resources             = resource_pattern.findall(Oilfile)

    # Parse the resource list
    for resource in resources:
        resource_name, resource_properties = resource
        resource_prop_match = resource_prop_pattern.search(resource_properties)
        resource_prop       = resource_prop_match.group(1) if resource_prop_match else None

        if resource_prop != "STANDARD" :
            print(f"The resource {resource_name} must have \"STANDARD\" as property !")
            exit()
        
        ResourcesTotalNumber += 1
        # Format: [Name, prio, property, mask]
        ResourcesList.append([resource_name, 0, resource_prop, 0])


