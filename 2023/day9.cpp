
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

//split a string of numbers seperated by delimeters
std::vector<long> parseNumbers(std::string numbers)
{
    std::stringstream ss(numbers);
    std::string num;
    std::vector<long> ans;
    while(std::getline(ss, num, ' '))
    {
        ans.push_back(std::stol(num));
    }
    // std::for_each(ans.begin(), ans.end(),[](long val){std::cout<<val<<"->";}); std::cout<<std::endl;
    return ans;
}

long findNext(std::vector<long> input)
{
    // std::cout<<"find next of ";
    // std::for_each(input.begin(), input.end(),[](long val){std::cout<<val<<" ";}); std::cout<<std::endl;
    if(std::all_of(input.cbegin(), input.cend(), [](long i){
        return i==0;
    }))
    {
        return 0;
    }

    std::vector<long> next;
    int n = input.size();

    for(int i = 1; i < n; i++)
    {
        next.push_back(input[i]-input[i-1]);
    }

    return input[n-1] + findNext(next);
}

long findPrev(std::vector<long> input)
{
    // std::cout<<"find next of ";
    // std::for_each(input.begin(), input.end(),[](long val){std::cout<<val<<" ";}); std::cout<<std::endl;
    if(std::all_of(input.cbegin(), input.cend(), [](long i){
        return i==0;
    }))
    {
        return 0;
    }

    std::vector<long> next;
    int n = input.size();

    for(int i = 1; i < n; i++)
    {
        next.push_back(input[i]-input[i-1]);
    }

    return input[0] - findPrev(next);
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day9input1.txt";
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

    long ans = 0;

    while(std::getline(file, line))
    {
        std::vector<long> input = parseNumbers(line);

        long val = findPrev(input);
        std::cout<< val <<std::endl;
        ans += val;
    }

    std::cout<<"the answer is "<<ans<<std::endl;

}


