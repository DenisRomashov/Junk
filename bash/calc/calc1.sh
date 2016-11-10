#!/bin/bash

calc()
{
  if [[  "$1" == "exit" ]]
  then
		echo "bye"
		exit
  else
    case $operation in
  	  "+")
	  	  let "result = value1 + value2"
		  echo $result
		  ;;
	  "-")
		  let "result = value1 - value2"
		  echo $result
		  ;;
	  "*")
		  let "result = value1 * value2"
		  echo $result
		  ;;
	  "/")
		  let "result = value1 / value2"
		  echo $result
		  ;;
	  "%")
		  let "result = value1 % value2"
		  echo $result
		  ;;
	  "**")
		  let "result = value1 ** value2"
		  echo $result
		  ;;
	  *) 
		  echo "error"
		  exit
    esac
   fi
 }

while [[ True ]]; do
	read value1 operation value2
	calc $value1 $operation $value2
done