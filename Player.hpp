//
//  Player.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 16.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "LoadingTheSpriteToMain.hpp"
using namespace sf;

class Player: public LoadingTheSpriteToMain {
private:
    float moveSpeed;
    sf::Texture t1, t2, t3;
    char name[20], name1[20], name2[20];
    int gunMode;
public:
    Player(const char name[], int X1, int Y1, int X2, int Y2, float speed, const char name1[], const char name2[]) :
    LoadingTheSpriteToMain(name, X1, Y1, X2, Y2), moveSpeed(speed) {
        gunMode=1;
        strcpy(this->name, name);
        strcpy(this->name1, name1);
        strcpy(this->name2, name2);
        if(!t1.loadFromFile(resourcePath()+name)) {
            cout << "Player texture t1 problem!" << endl;
            return EXIT_FAILURE;
        }
        if(!t2.loadFromFile(resourcePath()+name1)) {
            cout << "Player texture t2 problem!" << endl;
            return EXIT_FAILURE;
        }
        if(!t3.loadFromFile(resourcePath()+name2)) {
            cout << "Player texture t3 problem!" << endl;
            return EXIT_FAILURE;
        }
        SetSprite();
    }
    ~Player() {}
    Vector2f GetCurrentPosition();
    void SetMovementAndWalls(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, int mapX, int mapY, int offset);
    void Mode3();
    void Mode2();
    void Mode1();
    int GunMode();
};

#endif /* Player_hpp */
