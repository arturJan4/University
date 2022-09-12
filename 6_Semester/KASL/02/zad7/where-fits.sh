#!/bin/bash

# list which mounted filesystems can fit files or directories 
# passed as runtime arguments, usage: where-fits.sh <filename> *

# du(1) for file size
# df(1) for mounted filesystems

IFS=$'\n'

if [ $# -eq 0 ]
then
  echo "Usage: where-fits.sh <filename> *"
  exit 1
fi

# -s flag -> only one count for one given argument (and not recursive search)

# can use awk instead
sum=0
while [ $# -ne 0 ]
do
  sum=$(( $sum + $(du -s "$1" | cut -f1)))
  shift
done

echo "total size: $sum bytes"
# can use -v flag here instead for variables (code injection)
df | tail -n +2 | awk '{if ('"$sum"'<=$4) print $6;};'

# dd if=/dev/zero of=output.data bs=1M count=24