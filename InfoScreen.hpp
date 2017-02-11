//
//  InfoScreen.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef InfoScreen_hpp
#define InfoScreen_hpp


#include "ScreenBase.hpp"
#include "LoadingTheSpriteToMain.hpp"
#include "Background.hpp"
#include "IndicatorBase.hpp"

class InfoScreen: public ScreenBase {
private:
    sf::Text backToMenu, speed, textRifleSpeed, textShotgunSpeed;
    
    Background background;
    
    LoadingTheSpriteToMain rifle, shotgun;
    
    int currentMoney, rifleSpeed, shotgunSpeed, modRifle, modShotgun;
    
    bool updatedRifleSpeed, updatedShotgunSpeed;
    
    IndicatorBase money;
public:
    InfoScreen(void);
    ~InfoScreen() {  }
    virtual int Run(sf::RenderWindow &App);
    //void SetCurrentMoney();
    void FileProcessor(const char name[], sf::Text &text, int &speed, bool &updated, int &mod);
};

#endif /* InfoScreen_hpp */
