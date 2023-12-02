#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


static int ConvertToDigit(const std::string& s, std::vector<std::string>& strings)
{
    if (s.length() == 1)
        return s[0] - '0';
    auto it = std::find(strings.begin(), strings.end(), s);
    int index = it - strings.begin();
    if (index <= 8)
        return index + 1;
    return index - 8;
}

int main()
{
    std::vector<std::string> strings = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int sum = 0;
    std::ifstream inputFile("input.txt");
    while (!inputFile.eof())
    {
        std::string line;
        inputFile >> line;
        int firstDigitIndex = INT32_MAX;
        std::string firstDigit;
        int lastDigitIndex = -1;
        std::string lastDigit;
        for (std::string& s : strings)
        {
            int firstIndex = line.find(s);
            if (firstIndex != line.npos && firstIndex < firstDigitIndex)
            {
                firstDigitIndex = firstIndex;
                firstDigit = s;
            }
            int lastIndex = line.rfind(s);
            if (lastIndex != line.npos && lastIndex > lastDigitIndex)
            {
                lastDigitIndex = lastIndex;
                lastDigit = s;
            }
        }
        std::cout << firstDigit << " | " << lastDigit << std::endl;
        sum += ConvertToDigit(firstDigit, strings) * 10 + ConvertToDigit(lastDigit, strings);
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}