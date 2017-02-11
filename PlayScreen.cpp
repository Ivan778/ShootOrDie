//
//  PlayScreen.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 29.10.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "PlayScreen.hpp"

PlayScreen::PlayScreen(void):
player("PlayerWithRiffle.png", 0, 0, 253, 216, 6, "PlayerWithShotgun.png", "PlayerWithGun.png"),
gunsight("Gunsight.png", 0, 0, 600, 600),
newBullet("Bullet.png", 0, 0, 357, 100, 10),
background("Floor.jpg", 0, 0, 592, 592),
lightEffect("LightEffect.png", 0, 0, 1600, 1600, windowX, windowY),
/*enemy("citizenzombie1.png", 0, 0, 71, 71, 9.7, 3),*/
lifes(100, "Heart.png", 0, 0, 256, 256, font, 60, 0.4f),
score(0, "DollarSign.png", 0, 0, 230, 426, font, 80, 0.3f),
healthKit(10, "HealthKit.png", 0, 0, 400, 400),
wallpaper("GameOver.jpg", 0, 0, 1440, 900, windowX, windowY),
manualScreen("ManualScreen.jpg", 0, 0, 1920, 1080, windowX, windowY) {
    mapX=4000;
    mapY=4000;
    
    currentBullet=0;
    currentBulletRiffle=0;
    
    zombiePack=0;
    
    killedZombies=0;
    
    createBullet=false;
    mainCamera.reset(sf::FloatRect(0, 0, windowX, windowY));
    
    //Уточнение параметров игрока
    player.SetOriginOfEntity(0, 44);
    player.GetSprite().setScale(0.8, 0.8);
    player.GetSprite().setPosition(mapX*0.5, mapY*0.5);
    
    //Уточнение параметров прицела
    gunsight.GetSprite().setScale(0.2, 0.2);
    
    //Уточнение параметров пули
    newBullet.GetSprite().setScale(0.08, 0.08);
    
    for(int i=0;i<20;i++) {
        bulletsRiffle.push_back(newBullet);
        bulletsShotgun.push_back(newBullet);
    }
    
    //Уточнение параметров заднего фона
    background.SetMap(IntRect(0, 0, mapX, mapY));
    background.SetBackground();
    
    gunsight.GetSprite().scale(0.5, 0.5);
    
    //Настройка зомби
    enemy=new Enemy("citizenzombie1.png", 0, 0, 71, 71, 9.7, 3);
    enemy->GetSprite().setPosition(mapX*0.4, mapY*0.4);
    enemy->ComputeVectorTowardsTarget(player.GetCurrentPosition());
    enemy->GetSprite().setScale(2.3, 2.3);
    
    enemies.push_back(*enemy);
    
    healthKit.GetSprite().setScale(0.3, 0.3);
    
    wallpaper.SetOriginAndSetPosition();
    manualScreen.SetOriginAndSetPosition();
    
    sawManual=false;
    
    modRifle=1;
    modShotgun=1;
}

void PlayScreen::GetPlayerPosition(sf::View &camera, sf::Vector2f playerPosition, int windowX, int windowY, int mapX, int mapY) {
    if(playerPosition.x<windowX/2)
        playerPosition.x=windowX/2;
    
    if(playerPosition.y<windowY/2)
        playerPosition.y=windowY/2;
    
    if(playerPosition.x>mapX-windowX/2)
        playerPosition.x=mapX-windowX/2;
    
    if(playerPosition.y>mapY-windowY/2)
        playerPosition.y=mapY-windowY/2;
    
    camera.setCenter(playerPosition);
}

sf::Vector2f Vec(sf::Vector2f positionOfTarget, sf::Vector2f enemy) {
    float distanceX, distanceY, directionX, directionY, shortestDistance;
    
    distanceX=abs(positionOfTarget.x-enemy.x);
    distanceY=abs(positionOfTarget.y-enemy.y);
    
    shortestDistance=sqrt((directionX*directionX)+(directionY*directionY));
    
    if(positionOfTarget.x<enemy.x) {
        directionX=-distanceX/shortestDistance;
    }
    if(positionOfTarget.x>enemy.x) {
        directionX=distanceX/shortestDistance;
    }
    if(positionOfTarget.y<enemy.y) {
        directionY=-distanceY/shortestDistance;
    }
    if(positionOfTarget.y>enemy.y) {
        directionY=distanceY/shortestDistance;
    }
    
    return sf::Vector2f(directionX, directionY);
}

