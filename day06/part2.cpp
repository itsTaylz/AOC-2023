#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>

struct Record
{
    int64_t time, distance;
};

int64_t CalculateWays(const Record& record)
{
    // a will always be -1
    int64_t a = -1;
    int64_t b = record.time;
    int64_t c = -record.distance;
    double binom = sqrt(pow(b, 2) - 4 * a * c);
    double root1 = (-b - binom) / (2 * a);
    double root2 = (-b + binom) / (2 * a);
    std::cout << "x1=" << root1 << " x2=" << root2 << std::endl;
    int64_t min = floor(std::min(root1, root2) + 1);
    int64_t max = ceil(std::max(root1, root2) - 1);
    return max - min + 1;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input file '" << argv[0] << "'" << std::endl;
        return -1;
    }
    // vector of pairs <time, distance>
    std::string firstLine;
    std::string secondLine;
    std::getline(inputFile, firstLine);
    std::getline(inputFile, secondLine);
    firstLine = firstLine.substr(firstLine.find(":") + 1, firstLine.length());
    secondLine = secondLine.substr(secondLine.find(":") + 1, secondLine.length());
    firstLine.erase(std::remove(firstLine.begin(), firstLine.end(), ' '), firstLine.end());
    secondLine.erase(std::remove(secondLine.begin(), secondLine.end(), ' '), secondLine.end());
    Record record;
    record.time = std::stol(firstLine);
    record.distance = std::stol(secondLine);
    std::cout << "t=" << record.time << std::endl;
    std::cout << "d=" << record.distance << std::endl;
    int64_t result = CalculateWays(record);
    std::cout << "Result: " << result << std::endl;
    return 0;
}