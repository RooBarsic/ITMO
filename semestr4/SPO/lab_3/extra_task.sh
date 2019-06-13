#!/bin/bash
fileName=$1 # имя файла
if ls -l $fileName; then
	if [ -n "$2" ]; then
		access=$2 # права на файл
	else 
		access='???' # дефолтные права на файл
	fi
	ls_result=$(ls -l $fileName)
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
	if [[ (${ls_result:1:1} = ${access:0:1} || ${access:0:1} = '?') && 
		(${ls_result:2:1} = ${access:1:1} || ${access:2:1} = '?') && 
		(${ls_result:3:1} = ${access:2:1} || ${access:2:1} = '?') ]]
		then
		echo $user
	fi
	if [[ (${ls_result:4:1} = ${access:0:1} || ${access:0:1} = '?') && 
		(${ls_result:5:1} = ${access:1:1} || ${access:2:1} = '?') && 
		(${ls_result:6:1} = ${access:2:1} || ${access:2:1} = '?') ]]
		then
		echo $(members $group)
	fi
	if [[ (${ls_result:7:1} = ${access:0:1} || ${access:0:1} = '?') && 
		(${ls_result:8:1} = ${access:1:1} || ${access:2:1} = '?') && 
		(${ls_result:9:1} = ${access:2:1} || ${access:2:1} = '?') ]]
		then
		echo $(compgen -u)
	fi
fi	
exit 0 #Выход с кодом 0 (удачное завершение работы скрипта)
