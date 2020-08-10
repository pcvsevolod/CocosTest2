#include "AdvancedEnemy.h"
#include "EnemyController.h"

USING_NS_CC;

AdvancedEnemy::AdvancedEnemy(cocos2d::Scene * scene, cocos2d::Point position) : Enemy(scene) {
    sprite = Sprite::create("BadShip3.png");
    sprite->setPosition(position);
    auto badShipBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
    badShipBody->setDynamic(false);
    badShipBody->setCollisionBitmask(EnemyController::collisionBitmask);
    badShipBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(badShipBody);
    scene->addChild(sprite);
    startMoving();
}

bool AdvancedEnemy::getHit()  {
    lives--;
    if (lives <= 0) {
        return true;
    }
    return false;
}

void AdvancedEnemy::startMoving() {
    auto moveLeft = MoveBy::create(1, Point(-20, 0));
    auto moveRight = MoveBy::create(1, Point(20, 0));
    auto moveDown = MoveBy::create(1, Point(0, -15));
    auto seq = Sequence::create(moveLeft, moveDown, moveRight, moveDown, NULL);
    auto rep = RepeatForever::create(seq);
    sprite->runAction(rep);
}

int AdvancedEnemy::getScore() {
    return 5;
}
