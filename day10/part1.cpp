#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

struct Position
{
    int32_t x, y;

    Position() : Position(0, 0) { }

    Position(int32_t x, int32_t y) : x(x), y(y) { }

    bool operator==(const Position& other) const
    {
        return this->x == other.x && this->y == other.y;
    }
};

template<>
struct std::hash<Position>
{
    std::size_t operator()(const Position& pos) const
    {
        return pos.x + pos.y;
    }
};


class Map
{
private:
    std::vector<std::string> map;
    Position start;

public:
    Map(std::ifstream& file)
    {
        std::string line;
        for (int32_t i = 0; std::getline(file, line); i++)
        {
            map.push_back(line);
            size_t col = line.find('S');
            if (col != line.npos)
            {
                this->start.y = i;
                this->start.x = col;
            }
        }
    }

    std::vector<Position> GetMoves(const Position& pos) const
    {
        std::vector<Position> moves;
        const char c = map[pos.y][pos.x];
        // Down
        if (c == '|' || c == '7' || c == 'F' || c == 'S')
        {
            Position down(pos.x, pos.y+1);
            if (down.y >= 0 && down.y < map.size() && 
            (this->map[down.y][down.x] == 'L' || this->map[down.y][down.x] == 'J' 
            || this->map[down.y][down.x] == '|' || this->map[down.y][down.x] == 'S'))
                moves.push_back(down);
        }
        // Up
        if (c == '|' || c == 'L' || c == 'J' || c == 'S')
        {
            Position up(pos.x, pos.y-1);
            if (up.y >= 0 && up.y < map.size() && 
            (this->map[up.y][up.x] == '|' || this->map[up.y][up.x] == '7' 
            || this->map[up.y][up.x] == 'F' || this->map[up.y][up.x] == 'S'))
                moves.push_back(up);
        }
        // Left
        if (c == '-' || c == '7' || c == 'J' || c == 'S')
        {
            Position left(pos.x-1, pos.y);
            if (left.x >= 0 && left.x < map[left.y].size() && 
            (this->map[left.y][left.x] == '-' || this->map[left.y][left.x] == 'L' 
            || this->map[left.y][left.x] == 'F' || this->map[left.y][left.x] == 'S'))
                moves.push_back(left);
        }
        // Right
        if (c == '-' || c == 'L' || c == 'F' || c == 'S')
        {
            Position right(pos.x+1, pos.y);
            if (right.x >= 0 && right.x < map[right.y].size() && 
            (this->map[right.y][right.x] == '-' || this->map[right.y][right.x] == '7' 
            || this->map[right.y][right.x] == 'J' || this->map[right.y][right.x] == 'S'))
                moves.push_back(right);
        }
        return moves;
    }

    Position GetStart() const
    {
        return this->start;
    }
};


class Node
{
private:
    std::vector<Position> path;

public:
    Node(const std::vector<Position>& path) : path(path) { }

    std::vector<Position> GetPath() const
    {
        return this->path;
    }

    Position GetPosition() const
    {
        return path[path.size() - 1];
    }
};


std::vector<Position> Bfs(const Map& map)
{
    std::queue<Node> queue;
    std::unordered_set<Position> visited;
    // Create root node
    Position start = map.GetStart();
    Position firstMove = map.GetMoves(start)[0];
    std::vector<Position> path;
    path.push_back(start);
    path.push_back(firstMove);
    visited.insert(start);
    Node root(path);
    queue.push(root);
    while (!queue.empty())
    {
        const Node& node = queue.front();
        Position pos = node.GetPosition();
        std::cout << "Position(" << pos.x << ", " << pos.y << ") " << std::endl;
        visited.insert(pos);
        for (const Position& p : map.GetMoves(pos))
        {
            if (p == map.GetStart() && node.GetPath().size() > 2)
                return node.GetPath();
            if (visited.count(p) == 0)
            {
                std::vector<Position> copy = node.GetPath();
                copy.push_back(p);
                Node child(copy);
                queue.push(child);
            }
        }
        queue.pop();
    }
    path.clear();
    return path;
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
    Map map(inputFile);
    std::cout << "Start(" << map.GetStart().x << ", " << map.GetStart().y << ")" << std::endl;
    std::vector<Position> path = Bfs(map);
    if (path.size() == 0)
    {
        std::cout << "NO WAY" << std::endl;
    }
    else
    {
        std::cout << "Found cycle with size " << path.size() << std::endl;
        std::cout << "Farthest distance: " << (path.size() / 2) << std::endl;
    }
    return 0;
}
