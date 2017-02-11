//
//  Wallpaper.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 06.12.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Wallpaper_hpp
#define Wallpaper_hpp

#include "LoadingTheSpriteToMain.hpp"

class Wallpaper: public LoadingTheSpriteToMain {
private:
    int windowX, windowY;
public:
    Wallpaper(const char name[], int X1, int Y1, int X2, int Y2, int windowX, int windowY): LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {
        this->windowX=windowX;
        this->windowY=windowY;
    }
    ~Wallpaper() {  }
    void SetOriginAndSetPosition();
    void SetCustomPosition(int x, int y);
};

#endif /* Wallpaper_hpp */
