#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include "cocos2d.h"

#include "Gun.h"

class SpaceShip {
private:
    cocos2d::Scene * scene;
    float speed = 250.0;
    Gun * gun;
public:
    cocos2d::Sprite * sprite;
    void create(cocos2d::Scene *, cocos2d::Point);
    void move(cocos2d::Point destination, float delta);
    void startShooting();
    void stopShooting();
};


#endif //__SPACESHIP_H__
