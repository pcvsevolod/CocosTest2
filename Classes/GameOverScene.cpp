#include "GameOverScene.h"

USING_NS_CC;

#include "GamePlayScene.h"

Scene *GameOver::createScene( ) {
    return GameOver::create();
}

static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOver::init() {
    if (!Scene::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
            "Retry.png",
            "Retry.png",
            CC_CALLBACK_1(GameOver::menuReplayCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'Retry.png'");
    } else {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("You lost! \n Score: " + std::to_string(UserDefault::getInstance()->getIntegerForKey("score")), "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    } else {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }


    return true;
}


void GameOver::menuReplayCallback(Ref *pSender) {
    auto scene = GamePlay::createScene();
    Director::getInstance()->replaceScene(scene);
}
