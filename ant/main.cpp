#include "sdk.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <getopt.h>
using namespace std;
using namespace sdk;
/*struct option {
  const char *name;
    //name表示的是长参数名
  int has_arg;
    //has_arg有3个值，no_argument(或者是0)，表示该参数后面不跟参数值
    //   required_argument(或者是1),表示该参数后面一定要跟个参数值
    //   optional_argument(或者是2),表示该参数后面可以跟，也可以不跟参数值
  int *flag;
    //用来决定，getopt_long()的返回值到底是什么。如果flag是null，则函数会返回与该项option匹配的val值
  int val;
    //和flag联合决定返回值
}*/
void usage(const string &name) {
    cout << "Usage: " << name << " -w <map width> -h <map height> -a <ant number> -f <food number>" << endl
        << "        -u --usage          the program's usage" << endl
        << "        -w --width          the map's width" << endl
        << "        -h --height         the map's height" << endl
        << "        -a --ant            the ant's number" << endl
        << "        -f --food           the food's number" << endl;
}
string long_to_short(const option long_opts[], const int &opts_number) {
    string short_opts = "";
    for (int i = 0; i < opts_number; i++) {
        short_opts += long_opts[i].val;
        switch (long_opts[i].has_arg) {
            case no_argument:
                short_opts += "";
                break;
            case required_argument:
                short_opts += ":";
                break;
            case optional_argument:
                short_opts += ":";
                break;
        }
    }
    return short_opts;
}
int main(int argc, char *argv[]) {
    int width = -1, height = -1, ant = -1, food = -1;
    const option long_opts[] = {
        {"usage", no_argument, NULL, 'u'},
        {"width", required_argument, NULL, 'w'},
        {"height", required_argument, NULL, 'h'},
        {"ant", required_argument, NULL, 'a'},
        {"food", required_argument, NULL, 'f'}
    };
    for (int c; (c = getopt_long(argc, argv, long_to_short(long_opts, sizeof(long_opts) / sizeof(*long_opts)).c_str(), long_opts, NULL)) != -1; ) {
        switch (c) {
            case 'u':
                usage(argv[0]);
                return 0;
                break;
            case 'w':
                if ((width = atoi(optarg)) <= 0) {
                    cout << argv[0] << ": option requires a legal argument -- '" << (char)c << "'" << endl;
                    return 0;
                }
                break;
            case 'h':
                if ((height = atoi(optarg)) <= 0) {
                    cout << argv[0] << ": option requires a legal argument -- '" << (char)c << "'" << endl;
                    return 0;
                }
                break;
            case 'a':
                if ((ant = atoi(optarg)) <= 0) {
                    cout << argv[0] << ": option requires a legal argument -- '" << (char)c << "'" << endl;
                    return 0;
                }
                break;
            case 'f':
                if ((food = atoi(optarg)) <= 0) {
                    cout << argv[0] << ": option requires a legal argument -- '" << (char)c << "'" << endl;
                    return 0;
                }
                break;
            case '?':
                return 1;
                break;
                /* getopt() has it's own error process
                if (optopt == 'w' || optopt == 'h' || optopt == 'a' || optopt == 'f')
                    cout << "Error: option -" << (char)optopt << " requires an argument" << endl;
                else if (isprint(optopt))
                    cout << "Error: unknown option '-" << (char)optopt << "'" << endl;
                else
                    cout << "Error: unknown option character '\\" << optopt << "'" << endl;
                return 1;*/
        }
    }
/*
    srand(time(NULL));
    Map map(width, height, Home(0, 0));
    for (int i = 0; i < ant; i++)
        map.addant(Ant(map.home.x, map.home.y));
    for (int i = 0; i < food; i++)
        map.addfood(Food(rand() % width, rand() % height, 100));
    for (int i = 0; i < 100; i++) {
        cout << map << endl;
        map.flash();
    }*/
    return 0;
}
