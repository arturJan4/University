#!/bin/bash

# mp3-player with dialog UI 
IFS=$'\n' # internal field separator

files=$(find . -name "*.mp3")

HEIGHT=400
WIDTH=800

function addAllSongs()
{
  zenityArgs=("Search" "")
  zenityArgs+=("Search All" "")
  songs=()
  files_arr=()

  index=1
  for file in $files
  do
    info=("$(mp3info $file -p "%l (%a): %t")")
    songs+=($info)
    zenityArgs+=("$index" "$info")
    files_arr+=($file)
    index=$((index+1))
  done
}

# search for empty song to reset
function searchSong() {
  SEARCH=$(zenity --title "MP3play: Search" --forms --add-entry="Type title/artist/album" --height=$HEIGHT --width=$WIDTH)
  zenityArgs=("Search" "(current=$SEARCH)")
  zenityArgs+=("Search All" "")
  index=1
  for item in "${songs[@]}" 
  do
    # search term is substring of full name
    if [[ $item == *"$SEARCH"* ]]
    then
      zenityArgs+=("$index" "$item")
    fi 
    index=$((index+1))
  done
  continue
}

addAllSongs
while :;
do
  # height, width, length of list
  SELECTED=$(zenity --title "MP3play" --list --column="Number" --column="Description" --height=$HEIGHT --width=$WIDTH "${zenityArgs[@]}" &)
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