//
//  IndicatorBase.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 17.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef IndicatorBase_hpp
#define IndicatorBase_hpp

#include <LoadingTheSpriteToMain.hpp>

class IndicatorBase {
protected:
    sf::Text textIndicator;
    float indicator;
    int maxIndicator;
    LoadingTheSpriteToMain indicatorImage;
    bool zeroAmount;
protected:
    void UpdateText();
public:
    IndicatorBase(int indicator, const char name[], int X1, int Y1, int X2, int Y2, sf::Font &font, int size, float scale);
    ~IndicatorBase() { /*cout << "IndicatorBase destruction!" << endl;*/ }
    
    void IncreaseIndicator(float add);
    void DecreaseIndicator(float add);
    void ShowIndicator(sf::RenderWindow &window, sf::Vector2f centerOfTheScreen, int windowX, int windowY, int offsetX, int offsetY, int distance, int height);
    bool CheckIndicator();
    void IncreaseIndicatorBorder(float add);
    int ReturnIndicator();
    void SetIndicator(float newValue);
};

#endif /* IndicatorBase_hpp */
