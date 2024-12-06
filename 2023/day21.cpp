
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <sstream>

namespace {
    std::vector<int> rdir{0, 0, -1, 1};
    std::vector<int> cdir{-1, 1, 0, 0};
}

struct Record{
    int r;
    int c;
    int steps = 0;
    Record() = default;
    Record(int dr, int dc, int dsteps):r(dr),c(dc),steps(dsteps){}
};

void dfs(int r, int c, std::vector<std::string> &map, std::unordered_set<int> &seen, int steps)
{
    int key = r * map.size() + c;
    if(steps == 0)
    {
        seen.insert(key);
        return;
    }

    map[r][c] = 'P';
    for(int i = 0; i<4; ++i)
    {
        int nr = r + rdir[i], nc = c + cdir[i];

        if(nr < 0 || nc < 0 || nr >= map.size() || nc >= map[0].length())
        {
            continue;
        }

        if(map[nr][nc] == '.')
        {
            dfs(nr, nc, map, seen, steps-1);
        }
    }
    map[r][c] = '.';
}

std::string getKey(int r, int c, int steps)
{
    std::stringstream ss;
    ss<<r<<":"<<c<<":"<<steps;
    return ss.str();
}

std::string getKey(int r, int c)
{
    std::stringstream ss;
    ss<<r<<":"<<c<<":";
    return ss.str();
}

void bfs(int r, int c, std::vector<std::string> &map, std::unordered_set<std::string> &seen, int steps)
{

    std::queue<Record> queue;

    queue.push(Record{r,c, 0});
    std::unordered_set<std::string> visited;

    while(!queue.empty())
    {

        auto top = queue.front(); queue.pop();
        int tr = top.r, tc = top.c, currSteps = top.steps;


        std::string visitKey = getKey(tr, tc, currSteps);


        if(visited.count(visitKey))
        {
            continue;
        }

        visited.insert(visitKey);

        if(currSteps == steps)
        {
            seen.insert(getKey(tr,tc));
            // std::cout<<tr<<" "<<tc<<" "<<currSteps<<std::endl;
            continue;
        }

        // if(currSteps > steps)
        // {
        //     break;
        // }

        for(int i = 0; i<4; ++i)
        {
            int nr = tr + rdir[i], nc = tc + cdir[i];

            if(nr < 0 || nc < 0 || nr >= map.size() || nc >= map[0].length())
            {
                continue;
            }

            if(map[nr][nc] != '#')
            {
                // std::cout<<nr<<":"<<nc<<std::endl;
                queue.push(Record{nr,nc, currSteps + 1});
            }
        }

    }
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day21input1.txt";
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

    std::vector<std::string> map;
    std::unordered_set<std::string> seen;
    std::unordered_set<int> path;

    int startr = 0, startc = 0;
    bool part2 = true;

    int r= 0;
    while(std::getline(file, line))
    {
        // std::cout<< line <<std::endl;
        int sPos = line.find('S');

        if(sPos != std::string::npos)
        {
            // line[sPos] = '.';
            startr = r;
            startc = sPos;
        }

        std::string temp = line;
        if(part2)
        {
            for(int i = 0; i<4;i++) line+=temp;
        }
        map.push_back(line);
        r++;
    }

    for(auto i: map)
    {
        std::cout<<i<<std::endl;
    }

    //the elf must move a distance of N but displacement differs.
    // taking different paths, the elf either moves forward or backwards
    // if we take each backward step as negative we can just claculate displacement from start point
    // e.g for 64 stpes either
    // 64 forward 0 back  displacement = 64
    // 63 farward 1 back displacement = 62 etc.

    // int high = 64, low = 0;

    // while(high - low >=0 )
    // {
    //     int displacement = high - low;
    //     bfs(startr, startc, map, seen, displacement);
    //     std::cout<<high<<"-"<<low<<" there are "<<seen.size()<<" steps\n";
    //     high--;
    //     low++;
    // }

    std::cout<<startr<<":"<<startc<<std::endl;
    bfs(startr, startc, map, seen, 65 + 131 * 2);


    std::cout<<"there are "<<seen.size()<<" steps\n";

}


/**
7193
*/
