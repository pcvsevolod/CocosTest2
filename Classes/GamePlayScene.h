#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref *pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __GAMEPLAY_SCENE_H__
