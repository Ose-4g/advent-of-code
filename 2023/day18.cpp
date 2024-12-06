
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

namespace {
        //                    U, D, L, R
    std::vector<int> rDir{-1,1, 0, 0};
    std::vector<int> cDir{0, 0, -1, 1};
}
struct Move{
    char dir;
    int moves;
    std::string color;
    Move() = default;
};

void fill(std::vector<std::string>& grid, int i, int j, char c = '*')
{
    if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].length())
    {
        return;
    }
    if(grid[i][j]!='.')
    {
        return;
    }
    grid[i][j] = c;
    for(int index = 0; index< 4; index++)
    {
        fill(grid, i+rDir[index], j+cDir[index], c);
    }
}
int calculateDepth(int startr, int startc, std::vector<Move>& moveList, std::vector<std::string>& grid)
{
    std::unordered_map<char, std::pair<int,int>> dirMap;
    dirMap['U'] = {-1, 0};
    dirMap['D'] = {1, 0};
    dirMap['L'] = {0, -1};
    dirMap['R'] = {0, 1};

    int r = startr, c = startc;
    grid[r][c] = '#';

    for(auto move: moveList)
    {
        for(int i = 0; i< move.moves; ++i)
        {
            auto dxy = dirMap[move.dir];
            r += dxy.first;
            c += dxy.second;
            // std::cout<<"r:c = "<<r<<":"<<c<<std::endl;
            grid[r][c] = '#';
        }
    }

    // for each edge piece on left and right
    for(int i = 0; i < grid.size(); i++)
    {
        fill(grid, i,0);
        fill(grid, i, grid[0].length()-1);
    }

     // for each edge piece on up and down
    for(int j = 0; j < grid[0].length(); j++)
    {
        fill(grid, 0, j);
        fill(grid, grid.size()-1, j);
    }


    int ans = 0;
    for(std::string s: grid)
    {
        std::cout<<s<<std::endl;
        for(char c: s)
        {
            ans+= (c=='.' || c=='#');
        }
    }


    std::cout<<"the ans = "<<ans<<std::endl;
    return ans;
}
long long shoelace(std::vector<std::pair<long,long>>& coords)
{
    // https://artofproblemsolving.com/wiki/index.php/Shoelace_Theorem

    int n = coords.size();

    //x1y2 + x2y3+ ...... xny1
    long long a1 = 0;
    long long a2 = 0;
    for(int i = 0; i < n; i++)
    {
        // std::cout<<coords[i].first<<":->:"<<coords[i].second<<std::endl;
        int ind1 = i;
        int ind2 = (i+1)%n;

        // xi * yi+1
        a1 += coords[ind1].first * coords[ind2].second;

        // yi * xi+1
        a2 += coords[ind1].second * coords[ind2].first;
    }

    long long ans = std::abs(a1-a2);
    ans = ans / 2;
    return ans;
}

long long calculateDepth2(int startr, int startc, std::vector<Move>& moveList, std::vector<std::string>& grid)
{
    std::unordered_map<char, std::pair<int,int>> dirMap;
    dirMap['U'] = {-1, 0};
    dirMap['D'] = {1, 0};
    dirMap['L'] = {0, -1};
    dirMap['R'] = {0, 1};
    long long boundary = 0;

    int r = startr, c = startc;
    grid[r][c] = '#';

    std::vector<std::pair<long,long>> coords; // holds x,y which is col, row

    for(auto move: moveList)
    {
        auto dxy = dirMap[move.dir];
        r += (dxy.first * move.moves);
        c += (dxy.second * move.moves);
        boundary += move.moves;
        // std::cout<<"r:c = "<<r<<":"<<c<<std::endl;
        coords.push_back({c,r});
    }


    std::cout<<"completed getting all vertices\n";

    long long area = shoelace(coords);
    std::cout<<"the area = "<<area<<" and boundary = "<<boundary<<std::endl;

    //picks theorem says that Area = Internal points + Boundary/2 -1;
    long long internal = area - boundary/2 + 1;
    std::cout<<"ans = "<<internal <<"+"<<boundary<<" = "<<internal + boundary<<std::endl;
    return internal + boundary;
}

