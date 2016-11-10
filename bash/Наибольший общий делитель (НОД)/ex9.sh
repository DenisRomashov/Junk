#!/bin/bash

echo "БУДЕМ ИСКАТЬ НОД!"

gcd ()
{  
  if [[ $a -eq $b  ]]
  then
     echo "GSD is $a "
     return
  elif [[ $a -lt b  ]]
  then
     m=$a
     max=$b
  else
     m=$b
     max=$a
  fi

  let "max+=1"
  for (( count=$m; count<$max; count++ ))
  do
    first=$(($m%$count))
    second=$(($max%$count))
    if [[ $first == 0 && $second == 0  ]]
    then
      result=$count
      echo "-------->"
    else
      result=1
  fi
  done
}

read a b #читаем введенные
#если ввели пустоту
if [[ $a -eq ""  ]]
then
  echo "bye"
  exit
fi

gcd $a $b
echo $result
