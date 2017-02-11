//
//  IndicatorBase.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 17.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "IndicatorBase.hpp"

IndicatorBase::IndicatorBase(int indicator, const char name[], int X1, int Y1, int X2, int Y2, sf::Font &font, int size, float scale=1):
indicatorImage(name, X1, Y1, X2, Y2) {
    this->indicator=static_cast<float>(indicator);
    maxIndicator=indicator;
    
    textIndicator.setFont(font);
    textIndicator.setCharacterSize(size);
    textIndicator.setFillColor(sf::Color::White);
    UpdateText();
    
    indicatorImage.SetSprite();
    indicatorImage.GetSprite().setScale(scale, scale);
    
    zeroAmount=false;
}

void IndicatorBase::UpdateText() {
    textIndicator.setString(to_string(int(indicator)));
}

void IndicatorBase::ShowIndicator(sf::RenderWindow &window, sf::Vector2f centerOfTheScreen, int windowX, int windowY, int offsetX, int offsetY, int distance, int height=0) {
    int x=centerOfTheScreen.x-(windowX/2)+offsetX, y=centerOfTheScreen.y-(windowY/2)+offsetY;
    
    indicatorImage.GetSprite().setPosition(x, y);
    indicatorImage.DrawSprite(window);
    
    textIndicator.setPosition(x-distance, y+height);
    window.draw(textIndicator);
}

void IndicatorBase::IncreaseIndicator(float add) {
    indicator+=add;
    UpdateText();
}

void IndicatorBase::DecreaseIndicator(float add) {
    indicator-=add;
    if(indicator<=0) {
        zeroAmount=true;
        textIndicator.setString("You've been killed!");
        return;
    }
    UpdateText();
}

bool IndicatorBase::CheckIndicator() {
    return zeroAmount;
}

void IndicatorBase::IncreaseIndicatorBorder(float add) {
    indicator+=add;
    if(indicator>=maxIndicator) {
        indicator=float(maxIndicator);
    }
    UpdateText();
}

int IndicatorBase::ReturnIndicator() {
    return int(indicator);
}

void IndicatorBase::SetIndicator(float newValue) {
    indicator=newValue;
    UpdateText();
}
