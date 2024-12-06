
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <algorithm>


struct LensRecord{
    static int START_TIME;
    int timestamp;
    std::string label;
    int focal_length;

    LensRecord(){}
    LensRecord(std::string label, int focal_length){
        this->focal_length = focal_length;
        this->label = label;
        this->timestamp = START_TIME++;
    }

    bool operator<(LensRecord& other)
    {
        return timestamp < other.timestamp;
    }
};

int LensRecord::START_TIME = 0;

std::ostream& operator<<(std::ostream& output, LensRecord& record)
{
    output<<record.label<<":"<<record.focal_length<<"::"<<record.timestamp;
    return output;
}



int getHash(std::string code){
    int ans = 0;

    for(char& c: code)
    {
        if(c=='\n')
        {
            continue;
        }
        ans += c;
        ans *= 17;
        ans %= 256;
    }
    std::cout<<code<<" = "<<ans<<std::endl;
    return ans;
}

int getHash2(std::string code){
    int ans = 0;

    for(char& c: code)
    {
        if(c=='\n')
        {
            continue;
        }
        if(c == '-' || c == '=')
        {
            break;
        }
        ans += c;
        ans *= 17;
        ans %= 256;
    }
    // std::cout<<code<<" = "<<ans<<std::endl;
    return ans;
}

void processCode(std::string& code, int box, std::vector<std::unordered_map<std::string, LensRecord> > &boxes)
{
    int n = code.length();
    std::string label;

    if(code[n-1]=='-')
    {
        label = code.substr(0, n-1);
        if(boxes[box].count(label))
        {
            boxes[box].erase(label);
        }
        return;
    }

    int equalsPos = code.find('=');

    label = code.substr(0,equalsPos);
    int focal = stoi(code.substr(equalsPos+1));

    // if the label already existed simply upgrade the focal length
    if(boxes[box].count(label))
    {
        boxes[box][label].focal_length = focal;
        return;
    }
    boxes[box][label] = LensRecord(label, focal);


}


int main(int argc, char* argv[]){

    std::string FILENAME = "test/day15input1.txt";
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
    std::string code;
    std::string all;

    std::vector<std::unordered_map<std::string, LensRecord> > boxes(256);

    long ans = 0;
    std::getline(file, all);
    std::stringstream ss(all);


    while(std::getline(ss, code, ','))
    {
        // std::cout<< code <<std::endl;
        int box = getHash2(code);
        processCode(code, box, boxes);
    }

    int i = 0;
    for(auto box: boxes)
    {
        int rank = i+1;
        std::vector<LensRecord> slots;
        // std::cout<<i<<" ";
        for(auto &k: box)
        {
            // std::cout<<":"<<k.second<<" ";
            slots.push_back(k.second);
        }
        std::sort(slots.begin(), slots.end());

        for(int slot = 0; slot < slots.size(); slot++)
        {
            long val = rank * (slot + 1) * slots[slot].focal_length;
            std::cout<<slots[slot].label<<" "<<rank<<"*"<<slot + 1<<"*"<<slots[slot].focal_length<<" = "<<val<<std::endl;
            ans += val;
        }
        // std::cout<<"\n";
        i++;
    }

    std::cout<<"ans = "<<ans<<std::endl;


}


