
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

bool checkMatch(std::string line, std::vector<long>& records)
{
    line = line+'*';
    int i = 0;
    while(line[i]!='#')
    {
        i++;
    }

    int count = 0;
    int ref = 0;

    // std::cout<<"first value of i is"<<i<<std::endl;
    while(i < line.length())
    {
        if(line[i]=='#')
        {
            count++;
        }

        else if(count > 0)
        {

            //at this point we have the count of contiguous #
            //if we have more continous records than in the record
            // std::cout<<"count = "<<count<<std::endl;
            if(ref >= records.size())
            {
                return false;
            }
            if(count != records[ref])
            {
                return false;
            }
            count = 0;
            ref++;
        }
        i++;
    }

    return ref == records.size();
}

bool checkPartialMatch(std::string line ,std::vector<long>& records)
{
    line = line;
    int i = 0;
    while(line[i]!='#')
    {
        i++;
    }

    int count = 0;
    int ref = 0;

    // std::cout<<"first value of i is"<<i<<std::endl;
    while(i < line.length())
    {
        if(line[i]=='#')
        {
            count++;
        }

        else if(count > 0)
        {

            //at this point we have the count of contiguous #
            //if we have more continous records than in the record
            // std::cout<<"count = "<<count<<std::endl;
            if(ref >= records.size())
            {
                return false;
            }
            if(count != records[ref])
            {
                return false;
            }
            count = 0;
            ref++;
        }
        i++;
    }

    return true;
}

//split a string of numbers seperated by delimeters
std::vector<long> parseNumbers(std::string numbers, char delim = ' ')
{
    std::stringstream ss(numbers);
    std::string num;
    std::vector<long> ans;
    while(std::getline(ss, num, delim))
    {
        ans.push_back(std::stol(num));
    }
    // std::for_each(ans.begin(), ans.end(),[](long val){std::cout<<val<<"->";}); std::cout<<std::endl;
    return ans;
}

long getWays(std::string s, int i, std::vector<long>& records)
{
    //
    if(i==s.length())
    {
        bool val = checkMatch(s, records);
        // if(val) {std::cout<<"working on "<<s<<std::endl;}
        return val ? 1 : 0;
    }

    if(!checkPartialMatch(s.substr(0,i), records))
    {
        return 0;
    }

    if(s[i]!='?')
    {
        return getWays(s, i+1, records);
    }

    long ans = 0;

    s[i] = '#';
    ans += getWays(s, i+1, records);

    s[i] = '.';
    ans += getWays(s, i+1, records);
    s[i] = '?';

    return ans;

}

void multiply(std::string& pattern, std::vector<long>& records)
{
    std::string temp = pattern;
    int n = records.size();

    for(int i = 0; i < 4; i++)
    {
        temp += ("?"+pattern);

        for(int j = 0; j<n; j++)
        {
            records.push_back(records[j]);
        }
    }

    pattern = temp;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day12input1.txt";
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
        // std::cout<< line <<std::endl;
        int spacePos = line.find(' ');

        std::string pattern = line.substr(0, spacePos);
        std::vector<long> records = parseNumbers(line.substr(spacePos+1), ',');

        // for part 2
        multiply(pattern, records);

        // std::cout<<pattern<<std::endl;
        // std::for_each(records.begin(), records.end(),[](long val){std::cout<<val<<",";}); std::cout<<std::endl;




        // std::cout<<pattern<<std::endl;

        long ways = getWays(pattern, 0, records);
        std::cout<<ways<<std::endl;
        ans+= ways;

    }

    std::cout<<ans<<" ways\n";

    // std::cout<<checkMatch(".#....#...###.", std::vector<int>{1,1,3})<<std::endl;
    // std::cout<<checkMatch("#.#.##", std::vector<int>{1,1,3})<<std::endl;
    // std::cout<<checkMatch("#.##.###", std::vector<int>{1,1,3})<<std::endl;
    // std::cout<<checkMatch("#.#.###", std::vector<int>{1,1})<<std::endl;
    // std::cout<<checkMatch("#.#.###", std::vector<int>{1,1,3, 3})<<std::endl;

    // long ways = getWays("?###????????", 0, std::vector<long>{3,2,1});

    // std::cout<<"There are "<<ways<<" ways to do it\n";


}


