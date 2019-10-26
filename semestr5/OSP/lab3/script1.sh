#!/bin/bash
if [ -z $1 ]
then
   echo "Give this hard worker sleep!!"
   echo "He forgot the file name."
   exit 1
fi
fileName=$1 # имя файла
vara=$(ls $fileName)
if [ "$vara" != "" ]
then
    if [ -n "$2" ]; then
      access=$2 # права на файл
    else
      access='???' # дефолтные права на файл
    fi
    ls_result=$(ls -nd $fileName)
    i=0
    for var in $ls_result; do
      if [ $i -eq 2 ]; then
        user=$var
      fi
      if [ $i -eq 3 ]; then
        group=$var
      fi
      i=$(($i+1))
    done
    users_of_group=$(getent passwd | grep ".*:.*:.*:$group" | awk -F":" '{print $1}')
    if [[ (${ls_result:1:1} = ${access:0:1} || ${access:0:1} = '?') &&
      (${ls_result:2:1} = ${access:1:1} || ${access:2:1} = '?') &&
      (${ls_result:3:1} = ${access:2:1} || ${access:2:1} = '?') ]]
      then
      echo "Owner : $user"
    fi
    if [[ (${ls_result:4:1} = ${access:0:1} || ${access:0:1} = '?') &&
      (${ls_result:5:1} = ${access:1:1} || ${access:2:1} = '?') &&
      (${ls_result:6:1} = ${access:2:1} || ${access:2:1} = '?') ]]
      then
      echo "members of group $group , except owner."
      for arg in $users_of_group; do
        if [ arg != user ]; then
            echo "$arg"
        fi
      done
    fi
    if [[ (${ls_result:7:1} = ${access:0:1} || ${access:0:1} = '?') &&
      (${ls_result:8:1} = ${access:1:1} || ${access:2:1} = '?') &&
      (${ls_result:9:1} = ${access:2:1} || ${access:2:1} = '?') ]]
      then
      echo "Other users, except of Owner and members of group $group."
      echo $(compgen -u)
     fi
fi
exit 0 #Выход с кодом 0 (удачное завершение работы скрипта)
