#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy {
public:
    cocos2d::Sprite * sprite;
    cocos2d::Scene * scene;

    Enemy(cocos2d::Scene * scene);

    virtual bool getHit() = 0;
    virtual int getScore() = 0;

};


#endif //__ENEMY_H__
