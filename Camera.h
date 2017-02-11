//
//  Camera.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 11.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//


#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include "ResourcePath.hpp"
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>
using namespace sf;

void GetPlayerPosition(sf::View &camera, sf::Vector2f playerPosition, int windowX, int windowY, int mapX, int mapY) {
    if(playerPosition.x<windowX/2)
        playerPosition.x=windowX/2;
    
    if(playerPosition.y<windowY/2)
        playerPosition.y=windowY/2;
    
    if(playerPosition.x>mapX-windowX/2)
        playerPosition.x=mapX-windowX/2;
    
    if(playerPosition.y>mapY-windowY/2)
        playerPosition.y=mapY-windowY/2;
    
    camera.setCenter(playerPosition);
}

