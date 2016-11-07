#!/bin/bash

var1=$1
var2=$2

if [[ -z $2 ]]
then
	echo "Второй аргумент пустой!"
	echo "Первый аргумент: $1"
fi

if [[ $var1==$var2 ]]
then
	echo "АРГУМЕНТЫ РАВНЫ!"
fi
echo "Arguments are: \$1=$1 \$2=$2"
