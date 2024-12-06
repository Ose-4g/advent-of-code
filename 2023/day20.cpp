
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>


struct Module{
    std::string id;
    std::vector<Module*> destinations;
    static long long NUMBER_HIGHS;
    static long long NUMBER_LOWS;
    static bool RX_LOWPULSE_SEEN;
    static bool CYCLE_CHECK;

    const int HIGH = 1;
    const int LOW = 0;
    std::queue<std::pair<std::string, int>> commandQueue;



    Module(std::string _id):id(_id){}

    enum class Type{
        FLIP_FLOP,
        CONJUNCTION,
        BROADCAST,
        BUTTON,
        OUTPUT
    };

    virtual const Type getType() = 0;
    virtual std::vector<Module*> getnextDestinations() = 0;

    void sendPulse(int pulse)
    {
        long long total = destinations.size();
        if(pulse == HIGH)
        {
            NUMBER_HIGHS += total;
        }
        else if(pulse == LOW)
        {
            NUMBER_LOWS += total;
        }

        for(auto &destination: destinations)
        {
            // std::cout<<"adding to queue in "<<destination->id<<" "<<id<<":"<<pulse<<std::endl;
            destination->commandQueue.push({id, pulse});
        }
    }

    void addDestination(Module* module)
    {
        destinations.push_back(module);
    }
};

long long Module::NUMBER_HIGHS = 0;
long long Module::NUMBER_LOWS = 0;
bool Module::RX_LOWPULSE_SEEN = false;
bool Module::CYCLE_CHECK = false;

struct FlipFlopModule: public Module{
    FlipFlopModule(std::string id):Module(id){}
    bool isOn = false;
    const Type getType(){
        return Type::FLIP_FLOP;
    };

    std::vector<Module*> getnextDestinations(){
        auto command = commandQueue.front(); commandQueue.pop();
        int receivedPulse = command.second;
        std::string senderId = command.first;

        //  std::cout<<senderId<<"--"<<receivedPulse<<"-->"<<id<<std::endl;

        // ignore high pulse
        if(receivedPulse == HIGH)
        {
            return std::vector<Module*>();
        }

        int pulseToSend = (isOn ? LOW : HIGH);
        isOn = !isOn;

        sendPulse(pulseToSend);
        return destinations;
    }
};


struct ConjunctionModule: public Module{
    ConjunctionModule(std::string id):Module(id){}
    std::unordered_map<std::string, int> rememberMap;

    const Type getType(){
        return Type::CONJUNCTION;
    };

    void addInput(std::string id)
    {
        rememberMap[id] = LOW;
    }

    std::vector<Module*> getnextDestinations(){
         auto command = commandQueue.front(); commandQueue.pop();
        int receivedPulse = command.second;
        std::string senderId = command.first;

        //  std::cout<<senderId<<"--"<<receivedPulse<<"-->"<<id<<std::endl;

        rememberMap[senderId] = receivedPulse;
        int pulseToSend = LOW;

        // if all are high then send a lpw pulse
        for(auto &k: rememberMap)
        {
            if(k.second == LOW)
            {
                pulseToSend = (HIGH);
                break;
            }
        }

        if(pulseToSend == HIGH && id=="gp") CYCLE_CHECK = true;

       sendPulse(pulseToSend);

        return destinations;

    }
};

struct BroadcastModule: public Module{
    BroadcastModule(std::string id):Module(id){}
    std::unordered_map<std::string, int> rememberMap;

    const Type getType(){
        return Type::BROADCAST;
    };

    std::vector<Module*> getnextDestinations(){
        // if(commandQueue.empty()) std::cout<<id<<" command queue empty\n";
        auto command = commandQueue.front(); commandQueue.pop();
        int receivedPulse = command.second;
        std::string senderId = command.first;

        //  std::cout<<senderId<<"--"<<receivedPulse<<"-->"<<id<<std::endl;

        sendPulse(receivedPulse);
        return destinations;
    }
};

struct ButtonModule: public Module{
    ButtonModule():Module("button"){}

    const Type getType(){
        return Type::BUTTON;
    };

    std::vector<Module*> getnextDestinations(){
        sendPulse(LOW);
        return destinations;
    }
};

struct OutputModule: public Module{
    OutputModule(std::string id):Module(id){}

