#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>
#include <numeric>

#define FILEPATH "../Data.txt"
#define GRIDSIZE 99
using std::ifstream;


std::vector<std::vector<int>> read(ifstream &in) {
    std::vector<std::vector<int>> map(GRIDSIZE,std::vector<int>(GRIDSIZE));
    std::string buffer;
    int i = 0;
    while (in >> buffer)
    {
        for(int j = 0; j<buffer.length(); ++j){
            map[i][j] = int(buffer[j] - '0');
        }
        ++i;
    }

    in.close();
    return map;


}

int scenic_score(const std::vector<std::vector<int>> &map, int i, int j){
    std::vector<int> scenic_score;
    //left
    int visible = 1;
    for(int u = j-1; u > 0 ; u--){
        if(map.at(i).at(u) >= map.at(i).at(j)) {
            break;
        }
        visible++;
    }
    scenic_score.push_back(visible);

    //right
     visible = 1;
    for(int u = j+1; u < map[0].size()-1; ++u) {
        if (map.at(i).at(u) >= map.at(i).at(j)) {
            break;
        }
        visible++;

    }
    scenic_score.push_back(visible);

    //top
    visible = 1;
    for(int u = i-1; u > 0; u--){
        if(map.at(u).at(j) >= map.at(i).at(j)){
            break;
        }
        visible++;
    }
    scenic_score.push_back(visible);

    //bottom
    visible = 1;
    for(int u = i+1; u < map.size()-1; ++u) {
        if (map.at(u).at(j) >= map.at(i).at(j)){
            break;
        }
        visible++;
    }
    scenic_score.push_back(visible);


    return(std::accumulate(begin(scenic_score), end(scenic_score), 1, std::multiplies<>()));

}

int main() {

     std::ifstream input(FILEPATH);
     auto map = read(input);
     std::vector<int> scores;

    for(int i = 1; i < map.size()-1; ++i)
        for(int j = 1; j< map[0].size()-1; ++j)
            scores.push_back(scenic_score(map,i,j));



    std::sort(scores.begin(),scores.end(), std::greater());
    std::cout<< scores.at(0);



    return 0;
}
