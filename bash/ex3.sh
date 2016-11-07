#!/bin/bash

if [[ $1 -eq 0  ]]
then
   echo "No students"
   exit
elif [[ $1 -eq 1  ]]
then
   echo "1 student"
   exit
elif [[ $1 -le 4  ]]
then
   echo "$1 students"
else
   echo "A lot of students"
fi


