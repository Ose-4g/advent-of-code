
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

namespace {
    const int FIVE_OF_A_KIND = 127;
    const int FOUR_OF_A_KIND = 63;
    const int FULL_HOUSE = 31;
    const int THREE_OF_A_KIND = 15;
    const int TWO_PAIR = 7;
    const int ONE_PAIR = 3;
    const int HIGH_CARD = 1;};

int getHandType(std::string cards)
{
    // std::cout<<"testing for "<<cards<<std::endl;
    std::unordered_map<char, int> cardCountMap;

    for(char c: cards)
    {
        cardCountMap[c]++;
    }

    if(cardCountMap.size() == 5)
    {
        return HIGH_CARD;
    }

    if(cardCountMap.size() == 1 )
    {
        return FIVE_OF_A_KIND;
    }

    std::unordered_map<int, std::vector<char> > countCardMap;

    for(auto &k: cardCountMap)
    {
        countCardMap[k.second].push_back(k.first);
    }

    if(countCardMap.count(4) && countCardMap.count(1))
    {
        return FOUR_OF_A_KIND;
    }

    if(countCardMap.count(3))
    {
        if(countCardMap.count(2))
        {
            return FULL_HOUSE;
        }
        if(countCardMap.count(1))
        {
            return THREE_OF_A_KIND;
        }
    }

    if(countCardMap.count(2) && countCardMap[2].size()==2)
    {
        return TWO_PAIR;
    }

    if(countCardMap.count(2) && countCardMap[2].size()==1)
    {
        return ONE_PAIR;
    }
    return 0;
}

int getHandType2(std::string cards)
{
    // find the positions of J
    // get all charcaters that are not j

    // for each character, replace all js with the character, that will give you the maximum value for that character.
    std::vector<char> nonJChars;
    std::vector<int> jPositions;

    for(int i = 0; i < 5; ++i)
    {
        if(cards[i] == 'J')
        {
            jPositions.push_back(i);
        }
        else
        {
            nonJChars.push_back(cards[i]);
        }
    }

    if(nonJChars.size() == 0)
    {
        return FIVE_OF_A_KIND;
    }
    int handType = 0;

    for(char c: nonJChars)
    {
        for(int pos: jPositions)
        {
            cards[pos] = c;
        }
        handType = std::max(handType, getHandType(cards));
    }

    for(int pos: jPositions)
        {
            cards[pos] = 'J';
        }

    return handType;
}

int compare(std::string card1, std::string card2 ){
    std::unordered_map<char, int> symbolRank;
    symbolRank['A'] = 13;
    symbolRank['K'] = 12;
    symbolRank['Q'] = 11;
    symbolRank['J'] = 10;
    symbolRank['T'] = 9;
    symbolRank['9'] = 8;
    symbolRank['8'] = 7;
    symbolRank['7'] = 6;
    symbolRank['6'] = 5;
    symbolRank['5'] = 4;
    symbolRank['4'] = 3;
    symbolRank['3'] = 2;
    symbolRank['2'] = 1;


    int rank1 = getHandType(card1), rank2 = getHandType(card2);

    if(rank1 == rank2)
    {
        for(int i=0; i<5; ++i)
        {
            if(card1[i]==card2[i])
            {
                continue;
            }

            if(symbolRank[card1[i]] > symbolRank[card2[i]])
            {
                return 1;
            }
            else if(symbolRank[card1[i]] < symbolRank[card2[i]])
            {
                return -1;
            }
        }

        return 0;
    }

    return rank1 > rank2 ? 1 : -1;
}

int compare2(std::string card1, std::string card2 ){
    std::unordered_map<char, int> symbolRank;
    symbolRank['A'] = 13;
    symbolRank['K'] = 12;
    symbolRank['Q'] = 11;
    symbolRank['T'] = 9;
    symbolRank['9'] = 8;
    symbolRank['8'] = 7;
    symbolRank['7'] = 6;
    symbolRank['6'] = 5;
    symbolRank['5'] = 4;
    symbolRank['4'] = 3;
    symbolRank['3'] = 2;
    symbolRank['2'] = 1;
    symbolRank['J'] = 0;


    int rank1 = getHandType2(card1), rank2 = getHandType2(card2);

    if(rank1 == rank2)
    {
        for(int i=0; i<5; ++i)
        {
            if(card1[i]==card2[i])
            {
                continue;
            }

            if(symbolRank[card1[i]] > symbolRank[card2[i]])
            {
                return 1;
            }
            else if(symbolRank[card1[i]] < symbolRank[card2[i]])
            {
                return -1;
            }
        }

        return 0;
    }

    return rank1 > rank2 ? 1 : -1;
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day7input1.txt";
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

    std::unordered_map<std::string, int> cardBidMap;
    std::vector<std::string> cards;

    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string card;
        int bid;

        ss >> card >> bid;

        cardBidMap[card] = bid;
        cards.push_back((card));

        // std::cout<<"card = "<<card<<" and bid = "<<bid<<std::endl;
    }

    std::sort(cards.begin(), cards.end(), [](const std::string& card1, const std::string& card2){
        return compare2(card1, card2) < 0;
    });

    int finalRank = 1;
    long ans = 0;

    std::for_each(cards.cbegin(), cards.cend(), [&finalRank, &cardBidMap, &ans](const std::string card){
        std::cout<<card<<" rank = "<<finalRank<<std::endl;
        ans += cardBidMap[card] * finalRank;
        finalRank++;
    });

    std::cout<<"ans = "<<ans<<std::endl;

    // std::cout<<getHandType("AAAAA")<<std::endl;
    // std::cout<<getHandType("AA8AA")<<std::endl;
    // std::cout<<getHandType("23323")<<std::endl;
    // std::cout<<getHandType("TT9T8")<<std::endl;
    // std::cout<<getHandType2("T55J5")<<std::endl;
    // std::cout<<getHandType("A23A4")<<std::endl;
    // std::cout<<getHandType("23456")<<std::endl;



}


