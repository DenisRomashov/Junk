#!/bin/bash

validate()
{
    for i in + - * / % **
    do
        if [[ $i == $1 ]]
        then
            result="true"
        fi
    done
}

calculate()
{
    result=""
    validate $operator
    if [[ $1 == "exit" ]]
    then
        echo "bye"
        exit
    fi
    if [[ ( $# != 3 ) || ( $result != "true" ) ]]
    then
        echo "error"
        exit
    fi
    let "c = $1 $2 $3"
    echo "$c"
}


while [ true ] 
do
    read a operator b
    calculate $a "$operator" $b
done


