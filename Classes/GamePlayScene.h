#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"

#include "SpaceShip.h"

class GamePlay : public cocos2d::Scene {
private:
    bool touched;
    cocos2d::Point touchPoint;
    SpaceShip spaceShip;


public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void update(float delta);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    bool onContactBegin(cocos2d::PhysicsContact & contact);

    CREATE_FUNC(GamePlay);

    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; }
};

#endif // __GAMEPLAY_SCENE_H__
