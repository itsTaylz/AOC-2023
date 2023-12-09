#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>
#include <unordered_map>
#include <queue>
#include <sstream>

static constexpr int32_t FIVE_OF_A_KIND = 7;
static constexpr int32_t FOUR_OF_A_KIND = 6;
static constexpr int32_t FULL_HOUSE = 5;
static constexpr int32_t THREE_OF_A_KIND = 4;
static constexpr int32_t TWO_PAIR = 3;
static constexpr int32_t ONE_PAIR = 2;
static constexpr int32_t HIGH_CARD = 1;

class Hand
{
private:
    std::array<char, 5> cards;
    int32_t bid;
    int32_t type;

    int32_t GetLabelPower(char c) const
    {
        switch (c)
        {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 11;
        case 'T':
            return 10;
        default:
            return c - '0';
        }
    }

    int32_t CalculateType() const
    {
        std::unordered_map<char, int32_t> ocurrences;
        for (const char& c : this->cards)
        {
            ocurrences[c]++;
        }
        if (ocurrences.size() == 1)
            return FIVE_OF_A_KIND;
        if (ocurrences.size() == 2)
        {
            for (const char& c : this->cards)
            {
                if (ocurrences[c] == 4)
                    return FOUR_OF_A_KIND;
            }
            return FULL_HOUSE;
        }
        if (ocurrences.size() == 3)
        {
            for (const char& c : this->cards)
            {
                if (ocurrences[c] == 3)
                    return THREE_OF_A_KIND;
            }
            return TWO_PAIR;
        }
        if (ocurrences.size() == 5)
            return HIGH_CARD;
        return ONE_PAIR;
    }

public:
    Hand(std::array<char, 5> cards, int32_t bid) : cards(cards), bid(bid) 
    {
        this->type = CalculateType();
    }

    int32_t GetType() const
    {
        return this->type;
    }

    int32_t GetBid() const
    {
        return this->bid;
    }

    bool operator<(const Hand& other) const
    {
        int32_t typeDiff = GetType() - other.GetType();
        if (typeDiff != 0)
            return typeDiff < 0;
        for (int32_t i = 0; i < this->cards.size(); i++)
        {
            int32_t label1 = GetLabelPower(this->cards[i]);
            int32_t label2 = GetLabelPower(other.cards[i]);
            int32_t labelDiff = label1 - label2;
            if (labelDiff != 0)
                return labelDiff < 0;
        }
        return false;
    }
};



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
    std::priority_queue<Hand> queue;
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::array<char, 5> cards;
        int32_t bid;
        for (int32_t i = 0; i < cards.size(); i++)
        {
            char c;
            ss >> c;
            cards[i] = c;
        }
        ss >> bid;
        Hand hand(cards, bid);
        queue.emplace(hand);
    }
    int32_t rank = queue.size();
    int64_t sum = 0;
    while (!queue.empty())
    {
        Hand hand = queue.top();
        queue.pop();
        sum += hand.GetBid() * rank;
        rank--;
    }
    std::cout << "Result: " << sum << std::endl;
    inputFile.close();
    return 0;
}