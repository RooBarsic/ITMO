#!/bin/bash
IFS="";
if [ "$1" != "" ]
then
	getent group $1
else 
	echo "No argument passed. Please try again!"
fi
exit 0
