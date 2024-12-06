
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

// roll north
void rollRocksUp(std::vector<std::string>& pattern, int row)
{
    for(int i = 0; i < pattern[row].size(); ++i)
    {
        if(pattern[row][i]=='O')
        {
            int temp = row;
            while(temp-1 >= 0 && pattern[temp-1][i] == '.')
            {
                temp--;
            }

            pattern[row][i] = '.';
            pattern[temp][i] = 'O';
        }
    }
}

// roll west
void rollRocksLeft(std::vector<std::string>& pattern, int col)
{
    for(int i = 0; i < pattern.size(); ++i)
    {
        if(pattern[i][col]=='O')
        {
            int temp = col;
            while(temp-1 >= 0 && pattern[i][temp-1] == '.')
            {
                temp--;
            }

            pattern[i][col] = '.';
            pattern[i][temp] = 'O';
        }
    }
}

// roll south
void rollRocksDown(std::vector<std::string>& pattern, int row)
{
    for(int i = 0; i < pattern[row].size(); ++i)
    {
        if(pattern[row][i]=='O')
        {
            int temp = row;
            while(temp + 1 < pattern.size() && pattern[temp+1][i] == '.')
            {
                temp++;
            }

            pattern[row][i] = '.';
            pattern[temp][i] = 'O';
        }
    }
}

// roll east
void rollRocksRight(std::vector<std::string>& pattern, int col)
{
    for(int i = 0; i < pattern.size(); ++i)
    {
        if(pattern[i][col]=='O')
        {
            int temp = col;
            while(temp+1 < pattern[0].size() && pattern[i][temp+1] == '.')
            {
                temp++;
            }

            pattern[i][col] = '.';
            pattern[i][temp] = 'O';
        }
    }
}

void printPattern(std::vector<std::string>& pattern)
{
     for(auto s: pattern)
    {
        std::cout<<s<<std::endl;
    }
    std::cout<<"\n\n";
}

void cycle(std::vector<std::string> & pattern){
    int rown = pattern.size(), coln = pattern[0].size();


    //roll up
    for(int row = 1; row < rown; ++row)
    {
        rollRocksUp(pattern, row);
    }
    // printPattern(pattern);

    // roll left
    for(int col = 1; col < coln; ++col)
    {
        rollRocksLeft(pattern, col);
    }
    // printPattern(pattern);

     //roll down
    for(int row = rown-2; row >= 0; --row)
    {
        rollRocksDown(pattern, row);
    }
    // printPattern(pattern);

    // roll right
    for(int col = coln - 2; col >= 0; --col)
    {
        rollRocksRight(pattern, col);
    }
    // printPattern(pattern);
    // std::cout<<"cycle ended \n\n";
}

std::string getKey(std::vector<std::string>& pattern){
    std::string ans = "";
    for(auto s: pattern)
    {
        ans += s;
    }
    return ans;
}


int main(int argc, char* argv[]){

    std::string FILENAME = "test/day14input1.txt";
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

    std::vector<std::string> pattern;

    while(std::getline(file, line))
    {
        // std::cout<< line <<std::endl;
        pattern.push_back(line);
    }

    std::cout<<"\n\n";


    std::unordered_map<std::string, std::vector<int>> cycleMap;

    for(int i=1; i<=1000; i++) {
        cycle(pattern);
        cycleMap[getKey(pattern)].push_back(i);

    }

    int n = pattern.size();
    long ans = 0;

    // for(std::string s: pattern)
    // {
    //     ans += (std::count(s.cbegin(), s.cend(),'O') * n);
    //     n--;
    // }

    // printPattern(pattern);

    for(auto &k: cycleMap)
    {
        for(int cy: k.second)
        {
            std::cout<<cy<<" ";
        }
        std::cout<<"\n";
    }



    // for(int i = 1; i < pattern.size(); ++i)
    // {
    //     rollRocksUp(pattern, i);
    // }

    std::cout<<"the answer is "<<ans<<std::endl;
}



