#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>
#include <set>

#define FILEPATH "../Data.txt"

using std::ifstream;


int read(ifstream &in){

    char bufX[4895];
    in.getline(bufX, sizeof(bufX),'\0');
    std::string cipher = bufX;

    for(int i = 13; i < cipher.length(); ++i ){
        std::set<char> set  = {cipher.begin()+(i-13),cipher.begin()+i+1};
        if(set.size() == 14)
            return i+1;
    }

    return 0;

}
// b l j s p h d z t n v j f q
// x x x x x x x x x x
int main() {

    std::ifstream input(FILEPATH);
    std::cout << read(input);




    return 0;
}
