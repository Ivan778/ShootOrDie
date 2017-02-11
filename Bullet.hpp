//
//  Bullet.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 24.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "LoadingTheSpriteToMain.hpp"

class Bullet: public LoadingTheSpriteToMain {
private:
    int speed;
    sf::Vector2f direction;
    bool used;
public:
    Bullet(const char name[], int X1, int Y1, int X2, int Y2, int s):
    LoadingTheSpriteToMain(name, X1, Y1, X2, Y2), speed(s) {
        SetSprite();
        used=false;
    }
    ~Bullet() {}
    void MoveToCurrentPoint(float time);
    void SetBulletForShootToThrill(sf::Vector2f mousePosition, sf::Vector2f vector);
    void SetPosition(sf::Vector2f vector);
    bool ShouldWeEraseBullet(int mapX, int mapY);
    bool returnUsed();
    void SayUsed();
    void HideBullet();
protected:
    void SetDirection(sf::Vector2f mousePosition);
};

#endif /* Bullet_hpp */
