#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#define FILEPATH "/home/dimi/Desktop/AdventOfCode2022/Day1/Day1_Input.txt"
#include <iostream>
#include <fstream>
#include <numeric>
#include <cstring>
#include <algorithm>

class ElveCommunity{
public:
    ElveCommunity(std::ifstream &in){
        char bufX[10];
        individuals.emplace_back();
        while(in) {
            in.getline(bufX, sizeof(std::string), '\n');
            int calorie = atoi(bufX);
            if (calorie)
                individuals.back().add_calorie(calorie);
            else
                individuals.emplace_back();

        }
        std::for_each(individuals.begin(), individuals.end(), [&](Elve &elve) {
           elve.calc_calories();
        });
    }

    int max_element(){return std::max_element(individuals.begin(),individuals.end(), std::greater<>())->total_calories();}

    struct Elve {
public:
        void add_calorie(int food){foods_.push_back(food);}
        void calc_calories(){total_calories_ = std::accumulate(foods_.begin(), foods_.end(), 0);}
        int total_calories () const {return total_calories_;}
        bool operator>(const Elve& elve) const
        {return this->total_calories() < elve.total_calories();}
private:
        int total_calories_;
        std::vector<int> foods_;
    };

private:
    std::vector<Elve> individuals;

};


int main() {

    std::ifstream input(FILEPATH);
    ElveCommunity elves(input);
    // max amound of calories
    std::cout << elves.max_element();
    return 0;
}
