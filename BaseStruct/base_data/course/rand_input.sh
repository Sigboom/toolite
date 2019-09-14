#/bin/bash

if [ "$1" != "" ]; then 
    rm $1
    for i in {1..10} 
    do
        echo $(($RANDOM % 4)) $(($RANDOM % 10)) >> $1
    done
    echo '$1 is not empty. and $1 is '$1
fi

