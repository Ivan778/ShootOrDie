//
//  MenuScreen.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 28.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef MenuScreen_hpp
#define MenuScreen_hpp

#include "ResourcePath.hpp"
#include <iostream>
#include "ScreenBase.hpp"
#include "Wallpaper.hpp"

class MenuScreen: public ScreenBase {
private:
    sf::View mainCamera;
    
    sf::Text play;
    sf::Text info;
    sf::Text exit;
    sf::Text gameName;
    
    Wallpaper wallpaper;
public:
    MenuScreen();
    ~MenuScreen() {  }
    virtual int Run(sf::RenderWindow &App);
};

#endif /* MenuScreen_hpp */
