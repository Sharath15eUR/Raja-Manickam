#!/bin/bash

# Get the PID, memory usage, and name of the process with the highest memory usage
PROCESS_INFO=$(ps -eo pid,%mem,comm --sort=-%mem | awk 'NR==2 {print $1, $2, $3}')
PID=$(echo $PROCESS_INFO | awk '{print $1}')
MEMORY=$(echo $PROCESS_INFO | awk '{print $2}')
PROCESS_NAME=$(echo $PROCESS_INFO | awk '{print $3}')

# Printing the  formation to the terminal and save it to a file 
{
  echo "Process with highest memory usage:"
  echo "PID: $PID"
  echo "Memory Usage: $MEMORY%"
  echo "Process Name: $PROCESS_NAME"
} | tee process_info.txt

# Terminate the process
kill -9 $PID

# Informing the user that the process has been terminated
echo "Process $PID ($PROCESS_NAME) has been terminated." | tee -a process_info.txt
