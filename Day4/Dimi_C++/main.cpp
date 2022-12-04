#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>

#define FILEPATH "../Data.txt"
using std::ifstream;

struct Section{
public:
    Section(uint from, uint to):
        from_(from),
        to_(to)
    {}
    uint from_,to_;
};
// First Task
bool overlap(const std::pair<Section,Section> &section){
    return ((section.first.from_ <=  section.second.from_ && section.first.to_ >= section.second.to_)
          ||(section.second.from_ <= section.first.from_  && section.second.to_ >= section.first.to_));
}

// Second Task
bool intersect(const std::pair<Section,Section> &section){
    return ((section.first.from_ <= section.second.from_ && section.first.to_ >= section.second.from_)
          ||(section.second.from_ <= section.first.from_ && section.second.to_ >= section.first.from_));
}



std::vector<std::pair<Section,Section>> read(ifstream &in){

    std::vector<std::pair<Section,Section>> out;
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

        out.emplace_back(Section(atoi(bufX), atoi(bufY)),Section(atoi(bufZ), atoi(bufO)));
    }
    return out;
}

int main() {

    std::ifstream input(FILEPATH);
    auto sections = read(input);
    
    int count1{0};
    int count2{0};

    std::for_each(sections.begin(), sections.end(), [&](std::pair<Section,Section> &section){
        // First Task
        count1 += (overlap(section));
        // Second Task
        count2 += (intersect(section));
    });

    std::cout << count1 << "\n" << count2 << "\n";

    return 0;
}
