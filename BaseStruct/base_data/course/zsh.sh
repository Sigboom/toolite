#!/bin/bash

num=0
while [ $num -lt 10 ]
do
    let num+=1
    echo $num
done

for i in {1..10}
do
    echo $i
done
