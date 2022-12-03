#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <queue>

#define FILEPATH "/home/dimi/Desktop/AdventOfCode2022/Day1/Day1_Input.txt"

class ElfCommunity{
public:
    ElfCommunity(std::ifstream &in){
        char bufX[10];
        std::vector<int> food_list;
        while(in) {
            in.getline(bufX, sizeof(std::string), '\n');
            int calorie = atoi(bufX);
            if (calorie) {
                food_list.push_back(calorie);
                continue;
            }
            individuals.emplace(ElfCommunity::Elf(food_list));
            food_list.clear();
        }
    }

    struct Elf {
    public:
        explicit Elf(const std::vector<int> &food_list):
                foods_(food_list)
        {
            total_calories_ = std::accumulate(foods_.begin(), foods_.end(), 0);
        }
        int total_calories () const {return total_calories_;}
        bool operator<(const Elf& elve) const
        {return this->total_calories_ < elve.total_calories_;}
    private:
        int total_calories_;
        std::vector<int> foods_;
    };


    Elf max_elve(){return individuals.top();}
    void pop(){individuals.pop();}

private:
    std::priority_queue<Elf> individuals;

};


int main() {

    std::ifstream input(FILEPATH);
    ElfCommunity elves(input);
    // Top 3 Elves
    auto result = 0;
    for(int i = 0; i <=2; ++i) {
        result += elves.max_elve().total_calories();
        elves.pop();
    }
    std::cout << "Result: " << result << std::endl;

    return 0;
}
