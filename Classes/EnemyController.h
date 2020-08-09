#ifndef __ENEMYCONTROLLER_H__
#define __ENEMYCONTROLLER_H__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyController {
public:
    cocos2d::Scene * scene;
    std::vector<Enemy*> enemies;
    const int collisionBitmask = 16;

    EnemyController(cocos2d::Scene * scene);
    void place1();
};


#endif //__ENEMYCONTROLLER_H__
