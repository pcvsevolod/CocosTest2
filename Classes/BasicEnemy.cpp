#include "BasicEnemy.h"
#include "EnemyController.h"

USING_NS_CC;

BasicEnemy::BasicEnemy(cocos2d::Scene * scene, cocos2d::Point position) : Enemy(scene) {
    sprite = Sprite::create("BasicEnemy.png");
    sprite->setPosition(position);
    auto badShipBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
    badShipBody->setDynamic(false);
    badShipBody->setCollisionBitmask(EnemyController::collisionBitmask);
    badShipBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(badShipBody);
    scene->addChild(sprite);
}

bool BasicEnemy::getHit()  {
    return true;
}