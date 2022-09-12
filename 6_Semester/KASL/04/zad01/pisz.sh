#!/usr/bin/bash

exec {MYFD}> myfile.txt
echo "My" >& $MYFD
echo "long" >& $MYFD
echo "message" >& $MYFD
exec {MYFD}>&-