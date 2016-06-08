#include <vector>
#include "point.h"
#include "item.h"
#include <SFML/Graphics.hpp>

using namespace std;

#ifndef PLAYER_H
#define	PLAYER_H

class player{
public:
    player(int a, int b, int h, int c);
    point getCoord();
    void setCoord(point p);
    point move(char direction);
    int getHealth();
    int setHealth(int damage);
    bool getStatus();
    void setDest(int a, int b);
    void update(int time);
    bool hasItem(int type);
    void addItem(item* i);
    void changeSpeed(int i);
    sf::CircleShape topDown;
    vector<item*> inventory;
    bool hasTorch;
    item* torch;

private:
    int healthMax;
    int healthCur;
    int moveSpeed;
    int playerRad;
    point onMap;
    point destination;
    bool hasDest;
};

#endif	/* PLAYER_H */

