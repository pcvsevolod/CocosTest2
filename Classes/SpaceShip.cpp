#include "SpaceShip.h"
#include "BasicGun.h"
#include "AdvancedGun.h"

USING_NS_CC;

void SpaceShip::create(cocos2d::Scene * scene, cocos2d::Point position) {
    this->scene = scene;
    sprite = Sprite::create("SpaceShip1.png");
    sprite->setPosition(position);
    auto spaceShipBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
    spaceShipBody->setDynamic(false);
    spaceShipBody->setCollisionBitmask(collisionBitmask);
    spaceShipBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(spaceShipBody);
    this->scene->addChild(sprite, 0);

    gun = new BasicGun(scene, this->sprite);
}

void SpaceShip::move(cocos2d::Point destination, float delta) {
    float step = delta * speed;
    if(step > 0) {
        Point target = destination;
        float distance = target.getDistance(sprite->getPosition());
        if (distance > step) {
            target.subtract(sprite->getPosition());
            target.normalize();
            target.scale(step);
            target.add(sprite->getPosition());
            sprite->setPosition(target);
        } else {
            sprite->setPosition(target);
        }
    }
}

void SpaceShip::startShooting() {
    shooting = true;
    gun->startShooting();
}

void SpaceShip::stopShooting() {
    shooting = false;
    gun->stopShooting();
}

void SpaceShip::getHit() {
    lives--;
}

void SpaceShip::buff(cocos2d::Node *buff) {
    if (buff->getName() == "Life") {
        lives++;
    }
    if (buff->getName() == "Upgrade") {
        upgradeGun();
    }
}

void SpaceShip::upgradeGun() {
    if (gunLevel == 1) {
        CCLOG("hsajdklhfjsdhjfhsjkdfa MAX GUN MAX GUN");
        return;
    }
    gun->stopShooting();
    delete gun;
    gun = new AdvancedGun(scene, this->sprite);
    gunLevel = 1;
    if (shooting) {
        startShooting();
    }
}
