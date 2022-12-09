#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_set>

#define FILEPATH "../Data.txt"

using std::ifstream;


struct Snake {
    struct Position {
    public:
        Position(int x, int y) :
                x_(x),
                y_(y) {}
                int x_, y_;

        bool operator==(const Position &other) const
        {return (x_ == other.x_ && y_ == other.y_);}

        struct KeyHasher{
            std::size_t operator()(const Position& pos) const
            {return ((std::hash<int>()(pos.x_) ^ (std::hash<int>()(pos.y_) << 1)) >> 1);}
        };

    };
    Snake(Position start)
        {
            for(int i = 0; i <  10 ; ++i ){
                nodes.emplace_back(start.x_,start.y_);
            }

        }
    void check_diagonal(Position& head_, Position& tail_){
        tail_.x_ = (tail_.x_ + ((head_.x_ - tail_.x_) / std::abs(head_.x_ - tail_.x_)));
        tail_.y_ = (tail_.y_ + ((head_.y_ - tail_.y_) / std::abs(head_.y_ - tail_.y_)));

    }

    void move_head(char op){
        int factor = (op == 'L' || op == 'D') ?  -1 : 1;
        if(op == 'R' ||  op == 'L')
            this->nodes.at(0).x_ += factor;
        else
            this->nodes.at(0).y_ += factor;
        }
    void move2(char op, int amount) {
            for (int i = 0; i < amount; ++i){
                this->move_head(op);

                for (int j = 1; j < nodes.size(); j++){
                    if (std::abs(nodes.at(j-1).x_ - nodes.at(j).x_) > 1 || std::abs(nodes.at(j-1).y_ - nodes.at(j).y_) > 1){
                        if(nodes.at(j-1).x_ == nodes.at(j).x_){
                            int offset = (nodes.at(j-1).y_ - nodes.at(j).y_ >1) ? 1:-1;
                            nodes.at(j).y_ += (nodes.at(j-1).y_ - nodes.at(j).y_ -offset);
                            continue;
                        }
                        else if(nodes.at(j-1).y_ == nodes.at(j).y_){
                            int offset = (nodes.at(j-1).x_ - nodes.at(j).x_ >1) ? 1:-1;
                            nodes.at(j).x_ += (nodes.at(j-1).x_ - nodes.at(j).x_ -offset);
                            continue;
                        }
                        else
                            check_diagonal(nodes.at(j - 1), nodes.at(j));

                    }

                    //std::cout << nodes.at(nodes.size()-1).x_ << " : " << nodes.at(nodes.size()-1).y_ << "\n";
                }
                visited.insert(Position(nodes.at(nodes.size()-1).x_,nodes.at(nodes.size()-1).y_));

            }
    }


std::vector<Position> nodes;
std::unordered_set<Position,Position::KeyHasher> visited;

};


unsigned long read(ifstream &in){
    
    Snake snake(Snake::Position(0, 0));


    char bufX[10], bufY[10];
    while (in){
        in.getline(bufX, sizeof(bufX),' ');
        in.getline(bufY, sizeof(bufY),'\n');
        snake.move2(bufX[0],atoi(bufY));
    }
    return snake.visited.size();
}

int main() {

    std::ifstream input(FILEPATH);
    std::cout << read(input) << "\n";

    return 0;

    /**
     ..........................
..........................
..........................
..........................
..........................
..........................
..........................
..........................
..........................
#.........................
#.............###.........
#............#...#........
.#..........#.....#.......
..#..........#.....#......
...#........#.......#.....
....#......s.........#....
.....#..............#.....
......#............#......
.......#..........#.......
........#........#........
.........########.........
     */
}
