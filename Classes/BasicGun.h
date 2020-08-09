#ifndef __BASIC_GUN_H__
#define __BASIC_GUN_H__

#include "cocos2d.h"
#include "Gun.h"

class BasicGun : public Gun {
private:
    float firingDelay = 0.2;
    const int tag = 124;
    void f();
public:
    BasicGun(cocos2d::Scene * scene, cocos2d::Sprite * sprite) : Gun(scene, sprite) {};
    void shoot() override;
    void startShooting() override;
    void stopShooting() override;
};


#endif //__BASIC_GUN_H__
