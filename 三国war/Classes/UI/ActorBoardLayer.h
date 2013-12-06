//
//  ActorBoardLayer.h
//  三国war
//
//  Created by chunyu.wang on 13-12-2.
//
//

#ifndef ____war__ActorBoardLayer__
#define ____war__ActorBoardLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "HTabGroupLayerBase.h"
#include "BagLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
class ActorBoardLayer:public CCLayer,public TabDelegate
{
public:
      ActorBoardLayer();
    ~ActorBoardLayer();
    bool init();
    
    CREATE_FUNC(ActorBoardLayer);
   virtual CCNode* viewTabIndex(CCNode* pTabLayer,int index);
   virtual bool tabViewInitPage( CCNode* pTabLayer,cocos2d::CCNode *pPage, int nPage);
  virtual  void tabItemClick(CCNode* pTabLayer,CCNode* object);
    void closeMe();
private:
    HTabGroupLayerBase* m_Htab;
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    
};
#endif /* defined(____war__ActorBoardLayer__) */
