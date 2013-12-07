//
//  Item.h
//  三国war
//
//  Created by chunyu.wang on 13-11-29.
//
//

#ifndef ____war__Item__
#define ____war__Item__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Item:public CCNode
{
public:
    Item();
    ~Item();
    virtual bool init();
    static Item* Create(int id_var,int lev_var,int count_var);
    bool initWithItemID(int id_var,int lev_var,int count_var);
    CREATE_FUNC(Item);
    CCSprite* m_Sprite;
    CC_SYNTHESIZE(int, m_ID, ItemID);
    CC_SYNTHESIZE(const char*, m_Name, Name);
    CC_SYNTHESIZE(int, m_Level, Level);
    CC_SYNTHESIZE(const char*, m_Info, Info);
    CC_SYNTHESIZE(int, m_Cost, Cost);
    CC_SYNTHESIZE(int, m_Count, Count);
    void selectItem(bool var);
     bool itemTouchBegan();
     void itemTouchMoved() ;
     void itemTouchEnded();
     void itemTouchCancelled();

    void checkLongPress();
    void singleClickSprite();
    void doubleClickSprite();
protected:
    bool isSelect;
    CCSprite* NBackGroundSprite;
    CCSprite* SBackGroundSprite;

    bool isInSprite(CCTouch *theTouch);
    bool isInTouch;
    bool isInMove;
    bool afterLongPress;
    bool afterDoublePress;
    long touchBeginTime;
    CCPoint orignalPoint;
};
#endif /* defined(____war__Item__) */
