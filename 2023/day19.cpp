
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>


typedef std::unordered_map<char, long long> Xmas;


Xmas parseXmas(std::string s)
{
    // s os for hte form {x=a,m=b};
    std::string t = s.substr(1,s.length()-2);
    std::stringstream ss{t};
    std::string equation;

    Xmas xmas;
    long long arr[4];
    int i = 0;
    while(std::getline(ss, equation, ','))
    {
        int ePos = equation.find('=');
        arr[i++] = std::stoll(equation.substr(ePos+1));

    }
    // std::cout<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<"\n";

    xmas['x'] = arr[0];
    xmas['m'] = arr[1];
    xmas['a'] = arr[2];
    xmas['s'] = arr[3];
    return xmas;

}

void parseRules(std::string ruleString, std::unordered_map<std::string, std::vector<std::string>>& ruleMap){
    std::string ruleName;

    std::string temp = "";

    for(char c: ruleString)
    {
        if(c == '{')
        {
            ruleName = temp;
            temp = "";
        }
        else if(c==',' | c== '}')
        {
            // std::cout<<temp<<std::endl;
            ruleMap[ruleName].push_back(temp);
            temp = "";
        }
        else {
            temp+=c;
        }
    }
    // std::cout<<std::endl;
}

char applyRule(std::string rule, std::unordered_map<std::string, std::vector<std::string>>& ruleMap, Xmas& xmas)
{
    // std::cout<<"on rule "<<rule<<" x = "<<xmas['x']<<"  m= "<<xmas['m']<<" a = "<<xmas['a']<<" s = "<<xmas['s']<<std::endl;
    std::vector<std::string> formulas =ruleMap[rule];

    for(auto& formula: formulas)
    {
        if(formula == "A" || formula == "R")
        {
            return formula[0];
        }

        int colonPos = formula.find(':');

        // it is the name of another rule
        if(colonPos == std::string::npos)
        {
            return applyRule(formula, ruleMap, xmas);
        }

        char var = formula[0];
        char comparator = formula[1];
        int val = std::stoi(formula.substr(2,colonPos-2));
        std::string result = formula.substr(colonPos+1);
        // std::cout<< var <<" "<<comparator<<val<<"="<<result<<std::endl;

        bool conditionPassed = false;
        if(comparator == '<')
        {
            conditionPassed = xmas[var] < val;
        }
        else if(comparator == '>')
        {
            conditionPassed = xmas[var] > val;
        }

        if(!conditionPassed)
        {
            continue;
        }

        if(result == "A" || result == "R")
        {
            return result[0];
        }

        return applyRule(result, ruleMap, xmas);
    }

    return 'O';
}

