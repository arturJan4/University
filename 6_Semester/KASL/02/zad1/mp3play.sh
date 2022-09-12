#!/bin/bash

# mp3-player using file metadata
IFS=$'\n' # internal field separator

files=$(find . -name "*.mp3")

for file in $files
do
  info+=("$(mp3info $file -p "%l (%a): %t")")
  files_arr+=($file)
done

# echo ${#info[@]}
# {array[$arrayindex]}

# PS3 – Prompt used by “select” inside shell script
# select - $REPLY -> answer
PS3="Choose a number to play> "
select file in ${info[@]}
do
  if [[ $REPLY -ge 1 && $REPLY -le ${#info[@]} ]]
  then
    mplayer really-quiet ${files_arr[(($REPLY-1))]} 2>/dev/null
  else
    echo "Wrong answer."
  fi
done