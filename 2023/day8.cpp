
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node{
    std::string value;
    Node* left;
    Node* right;

    Node(std::string s):value(s){}
};

int findNumberOfStepsToReachZ(Node* start, std::string& directions)
{
    int steps = 0;
    int i = 0;
    int n = directions.length();

    Node* temp = start;
    while(temp->value[2]!='Z')
    {
        i = i % n;

        if(directions[i]=='L')
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }

        ++steps;
        ++i;

    }
    return steps;
}

bool allEndsWithZ(std::vector<Node*>& nodes)
{
    bool ans = true;

    for(Node* node: nodes)
    {
        ans  = ans && node->value[2] == 'Z';
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

    std::unordered_map<std::string, Node*> nodeMap;

    std::getline(file, line);
    std::string directions = line;

    std::cout<<directions<<std::endl;

    std::getline(file, line); //secape the first new line.

    /**
    0123456789jklmn
    AAA = (BBB, CCC)
    */

    std::vector<Node*> start;
    std::vector<Node*> dest;


    while( std::getline(file, line))
    {
        std::string node, left, right;
        node = line.substr(0,3);
        left = line.substr(7,3);
        right = line.substr(12,3);

        // std::cout<<node<<" "<<left<<" "<<right<<std::endl;

        if(!nodeMap.count(node))
        {
            nodeMap[node] = new Node(node);
        }

        if(!nodeMap.count(left))
        {
            nodeMap[left] = new Node(left);
        }

        if(!nodeMap.count(right))
        {
            nodeMap[right] = new Node(right);
        }

        nodeMap[node]->left = nodeMap[left];
        nodeMap[node]->right = nodeMap[right];

        if(node[2]=='A')
        {
            start.push_back(nodeMap[node]);
        }
    }


    std::cout<<"starting with ";
    for(int i=0;i<start.size(); i++){
        std::cout<<start[i]->value<<" ";
    }
    std::cout<<std::endl;






    //  while(!allEndsWithZ(start))
    //  {
    //     i = i % n;

    //     for(int index = 0; index < start.size(); ++index)
    //     {
    //         if(directions[i]=='L')
    //         {
    //             start[index] = start[index]->left;
    //         }
    //         else
    //         {
    //             start[index] = start[index]->right;
    //         }
    //     }


    //     // std::cout<<"go "<<directions[i]<<" to ";
    //     // for(int j=0;j<start.size(); j++){
    //     //     std::cout<<start[j]->value<<" ";
    //     // }
    //     // std::cout<<std::endl;
    //     ++steps;
    //     ++i;

    //  }

    for(int index = 0; index < start.size(); ++index)
    {
        int i = 0;
        long steps = 0;
        int n = directions.length();
        Node* temp = start[index];

        std::cout<<"from "<<temp->value;
        while (temp->value[2]!='Z') {
            i = i % n;
            // std::cout<<temp->value<<std::endl;
            // std::cout<<i;
            if(directions[i]=='L')
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }

            ++i;
            ++steps;
            // std::cout<<" "<<steps<<std::endl;
        }
        // std::cout<<temp->value<<std::endl;
         std::cout<<" to "<<temp->value<<" is "<<steps<<" steps\n";
        // break;

    }

    std::cout<<directions.length()<<std::endl;



   /**
from AAA to ZZZ is 292 steps
from GSA to SPZ is 282 steps
from QGA to GHZ is 318 steps
from LHA to HVZ is 295 steps
from LBA to NPZ is 301 steps
from XCA to NNZ is 284 steps

292 282 318 295 301 284
660337454669760
13757030305620
   */

}


