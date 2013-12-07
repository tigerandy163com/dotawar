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
#include "HTabGroupLayerBase.h"
USING_NS_CC;
class Item;
class BagLayer:public CCCGameScrollViewDelegate,public CCLayer,public TabDelegate
{
public:
    BagLayer();
    ~BagLayer();
 
    virtual bool init();
	virtual bool scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage);
	virtual void scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage );

    virtual void scrollViewTouchBegan(cocos2d::CCNode *pScroll, CCPoint pos);
    
	virtual void scrollViewTouchMoved(cocos2d::CCNode *pScroll, CCPoint pos);
    
	virtual void scrollViewTouchEnded(cocos2d::CCNode *pScroll,CCPoint pos );
    
	virtual void scrollViewTouchCancelled(cocos2d::CCNode *pScroll,CCPoint pos);
    
    
	virtual void scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual CCNode* viewTabIndex(CCNode* pTabLayer,int index);
    virtual bool tabViewInitPage( CCNode* pTabLayer,cocos2d::CCNode *pPage, int nPage);
    virtual  void tabItemClick(CCNode* pTabLayer,CCNode* object);
    
    

    CREATE_FUNC(BagLayer);
    void ItemDidClick(CCNode* pNode);
private:
    Item* selectItem;
    HTabGroupLayerBase* m_Htab;
    CCCGameScrollView* m_ScrollView;
    CCSize itemSize;
    CCSize itemSizeWithMargin;
    CC_SYNTHESIZE(int, m_ItemCount, ItemCount);
    void nodeDidClick(CCNode* pNode,const CCPoint& clickPos);
    CCNode* getTouchItem(CCNode* ParentNode,const CCPoint& clickPos);
private:
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
     virtual void registerWithTouchDispatcher();
};
#endif /* defined(____war__BagLayer__) */
