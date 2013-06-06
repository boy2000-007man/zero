#ifndef COLOR_H
#define COLOR_H

#ifdef MAIN_C
int mapSize;
#else
extern int mapSize;
#endif

#ifndef __cplusplus
#define true 1
#define false 0
typedef int bool;
#endif

struct colorPoint{
    enum {
        none = -1, red, yellow, green, blue
    } color;
}; 
typedef struct colorPoint* colorMap;

void selectColor(struct colorPoint*);
void hideCursor();
void cleanScreen();
int locatePoint(int, int);
colorMap newMap();
void deleteMap(colorMap);
void cleanColumn(colorMap, int);
void cleanLine(colorMap);
void cleanMap(colorMap);
void printPoint(struct colorPoint);
void printMap(colorMap);
int mainMenu();
int firstMenu();
void comment(int);
bool checkPoint(colorMap, int, int);
bool checkMap(colorMap);
int eatPoint(colorMap, int, int, int);

#endif
