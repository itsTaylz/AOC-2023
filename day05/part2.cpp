#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cstdint>

void ReadSeeds(std::ifstream& inputFile, std::unordered_set<uint32_t>& seeds)
{
    std::string line;
    std::getline(inputFile, line);
    std::string seedsStr = line.substr(line.find(":")+1, line.length());
    std::stringstream ss(seedsStr);
    while (!ss.eof())
    {
        uint32_t start, len;
        ss >> start;
        ss >> len;
        for (uint32_t i = 0; i < len; i++)
        {
            seeds.insert(start + i);
        }
    }
}

void PrintSet(const std::unordered_set<uint32_t>& set)
{
    for (const uint32_t& e : set)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    std::unordered_set<uint32_t> seeds;
    ReadSeeds(inputFile, seeds);
    std::string line;
    std::getline(inputFile, line); // skip blank
    std::getline(inputFile, line); // skip first header
    std::unordered_set<uint32_t> processing;
    while (std::getline(inputFile, line))
    {
        if (line == "") // blank line
        {
            for (const uint32_t& seed : seeds)
            {
                processing.insert(seed);
            }
            seeds = processing;
            processing.clear();
            std::getline(inputFile, line); // skip header
            std::cout << "MAPPING:" << std::endl;
            PrintSet(seeds);
            continue;
        }
        uint32_t dst;
        uint32_t src;
        uint32_t len;
        std::stringstream ss(line);
        ss >> dst;
        ss >> src;
        ss >> len;
        const std::unordered_set<uint32_t> copy = seeds;
        for (const uint32_t& seed : copy)
        {
            if (seed >= src && seed < src + len)
            {
                std::cout << "Testing " << seed << " for range " << src << "-" << src+len-1 << std::endl;
                uint32_t diff = seed - src;
                seeds.erase(seed);
                processing.insert(dst + diff);
            }
        }
    }
    for (const uint32_t& seed : seeds)
    {
        processing.insert(seed);
    }
    
    uint32_t min = UINT32_MAX;
    for (const uint32_t& seed : processing)
    {
        if (seed < min)
            min = seed;
    }
    std::cout << "Result: " << min << std::endl;
    return 0;
}