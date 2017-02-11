//
//  LoadingTheSpriteToMain.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 15.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "LoadingTheSpriteToMain.hpp"

void LoadingTheSpriteToMain::SetSprite() {
    LoadTexture();
    SetSpriteTexture();
    sprite.setTextureRect(sf::IntRect(x1, y1, x2, y2));
    sprite.setOrigin(abs((x2-x1)/2), abs((y2-y1)/2));
}

void LoadingTheSpriteToMain::SetNewTexture(sf::Texture &texture) {
    sprite.setTexture(texture);
}

sf::Sprite& LoadingTheSpriteToMain::GetSprite() {
    return sprite;
}

void LoadingTheSpriteToMain::DrawSprite(sf::RenderWindow &window) {
    window.draw(sprite);
}

void LoadingTheSpriteToMain::SetAngleToSomething(sf::Vector2f positionOfSomething) {
    float angle;
    angle=atan2f((positionOfSomething.y-sprite.getPosition().y),(positionOfSomething.x-sprite.getPosition().x))*180/PI;
    sprite.setRotation(angle);
}

void LoadingTheSpriteToMain::SetOriginOfEntity(int x, int y) {
    sprite.setOrigin(abs(((x2-x1)/2)+x), abs(((y2-y1)/2)+y));
}

bool LoadingTheSpriteToMain::OnCollisionWithObject(sf::FloatRect object) {
    sf::FloatRect currentObjectBounds;
    currentObjectBounds=sprite.getGlobalBounds();
    if(currentObjectBounds.intersects(object)) {
        return true;
    }
    else {
        return false;
    }
}

void LoadingTheSpriteToMain::SetColor(sf::Color color) {
    sprite.setColor(color);
}

sf::FloatRect LoadingTheSpriteToMain::GetGlobalBound() {
    return sprite.getGlobalBounds();
}

sf::Texture& LoadingTheSpriteToMain::GetTexture() {
    return texture;
}

void LoadingTheSpriteToMain::LoadTexture() {
    if(!texture.loadFromFile(resourcePath()+nameOfTheSprite)) {
        cout << "LoadProblem" << endl;
        return EXIT_FAILURE;
    }
}

void LoadingTheSpriteToMain::SetSpriteTexture() {
    sprite.setTexture(texture);
}

sf::Vector2f LoadingTheSpriteToMain::GetSizeOfSprite() {
    return sf::Vector2f(x2-x1, y2-y1);
}

sf::Vector2f LoadingTheSpriteToMain::GetCurrentPosition() {
    return sprite.getPosition();
}