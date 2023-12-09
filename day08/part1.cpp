#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct Node
{
    std::string label;
    Node* left = nullptr;
    Node* right = nullptr;
};

void CreateBinaryTree(std::ifstream& inputFile, std::unordered_map<std::string, Node*>& map)
{
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string label;
        ss >> label;
        std::string left;
        ss >> left >> left;
        left = left.substr(1, left.length() - 2);
        std::string right;
        ss >> right;
        right = right.substr(0, right.length() - 1);
        Node* node = map[label];
        if (node == nullptr)
        {
            node = new Node();
            node->label = label;
            map[label] = node;
        }
        Node* leftNode = map[left];
        if (leftNode == nullptr)
        {
            leftNode = new Node();
            leftNode->label = left;
            map[left] = leftNode;
        }
        Node* rightNode = map[right];
        if (rightNode == nullptr)
        {
            rightNode = new Node();
            rightNode->label = right;
            map[right] = rightNode;
        }
        node->left = leftNode;
        node->right = rightNode;
        std::cout << "    " << node->label << std::endl;
        std::cout << node->left->label << "     " << node->right->label << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
}

void DeleteBinaryTree(std::unordered_map<std::string, Node*>& map)
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        delete it->second;
    }
}

int32_t StepsToFinal(Node* current, const std::string& directions)
{
    int32_t steps = 0;
    while (current->label != "ZZZ")
    {
        for (int32_t i = 0; i < directions.length(); i++)
        {
            char action = directions[i];
            if (action == 'L')
                current = current->left;
            else if (action == 'R')
                current = current->right;
            steps++;
        }
    }
    return steps;
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
    std::string directions;
    std::getline(inputFile, directions);
    std::string line;
    std::getline(inputFile, line); // ignore blank line
    std::unordered_map<std::string, Node*> map;
    CreateBinaryTree(inputFile, map);
    Node* start = map["AAA"];
    int32_t steps = StepsToFinal(start, directions);
    DeleteBinaryTree(map);
    std::cout << steps << std::endl;
    return 0;
}