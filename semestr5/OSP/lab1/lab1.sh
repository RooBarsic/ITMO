#!/bin/bash
err="lab1_err"
comand=1

function my_error {
	 date >> "$err" 2>>"/dev/null" || echo "Can't create file. Mabye access denied."
	 echo "An error has occurred. Detailed information can be found in the file. `pwd`/$err" 1>&2 
	 echo -e '\n' >> "$err" 2>>"/dev/null" 
}

while [ $comand != 6 ]
do
	echo "Write: 1 -- to print path to current directory.
       2 -- to change current directory
       3 -- to display the contents of the current directory
       4 -- to create a soft link to the file
       5 -- to delete symbolic link to file
       6 -- to exit"
    
    read comand

    if [ $comand == 1 ]
    then
    	pwd
    	continue
    fi

    if [ $comand == 2 ]
    then
    	echo "write path to directory"
		read path
		cd $path 2>>"$err" || my_error
		continue
	fi

	if [ $comand == 3 ]
	then
		ls
		continue
	fi

	if [ $comand == 4 ]
	then
		echo "write path to origin file" 2>>"$err" || my_error
		read originFilePath 2>>"$err" || my_error
		echo "write path to directory for creating link" 2>>"$err" || my_error
		read linkPath 2>>"$err" || my_error
		echo "write the name of link" 2>>"$err" || my_error
		read linkName 2>>"$err" || my_error
		ln -s $originFilePath $linkPath"/"$linkName 2>>"$err" || my_error
		continue
	fi

	if [ $comand == 5 ]
	then
		echo "write path to deleting link"
		read linkPath
		if [[ -L "$linkPath" ]] 
			then 
				rm $linkPath 2>>"$err" || my_error
			else
				echo \"$linkPath " - this is not soft link" \" >>"$err" || my_error
			fi
	fi

	if [ $comand < 1 or 6 < $comand ]
	then
		echo "Wrong comand number" >>"$err" 2>>"$err" || my_error

done
