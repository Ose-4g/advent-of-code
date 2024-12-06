
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

void markPath(std::vector<std::string>& lines, int r, int c)
{
    std::vector<std::vector<int>>  dirs{
        {-1, 0}, //up
        {0, 1}, //right
        {1,0}, //down
        {0, -1} //left
    };

    int rows = lines.size();
    int cols = lines[0].length();
    int dir = 0;

    lines[r][c] = 'X';
    while(true)
    {
        int dr = dirs[dir][0]; 
        int dc = dirs[dir][1];
        int nr = r + dr;
        int nc = c + dc;

        if(nr < 0 || nr >= rows || nc < 0 || nc >= cols)
        {
            break;
        }

        if(lines[nr][nc] == '#')
        {
            dir++;
            dir%=4;
            continue;
        }

        lines[nr][nc] = 'X';
        r = nr;
        c = nc;
    }
}

bool hasLoop(std::vector<std::string>& lines, int r, int c)
{
    std::vector<std::vector<int>>  dirs{
        {-1, 0}, //up
        {0, 1}, //right
        {1,0}, //down
        {0, -1} //left
    };


    int rows = lines.size();
    int cols = lines[0].length();
    int dir = 0;

    auto getPos = [&rows, &cols](int r, int c){
        return r * rows + c;
    };


    std::vector<std::unordered_set<int>> seen(4);
    seen[0].insert(getPos(r,c));
    while(true)
    {
        int dr = dirs[dir][0]; 
        int dc = dirs[dir][1];
        int nr = r + dr;
        int nc = c + dc;

        if(nr < 0 || nr >= rows || nc < 0 || nc >= cols)
        {
            break;
        }

        if(lines[nr][nc] == '#' || lines[nr][nc]=='0')
        {
            dir++;
            dir%=4;
            continue;
        }

        if(seen[dir].count(getPos(nr, nc)))
        {
            return true;
        }

        seen[dir].insert(getPos(nr, nc));
        r = nr;
        c = nc;
    }

    return false;
}


long long solve(std::vector<std::string>& lines, int r, int c)
{
    markPath(lines, r,  c);

    long long ans = 0;
    for(auto& row: lines)
    {
        ans += std::count(row.begin(), row.end(), 'X');
    }

    return ans;
}

long long solve2(std::vector<std::string>& lines, int r, int c)
{
     int rows = lines.size();
    int cols = lines[0].length();
    long long ans = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(lines[i][j]=='#')
            {
                continue;
            }

            lines[i][j] = '0';
            ans += hasLoop(lines, r, c);
            lines[i][j] = '.';
        }
    }

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


    std::ifstream file(FILENAME);
    std::string line;
    std::vector<std::string> lines;
    int r,c;

    while(std::getline(file, line))
    {
        int pos = line.find('^');
        if(pos!=std::string::npos)
        {
            r = lines.size();
            c = pos;
            line[pos] = '.';
        }
        lines.push_back(line);
        // std::cout<<line<<std::endl;
    }

    std::cout<<"ans is "<<solve2(lines, r, c)<<std::endl;
    // std::cout<<(hasLoop(lines, r, c) ? "HAS LOOP" : "HAS NO LOOP" )<<"\n";

}


