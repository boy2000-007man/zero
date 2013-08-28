#include "sdk.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
namespace sdk {
Location::Location(const int &tx, const int &ty) : x(tx), y(ty) {
}
bool operator< (const Location &l1, const Location &l2) {
    if (l1.x != l2.x)
        return l1.x < l2.x;
    return l1.y < l2.y;
}
bool operator> (const Location &l1, const Location &l2) {
    return l2 < l1;
}
bool operator== (const Location &l1, const Location &l2) {
    return l1.x == l2.x && l1.y == l2.y;
}
bool operator!= (const Location &l1, const Location &l2) {
    return !(l1 == l2);
}
Home::Home(const int &tx, const int &ty, int tfood) : Location(tx, ty), food(tfood) {
}
static int distance(const Location &l1, const Location &l2) {
    return abs(l1.x - l2.x) + abs(l1.y - l2.y);
}
static bool cmp(const Location &l1, const Location &l2) {
    return l1 < l2;
}
Food::Food(const int &tx, const int &ty, const int &tfood) : Location(tx, ty), food(tfood) {
}
Ant::Ant(const int &tx, const int &ty, int tfood) : Location(tx, ty), food(tfood) {
}
void Ant::moveto(const Location &target) {
    if (x < target.x)
        x++;
    if (x > target.x)
        x--;
    if (y < target.y)
        y++;
    if (y > target.y)
        y--;
}
void Ant::action(const Map &map) {
    if (food != 0) {
        moveto(map.home);
    } else if (foods.empty()) {
        moveto(Location(rand() % map.x, rand() % map.y));
    } else {
        Location nearfood = foods[0];
        for (int i = 0; i < foods.size(); i++)
            if (distance(*this, nearfood) > distance(*this, foods[i]))
                nearfood = foods[i];
        moveto(nearfood);
    }
}
static int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1},
           dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
static int num = sizeof(dx) / sizeof(*dx);
static const int antValue = 10;
template <class T>
static void merge(std::vector<T> &target, const std::vector<T> &source) {
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
Map::Map(const int &tx, const int &ty, const Home &thome) : x(tx), y(ty), home(thome) {
}
void Map::flash() {
    sort(ants.begin(), ants.end(), cmp);
    for (int i = 0; i < ants.size(); ) {
        int same = 1;
        while (i + same < ants.size() && ants[i] == ants[i + same])
            same++;
        for (int j = 1; j < same; j++) {
            merge(ants[i].foods, ants[i + j].foods);
        }
        for (int j = 1; j < same; j++) {
            ants[i + j].foods = ants[i].foods;
        }
        i += same;
    }
    int food[x][y];
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            food[i][j] = 0;
    for (int i = 0; i < foods.size(); i++)
        food[foods[i].x][foods[i].y] = foods[i].food;
    for (int i = 0; i < ants.size(); i++) {
        Ant &ant = ants[i];
        if (food[ant.x][ant.y] != 0) {
            merge(ant.foods, std::vector<Food>(1, Food(ant.x, ant.y, food[ant.x][ant.y])));
            if (ant.food == 0) {
                ant.food++;
            }
        }
        if (ant == home) {
            home.food += ant.food;
            ant.food = 0;
        }
        ant.action(*this);
    }
    while (home.food >= antValue) {
        home.food -= antValue;
        ants.push_back(Ant(home.x, home.y));
    }
}
std::ostream& operator<< (std::ostream &out, const Map &map) {
    const int x = map.x, y = map.y;
    char tmap[x][y];
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            tmap[i][j] = '*';
    for (int i = 0; i < map.ants.size(); i++)
        tmap[map.ants[i].x][map.ants[i].y] = 'A';
    for (int i = 0; i < map.foods.size(); i++)
        tmap[map.foods[i].x][map.foods[i].y] = 'F';
    tmap[map.home.x][map.home.y] = 'H';
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++)
            out << tmap[i][j];
        out << std::endl;
    }
}
void Map::addant(const Ant &ant) {
    ants.push_back(ant);
}
void Map::addfood(const Food &food) {
    for (int i = 0; i < foods.size(); i++)
    if (foods[i] == food) {
        foods[i].food += food.food;
        return ;
    }
    foods.push_back(food);
}
}   // namespace sdk
