#ifndef _SCENE_START_H_
#define _SCENE_START_H_

#include "cocos2d.h"
using namespace cocos2d;

class SceneStart : public CCLayer
{
public :
    virtual bool init();
   static CCScene *Scene();
    CREATE_FUNC(SceneStart);
    
private :
	void click_start(CCObject* pSender);
	void click_setting(CCObject* pSender);
};

#endif