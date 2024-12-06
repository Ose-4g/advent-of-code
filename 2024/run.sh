#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    exit
fi

DAY=$1
INPUT=$2


g++ -std=c++11 -o run.tsk day$DAY.cpp && ./run.tsk $DAY $INPUT
