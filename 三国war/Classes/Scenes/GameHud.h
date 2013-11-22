//
//  GameHud.h
//  三国war
//
//  Created by chunyu.wang on 13-11-13.
//
//

#ifndef ____war__GameHud__
#define ____war__GameHud__

#include <iostream>
#include "cocos2d.h"
#include "ActorData.h"

USING_NS_CC;
class GameHud:public CCLayer
{
public:
    virtual bool init();
   
   static  GameHud* shareGameHud();
    CREATE_FUNC(GameHud);
    void soldier1_Select(CCNode *pSender);
    void soldier2_Select(CCNode *pSender);
    void soldier3_Select(CCNode *pSender);
    void soldier4_Select(CCNode *pSender);
    void click_attack(CCNode *pSender);
    void click_addSoldier(CCNode *pSender);
    void giveMeALife();
    void countDown();
    void hidenReLive();
    void showReLive();
    string selectID;
    ActorPro selectPro;
    CCLabelTTF* timerLab;
    CCSprite* selectFlag;
    CCLayer* bottomLayer;
    int count;
    void showBottomMenu();
     void unShowBottomMenu();
    void addLeftHead(const  char* name);
    void addRightHead(const char* name );
    void selMyHead();
    void selEnemyHead();
    void addMask();
    bool isShowing;
    CC_SYNTHESIZE(bool, _heroSel, HeroSel);


};
#endif /* defined(____war__GameHud__) */
