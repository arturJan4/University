#!/bin/bash

# mp3-player with dialog UI 
IFS=$'\n' # internal field separator

files=$(find . -name "*.mp3")

HEIGHT=16
WIDTH=80

function addAllSongs()
{
  dialogArgs=("Search" "")
  dialogArgs+=("Search All" "")
  songs=()
  files_arr=()

  index=1
  for file in $files
  do
    info=("$(mp3info $file -p "%l (%a): %t")")
    songs+=($info)
    dialogArgs+=("$index" "$info")
    files_arr+=($file)
    index=$((index+1))
  done
}

# search for empty song to reset
function searchSong() {
  SEARCH=$(dialog --title "MP3play" --inputbox "Song title:" $HEIGHT $WIDTH "" 3>&1 1>&2 2>&3)
  dialogArgs=("Search" "(current=$SEARCH)")
  dialogArgs+=("Search All" "")
  index=1
  for item in "${songs[@]}" 
  do
    # search term is substring of full name
    if [[ $item == *"$SEARCH"* ]]
    then
      dialogArgs+=("$index" "$item")
    fi 
    index=$((index+1))
  done
  continue
}

addAllSongs
while :;
do
  # height, width, length of list
  SELECTED=$(dialog --title "MP3play" --menu "Choose a song:" $HEIGHT $WIDTH 8 "${dialogArgs[@]}" 3>&1 1>&2 2>&3)
  if [[ "$SELECTED" == "Search" ]]
  then
    searchSong
  fi

  if [[ "$SELECTED" == "Search All" ]]
  then
    addAllSongs
  fi

  # exit (ESC)
  if [[ $SELECTED == "" ]]
  then
    exit 0
  fi
  
  # selected a song (index 1-n), continue for returning to menu
  if [ "$SELECTED" -gt 0 ] && [ "$SELECTED" -le $index ]
  then 
    mplayer really-quiet ${files_arr[(($SELECTED-1))]} 2>/dev/null && continue
  fi

done