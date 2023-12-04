#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <unordered_map>

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
    std::unordered_map<int32_t, int32_t> cardsCopies;
    std::ifstream inputFile(argv[1]);
    std::string line;
    int32_t totalPoints = 0;
    for (int32_t i = 1; std::getline(inputFile, line); i++)
    {
        int32_t amountOfWinningNumbers = CalculateWinningNumbers(line);
        int32_t instances = 1 + cardsCopies[i];
        std::cout << "Card " << i << " has " << instances << " instances." << std::endl;
        totalPoints += instances;
        for (int32_t j = 1; j <= amountOfWinningNumbers; j++)
        {
            cardsCopies[i+j] += instances;
        }
    }
    std::cout << "Result: " << totalPoints << std::endl;
}
