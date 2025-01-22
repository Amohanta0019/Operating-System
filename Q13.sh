#!/bin/bash

# Display processes with sleeping status
echo "Processes with Sleeping Status (S):"
ps -eo pid,comm,state | awk '$3 == "S" {print "PID: "$1", Command: "$2", Status: "$3}'
