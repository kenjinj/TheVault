#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <ctime>
#include "enemy.h"

using namespace std;

enemy::enemy (int xIn, int yIn, int t){
    type = t;
    x = xIn;
    y = yIn;
    health = 0;
    justAttacked = false;
    if (type == 1) health = 2;
}

point enemy::getCoord(){
    point coord;
    coord.x = x;
    coord.y = y;

    return(coord);
}

int enemy::attack(point player){
    int damageDone = 0;
    if (health > 0){
        // If on same cell as player
        if (x == player.x && y == player.y){
            if (type == 1){
                cout << "\n * A giant bat shrieks out from the darkness and claws your face.\n";
                damageDone += 1;
            }
        }
    }
    return (damageDone);
}

int enemy::getHealth(){
    return(health);
}

void enemy::setStatus(bool attacked){
    justAttacked = attacked;
}

bool enemy::getStatus(){
    return(justAttacked);
}

void enemy::setHealth(int damage){
    health -= damage;
    if (type == 1){
        printf("\n * The giant bat reels from the hit. ");
        if (health > 0)
            printf("\n   You sense it has %d health left.\n", health);
        else
            cout << "\n   It shrieks and falls to the ground, it hath been vanquished!\n";
    }
}

point enemy::move(int size){
    srand (time(NULL));
    point coord;
    coord.x = x;
    coord.y = y;
    if (health > 0){
        // bat
        if(type == 1){
            int direction = rand() % 2;
            if (direction == 0){;
                direction = rand() % 2;
                if (direction == 0 && y > 0)
                    coord.y = y - 1;
                else if (y < size-1)
                    coord.y = y + 1;
                coord.x = x;
            }
            else{
                direction = rand() % 2;
                if (direction == 0 && x > 0)
                    coord.x = x - 1;
                else if (x < size-1)
                    coord.x = x + 1;
                coord.y = y;
            }
            cout << "\n * You hear the soft flutter of giant wings in the distance.\n";
        }
        // wumpus
        else if (type == 1){
        // dormant, does not move
        // if player 1 cell over, start to stir, send signal out
        // if plater still one cell over second turn, waken
        // if waken, move towards character
        // if character is in same cell, dies unless has some sort of CQC weapon
        };
        x = coord.x;
        y = coord.y;
    }
    return (coord);
}
