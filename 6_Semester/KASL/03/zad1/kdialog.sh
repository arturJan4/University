#!/bin/bash

# mp3-player with dialog UI 
IFS=$'\n' # internal field separator

files=$(find . -name "*.mp3")

GEOMETRY="500x300+3600+300"

function addAllSongs()
{
  kdialogArgs=("0" "Search")
  kdialogArgs+=("1" "Search All")
  songs=()
  files_arr=()

  index=2
  for file in $files
  do
    info=("$(mp3info $file -p "%l (%a): %t")")
    songs+=($info)
    kdialogArgs+=("$index" "$info")
    files_arr+=($file)
    index=$((index+1))
  done
}

# search for empty song to reset
function searchSong() {
  SEARCH=$(kdialog --title "MP3play" --inputbox "Song title:")
  kdialogArgs=("0" "Search (current=$SEARCH)")
  kdialogArgs+=("1" "Search All")
  index=2
  for item in "${songs[@]}" 
  do
    # search term is substring of full name
    if [[ $item == *"$SEARCH"* ]]
    then
      kdialogArgs+=("$index" "$item")
    fi 
    index=$((index+1))
  done
  continue
}

addAllSongs
while :;
do
  # height, width, length of list
  SELECTED=$(kdialog --title "MP3play" --geometry 500x300+3600+300 --menu "Choose a song:" ${kdialogArgs[@]})
  if [[ "$SELECTED" == 0 ]]
  then
    searchSong
  fi

  if [[ "$SELECTED" == 1 ]]
  then
    addAllSongs
  fi

  # exit (ESC)
  if [[ $SELECTED == "" ]]
  then
    exit 0
  fi
  
  mplayer really-quiet ${files_arr[(($SELECTED-2))]} 2>/dev/null && continue

done