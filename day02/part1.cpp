#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

static constexpr uint32_t MAX_RED = 12;
static constexpr uint32_t MAX_GREEN = 13;
static constexpr uint32_t MAX_BLUE = 14;

bool CheckIfPossible(const std::string& rounds)
{
    std::stringstream ss(rounds);
    while (!ss.eof())
    {
        uint32_t amount;
        std::string color;
        ss >> amount;
        ss >> color;
        if (color[color.length() - 1] == ';' || color[color.length() - 1] == ',')
            color = color.substr(0, color.length() - 1);
        if (color == "red" && amount > MAX_RED || color == "blue" && amount > MAX_BLUE || color == "green" && amount > MAX_GREEN)
            return false;
    }
    return true;
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
        if (CheckIfPossible(substr))
            sum += id;
        id++;
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}