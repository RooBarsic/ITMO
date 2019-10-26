#!/bin/bash
  2 # checking input parameters
  3 if [ -z $1 ]
  4 then
  5    echo "Give this hard worker sleep!!"
  6    echo "He forgot the username."
  7    exit 1
  8 fi
  9 
 10 # checking user availability
 11 if ! [ -n "$(getent passwd $1)" ]
 12 then
 13    echo "User I can't find that you are looking for"
 14    exit 1
 15 fi
 16 param_user=$1
 17 
 18 param_user_id=$(getent passwd $param_user | awk -F":" '{print $3}')
 19 
 20 for file in $(ls)
 21 do
 22     file_le_result=$(ls -l $file)
 23 
 24     if [ ${file_le_result:0:1} == '-' ]
 25     then
 26             file_user_id=$(ls -nd "$file" | awk '{ print $3 }')
 27             file_group_id=$(ls -nd "$file" | awk '{ print $4 }')
 28     
 29             # is user - is file owner
 30           if [ "$param_user_id" == "$file_user_id" ]
 31           then
 32                 echo "$file ( by owner rules )"
 33                 continue
 34           fi
 35 
 36           # checking for others
 37           if [ ${file_le_result:7:1} == 'r' ]
 38           then
 39                 echo "$file ( by other rules )"
 40                 continue
 41           fi
 42 
 43           # Checking for the group
 44           users_of_file_group=$(getent passwd | grep ".*:.*:.*:$file_group_id" | awk -F":" '{print $1}')
  46           for group_user in $users_of_file_group;
 47           do
 48                 if [ "$group_user" == "$param_user" ]
 49                 then
 50                 echo "$file ( by group rules )"
 51                 break
 52                 fi
 53           done
 54       fi
 55 done
 56 exit 0
