
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

long long solve(const std::vector<int>& one, const std::vector<int>&  two)
{
    std::priority_queue<int> pq1(one.begin(), one.end());
    std::priority_queue<int> pq2(two.begin(), two.end());

    long long ans = 0;
    while(!pq1.empty())
    {
        ans += std::abs(pq1.top()-pq2.top());
        pq1.pop(); pq2.pop();
    }

    return ans;
}

long long solve2(const std::vector<int>& one, const std::vector<int>&  two)
{
    std::unordered_map<int, int> count;

    for(int i: two)
    {
        count[i]++;
    }

    long long ans = 0;
    for(int i: one)
    {
        ans += i * count[i];
    }

    return ans;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day1input1.txt";
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

    std::vector<int> one, two;

    while(std::getline(file, line))
    {
        int a, b;
        std::stringstream ss(line);
        ss >> a >> b;
        one.push_back(a);
        two.push_back(b);
    }

    std::cout<<"ans: "<<solve2(one,two)<<std::endl;

}