// int main(int argc, char* argv[]){

//     std::string FILENAME = "test/day18input1.txt";
//     if(argc == 3)
//     {
//         std::string DAY = argv[1];
//         std::string INPUT = argv[2];

//         FILENAME = "test/day"
//         + DAY
//         + "input"
//         + INPUT
//         + ".txt";
//     }


//     std::ifstream file(FILENAME);
//     std::string line;

//     int H = 0;
//     int W = 0;
//     int maxH = 0;
//     int maxW = 0;
//     int minH = 0;
//     int minW = 0;

//     std::vector<Move> moveList;
//     while(std::getline(file, line))
//     {
//         std::stringstream ss(line);
//         char dir; int moves; std::string color;
//         ss >> dir >> moves >> color;
//         moveList.emplace_back(Move{dir, moves, color});

//         //  std::cout<<dir<<"->"<<moves<<"->"<<color<<std::endl;
//         if(dir =='R')
//         {
//             W+=moves;
//         }
//         if(dir == 'D')
//         {
//             H+=moves;
//         }
//         if(dir == 'L')
//         {
//             W-=moves;
//         }
//         if(dir == 'U')
//         {
//             H-=moves;
//         }

//         maxH = std::max(maxH, H);
//         maxW = std::max(maxW, W);
//         minH = std::min(minH, H);
//         minW = std::min(minW, W);
//     }

//     // std::cout<<H<<":"<<W<<std::endl;
//     // std::cout<<maxH<<":"<<maxW<<std::endl;
//     // std::cout<<minH<<":"<<minW<<std::endl;
//     // std::cout<<maxH - minH + 1<<":"<<maxW - minW + 1<<std::endl;

//     std::vector<std::string> grid(maxH-minH+1, std::string(maxW-minW+1, '.'));
//     // std::cout<<grid.size()<<"::"<<grid[0].size()<<std::endl;

//     std::vector<std::pair<int,int>> testSquare{{0,0}, {0,2}, {2,2}, {2,0}};
//     // std::cout<<"test shoelace:"<<shoelace(testSquare)<<std::endl;

//     calculateDepth2(minH * -1, minW * -1, moveList, grid);

// }


int main(int argc, char* argv[]){

    std::string FILENAME = "test/day18input1.txt";
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

    int H = 0;
    int W = 0;
    int maxH = 0;
    int maxW = 0;
    int minH = 0;
    int minW = 0;

    std::vector<char> hexDirMap{'R', 'D', 'L', 'U'};

    std::vector<Move> moveList;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        char dir; int moves; std::string color;
        ss >> dir >> moves >> color;

        dir = hexDirMap[color[7]-'0'];
        std::stringstream sss;
        sss << std::hex <<color.substr(2,5);
        sss >> moves;

        moveList.push_back(Move{dir, moves, color});
        // std::cout<<color<<" = "<<dir<<" "<<moves<<std::endl;

        //  std::cout<<dir<<"->"<<moves<<"->"<<color<<std::endl;
        if(dir =='R')
        {
            W+=moves;
        }
        if(dir == 'D')
        {
            H+=moves;
        }
        if(dir == 'L')
        {
            W-=moves;
        }
        if(dir == 'U')
        {
            H-=moves;
        }

        maxH = std::max(maxH, H);
        maxW = std::max(maxW, W);
        minH = std::min(minH, H);
        minW = std::min(minW, W);
    }

    // std::cout<<H<<":"<<W<<std::endl;
    // std::cout<<maxH<<":"<<maxW<<std::endl;
    // std::cout<<minH<<":"<<minW<<std::endl;
    // std::cout<<maxH - minH + 1<<":"<<maxW - minW + 1<<std::endl;

    std::vector<std::string> grid(maxH-minH+1, std::string(maxW-minW+1, '.'));
    std::cout<<grid.size()<<"::"<<grid[0].size()<<std::endl;


    calculateDepth2(0, 0, moveList, grid);

}
