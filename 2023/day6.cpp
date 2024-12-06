
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

bool checkCanWin(long timePressed, long totalRaceTime, long currentMaxDistance)
{
    return timePressed * (totalRaceTime - timePressed) > currentMaxDistance;
}

std::vector<long> parseNumbers(std::string numbers, char delim = ' ')
{
    std::stringstream ss(numbers);
    std::string num;
    std::vector<long> ans;
    while(std::getline(ss, num, delim))
    {
        ans.push_back(std::stol(num));
    }
    std::for_each(ans.begin(), ans.end(),[](long val){std::cout<<val<<"->";}); std::cout<<std::endl;
    return ans;
}


int main(int argc, char* argv[]){

    std::string FILENAME = "test/day6input1.txt";
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


    // std::ifstream file(FILENAME);
    // std::string line;

    // std::getline(file, line);
    // std::vector<long> times = parseNumbers(line.substr(5));

    // std::getline(file, line);
    // std::vector<long> distances = parseNumbers(line.substr(9));

    // long ans = 1;

    // long n = times.size();

    // for(long i = 0; i < n; ++i)
    // {
    //     long totalRaceTime = times[i];
    //     long currentMaxDistance = distances[i];
    //     long waysToBeatCurrentRecord = 0;

    //     for(long timePressed = 1; timePressed < totalRaceTime; ++timePressed)
    //     {
    //         waysToBeatCurrentRecord += checkCanWin(timePressed, totalRaceTime, currentMaxDistance);
    //     }
    //     ans *= waysToBeatCurrentRecord;
    //     std::cout<<"for race there are "<<waysToBeatCurrentRecord<<" ways to win"<<std::endl;
    // }


    // std::cout<<"The answer is "<<ans<<std::endl;;

    std::ifstream file(FILENAME);
    std::string line;

    std::getline(file, line);
    long totalRaceTime = parseNumbers(line.substr(5))[0];

    std::getline(file, line);
    long currentMaxDistance = parseNumbers(line.substr(9))[0];


    long waysToWinCurrentRecord = 0;
    for(long timePressed = 1; timePressed < totalRaceTime; ++timePressed)
    {
        waysToWinCurrentRecord += checkCanWin(timePressed, totalRaceTime, currentMaxDistance);
    }

    std::cout<<"for race there are "<<waysToWinCurrentRecord<<" ways to win"<<std::endl;


    std::cout<<"The answer is "<<waysToWinCurrentRecord<<std::endl;;


}


