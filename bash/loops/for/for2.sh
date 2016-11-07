#!/bin/bash
for str in a , b , c_d
do
  echo "$str<--- start"  
  if [[ $str > "c" ]]
  then
    echo "----->>>$str"
    continue
  fi
  echo "finish"
done
