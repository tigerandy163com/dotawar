#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_
#include "ActorBase.h"
#include "cocos2d.h"

using namespace cocos2d;
class GameRoot;
class SceneGame : public CCLayer
{
public :
    ~SceneGame();
    virtual bool init();
    static CCScene *Scene();
  
//    void onExit();
    CREATE_FUNC(SceneGame);
    GameRoot* GR;
    void addSoldier(CCPoint pos,const char* soldierId,ActorType type,ActorPro pro);
        bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CCTMXTiledMap* _map;
    cocos2d::CCTMXObjectGroup *_objects;
    cocos2d::CCTMXLayer* _bg1layer;
    CCTMXObjectGroup* _touchObj;
    void removeMask();
    void hidenAimSprite();
     CCSprite* _aimSprite;
    bool aimState;
private :
	void click_attack(CCObject* pSender);
    
};

#endif