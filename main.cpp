#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <string>

#include "board.h"
#include "player.h"
#include "event.h"
#include "enemy.h"

#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    bool devMode = false;

    stringstream ss;
    srand( (time(NULL)));

    // Anti-aliasing Set
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    // Init Window
    int windowX = 1280;
    int windowY = 720;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "The Vault", sf::Style::Default, settings);
    //window.setFramerateLimit(61);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    // Lost focus overlay
    sf::RectangleShape overlay(sf::Vector2f(windowX,windowY));
    overlay.setPosition(0,0);
    overlay.setFillColor(sf::Color(0,0,0,175));

    // Foreground fade
    sf::RectangleShape fgFade(sf::Vector2f(windowX,windowY));
    fgFade.setPosition(0,0);
    int fgFadeAlpha = 255;
    fgFade.setFillColor(sf::Color(0,0,0,fgFadeAlpha));

    // Frames

    // mapMain
    int mapX = 270;
    int mapY = 270;
    sf::RectangleShape mapBG(sf::Vector2f(mapX,mapY));
    mapBG.setPosition(windowX - mapX - 10, 10);
    mapBG.setFillColor(sf::Color(150,150,150,255));

    // Logo
    sf::RectangleShape logoBG(sf::Vector2f(mapX,mapY));
    logoBG.setPosition(10,10);
    logoBG.setFillColor(sf::Color(255,255,255,75));
    sf::Texture logo;
    if (!logo.loadFromFile("Textures/VaultLogo.png"))
        cerr << "File eventLog.png load error\n";
    logo.setSmooth(true);
    logoBG.setTexture(&logo, false);

    // Status
    int statusX = 270;
    int statusY = 420;
    sf::RectangleShape statusBG(sf::Vector2f(statusX,statusY));
    statusBG.setPosition(windowX - statusX - 10, mapY + 20);
    statusBG.setFillColor(sf::Color(255,255,255,255));
    sf::Texture statusTexture;
    if (!statusTexture.loadFromFile("Textures/statusBG.png"))
        cerr << "File eventLog.png load error\n";
    statusTexture.setSmooth(true);
    statusBG.setTexture(&statusTexture, false);

    // Text box
    int textX = 270;
    int textY = 420;
    sf::RectangleShape textBG(sf::Vector2f(textX,textY));
    textBG.setPosition(10, mapY + 20);
    textBG.setFillColor(sf::Color(255,255,255,255));
    sf::Texture eventTexture;
    if (!eventTexture.loadFromFile("Textures/eventLog.png"))
        cerr << "File eventLog.png load error\n";
    eventTexture.setSmooth(true);
    textBG.setTexture(&eventTexture, false);
    sf::RectangleShape textBGbottom(sf::Vector2f(textX,textY));
    textBGbottom.setPosition(10, mapY + 20);
    textBGbottom.setFillColor(sf::Color(255,255,255,255));
    sf::Texture eventTextureBottom;
    if (!eventTextureBottom.loadFromFile("Textures/eventLogBottom.png"))
        cerr << "File eventLogBottom.png load error\n";
    eventTextureBottom.setSmooth(true);
    textBGbottom.setTexture(&eventTextureBottom, false);

    // Load fonts
    sf::Font mainFont;
    if (!mainFont.loadFromFile("Fonts/TrajanPro-Bold.otf")){
        cerr << "File TrajanPro-Bold.otf load error\n";
    }
    sf::Font eventFont;
    if (!eventFont.loadFromFile("Fonts/nyala.ttf")){
        cerr << "File nyala.ttf load error\n";
    }

    // Program clock
    int32_t mytime = 0;
    bool focus = true;

    // Declare clock
    sf::Clock clock;

    int keyPressTimer = 0;
    int mouseClickTimer = 0;
    bool mouseLeft = false;
    bool keyInspect = false;
    bool keyQuit = false;
    bool introTitlePlay = false;
    bool introTitleFade = false;
    bool introTextPlay = false;
    bool endTextPlay = false;
    bool playMode = false;
    bool pausedScreen = false;
    int introTimeStart = 0;
    int endTimeStart = 0;
    int messageEasterEgg = 0;

    srand (time(NULL));

    // Game logic and input
    bool hasWon = false;

    // Set up game
    int mapSize = 3;
    int cellWidth = 700;

    board * mapMain = new board(mapSize, cellWidth);

    int health = 3;
    //int damage = 0;
    //bool enemyNear = false;
    //bool hasDied = false;

    player * P = new player(1,1,health,cellWidth);
    event * exit = new event(1,0,1);

    mapMain->updateCell(P->getCoord().x, P->getCoord().y, 1);
    mapMain->updateCell(exit->getCoord().x, exit->getCoord().y, 3);
    mapMain->updateCell(exit->getCoord().x, exit->getCoord().y, 4);
    mapMain->setEventType(exit->getCoord().x, exit->getCoord().y, 1);

    mapMain->generateDoor(1,1,'n',4);
    mapMain->generateDoor(1,1,'s',3);
    mapMain->generateDoor(1,1,'w',2);
    mapMain->generateDoor(1,1,'e',1);
    mapMain->generateDoor(1,2,'n',0);
    mapMain->generateDoor(0,1,'e',0);
    mapMain->generateDoor(2,1,'w',0);

    mapMain->generateItem(1,1,1,527,219);
    mapMain->generateItem(1,2,2,426,600);
    mapMain->generateItem(2,1,3,415,360);
    mapMain->generateItem(0,1,4,527,519);
    mapMain->generateItem(2,1,5,875,220);

    vector<enemy *> enemyList;
    //enemyList.push_back(new enemy(spawnX, spawnY, 1));
    //mapMain->updateCell(enemyList[0]->getCoord().x, enemyList[0]->getCoord().y, 2);

    //event * pitfall = new event(spawnX, spawnY, 2);
    //mapMain->updateCell(pitfall->getCoord().x, pitfall->getCoord().y, 3);

    // Set text
    sf::Text title;
    int titleAlpha = 0;
    int scrollAlpha = 255;
    title.setFont(mainFont);
    title.setString("The Vault");
    title.setCharacterSize(80);
    title.setColor(sf::Color(255,255,255,titleAlpha));
    title.setPosition(windowX/2,windowY/2);
    string temp = "You wake up and find yourself in a dimly lit room with cold stone walls.\n"
                  "You have no memory of how you arrived in this place, or who you are.\n"
                  "A sudden grip of fear overwhelms you as you realize what this place might be...\n\n"
                  "Your only thoughts are of escape.\n\nMake your move.";
    int tempLen = temp.length();
    string temp2 = "";

    sf::Text paused;
    paused.setFont(mainFont);
    paused.setString("Paused");
    paused.setCharacterSize(80);
    paused.setColor(sf::Color(255,255,255,255));
    paused.setPosition(windowX/2-155,windowY/2-70);
    sf::Text pausedInfo;
    pausedInfo.setFont(mainFont);
    pausedInfo.setString("'Q' to Quit");
    pausedInfo.setCharacterSize(40);
    pausedInfo.setColor(sf::Color(255,255,255,255));
    pausedInfo.setPosition(windowX/2-150,windowY/2+30);

    int menuAlpha = 0;

    sf::Text startMenu_start;
    startMenu_start.setFont(mainFont);
    startMenu_start.setString("Start");
    startMenu_start.setCharacterSize(50);
    startMenu_start.setColor(sf::Color(255,255,255,menuAlpha));
    startMenu_start.setPosition(windowX/2+60,windowY/2+60);

    /*
    sf::Text startMenu_credits;
    startMenu_credits.setFont(mainFont);
    startMenu_credits.setString("Credits");
    startMenu_credits.setCharacterSize(50);
    startMenu_credits.setColor(sf::Color(255,255,255,menuAlpha));
    startMenu_credits.setPosition(windowX/2,windowY/2-60);
    */

    sf::Text startMenu_exit;
    startMenu_exit.setFont(mainFont);
    startMenu_exit.setString("Exit");
    startMenu_exit.setCharacterSize(50);
    startMenu_exit.setColor(sf::Color(255,255,255,menuAlpha));
    startMenu_exit.setPosition(windowX/2+60,windowY/2+120);

    // Menu Logo
    sf::RectangleShape startMenuLogoBG(sf::Vector2f(500,500));
    startMenuLogoBG.setPosition(100,50);
    startMenuLogoBG.setFillColor(sf::Color(255,255,255,menuAlpha));
    startMenuLogoBG.setTexture(&logo, false);

    // Read Me Info
    sf::Text readMe;
    readMe.setFont(eventFont);
    readMe.setString("Thank you for testing my game.\nIt's still in an early phase without\n"
                     "some of the features (puzzles, items, etc.)\nI'd greatly appreciate any comments\nor questions.\n\n"
                     "Thanks! - Kenji Johnson\n\n\n"
                     "Controls:\nMouse Left Click to Move\n\n'E' to Inspect\n\n'Esc' to Pause or Quit"
                     "\n\nAlso, make sure window is in focus\n"
                     "for key presses to work.");

    readMe.setCharacterSize(18);
    readMe.setPosition(windowX/2+300,windowY/2-300);

    sf::Text eventLog;
    string eventString = "";
    eventLog.setFont(eventFont);
    eventLog.setString(eventString);
    eventLog.setCharacterSize(16);
    eventLog.setColor(sf::Color(0,0,0,255));
    eventLog.setPosition(60, mapY + 60);

    // Dev settings
    if (devMode == true){
        introTitlePlay = true;
        introTextPlay = true;
        endTextPlay = true;
        playMode = true;
        //P->changeSpeed(6);
    }

	// Start the game loop
    while (window.isOpen())
    {
        windowX = window.getSize().x;
        windowY = window.getSize().y;

        // Update clock
        if (focus == true){
            mytime++;
        }

        if (keyPressTimer >= 1)
            keyPressTimer++;
        if (keyPressTimer > 10){
            keyPressTimer = 0;
            keyInspect = false;
            keyQuit = false;
        }

        if (mouseClickTimer >= 1)
            mouseClickTimer++;
        if (mouseClickTimer > 15){
            mouseClickTimer = 0;
            mouseLeft = false;
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    cout << "Closing program...\n";
                    window.close();
                    break;

                case sf::Event::LostFocus:
                    //cout << "\nPausing\n";
                    //focus = false;
                    break;

                case sf::Event::GainedFocus:
                    //cout << "Resuming\n\n";
                    //focus = true;
                    break;

                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape){
                        //cout << "Closing program...\n";
                        //window.close();
                        if (pausedScreen == false && playMode == true) pausedScreen = true;
                        else pausedScreen = false;
                        if (playMode == false) window.close();
                    }
                    if(event.key.code == sf::Keyboard::E){
                        keyPressTimer = 1;
                        keyInspect = true;
                    }
                    if(event.key.code == sf::Keyboard::Q){
                        keyPressTimer = 1;
                        keyQuit = true;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left && mouseClickTimer == 0){
                        mouseClickTimer = 1;
                        mouseLeft = true;
                    }
                    break;

                default:
                    break;
            }
        }

        // Clear screen
        if (hasWon == false)
            window.clear(sf::Color(0,0,0,255));
        else
            window.clear(sf::Color(255,255,255,255));

        // Title Sequence
        if (introTitlePlay == false && mytime > 60){
            if (titleAlpha < 255 && introTitleFade == false) titleAlpha++;
            if (mytime > 200) introTitleFade = true;
            if (titleAlpha > 0 && introTitleFade == true) titleAlpha--;
            title.setColor(sf::Color(255,255,255,titleAlpha));
            window.draw(title);
            if (mytime > 400){
                introTitlePlay = true;
                titleAlpha = 255;
            }
        }
        // End Title Sequence

        // Start Screen
        if (introTitlePlay == true && playMode == false){
            if (menuAlpha < 255) menuAlpha++;
            startMenu_start.setColor(sf::Color(255,255,255,menuAlpha));
            //startMenu_credits.setColor(sf::Color(255,255,255,menuAlpha));
            startMenu_exit.setColor(sf::Color(255,255,255,menuAlpha));
            startMenuLogoBG.setFillColor(sf::Color(255,255,255,menuAlpha));
            readMe.setColor(sf::Color(255,255,255,menuAlpha));
            window.draw(startMenu_start);
            //window.draw(startMenu_credits);
            window.draw(startMenu_exit);
            window.draw(startMenuLogoBG);
            window.draw(readMe);

            if (mouseClickTimer == 1 && mouseLeft == true){
                printf("Mouse X: %d   Mouse Y: %d\n",sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                if (sf::Mouse::getPosition(window).x > 705 && sf::Mouse::getPosition(window).y > 434 &&
                    sf::Mouse::getPosition(window).x < 857 && sf::Mouse::getPosition(window).y < 467){
                    playMode = true;
                    introTimeStart = mytime;
                    }
                if (sf::Mouse::getPosition(window).x > 702 && sf::Mouse::getPosition(window).y > 492 &&
                    sf::Mouse::getPosition(window).x < 815 && sf::Mouse::getPosition(window).y < 530)
                    window.close();
            }
        }

        // Play Mode
        int scrollSpeed = 3;

        if (playMode == true && introTextPlay == false){
            sf::Text scrolling;
            scrolling.setFont(mainFont);
            if (mytime % scrollSpeed == 1 && temp.length() > 0){
                string temp3;
                ss << temp[0];
                ss >> temp3;
                temp3 = temp[0];
                temp2.append(temp3);
                temp.erase(0,1);
            }
            scrolling.setString(temp2);
            scrolling.setCharacterSize(18);
            if (mytime > introTimeStart + scrollSpeed*(tempLen+10)) scrollAlpha--;
            else if (scrollAlpha < 1) scrollAlpha = 0;
            scrolling.setColor(sf::Color(255,255,255,scrollAlpha));
            scrolling.setPosition(250,180);
            window.draw(scrolling);
            if (mytime > introTimeStart + scrollSpeed*(tempLen) + 280){
                introTextPlay = true;
            }
        }

        if (introTextPlay == true && playMode == true && hasWon == false){
            // Main Display
            point currentPLoc;
            currentPLoc.x = P->getCoord().x;
            currentPLoc.y = P->getCoord().y;
            // Draw main room
            window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->bg);
            window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->bgTorch);
            mapMain->array2d[currentPLoc.x][currentPLoc.y]->updateAnim(mytime);
            // Draw items
            for (int i = 0; i < (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents.size(); i++){
                if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->onMap){
                    // Move key 4 randomly
                    if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getType() == 4){
                        if (mytime % 120 == 1){
                            int randX = rand() % 470 + 400;
                            int randY = rand() % 470 + 120;
                            mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->setLocation(randX, randY);
                        }
                    }
                    // Set alpha for keys 2, 3 based on player pos
                    if ((mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getType() == 3 ||
                         mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getType() == 2) && P->hasTorch){
                        int keyAlpha = 255-(abs((int)P->topDown.getPosition().x - (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getLocation().x) +
                                            abs((int)P->topDown.getPosition().y - (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getLocation().y));
                        if (keyAlpha < 1) keyAlpha = 1;
                        mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->bgFloor.setFillColor(sf::Color(255,255,255,keyAlpha));
                    }
                    window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->bgFloor);
                    // Update glow for torch
                    if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getType() == 5){
                        window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->bgGlow);
                        mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->updateAnim(mytime);
                    }
                }
            }

            // Draw doors
            for (int i = 0; i < (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits.size(); i++){
                window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->bg);
                if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->getType() == 4){
                    window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->bgDemon);
                    mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->updateAnim(mytime);
                }
            }

            // Player move input
            if (mouseClickTimer == 1 && mouseLeft == true && pausedScreen == false){
                printf("Mouse X: %d   Mouse Y: %d\n",sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                point playerLoc = P->getCoord();
                if (sf::Mouse::getPosition(window).x > mapMain->array2d[playerLoc.x][playerLoc.y]->nw.x + 75 &&
                    sf::Mouse::getPosition(window).x < mapMain->array2d[playerLoc.x][playerLoc.y]->se.x - 80 &&
                    sf::Mouse::getPosition(window).y > mapMain->array2d[playerLoc.x][playerLoc.y]->nw.y + 75 &&
                    sf::Mouse::getPosition(window).y < mapMain->array2d[playerLoc.x][playerLoc.y]->se.y - 75)
                        P->setDest(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }

            // Update player position
            P->update(mytime);
            // Draw player sprite
            window.draw(P->topDown);
            if (P->hasTorch){
                P->torch->bgGlow.setPosition(P->topDown.getPosition().x + 10,P->topDown.getPosition().y - 10);
                window.draw(P->torch->bgGlow);
                P->torch->updateAnim(mytime);
            }

            // Lighting
            window.draw(mapMain->array2d[currentPLoc.x][currentPLoc.y]->bgGlow);

            point playerPos;
            playerPos.x = P->topDown.getPosition().x;
            playerPos.y = P->topDown.getPosition().y;

            // Interaction
            if (keyPressTimer == 1 && keyInspect == true && pausedScreen == false){
                bool madeStatement = false;
                // Door
                bool attemptedOpen = false;
                bool hasKey = false;
                for (int i = 0; i < (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits.size(); i++){
                    point exitLoc = mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->getLocation();
                    if (abs(playerPos.x - exitLoc.x) < 75 && abs(playerPos.y - exitLoc.y) < 75){
                        if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->isLocked){
                            for (int j = 0; j < (int)P->inventory.size(); j++){
                                attemptedOpen = true;
                                int itemType = P->inventory[j]->getType();
                                if (!hasKey) hasKey = mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->unlock(itemType);
                            }
                            if (hasKey) eventString.insert(0, "\nThe door unlocks with a\nsatisfying click.\n");
                            madeStatement = true;
                            messageEasterEgg = 0;
                        }
                        else{
                            point newRoom = mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->getDoorDest();
                            mapMain->updateCell(P->getCoord().x, P->getCoord().y, 5);
                            point oldRoom = P->getCoord();
                            P->setCoord(newRoom);
                            mapMain->updateCell(P->getCoord().x, P->getCoord().y, 1);
                            if (oldRoom.x - newRoom.x > 0) P->topDown.setPosition(playerPos.x + 520, playerPos.y);
                            if (oldRoom.x - newRoom.x < 0) P->topDown.setPosition(playerPos.x - 520, playerPos.y);
                            if (oldRoom.y - newRoom.y > 0) P->topDown.setPosition(playerPos.x, playerPos.y + 530);
                            if (oldRoom.y - newRoom.y < 0) P->topDown.setPosition(playerPos.x, playerPos.y - 530);
                            fgFadeAlpha = 255;
                        }
                        int doorType = mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->getType();
                        if (doorType !=0 && attemptedOpen) eventString.insert(0, mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->description);
                        if (!hasKey && attemptedOpen) eventString.insert(0, "\nYou do not have the right key.\n\n");
                        if (!attemptedOpen && doorType == 0) eventString.insert(0, mapMain->array2d[currentPLoc.x][currentPLoc.y]->exits[i]->description);
                        madeStatement = true;
                        messageEasterEgg = 0;
                    }
                }
                // Items
                int itemPickupDist = 40;
                for (int i = 0; i < (int)mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents.size(); i++){
                    point itemLoc = mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->getLocation();
                    if (abs(playerPos.x - itemLoc.x) < itemPickupDist && abs(playerPos.y - itemLoc.y) < itemPickupDist){
                        if (mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->canPickUp){
                            mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i]->pickUp();
                            item* recievedItem = mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents[i];
                            P->addItem(recievedItem);
                            if (recievedItem->getType() == 5){
                                    P->hasTorch = true;
                                    P->torch = recievedItem;
                            }
                            mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents.erase(mapMain->array2d[currentPLoc.x][currentPLoc.y]->contents.begin()+i);
                            eventString.insert(0, recievedItem->description);
                            madeStatement = true;
                            messageEasterEgg = 0;
                        }
                    }
                }
                // Torches
                int interactionDist = 50;
                if (currentPLoc.x == 2 && currentPLoc.y == 1){
                    if((abs(playerPos.x - 502) < interactionDist && abs(playerPos.y - 66) < interactionDist) ||
                       (abs(playerPos.x - 777) < interactionDist && abs(playerPos.y - 66) < interactionDist) ||
                       (abs(playerPos.x - 935) < interactionDist && abs(playerPos.y - 498) < interactionDist) ||
                       (abs(playerPos.x - 777) < interactionDist && abs(playerPos.y - 656) < interactionDist) ||
                       (abs(playerPos.x - 502) < interactionDist && abs(playerPos.y - 656) < interactionDist) ||
                       (abs(playerPos.x - 344) < interactionDist && abs(playerPos.y - 498) < interactionDist) ||
                       (abs(playerPos.x - 344) < interactionDist && abs(playerPos.y - 223) < interactionDist)){
                            eventString.insert(0, "\nThe warmly glowing torch is\nfirmly bolted to the stone wall.\n");
                            madeStatement = true;
                       }
                }
                else{
                    if((abs(playerPos.x - 502) < interactionDist && abs(playerPos.y - 66) < interactionDist) ||
                       (abs(playerPos.x - 777) < interactionDist && abs(playerPos.y - 66) < interactionDist) ||
                       (abs(playerPos.x - 935) < interactionDist && abs(playerPos.y - 223) < interactionDist) ||
                       (abs(playerPos.x - 935) < interactionDist && abs(playerPos.y - 498) < interactionDist) ||
                       (abs(playerPos.x - 777) < interactionDist && abs(playerPos.y - 656) < interactionDist) ||
                       (abs(playerPos.x - 502) < interactionDist && abs(playerPos.y - 656) < interactionDist) ||
                       (abs(playerPos.x - 344) < interactionDist && abs(playerPos.y - 498) < interactionDist) ||
                       (abs(playerPos.x - 344) < interactionDist && abs(playerPos.y - 223) < interactionDist)){
                            eventString.insert(0, "\nThe warmly glowing torch is\nfirmly bolted to the stone wall.\n");
                            madeStatement = true;
                            messageEasterEgg = 0;
                    }
                }
                if (madeStatement == false){
                    int messageChoice = rand() % 3;
                    messageEasterEgg++;
                    if (messageEasterEgg == 7){
                        if (messageChoice == 0) eventString.insert(0, "\nYou're top tier NA at this.\n(I can tell).\n");
                        if (messageChoice == 1) eventString.insert(0, "\nThose confines are really\ngetting to you, chill bro.\n");
                        if (messageChoice == 2) eventString.insert(0, "\nBetter drink your own piss.\n\n");
                        messageEasterEgg = 0;
                    }
                    else{
                        if (messageChoice == 0) eventString.insert(0, "\nYou see utterly nothing of\nsignificance.\n");
                        if (messageChoice == 1) eventString.insert(0, "\nThe dark confines of these\nwalls are slowly getting to you.\n");
                        if (messageChoice == 2) eventString.insert(0, "\nI need water.\n\n");
                    }
                }
            }

            // Display minimap (upper right)
            window.draw(mapBG);
            mapMain->miniMapUpdate();
            for (int i = 0; i < mapSize; i++){
                for (int j = 0; j < mapSize; j++){
                    if (mapMain->array2d[i][j]->isRevealed)
                        window.draw(mapMain->array2d[i][j]->bgMini);
                }
            }
            // Display Status (right)
            window.draw(statusBG);
            for (int i = 0; i < (int)P->inventory.size(); i++){
                if (P->inventory[i]->pickedUp) window.draw(P->inventory[i]->bgInven);
            }
            // Display Event Log (left)
            window.draw(textBG);
            eventLog.setString(eventString);
            window.draw(eventLog);
            window.draw(textBGbottom);

            //Display Logo (upper left)
            window.draw(logoBG);

            // Screen Fader
            fgFadeAlpha--;
            fgFade.setFillColor(sf::Color(0,0,0,fgFadeAlpha));
            if (fgFadeAlpha > 1)
                window.draw(fgFade);

            if (P->getCoord().x == exit->getCoord().x && P->getCoord().y == exit->getCoord().y){
                hasWon = true;
                temp = "The open vault door reveals a winding staircase thrusting seemingly forever upwards.\n"
                       "With only one option left, you venture upwards into the darkness.\n"
                       "You emerge into a vast room with a seemingly limitless expanse.\n"
                       "It starts as a flicker, but quickly transforms into a blaze...\n"
                       "\nAs you gaze upon what now stands before you...\n\n"
                       "You immediately regret your decision of rashly breaking that last seal...";
                tempLen = temp.length();
                temp2 = "";
                endTimeStart = mytime;
                scrollAlpha = 255;
            }
        }

        if (playMode == true && endTextPlay == false && hasWon == true){
            sf::Text scrolling;
            scrolling.setFont(mainFont);
            if (mytime % scrollSpeed == 1 && temp.length() > 0){
                string temp3;
                ss << temp[0];
                ss >> temp3;
                temp3 = temp[0];
                temp2.append(temp3);
                temp.erase(0,1);
            }
            scrolling.setString(temp2);
            scrolling.setCharacterSize(18);
            if (mytime > endTimeStart + scrollSpeed*(tempLen+10)) scrollAlpha--;
            else if (scrollAlpha < 1) scrollAlpha = 0;
            scrolling.setColor(sf::Color(0,0,0,scrollAlpha));
            scrolling.setPosition(250,150);
            window.draw(scrolling);
            if (mytime > endTimeStart + scrollSpeed*(tempLen) + 280){
                endTextPlay = true;
            }

            if (endTextPlay == true) window.close();
        }

        // Pause and Quit screen
        if (pausedScreen == true){
            window.draw(overlay);
            window.draw(readMe);
            window.draw(paused);
            window.draw(pausedInfo);
            if (keyPressTimer == 1 && keyQuit == true) window.close();
        }

        window.display();

    }

    if (devMode == true){
        cout << "\nClosing application time (ticks) is: " << mytime << endl;
        cout << "Closing application time (clock) is: " << clock.getElapsedTime().asSeconds() << endl;
        cout << "Ticks per second was: " << (int)mytime / clock.getElapsedTime().asSeconds() << endl;
    }

    return EXIT_SUCCESS;
}
