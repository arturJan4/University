#!/bin/bash

# list oldest files that need to be delete in given directory
# to fit the limit given as first argument

if [ $# -lt 2 ]
then
  echo "Usage: filerotate <limit> <path>"
  exit 1
fi

IFS=$'\n'

# don't follow links (-L option)
# find recursively
# %Tk (last modification in format k), k==@ -> seconds
# %s -> size in bytes
# %p -> file name
FILES=$(find "$2" -type f -printf "%T@ %s %p\n" | sort)
sum=0
for file in $FILES
do
  sum=$(( $sum + $(echo $file | awk '{ print $2 }') ))
done

# echo $sum
for file in $FILES
do
  if [[ $sum -gt $1 ]]
  then
    echo $file
    sum=$(( $sum - $(echo $file | awk '{ print $2 }') ))
  else
    break
  fi
done
