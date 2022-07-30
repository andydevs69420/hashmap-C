#!/bin/bash

############ FOR LINUX ONLY ############
if [[ $(ls . | grep bin) != "bin" ]];
then
    mkdir bin;
fi

gcc src/main.c src/hashmap.c -o bin/main && bin/main;