#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>


void GetGearsNumbers(const std::vector<std::string>& map, int32_t i, int32_t firstIndex, int32_t lastIndex, int32_t number, 
                                std::unordered_multimap<std::string, int32_t>& gears)
{
    for (int32_t y = i-1; y <= i+1; y++)
    {
        for (int32_t x = firstIndex-1; x <= lastIndex+1; x++)
        {
            if (y >= 0 && y < map.size() && x >= 0 && x < map[y].length())
            {
                char c = map[y][x];
                if (c == '*')
                {
                    std::string key = std::to_string(y) + "," + std::to_string(x);
                    gears.insert({key, number});
                }
            }
        }
    }
}





int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[1] << " <file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    std::vector<std::string> map;
    std::string line;
    while (std::getline(inputFile, line))
    {
        map.push_back(line);
    }
    int32_t sum = 0;
    std::unordered_multimap<std::string, int32_t> gears;
    for (int32_t i = 0; i < map.size(); i++)
    {
        const std::string& mapLine = map[i];
        int32_t firstIndex = -1;
        int32_t lastIndex = -1;
        for (int32_t j = 0; j < mapLine.length(); j++)
        {
            if (firstIndex == -1 && std::isdigit(mapLine[j]))
                firstIndex = j;
            if (firstIndex != -1 && !std::isdigit(mapLine[j]))
                lastIndex = j-1;
            if (firstIndex != -1 && lastIndex == -1 && j == mapLine.length() - 1)
                lastIndex = j;
            if (firstIndex != -1 && lastIndex != -1)
            {
                const std::string numbStr = mapLine.substr(firstIndex, lastIndex+1);
                int32_t num = std::stoi(numbStr);
                GetGearsNumbers(map, i, firstIndex, lastIndex, num, gears);
                firstIndex = -1;
                lastIndex = -1;
            }
        }
    }
    std::string curr = gears.begin()->first;
    for (auto it = gears.begin(); it != gears.end();)
    {
        int32_t power = 1;
        int32_t count = 0;
        while (it != gears.end() && it->first == curr)
        {
            count++;
            power *= it->second;
            it++;
        }
        if (count == 2)
            sum += power;
        if (it != gears.end())
            curr = it->first;
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}