//
//  MenuScreen.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 28.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "MenuScreen.hpp"

MenuScreen::MenuScreen(): wallpaper("Menu.jpg", 0, 0, 1920, 1080, windowX, windowY) {
    //Настраиваем кнопку "Play"
    SetButtonText(play, font, sf::Color::White, 110, "Play", sf::Vector2f(windowX*0.09, windowY*0.45));
    //Настраиваем кнопку "Info"
    SetButtonText(info, font, sf::Color::White, 110, "Upgrades", sf::Vector2f(windowX*0.09, windowY*0.55));
    //Настраиваем кнопку "Exit"
    SetButtonText(exit, font, sf::Color::White, 110, "Exit", sf::Vector2f(windowX*0.09, windowY*0.65));
    //Настроиваем название игры
    SetButtonText(gameName, font, sf::Color::Red, 200, "Shoot or Die", sf::Vector2f(windowX*0.2, windowY*0.05));
    gameName.setRotation(20);
    
    wallpaper.SetOriginAndSetPosition();
    
    mainCamera.reset(sf::FloatRect(0, 0, windowX, windowY));
}

int MenuScreen::Run(sf::RenderWindow &App) {
    sf::Event Event;
    bool Running = true;
    int menu = 0;
    sf::FloatRect playBox=play.getGlobalBounds();
    sf::FloatRect infoBox=info.getGlobalBounds();
    sf::FloatRect exitBox=exit.getGlobalBounds();
    
    App.setMouseCursorVisible(true);
    
    while (Running)
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(exitBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return -1;
                }
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(infoBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return 1;
                }
            }
             
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(playBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return 3;
                }
            }
        }
        //Clearing screen
        App.clear();
        
        App.setView(mainCamera);
        mainCamera.setCenter(windowX*0.5, windowY*0.5);
        
        //Идёт код обработки меняющихся событий
        wallpaper.DrawSprite(App);
        App.draw(gameName);
        
        App.draw(play);
        App.draw(info);
        App.draw(exit);
        
        MouseOverButtonText(playBox, sf::Mouse::getPosition(App), play);
        MouseOverButtonText(infoBox, sf::Mouse::getPosition(App), info);
        MouseOverButtonText(exitBox, sf::Mouse::getPosition(App), exit);
        
        
        //Update the screen
        App.display();
    }
    
    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}