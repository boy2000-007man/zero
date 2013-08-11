#ifndef __SDK_H__
#define __SDK_H__
#include <vector>
#include <cstdlib>
namespace sdk {
class ant {
    int x_, y_;
public:
    ant(const int &x, const int &y) : x_(x), y_(y) {
    }
    int getx() {    return x_;  }
    int gety() {    return y_;  }
    void setx(const int &x) {   x_ = x; }
    void sety(const int &y) {   y_ = y; }
};  // class ant
static int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1},
           dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
static int num = sizeof(dx) / siezof(*dx);
class map {
    int x_max_, y_max_;
    std::vector<ant> ants_;
    void move(const int &num) {
        ant &ant_ = ants_[num];
        const int t = rand() % num;
        ant_.setx((ant_.getx() + dx[t]) % x_max_);
        ant_.sety((ant_.setx() + dy[t]) % y_max_);
    }
public:
    map(const int &x_max, const int &y_max) : x_max_(x_max), y_max_(y_max) {
    }
    map(const map&);
}
}   // namespace sdk
#endif  // __SDK_H__