    const Type getType(){
        return Type::OUTPUT;
    };

    std::vector<Module*> getnextDestinations(){
        auto command = commandQueue.front(); commandQueue.pop();
        int receivedPulse = command.second;
        std::string senderId = command.first;

        if(id == "rx" && receivedPulse == LOW)
        {
            RX_LOWPULSE_SEEN = true;
        }
        // std::cout<<senderId<<"--"<<receivedPulse<<"-->"<<id<<std::endl;
        return std::vector<Module*>();
    }
};

std::vector<std::string> parseOutputs(std::string line)
{
    std::vector<std::string> ans;
    line += ',';
    std::string temp;
    for(char c: line)
    {
        if(c==' ')
        {
            continue;
        }
        if(c==',')
        {
            ans.push_back(temp);
            // std::cout<<"'"<<temp<<"'\n";
            temp = "";
            continue;
        }
        temp += c;
    }
    // std::cout<<"\n\n";
    return ans;
}

void BFS(Module* button)
{
    std::queue<Module*> queue;

    queue.push(button);

    while(!queue.empty())
    {
        Module* front = queue.front(); queue.pop();

        // std::cout<<front->id<<"::";
        auto dests = front->getnextDestinations();
        for(Module* module: dests)
        {
            // std::cout<<module->id<<",";
            queue.push(module);
        }
        // std::cout<<"\n";
    }
}

int main(int argc, char* argv[]){

    std::string FILENAME = "test/day20input1.txt";
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

    std::unordered_map<std::string, std::vector<std::string>> idOutputMap;
    std::unordered_map<std::string, Module*> idModuleMap;
    BroadcastModule* broadcast;
    ButtonModule* button = new ButtonModule();

    while(std::getline(file, line))
    {
        // std::cout<< line <<std::endl;
        int dash = line.find('-');
        std::vector<std::string> outputs = parseOutputs(line.substr(dash+2));
        std::string id = line.substr(0, dash-1);

        // flip flop module
        if(line[0]=='%')
        {
            id = id.substr(1);
            idModuleMap[id] = new FlipFlopModule(id);
            // std::cout<<"fliptl "<<id<<std::endl;
        }
        else if(line[0]=='&')
        {
            id = id.substr(1);
            idModuleMap[id] = new ConjunctionModule(id);
        }

        else{
            broadcast = new BroadcastModule(id);
            idModuleMap[id] = broadcast;
        }

        idOutputMap[id] = outputs;
    }

    button->addDestination(broadcast);

    for(auto &k: idOutputMap){
        std::string id = k.first;
        Module* module = idModuleMap[k.first];

        for(std::string destinationId: k.second)
        {
            if(!idModuleMap.count(destinationId))
            {
                idModuleMap[destinationId] = new OutputModule(destinationId);
            }
            module->addDestination(idModuleMap[destinationId]);

            if(idModuleMap[destinationId]->getType() == Module::Type::CONJUNCTION)
            {
                dynamic_cast<ConjunctionModule*>(idModuleMap[destinationId])->addInput(id);
            }
        }
    }

    for(auto &k: idModuleMap)
    {
        std::cout<<k.first<<"::";
        for(auto d: k.second->destinations)
        {
            std::cout<<d->id<<", ";
        }

        if(k.second->getType()==Module::Type::CONJUNCTION)
        {
            std::cout<<"ths input are :";
            for(auto &k: dynamic_cast<ConjunctionModule*>(k.second)->rememberMap)
            {
                std::cout<<k.first<<", ";
            }
        }
        std::cout<<"\n\n";
    }


    long long i = 0;
    long long prev = 0;

    while(true)
    {
        BFS(button);

        if(Module::CYCLE_CHECK)
        {
            std::cout<<i-prev<<std::endl;
            prev = i;
            Module::CYCLE_CHECK = false;
        }
        i++;
    }

    std::cout<<"button pressed "<<i<<" times to get low pulse to rx"<<std::endl;

    std::cout<<"highs = "<<Module::NUMBER_HIGHS<<std::endl;
    std::cout<<"lows = "<<Module::NUMBER_LOWS<<std::endl;
    std::cout<<"product = "<<Module::NUMBER_LOWS * Module::NUMBER_HIGHS<<std::endl;

}


