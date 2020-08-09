#include "EnemyController.h"

USING_NS_CC;

#include "BasicEnemy.h"

void EnemyController::place1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::vector<Point> badPositions;

    for (int i = 0; i <4; ++i){
        for (int j = 1; j < 7; ++j) {
            badPositions.emplace_back(visibleSize.width / 2 + origin.x - j * 8, visibleSize.height / 8 * 7 + origin.y - i * 8);
            badPositions.emplace_back(visibleSize.width / 2 + origin.x + j * 8, visibleSize.height / 8 * 7 + origin.y - i * 8);
        }
        badPositions.emplace_back(visibleSize.width / 2 + origin.x, visibleSize.height / 8 * 7 + origin.y - i * 8);
    }
    for (auto & bp : badPositions) {
        auto enemy = new BasicEnemy(scene, bp);
        enemies.push_back(enemy);
    }
}

EnemyController::EnemyController(cocos2d::Scene * scene) {
    this->scene = scene;
}

void EnemyController::getHit(cocos2d::Node *node) {
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->sprite == node) {
            bool dead = enemies[i]->getHit();
            if (dead) {
                scene->removeChild(node);
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
            }
        }
    }
}
