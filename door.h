#include <string>
#include "point.h"
#include <SFML/Graphics.hpp>

using namespace std;

#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

class door{
public:
    door(int a, char pos, point origin);
    bool isLocked;
    sf::RectangleShape bg;
    bool unlock(int key);
    point getLocation();
    point getDoorDest();
    int getType();
    string description;
    // final door
    sf::RectangleShape bgDemon;
    void updateAnim(int time);

private:
    point location;
    point connectedTo;
    int type;
    sf::Texture texture;
    // final door
    sf::Texture demonGlow;
    int glowAlpha;
    bool glowIsInc;
};

#endif // DOOR_H_INCLUDED
