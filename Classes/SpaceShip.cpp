#include "SpaceShip.h"
#include "BasicGun.h"

USING_NS_CC;

void SpaceShip::create(cocos2d::Scene * scene, cocos2d::Point position) {
    this->scene = scene;
    sprite = Sprite::create("SpaceShip.png");
    sprite->setPosition(position);
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
    gun->startShooting();
}

void SpaceShip::stopShooting() {
    gun->stopShooting();
}
