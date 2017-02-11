//
//  Entity.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 11.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

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
using namespace std;

class Entity {
public:
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
    sf::Texture texture;
};

#endif /* Entity_hpp */
