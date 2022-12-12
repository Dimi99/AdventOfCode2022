#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>
#include <cstring>
#include <queue>
#include <list>

#define FILEPATH "../Data.txt"

using std::ifstream;

struct Position{
    Position(int i, int j, int value):
    i_(i),
    j_(j),
    value_(value)
    {}

    void check_adjacency(Position& pos){

        if (pos.value_ - this->value_ < -1)
            this->available.emplace_back(pos.i_,pos.j_);
        else if (pos.value_ - this->value_ > 1)
            pos.available.emplace_back(this->i_, this->j_);
        else {
            this->available.emplace_back(pos.i_,pos.j_);
            pos.available.emplace_back(this->i_, this->j_);
        }
    }

    [[nodiscard]] size_t id(const std::vector<std::vector<Position>>& map)const{
        return ((this->i_ * map[0].size()) + this->j_);
    }

    const int i_,j_;
    int value_;
    std::vector<std::pair<int,int>> available;
};
// TODO make this inherit from std::vector so it is not as ugly
struct Map{
    std::pair<int,int> start{0,0}, end{0,0};
    std::vector<std::vector<Position>> map;
};



Map read(ifstream &in){
    const size_t arraySize = 200;
    Map map;

    char bufX[arraySize];
    std::pair<int,int> start, finish;


    while (in) {
        in.getline(bufX, sizeof(bufX), '\n');
        if (bufX[0] == '\0')
            break;

        std::string s(bufX);
        map.map.emplace_back();

        int j = 0;
        for(auto a: s){
            char gradient = a;
            if(a == int('S')){
                map.start = {map.map.size()-1,j};
                gradient = 'a';
            }
            else if(a == int('E')){
                map.end = {map.map.size()-1,j};
                gradient = 'z';
            }
            map.map.at(map.map.size()-1).emplace_back(map.map.size()-1,j,gradient);


            //check for left & right
            if(j > 0)
                map.map.at(map.map.size()-1).at(j).check_adjacency(map.map.at(map.map.size()-1).at(j-1));
            //check for top & bottom
            if(map.map.size()-1 > 0)
                map.map.at(map.map.size()-1).at(j).check_adjacency(map.map.at(map.map.size()-2).at(j));


            ++j;
        }

        std::memset(&(bufX[0]), 0, arraySize);
    }

return map;
}

struct DjikstraPoint{

    DjikstraPoint(size_t id,float fscore,float heuristic,float dist = std::numeric_limits<float>::max(), size_t prev = std::numeric_limits<int>::max()):
            id_(id),
            fscore_(fscore),
            heuristic_(heuristic),
            dist_(dist),
            prev_(prev)

    {}
    size_t id_;
    float fscore_;
    float heuristic_;
    std::optional<float> dist_;
    std::optional<size_t> prev_;

    bool operator<(const DjikstraPoint& other) const{
        {return this->fscore_ > other.fscore_ ;}
    }

};
std::vector<size_t> a_star(const Map& map){
    size_t num_visited = 0;

    //initialize list of djikstra points + visited list
    std::vector<size_t> visited;
    std::vector<size_t> popped;
    std::vector<DjikstraPoint> points;

    size_t end_id = map.map[map.end.first][map.end.second].id(map.map);
    size_t start_id = map.map[map.start.first][map.start.second].id(map.map);

    points.reserve(map.map.size() * map.map[0].size());

    for(int i = 0; i < map.map.size(); ++i){
        for(int j = 0; j < map.map[0].size(); ++j) {
            double res{0.};
            res = std::sqrt(std::pow(map.end.first - i, 2) + std::pow(map.end.second - j, 2));
            auto heur = static_cast<float>(res);
            points.emplace_back(map.map[i][j].id(map.map), std::numeric_limits<float>::max(), heur, std::numeric_limits<int>::max());
        }
    }

    // initialize begin point, heuristic irrelevant as we always start here
    double res{0.};
    res = std::sqrt(std::pow(map.end.first - map.start.first, 2) + std::pow(map.end.second - map.start.second, 2));
    float heur = static_cast<float>(res);
    points.at(start_id) = DjikstraPoint(start_id ,heur + 0,heur,0);


    // our queue as priority queue for the bonus points;)
    std::priority_queue<DjikstraPoint> q;
    q.push(points.at(start_id));

    while(!q.empty()){
        auto u = q.top();
        visited.push_back(u.id_);

        // we reached the goal
        if(u.id_ == end_id )
            break;

        q.pop();
        popped.push_back(u.id_);
        num_visited++;

        Position curr = map.map.at(u.id_/map.map[0].size()).at(u.id_%map.map[0].size());

        if(u.dist_.value() == std::numeric_limits<float>::max())
            break;

        //determine neighbors
        for(auto & neighbor : curr.available){

                size_t i = (neighbor.first * map.map[0].size()) + neighbor.second;

                if (std::any_of(popped.begin(), popped.end(), [&](const size_t &id) { return id == points.at(i).id_; }))
                    continue;

                auto alt = u.dist_.value() +1;

                if (alt < points.at(i).dist_) {
                    points.at(i) = DjikstraPoint(i, alt + points.at(i).heuristic_, points.at(i).heuristic_, alt,u.id_);
                    std::priority_queue<DjikstraPoint> q2;

                    while (!q.empty()) {
                        auto p = q.top();
                        q.pop();
                        if (p.id_ == points.at(i).id_)
                            q2.emplace(points.at(p.id_));
                        else
                            q2.emplace(p);

                    }
                    q = q2;
                }

                if (std::any_of(visited.begin(), visited.end(),[&](const size_t &id) { return id == points.at(i).id_; }))
                    continue;
                q.emplace(points.at(i));
                visited.push_back(points.at(i).id_);
            }

    }

    std::vector<size_t> result;
    DjikstraPoint u = points.at(end_id);


    if(points.at(end_id).prev_ == std::numeric_limits<int>::max())
        return{};

    while(u.id_ != start_id){
        result.push_back(u.id_);
        u = points.at((u.prev_.value()));
    }

    result.push_back(start_id);

    std::reverse(result.begin(),result.end());

    return result;
}


int main() {

    std::ifstream input(FILEPATH);
    auto map = read(input);

    //Part 1 A* Algorithm
    auto result1 =a_star(map);
    std::cout << "Steps required for part 1: " <<result1.size()-1 << "\n";

    // Just brute force this part, c++ is fast enough and I am tired
    int part2 = std::numeric_limits<int>::max();
    for(auto &row: map.map){
        for(auto &elem: row){
            if(elem.value_ != int('a'))
                continue;
            map.start = {elem.i_,elem.j_};
            int temp = a_star(map).size()-1;
            if(temp < part2 && temp > 0)
                part2 = temp;

        }
    }
    //Part 2 Brute Force 
   std::cout << "Steps required for part 2: " << part2 << "\n";


    return 0;
}
