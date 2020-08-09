#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"

#include "SpaceShip.h"
#include "EnemyController.h"

class GamePlay : public cocos2d::Scene {
private:
    bool touched;
    cocos2d::Point touchPoint;
    SpaceShip spaceShip;
    EnemyController * ec;
    cocos2d::Label * livesLabel;

    void updateLabel();

    void initTouch();
    void initCollision();
    void initUpdate();
    void initLabel();


public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    ~GamePlay();

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
