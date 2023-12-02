#include <iostream>
#include <fstream>

int main()
{
    int sum = 0;
    std::ifstream inputFile("input.txt");
    while (!inputFile.eof())
    {
        std::string line;
        inputFile >> line;
        int firstDigit = -1;
        int lastDigit = -1;
        for (int i = 0; i < line.length(); i++) 
        {
            if (firstDigit != -1 && lastDigit != -1)
                break;
            char c1 = line[i];
            char c2 = line[line.length() - 1 - i];
            if (firstDigit == -1 && std::isdigit(c1)) 
                firstDigit = c1 - '0';
            if (lastDigit == -1 && std::isdigit(c2))
                lastDigit = c2 - '0';
        }
        sum += firstDigit*10 + lastDigit;
    }
    std::cout << "Result: " << sum << std::endl;
    return 0;
}