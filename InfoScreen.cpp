//
//  InfoScreen.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "InfoScreen.hpp"

InfoScreen::InfoScreen(void):
background("Metal.png", 0, 0, 660, 660),
rifle("RiffleImage.png", 0, 0, 600, 225),
shotgun("ShotgunImage.png", 0, 0, 860, 150),
money(0, "DollarSign.png", 0, 0, 230, 426, font, 80, 0.3f) {
    SetButtonText(backToMenu, font, sf::Color::Red, 100, "Back to menu", sf::Vector2f(100, 50));
    
    SetButtonText(speed, font, sf::Color::White, 80, "Speed", sf::Vector2f(windowX*0.1, windowY*0.4));
    
    background.SetMap(sf::IntRect(0, 0, windowX, windowY));
    background.SetBackground();
    
    rifle.SetSprite();
    rifle.GetSprite().setScale(0.55, 0.55);
    rifle.GetSprite().setPosition(windowX*0.8-80, windowY*0.3);
    
    shotgun.SetSprite();
    shotgun.GetSprite().setScale(0.4, 0.4);
    shotgun.GetSprite().setPosition(windowX*0.5-40, windowY*0.3);
    
    updatedRifleSpeed=false;
    updatedShotgunSpeed=false;
    
    modRifle=1;
    modShotgun=1;
}

void InfoScreen::FileProcessor(const char name[], sf::Text &text, int &speed, bool &updated, int &mod) {
    FILE *file;
    if(!(file=fopen(name, "r+b"))) {
        cout << "File is not opened!" << endl;
    }
    fpos_t fileSize;
    fseek(file, 0, SEEK_END);
    fgetpos(file, &fileSize);
    
    if(!updated) {
        if(fileSize>0) {
            int t;
            rewind(file);
            fread(&speed, sizeof(int), 1, file);
            
            text.setString(to_string(speed));
            
            if(speed<=currentMoney) {
                if(fileSize>=sizeof(int)) {
                    currentMoney-=speed;
                    mod++;
                    
                    money.SetIndicator(currentMoney);
                    for(fpos_t i=0, j=sizeof(int);j<=fileSize-sizeof(int);i+=sizeof(int), j+=sizeof(int)) {
                        fsetpos(file, &j);
                        fread(&t, sizeof(int), 1, file);
                        
                        fsetpos(file, &i);
                        fwrite(&t, sizeof(int), 1, file);
                    }
                    ftruncate(fileno(file), fileSize-sizeof(int));
                    
                    fseek(file, 0, SEEK_END);
                    fgetpos(file, &fileSize);
                    
                    if(fileSize!=0) {
                        rewind(file);
                        fread(&speed, sizeof(int), 1, file);
                        text.setString(to_string(speed));
                    }
                    else {
                        updated=true;
                        rewind(file);
                        t=-1;
                        fwrite(&t, sizeof(int), 1, file);
                        text.setString("Updated");
                        text.setPosition(text.getPosition().x-80, text.getPosition().y);
                    }
                }
            }
        }
    }
    fclose(file);
}