void PlayScreen::AddOneMoreZombie(int randNumber) {
    int x, y;
    
    //Установка точки генератора чисел
    std::srand(randNumber);
    
    //Генерируем местоположение появления зомби
    x=500+std::rand()%mapX;
    y=500+std::rand()%mapY;
    
    //Устанавливаем позицию зомби и его скорость
    enemy->GetSprite().setPosition(x, y);
    enemy->SetSpeed(2+rand()%8);
    
    //Отправляем этого зомби в вектор
    enemies.push_back(*enemy);
}

void PlayScreen::BulletCollisionWithWalls() {
    for(int i=0;i<bulletsRiffle.size();i++) {
        if(bulletsRiffle[i].ShouldWeEraseBullet(mapX, mapY)) {
            bulletsRiffle[i].GetSprite().setPosition(-4000, -4000);
            bulletsRiffle[i].HideBullet();
        }
    }
}

void PlayScreen::ShootToThrill(sf::RenderWindow &window) {
    for(int i=0;i<currentBulletRiffle;i++) {
        bulletsRiffle[i].DrawSprite(window);
        bulletsRiffle[i].MoveToCurrentPoint(13);
    }
}

void PlayScreen::CreateBulletAndPushItInMyGun(sf::RenderWindow &window) {
    if(createBullet) {
        if(currentBulletRiffle>19) {
            currentBulletRiffle=0;
        }
        bulletsRiffle[currentBulletRiffle].SetBulletForShootToThrill(window.mapPixelToCoords(sf::Mouse::getPosition(window)), player.GetCurrentPosition());
        createBullet=false;
        currentBulletRiffle++;
    }
}

