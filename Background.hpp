//
//  Background.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 09.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Background_hpp
#define Background_hpp

#include "LoadingTheSpriteToMain.hpp"

class Background: public LoadingTheSpriteToMain {
private:
    sf::IntRect rectangle;
public:
    Background(const char name[], int X1, int Y1, int X2, int Y2): LoadingTheSpriteToMain(name, X1, Y1, X2, Y2) {  }
    ~Background() { /*cout << "Background destruction!" << endl;*/ }
    void SetMap(sf::IntRect rectangle);
    void SetBackground();
protected:
    void SetTextureB();
    void SetSpriteB();
};

#endif /* Background_hpp */
