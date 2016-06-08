#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>
#include "player.h"

using namespace std;

// c is room width
player::player(int a, int b, int h, int c){
    onMap.x = a;
    onMap.y = b;
    playerRad = 20;
    healthMax = h;
    healthCur = healthMax;
    moveSpeed = 2;
    topDown = sf::CircleShape(playerRad);
    topDown.setOrigin(playerRad,playerRad);
    topDown.setFillColor(sf::Color(255,255,255,255));
    topDown.setPosition((290)+(c/2),(c/2));

    destination.x = topDown.getPosition().x;
    destination.y = topDown.getPosition().y;
    hasDest = false;
    hasTorch = false;
}

point player::getCoord(){
    point coord;
    coord.x = onMap.x;
    coord.y = onMap.y;

    return(coord);
}

void player::setCoord(point p){
    onMap.x = p.x;
    onMap.y = p.y;
}

point player::move(char direction){
    point coord;
    if (direction == 'n'){
        coord.y = onMap.y - 1;
        coord.x = onMap.x;
    }
    if (direction == 's'){
        coord.y = onMap.y + 1;
        coord.x = onMap.x;
    }
    if (direction == 'w'){
        coord.y = onMap.y;
        coord.x = onMap.x - 1;
    }
    if (direction == 'e'){
        coord.y = onMap.y;
        coord.x = onMap.x + 1;
    }
    onMap.x = coord.x;
    onMap.y = coord.y;
    return (coord);
}

int player::getHealth(){
    return (healthCur);
}

int player::setHealth(int damage){
    healthCur -= damage;
    return(healthCur - damage);
}

// returns if player is dead;
bool player::getStatus(){
    bool hasDied = false;
    if (healthCur < healthMax && healthCur != 0)
        printf("\n * You are wounded with %d health remaining\n", healthCur);
    else if (healthCur == healthMax)
        printf("\n * You are at full health.\n");
    else {
        hasDied = true;
        srand (time(NULL));
        int deathMsg = rand() % 5;
        if (deathMsg == 0 || deathMsg == 1) cout << "\n * Your last breath passes through your now lifeless lips, you have died.\n";
        if (deathMsg == 2 || deathMsg == 3) cout << "\n * So close and yet so far. This place will be your tomb, you have perished.\n";
        if (deathMsg == 4) cout << "\n * By some stroke of luck you have defeated the mon... wait, no, you have died.\n";
    }
    return(hasDied);
}

void player::setDest(int a, int b){
    destination.x = a;
    destination.y = b;
    hasDest = true;
}

void player::update(int time){
    if (hasDest){
        if ((int)topDown.getPosition().x > destination.x + moveSpeed){
            topDown.setPosition(topDown.getPosition().x - moveSpeed, topDown.getPosition().y);
        }
        if ((int)topDown.getPosition().x < destination.x + moveSpeed){
            topDown.setPosition(topDown.getPosition().x + moveSpeed, topDown.getPosition().y);
        }
        if ((int)topDown.getPosition().y > destination.y + moveSpeed){
            topDown.setPosition(topDown.getPosition().x, topDown.getPosition().y - moveSpeed);
        }
        if ((int)topDown.getPosition().y < destination.y + moveSpeed){
            topDown.setPosition(topDown.getPosition().x, topDown.getPosition().y + moveSpeed);
        }
    }
    if (abs((int)topDown.getPosition().x - destination.x - 3) < 2*moveSpeed && abs((int)topDown.getPosition().y - destination.y - 3) < 2*moveSpeed){
        hasDest = false;
    }
}

void player::addItem(item* i){
    inventory.push_back(i);
}

void player::changeSpeed(int i){
    moveSpeed = i;
}
