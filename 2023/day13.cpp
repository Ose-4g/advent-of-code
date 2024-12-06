
#include <iostream>
#include <fstream>
#include <string>
#include<vector>

bool checkVertical(std::vector<std::string>& pattern, int i, int j)
{
    //check if they reflect vertically
    // we're moving left and right
    int coln = pattern[0].length();
    int rown = pattern.size();

    while(i>=0 && j < coln)
    {
        for(int row = 0; row < rown; ++row)
        {
            if(pattern[row][i] != pattern[row][j])
            {
                return false;
            }
        }

        i--;
        j++;
    }
    return true;
}

bool checkHorizontal(std::vector<std::string>& pattern, int i, int j)
{
    // we're moving up and down
    // check that they reflect horizonally
    int coln = pattern[0].length();
    int rown = pattern.size();

    while(i>=0 && j < rown)
    {
        for(int col = 0; col < coln; ++col)
        {
            if(pattern[i][col] != pattern[j][col])
            {
                return false;
            }
        }

        i--;
        j++;
    }
    return true;
}

bool checkVertical2(std::vector<std::string>& pattern, int i, int j)
{
    //check if they reflect vertically
    // we're moving left and right
    //there must be one mismatch
    int coln = pattern[0].length();
    int rown = pattern.size();
    bool mismatchFound = false;

    while(i>=0 && j < coln)
    {
        for(int row = 0; row < rown; ++row)
        {
            if(pattern[row][i] != pattern[row][j])
            {
                if(!mismatchFound)
                {
                    mismatchFound = true;
                }
                else {
                    return false;
                }
            }
        }

        i--;
        j++;
    }
    return mismatchFound;
}

bool checkHorizontal2(std::vector<std::string>& pattern, int i, int j)
{
    // we're moving up and down
    // check that they reflect horizonally
    //there must be one mismatch
    int coln = pattern[0].length();
    int rown = pattern.size();
    bool mismatchFound = false;

    while(i>=0 && j < rown)
    {
        for(int col = 0; col < coln; ++col)
        {
            if(pattern[i][col] != pattern[j][col])
            {
                if(!mismatchFound)
                {
                    mismatchFound = true;
                }
                else
                {
                    return false;
                }
            }
        }

        i--;
        j++;
    }
    return mismatchFound;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day13input1.txt";
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

    std::vector<std::vector<std::string> > patterns;

    std::vector<std::string> pattern;

    while(std::getline(file, line))
    {
        if(line == "")
        {
            // std::cout<<"finsihed parseing pattern\n\n";
            patterns.push_back(pattern);
            pattern.clear();
            // add up the characters

        }
        else{
            // std::cout<<line<<std::endl;
            pattern.push_back(line);
        }

    }

    if(pattern.size() > 0)
    {
        patterns.push_back(pattern);
    }

    long ans = 0;

    for(auto &pattern: patterns)
    {
        int rown = pattern.size(), coln = pattern[0].length();

        // check vertical
        int i = 0, j = 1;

        int verticalDivide = -1;
        int horizontalDivide = -1;

        while(j < coln)
        {
            if(checkVertical2(pattern, i, j))
            {
                verticalDivide = i;
                break;
            }
            j++;
            i++;
        }

        i = 0, j = 1;
        while(verticalDivide == -1 && j < rown){
            if(checkHorizontal2(pattern, i, j))
            {
                horizontalDivide = i;
                break;
            }
            j++;
            i++;
        }

        std::cout<<verticalDivide+1<<" "<<horizontalDivide+1<<std::endl;

        if(verticalDivide != -1)
        {
            ans += (verticalDivide + 1);
        }
        else if(horizontalDivide != -1){
            ans += (100 * (horizontalDivide+1));
        }

    }

    std::cout<<"answer = "<<ans<<std::endl;


}


