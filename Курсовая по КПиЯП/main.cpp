
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "ScreenBase.hpp"

#include "MenuScreen.hpp"
#include "InfoScreen.hpp"
#include "PlayScreen.hpp"
#include "PauseScreen.hpp"

using namespace sf;

int main(int, char const**) {
    setlocale(LC_ALL, "Russian");
    
    //Создание главного окна
    const int windowX=1500, windowY=1100, mapX=4000, mapY=4000;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Shoot or Die", sf::Style::Titlebar | sf::Style::Close);
    
    //Устанавливаем иконку окна
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    window.setVerticalSyncEnabled(true);
    
    //Объявление вектора окон
    std::vector<ScreenBase*> Screens;
    int screen=0;
    
    
    FILE *fileRifleSpeedPrice, *fileShotgunSpeedPrice, *weaponModifications;
    int rifle[3]={500, 1000, 2000}, shotgun[3]={300, 600, 1200}, modifications[2]={1, 1};
    
    if(!(fileRifleSpeedPrice=fopen("/Users/ivan/Documents/RifleSpeed.txt", "a+b"))) {
        cout << "RifleSpeedMain is not opened!" << endl;
    }
    
    rewind(fileRifleSpeedPrice);
    int temp=0;
    fread(&temp, sizeof(int), 1, fileRifleSpeedPrice);
    if(temp==0) {
        for(int i=0;i<3;i++) {
            fwrite(&(rifle[i]), sizeof(int), 1, fileRifleSpeedPrice);
        }
    }
    
    fclose(fileRifleSpeedPrice);
    
    if(!(fileShotgunSpeedPrice=fopen("/Users/ivan/Documents/ShotgunSpeed.txt", "a+b"))) {
        cout << "ShotgunMain is not opened!" << endl;
    }
    rewind(fileShotgunSpeedPrice);
    temp=0;
    fread(&temp, sizeof(int), 1, fileShotgunSpeedPrice);
    if(temp==0) {
        for(int i=0;i<3;i++) {
            fwrite(&(shotgun[i]), sizeof(int), 1, fileShotgunSpeedPrice);
        }
    }
    
    fclose(fileShotgunSpeedPrice);
    
    if(!(weaponModifications=fopen("/Users/ivan/Documents/WeaponModifications.txt", "a+b"))) {
        cout << "ModificationsMain is not opened!" << endl;
    }
    rewind(weaponModifications);
    temp=0;
    fread(&temp, sizeof(int), 1, weaponModifications);
    if(temp==0) {
        for(int i=0;i<2;i++) {
            fwrite(&(modifications[i]), sizeof(int), 1, weaponModifications);
        }
    }
    
    fclose(weaponModifications);
     
    //Объявляем окно меню
    MenuScreen *menu;
    menu=new MenuScreen;
    //Объявляем окно улучшений
    InfoScreen *info;
    info=new InfoScreen;
    //Объявляем игровое окно
    PlayScreen *play;
    play=new PlayScreen;
    //Объявляем окно пауза
    PauseScreen *pause;
    pause=new PauseScreen;
    
    
    //Закидываем все окна в вектор
    Screens.push_back(&(*menu));
    Screens.push_back(&(*info));
    Screens.push_back(&(*pause));
    Screens.push_back(&(*play));
    
    //Запуск цикла игры
    while(screen>=0) {
        screen=Screens[screen]->Run(window);
        if(screen==-11) {
            delete Screens[3];
            Screens.pop_back();
            play=new PlayScreen;
            Screens.push_back(play);
            screen=3;
        }
        if(screen==-12) {
            delete Screens[3];
            Screens.pop_back();
            play=new PlayScreen;
            Screens.push_back(play);
            screen=0;
        }
    }
    
    return EXIT_SUCCESS;
}
