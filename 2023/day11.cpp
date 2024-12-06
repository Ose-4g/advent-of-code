
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

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

void insertColumns(std::vector<std::vector<char> >& map, int col)
{
    int n = map.size();

    for(int i = 0; i < n; ++i)
    {
        map[i].insert(map[i].begin()+col, '.');
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

    std::unordered_set<int> colsWithGalaxies;
    std::unordered_set<int> rowsWithoutGalaxies;
    std::vector<std::vector<char> > map;

    int r = 0;
    std::vector<std::pair<int,int> > galaxies;

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
                colsWithGalaxies.insert(i);
                rowHasGalaxy = true;
                galaxies.push_back({r,i});
            }
            row.push_back(line[i]);
        }

        map.push_back(row);

        if(!rowHasGalaxy)
        {
            rowsWithoutGalaxies.insert(r);
        }
        r++;

    }


    long sum = 0;

    int galLen = galaxies.size();
    int MAG = 1000000;

    std::vector<int> rowPrefixSum(map.size(),0);
    std::vector<int> colPrefixSum(map[0].size(),0);

    rowPrefixSum[0] = rowsWithoutGalaxies.count(0) ? MAG : 1;
    colPrefixSum[0] = colsWithGalaxies.count(0) ? 1 : MAG;

    for(int row = 1; row < map.size(); ++row)
    {
        rowPrefixSum[row] = rowPrefixSum[row-1];
        rowPrefixSum[row] += rowsWithoutGalaxies.count(row) ? MAG : 1;
    }

    for(int col = 1; col < map[0].size(); ++col)
    {
        colPrefixSum[col] = colPrefixSum[col-1];
        colPrefixSum[col] += colsWithGalaxies.count(col) ? 1 : MAG;
    }


    for(int i = 0; i < galLen-1; ++i)
    {
        for(int j = i+1; j<galLen; ++j)
        {
            auto p1 = galaxies[i], p2 = galaxies[j];
            int minCol = std::min(p1.second, p2.second), maxCol = std::max(p1.second, p2.second);
            int minRow = std::min(p1.first, p2.first), maxRow = std::max(p1.first, p2.first);

            long distance = 0;

            // for(int col = minCol; col<maxCol; ++col)
            // {
            //     if(colsWithGalaxies.count(col))
            //     {
            //         distance += 1;
            //     }
            //     else
            //     {
            //         distance += MAG;
            //     }
            // }

            // for(int row = minRow; row<maxRow; ++row)
            // {
            //     if(rowsWithoutGalaxies.count(row))
            //     {
            //         distance += MAG;
            //     }
            //     else
            //     {
            //         distance += 1;
            //     }
            // }
            distance += (rowPrefixSum[maxRow]-rowPrefixSum[minRow] + colPrefixSum[maxCol] - colPrefixSum[minCol]);

            std::cout<<"("<<p1.first<<","<<p1.second<<")"<<" "
            <<"("<<p2.first<<","<<p2.second<<")"<<" "
            << distance<<std::endl;

            sum += distance;
        }
    }

    std::cout<<"the distance pf the "<<galaxies.size()<<" galaxies = "<<sum<<std::endl;

}



// 9639160
