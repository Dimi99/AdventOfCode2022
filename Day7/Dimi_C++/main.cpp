#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <stack>


#define FILEPATH "../Data.txt"

struct Directory{
    Directory(const std::string &name):
    name_(name),
    memory_(0)
    {}
    [[nodiscard]] int memory()const {return memory_;}
    [[nodiscard]] std::vector<Directory> dir()const {return dirs_;}
    [[nodiscard]] std::string name()const{return name_;}
    void add_memory(int memory){memory_ += memory;}
    void add_dir_(const Directory &dir){dirs_.push_back(dir);}
    bool operator<(const Directory& dir) const
    {return (this->memory_ < dir.memory_);}
    Directory& operator=(const Directory& other)
    {
        name_ = other.name_;
        memory_ = other.memory_;
        dirs_ = other.dirs_;
        return *this;
    }


    int update_memory(std::vector<Directory>& list){
    int memory = 0;
     for(Directory dir: dirs_){
         auto temp = std::find_if(list.begin(), list.end(), [&](Directory& child){
             return child.name_ == dir.name_;
         });
         memory += temp->memory_;

         if(!temp->dirs_.empty())
             memory += temp->update_memory(list);

     }
     return memory;
    }

private:
    std::string name_;
    int memory_;
    std::vector<Directory> dirs_;

};

using std::ifstream;
//1792222

std::vector<Directory> read(ifstream &in){

    char bufX[50];
    std::vector<Directory> directories {};
    Directory temp{""};
    std::stack<std::string> path;
    path.emplace("");

    while (in) {
        in.getline(bufX, sizeof(bufX),'\n');
        if(bufX[0] == '\0')
            continue;
        std::string s; s.append(bufX);
        if(auto back = s.substr(4,s.length()-4);s.substr(0,4) == "$ cd") {
            if(back  != " ..") {
                directories.push_back(temp);
                path.push(path.top() + back);
                temp = Directory(path.top());
            }
            else
                path.pop();
        }
        if(s.substr(0,1) == "$")
            continue;
        if(s.substr(0,3) == "dir")
            temp.add_dir_(path.top()+s.substr(3,s.length()-3));
        else{
            temp.add_memory(std::stoi(s.substr(0,s.find(' '))));
        }

    }
    directories.push_back(temp);





    return directories;
}

int main() {

    std::ifstream input(FILEPATH);
    auto op = read(input);
    int result = 0;
    int used_space{0};
    for(auto& b:op){
        b.add_memory(b.update_memory(op));
        if(b.memory() <= 100000)
            result += b.memory();
        if(b.name() == " /")
            used_space = b.memory();

    }

    std::cout << result << std::endl;

    // Part 2
    int required_space = 30000000 - (70000000 - used_space );
    std::sort(op.begin(),op.end());
    for(auto &dir:op){
        if(dir.memory() >= required_space) {
            std::cout << dir.memory() << "\n";
            break;
        }
    }

    return 0;
}
