#include <iostream>
#include <fstream>
#include <vector>
#include <string>


bool ContainsAdjacentSymbol(const std::vector<std::string>& map, int32_t i, int32_t j)
{
    for (int32_t y = i-1; y <= i+1; y++)
    {
        for (int32_t x = j-1; x <= j+1; x++)
        {
            if (y >= 0 && y < map.size() && x >= 0 && x < map[y].length())
            {
                char c = map[y][x];
                if (!std::isdigit(c) && c != '.' && c != '\n' && c != '\r')
                {
                    return true;
                }
            }
        }
    }
    return false;
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
                bool symbolsFound = false;
                for (int32_t k = firstIndex; k <= lastIndex && !symbolsFound; k++)
                {
                    symbolsFound = ContainsAdjacentSymbol(map, i, k);
                }
                const std::string numbStr = mapLine.substr(firstIndex, lastIndex+1);
                int32_t num = std::stoi(numbStr);
                if (symbolsFound)
                {
                    sum += num;
                    std::cout << "ACCEPT: " << num << std::endl;
                }
                else
                {
                    std::cout << "DENY: " << num << std::endl;
                }
                firstIndex = -1;
                lastIndex = -1;
            }
        }
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}