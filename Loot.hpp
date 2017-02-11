//
//  Loot.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Loot_hpp
#define Loot_hpp

#include "LoadingTheSpriteToMain.hpp"

class Loot: public LoadingTheSpriteToMain {
private:
    int add;
public:
    Loot(int add, const char name[], int X1, int Y1, int X2, int Y2);
    ~Loot() { /*cout << "Loot destruction!" << endl;*/ }
    int returnAdd();
};

#endif /* Loot_hpp */
