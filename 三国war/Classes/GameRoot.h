#ifndef _GAME_ROOT_H_
#define _GAME_ROOT_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "SceneStart.h"
#include "SceneSelect.h"
#include "SceneGame.h"
#include "SceneOver.h"
extern float ScaleX;
extern float ScaleY;
class GameRoot:public CCObject
{
public :
    ~GameRoot();
    virtual bool init();
    static GameRoot* shareGameRoot();
	void InitializeResource();
	SceneStart* getSceneStart();
	SceneSelect* getSceneSelect();
	SceneGame* getSceneGame();
	SceneOver* getSceneOver();
    bool resetSceneGame();
    void addSpriteTag();
    void startGame();
    CC_SYNTHESIZE(int, _spriteTag , spriteTag);
    CC_SYNTHESIZE_RETAIN( CCArray *, _actorArrL, actorArrL);
    CC_SYNTHESIZE_RETAIN( CCArray *, _actorArrR,actorArrR);
    CC_SYNTHESIZE(bool, _hasStart, hasStart);
    CC_SYNTHESIZE_RETAIN( CCArray *, _TowerArrL, TowerArrL);
    CC_SYNTHESIZE_RETAIN( CCArray *, _TowerArrR,TowerArrR);
    int getLiveActors(int var);
    int getLiveTowers(int var);

};

#endif