//
//  Background.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 09.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Background.hpp"

void Background::SetTextureB() {
    LoadTexture();
    GetTexture().setRepeated(true);
}

void Background::SetSpriteB() {
    SetSpriteTexture();
    GetSprite().setTextureRect(rectangle);
}

void Background::SetBackground() {
    SetTextureB();
    SetSpriteB();
}

void Background::SetMap(sf::IntRect rectangle) {
    this->rectangle=rectangle;
}