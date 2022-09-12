#!/bin/bash

PIPE="/tmp/mylog.fifo"
if ! [[ -p $PIPE ]]
then
  mkfifo $PIPE
fi

while true
do
    while read -r LINE
    do
    if [ "$LINE" != "" ] 
      then
      timestamp="$(date +'%Y-%m-%d %H:%M:%S')"
      echo "($timestamp) $LINE"
    fi
    done < $PIPE
done