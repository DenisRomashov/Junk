#!/bin/bash
gcd () {
#Without recursion
m=$1
n=$2
#while ((m-n))
#do
    #if [ $m -gt $n ]
    #then
    #    ((m-=n))
   # else
  #      ((n-=m))
 #   fi
#done
# Other variant with recursion:
 if [ $1 -gt $2 ]
 then
     gcd $2 $(($1-$2))
     echo "GCD is $m"
 elif [ $1 -eq $2 ]
 then
     echo "GCD is $1"
 else
     gcd $1 $(($2-$1))
 fi
}
read m n
while ((m+n))
do
    gcd $m $n
    read m n
done
echo "bye"