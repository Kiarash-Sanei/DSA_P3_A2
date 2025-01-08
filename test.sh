#!/bin/bash

n=$(find . -maxdepth 1 -name "*.c" | wc -l)
for ((i=1; i<=$n; i++))
do
    echo "***************************"
    echo "---------------------------"
    gcc $i.c -o $i.out -lm
    cd ./tests
    m=$((1))
    for file in *.txt
    do
        echo "testing $i, testcase $m:"
        start=$(date +%s%N)
        ../$i.out < $file
        end=$(date +%s%N)
        time_ns=$((end - start))
        time_ms=$(echo "scale=3; $time_ns / 1000000" | bc)
        echo "execution time: $time_ns ns"
        echo "execution time: $time_ms ms"
        ((m++))
        echo "---------------------------"
    done
    cd ..
    rm $i.out
    echo "***************************"
done