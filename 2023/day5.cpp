
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

struct RangeValue{
    long sourceStart;
    long sourceEnd;
    long destinationStart;
    long destinationEnd;

    bool operator<(const RangeValue& other)
    {
        return this->sourceEnd < other.sourceEnd;
    }

    void print()
    {
        std::cout<<"Range: "<<sourceStart<<"->"<<sourceEnd<<" "<<destinationStart<<"->"<<destinationEnd<<std::endl;
    }
};



std::vector<RangeValue> seedSoilMap;
std::vector<RangeValue> soilFertilizerMap;
std::vector<RangeValue> fertilizerWaterMap;
std::vector<RangeValue> waterLightMap;
std::vector<RangeValue> lightTemperatureMap;
std::vector<RangeValue> temperatureHumidityMap;
std::vector<RangeValue> humidityLocationMap;
std::unordered_map<long, long> seedLocationMap;

std::unordered_map<long, long> seedSoilDP;
std::unordered_map<long, long> soilFertilizerDP;
std::unordered_map<long, long> fertilizerWaterDP;
std::unordered_map<long, long> waterLightDP;
std::unordered_map<long, long> lightTemperatureDP;
std::unordered_map<long, long> temperatureHumidityDP;
std::unordered_map<long, long> humidityLocationDP;

std::unordered_map<std::vector<RangeValue>* , std::unordered_map<long, long>* > dpMap;



//split a string of numbers seperated by delimeters
std::vector<long> parseNumbers(std::string numbers, char delim = ' ')
{
    std::stringstream ss(numbers);
    std::string num;
    std::vector<long> ans;
    while(std::getline(ss, num, delim))
    {
        ans.push_back(std::stol(num));
    }
    std::for_each(ans.begin(), ans.end(),[](long val){std::cout<<val<<"->";}); std::cout<<std::endl;
    return ans;
}

void addToMap(std::vector<RangeValue>& myMap, const std::string& description)
{
    std::stringstream ss(description);
    long destination, source, range;
    ss >> destination>> source>> range;
    // std::cout<<destination<<" "<<source<<" "<<range<<"-->"<<description<<std::endl;

    myMap.emplace_back(RangeValue{source, source + range - 1, destination, destination + range -1});
}

long getValueFromMap(std::vector<RangeValue>& myMap, long key ){


    auto dp = dpMap[&myMap];

    if(dp->count(key))
    {
        return (*dp)[key];
    }

    int i = 0, j = myMap.size()-1;

    long ans = -1;
    while(i<=j)
    {
        int m = (i+j)/2;
        RangeValue r = myMap[m];
        // std::cout<<"getting key = "<<key<<"<->"<<i<<":"<<j<<"->"<<r.sourceStart<<" "<<r.sourceEnd<<"-->"<<r.destinationStart<<" "<<r.destinationEnd<<std::endl;

        if(r.sourceStart <= key && r.sourceEnd >=key)
        {
            // std::cout<<"I got my value  = "<<r.destinationStart + key - r.sourceStart<<std::endl;
            ans = r.destinationStart + key - r.sourceStart;
            //  std::cout<<"\n\n";
            return ans;
        }

        if(key > r.sourceEnd)
        {
            i = m + 1;
        }

        else if(key < r.sourceStart)
        {
            j = m-1;
        }
    }
    // std::cout<<"\n\n";
    (*dp)[key] = key;
    return key;

}

long getLocation(long seed){
    if(seedLocationMap.count(seed))
    {
        return seedLocationMap[seed];
    }
    long soil = getValueFromMap(seedSoilMap, seed);
    long fertilizer = getValueFromMap(soilFertilizerMap, soil);
    long water = getValueFromMap(fertilizerWaterMap, fertilizer);
    long light = getValueFromMap(waterLightMap, water);
    long temperature = getValueFromMap(lightTemperatureMap, light);
    long humidity = getValueFromMap(temperatureHumidityMap, temperature);
    long location = getValueFromMap(humidityLocationMap, humidity);

    // std::cout<<seed<<"->"<<soil<<"->"<<fertilizer<<"->"<<water<<"->"<<light<<"->"<<temperature<<"->"<<humidity<<"->"<<location<<"->"<<std::endl;
    seedLocationMap[seed] = location;
    return location;
}

long getLocation(long start, long end){
    std::vector<std::pair<long,long>> intervals;

   for(RangeValue r: seedSoilMap)
   {
        //check for intervals that intersenct in this range
       if(r.sourceStart <= end)
       {
        intervals.push_back({std::max(r.sourceStart, start), std::min(end, r.sourceEnd)});
       }

   }

//    std::cout<<"there are "<<intervals.size()<<" intervals\n";
    std::vector<long> locations;

    for(long i = start; i <= intervals[0].first; i++)
    {
        locations.push_back(getLocation(i));
    }
    for(auto interval:intervals)
    {
        locations.push_back(getLocation(interval.first));
        locations.push_back(getLocation(interval.second));
    }
    for(long i = intervals.back().second; i <= end; ++i)
    {
        locations.push_back(getLocation(i));
    }

   return *(std::min_element(locations.cbegin(), locations.cend()));
}

