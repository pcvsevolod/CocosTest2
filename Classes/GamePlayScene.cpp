#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlay::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = GamePlay::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GamePlay::init() {
    if (!Scene::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /*auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);*/

    spaceShip.create(this, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    ec = new EnemyController(this);
    ec->place1();
    ec->startShootingBack();

    initTouch();
    initCollision();
    initUpdate();
    initLabel();
    initCheckOffScreen();



    return true;
}

bool GamePlay::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    CCLOG("hsajdklhfjsdhjfhsjkdfa");
    touched = true;
    touchPoint = Point(touch->getLocation().x, touch->getLocation().y);
    spaceShip.startShooting();

    return true;
}

bool GamePlay::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    CCLOG("hsajdklhfjsdhjfhsjkdfa moving");
    touched = true;
    touchPoint = Point(touch->getLocation().x, touch->getLocation().y);

    return true;
}

bool GamePlay::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    touched = false;
    spaceShip.stopShooting();

    return true;
}

void GamePlay::update(float delta) {
    if(touched){
        //moveShip(shipSpeed, touchPoint, delta);
        spaceShip.move(touchPoint, delta);
    }
}

bool GamePlay::onContactBegin(cocos2d::PhysicsContact &contact) {
    CCLOG("hsajdklhfjsdhjfhsjkdfa HITHITHIT");
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    CCLOG("hsajdklhfjsdhjfhsjkdfa a = %d", a->getCollisionBitmask());
    CCLOG("hsajdklhfjsdhjfhsjkdfa b = %d", b->getCollisionBitmask());

    if(EnemyController::collisionBitmask == a->getCollisionBitmask() && SpaceShip::projectileCollisionBitmask == b->getCollisionBitmask()){
        CCLOG("hsajdklhfjsdhjfhsjkdfa enemy hit");
        ec->getHit(a->getNode());
        this->removeChild(b->getNode());
    }
    if(EnemyController::collisionBitmask == b->getCollisionBitmask() && SpaceShip::projectileCollisionBitmask == a->getCollisionBitmask()){
        CCLOG("hsajdklhfjsdhjfhsjkdfa enemy hit");
        ec->getHit(b->getNode());
        this->removeChild(a->getNode());
    }

    if(EnemyController::projectileCollisionBitmask == a->getCollisionBitmask() && SpaceShip::collisionBitmask == b->getCollisionBitmask()){
        CCLOG("hsajdklhfjsdhjfhsjkdfa spaceship hit");
        spaceShip.getHit();
        this->removeChild(a->getNode());
        updateLabel();
    }
    if(EnemyController::projectileCollisionBitmask == b->getCollisionBitmask() && SpaceShip::collisionBitmask == a->getCollisionBitmask()){
        CCLOG("hsajdklhfjsdhjfhsjkdfa spaceship hit");
        spaceShip.getHit();
        this->removeChild(b->getNode());
        updateLabel();
    }

    return true;
}

void GamePlay::initTouch() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GamePlay::initCollision() {
    auto contactListeneer = EventListenerPhysicsContact::create();
    contactListeneer->onContactBegin = CC_CALLBACK_1(GamePlay::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListeneer, this);

}

void GamePlay::initUpdate() {
    this->scheduleUpdate();
}

void GamePlay::initLabel() {
    livesLabel = Label::createWithTTF("Lives = " + std::to_string(spaceShip.lives), "fonts/Marker Felt.ttf", 12);
    livesLabel->setPosition(Vec2(origin.x + visibleSize.width / 10 * 2,
                                 origin.y + visibleSize.height - livesLabel->getContentSize().height));
    this->addChild(livesLabel, 1);
}

GamePlay::~GamePlay() {
    delete ec;
}

void GamePlay::updateLabel() {
    livesLabel->setString("Lives = " + std::to_string(spaceShip.lives));
    if(spaceShip.lives <= 0) {
        livesLabel->setString("Game Over");
        //auto scene = GameOverScene::createScene();
        //Director::getInstance()->replaceScene(scene);
    }
}

void GamePlay::checkEnemiesOffScreen() {
    ec->checkOffScreen();
}

void GamePlay::initCheckOffScreen() {
    auto delay = DelayTime::create(1);
    auto func = CallFunc::create(CC_CALLBACK_0(GamePlay::checkEnemiesOffScreen, this));
    auto seq = Sequence::create(delay, func, NULL);
    auto rep = RepeatForever::create(seq);
    this->runAction(rep);
}
