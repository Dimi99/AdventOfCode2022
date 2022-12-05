#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>

#define FILEPATH "../Data.txt"

using std::ifstream;


void read(ifstream &in){

    char bufX[3];
    char bufY[3];
    char bufZ[3];
    char bufO[3];

    while(in) {
        in.getline(bufX, sizeof(bufX),'-');
        in.getline(bufY,sizeof(bufY),',');
        in.getline(bufZ,sizeof(bufZ),'-');
        in.getline(bufO,sizeof(bufO),'\n');
        if(bufX[0] == '\0')
            continue;
    }
}

int main() {

    std::ifstream input(FILEPATH);

    return 0;
}
