#!/usr/bin/bash

exec {MYFD}>> myfile_a.txt
echo "My" >& $MYFD
echo "long" >& $MYFD
echo "message" >& $MYFD
exec {MYFD}>&-