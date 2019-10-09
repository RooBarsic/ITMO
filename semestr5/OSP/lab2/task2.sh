#!/bin/bash
IFS="";
if [ "$1" != "" ]
then
	usersInfo=$(getent group $1)
	colonsNum=0
	for (( i=0; i<${#usersInfo}; i++ )); do
	  if [ $colonsNum == 3 ]
	  then
	  	echo "${usersInfo:$i}"
	  	break
	  fi
	  if [ "${usersInfo:$i:1}" == ":" ]
	  then
	  	colonsNum=$(($colonsNum+1))
	  fi
	done
else 
	echo "No argument passed. Please try again!"
fi
exit 0
