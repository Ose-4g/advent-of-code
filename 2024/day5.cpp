
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>

using Graph = std::unordered_map<int,std::unordered_set<int>>;

std::vector<int> getList(const std::string& line)
{
    std::stringstream ss(line);
    int num;
    std::vector<int> ans;
    while(ss >> num){
        ans.push_back(num);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return ans;
}

bool isValid(const std::vector<int>& query, Graph& graph)
{
    int n = query.size();

    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            // graph t->u means t comes before u
            // here 
            int front = query[i];
            int back = query[j];
            if(graph[back].count(front))
            {
                return false;
            }
        }
    }

    return true;
}

void sort(std::vector<int>& query, Graph& graph)
{
    auto isLess = [&graph](int a, int b){
        return graph[a].count(b);
    };
    std::sort(query.begin(), query.end(), isLess);
}

long long processQueries(std::vector<std::vector<int>>& queries, Graph& graph)
{
    long long ans = 0;
    for(auto& query: queries)
    {
        if(isValid(query, graph))
        {
            // std::cout<<"good\n";
            // std::cout<<query[query.size()/2]<<"note\n";
            // ans += query[query.size()/2];
        }
        else
        {
            sort(query, graph);
            // for(int i: query)
            // {
            //     std::cout<<i<<",";
            // }
            // std::cout<<std::endl;
            ans += query[query.size()/2];
        }
    }

    return ans;
}
int main(int argc, char* argv[]){

    std::string FILENAME = "test/day5input1.txt";
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

    Graph graph;
    std::vector<std::vector<int>> queries;
    bool graphComplete = false;


    while(std::getline(file, line))
    {
        if(graphComplete)
        {
            queries.push_back(getList(line));
            continue;
        }

        if(line == "")
        {
            graphComplete = true;
            continue;
        }
        
        int bar = line.find('|');
        int start = std::stoi(line.substr(0,bar)); int end = std::stoi(line.substr(bar+1));
        graph[start].insert(end);
    }

   

    std::cout<<"The ans is "<<processQueries(queries, graph)<<std::endl;
}


