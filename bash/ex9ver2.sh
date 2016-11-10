#!/bin/bash

gcd()
{    
	if [[ $# == 0 ]]
	then
	  echo "bye"
	  exit
	fi
	if [[ $a == $b ]]; then
	  echo "GCD is $a"
	elif [[ $a > $b ]]; then
	  let "m = a - b"
	  gcd $m $b
	elif [[ $b > $a ]]; then
	  let "n = b - a"
	  gcd $a $n
	fi
}

while [[ True ]]; do
	read a b
	gcd $a $b
done