void PlayScreen::DrawPlayerAndSetItsProperties(sf::RenderWindow &window) {
    player.DrawSprite(window);
    //Учим главного героя двигаться и создаём стены для него
    player.SetMovementAndWalls(Keyboard::Key::W, Keyboard::Key::S, Keyboard::Key::A, Keyboard::Key::D, mapX, mapY, 300);
    //Изменяем угол главного героя в зависимости от позиции курсора
    player.SetAngleToSomething(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void PlayScreen::DrawZombieAndDetectItsCollisionWithBullets(sf::RenderWindow &window) {
    for(int i=0;i<enemies.size();i++) {
        enemies[i].DrawSprite(window);
        enemies[i].MoveInTheDirectionOfTarget(player.GetCurrentPosition());
        for(int j=0;j<currentBulletRiffle;j++) {
            if(enemies[i].OnCollisionWithObject(bulletsRiffle[j].GetGlobalBound())) {
                bulletsRiffle[j].GetSprite().setPosition(-4000, -4000);
                bulletsRiffle[j].HideBullet();
                enemies[i].Damage();
                enemies[i].Damage();
                enemies[i].Damage();
                if(enemies[i].IsKilled()) {
                    if(i%6==0 && i!=0) {
                        score.IncreaseIndicator(3);
                    }
                    score.IncreaseIndicator(1);
                    enemies[i].ResetLifes();
                    killedZombies++;
                    enemies[i].GetSprite().setPosition(-2000, -2000);
                }
            }
        }
    }
}

void PlayScreen::DrawAndSetPositionOfLightEffect(sf::RenderWindow &window) {
    lightEffect.DrawSprite(window);
    lightEffect.SetPositionToPlayer(player.GetCurrentPosition(), mapX, mapY);
}

void PlayScreen::HealthBarControl(sf::RenderWindow &window) {
    lifes.ShowIndicator(window, window.getView().getCenter(), windowX, windowY, 80, 80, -70, 0);
    for(int i=0;i<enemies.size();i++) {
        if(enemies[i].OnCollisionWithPlayer(player.GetCurrentPosition())) {
            lifes.DecreaseIndicator(0.05f);
        }
    }
}

void PlayScreen::ScoreControl(sf::RenderWindow &window) {
    score.ShowIndicator(window, window.getView().getCenter(), windowX, windowY, 80, 160, -70, 0);
    score.IncreaseIndicator(10);
}

void PlayScreen::DrawGunsightAndSetItsPosition(sf::RenderWindow &window) {
    gunsight.DrawSprite(window);
    gunsight.GetSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void PlayScreen::RunManualScreen(sf::RenderWindow &window, sf::Event &event) {
    sf::Text textInstruction, playingButtons, changeArm, shotButton;
    SetButtonText(textInstruction, font, sf::Color::Red, 150, "* How to play *", sf::Vector2f(windowX*0.5-600, windowY*0.1));
    SetButtonText(playingButtons, font, sf::Color::White, 70, "To move your player press W A S D", sf::Vector2f(250, windowY*0.5-110));
    SetButtonText(changeArm, font, sf::Color::White, 70, "To change weapon press Space", sf::Vector2f(289, windowY*0.5+110));
    SetButtonText(shotButton, font, sf::Color::White, 70, "To shoot press left mouse button", sf::Vector2f(270, windowY*0.5));
    while(1) {
        //Verifying events
        while(window.pollEvent(event))
        {
            //Выходим в меню по нажатии клавиши Space
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                sawManual=true;
                zombieTime.restart();
                helpKIT.restart();
                return;
                
            }
            if(event.type == sf::Event::Closed) {
                return (-1);
            }
        }
        //Clearing screen
        window.clear();
        
        manualScreen.DrawSprite(window);
        
        window.draw(textInstruction);
        window.draw(playingButtons);
        window.draw(changeArm);
        window.draw(shotButton);
        
        window.display();
    }
}

void PlayScreen::RunGameOverScreen(sf::RenderWindow &window, sf::Event &event) {
    int previousScore=0, previousMoney=0;
    bool newHighScore=false;
    FILE *fileScore, *fileMoney;
    fpos_t beg=0, fin;
    if(!(fileScore=fopen("/Users/ivan/Documents/Score.txt", "a+"))) {
        cout << "Score is not opened!" << endl;
    }
    fseek(fileScore, 0, SEEK_END);
    fgetpos(fileScore, &fin);
    int size=int(fin-beg);
    //cout << "Size - " << size << endl;
    if(size>0) {
        rewind(fileScore);
        fscanf(fileScore, "%d", &previousScore);
    }
    //cout << "Previous score - " << previousScore << endl;
    if(previousScore==0) {
        rewind(fileScore);
        fprintf(fileScore, "%d", score.ReturnIndicator());
    }
    if(previousScore!=0 && previousScore<score.ReturnIndicator()) {
        ftruncate(fileno(fileScore), 0);
        rewind(fileScore);
        fprintf(fileScore, "%d", score.ReturnIndicator());
        newHighScore=true;
    }
    
    if(!(fileMoney=fopen("/Users/ivan/Documents/Money.txt", "a+"))) {
        cout << "Money is not opened!" << endl;
    }
    
    fseek(fileMoney, 0, SEEK_END);
    fgetpos(fileMoney, &fin);
    size=fin;
    
    if(size>0) {
        rewind(fileMoney);
        fscanf(fileMoney, "%d", &previousMoney);
        previousMoney+=score.ReturnIndicator();
        ftruncate(fileno(fileMoney), 0);
        rewind(fileMoney);
        fprintf(fileMoney, "%d", previousMoney);
    }
    else {
        rewind(fileMoney);
        fprintf(fileMoney, "%d", score.ReturnIndicator());
    }
    
    while(1) {
        //Verifying events
        while(window.pollEvent(event))
        {
            //Выходим в меню по нажатии клавиши Space
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                fclose(fileScore);
                fclose(fileMoney);
                return -12;
            }
            
        }
        //Clearing screen
        window.clear();
        
        sf::Text youHaveDied, pressSpaceToContinue, killings, newRecord;
        string kills;
        kills=to_string(killedZombies)+" killed zombies";
        
        SetButtonText(youHaveDied, font, sf::Color::Red, 120, "You have been KILLED", sf::Vector2f(windowX*0.1+30, windowY*0.1));
        
        SetButtonText(killings, font, sf::Color::White, 60, kills.c_str(), sf::Vector2f(windowX*0.16, windowY*0.5));
        
        SetButtonText(pressSpaceToContinue, font, sf::Color::White, 50, "Press Space to continue", sf::Vector2f(windowX*0.1, windowY*0.7));
        
        SetButtonText(newRecord, font, sf::Color::Yellow, 100, "New record", sf::Vector2f(windowX*0.55, windowY*0.4));
        newRecord.setRotation(45);
        
        wallpaper.DrawSprite(window);
        
        window.draw(youHaveDied);
        
        score.ShowIndicator(window, window.getView().getCenter(), windowX, windowY, windowX*0.2, windowY*0.4, -70, -37);
        window.draw(killings);
        
        window.draw(pressSpaceToContinue);
        if(newHighScore) {
            window.draw(newRecord);
        }
        
        window.display();
    }
}

void PlayScreen::GenerateHelpKIT() {
    if(helpKIT.getElapsedTime().asSeconds()>=60) {
        int x, y;
        x=300+std::rand()%500;
        y=300+std::rand()%500;
        x+=player.GetCurrentPosition().x;
        y+=player.GetCurrentPosition().y;
        if(x>=mapX-300 || x<=0+300) {
            x=mapX*0.5;
        }
        if(y>=mapY-300 || y<=0+300) {
            y=mapY*0.5;
        }
        healthKit.GetSprite().setPosition(sf::Vector2f(x, y));
        helpKIT.restart();
    }
}

void PlayScreen::GenerateZombies() {
    timeZ=zombieTime.getElapsedTime();
    
    if(timeZ.asSeconds()>=5) {
        if(clock.getElapsedTime().asSeconds()>=13) {
            zombiePack++;
            clock.restart();
        }
        for(int i=0;i<2;i++) {
            int r;
            std::srand(i*11);
            r=clock.getElapsedTime().asMilliseconds();
            if(i%2==0) {
                r+=rand()%300;
            }
            AddOneMoreZombie(r);
        }
        zombieTime.restart();
    }
}

void PlayScreen::SetModifications() {
    FILE *modifications;
    if(!(modifications=fopen("/Users/ivan/Documents/WeaponModifications.txt", "r+b"))) {
        cout << "Modifications is not opened!" << endl;
    }
    rewind(modifications);
    fread(&modRifle, sizeof(int), 1, modifications);
    fread(&modShotgun, sizeof(int), 1, modifications);
    fclose(modifications);
    
    cout << "Riffle - " << modRifle << endl << "Shotgun - " << modShotgun << endl;
}

void PlayScreen::RiffleBulletsCollisionWithWalls() {
    if(player.GunMode()==2) {
        for(int i=0;i<currentBullet;i++) {
            if(bulletsShotgun[i].ShouldWeEraseBullet(mapX, mapY)) {
                bulletsShotgun[i].GetSprite().setPosition(-4000, -4000);
                bulletsShotgun[i].HideBullet();
            }
        }
    }
}

void PlayScreen::DrawRiffleBulletsAndMoveIt(sf::RenderWindow &window) {
    if(player.GunMode()==2) {
        for(int i=0;i<currentBullet;i++) {
            bulletsShotgun[i].DrawSprite(window);
            bulletsShotgun[i].MoveToCurrentPoint(13);
        }
    }
}

void PlayScreen::DetectBulletCollisionWithZombie() {
    if(player.GunMode()==2) {
        for(int i=0;i<enemies.size();i++) {
            for(int j=0;j<=currentBullet;j++) {
                if(bulletsShotgun[j].OnCollisionWithObject(enemies[i].GetGlobalBound())) {
                    bulletsShotgun[j].GetSprite().setPosition(-4000, -4000);
                    bulletsShotgun[j].HideBullet();
                    enemies[i].Damage();
                    if(enemies[i].IsKilled()) {
                        if(i%6==0 && i!=0) {
                            score.IncreaseIndicator(3);
                        }
                        enemies[i].ResetLifes();
                        score.IncreaseIndicator(1);
                        killedZombies++;
                        enemies[i].GetSprite().setPosition(-2000, -2000);
                    }
                }
            }
        }
    }
}

void PlayScreen::DetectCollisionWithHealthKIT() {
    if(player.OnCollisionWithObject(healthKit.GetGlobalBound())) {
        lifes.IncreaseIndicatorBorder(healthKit.returnAdd());
        healthKit.GetSprite().setPosition(-2000, -2000);
    }
}

void PlayScreen::ShotgunBulletShot(sf::RenderWindow &window) {
    if(shotGunBullet.getElapsedTime().asSeconds()>=(0.33/double(modShotgun))) {
        if(player.GunMode()==2) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if(currentBullet>19) {
                    currentBullet=0;
                }
                bulletsShotgun[currentBullet].SetBulletForShootToThrill(window.mapPixelToCoords(sf::Mouse::getPosition(window)), player.GetCurrentPosition());
                currentBullet++;
            }
        }
        shotGunBullet.restart();
    }
}

