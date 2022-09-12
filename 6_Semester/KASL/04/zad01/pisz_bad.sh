#!/usr/bin/bash


MYFILE=myfile_b.txt
echo -n "My " >> "$MYFILE"
echo -n "long " >> "$MYFILE"
echo "message" >> "$MYFILE"