#!/bin/bash
m=5
max=10

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

  
echo $result

