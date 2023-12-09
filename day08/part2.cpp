#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

struct Node
{
    std::string label;
    Node* left = nullptr;
    Node* right = nullptr;
};

void CreateBinaryTree(std::ifstream& inputFile, std::unordered_map<std::string, Node*>& map, std::vector<Node*>& startingNodes)
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
            if (label[label.length() - 1] == 'A')
                startingNodes.push_back(node);
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

bool IsFinalNodes(const std::vector<Node*> nodes)
{
    for (const Node* node : nodes)
    {
        if (node->label[node->label.length() - 1] != 'Z')
            return false;
    }
    return true;
}

int64_t gcd(int64_t a, int64_t b)
{
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

int64_t lcm(const std::vector<int64_t>& numbers)
{
    int64_t lcm = numbers[0];
    for (int64_t i = 1; i < numbers.size(); i++)
    {
        lcm = (numbers[i] * lcm) / gcd(numbers[i], lcm);
    }
    return lcm;
}

int64_t StepsToFinal(std::vector<Node*> nodes, const std::string& directions)
{
    std::vector<int64_t> stepsToZ;
    for (Node* node : nodes)
    {
        std::string startingLabel = node->label;
        int64_t steps = 0;
        while (node->label[node->label.length() - 1] != 'Z')
        {
            for (int64_t i = 0; i < directions.length(); i++)
            {
                char action = directions[i];
                if (action == 'L')
                    node = node->left;
                else if (action == 'R')
                    node = node->right;
                steps++;
            }
        }
        stepsToZ.push_back(steps);
    }
    return lcm(stepsToZ);
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
    std::vector<Node*> startingNodes;
    CreateBinaryTree(inputFile, map, startingNodes);
    int64_t steps = StepsToFinal(startingNodes, directions);
    DeleteBinaryTree(map);
    std::cout << steps << std::endl;
    return 0;
}