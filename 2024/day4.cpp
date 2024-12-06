
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool check(const std::vector<std::string>& lines,int r, int c, int dr, int dc)
{
    std::string find = "XMAS";
    int n = 4;

    for(int i = 0; i < 4; i++)
    {
        if(r < 0 || r >= lines.size() || c < 0 || c >= lines[0].length())
        {
            return false;
        }

        if(find[i] != lines[r][c])
        {
            return false;
        }
        r+=dr; c+=dc;
    }

    return true;
}

int solve2(const std::vector<std::string>& lines)
{
    int rows = lines.size(); int cols = lines[0].length();

    long long ans = 0;
    for(int i = 1; i < rows-1; i++)
    {
        for(int j = 1; j < cols-1; j++)
        {
            if(lines[i][j]=='A')
            {
                std::string dg1 = "", dg2 = "";

                dg1+=lines[i-1][j+1]; dg1 += lines[i+1][j-1];
                dg2+=lines[i-1][j-1]; dg2 += lines[i+1][j+1];

                if((dg1 == "SM" || dg1 == "MS") && (dg2 == "SM" || dg2 == "MS") )
                {
                    ans += 1;
                }
            }
        }
    }

    return ans;
}
int solve(const std::vector<std::string>& lines)
{
    std::vector<std::vector<int>> dirs {
        {-1,0},//up
        {1, 0},//down
        {0, -1},//leff
        {0 , 1},//right
        {-1, 1},//upright
        {1,1},//bottom right
        {1, -1}, //bottom left
        {-1, -1}// top left
    };

    int rows = lines.size(); int cols = lines[0].length();

    long long ans = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            for(auto dir: dirs)
            {
                ans += check(lines, i, j, dir[0], dir[1]);
            }
        }
    }

    return ans;
}
int main(int argc, char* argv[]){

    std::string FILENAME = "test/day4input1.txt";
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


    while(std::getline(file, line))
    {   
        lines.push_back(line);
    }

    std::cout<<"ans = "<<solve2(lines)<<std::endl;

}


