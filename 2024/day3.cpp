
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

long long solve(const std::string& line)
{
    std::regex re("mul\\((\\d+),(\\d+)\\)");
    long long ans =0;
    for(std::sregex_iterator it(line.begin(), line.end(), re); it!=std::sregex_iterator(); it++)
    {
        int val1 = std::stoi(it->str(1)); 
        int val2 = std::stoi(it->str(2));
        ans += val1 * val2;
    }
    return ans;
}

long long solve2(const std::string& line)
{
    std::regex re1("(mul\\(\\d+,\\d+\\))|(do(n't)?\\(\\))");
    bool should_do = true;
    long long ans =0;
    for(std::sregex_iterator it(line.begin(), line.end(), re1); it!=std::sregex_iterator(); it++)
    {
        auto val = it->str();
        if(val=="do()")
        {
            should_do = true;
        }
        else if(val=="don't()")
        {
            should_do = false;
        }
        else
        {
            int open_bracket = val.find('(');
            int close_bracket = val.find(')');
            int comma = val.find(',');
            // std::cout<<""
            if(should_do){
                ans += std::stoi(val.substr(open_bracket+1, comma-open_bracket)) * std::stoi(val.substr(comma+1, close_bracket-comma));
            }
        }
        
    }

    return ans;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day3input1.txt";
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
    std::string fullLine = "";

    long long totalAns = 0;
    while(std::getline(file, line))
    {
        fullLine += line;
    }

    std::cout<<"ans = "<<solve2(fullLine)<<std::endl;;

}


