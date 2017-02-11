//
//  LightEffect.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 11.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "LightEffect.hpp"

void LightEffect::SetLightUpToWindow(int windowX, int windowY) {
    double xScale, yScale;
    xScale=windowX/GetSizeOfSprite().x;
    yScale=windowY/GetSizeOfSprite().y;
    GetSprite().setScale(xScale, yScale);
}

void LightEffect::SetPositionToPlayer(sf::Vector2f playerPosition, int mapX, int mapY) {
    
    if(playerPosition.x<windowX/2)
        playerPosition.x=windowX/2;
    if(playerPosition.y<windowY/2)
        playerPosition.y=windowY/2;
    
    if(playerPosition.x>mapX-windowX/2)
        playerPosition.x=mapX-windowX/2;
    if(playerPosition.y>mapY-windowY/2)
        playerPosition.y=mapY-windowY/2;
    
    GetSprite().setPosition(playerPosition);
}

sf::Vector2f LightEffect::GetPosition() {
    return  sprite.getPosition();
}
