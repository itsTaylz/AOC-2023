#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

uint32_t FindPower(const std::string& rounds)
{
    uint32_t maxRed = 0;
    uint32_t maxBlue = 0;
    uint32_t maxGreen = 0;
    std::stringstream ss(rounds);
    while (!ss.eof())
    {
        uint32_t amount;
        std::string color;
        ss >> amount;
        ss >> color;
        if (color[color.length() - 1] == ';' || color[color.length() - 1] == ',')
            color = color.substr(0, color.length() - 1);
        if (color == "blue" && amount > maxBlue)
            maxBlue = amount;
        if (color == "red" && amount > maxRed)
            maxRed = amount;
        if (color == "green" && amount > maxGreen)
            maxGreen = amount;
    }
    return maxRed * maxBlue * maxGreen;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "<file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    uint32_t id = 1;
    std::string line;
    uint32_t sum = 0;
    while (std::getline(inputFile, line))
    {
        bool impossible = false;
        size_t dots = line.find(":");
        std::string substr = line.substr(dots + 2, line.length());
        sum += FindPower(substr);
        id++;
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}