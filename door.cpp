#include <iostream>
#include "door.h"

using namespace std;

door::door(int a, char pos, point origin){
    type = a;
    bg = sf::RectangleShape(sf::Vector2f(50, 75));
    bg.setOrigin(25,(75/2));
    if (type == 0){
        if (!texture.loadFromFile("Textures/doorOpen00.png"))
            cerr << "File doorOpen00.png load error\n";
        description = "\nYou enter the open passage.\n\n";
        isLocked = false;
    }
    if (type == 1){
        if (!texture.loadFromFile("Textures/doorLocked00.png"))
            cerr << "File doorLocked00.png load error\n";
        description = "\nA locked door bearing a white\nsun blocks your path.\n";
        isLocked = true;
    }
    if (type == 2){
        if (!texture.loadFromFile("Textures/doorLocked01.png"))
            cerr << "File doorLocked01.png load error\n";
        description = "\nA locked door bearing a golden\nscorpion blocks your path.\n";
        isLocked = true;
    }
    if (type == 3){
        if (!texture.loadFromFile("Textures/doorLocked02.png"))
            cerr << "File doorLocked02.png load error\n";
        description = "\nA locked door bearing an azure\nhorse blocks your path.\n";
        isLocked = true;
    }
    if (type == 4){
        if (!texture.loadFromFile("Textures/doorLocked03.png"))
            cerr << "File doorLocked03.png load error\n";
        description = "\nYou sense an evil presence\nbinding this door shut.\n";
        bgDemon = sf::RectangleShape(sf::Vector2f(225, 255));
        bgDemon.setOrigin(112,112);
        if (!demonGlow.loadFromFile("Textures/demonGlow.png"))
            cerr << "File demonGlow.png load error\n";
        demonGlow.setSmooth(true);
        bgDemon.setTexture(&demonGlow, false);
        bgDemon.setPosition(288+350,45);
        glowAlpha = 125;
        glowIsInc = false;
        bgDemon.setFillColor(sf::Color(255,255,255,glowAlpha));
        isLocked = true;
    }
    texture.setSmooth(true);
    bg.setTexture(&texture, false);
    if (pos == 'n'){
        bg.setPosition(290 + 350, 45);
        location.x = 290 + 350;
        location.y = 45;
        connectedTo.x = origin.x;
        connectedTo.y = origin.y - 1;
    }
    if (pos == 's'){
        bg.setPosition(290 + 350, 675);
        location.x = 290 + 350;
        location.y = 675;
        bg.rotate(180);
        bg.setFillColor(sf::Color(200,200,200,255));
        connectedTo.x = origin.x;
        connectedTo.y = origin.y + 1;
    }
    if (pos == 'w'){
        bg.setPosition(325, 10 + 350);
        location.x = 325;
        location.y = 10 + 350;
        bg.rotate(270);
        connectedTo.x = origin.x - 1;
        connectedTo.y = origin.y;
    }
    if (pos == 'e'){
        bg.setPosition(955, 10 + 350);
        location.x = 955;
        location.y = 10 + 350;
        bg.rotate(90);
        bg.setFillColor(sf::Color(200,200,200,255));
        connectedTo.x = origin.x + 1;
        connectedTo.y = origin.y;
    }
}

bool door::unlock(int key){
    if (type == key){
        isLocked = false;
        type = 0;
        if (!texture.loadFromFile("Textures/doorOpen00.png"))
            cerr << "File doorOpen00.png load error\n";
        bg.setTexture(&texture, false);
        description = "\nYou enter the open passage.\n\n";
        return (true);
    }
    else
        return (false);

}

point door::getLocation(){
    return (location);
}

point door::getDoorDest(){
    return(connectedTo);
}

int door::getType(){
    return (type);
}

void door::updateAnim(int time){
    if (glowIsInc == false) glowAlpha--;
    if (glowAlpha < 75) glowIsInc = true;
    if (glowIsInc == true) glowAlpha++;
    if (glowAlpha > 125) glowIsInc = false;
    bgDemon.setFillColor(sf::Color(255,255,255,glowAlpha));
}
