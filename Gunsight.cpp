//
//  Gunsight.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 07.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Gunsight.hpp"

void Gunsight::SetPositionToMouse(sf::Vector2i mousePosition) {
    GetSprite().setPosition(mousePosition.x, mousePosition.y);
}
