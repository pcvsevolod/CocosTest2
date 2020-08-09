#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlay::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);*/

    spaceShip.create(this, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    ec = new EnemyController(this);
    ec->place1();

    initTouch();
    initCollision();
    initUpdate();


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
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

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

GamePlay::~GamePlay() {
    delete ec;
}
