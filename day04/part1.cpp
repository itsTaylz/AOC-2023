#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <cmath>


int32_t CalculateWinningNumbers(const std::string& card)
{
    int32_t amountOfWinningNumbers = 0;
    size_t dots = card.find(":");
    std::string substr = card.substr(dots + 2, card.length());
    size_t bar = substr.find("|");
    std::string winningNumbersStr = substr.substr(0, bar);
    std::string cardNumbersStr = substr.substr(bar+1, substr.length());
    std::unordered_set<int32_t> winningNumbers;
    std::stringstream winningSS(winningNumbersStr);
    while (!winningSS.eof())
    {
        int32_t num;
        winningSS >> num;
        winningNumbers.insert(num);
    }
    std::stringstream cardSS(cardNumbersStr);
    while (!cardSS.eof())
    {
        int32_t num;
        cardSS >> num;
        if (winningNumbers.count(num) > 0)
            amountOfWinningNumbers++;
    }
    return amountOfWinningNumbers;
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "<file>" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    std::string line;
    int32_t totalPoints = 0;
    while (std::getline(inputFile, line))
    {
        int32_t amountOfWinningNumbers = CalculateWinningNumbers(line);
        if (amountOfWinningNumbers > 0)
        {
            int32_t points = std::pow(2, amountOfWinningNumbers-1);
            std::cout << points << " points!" << std::endl;
            totalPoints += points;
        }
        else
        {
            std::cout << "No points :(" << std::endl;
        }
    }
    std::cout << "Result: " << totalPoints << std::endl;
}
