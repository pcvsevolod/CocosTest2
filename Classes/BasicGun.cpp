#include "BasicGun.h"
#include "SpaceShip.h"

USING_NS_CC;

void BasicGun::shoot() {
    std::vector<Point> directions;

    directions.emplace_back(0, 1000);

    for (auto & dir : directions){
        auto projectile = Sprite::create("Projectile.png");
        projectile->setPosition(sprite->getPosition());

        auto projectileBody = PhysicsBody::createCircle(projectile->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
        projectileBody->setDynamic(false);
        projectileBody->setCollisionBitmask(SpaceShip::projectileCollisionBitmask);
        projectileBody->setContactTestBitmask(true);
        projectile->setPhysicsBody(projectileBody);

        scene->addChild(projectile);

        auto move = MoveBy::create(3, dir);
        auto removeSelf = RemoveSelf::create();
        projectile->runAction(Sequence::create(move, removeSelf, NULL));
    }
}

void BasicGun::startShooting() {
    auto delay = DelayTime::create(firingDelay);
    auto func = CallFunc::create(CC_CALLBACK_0(BasicGun::shoot, this));
    //auto func = CallFunc::create(std::bind(&BasicGun::shoot, scene));
    auto seq = Sequence::create(delay, func, NULL);
    auto action = RepeatForever::create(seq);
    action->setTag(tag);
    scene->runAction(action);
}

void BasicGun::stopShooting() {
    scene->stopActionByTag(tag);
}