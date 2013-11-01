#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "cocos2d.h"
using namespace cocos2d;

class SceneGame : public CCLayer
{
public :
    ~SceneGame();
    virtual bool init();
    static CCScene *Scene();
    CREATE_FUNC(SceneGame);
    CCTMXTiledMap* _map;
    cocos2d::CCTMXObjectGroup *_objects;
    cocos2d::CCTMXLayer* _bg1layer;
private :
	void click_attack(CCObject* pSender);

};

#endif