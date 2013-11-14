#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_
#include "ActorBase.h"
#include "cocos2d.h"
using namespace cocos2d;

class SceneGame : public CCLayer
{
public :
    ~SceneGame();
    virtual bool init();
    static CCScene *Scene();
    virtual void addChild(CCNode * child);
    CREATE_FUNC(SceneGame);
   
    void addSoldier(CCPoint pos,const char* soldierId,ActorPro pro);
    CCTMXTiledMap* _map;
    cocos2d::CCTMXObjectGroup *_objects;
    cocos2d::CCTMXLayer* _bg1layer;
private :
	void click_attack(CCObject* pSender);

};

#endif