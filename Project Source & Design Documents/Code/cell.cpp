#include "cell.h"

using namespace std;

cell::cell(int a, int b, int c, int d, int aMini, int bMini, int cMini, int dMini, int type){
    nw.x = a;
    nw.y = b;
    se.x = c;
    se.y = d;

    nwMini.x = aMini;
    nwMini.y = bMini;
    seMini.x = cMini;
    seMini.y = dMini;

    isEmpty = true;
    hasPlayer = false;
    hasEnemy = false;
    hasEvent = false;
    isRevealed = false;
    eventType = 0;

    bg = sf::RectangleShape(sf::Vector2f(c-a,d-b));
    bg.setFillColor(sf::Color(200,200,200,255));
    bg.setPosition(a,b);
    if (!texture.loadFromFile("Textures/cellTexture01.png"))
        cerr << "File cellTexture01.png load error\n";
    texture.setSmooth(true);
    bg.setTexture(&texture, false);

    bgTorch = sf::RectangleShape(sf::Vector2f(c-a,d-b));
    bg.setFillColor(sf::Color(255,255,255,255));
    bgTorch.setPosition(a,b);
    if (type == 1){
        if (!torch01.loadFromFile("Textures/cellTorchesRoom101.png"))
            cerr << "File cellTorchesRoom101.png load error\n";
        if (!torch02.loadFromFile("Textures/cellTorchesRoom102.png"))
            cerr << "File cellTorchesRoom102.png load error\n";
    }
    if (type == 0) {
        if (!torch01.loadFromFile("Textures/cellTorchesFull01.png"))
            cerr << "File cellTorchesFull01.png load error\n";
        if (!torch02.loadFromFile("Textures/cellTorchesFull02.png"))
            cerr << "File cellTorchesFull02.png load error\n";
    }
    torch01.setSmooth(true);
    torch02.setSmooth(true);
    bgTorch.setTexture(&torch01, false);
    whichTorch = 1;

    bgGlow = sf::RectangleShape(sf::Vector2f(c-a,d-b));
    bgGlow.setPosition(a,b);
    if (type == 1)
        if (!glow.loadFromFile("Textures/cellTorchesGlowRoom1.png"))
            cerr << "File cellTorchesGlowRoom1.png load error\n";
    if (type == 0)
        if (!glow.loadFromFile("Textures/cellTorchesGlowFull.png"))
            cerr << "File cellTorchesGlowFull.png load error\n";
    glow.setSmooth(true);
    bgGlow.setTexture(&glow, false);
    glowAlpha = 150;
    glowIsInc = false;
    bgGlow.setFillColor(sf::Color(255,255,255,glowAlpha));

    bgMini = sf::RectangleShape(sf::Vector2f(cMini-aMini,dMini-bMini));
    bgMini.setFillColor(sf::Color(200,200,200,255));
    bgMini.setPosition(aMini,bMini);
}

void cell::updateAnim(int time){
    if (glowIsInc == false) glowAlpha--;
    if (glowAlpha < 75) glowIsInc = true;
    if (glowIsInc == true) glowAlpha++;
    if (glowAlpha > 150) glowIsInc = false;
    bgGlow.setFillColor(sf::Color(255,255,255,glowAlpha));
    if (time % 15 == 1){
        if (whichTorch == 1){
            bgTorch.setTexture(&torch02, false);
            whichTorch = 2;
        }
        else {
            bgTorch.setTexture(&torch01, false);
            whichTorch = 1;
        }
    }
}
