#include "BasicEnemy.h"
#include "EnemyController.h"

USING_NS_CC;

BasicEnemy::BasicEnemy(cocos2d::Scene * scene, cocos2d::Point position) : Enemy(scene) {
    sprite = Sprite::create("BadShip2.png");
    sprite->setPosition(position);
    auto badShipBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
    badShipBody->setDynamic(false);
    badShipBody->setCollisionBitmask(EnemyController::collisionBitmask);
    badShipBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(badShipBody);
    scene->addChild(sprite);
    startMoving();
}

bool BasicEnemy::getHit()  {
    return true;
}

void BasicEnemy::startMoving() {
    auto moveLeft = MoveBy::create(1, Point(-10, 0));
    auto moveRight = MoveBy::create(1, Point(10, 0));
    auto moveDown = MoveBy::create(1, Point(0, -10));
    auto seq = Sequence::create(moveLeft, moveDown, moveRight, moveDown, NULL);
    auto rep = RepeatForever::create(seq);
    sprite->runAction(rep);
}

int BasicEnemy::getScore() {
    return 1;
}
