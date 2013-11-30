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
    virtual bool tabViewInitPage(cocos2d::CCNode *pPage, int nPage) = 0;
};

class HTabGroupLayerBase:public CCLayer,public CCTableViewDelegate,public CCTableViewDataSource
{
public:
    HTabGroupLayerBase();
    ~HTabGroupLayerBase();
    void scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
    {
        
    }
    
    void scrollViewDidZoom(cocos2d::extension::CCScrollView* view)
    {
        
    }
    
    void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(CCTableView *table);
public:
    CREATE_FUNC(HTabGroupLayerBase);
    bool init();
    bool creatTabsWithCount(int var);
private:
    CCArray* m_TabsArray;
    int m_curSel;
    int m_count;
    
};
#endif /* defined(____war__HTabGroupLayerBase__) */
