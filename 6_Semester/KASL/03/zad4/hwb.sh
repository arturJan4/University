#!/usr/bin/bash

CAPITALIZE=false
COLOR='auto'
GREETING="Hello,"
CURRENT_COLOR='\033[0;33m' # yellow
NC='\033[0m' # no color
WORLD=false

function hello() {
    i=$1
    
    # this shouldn't happen but just in case
    # don't print options starting from '-'
    if [[ $(echo $i | grep "^-") != "" ]]
    then
      return
    fi
    
    if $CAPITALIZE
    then
      i=${i^}
    else
      i=$i
    fi
        
    case $COLOR in
      'always') 
        echo -e "$GREETING ${CURRENT_COLOR}$i${NC}!";;
      'auto') 
        if [ -t 1 ]; then 
          echo -e "$GREETING ${CURRENT_COLOR}$i${NC}!"; 
        else 
          echo "$GREETING $i!"; 
        fi;;
      'never') 
        echo "$GREETING $i!";;
    esac
}


function help() {
	cat <<- _end_text 
	hwb - the ultimate greeter"
	
	Usage: hwb [OPTIONS] {ARGS...}"
  Where ARGS are people to greet

	Options:
	-c --capitalize 				= capitalize the string
	-g text --greeting=text = the first part of the greeting
	-h --help   					  = prints help (this message)
	-v --version 						= current version and license
	-w --world 							= prints an additional line with "world" argument
	--color=[always|auto|never] (default auto) = colorize the output

	Example usage:
	./hwb --color=never artur sample
	./hwb -w --greeting="HI" -c artur dawid
_end_text
    exit 0
}

function version() {
  cat <<- _end_text 
	Version 0.1337
	2022 Artur Jankowski"
_end_text
	exit 0
}

# : - required options
SHORT_OPTIONS=(
"c,\
g:,\
h,\
v,\
w"
)

LONG_OPTIONS=(
"capitalize,\
color:,\
greeting:,\
help,\
version,\
world"
)

# join string throug ","
join () {
  local IFS="$1"
  shift
  echo "$*"
}

function parseOpts() {
    OPTS=$(getopt -l $LONG_OPTIONS -o $SHORT_OPTIONS -n 'hwb' -- "$@")

    if [ $? -ne 0  ]; then
      # getopt failed
      echo "Invalid arguments. Use '$0 --help' to learn more."
      exit 1
    fi

    if [ $# -eq 0 ]; then
      echo "$0 needs more arguments. Use '$0 --help' to learn more."
      exit 1
    fi

    eval set -- "$OPTS"

    while true
    do
        case $1 in
            -h | --help) 
              help 
              shift;;
            -v | --version) 
              version 
              shift;;
            --color) 
              COLOR="$2" 
              shift 2;;
            -g | --greeting) 
              GREETING="$2"; 
              shift 2;;
            -c | --capitalize) 
              CAPITALIZE=true
              shift;;
            -w | --world) 
              WORLD=true; 
              shift;;
            --) break;;
        esac
    done

    # loop through arguments
    for arg do
      hello $arg
    done
    
    if $WORLD; then
      hello "world"
    fi

    exit 0
}

parseOpts $@
