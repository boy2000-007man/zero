#define MAIN_C
#include "color.h"
#include <time.h>
#include <stdio.h>

int main() {
    srand(time(NULL));
    for (; mainMenu() == 1;) {
        int score = 0;
        mapSize = firstMenu();//一级子菜单,获得地图边长 
        colorMap map = newMap();
        int x, y;
        while (checkMap(map)) {
            printMap(map);
            scanf("%d%d", &y, &x);
            x--;y--;
            if (checkPoint(map, x, y)) {
                int tmp = eatPoint(map, x, y, map[locatePoint(x, y)].color);
                printf("you clear %d points!", tmp);
                while (!kbhit());
                score += tmp * tmp;
            }
            cleanMap(map);
        }
        deleteMap(map);
        printf("GameOver!\nYou have got %d scores\n", score);
        comment(score);
        printf("Press any key to Main Menu\n");
        while (!kbhit());
    }
    system("pause");
    return 0;
}
