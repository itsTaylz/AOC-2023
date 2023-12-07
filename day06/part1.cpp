#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>

struct Record
{
    int32_t time, distance;
};

int32_t CalculateWays(const Record& record)
{
    // a will always be -1
    int32_t a = -1;
    int32_t b = record.time;
    int32_t c = -record.distance;
    float binom = sqrt(pow(b, 2) - 4 * a * c);
    float root1 = (-b - binom) / (2 * a);
    float root2 = (-b + binom) / (2 * a);
    std::cout << "x1=" << root1 << " x2=" << root2 << std::endl;
    int32_t min = floor(std::min(root1, root2) + 1);
    int32_t max = ceil(std::max(root1, root2) - 1);
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
    std::vector<Record> records;
    std::string firstLine;
    std::string secondLine;
    std::getline(inputFile, firstLine);
    std::getline(inputFile, secondLine);
    firstLine = firstLine.substr(firstLine.find(":") + 1, firstLine.length());
    secondLine = secondLine.substr(secondLine.find(":") + 1, secondLine.length());
    std::stringstream firstSS(firstLine);
    std::stringstream secondSS(secondLine);
    while (!firstSS.eof())
    {
        Record record;
        firstSS >> record.time;
        secondSS >> record.distance;
        records.push_back(record);
    }
    int32_t total = 1;
    for (const Record& record : records)
    {
        std::cout << "Record: t=" << record.time << " d=" << record.distance << std::endl;
        int32_t ways = CalculateWays(record);
        std::cout << "Ways: " << ways << std::endl;
        total *= ways;
    }
    std::cout << "Result: " << total << std::endl;
    return 0;
}