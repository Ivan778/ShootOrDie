//
//  PauseScreen.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 01.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef PauseScreen_hpp
#define PauseScreen_hpp

#include <stdlib.h>
#include "ScreenBase.hpp"
#include "Wallpaper.hpp"

class PauseScreen: public ScreenBase {
private:
    sf::View mainCamera;
    
    sf::Text continueGame, backToMenu, restartGame;
    Wallpaper wallpaper;
public:
    PauseScreen(void);
    ~PauseScreen() {  }
    virtual int Run(sf::RenderWindow &App);
};

#endif /* PauseScreen_hpp */
