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
};  // struct Location
struct Home : public Location {
    int food;
    Home(const int &tx, const int &ty) : x(tx), y(ty), food(0) {
    }
}
int distance(const Location &l1, const Location &l2) {
    return abs(l1.x - l2.x) + abs(l1.y - l2.y);
}
bool cmp(const Location &l1, const Location &l2) {
    return l1 < l2;
}
struct Food : public Location {
    int food;
    Food(const int &tx, const int &ty, const int &vol) : x(tx), y(ty), volume(vol) {
    }
};  // struct Food
struct Ant : public Location {
    int food;
    std::vector<Food> foods;
    Ant(const int &tx, const int &ty) : x(tx), y(ty), food(0) {
    }
    void moveto(const Location &target) {
        if (x < target.x)
            x++;
        if (x > target.x)
            x--;
        if (y < target.y)
            y++;
        if (y > target.y)
            y--;
    }
    void action() {
        if (food != 0) {
            moveto(Map::home);
        } else if (foods.empty()) {
            moveto(Location(rand() % Map::x, rand() % Map::y));
        } else {
            Location nearfood = foods[0];
            for (int i = 0; i < foods.size(); i++)
                if (distance(*this, nearfood) > distance(*this, foods[i]))
                    nearfood = foods[i];
            moveto(nearfood);
        }
    }
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
    while (i < target.size())
        temp.push_back(target[i++]);
    while (j < source.size())
        temp.push_back(source[j++]);
    target = temp;
}
class Map {
    static int x, y;
    static Home home;
    std::vector<Ant> ants;
    std::vector<Food> foods;
public:
    Map(const int &x, const int &y) : map_x(x), map_y(y) {
    }
    void flash() {
        sort(ants.begin(), ants.end(), cmp);
        for (int i = 0; i < ants.size(); ) {
            int same = 1;
            while (i + same < ants.size() && ants[i] == ants[i + same])
                same++;
            for (int j = 1; j < same; j++) {
                merge(ant[i].foods, ant[i + j].foods);
            }
            for (int j = 1; j < same; j++) {
                ant[i + j].foods = ant[i].foods;
            }
            i += same;
        }
        int food[map_x][map_y];
        for (int i = 0; i < map_x; i++)
            for (int j = 0; j < map_y; j++)
                food[i][j] = 0;
        for (int i = 0; i < foods.size(); i++)
            food[foods.x][foods.y] = foods.food;
        for (int i = 0; i < ants.size(); i++) {
            Ant &ant = ants[i];
            if (food[ant.x][ant.y] != 0) {
                merge(ant.foods, std::vector<Food>(1, Food(ant.x, ant.y, food[ant.x][ant.y])));
                if (ant.food == 0) {
                    ant.food++;
                }
            }
            if (ant == Map::home) {
                Map::home.food += ant.food;
                ant.food = 0;
            }
            ant.action();
        }
    }
};  // class Map
int Map::x(100), Map::y(100);
Home Map::home(0, 0);
}   // namespace sdk
#endif  // __SDK_H__
