//
//  LightEffect.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 11.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef LightEffect_hpp
#define LightEffect_hpp

#include <stdio.h>
#include "LoadingTheSpriteToMain.hpp"

class LightEffect: public LoadingTheSpriteToMain {
private:
    int windowX, windowY;
protected:
    void SetLightUpToWindow(int windowX, int windowY);
public:
    LightEffect(const char name[], int X1, int Y1, int X2, int Y2, int windowX, int windowY): LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {
        SetSprite();
        this->windowX=windowX;
        this->windowY=windowY;
        SetLightUpToWindow(windowX, windowY);
    }
    ~LightEffect() { /*cout << "LightEffect destruction!" << endl;*/ }
    void SetPositionToPlayer(sf::Vector2f playerPosition, int mapX, int mapY);
    sf::Vector2f GetPosition();
};

#endif /* LightEffect_hpp */