int InfoScreen::Run(sf::RenderWindow &App) {
    sf::Event Event;
    bool Running = true;
    int menu = 0;
    
    sf::FloatRect backToMenuBox=backToMenu.getGlobalBounds();
    
    FILE *fileMoney, *fileRifleSpeedPrice, *fileShotgunSpeedPrice, *modifications;
    
    if(!(fileMoney=fopen("/Users/ivan/Documents/Money.txt", "a+"))) {
        cout << "MoneyInfo is not opened!" << endl;
    }
    rewind(fileMoney);
    fscanf(fileMoney, "%d", &currentMoney);
    money.SetIndicator(currentMoney);
    
    if(!(fileRifleSpeedPrice=fopen("/Users/ivan/Documents/RifleSpeed.txt", "r+b"))) {
        cout << "RifleSpeed is not opened!" << endl;
    }
    
    string temp;
    
    rewind(fileRifleSpeedPrice);
    fread(&rifleSpeed, sizeof(int), 1, fileRifleSpeedPrice);
    
    if(rifleSpeed==-1) {
        updatedRifleSpeed=true;
        SetButtonText(textRifleSpeed, font, sf::Color::White, 80, "Updated", sf::Vector2f(windowX*0.5-70-80, windowY*0.4));
    }
    else {
        updatedRifleSpeed=false;
        temp=to_string(rifleSpeed);
        SetButtonText(textRifleSpeed, font, sf::Color::White, 80, temp.c_str(), sf::Vector2f(windowX*0.5-70, windowY*0.4));
    }
    
    fclose(fileRifleSpeedPrice);
    
    if(!(fileShotgunSpeedPrice=fopen("/Users/ivan/Documents/ShotgunSpeed.txt", "r+b"))) {
        cout << "ShotgunSpeed is not opened!" << endl;
    }
    
    rewind(fileShotgunSpeedPrice);
    fread(&shotgunSpeed, sizeof(int), 1, fileShotgunSpeedPrice);
    
    if(shotgunSpeed==-1) {
        updatedShotgunSpeed=true;
        SetButtonText(textShotgunSpeed, font, sf::Color::White, 80, "Updated", sf::Vector2f(windowX*0.74-70-80, windowY*0.4));
    }
    else {
        updatedShotgunSpeed=false;
        temp=to_string(shotgunSpeed);
        SetButtonText(textShotgunSpeed, font, sf::Color::White, 80, temp.c_str(), sf::Vector2f(windowX*0.74-70, windowY*0.4));
    }
    
    fclose(fileShotgunSpeedPrice);
    
    if(!(modifications=fopen("/Users/ivan/Documents/WeaponModifications.txt", "r+b"))) {
        cout << "Modifications is not opened!" << endl;
    }
    rewind(modifications);
    fread(&modRifle, sizeof(int), 1, modifications);
    fread(&modShotgun, sizeof(int), 1, modifications);
    fclose(modifications);
    
    sf::FloatRect rifleSpeedBox=textRifleSpeed.getGlobalBounds();
    sf::FloatRect shotgunSpeedBox=textShotgunSpeed.getGlobalBounds();
    
    while (Running)
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                if(!(modifications=fopen("/Users/ivan/Documents/WeaponModifications.txt", "r+b"))) {
                    cout << "Modifications is not opened!" << endl;
                }
                rewind(modifications);
                fwrite(&modRifle, sizeof(int), 1, modifications);
                fwrite(&modShotgun, sizeof(int), 1, modifications);
                fclose(modifications);
                
                ftruncate(fileno(fileMoney), 0);
                rewind(fileMoney);
                fprintf(fileMoney, "%d", currentMoney);
                
                fclose(fileMoney);
                fclose(fileRifleSpeedPrice);
                fclose(fileShotgunSpeedPrice);
                return (-1);
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(backToMenuBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    if(!(modifications=fopen("/Users/ivan/Documents/WeaponModifications.txt", "r+b"))) {
                        cout << "Modifications is not opened!" << endl;
                    }
                    rewind(modifications);
                    fwrite(&modRifle, sizeof(int), 1, modifications);
                    fwrite(&modShotgun, sizeof(int), 1, modifications);
                    fclose(modifications);
                    
                    ftruncate(fileno(fileMoney), 0);
                    rewind(fileMoney);
                    fprintf(fileMoney, "%d", currentMoney);
                    
                    fclose(fileMoney);
                    fclose(fileRifleSpeedPrice);
                    fclose(fileShotgunSpeedPrice);
                    return 0;
                }
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(rifleSpeedBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    FileProcessor("/Users/ivan/Documents/RifleSpeed.txt", textRifleSpeed, rifleSpeed, updatedRifleSpeed, modRifle);
                }
            }
            
            if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                if(shotgunSpeedBox.contains(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y)) {
                    FileProcessor("/Users/ivan/Documents/ShotgunSpeed.txt", textShotgunSpeed, shotgunSpeed, updatedShotgunSpeed, modShotgun);
                }
            }
            
    
        }
        //Clearing screen
        App.clear();
        
        //Идёт код обработки меняющихся событий
        background.DrawSprite(App);
        
        App.draw(backToMenu);
        
        rifle.DrawSprite(App);
        App.draw(speed);
        App.draw(textRifleSpeed);
        App.draw(textShotgunSpeed);
        
        shotgun.DrawSprite(App);
        
        money.ShowIndicator(App, App.getView().getCenter(), windowX, windowY, 1180, 80, -70, -31);
        
        MouseOverButtonText(backToMenuBox, sf::Mouse::getPosition(App), backToMenu);
        MouseOverButtonText(rifleSpeedBox, sf::Mouse::getPosition(App), textRifleSpeed);
        MouseOverButtonText(shotgunSpeedBox, sf::Mouse::getPosition(App), textShotgunSpeed);
        
        //Update the screen
        App.display();
    }
    
    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}