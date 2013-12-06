//
//  HTabGroupLayerBase.h
//  三国war
//
//  Created by sven on 13-11-30.
//
//

#ifndef ____war__HTabGroupLayerBase__
#define ____war__HTabGroupLayerBase__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class TabDelegate
{
public:
    virtual bool tabViewInitPage( CCNode* pTabLayer,cocos2d::CCNode *pPage, int nPage) = 0;
    virtual CCNode* viewTabIndex(CCNode* pTabLayer,int index)=0;
    virtual void tabItemClick(CCNode* pTabLayer,CCNode* object)=0;
};
typedef enum{
    AlignLeft=0,
    AlignRight
}TabAlignDir ;
class HTabGroupLayerBase:public CCLayer
{
public:
    HTabGroupLayerBase();
    ~HTabGroupLayerBase();
public:
    CREATE_FUNC(HTabGroupLayerBase);
    CC_SYNTHESIZE(TabAlignDir, m_AlignDir, AlignDir);
    bool init();
    bool creatTabsWithCount(TabDelegate* pDelegate,int var,TabAlignDir dir,CCSize frame);
private:
    CCArray* m_TabsArray;
    CCArray* m_IndexLayersArray;
    int m_curSel;
    int m_count;
    CC_SYNTHESIZE(TabDelegate*, m_pDelegate, Delegate);
    void tabItemClick(CCNode* object);
    void selectItemIndex(int index);
};
#endif /* defined(____war__HTabGroupLayerBase__) */
