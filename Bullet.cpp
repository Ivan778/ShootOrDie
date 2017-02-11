//
//  Bullet.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 24.09.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Bullet.hpp"


void Bullet::SetDirection(sf::Vector2f mousePosition) {
    double x, y, c;
    int kx, ky;
    x=GetSprite().getPosition().x-mousePosition.x;
    y=GetSprite().getPosition().y-mousePosition.y;
    if(x>0 && y>0) {
        kx=1;
        ky=1;
    }
    if(x>0 && y<0) {
        kx=1;
        ky=-1;
    }
    if(x<0 && y<0) {
        kx=-1;
        ky=-1;
    }
    if(x<0 && y>0) {
        kx=-1;
        ky=1;
    }
    x=abs(x);
    y=abs(y);
    
    kx*=-1;
    ky*=-1;
    
    c=sqrt(x*x+y*y);
    x/=c;
    y/=c;
    
    direction.x=(kx*x)*speed;
    direction.y=(ky*y)*speed;
}

void Bullet::MoveToCurrentPoint(float time) {
    GetSprite().move(direction*time);
}

void Bullet::SetPosition(sf::Vector2f vector) {
    GetSprite().setPosition(vector);
}

void Bullet::SetBulletForShootToThrill(sf::Vector2f mousePosition, sf::Vector2f vector) {
    SetPosition(vector);
    SetDirection(mousePosition);
    SetAngleToSomething(mousePosition);
}

bool Bullet::ShouldWeEraseBullet(int mapX, int mapY){
    if(GetCurrentPosition().x<0-500) {
        return true;
    }
    if(GetCurrentPosition().x>mapX+500) {
        return true;
    }
    if(GetCurrentPosition().y<0-500) {
        return true;
    }
    if(GetCurrentPosition().y>mapY+500) {
        return true;
    }
    return false;
}

void Bullet::SayUsed() {
    used=true;
}

bool Bullet::returnUsed() {
    return used;
}

void Bullet::HideBullet() {
    direction=sf::Vector2f(-1, -1);
}
