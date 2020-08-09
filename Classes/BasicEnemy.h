#ifndef __BASIC_ENEMY_H__
#define __BASIC_ENEMY_H__

#include "cocos2d.h"
#include "Enemy.h"

class BasicEnemy : public Enemy {
public:
    BasicEnemy(cocos2d::Scene * scene, cocos2d::Point position);
    bool getHit() override;

};


#endif //__BASIC_ENEMY_H__
