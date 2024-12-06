
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::pair<bool, int> isIncrease(const std::vector<int>& report)
{
    int ignored = -1;
    int prev = report[0]-1;

    // check for increasing. 
    int n = report.size();
    for(int i = 0; i < n; i++)
    {
        if(prev >= report[i] && ignored!=-1)
        {
            return {false, ignored};
        }
        if(prev >= report[i] && ignored == -1)
        {
            ignored = i;
            continue;
        }
        
        prev = report[i];
    }
    return {true, ignored};
}


std::pair<bool, int> isDecrease(const std::vector<int>& report)
{
    int ignored = -1;
    int prev = report[0]+1;

    // check for decreasing. 
    int n = report.size();
    for(int i = 0; i < n; i++)
    {
        if(prev <= report[i] && ignored!=-1)
        {
            return {false, ignored};
        }
        if(prev <= report[i] && ignored == -1)
        {
            ignored = i;
            continue;
        }
        
        prev = report[i];
    }
    return {true, ignored};
}


std::vector<int> getList(const std::string& line)
{
    std::stringstream ss(line);
    int num;
    std::vector<int> ans;
    while(ss >> num){
        ans.push_back(num);
    }

    return ans;
}



bool isSafe(const std::vector<int>& report)
{
    bool should_increase = report[1]-report[0] > 0;
    int n = report.size();
    for(int i = 1; i < n; i++)
    {
        if((should_increase && (report[i-1] > report[i])) || (!should_increase && report[i-1] < report[i] ))
        {
            return false;
        }
        int diff = abs(report[i]-report[i-1]);
        if( diff > 3 || diff < 1)
        {
            return false;
        }
    }

    return true;
}


bool isSafe2(const std::vector<int>& report)
{
    if(isSafe(report))
    {
        return true;
    }

    int n = report.size();

    for(int ignored = 0; ignored < n; ignored++)
    {
        std::vector<int> newReport;
        for(int i = 0; i < n; i++)
        {
            if(i==ignored)
            {
                continue;
            }
            newReport.push_back(report[i]);
        }
        if(isSafe(newReport))
        {
            return true;
        }
    }

    return false;
}


int solve(std::vector<std::vector<int>>& all)
{
    int ans = 0;
    for(const auto& report: all)
    {
        ans += isSafe(report);
    }

    return ans;
}


int solve2(std::vector<std::vector<int>>& all)
{
    int ans = 0;
    for(const auto& report: all)
    {
        ans += isSafe2(report);
    }

    return ans;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day2input1.txt";
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

    std::vector<std::vector<int>> all;
    while(std::getline(file, line))
    {
        all.push_back(getList(line));
    }

    std::cout<<" ans: "<<solve2(all)<<std::endl;

}


