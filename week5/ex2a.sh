#!/usr/bin/env bash

for i in {1..5000} \
do
    while true;
    do
        if `ln "ex2.txt" "ex2.txt.lock"`;  then
            num=$(tail -n 1 "ex2.txt")
            echo "$(($num + 1))" >> "ex2.txt"
            rm "ex2.txt.lock"
            break
        fi
    done

done 