#ifndef __SDK_H__
#define __SDK_H__
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
namespace sdk {
struct Location {
    int x, y;
    Location(const int &tx, const int &ty) : x(tx), y(ty) {
    }
    friend bool operator< (const Location &l1, const Location &l2) {
        if (l1.x != l2.x)
            return l1.x < l2.x;
        return l1.y < l2.y;
    }
    friend bool operator> (const Location &l1, const Location &l2) {
        return l2 < l1;
    }
    friend bool operator== (const Location &l1, const Location &l2) {
        return l1.x == l2.x && l1.y == l2.y;
    }
    friend bool operator!= (const Location &l1, const Location &l2) {
        return !(l1 == l2);
    }
} home(0, 0);   // struct Location
int distance(const Location &l1, const Location &l2) {
    return abs(l1.x - l2.x) + abs(l1.y - l2.y);
}
bool cmp(const Location &l1, const Location &l2) {
    return l1 < l2;
}
struct Food : public Location {
    int number;
};  // struct Food
struct Ant : public Location {
    std::vector<Food> foods;
};  // struct Ant
static int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1},
           dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
static int num = sizeof(dx) / siezof(*dx);
template <class T>
void merge(std::vector<T> &target, const std::vector<T> &source) {
    std::vector<T> temp;
    int i, j;
    for (i = 0, j = 0; i < target.size() && j < source.size(); ) {
        if (target[i] < source[j])
            temp.push_back(target[i++]);
        else if (target[i] > source[j])
            temp.push_back(source[j++]);
        else {  // asset target and source have been sorted and have no repeat
            temp.push_back(target[i++]);
            j++;
        }
    }
}
class Map {
    int x_max, y_max;
    std::vector<Ant> ants;
    void action(const int &num) {
        Ant &ant = ants[num];
        if (!ant.foods.empty()) {
            Location nearfood = ant.foods[0];
            for (int i = 0; i < ant.foods.size(); i++)
                if (distance(ant, nearfood) > distance(ant, ant.foods[i]))
                    nearfood = ant.foods[i];
            if (ant.x < nearfood.x)
                ant.x++;
            else if (ant.x > nearfood.x)
                ant.x--;
            if (ant.y < nearfood.y)
                ant.y++;
            else if (ant.y > nearfood.y)
                ant.y--;
            return ;
        }
        const int t = rand() % num;
        ant.x = (ant.x + dx[t]) % x_max;
        ant.y = (ant.y + dy[t]) % y_max;
    }
public:
    Map(const int &x, const int &y) : x_max(x), y_max(y) {
    }
    void flash() {
        sort(ants.begin(), ants.end(), cmp);
        for (int i = 0; i < ants.size(); i++) {
            int same = 1;
            while (i + same < ants.size() && ants[i] == ants[i + same])
                same++;
            std::vector<Food> foods;
            for (int j = 0; j < same; j++) {
            }
        }
    }
}
}   // namespace sdk
#endif  // __SDK_H__
