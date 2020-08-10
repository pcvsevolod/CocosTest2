#ifndef __GAMEWON_SCENE_H__
#define __GAMEWON_SCENE_H__

#include "cocos2d.h"

class GameWon : public cocos2d::Scene {
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    static cocos2d::Scene *createScene();
    virtual bool init();

    void menuReplayCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameWon);

};


#endif //__GAMEWON_SCENE_H__
