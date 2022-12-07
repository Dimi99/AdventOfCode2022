#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>

#define FILEPATH "../Data.txt"

using std::ifstream;


void read(ifstream &in){

    char bufX[50];


    while (in) {
        in.getline(bufX, sizeof(bufX),'\n');
        if(bufX[0] == '\0')
            continue;

        

    }

}

int main() {

    std::ifstream input(FILEPATH);
    read(input);

    return 0;
}
