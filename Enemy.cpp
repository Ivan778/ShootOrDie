//
//  Enemy.cpp
//  Курсовая по КПиЯП
//
//  Created by Иван on 12.11.16.
//  Copyright © 2016 IvanCode. All rights reserved.
//

#include "Enemy.hpp"

void Enemy::MoveInTheDirectionOfTarget(sf::Vector2f positionOfTarget) {
    SetAngleToSomething(positionOfTarget);
    
    sprite.move(ComputeVectorTowardsTarget(positionOfTarget).x*moveSpeed, ComputeVectorTowardsTarget(positionOfTarget).y*moveSpeed);
}

sf::Vector2f Enemy::ComputeVectorTowardsTarget(sf::Vector2f positionOfTarget) {
    float distanceX, distanceY, directionX, directionY, shortestDistance;
    
    distanceX=abs(positionOfTarget.x-sprite.getPosition().x);
    
    if(distanceX<=70) {
        distanceX=0;
    }
    
    distanceY=abs(positionOfTarget.y-sprite.getPosition().y);
    
    if(distanceY<=70) {
        distanceY=0;
    }
    
    shortestDistance=sqrt((distanceX*distanceX)+(distanceY*distanceY));
    if(shortestDistance==0) {
        return sf::Vector2f(0, 0);
    }
    
    directionX=(abs(positionOfTarget.x-sprite.getPosition().x)/(positionOfTarget.x-sprite.getPosition().x))*(distanceX/shortestDistance);
    directionY=(abs(positionOfTarget.y-sprite.getPosition().y)/(positionOfTarget.y-sprite.getPosition().y))*(distanceY/shortestDistance);
    
    /*
    if(positionOfTarget.x<sprite.getPosition().x) {
        directionX=-distanceX/shortestDistance;
    }
    else {
        if(positionOfTarget.x>sprite.getPosition().x) {
            directionX=distanceX/shortestDistance;
        }
    }
    if(positionOfTarget.y<sprite.getPosition().y) {
        directionY=-distanceY/shortestDistance;
    }
    else {
        if(positionOfTarget.y>sprite.getPosition().y) {
            directionY=distanceY/shortestDistance;
        }
    }
    */
     
    return sf::Vector2f(directionX, directionY);
}

void Enemy::SetSpeed(float moveSpeed) {
    this->moveSpeed=moveSpeed;
}

bool Enemy::IsKilled() {
    if(amountOfLifes<=0) {
        return true;
    }
    return false;
}

void Enemy::SetSkins(sf::Texture &t, const char name[]) {
    if(!t.loadFromFile(resourcePath()+name)) {
        cout << "Enemy texture problem" << endl;
        return EXIT_FAILURE;
    }
}

bool Enemy::OnCollisionWithPlayer(sf::Vector2f playerPosition) {
    float a, b, c;
    
    a=playerPosition.x-sprite.getPosition().x;
    a*=a;
    
    b=playerPosition.y-sprite.getPosition().y;
    b*=b;
    
    c=sqrt(a+b);
    
    if(c<=100) {
        return true;
    }
    return false;
}

void Enemy::ResetLifes() {
    amountOfLifes=amountOfLifesReserve;
}

void Enemy::Damage() {
    amountOfLifes--;
}
