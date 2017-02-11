//
//  Player.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 16.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Player.hpp"
#include "LoadingTheSpriteToMain.hpp"

sf::Vector2f Player::GetCurrentPosition() {
    return GetSprite().getPosition();
}

void Player::SetMovementAndWalls(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, int mapX, int mapY, int offset) {
    
    if(sf::Keyboard::isKeyPressed(up)) {
        if(GetCurrentPosition().y>offset) {
            GetSprite().move(0, -moveSpeed);                //Двигаемся вверх
        }
    }
    if(sf::Keyboard::isKeyPressed(down)) {
        if(GetCurrentPosition().y<mapY-offset) {
            GetSprite().move(0, moveSpeed);                 //Двигаемся вниз
        }
    }
    if(sf::Keyboard::isKeyPressed(left)) {
        if(GetCurrentPosition().x>offset) {
            GetSprite().move(-moveSpeed, 0);                //Двигаемся влево
        }
    }
    if(sf::Keyboard::isKeyPressed(right)) {
        if(GetCurrentPosition().x<mapX-offset) {
            GetSprite().move(moveSpeed, 0);                 //Двигаемся вправо
        }
    }
}

void Player::Mode3() {
    SetNewTexture(t3);
    gunMode=3;
}

void Player::Mode2() {
    SetNewTexture(t2);
    gunMode=2;
}

void Player::Mode1() {
    SetNewTexture(t1);
    gunMode=1;
}

int Player::GunMode() {
    return gunMode;
}
