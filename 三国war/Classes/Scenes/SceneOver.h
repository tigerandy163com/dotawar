#ifndef _SCENE_OVER_H_
#define _SCENE_OVER_H_

#include "cocos2d.h"
using namespace cocos2d;

class SceneOver : public CCLayer
{
public :
    virtual bool init();
    static CCScene *Scene();
    CREATE_FUNC(SceneOver);
private :
	void click_back(CCObject* pSender);
};

#endif