#!/bin/bash

again=yes
while [[ "$again" = "yes" || "$again" = "y" ]]
do
  echo "Please enter a name:"
  read name
  echo "The name entered is name $name"

  echo "Do you wish a continue(y/n)"
  read again
done
