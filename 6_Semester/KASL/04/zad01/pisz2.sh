#!/usr/bin/bash

exec {MYFD}> myfile.txt
echo "My" >& $MYFD
echo "rather" >& $MYFD
echo "long" >& $MYFD
echo "message" >& $MYFD
echo "." >& $MYFD
exec {MYFD}>&-