#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>

#define FILEPATH "../Data.txt"

using std::ifstream;


std::array<std::stack<char>,9> read(ifstream &in){

    std::array<std::stack<char>,9> stacks = {};
    char bufX[50];


    while (in) {
        in.getline(bufX, sizeof(bufX),'\n');
        if(bufX[0] == ' ')
            break;
        std::string s(bufX);

        for (int i = 0; i < s.length(); i+=4) {
            if (s[i+1] == ' ')
                continue;
            stacks[i/4].emplace(s[i+1]);
        }
    }
    for(auto &stack: stacks){
        std::stack<char> tmpstack;
        while (!stack.empty())
        {
            auto item = stack.top();
            stack.pop();
            tmpstack.push(item);
        }
        stack = tmpstack;
    }
    return stacks;
}

void move_crates_task1(std::array<std::stack<char>,9> &stacks,ifstream &in){

    char bufA[10], bufB[10], bufX[10], bufY[10], bufZ[10];
    char* end;
    while (in){
        in.getline(bufA, sizeof(bufX),' ');
        in.getline(bufX, sizeof(bufX),'f');
        in.getline(bufB, sizeof(bufX),' ');
        in.getline(bufY, sizeof(bufY),'t');
        in.getline(bufZ, sizeof(bufZ),'\n');
        if(bufX[0] == '\0')
            continue;
        int  x = atoi(bufX);
        int from = atoi(bufY)-1;
        std::string z(bufZ);
        std::size_t pos{};
        int to = atoi(&z.at(z.length()-1))-1;

        for(int i = 0; i < x; ++i){
            stacks[to].push(stacks[from].top());
            stacks[from].pop();
        }

    }
}


void move_crates_task2(std::array<std::stack<char>,9> &stacks,ifstream &in){

    char bufA[10], bufB[10], bufX[10], bufY[10], bufZ[10];
    char* end;
    while (in){
        in.getline(bufA, sizeof(bufX),' ');
        in.getline(bufX, sizeof(bufX),'f');
        in.getline(bufB, sizeof(bufX),' ');
        in.getline(bufY, sizeof(bufY),'t');
        in.getline(bufZ, sizeof(bufZ),'\n');
        if(bufX[0] == '\0')
            continue;
        int  x = atoi(bufX);
        int from = atoi(bufY)-1;
        std::string z(bufZ);
        std::size_t pos{};
        int to = atoi(&z.at(z.length()-1))-1;
        std::vector<char> temp_vector;
        for(int i = 0; i < x; ++i){
            temp_vector.push_back(stacks[from].top());
            stacks[from].pop();
        }
        for (unsigned i = temp_vector.size(); i-- > 0; )
            stacks[to].push(temp_vector[i]);

    }
}

int main() {

    std::ifstream input(FILEPATH);
    auto stacks1 = read(input);

    move_crates_task1(stacks1,input);
    for(int i = 0; i < stacks1.size(); ++i){
       std::cout << stacks1[i].top();
    }

    std::cout << "\n ---------------- \n";
    std::ifstream input2(FILEPATH);

    auto stacks2 = read(input2);
    move_crates_task2(stacks2,input2);
    for(int i = 0; i < stacks2.size(); ++i){
        std::cout << stacks2[i].top();
    }



    return 0;
}
