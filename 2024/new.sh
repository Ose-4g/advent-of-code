#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    exit
fi

DAY=$1

echo "
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){

    std::string FILENAME = \"test/day${DAY}input1.txt\";
    if(argc == 3)
    {
        std::string DAY = argv[1];
        std::string INPUT = argv[2];

        FILENAME = \"test/day\"
        + DAY
        + \"input\"
        + INPUT
        + \".txt\";
    }


    std::ifstream file(FILENAME);
    std::string line;


    while(std::getline(file, line))
    {
        std::cout<< line <<std::endl;

    }

}

" > day$DAY.cpp

touch test/day${DAY}input{1,2,3,4}.txt


