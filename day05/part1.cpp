#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cstdint>

class Range
{
private:
    uint32_t start;
    uint32_t end;

public:
    Range(uint32_t start, uint32_t end) : start(start), end(end) { }

    const bool InsideOf(const Range& other) const
    {
        return this->start >= other.start && this->end <= other.end;
    }

    bool operator==(const Range& other) const
    {
        return true;
    }

    friend class std::hash<Range>;
};

template<>
struct std::hash<Range>
{
    std::size_t operator()(const Range& range) const
    {
        std::hash<uint32_t> hasher;
        return hasher(range.start) + hasher(range.end);
    }
};

void ReadSeeds(std::ifstream& inputFile, std::unordered_set<Range>& seeds)
{
    std::string line;
    std::getline(inputFile, line);
    std::string seedsStr = line.substr(line.find(":")+1, line.length());
    std::stringstream ss(seedsStr);
    while (!ss.eof())
    {
        uint32_t start, len;
        ss >> start >> len;
        Range r(start, start+len-1);
        seeds.insert(r);
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
    std::unordered_set<Range> seeds;
    ReadSeeds(inputFile, seeds);
    std::string line;
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    std::unordered_set<uint32_t> processing;
    while (std::getline(inputFile, line))
    {
        
    }
    return 0;
}