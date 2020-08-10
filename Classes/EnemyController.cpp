#include "EnemyController.h"

USING_NS_CC;

#include "BasicEnemy.h"
#include "AdvancedEnemy.h"
#include "GamePlayScene.h"

void EnemyController::place1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::vector<Point> badPositions;

    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 3; ++j) {
            badPositions.emplace_back(visibleSize.width / 2 + origin.x - j * 8,
                                      visibleSize.height / 8 * 7 + origin.y - i * 8);
            badPositions.emplace_back(visibleSize.width / 2 + origin.x + j * 8,
                                      visibleSize.height / 8 * 7 + origin.y - i * 8);
        }
        badPositions.emplace_back(visibleSize.width / 2 + origin.x,
                                  visibleSize.height / 8 * 7 + origin.y - i * 8);
    }
    for (auto &bp : badPositions) {
        auto enemy = new BasicEnemy(scene, bp);
        enemies.push_back(enemy);
    }
}

void EnemyController::place2() {
    stage = 1;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::vector<Point> badPositions;

    float spacing = 20;
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 2; ++j) {
            badPositions.emplace_back(visibleSize.width / 2 + origin.x - j * spacing,
                                      visibleSize.height / 8 * 7 + origin.y - i * spacing);
            badPositions.emplace_back(visibleSize.width / 2 + origin.x + j * spacing,
                                      visibleSize.height / 8 * 7 + origin.y - i * spacing);
        }
        badPositions.emplace_back(visibleSize.width / 2 + origin.x,
                                  visibleSize.height / 8 * 7 + origin.y - i * spacing);
    }
    for (auto &bp : badPositions) {
        auto enemy = new AdvancedEnemy(scene, bp);
        enemies.emplace_back(enemy);
    }
}

EnemyController::EnemyController(cocos2d::Scene *scene) {
    this->scene = scene;
}

int EnemyController::getHit(cocos2d::Node *node) {
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->sprite == node) {
            bool dead = enemies[i]->getHit();
            if (dead) {
                dropBuff(enemies[i]->sprite->getPosition());
                int score = enemies[i]->getScore();
                scene->removeChild(node);
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                return score;
            }
            CCLOG("hsajdklhfjsdhjfhsjkdfa getHit size = %d", enemies.size());
            return 0;
        }
    }
}

void EnemyController::startShootingBack() {
    auto delay = DelayTime::create(shotDelay);
    auto func = CallFunc::create(CC_CALLBACK_0(EnemyController::shootBack, this));
    auto seq = Sequence::create(delay, func, NULL);
    auto action = RepeatForever::create(seq);
    scene->runAction(action);
}

void EnemyController::shootBack() {
    if (enemies.empty()) {
        return;
    }
    auto shooter = enemies[std::rand() % enemies.size()];
    std::string projFile;
    if (stage == 0) {
        projFile = "BadBullet.png";
    }
    else {
        projFile = "BadBullet2.png";
    }
    auto projectile = Sprite::create(projFile);
    projectile->setPosition(shooter->sprite->getPosition());

    auto projectileBody = PhysicsBody::createCircle(projectile->getContentSize().width / 2,
                                                    PHYSICSBODY_MATERIAL_DEFAULT);
    projectileBody->setDynamic(false);
    projectileBody->setCollisionBitmask(EnemyController::projectileCollisionBitmask);
    projectileBody->setContactTestBitmask(true);
    projectile->setPhysicsBody(projectileBody);

    scene->addChild(projectile);

    auto move = MoveBy::create(shotDuration / 3 * 2, shotDirection);
    auto removeSelf = RemoveSelf::create();
    projectile->runAction(Sequence::create(move, removeSelf, NULL));
}

void EnemyController::checkOffScreen() {
    if (enemies.empty()) {
        ((GamePlay*)scene)->next();
        return ;
    }
    for (int i = enemies.size() - 1; i >= 0; --i) {
        if (enemies[i]->sprite->getPosition().y < 0) {
            scene->removeChild(enemies[i]->sprite);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            if (enemies.empty()) {
                ((GamePlay*)scene)->next();
                return ;
            }
            return ;
        }
    }
    CCLOG("hsajdklhfjsdhjfhsjkdfa check off screen, size = %d", enemies.size());
}

void EnemyController::dropBuff(cocos2d::Point pos) {
    if (std::rand() % 100 < 100) {
        std::string buffName = "Life";
        if (std::rand() % 100 < 50) {
            buffName = "Upgrade";
        }
        else {
            buffName = "Life";
        }

        auto buff = Sprite::create(buffName + ".png");
        buff->retain();
        buff->setPosition(pos);

        scene->addChild(buff);

        auto wait = DelayTime::create(0.1);
        auto func = CallFunc::create(CC_CALLBACK_0(EnemyController::test, this, buff, buffName));
        auto move = MoveBy::create(10, Point(0, -100));
        auto removeSelf = RemoveSelf::create();
        buff->runAction(Sequence::create(wait, func, move, removeSelf, NULL));
    }
}

void EnemyController::test(cocos2d::Sprite * buff, std::string buffName) {
    auto buffBody = PhysicsBody::createCircle(buff->getContentSize().width / 4, PHYSICSBODY_MATERIAL_DEFAULT);
    buffBody->setDynamic(false);
    buffBody->setCollisionBitmask(EnemyController::buffCollisionBitmask);
    //buffBody->setCollisionBitmask(128);
    buffBody->setContactTestBitmask(true);
    buff->setPhysicsBody(buffBody);
    buff->setName(buffName);
}

