
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::vector<long long> getList(const std::string& line)
{
    std::stringstream ss(line);
    long long num;
    std::vector<long long> ans;
    while(ss >> num){
        ans.push_back(num);
    }

    return ans;
}

bool canDo(long long testValue, std::vector<long long>& values, int i, std::vector<std::unordered_map<long long, bool>>& dp)
{
    // std::cout<<testValue<<" "<<i<<std::endl;
    if(i == 0 && testValue == values[i])
    {
        return true;
    }

    if(i<0)
    {
        return false;
    }

    if(dp[i].count(testValue))
    {
        return dp[i][testValue];
    }

    
    bool ans = false;

    if(testValue >= values[i])
    {
        ans = ans || canDo(testValue-values[i], values, i-1, dp);
    }
    
    if(testValue % values[i] == 0)
    {
        ans = ans || canDo(testValue / values[i], values, i-1, dp);
    }

    dp[i][testValue] = ans;
    return ans;
}


std::pair<bool, long long> removeEnd(long long concatenated, long long end)
{
    long long temp = end;
    long long power = 1;
    while(temp)
    {
        power *= 10;
        temp/=10;
    }

    if(concatenated % power == end)
    {
        return {true, concatenated / power};
    }

    return {false, 0};
}


bool canDoNODP(long long testValue, std::vector<long long>& values, int i)
{
   if(i == 0 && testValue == values[i])
    {
        return true;
    }

    if(i<0)
    {
        return false;
    }


    
    bool ans = false;

    if(testValue >= values[i])
    {
        ans = ans || canDoNODP(testValue-values[i], values, i-1);
    }
    
    if(testValue % values[i] == 0)
    {
        ans = ans || canDoNODP(testValue / values[i], values, i-1);
    }
    return ans;
}


bool canDoNODP2(long long testValue, std::vector<long long>& values, int i)
{
   if(i == 0 && testValue == values[i])
    {
        return true;
    }

    if(i<0)
    {
        return false;
    }


    
    bool ans = false;

    if(testValue >= values[i])
    {
        ans = ans || canDoNODP2(testValue-values[i], values, i-1);
    }
    
    if(testValue % values[i] == 0)
    {
        ans = ans || canDoNODP2(testValue / values[i], values, i-1);
    }

    auto checkConcat = removeEnd(testValue, values[i]);
    if(checkConcat.first)
    {
        ans = ans || canDoNODP2(checkConcat.second, values, i-1);
    }
    return ans;
}

long long solve(std::vector<long long>& testValues, std::vector<std::vector<long long>>& values)
{
    int n = testValues.size();
    long long ans = 0;
    std::vector<long long> vals;
    for(int i = 0; i < n; i++)
    {
        int nv = values[i].size();
        std::vector<std::unordered_map<long long, bool>> dp(nv);
        if(canDoNODP(testValues[i], values[i], nv-1)){
            ans += testValues[i];
            vals.push_back(testValues[i]);
        }
    }

    for(auto i: vals)
    {
        std::cout<<i<<std::endl;
    }

    std::cout<<"\n\n";

    return ans;
}


long long solve2(std::vector<long long>& testValues, std::vector<std::vector<long long>>& values)
{
    int n = testValues.size();
    long long ans = 0;

    for(int i = 0; i < n; i++)
    {
        int nv = values[i].size();
        std::vector<std::unordered_map<long long, bool>> dp(nv);
        if(canDoNODP2(testValues[i], values[i], nv-1)){
            ans += testValues[i];
        }
    }

    return ans;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day7input1.txt";
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
    std::vector<std::vector<long long>> values;
    std::vector<long long> testValues;


    while(std::getline(file, line))
    {
        int colon = line.find(':');
        testValues.push_back(std::stoll(line.substr(0,colon)));
        values.push_back(getList(line.substr(colon+1)));
    }

    // for(auto top: values)
    // {
    //     for(auto i: top)
    //     {
    //         std::cout<<i<<" ";
    //     }
    //     std::cout<<std::endl;
    // }

    std::cout<<"The ans is "<<solve2(testValues, values)<<std::endl;

    // auto val = removeEnd(156, 7);
    // std::cout<<val.first<<" "<<val.second<<std::endl;

}


