#!/bin/bash

PID=$(ps -eo pid,%mem --sort=-%mem | awk 'NR==2 {print $1}') #fetching the process with high memory usage 

if [ -n "$PID" ]; then
    kill -9 $PID
    if [ $? -eq 0 ]; then #checks if exit status of last command is 0(successful)
        echo "process $PID has been terminated"
    else
        echo "Process $PID not terminated"
    fi
else
    echo "process not found "
fi
