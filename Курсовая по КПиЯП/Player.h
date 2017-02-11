//
//  Player.h
//  Курсовая по КПиЯП
//
//  Created by Иван on 11.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

class Player {
private:
    sf::Texture texturePlayer;
    sf::Sprite spritePlayer;
public:
    void loadTexture(char path[]) {
        if (!texturePlayer.loadFromFile(resourcePath() + path)) {
            return EXIT_FAILURE;
        }
    }
};

#endif /* Player_h */
