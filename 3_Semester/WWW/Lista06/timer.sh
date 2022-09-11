#!/bin/bash
var=$(netstat -n | grep "79.96.11.200")
while [ -n "$var" ]
do
  var=$(netstat -n | grep "79.96.11.200")
  sleep 1
done
printf "finished - empty"
