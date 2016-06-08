#include <vector>
#include "point.h"
#include "door.h"
#include "cell.h"
#include <SFML/Graphics.hpp>

using namespace std;

#ifndef BOARD_H
#define	BOARD_H

class board {
public:
    board(int s, int w);
    bool checkCell(int x, int y);
    void setEventType (int x, int y, int i);
    int getEventType (int x, int y);
    void updateCell(int x, int y, int c);
    bool onEnemy(point player);
    void miniMapUpdate();
    void generateDoor(int x, int y, char pos, int t);
    void generateItem(int x, int y, int t, int posX, int posY);
    cell*** array2d;

private:
    vector<point> getAdj(int x, int y);
    int size;
};

#endif	/* BOARD_H */
