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

    EnemyController(cocos2d::Scene * scene);
    void place1();
    void getHit(cocos2d::Node * node);
};


#endif //__ENEMYCONTROLLER_H__
