
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

void getAntinodes(std::vector<std::pair<int,int>>& nodes, std::vector<std::string>& seen )
{
   int rows = seen.size();
   int cols = seen[0].length();

    int n = nodes.size();

    auto isInBound = [&rows, &cols](int r, int c){
        return 0 <= r && r < rows && 0 <= c && c < cols;
    };


    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
             int r1 = nodes[i].first,  c1 = nodes[i].second;
             int r2 = nodes[j].first,  c2 = nodes[j].second;

             int dr = r2 - r1, dc = c2 - c1;

             int fr = r2 + dr, fc = c2 + dc;

             int br = r1 - dr, bc = c1 - dc;

             if(isInBound(fr, fc))
             {
                seen[fr][fc] = '#';
             }

             if(isInBound(br, bc))
             {
                seen[br][bc] = '#';
             }
        }
    }
}

void getAntinodes2(std::vector<std::pair<int,int>>& nodes, std::vector<std::string>& seen )
{
   int rows = seen.size();
   int cols = seen[0].length();

    int n = nodes.size();

    auto isInBound = [&rows, &cols](int r, int c){
        return 0 <= r && r < rows && 0 <= c && c < cols;
    };


    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {

             int r1 = nodes[i].first,  c1 = nodes[i].second;
             int r2 = nodes[j].first,  c2 = nodes[j].second;

             int dr = r2 - r1, dc = c2 - c1;

             int fr = r2, fc = c2;

             int br = r1, bc = c1;
            
            while(isInBound(fr, fc))
            {
                seen[fr][fc] = '#';
                fr += dr;
                fc += dc;
            }

             while(isInBound(br, bc))
             {
                seen[br][bc] = '#';
                br -= dr;
                bc -= dc;
             }
        }
    }
}

long long solve( std::unordered_map<char, std::vector<std::pair<int,int>>>& antennas, std::vector<std::string>& seen)
{
    for(auto &k: antennas)
    {
        getAntinodes(k.second, seen);
    }

    long long ans = 0;
    for(auto& s: seen)
    {   
        ans += std::count(s.begin(), s.end(), '#');
    }

    return ans;
}

long long solve2( std::unordered_map<char, std::vector<std::pair<int,int>>>& antennas, std::vector<std::string>& seen)
{
    for(auto &k: antennas)
    {
        getAntinodes2(k.second, seen);
    }

    long long ans = 0;
    for(auto& s: seen)
    {   
        ans += std::count(s.begin(), s.end(), '#');
    }

    return ans;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day8input1.txt";
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
    std::unordered_map<char, std::vector<std::pair<int,int>>> antennas;
    std::vector<std::string> seen;

    int r = 0;
    while(std::getline(file, line))
    {
        for(int c = 0; c < line.length(); c++)
        {
            if(line[c]!='.')
            {
                antennas[line[c]].push_back({r,c});
            }
        }
        seen.push_back(line);
        r++;
    }

    std::cout<<" The ans is "<<solve2(antennas, seen)<<std::endl;

}


