#ifndef __ADVANCED_ENEMY_H__
#define __ADVANCED_ENEMY_H__

#include "cocos2d.h"
#include "Enemy.h"

class AdvancedEnemy : public Enemy {
private:
    int lives = 5;

    void startMoving();

public:
    AdvancedEnemy(cocos2d::Scene * scene, cocos2d::Point position);
    bool getHit() override;
    int getScore() override;

};


#endif //__ADVANCED_ENEMY_H__
