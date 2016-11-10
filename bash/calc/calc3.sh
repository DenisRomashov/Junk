#!/bin/bash
while [[ 0 -eq 0 ]]; do
read arg1 fun arg2
        if [[ "$arg1" = "exit" ]]; then
                echo "bye"
                exit
        elif [[ -n $arg1 &&  $fun && $arg2 ]]; then
                let "res=${arg1}${fun}${arg2}"
                echo "$res"
                continue
        else
                echo "error"
                exit
        fi
done