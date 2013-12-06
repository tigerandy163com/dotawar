//
//  HTabGroupLayerBase.cpp
//  三国war
//
//  Created by sven on 13-11-30.
//
//

#include "HTabGroupLayerBase.h"

HTabGroupLayerBase::HTabGroupLayerBase()
:m_count(0)
,m_curSel(-1)
,m_TabsArray(NULL)
{
    
}
HTabGroupLayerBase::~HTabGroupLayerBase()
{
    CC_SAFE_RELEASE_NULL(m_TabsArray);
    CC_SAFE_RELEASE_NULL(m_IndexLayersArray);
}

bool HTabGroupLayerBase::init()
{
    bool bRet =false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        m_TabsArray = CCArray::create();
        m_TabsArray->retain();
        m_IndexLayersArray = CCArray::create();
        m_IndexLayersArray->retain();
        bRet = true;
    } while (0);
    return bRet;
}

bool HTabGroupLayerBase::creatTabsWithCount(TabDelegate* pDelegate,int var,TabAlignDir dir,CCSize frame)

{
    bool bRet = false;
    if (var>0) {
        m_count = var;
        setDelegate(pDelegate);
        setAlignDir(dir);
        setContentSize(frame);
        
        for (int i = 0; i < m_count; ++i)
        {
            CCMenuItemSprite* menuItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("btn_level1.png"), CCSprite::createWithSpriteFrameName("btn_level2.png"), this, menu_selector(HTabGroupLayerBase::tabItemClick));
            //menuItem->setAnchorPoint(ccp(0,0));
            CCMenu *menu = CCMenu::createWithItem(menuItem);
            menu->setAnchorPoint(ccp(0,0));
            CCPoint pos;
            if (m_AlignDir==AlignLeft) {
                pos = ccp(50,150);
            }else if (m_AlignDir==AlignRight)
                pos = ccp(frame.width-300 ,150);
            pos.y += 100*i;
            
            menu->setPosition(pos);
            menuItem->setTag(i);
            pDelegate->tabViewInitPage(this,menu, i);
            this->addChild(menu);
            
            CCNode* indexView = pDelegate->viewTabIndex(this, i);
        
            indexView->setPosition(200, 0);
            this->addChild(indexView, i,i);
            
            m_IndexLayersArray->addObject(indexView);
            m_TabsArray->addObject(menu);
        }
        
        bRet = true;
    }
    selectItemIndex(0);
    return bRet;
}
void HTabGroupLayerBase::tabItemClick(cocos2d::CCNode *pSender)
{
    CCObject *item;
	CCARRAY_FOREACH(m_TabsArray, item)
	{
		CCMenu *menu= dynamic_cast<CCMenu *>(item);
		menu->setEnabled(true);
	}
    int index =pSender->getTag();
    CCMenu* selMenu = (CCMenu*)m_TabsArray->objectAtIndex(index);
    selMenu->setEnabled(false);
    selectItemIndex(index);
 
}
void HTabGroupLayerBase::selectItemIndex(int index)
{
    CCObject *node;
	CCARRAY_FOREACH(m_IndexLayersArray, node)
	{
		CCNode *mNode= dynamic_cast<CCNode *>(node);
		mNode->setVisible(false);
        
	}
    CCNode *selNode;
    m_curSel = index;
    selNode = (CCNode*)m_IndexLayersArray->objectAtIndex(m_curSel);
    selNode->setVisible(true);
   
}
