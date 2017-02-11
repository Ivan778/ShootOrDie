//
//  GameOverStatistics.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 24.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef GameOverStatistics_hpp
#define GameOverStatistics_hpp

#include "ScreenBase.hpp"

class GameOverStatistics:public ScreenBase {
private:
    sf::View mainCamera;
    
    sf::Texture texture;
    sf::Sprite background;
    sf::Text play;
    sf::Text info;
    sf::Text exit;
    sf::Text gameName;
public:
    GameOverStatistics();
    virtual int Run(sf::RenderWindow &App);
};

#endif /* GameOverStatistics_hpp */
