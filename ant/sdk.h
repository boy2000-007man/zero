#ifndef __SDK_H__
#define __SDK_H__
#include <vector>
#include <iostream>
namespace sdk {
struct Location {
    int x, y;
    Location(const int &tx, const int &ty);
    friend bool operator< (const Location &l1, const Location &l2);
    friend bool operator> (const Location &l1, const Location &l2);
    friend bool operator== (const Location &l1, const Location &l2);
    friend bool operator!= (const Location &l1, const Location &l2);
};  // struct Location
struct Home : public Location {
    int food;
    Home(const int &tx, const int &ty, int tfood = 0);
};  // struct Home
struct Food : public Location {
    int food;
    Food(const int &tx, const int &ty, const int &tfood);
};  // struct Food
class Map;
struct Ant : public Location {
    int food;
    std::vector<Food> foods;
    Ant(const int &tx, const int &ty, int tfood = 0);
    void moveto(const Location &target);
    void action(const Map &map);
};  // struct Ant
class Map {
    std::vector<Ant> ants;
    std::vector<Food> foods;
public:
    int x, y;
    Home home;
    Map(const int &tx, const int &ty, const Home &thome);
    void flash();
    friend std::ostream& operator<< (std::ostream &out, const Map &map);
    void addant(const Ant &ant);
    void addfood(const Food &food);
};  // class Map
}   // namespace sdk
#endif  // __SDK_H__
