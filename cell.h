#include <vector>
#include <iostream>
#include "point.h"
#include "door.h"
#include "item.h"
#include <SFML/Graphics.hpp>

using namespace std;

#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class cell {
public:
    cell(int a, int b, int c, int d, int aMini, int bMini, int cMini, int dMini, int type);
    void updateAnim(int time);

    bool isEmpty;
    bool hasPlayer;
    bool hasEnemy;
    bool hasEvent;
    bool isRevealed;
    point nw;
    point se;
    point nwMini;
    point seMini;
    int eventType;

    sf::RectangleShape bg;
    sf::RectangleShape bgMini;
    sf::RectangleShape bgTorch;
    sf::RectangleShape bgGlow;
    vector<door*> exits;
    vector<item*> contents;

    bool operator==(const cell &other){
        return (nw.x == other.nw.x && nw.y == other.nw.y && se.x == other.se.x && se.y == other.se.y);
    }

private:
    int glowAlpha;
    bool glowIsInc;
    sf::Texture texture;
    sf::Texture torch01;
    sf::Texture torch02;
    sf::Texture glow;
    int whichTorch;
};

#endif // CELL_H_INCLUDED
