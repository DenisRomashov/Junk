#!/bin/bash

gcd()
{    
    a=$c
    b=$d


	if [[ $# == 0 ]]
	then
	  echo "bye"
	  exit
	fi
	if [[ $a -eq $b ]]; then
	  echo "GCD is $a"
	elif [[ $a -gt $b ]]; then
	  let "m = a - b"
	  gcd $m $b
	elif [[ $b -gt $a ]]; then
	  let "n = b - a"
	  gcd $a $n
	fi
}

while [[ True ]]; do
	read c d
	gcd $c $d
done