int PlayScreen::Run(sf::RenderWindow &App) {
    sf::Event Event;
    bool Running = true;
    //sf::Clock zombieTime;
    //sf::Time timeZ;
    zombieTime.restart();
    
    bool goTo=false;
    
    //Запуск экрана с мануалом
    if(!sawManual) {
        RunManualScreen(App, Event);
    }

    Running=true;
    SetModifications();
    
    while(Running)
    {
        if(lifes.CheckIndicator()) {
            break;
        }
        
        GenerateHelpKIT();
        GenerateZombies();
        
        //Verifying events
        while(App.pollEvent(Event))
        {
            // Window closed
            if(Event.type == sf::Event::Closed) {
                return (-1);
            }
            
            if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::T) {
                goTo=true;
            }
            
            //Выходим в меню-пауза по нажатии клавиши Escape
            if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape) {
                return 2;
            }
            
            if(player.GunMode()==1) {
                //Обрабатываем левый щелчок мыши для создания пули
                if(Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                    if(rifflePing.getElapsedTime().asSeconds()>=(0.99/double(modRifle))) {
                        createBullet=true;
                        rifflePing.restart();
                    }
                }
            }
            
            //Блок с переключением оружия
            if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Space) {
                if(player.GunMode()==1) {
                    player.Mode2();
                    continue;
                }
                if(player.GunMode()==2) {
                    player.Mode1();
                    continue;
                }
            }
        }
        //Clearing screen
        App.clear();
        
        //Установка камеры
        App.setView(mainCamera);
        
        //Делаем курсор невидимым
        App.setMouseCursorVisible(false);
        
        //Устанавливаем задний фон
        background.DrawSprite(App);
        
        //Добавление пули в массив пуль по необходимости
        CreateBulletAndPushItInMyGun(App);
        
        //Блок с описанием работы пуль дробовика
        ShootToThrill(App);
        ShotgunBulletShot(App);
        
        //Блок с описанием работы пуль автомата
        DrawRiffleBulletsAndMoveIt(App);
        RiffleBulletsCollisionWithWalls();
        DetectBulletCollisionWithZombie();
        
        //Описание работы аптечки
        healthKit.DrawSprite(App);
        DetectCollisionWithHealthKIT();
        
        //Блок с описанием главного героя
        DrawPlayerAndSetItsProperties(App);
        
        //Обработка столкновений пуль
        BulletCollisionWithWalls();
        
        //Блок с описанием работы зомби
        DrawZombieAndDetectItsCollisionWithBullets(App);
        
        //Настройка и вывод на экран затемнения вокруг главного героя
        DrawAndSetPositionOfLightEffect(App);
         
        //Блок с описанием прицела
        DrawGunsightAndSetItsPosition(App);
        
        //Индикатора здоровья
        HealthBarControl(App);
        
        //Индикатор очков
        score.ShowIndicator(App, App.getView().getCenter(), windowX, windowY, 1300, 80, -70, -31);
        
        //Настройка камеры
        GetPlayerPosition(mainCamera, player.GetCurrentPosition(), windowX, windowY, mapX, mapY);
        
        //Update the screen
        App.display();
    }
    
    mainCamera.setCenter(windowX*0.5, windowY*0.5);
    App.setView(mainCamera);
    
    RunGameOverScreen(App, Event); return (-12);
    
    //На всякий случай оставим здесь выход в main
    return (-1);
}
