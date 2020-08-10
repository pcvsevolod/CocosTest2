#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene {
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    static cocos2d::Scene *createScene();
    virtual bool init();

    void menuReplayCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameOver);

};


#endif //__GAMEOVER_SCENE_H__
