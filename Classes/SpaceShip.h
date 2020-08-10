#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include "cocos2d.h"

#include "Gun.h"

class SpaceShip {
private:
    cocos2d::Scene * scene;
    float speed = 250.0;
    Gun * gun;
    int gunLevel = 0;
    bool shooting = false;

    void upgradeGun();
public:
    cocos2d::Sprite * sprite;
    static const int collisionBitmask = 1;
    static const int projectileCollisionBitmask = 2;
    int lives = 3;
    void create(cocos2d::Scene *, cocos2d::Point);
    void move(cocos2d::Point destination, float delta);
    void startShooting();
    void stopShooting();
    void getHit();
    void buff(cocos2d::Node * buff);
};


#endif //__SPACESHIP_H__
