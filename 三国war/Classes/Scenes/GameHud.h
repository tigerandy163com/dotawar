//
//  GameHud.h
//  三国war
//
//  Created by chunyu.wang on 13-11-13.
//
//

#ifndef ____war__GameHud__
#define ____war__GameHud__
#include "cocos2d.h"
#include "ActorData.h"
#include <iostream>
USING_NS_CC;
class GameHud:public CCLayer
{
public:
    virtual bool init();
   static  GameHud* shareGameHud();
    CREATE_FUNC(GameHud);
    void soldier1_Select();
    void soldier2_Select();
    void soldier3_Select();
    void soldier4_Select();
    void click_attack(CCObject *pSender);
    string selectID;
    ActorPro selectPro;
};
#endif /* defined(____war__GameHud__) */
