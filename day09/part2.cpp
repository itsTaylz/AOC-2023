#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>

bool IsAllZerosSequence(const std::deque<int64_t>& sequence)
{
    for (const int64_t& num : sequence)
    {
        if (num != 0)
            return false;
    }
    return true;
}

int64_t CalculatePrevSequenceNumber(const std::deque<int64_t>& starting)
{
    std::vector<std::deque<int64_t>> sequences;
    sequences.push_back(starting);
    while (!IsAllZerosSequence(sequences[sequences.size() - 1]))
    {
        const std::deque<int64_t>& prev = sequences[sequences.size() - 1];
        std::deque<int64_t> next;
        for (int32_t i = 1; i < prev.size(); i++)
        {
            next.push_back(prev[i] - prev[i-1]);
        }
        sequences.push_back(next);
    }
    sequences[sequences.size() - 1].push_back(0);
    int64_t num = 0;
    for (int32_t i = sequences.size() - 2; i >= 0; i--)
    {
        int64_t first = sequences[i][0];
        int64_t diff = sequences[i+1][0];
        sequences[i].push_front(first - diff);
    }
    return sequences[0][0];
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
        std::cerr << "Failed to open file " << argv[1] << std::endl;
        return -1;
    }
    std::string line;
    int64_t sum = 0;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::deque<int64_t> sequence;
        while (!ss.eof())
        {
            int64_t num;
            ss >> num;
            sequence.push_back(num);
        }
        sum += CalculatePrevSequenceNumber(sequence);
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}