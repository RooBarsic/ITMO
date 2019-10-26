#!/bin/bash
# checking input parameters
if [ -z $1 ]
then
   echo "Give this hard worker sleep!!"
   echo "He forgot the username."
   exit 1
fi

# checking user availability
if ! [ -n "$(getent passwd $1)" ]
then
   echo "User I can't find that you are looking for"
   exit 1
fi
param_user=$1

param_user_id=$(getent passwd $param_user | awk -F":" '{print $3}')

for file in $(ls)
do
    file_le_result=$(ls -l $file)

    if [ ${file_le_result:0:1} == '-' ]
    then
        file_user_id=$(ls -nd "$file" | awk '{ print $3 }')
        file_group_id=$(ls -nd "$file" | awk '{ print $4 }')

        # is user - is file owner
      if [[ (${file_le_result:1:1} == 'r') &&
            ("$param_user_id" == "$file_user_id") ]]
      then
         echo "$file ( by owner rules )"
      elif [ "$param_user_id" != "$file_user_id" ]
      then
          users_of_file_group=$(getent passwd | grep ".*:.*:.*:$file_group_id" | awk -F":" '{print $1}')
          is_user_of_group=0
          for group_user in $users_of_file_group;
          do
                if [ "$group_user" == "$param_user" ]
                then
                    is_user_of_group=1
                    break
                fi
          done
          if [[ (${file_le_result:4:1} == 'r') &&
                ("$is_user_of_group" == '1') ]]
          then
                echo "$file ( by group rules )"
          elif [ "$is_user_of_group" == '0' ]
          then
                if [ ${file_le_result:7:1} == 'r' ]
                then
                      echo "$file ( by other rules )"
                      continue
                fi
          fi
      fi
    fi
done
exit 0
