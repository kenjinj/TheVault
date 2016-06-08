#include "point.h"
#include <SFML/Graphics.hpp>

#ifndef ENEMY_H
#define	ENEMY_H

using namespace std;

class enemy{
public:
    enemy (int xIn, int yIn, int t);
    point getCoord();
    int attack(point player);
    int getHealth();
    void setStatus(bool attacked);
    bool getStatus();
    void setHealth(int damage);
    point move(int size);

private:
    int type;
    int health;
    int x;
    int y;
    bool justAttacked;
};

#endif	/* ENEMY_H */
