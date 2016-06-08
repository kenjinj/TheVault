#include <string>
#include "point.h"
#include <SFML/Graphics.hpp>

using namespace std;

#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

class item{
public:
    item(int t, point origin);
    void pickUp();
    bool pickedUp;
    bool onMap;
    bool canPickUp;
    point getLocation();
    void setLocation(int x, int y);
    int getType();
    sf::RectangleShape bgFloor;
    sf::RectangleShape bgInven;
    string description;
    bool activate1;
    bool activate2;
    bool activate3;

    // For Torch
    sf::RectangleShape bgGlow;
    void updateAnim(int time);

private:
    point location;
    int type;
    sf::Texture floorSprite;
    sf::Texture inventoryIcon;

    // For Torch
    sf::Texture floorSprite2;
    sf::Texture glow;
    int glowAlpha;
    bool glowIsInc;
    int whichTorch;
};

#endif // ITEM_H_INCLUDED
