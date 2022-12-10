#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>

#define FILEPATH "../Data.txt"

using std::ifstream;


void draw_pixel(int cycle, int X, std::vector<std::vector<char>>& map) {
    int row = 0;
    int column = 0;
    for (int i = 40; i <= 240 ; i += 40) {
        if (i-cycle >= 0) {
            row = (i / 40) -1;
            column = (cycle - row * 40)-1;
            if(column >= X-1 && column <= X+1 )
                map.at(row).at(column) = '*';
            else
                map.at(row).at(column) = '.';
            break;
        }
    }
}
std::ostream& operator<<(std::ostream& os,const std::vector<std::vector<char>> &map){
    for(auto& o: map){
        for(auto u:o)
            os << " " << u << " " ;
        os << "\n";
    }
    return os;
}

std::vector<std::vector<char>> read(ifstream &in){
    int cycle = 1;
    std::vector<std::vector<char>> map(6,std::vector<char>(40));
    int X{1};
    char  bufX[10];
    while (in){
        in.getline(bufX, sizeof(bufX),'\n');

        if(bufX[0] == '\0')
           continue;

        if(bufX[0] == 'n'){
            draw_pixel(cycle,X,map);
            cycle ++;
        }
        if(bufX[0] == 'a'){
            for(int j = 0; j <= 1; j++) {
                draw_pixel(cycle,X,map);
                cycle += 1;
            }
            std::string temp = bufX;
            long add = stoi(temp.substr(4,temp.size()-4));
            int a = add;
            X += a;

        }
    }
    return map;

}

int main() {

    std::ifstream input(FILEPATH);
    auto map = read(input);
    std::cout << map;



    return 0;
}
