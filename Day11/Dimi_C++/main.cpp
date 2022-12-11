#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <cstring>
#include <cmath>

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
        try {
            partner = stoi(operation_.substr(23,operation_.size()-23));

        }
        catch (const std::invalid_argument& e) {
           partner = number;
        }

        if(operation_.substr(21,1) == "*")
            return number * partner;
        else if(operation_.substr(21,1) == "+")
            return number + partner;
        else
            throw std::invalid_argument("wrong operation");
    }

    bool operator>(const Monkey& other){
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
            //double divide = static_cast<double>(monkey.items_.at(0))/3;
           long long int temp =  monkey.items_.at(0);
           //if(monkey.items_.at(0) > lcm)
           //long long int temp = monkey.items_.at(0) % lcm;
           monkey.items_.at(0)  = monkey.items_.at(0) % lcm ;


           std::cout << (monkey.items_.at(0) == temp) << "\n";

            if(monkey.test(monkey.items_.at(0))) //number % test_ == 0
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
    std::cout << lcm << "\n";
    for(int i = 0; i < 10000 ; ++i){
        round(monkeys,lcm);
    }

    std::sort(monkeys.begin(),monkeys.end(),std::greater());
    unsigned long long result = 1;
    for(int j = 0; j<2 ; ++j){
        result *= monkeys.at(j).items_inspected;
    }
    std::cout << result << std::endl;
    std::cout << monkeys.at(0).items_inspected << " :: " << monkeys.at(1).items_inspected<<std::endl;



    return 0;
}


/**
* I actually didn't really know the maths but I reasoned out a working solution!

But the way I did it was pretty unorthodox as well. I didn't keep track of any particular number, instead I gave every Item instance a "worryDebt" vector attribute that stored how "far away" each of the modulo are away from being divisible.

For example if the monkeys would check 7, 9, and 13, and the initial worry number was 22, then it would store <7, 6>, <9, 5>, and <13, 4>.

Then for every operation that's done by a monkey, the item is updated accordingly. Addition? All of the values decrease by the amount, and then get added back to the positive if they are negative. For example if a monkey did a +5;

<7, 1>, <9, 0>, <13, 12> (this indeed checks out with 27)

And now we know that it's divisible by 9. Well what if it multiplies by a number? I experimentally determined that the "debt" also multiplies, and then mods down. So suppose it was times 3:

<7, 3>, <9, 0>, <13, 10> (this indeed checks out with 81)

And the only other thing to worry about was squares. This one took a while, but I realized that the debt squares, then gets modded, and then becomes the INVERSE as it relates to the key, i.e. key - calcValue. Let's square these:

<7, 5>, <9, 0>, <13, 4> (this indeed checks out with 6561)

The modulus operations are just as simple as finding the correct key and checking if the number is 0. No need to keep track of any number greater than any of the modulo. I don't
*/