void getNumberOfWays(std::string rule, std::unordered_map<std::string, std::vector<std::string>>& ruleMap, Xmas min, Xmas max, long long& ways)
{
    std::vector<std::string>& formulas =ruleMap[rule];
    for(auto& formula: formulas)
    {
        // std::cout<<rule<<"  "<<formula<<" "<<min['x']<<":"<<max['x']<<" "<<min['m']<<":"<<max['m']<<" "<<min['a']<<":"<<max['a']<<" "<<min['s']<<":"<<max['s']<<std::endl;
        if(formula == "A")
        {
            // std::cout<<rule<<": the multiplication part 1 is "
            // <<max['x'] <<" - "<< min['x'] + 1<<std::endl
            // <<max['m'] <<" - "<< min['m'] + 1<<std::endl
            // <<max['a'] <<" - "<< min['a'] + 1<<std::endl
            // <<max['s'] <<" - "<< min['s'] + 1<<std::endl
            // <<ways<<std::endl;

            long long way = (long long)(
                (max['x'] - min['x'] + 1) *
                (max['m'] - min['m'] + 1) *
                (max['a'] - min['a'] + 1) *
                (max['s'] - min['s'] + 1)
            );

            ways += way;
            // std::cout<<"answer line:  "<<rule<<"  "<<formula<<" "<<min['x']<<":"<<max['x']<<" "<<min['m']<<":"<<max['m']<<" "<<min['a']<<":"<<max['a']<<" "<<min['s']<<":"<<max['s']<<std::endl;
            // std::cout<<way<<std::endl;
            return;
        }

        if(formula == "R")
        {
            return;
        }

        int colonPos = formula.find(':');



        // it is the name of another rule
        if(colonPos == std::string::npos)
        {
            getNumberOfWays(formula, ruleMap, min, max, ways);
            return;
        }

        char var = formula[0];
        char comparator = formula[1];
        int val = std::stoi(formula.substr(2,colonPos-2));
        std::string result = formula.substr(colonPos+1);
        // std::cout<< var <<" "<<comparator<<val<<"="<<result<<std::endl;

        // number of ways for it to pass this current level;

        int prevmin = min[var];
        int prevmax = max[var];

        if(comparator == '<')
        {
            max[var] = std::min(max[var],(long long)(val-1));
        }
        else if(comparator == '>')
        {
           min[var] = std::max((long long)(val+1), min[var]);
        }

        // if range is invalid reutrn'
        if(max[var] < min[var] || max[var] > 4000 || max[var] < 1 || min[var] > 4000 || min[var] < 1)
        {
            return;
        }

        if(result == "A")
        {
            //  std::cout<<rule<<": the multiplication part 2 is "
            // <<max['x'] <<" - "<< min['x']<<std::endl
            // <<max['m'] <<" - "<< min['m']<<std::endl
            // <<max['a'] <<" - "<< min['a']<<std::endl
            // <<max['s'] <<" - "<< min['s']<<std::endl
            // <<ways<<std::endl;
            long long way = (long long)(
                (max['x'] - min['x'] + 1) *
                (max['m'] - min['m'] + 1) *
                (max['a'] - min['a'] + 1) *
                (max['s'] - min['s'] + 1)
            );
            ways += way;
            // std::cout<<way<<std::endl;
            // std::cout<<"answer line:  "<<rule<<"  "<<formula<<" "<<min['x']<<":"<<max['x']<<" "<<min['m']<<":"<<max['m']<<" "<<min['a']<<":"<<max['a']<<" "<<min['s']<<":"<<max['s']<<std::endl;
        }

        else if(result == "R")
        {
        }

        // It lnks to another rule
        else{
             getNumberOfWays(result, ruleMap, min, max, ways);
        }

        //  std::cout<<rule<<"  "<<formula<<" here 1 \n";
        // make it fail and it goes to the next one.

        max[var] = prevmax;
        min[var] = prevmin;

        if(comparator == '<')
        {
            min[var] = std::max((long long)val, min[var]);

        }
        else if(comparator == '>')
        {
           max[var] = std::min((long long)val, max[var]);

        }

        // std::cout<<rule<<"  "<<formula<<" here 2 \n";
    //    std::cout<<"at end of loop = "<<rule<<"  "<<formula<<" "<<min['x']<<":"<<max['x']<<" "<<min['m']<<":"<<max['m']<<" "<<min['a']<<":"<<max['a']<<" "<<min['s']<<":"<<max['s']<<std::endl;

        if(max[var] < min[var] || max[var] > 4000 || max[var] < 1 || min[var] > 4000 || min[var] < 1)
        {
            return;
        }
        // std::cout<<rule<<"  "<<formula<<" here 3 \n";

    }


}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day19input1.txt";
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


    std::vector<Xmas> xmasses;
    std::unordered_map<std::string, std::vector<std::string>> ruleMap;

    while(std::getline(file, line))
    {
        // std::cout<< line <<std::endl;
        if(line == "") continue;

        // parsing of the xmases
        if(line[0]=='{')
        {
            //
            xmasses.push_back(parseXmas(line));
        }
        else{
            parseRules(line, ruleMap);
        }

    }

    // for(auto &k: ruleMap)
    // {
    //     std::cout<<k.first<<":-> ";
    //     for(auto& s: k.second)
    //     {
    //         std::cout<< s <<" ";
    //     }
    //     std::cout<<std::endl<<std::endl;
    // }

    int i = 1;
    long long final = 0;

    // for(auto& xmas: xmasses)
    // {
    //     std::cout<<i++<<"---------------------->\n";
    //      char verdict = applyRule("in",ruleMap, xmas);
    //     std::cout<<verdict<<std::endl;
    //     std::cout<<"\n\n\n";

    //     if(verdict=='A')
    //     {
    //         final += (xmas['x'] + xmas['m'] + xmas['a'] + xmas['s']);
    //     }

    // }

    std::cout<<"final ans = "<<final<<std::endl;

    long long totalWays = 0;

    for(auto &k: ruleMap)
    {
        if(k.first!="in") continue;
         Xmas min, max;

        min['x'] = 1;
        min['m'] = 1;
        min['a'] = 1;
        min['s'] = 1;

        max['x'] = 4000;
        max['m'] = 4000;
        max['a'] = 4000;
        max['s'] = 4000;

        long long ways = 0;

        getNumberOfWays(k.first, ruleMap, min, max, ways);
        std::cout<<"for "<<k.first<<" we have "<<ways<<" ways"<<std::endl;
        totalWays += ways;
    }

    // for(int x = 1; x <= 4000; x++)
    // {
    //     for(int m = 1; m <= 4000; m++)
    //     {
    //         for(int a = 1; a <= 4000; a++)
    //         {
    //             for(int s = 1; s <= 4000; s++)
    //             {
    //                 Xmas xmas;
    //                 xmas['x'] = x;
    //                 xmas['m'] = m;
    //                 xmas['a'] = a;
    //                 xmas['s'] = s;

    //                 char verdict = applyRule("in",ruleMap, xmas);
    //                 if(verdict == 'A')
    //                 {
    //                     totalWays++;
    //                 }

    //             }
    //         }
    //     }
    // }

    std::cout<<totalWays<<" ways\n\n";
}