std::vector<std::pair<long, long> > mergeIntervals(std::vector<std::pair<long, long> >& seedIntervals)
{
    std::vector<std::pair<long, long> > newIntervals;
    long start = seedIntervals[0].first;
    long end = seedIntervals[0].second;

    for(int i = 1; i< seedIntervals.size(); i++)
    {
        auto pair = seedIntervals[i];
        if(pair.first <= end)
        {
            start = std::min(start, pair.first);
            end = std::max(end, pair.second);
        }
        else{
            newIntervals.push_back({start, end});
            start = pair.first;
            end = pair.second;
        }
    }

    newIntervals.push_back({start, end});
    return newIntervals;
}

void part1(std::ifstream& file)
{
    dpMap[&seedSoilMap] = &seedSoilDP;
    dpMap[&soilFertilizerMap] = &soilFertilizerDP;
    dpMap[&fertilizerWaterMap] = &fertilizerWaterDP;
    dpMap[&waterLightMap] = &waterLightDP;
    dpMap[&lightTemperatureMap] = &lightTemperatureDP;
    dpMap[&temperatureHumidityMap] = &temperatureHumidityDP;
    dpMap[&humidityLocationMap] = &humidityLocationDP;

    std::string line;

    std::getline(file, line);


    std::vector<long> seeds = parseNumbers(line.substr(7));
    std::vector<std::string> all;



    while(std::getline(file, line))
    {
        if(line == "")
        {
            continue;
        }
        all.push_back(line);
        // std::cout<<"push back line "<<line<<std::endl;
    }

    long i = 0;
    long n = all.size();
    while (i < n && i < all.size())
    {
        if(all[i]=="seed-to-soil map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(seedSoilMap, all[i]);
                i++;
            }

            for(RangeValue r: seedSoilMap)
            {
                r.print();
            }
        }

        if(all[i]=="soil-to-fertilizer map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(soilFertilizerMap, all[i]);
                i++;
            }
        }

        if(all[i]=="fertilizer-to-water map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(fertilizerWaterMap, all[i]);
                i++;
            }
        }

        if(all[i]=="water-to-light map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(waterLightMap, all[i]);
                i++;
            }
        }

        if(all[i]=="light-to-temperature map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(lightTemperatureMap, all[i]);
                i++;
            }
        }

        if(all[i]=="temperature-to-humidity map:")
        {
            i++;
            while(std::isdigit(all[i][0]))
            {
                addToMap(temperatureHumidityMap, all[i]);
                i++;
            }
        }

        if(all[i]=="humidity-to-location map:")
        {
            i++;
            while(i < n && std::isdigit(all[i][0]))
            {
                addToMap(humidityLocationMap, all[i]);
                i++;
            }
        }
        i++;
    }

    std::cout<<"started sorting\n";

    std::sort(seedSoilMap.begin(), seedSoilMap.end());
    std::sort(soilFertilizerMap.begin(), soilFertilizerMap.end());
    std::sort(fertilizerWaterMap.begin(), fertilizerWaterMap.end());
    std::sort(waterLightMap.begin(), waterLightMap.end());
    std::sort(lightTemperatureMap.begin(), lightTemperatureMap.end());
    std::sort(temperatureHumidityMap.begin(), temperatureHumidityMap.end());
    std::sort(humidityLocationMap.begin(), humidityLocationMap.end());

    std::cout<<"ended sorting\n";

    //  for(RangeValue r: seedSoilMap)
    // {
    //     r.print();
    // }


    std::vector<long> locations;
    // for(long seed: seeds)
    // {
    //     locations.push_back(getLocation(seed));
    //     // break;
    // }

    long seedSize = seeds.size();
    std::vector<std::pair<long, long> > seedIntervals;

    for(long i = 0; i<seedSize; i+=2)
    {
        long start = seeds[i];
        long range = seeds[i+1];

        seedIntervals.push_back({start, start+range-1});

    }

    std::cout<<"just aboue to read from map"<<std::endl;

    // std::sort(seedIntervals.begin(), seedIntervals.end(), [](std::pair<long, long> one, std::pair<long, long> two){
    //     if(one.second == two.second)
    //     {
    //         return one.first < two.first;
    //     }
    //     return one.second < two.second;
    // });

    // for(auto pair: seedIntervals)
    // {
    //     std::cout<<pair.first<<"->"<<pair.second<<" ";
    // }
    // std::cout<<std::endl;
    //to do 2 6
    int interval_to_do = 2;

    for(int index=0; index< seedIntervals.size(); index++){

        auto interval = seedIntervals[index];
        std::cout<<interval.first<<" ----------> "<<interval.second<<std::endl;
        // if(index==interval_to_do)
        // {
            long start = interval.first;
            long end = interval.second;

            // locations.push_back(getLocation(start, end));

            // for(long i = start; i <= end; i++)
            // {
                locations.push_back(getLocation(end));
                locations.push_back(getLocation(end-1));
                locations.push_back(getLocation(end+1));
            // }
            // break;
        // }
    }

    // std::cout<<getValueFromMap(seedSoilMap,79)<<std::endl;





    std::cout<<"the minimum location is "<<*(std::min_element(locations.cbegin(), locations.cend()))<<std::endl;
    // getValueFromMap(waterLightMap, 81);
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
    part1(file);

}


