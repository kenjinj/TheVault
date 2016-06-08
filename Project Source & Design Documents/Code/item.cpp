#include <iostream>
#include <cstdio>
#include "item.h"

using namespace std;

item::item(int t, point origin){
    location.x = origin.x;
    location.y = origin.y;
    bgInven = sf::RectangleShape(sf::Vector2f(40,40));
    bgFloor = sf::RectangleShape(sf::Vector2f(40,40));
    type = t;
    canPickUp = false;
    if (type == 0){}
    //keys types 1 - 4
    if (type == 1){
        if (!floorSprite.loadFromFile("Textures/keyFloor00.png"))
            cerr << "File keyFloor00.png load error\n";
        if (!inventoryIcon.loadFromFile("Textures/keyInven00.png"))
            cerr << "File keyInven00.png load error\n";
        description = "\nYou pick up a key engraved\nwith a white sun.\n";
        bgInven.setPosition(1030,625);
    }
    if (type == 2){
        if (!floorSprite.loadFromFile("Textures/keyFloor01.png"))
            cerr << "File keyFloor01.png load error\n";
        if (!inventoryIcon.loadFromFile("Textures/keyInven01.png"))
            cerr << "File keyInven01.png load error\n";
        description = "\nYou pick up a key engraved\nwith a golden scorpion.\n";
        bgInven.setPosition(1087,625);
    }
    if (type == 3){
        if (!floorSprite.loadFromFile("Textures/keyFloor02.png"))
            cerr << "File keyFloor02.png load error\n";
        if (!inventoryIcon.loadFromFile("Textures/keyInven02.png"))
            cerr << "File keyInven02.png load error\n";
        description = "\nYou pick up a key engraved\nwith an azure horse.\n";
        bgInven.setPosition(1146,625);
    }
    if (type == 4){
        if (!floorSprite.loadFromFile("Textures/keyFloor03.png"))
            cerr << "File keyFloor03.png load error\n";
        if (!inventoryIcon.loadFromFile("Textures/keyInven03.png"))
            cerr << "File keyInven03.png load error\n";
        description = "\nYou pick up a key engraved\nwith a crimson design.\n";
        bgInven.setPosition(1203,625);
    }
    // Torch
    if (type == 5){
        bgGlow = sf::RectangleShape(sf::Vector2f(150,150));
        if (!floorSprite.loadFromFile("Textures/fallenTorch01.png"))
            cerr << "File fallenTorch01.png load error\n";
        if (!inventoryIcon.loadFromFile("Textures/fallenTorch01.png"))
            cerr << "File fallenTorch01.png load error\n";
        inventoryIcon.setSmooth(true);
        if (!floorSprite2.loadFromFile("Textures/fallenTorch02.png"))
            cerr << "File fallenTorch02.png load error\n";
        floorSprite2.setSmooth(true);
        if (!glow.loadFromFile("Textures/torchItemGlow.png"))
            cerr << "File torchItemGlow.png load error\n";
        glow.setSmooth(true);
        description = "\nYou retrieve the fallen torch.\n\n";
        bgInven.setPosition(1053,360);
        bgGlow.setTexture(&glow, false);
        bgGlow.setOrigin(75, 75);
        bgGlow.setPosition(location.x, location.y);
        glowAlpha = 150;
        glowIsInc = false;
        bgGlow.setFillColor(sf::Color(255,255,255,glowAlpha));
        whichTorch = 1;
    }
    canPickUp = true;
    pickedUp = false;
    inventoryIcon.setSmooth(true);
    bgInven.setTexture(&inventoryIcon, false);
    floorSprite.setSmooth(true);
    bgFloor.setTexture(&floorSprite, false);
    bgFloor.setFillColor(sf::Color(255,255,255,255));
    if (type == 3) bgFloor.setFillColor(sf::Color(255,255,255,1));
    bgFloor.setOrigin(20, 20);
    bgFloor.setPosition(location.x, location.y);
    onMap = true;
}

void item::pickUp(){
    canPickUp = false;
    pickedUp = true;
    onMap = false;
}

point item::getLocation(){
    return (location);
}

void item::setLocation(int x, int y){
    location.x = x;
    location.y = y;
    bgFloor.setPosition(location.x, location.y);
}

int item::getType(){
    return (type);
}

void item::updateAnim(int time){
    if (glowIsInc == false) glowAlpha--;
    if (glowAlpha < 75) glowIsInc = true;
    if (glowIsInc == true) glowAlpha++;
    if (glowAlpha > 150) glowIsInc = false;
    bgGlow.setFillColor(sf::Color(255,255,255,glowAlpha));
    if (time % 15 == 1){
        if (whichTorch == 1){
            bgFloor.setTexture(&floorSprite2, false);
            whichTorch = 2;
        }
        else {
            bgFloor.setTexture(&floorSprite, false);
            whichTorch = 1;
        }
    }
}
