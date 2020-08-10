#ifndef __ENEMYCONTROLLER_H__
#define __ENEMYCONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyController {
public:
    cocos2d::Scene * scene;
    std::vector<Enemy*> enemies;
    static const int collisionBitmask = 16;
    static const int projectileCollisionBitmask = 32;
    cocos2d::Point shotDirection = cocos2d::Point(4, -400);
    float shotDuration = 4;
    float shotDelay = 2;

    EnemyController(cocos2d::Scene * scene);
    void place1();
    void place2();
    int getHit(cocos2d::Node * node);
    void startShootingBack();
    void checkOffScreen();

private:
    int stage = 0;
    void shootBack();
};


#endif //__ENEMYCONTROLLER_H__
