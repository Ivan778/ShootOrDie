//
//  PlayScreen.hpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#ifndef PlayScreen_hpp
#define PlayScreen_hpp

#include "ScreenBase.hpp"
#include "LoadingTheSpriteToMain.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Gunsight.hpp"
#include "Background.hpp"
#include "LightEffect.hpp"
#include "Enemy.hpp"
#include "IndicatorBase.hpp"
#include "Loot.hpp"
#include "Wallpaper.hpp"

class PlayScreen: public ScreenBase {
private:
    sf::Clock clock, gameTime, shotGunBullet, helpKIT, rifflePing, zombieTime;
    sf::Time timeZ;
    float time;
    int mapX, mapY, zombiePack, currentBullet, currentBulletRiffle;
    
    sf::View mainCamera;
    bool createBullet, sawManual;
    
    Player player;
    Gunsight gunsight;
    
    Bullet newBullet;
    vector<Bullet> bulletsRiffle, bulletsShotgun, bulletsGun;
    
    Background background;
    LightEffect lightEffect;
    
    Enemy *enemy;
    vector<Enemy> enemies;
    
    IndicatorBase lifes, score;
    
    Loot healthKit;
    
    Wallpaper wallpaper, manualScreen;
    
    int killedZombies;
    
    int modRifle, modShotgun;
public:
    PlayScreen(void);
    ~PlayScreen() {  }
    void GetPlayerPosition(sf::View &camera, sf::Vector2f playerPosition, int windowX, int windowY, int mapX, int mapY);
    virtual int Run(sf::RenderWindow &App);
    
    void AddOneMoreZombie(int randNumber);
    void DrawZombieAndDetectItsCollisionWithBullets(sf::RenderWindow &window);
    
    void BulletCollisionWithWalls();
    void ShootToThrill(sf::RenderWindow &window);
    void CreateBulletAndPushItInMyGun(sf::RenderWindow &window);
    void ShotgunBulletShot(sf::RenderWindow &window);
    
    void DrawPlayerAndSetItsProperties(sf::RenderWindow &window);
    
    void DrawAndSetPositionOfLightEffect(sf::RenderWindow &window);
    
    void HealthBarControl(sf::RenderWindow &window);
    void ScoreControl(sf::RenderWindow &window);
    
    void DrawGunsightAndSetItsPosition(sf::RenderWindow &window);
    
    void GenerateHelpKIT();
    void GenerateZombies();
    void DetectCollisionWithHealthKIT();
    
    void RunManualScreen(sf::RenderWindow &window, sf::Event &event);
    void RunGameOverScreen(sf::RenderWindow &window, sf::Event &event);
    
    void SetModifications();
    
    void RiffleBulletsCollisionWithWalls();
    void DrawRiffleBulletsAndMoveIt(sf::RenderWindow &window);
    void DetectBulletCollisionWithZombie();
};

#endif /* PlayScreen_hpp */
