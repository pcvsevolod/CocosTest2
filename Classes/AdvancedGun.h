#ifndef __ADVANCED_GUN_H__
#define __ADVANCED_GUN_H__

#include "cocos2d.h"
#include "Gun.h"

class AdvancedGun : public Gun {
private:
    float firingDelay = 0.1;
    const int tag = 124;
public:
    AdvancedGun(cocos2d::Scene * scene, cocos2d::Sprite * sprite) : Gun(scene, sprite) {};
    void shoot() override;
    void startShooting() override;
    void stopShooting() override;
};


#endif //__ADVANCED_GUN_H__
