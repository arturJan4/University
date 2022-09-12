#!/bin/bash

# count available entropy
while true
do
  left=$(cat /proc/sys/kernel/random/entropy_avail)
  total=$(cat /proc/sys/kernel/random/poolsize)
  printf "Available entropy: $left/$total. Press any key to exit! \r"
  
  # read default -> only "enter"
  # returns zero on success
  # -n -> how many characters to read
  # -s -> hide user input
  # -r -> raw string (no backslash escapes)
  # -t -> timeout (needed for live update)

  if read -n 1 -sr -t 0.1
  then
    break
  fi
done

# help read
# -t time out and return failure if a complete line of input is not read within TIMEOUT seconds.
# arrows workaround
read -N 2 -t 0.01 
echo