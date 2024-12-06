
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <climits>
#include <unordered_map>

struct Cell{
    int r;
    int c;
    int distance;
    char inDir;

    bool operator<(const Cell& other)
    {
        return distance < other.distance;
    }
};

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day17input1.txt";
    if(argc == 3)
    {
        std::string DAY = argv[1];
        std::string INPUT = argv[2];

        FILENAME = "test/day"
        + DAY
        + "input"
        + INPUT
        + ".txt";
    }


    std::ifstream file(FILENAME);
    std::string line;


    while(std::getline(file, line))
    {
        std::cout<< line <<std::endl;

    }

}


