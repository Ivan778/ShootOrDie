//
//  PauseScreen.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 01.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "PauseScreen.hpp"

PauseScreen::PauseScreen(): wallpaper("PauseBackground.jpg", 0, 0, 1920, 1200, windowX, windowY) {
    //Настраиваем кнопку "Play"
    SetButtonText(continueGame, font, sf::Color::White, 110, "Continue", sf::Vector2f(windowX*0.1, windowY*0.45));
    //Настраиваем кнопку "Info"
    SetButtonText(restartGame, font, sf::Color::White, 110, "Restart", sf::Vector2f(windowX*0.1, windowY*0.55));
    //Настраиваем кнопку "Exit"
    SetButtonText(backToMenu, font, sf::Color::White, 110, "Back to menu", sf::Vector2f(windowX*0.1, windowY*0.65));
    
    double scaleX=double(windowX)/1920, scaleY=double(windowY)/1200;
    
    
    wallpaper.SetOriginAndSetPosition();
    wallpaper.SetCustomPosition(0, 0);
    
    mainCamera.reset(sf::FloatRect(0, 0, windowX, windowY));
}

int PauseScreen::Run(sf::RenderWindow &App) {
    sf::Event Event;
    bool Running = true;
    int menu = 0;
    sf::FloatRect continueGameBox=continueGame.getGlobalBounds();
    sf::FloatRect restartGameBox=restartGame.getGlobalBounds();
    sf::FloatRect backToMenuBox=backToMenu.getGlobalBounds();
    
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
                if(continueGameBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return 3;
                }
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(restartGameBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return -11;
                }
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(backToMenuBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    return -12;
                }
            }
        }
        //Clearing screen
        App.clear();
        
        App.setView(mainCamera);
        mainCamera.setCenter(windowX*0.5, windowY*0.5);
        
        //Идёт код обработки меняющихся событий
        wallpaper.DrawSprite(App);
        
        App.draw(continueGame);
        App.draw(restartGame);
        App.draw(backToMenu);
        
        MouseOverButtonText(continueGameBox, sf::Mouse::getPosition(App), continueGame);
        MouseOverButtonText(restartGameBox, sf::Mouse::getPosition(App), restartGame);
        MouseOverButtonText(backToMenuBox, sf::Mouse::getPosition(App), backToMenu);
        
        
        //Update the screen
        App.display();
    }
    
    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}