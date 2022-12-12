#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <cstring>

#define FILEPATH "../Data.txt"

using std::ifstream;


class Monkey{
public:
    Monkey(int target_true,int target_false,const std::string& operation, const std::string& items, const std::string& test):
    target_monkey_true_(target_true),
    target_monkey_false_(target_false),
    operation_(operation)
    {
        //Starting items:
        auto item = items.substr(14,items.size()-14);
        for(int i = 0; i<item.size()-4;i+=4){
            items_.push_back(stoi(item.substr(i+2,2) ));
        }

        //Test Number
        test_ = stoi(test.substr(19,test.size()-19));

    }

    bool test(long long int number){
        return(number % test_ == 0);
    }
    long long int operation(long long int number){
        long long int partner = 0;
        try {partner = stoi(operation_.substr(23,operation_.size()-23));}
        catch (const std::invalid_argument& e) {partner = number;   }
        //Todo
        if(operation_.substr(21,1) == "*")
            return number * partner;
        else if(operation_.substr(21,1) == "+")
            return number + partner;
        else
            throw std::invalid_argument("wrong operation");
    }

    bool operator>(const Monkey& other) const{
        return (this->items_inspected > other.items_inspected);
    }

    int target_monkey_true_, target_monkey_false_;
    std::string operation_;
    std::vector<long long int> items_;
    long long int test_{0};
    long long int items_inspected{0};
};


std::vector<Monkey> read(ifstream &in) {
    const size_t arraySize = 200;
    std::vector<Monkey> monkeys;


    while (in) {
        char bufX[arraySize];
        in.getline(bufX, sizeof(bufX), 'M');
        if (bufX[0] == '\0'){
            continue;
        }
        std::string buf(bufX);
        std::string starting = "Starting items: ";
        std::string op = "Operation: new =";
        std::string t = "Test: divisible by ";
        std::string true_monk = "If true: throw to monkey ";
        std::string false_monk = "If false: throw to monkey ";

        auto a = buf.find(starting);
        auto b = buf.find(op);
        auto c = buf.find(t);
        auto d = buf.find(true_monk);
        auto e = buf.find(false_monk);

        monkeys.emplace_back(stoi(buf.substr(d+true_monk.size(),1)),
                             stoi(buf.substr(e+false_monk.size(),1)),
                             buf.substr(b,c-b),
                             buf.substr(a,b-a),
                             buf.substr(c,d-c));

        std::memset(&(bufX[0]), 0, arraySize);
    }
    return monkeys;
}


void round(std::vector<Monkey>& monkeys,long long int lcm){

    for(Monkey &monkey: monkeys){
        int size = monkey.items_.size();
        for(int j = 0; j<size; ++j){
            monkey.items_inspected++;
            monkey.items_.at(0) = monkey.operation(monkey.items_.at(0));
            long long int temp =  monkey.items_.at(0);
            monkey.items_.at(0)  = monkey.items_.at(0) % lcm ;

            if(monkey.test(monkey.items_.at(0)))
                monkeys.at(monkey.target_monkey_true_).items_.push_back(monkey.items_.at(0));
            else
                monkeys.at(monkey.target_monkey_false_).items_.push_back(monkey.items_.at(0));

            monkey.items_.erase(monkey.items_.begin()+0);
        }
    }

}

int main(){

    std::ifstream input(FILEPATH);
    auto monkeys = read(input);
    long long int lcm = 1;
    for(Monkey& monkey: monkeys){
        lcm *= monkey.test_;
    }
    
    for(int i = 0; i < 10000 ; ++i){
        round(monkeys,lcm);
    }

    std::sort(monkeys.begin(),monkeys.end(),std::greater());
    unsigned long long result = 1;
    for(int j = 0; j<2 ; ++j){
        result *= monkeys.at(j).items_inspected;
    }
    std::cout << result << std::endl;



    return 0;
}