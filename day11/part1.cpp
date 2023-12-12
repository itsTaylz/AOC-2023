#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

bool ContainsInCol(const std::vector<std::string>& map, int32_t col, char c)
{
    for (int32_t i = 0; i < map[0].size(); i++)
    {
        if (map[i][col] == c)
            return true;
    }
    return false;
}

void Transpose(std::vector<std::string>& map)
{
    std::vector<std::string> tranposed;
    for (int32_t i = 0; i < map[0].size(); i++)
    {
        tranposed.push_back("");
    }
    for (int32_t i = 0; i < map.size(); i++)
    {
        for (int32_t j = 0; j < map[i].size(); j++)
        {
            tranposed[j].push_back(map[i][j]);
        }
    }
    map = tranposed;
}

void ExpandLines(std::vector<std::string>& map)
{
    for (int32_t i = 0; i < map.size(); i++)
    {
        const std::string& line = map[i];
        // expand lines
        if (line.find("#") == line.npos)
        {
            map.insert(map.begin() + i, line);
            i++;
        }
    }
}

void ExpandMap(std::vector<std::string>& map)
{
    ExpandLines(map);
    Transpose(map);
    ExpandLines(map);
    Transpose(map);
}

void GetGalaxiesPositions(const std::vector<std::string>& map, std::vector<std::pair<int32_t, int32_t>>& positions)
{
    for (int32_t i = 0; i < map.size(); i++)
    {
        for (int32_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == '#')
                positions.push_back({i, j});
        }
    }
}

int32_t ManhathanDistance(const std::pair<int32_t, int32_t>& pos1, const std::pair<int32_t, int32_t>& pos2)
{
    return std::abs(pos1.first - pos2.first) + std::abs(pos1.second - pos2.second);
}

int32_t CalculateSumDistance(const std::vector<std::string>& map)
{
    std::vector<std::pair<int32_t, int32_t>> positions;
    GetGalaxiesPositions(map, positions);
    int32_t sum = 0;
    int32_t count = 0;
    for (int32_t i = 0; i < positions.size(); i++)
    {
        for (int32_t j = i+1; j < positions.size(); j++)
        {
            std::cout << "G1 = " << positions[i].first << " " << positions[i].second << std::endl;
            std::cout << "G2 = " << positions[j].first << " " << positions[j].second << std::endl;
            int32_t dist = ManhathanDistance(positions[i], positions[j]);
            std::cout << "Dist = " << dist << std::endl;
            std::cout << "-------------------------------" << std::endl;
            sum += ManhathanDistance(positions[i], positions[j]);
            count++;
        }
    }
    std::cout << "Pairs: " << count << std::endl;
    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[1] << " <file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open file " << argv[1] << std::endl;
        return -1;
    }
    std::vector<std::string> map;
    std::string line;
    while (std::getline(inputFile, line))
    {
        map.push_back(line);
    }
    std::cout << map.size() << std::endl;
    std::cout << "Expanding map..." << std::endl;
    ExpandMap(map);
    for (const std::string& s : map)
    {
        std::cout << s << std::endl;
    }
    int32_t result = CalculateSumDistance(map);
    std::cout << "Result: " << result << std::endl;
    std::pair<int32_t, int32_t> p1 = {0, 3};
    std::pair<int32_t, int32_t> p2 = {3, 7};
    std::cout << ManhathanDistance(p1, p2) << std::endl;
    return 0;
}