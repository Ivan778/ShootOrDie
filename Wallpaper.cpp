//
//  Wallpaper.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 06.12.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Wallpaper.hpp"

void Wallpaper::SetOriginAndSetPosition() {
    SetSprite();
    GetSprite().setPosition(0, 0);
    
    float originX, originY;
    originX=float(windowX)/GetTexture().getSize().x;
    originY=float(windowY)/GetTexture().getSize().y;
    
    GetSprite().setOrigin(0, 0);
    GetSprite().setScale(originX, originY);
}

void Wallpaper::SetCustomPosition(int x, int y) {
    GetSprite().setPosition(x, y);
}
