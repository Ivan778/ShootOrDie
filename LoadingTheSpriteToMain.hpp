//
//  LoadingTheSpriteToMain.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 15.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef LoadingTheSpriteToMain_hpp
#define LoadingTheSpriteToMain_hpp

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
#include <ctime>
#include <fstream>

const float PI=3.14159265;

using namespace std;

class LoadingTheSpriteToMain {
private:
    sf::Texture texture;
    char nameOfTheSprite[20];
    int x1, y1, x2, y2;
protected:
    sf::Sprite sprite;
    sf::Texture& GetTexture();
    void LoadTexture();
    void SetSpriteTexture();
    sf::Vector2f GetSizeOfSprite();
public:
    LoadingTheSpriteToMain(const char name[], int X1, int Y1, int X2, int Y2) {
        x1=X1;
        x2=X2;
        y1=Y1;
        y2=Y2;
        strcpy(nameOfTheSprite, name);
    }
    ~LoadingTheSpriteToMain() {  }
    void SetColor(sf::Color color);
    void SetSprite();
    void DrawSprite(sf::RenderWindow &window);
    void SetAngleToSomething(sf::Vector2f mousePosition);
    sf::Sprite& GetSprite();
    void SetOriginOfEntity(int x, int y);
    bool OnCollisionWithObject(sf::FloatRect object);
    sf::FloatRect GetGlobalBound();
    sf::Vector2f GetCurrentPosition();
    //bool SpecialCollision(sf::Vector2f object);
    void SetNewTexture(sf::Texture &texture);
};

#endif /* LoadingTheSpriteToMain_hpp */
