#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "cocos2d.h"
using namespace cocos2d;

class SceneGame : public CCLayer
{
public :
    virtual bool init();
    static CCScene *Scene();
    CREATE_FUNC(SceneGame);

private :
	void click_attack(CCObject* pSender);
};

#endif