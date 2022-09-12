#!/bin/bash

IFS=$'\n' # internal field separator

# $@ -> all positional parameters -> expand to separate strings
print_helper() {
  echo $@ | awk '{print\
  "Device:            " $1 "\n"\
  "Filesystem type:   " $3 "\n"\
  "Mount options:     " $4 "\n"\
  "Dump freqency:     " $5 "\n"\
  "Fsck pass number:  " $6}'
}

# no passed arguments
if [ $# -eq 0 ] 
then
  # non-comment lines
  lines=$(cat /etc/fstab | grep "^[^#]")
  for line in $lines 
  do
    print_helper $line
    echo
  done
else 
  if [ $1 = "/" ] 
  then
    argg=$1
  else
  # http://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Parameter-Expansion
    argg=$(echo ${1%/})
  fi
  line=$(cat /etc/fstab | grep "^[^#]*$argg ")
  print_helper $line
fi


