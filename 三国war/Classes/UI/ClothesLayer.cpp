//
//  ClothesLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-12-5.
//
//

#include "ClothesLayer.h"


bool ClothesLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSprite* bgsprite = CCSprite::create("Player0Large.png");
        bgsprite->setPosition(CCPointZero);
        addChild(bgsprite);
        
        
        bRet = true;
    } while (0);
    return bRet;
}