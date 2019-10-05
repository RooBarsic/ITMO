#!/bin/bash
err="lab1_err"
comand=1

function my_error {
         date >> "$err" 2>>"/dev/null" || echo "Can't create file. Mabye access denied."
         echo "An error has occurred. Detailed information can be found in the file. `pwd`/$err" 1>&2 
         echo -e '\n' >> "$err" 2>>"/dev/null" 
}

IFS="";
flag=1

while [ $flag == 1 ]
do
        echo "Write: 1 -- to print path to current directory.
       2 -- to change current directory
       3 -- to display the contents of the current directory
       4 -- to create a soft link to the file
       5 -- to delete symbolic link to file
       6 -- to exit"
    
    read comand

    case "$comand" in
        1) pwd ;;
                2) echo "write path to directory"
                   read path
                   cd "$path" 2>>"$err" || my_error
                ;;
                3) ls ;;
                4) echo "write path to origin file" 2>>"$err" || my_error
                read originFilePath 2>>"$err" || my_error
                echo "write path to directory for creating link" 2>>"$err" || my_error
                read linkPath 2>>"$err" || my_error
                echo "write the name of link" 2>>"$err" || my_error
                read linkName 2>>"$err" || my_error
                ln -s $originFilePath $linkPath"/"$linkName 2>>"$err" || my_error
                ;;
                5) echo "write path to deleting link"
                read linkPath
                if [[ -L "$linkPath" ]] 
                then 
                        rm $linkPath 2>>"$err" || my_error
                else
                        echo "Some Error. Look in " $err
                        echo \"$linkPath " - this is not soft link" \" >>"$err" || my_error
                fi
                ;;
                6) flag=0 
                        echo "Bue come again"
                ;;
        esac
done
