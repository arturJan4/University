#!/bin/bash

# Erastotenes sieve (get upper bound from command-line)
# usage: ./primes 500

# check arguments
if [ $# -eq 1 ]
then
  MAX=$1
elif [ $# -eq 0 ]
then
  MAX=1000
else
  echo "Usage: ./primes <upper_bound>"
  exit 1
fi

# array
PRIMES=(2)
i=1
n=3

while [ $n -le $MAX ]
do
  j=0
  # ${PRIMES[$j]} and $(())
  while [ $((${PRIMES[$j]}*${PRIMES[$j]})) -le $n ]
  do
    if [ $(($n%${PRIMES[$j]})) -eq 0 ]
     # https://linuxize.com/post/bash-break-continue/
    then
      n=$((n+1))
      continue 2
    else
     j=$((j+1))
    fi
  done
  PRIMES[((i++))]=$n
  n=$((n+1))
done

echo ${PRIMES[@]}
