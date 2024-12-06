
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void print2dArr(std::vector<std::vector<char> >& map)
{
    for(auto v: map)
    {
        for(char c: v)
        {
            std::cout<<c<<" ";
        }
        std::cout<<std::endl;
    }
}
int main(int argc, char* argv[]){

    std::string FILENAME = "test/day10input1.txt";
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

    std::vector<int> colsWithGalaxies;
    std::vector<std::vector<char> > map;

    int r = 0;
    while(std::getline(file, line))
    {
        std::cout<< line <<std::endl;

        std::vector<char> row;

        bool rowHasGalaxy = false;


        int n = line.length();
        for(int i = 0; i<n; ++i)
        {
            if(line[i]=='#')
            {
                colsWithGalaxies.push_back(i);
                rowHasGalaxy = true;
            }
            row.push_back(line[i]);
        }

        map.push_back(row);

        if(!rowHasGalaxy)
        {
            map.push_back(std::vector<char>(row.size(), '.'));
        }

    }

    for(int i: colsWithGalaxies)
    {
        std::cout<<"col "<<i<<std::endl;
    }

}


