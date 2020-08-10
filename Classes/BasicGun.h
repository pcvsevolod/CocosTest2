#ifndef __BASIC_GUN_H__
#define __BASIC_GUN_H__

#include "cocos2d.h"
#include "Gun.h"

class BasicGun : public Gun {
private:
    int level = 0;
    float firingDelay = 0.2;
    const int tag = 124;
public:
    BasicGun(cocos2d::Scene * scene, cocos2d::Sprite * sprite) : Gun(scene, sprite) {};
    void shoot() override;
    void startShooting() override;
    void stopShooting() override;
    void upgrade();
};


#endif //__BASIC_GUN_H__
