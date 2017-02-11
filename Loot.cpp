//
//  Loot.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Loot.hpp"

Loot::Loot(int add, const char name[], int X1, int Y1, int X2, int Y2): LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {
    SetSprite();
    this->add=add;
}

int Loot::returnAdd() {
    return add;
}