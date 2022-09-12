#!/bin/bash

while true; do
    str=$(free --mega | awk 'NR==2 {print $4 " MB"}' )

    echo "Free memory: $str" >> /tmp/mylog.fifo
    sleep 2
done