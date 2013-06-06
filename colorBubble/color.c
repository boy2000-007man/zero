#include "color.h"
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>

void setColor(struct colorPoint *p) {
     p->color = rand() % 4;
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    return ;
}//隐藏光标 

void cleanScreen() {
     system("cls");
}
//清理屏幕 

int locatePoint(int line, int column) {
    return mapSize * line + column;
}
//将二维点转化为一维数组 

colorMap newMap() {
    colorMap map = malloc(mapSize * mapSize * sizeof(struct colorPoint));
    int i;
    for (i = 0; i < mapSize * mapSize; i++)
        setColor(&map[i]);
    return map;
}

void deleteMap(colorMap map) {
    free(map);
}

void cleanColumn(colorMap map, int column) {
    int line, lineToPlace = mapSize - 1;
    for (line = mapSize - 1; line >= 0; line--)
        if (map[locatePoint(line, column)].color != -1) {
            struct colorPoint tmp = map[locatePoint(line, column)];
            map[locatePoint(line, column)].color = -1;
            map[locatePoint(lineToPlace--, column)] = tmp;
        }
}

void cleanLine(colorMap map) {
    int line, column, columnToPlace = mapSize - 1;
    for (column = mapSize - 1; column >= 0; column--) {
        bool empty = true;
        for (line = 0; line < mapSize; line++)
            empty &= map[locatePoint(line, column)].color == -1;
        if (!empty) {
            for (line = 0; line < mapSize; line++) {
                struct colorPoint tmp = map[locatePoint(line, column)];
                map[locatePoint(line, column)].color = -1;
                map[locatePoint(line, columnToPlace)] = tmp;
            }
            columnToPlace--;
        }
    }
}

void cleanMap(colorMap map) {
     int column;
     for (column = 0; column < mapSize; column++)
         cleanColumn(map, column);
     cleanLine(map);
}//清理数组xy 

void printPoint(struct colorPoint p) {
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
     WORD att;
     switch (p.color){
         case -1:att = FOREGROUND_INTENSITY;break;
         case 0:att = FOREGROUND_RED|FOREGROUND_INTENSITY;break;
         case 1:att = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;break;
         case 2:att = FOREGROUND_GREEN|FOREGROUND_INTENSITY;break;
         case 3:att = FOREGROUND_BLUE|FOREGROUND_INTENSITY;break;
     }
     SetConsoleTextAttribute(handle, att);
     printf("●");
     SetConsoleTextAttribute(handle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}//打印有颜色的点 

void printMap(colorMap map){
     cleanScreen();
     int line, column;
     for (line = 0; line < mapSize; line++) {
         for (column = 0; column < mapSize; column++)
             printPoint(map[locatePoint(line, column)]);
         printf("\n");
     }
}//将一维数组打印成二维点阵 


int mainMenu(){
    cleanScreen();
    printf("                Snake\n");
    printf("             1.Start Game\n");
    printf("             2.Quit Game\n");
    while (!kbhit());
    switch (getch()){
           case '1':
                return 1;
           case '2':
                return 2;
           default:
                return mainMenu();
    }
}//主菜单 

int firstMenu() {
    int N;
    do {
        cleanScreen();
        printf("     Please enter the size of the map(10 or 20):\n");
        scanf("%d", &N);
    } while (N != 10 && N != 20);
    return N;

}//一级子菜单 

void comment(int score){
     if (score < 10)
            printf("Your performance is too bad.\nTry harder next time and get a better score.\n");
        else if (score <20)
            printf("Your performance is good.\nTry harder next time and get a better score.\n");
        else if (score <30)
            printf("Your performance is very good.\nTry harder next time and get a better score.\n");
        else
            printf("You have wasted so much time on this game.\nMake sure your homework is done.\n");

}//评论 


static const int dx[] = {1, -1, 0, 0},
                 dy[] = {0, 0, 1, -1};


bool checkPoint(colorMap map, int x, int y) {
    bool tmp = false;
    int i;
    for (i = 0; i < 4; i++)
        if (0 <= x + dx[i] && x + dx[i] < mapSize && 0 <= y + dy[i] && y + dy[i] < mapSize)
            tmp |= map[locatePoint(x + dx[i], y + dy[i])].color == map[locatePoint(x, y)].color && map[locatePoint(x, y)].color != -1;
    return tmp;

}

bool checkMap(colorMap map) {
    bool tmp = false;
    int i, j;
    for (i = 0; i < mapSize; i++)
        for (j = 0; j < mapSize; j++)
            tmp |= checkPoint(map, i, j);
    return tmp;

}

int eatPoint(colorMap map, int x, int y, int color) {
    if (x < 0 || x >= mapSize || y < 0 || y >= mapSize)
        return 0;
    if (map[locatePoint(x, y)].color != color)
        return 0;
    map[locatePoint(x, y)].color = -1;
    int tmp = 0, i;
    for (i = 0; i < 4; i++)
        tmp += eatPoint(map, x + dx[i], y + dy[i], color);
    return tmp + 1;
}
