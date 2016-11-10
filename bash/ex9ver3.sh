#!/bin/bash

gcd ()
{
  remainder=1  

  if [[ $# == 0 ]]
  then
    echo "bye"
    exit
  fi                  

  until [ "$remainder" -eq 0 ]
  do
    let "remainder = $a % $b"
    a=$b            
    b=$remainder
  done                           
  echo "GCD is $a"
}

while [[ True ]]; do
  read a b
  gcd $a $b
done