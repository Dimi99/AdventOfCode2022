#include <iostream>
#include <fstream>
#include <map>
#include <cmath>

#define FILEPATH "../Data.txt"
using std::ifstream;

/**
 X means you need to lose,
 Y means a draw,
 and Z means you need to win
**/

int read(ifstream &in, std::map<char,int> &win, std::map<char,int> &loose){

    std::map<char,int> map{{'A',1},{'B',2},{'C',3}};
    int score = 0;
    char bufX[10], bufY[10];
    while(in) {
        in.getline(bufX, sizeof(bufX), ' ');
        in.getline(bufY, sizeof(bufY), '\n');
        if(bufX[0] == '\0')
            continue;
        if(bufY[0] == 'X')
            score += loose.find(bufX[0])->second;
        else if(bufY[0] == 'Z'){
            score += 6;
            score += win.find(bufX[0])->second;
        }
        else{
            score += 3;
            score += map.find(bufX[0])->second;

        }





        //scoring


    }
    return score;
}
int main() {
    std::map<char,int> win{{'A',2},{'B',3},{'C',1}};
    std::map<char,int> loose{{'A',3},{'B',1},{'C',2}};

    std::ifstream input(FILEPATH);
    std::cout << read(input,win,loose)<< "\n";


    return 0;
}
