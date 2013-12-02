//
//  BagLayer.h
//  三国war
//
//  Created by chunyu.wang on 13-11-28.
//
//

#ifndef ____war__BagLayer__
#define ____war__BagLayer__

#include <iostream>
#include "cocos2d.h"
#include "CCGameScrollView.h"
USING_NS_CC;
class BagLayer:public CCCGameScrollViewDelegate,public CCLayer
{
public:
    BagLayer();
    ~BagLayer();
 
    virtual bool init();
	virtual bool scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage);
	virtual void scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage );
	virtual void scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    CREATE_FUNC(BagLayer);
    void ItemDidClick(CCNode* pNode);
private:
    CCCGameScrollView* m_ScrollView;
    CCSize itemSize;
    CCSize itemSizeWithMargin;
    CC_SYNTHESIZE(int, m_ItemCount, ItemCount);
    void nodeDidClick(CCNode* pNode,const CCPoint& clickPos);
private:
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
     virtual void registerWithTouchDispatcher();
};
#endif /* defined(____war__BagLayer__) */
