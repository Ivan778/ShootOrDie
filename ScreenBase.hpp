//
//  ScreenBase.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 28.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef ScreenBase_hpp
#define ScreenBase_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ResourcePath.hpp>

class ScreenBase {
protected:
    sf::Font font;
    int windowX, windowY;
public:
    ScreenBase() {
        windowX=1500;
        windowY=1100;
        if(!font.loadFromFile(resourcePath()+"28 Days Later.ttf")) {
            return EXIT_FAILURE;
        }
    }
    virtual ~ScreenBase() {  }
    virtual int Run(sf::RenderWindow &App) = 0;
    void MouseOverButtonText(sf::FloatRect &box, sf::Vector2i mousePosition, sf::Text &text) {
        sf::Color previousColor;
        previousColor=text.getFillColor();
        if(box.contains(mousePosition.x, mousePosition.y)) {
            text.setFillColor(sf::Color::Yellow);
        }
        else {
            text.setFillColor(sf::Color::White);
        }
    }
    void SetButtonText(sf::Text &text, sf::Font &f, sf::Color color, int characterSize, const char *str, sf::Vector2f position) {
        text.setString(str);
        text.setFont(f);
        text.setCharacterSize(characterSize);
        text.setFillColor(color);
        text.setPosition(position);
    }
};

#endif /* ScreenBase_hpp */
