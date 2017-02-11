//
//  Gunsight.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 07.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Gunsight_hpp
#define Gunsight_hpp

#include <stdio.h>
#include "LoadingTheSpriteToMain.hpp"

class Gunsight: public LoadingTheSpriteToMain {
private:
    sf::Vector2i mousePosition;
public:
    Gunsight(const char name[], int X1, int Y1, int X2, int Y2): LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {
        SetSprite();
    }
    ~Gunsight() { /*cout << "Gunsight destruction!" << endl;*/ }
    void SetPositionToMouse(sf::Vector2i mousePosition);
};

#endif /* Gunsight_hpp */
