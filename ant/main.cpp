#include "sdk.h"
#include <iostream>
using namespace std;
using namespace sdk;

int main() {
    Map map(30, 30, Home(0, 0));
    map.addant(Ant(0, 0));
    map.addfood(Food(10, 1, 100));
    //for (int i = 0; i < 10; i++) {
        cout << map << endl;
        //map.flash();
    return 0;
}
