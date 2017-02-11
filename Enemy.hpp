//
//  Enemy.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 12.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "LoadingTheSpriteToMain.hpp"

class Enemy: public LoadingTheSpriteToMain {
private:
    float moveSpeed;
    int amountOfLifes, amountOfLifesReserve;
    bool amIKilled;
    sf::Vector2f vectorTowardsTarget;
public:
    Enemy(const char name[], int X1, int Y1, int X2, int Y2, float moveSpeed, int amountOfLifes):
    LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {
        this->moveSpeed=moveSpeed;
        this->amountOfLifes=amountOfLifes;
        amountOfLifesReserve=amountOfLifes;
        SetSprite();
        amIKilled=false;
    }
    ~Enemy() { /*cout << "Enemy destruction!" << endl;*/ }
    
    void SetSkins(sf::Texture &t, const char name[]);
    void MoveInTheDirectionOfTarget(sf::Vector2f positionOfTarget);
    sf::Vector2f ComputeVectorTowardsTarget(sf::Vector2f positionOfTarget);
    void SetSpeed(float moveSpeed);
    bool IsKilled();
    bool OnCollisionWithPlayer(sf::Vector2f playerPosition);
    void ResetLifes();
    void Damage();
};

#endif /* Enemy_hpp */
