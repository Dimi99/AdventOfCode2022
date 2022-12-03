#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>

#define FILEPATH "../Data.txt"
using std::ifstream;


int read1(ifstream &in){

    char bufX[80];
    int result = 0;
    while(in) {
        in.getline(bufX, sizeof(bufX), '\n');
        if(bufX[0] == '\0')
            continue;
        std::string inter = bufX;

        std::string first = inter.substr(0,inter.length()/2);
        std::string second = inter.substr(inter.length()/2);

        std::sort(first.begin(),first.end());
        std::sort(second.begin(),second.end());
        std::string out{};
        std::set_intersection(first.begin(),first.end(),second.begin(),second.end(),out.begin());
        // intersection
        if(auto item = *out.begin(); islower(item))
            result +=  static_cast<int>(item) - 96;
        else
            result +=  static_cast<int>(item) - 38;

    }
    return result;
}

int read2(ifstream &in){

    char bufX[80];
    int result = 0;
    int line = 0;
    std::vector<std::string> group;
    group.resize(3);
    while(in) {
        in.getline(bufX, sizeof(bufX), '\n');
        if(bufX[0] == '\0')
            continue;
        std::string inter = bufX;
        group.at(line) = inter;
        if (line == 2){
            std::string intermediate_intersection{};
            for(char u:group.at(1)){
                for(char v:group.at(0)) {
                    if (u == v)
                        intermediate_intersection += u;
                }
            }

            for(char u:group.at(2)) {
                if (intermediate_intersection.find(u) != std::string::npos) {
                    // intersection
                    if (islower(u))
                        result += static_cast<int>(u) - 96;
                    else
                        result += static_cast<int>(u) - 38;
                    break;
                }
            }
                line = -1;
        }

        line++;
    }
    return result;
}
int main() {


    std::ifstream input(FILEPATH);
    std::cout << read1(input) << "\n";
    std::ifstream input2(FILEPATH);
    std::cout << read2(input2) << "\n";



    return 0;
}
