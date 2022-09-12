#!/usr/bin/bash

# no passed argument
if [ $# -ne 1 ] 
then
  echo "Usage: $0 [sleep time in seconds]"
  exit
fi

while IFS= read -r line; 
do
  printf '[%s] %s\n' "$$" "$line"
  sleep $1
done

