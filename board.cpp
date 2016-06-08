#include <cstdio>
#include "board.h"

#include <SFML/Graphics.hpp>

using namespace std;

// Initialize board to be a s x s grid, initialize w-wide cells
board::board(int s, int w){
    size = s;
    array2d = new cell**[size];

    for (int i = 0; i < size; i++) {
        array2d[i] = new cell*[size];
    }

    int offsetX = 0;
    int offsetY = 0;

    for (int i = 0; i < size; i++) {
        offsetX += 18;
        for (int j = 0; j < size; j++) {
            offsetY += 18;
            if (i == 2 && j == 1)
                array2d[i][j] = new cell(290,10,990,710,
                                     w/14*(i)+offsetX+1022,
                                     w/14*(j)+offsetY+32,
                                     w/14*(i+1)+offsetX+1022,
                                     w/14*(j+1)+offsetY+32, 1);
            else
                array2d[i][j] = new cell(290,10,990,710,
                                     w/14*(i)+offsetX+1022,
                                     w/14*(j)+offsetY+32,
                                     w/14*(i+1)+offsetX+1022,
                                     w/14*(j+1)+offsetY+32, 0);
        }
        offsetY = 0;
    }
}

// is cell at coordinates x,y empty, returns true if empty, false otherwise
bool board::checkCell(int x, int y){
    return (array2d[x][y]->isEmpty);
}

void board::setEventType (int x, int y, int i){
    array2d[x][y]->eventType = i;
}

int board::getEventType (int x, int y){
    return (array2d[x][y]->eventType);
}

// updates cell conditions with c variable
void board::updateCell(int x, int y, int c){
    //vector<point> list = this->getAdj(x,y);
    switch (c){
        // Set empty
        case 0:
            array2d[x][y]->hasPlayer = false;
            array2d[x][y]->hasEvent = false;
            array2d[x][y]->hasEnemy = false;
            array2d[x][y]->isEmpty = true;
            break;

        // Move player
        case 1:
            array2d[x][y]->hasPlayer = true;
            array2d[x][y]->isRevealed = true;
            array2d[x][y]->isEmpty = false;
            //for (int i = 0; i < list.size(); i++)
            //    this->updateCell(list[i].x,list[i].y,4);
            break;

        // Has Enemy
        case 2:
            array2d[x][y]->hasEnemy = true;
            array2d[x][y]->isEmpty = false;
            break;

        // Has Event
        case 3:
            array2d[x][y]->hasEvent = true;
            array2d[x][y]->isEmpty = false;
            break;

        // Reveal
        case 4:
            array2d[x][y]->isRevealed = true;
            break;

        // Remove player
        case 5:
            array2d[x][y]->hasPlayer = false;
            if (array2d[x][y]->hasEvent || array2d[x][y]->hasEnemy)
                array2d[x][y]->isEmpty = false;
            else array2d[x][y]->isEmpty = true;
            break;

        // Remove enemy
        case 6:
            array2d[x][y]->hasEnemy = false;
            if (array2d[x][y]->hasEvent || array2d[x][y]->hasPlayer)
                array2d[x][y]->isEmpty = false;
            else array2d[x][y]->isEmpty = true;
            break;

        default:
            printf("You entered %d\n", c);
            cerr << "Update cell failed, not valid condition code\n";
    }
}

bool board::onEnemy(point player){
    if (array2d[player.x][player.y]->hasEnemy) return true;
    else return false;
}

void board::miniMapUpdate(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (array2d[i][j]->hasPlayer)
                array2d[i][j]->bgMini.setFillColor(sf::Color::Yellow);
            else
                array2d[i][j]->bgMini.setFillColor(sf::Color(200,200,200,255));
        }
    }
}

void board::generateDoor(int x, int y, char pos, int t){
    point origin;
    origin.x = x;
    origin.y = y;
    array2d[x][y]->exits.push_back(new door(t, pos, origin));
}

void board::generateItem(int x, int y, int t, int posX, int posY){
    point origin;
    origin.x = posX;
    origin.y = posY;
    array2d[x][y]->contents.push_back(new item(t, origin));
}

vector<point> board::getAdj(int x, int y){
    vector<point> list;
    if (y-1 > -1){
        point s;
        s.x = x;
        s.y = y-1;
        list.push_back(s);
    }
    if (x-1 > -1){
        point w;
        w.x = x-1;
        w.y = y;
        list.push_back(w);
    }
    if (x+1 < size){
        point e;
        e.x = x+1;
        e.y = y;
        list.push_back(e);
    }
    if (y+1 < size){
        point n;
        n.x = x;
        n.y = y+1;
        list.push_back(n);
    }

    return (list);
}
