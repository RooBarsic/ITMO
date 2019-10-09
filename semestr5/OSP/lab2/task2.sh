#!/bin/bash
if [ "$1" != "" ]
then
  lsOut=$(ls -t)
  for file in $lsOut; do 
    va1=$(ls -l $file)
    flag=0
    link=""
    last=""
    for var in $va1; do
      if [ "$flag" == 1 ]
        then
        if [ "$var" == "$1" ]
    	  then
    	    echo "$link"
    	fi
      fi
      if [ "$var" == "->" ]
    	then
    	  flag=1
    	  link="$last"
      fi
      last="$var"
    done
  done
else 
  echo "No argument passed. Please try again!"
fi
exit 0


