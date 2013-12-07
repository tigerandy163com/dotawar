#pragma once

#ifndef _H_CCGAMESCROLLVIEW_H_
#define _H_CCGAMESCROLLVIEW_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

// 校正滑动动画速度
#define ADJUST_ANIM_VELOCITY 2000

class CCCGameScrollViewDelegate
	: public cocos2d::extension::CCScrollViewDelegate
{
public:
	virtual bool scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage) = 0;
	virtual void scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage ) = 0;
	virtual void scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage) = 0;
    
    virtual void scrollViewTouchBegan(cocos2d::CCNode *pScroll,CCPoint pos )=0;
    
	virtual void scrollViewTouchMoved( cocos2d::CCNode *pScroll,CCPoint pos)=0;
    
	virtual void scrollViewTouchEnded( cocos2d::CCNode *pScroll,CCPoint pos)=0;
    
	virtual void scrollViewTouchCancelled(cocos2d::CCNode *pScroll,CCPoint pos)=0;
    
};

class CCCGameScrollView
	: public cocos2d::extension::CCScrollView
{
public:
	CCCGameScrollView();
	~CCCGameScrollView();
public:
	CREATE_FUNC(CCCGameScrollView);

	bool init();

	bool createContainer(CCCGameScrollViewDelegate *pDele, int nCount, const cocos2d::CCSize &oSize );

	virtual bool ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

	virtual void setDirection(CCScrollViewDirection eDirection);

	void setCurPage(int nPage);
	void scrollToPage(int nPage);
	void scrollToNextPage();
	void scrollToPrePage();
	int getPageCount();
	int getCurPage();
	CCNode *getPage(int nPage);
protected:
	void adjustScrollView(const cocos2d::CCPoint &oBegin, const cocos2d::CCPoint &oEnd);

	virtual void onScrollEnd(float fDelay);
protected:
    virtual void registerWithTouchDispatcher()
    {
        //使用-128和CCMenu优先级相同,并且吞掉事件true//
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
       // CCLayer::registerWithTouchDispatcher();
    }
	int m_nPageCount;
	int m_nPrePage;
	cocos2d::CCPoint m_BeginOffset;
	cocos2d::CCSize m_CellSize;
	float m_fAdjustSpeed;
	bool m_bSetDirection;
	int m_nCurPage;
};

#endif

