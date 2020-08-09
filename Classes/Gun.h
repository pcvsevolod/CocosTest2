#ifndef __GUN_H__
#define __GUN_H__

#include "cocos2d.h"

class Gun {
protected:
    cocos2d::Scene * scene;
    cocos2d::Sprite * sprite;

public:
    Gun(cocos2d::Scene * scene, cocos2d::Sprite * sprite);
    virtual void shoot() = 0;
    virtual void startShooting() = 0;
    virtual void stopShooting() = 0;
};


#endif //__GUN_H__
