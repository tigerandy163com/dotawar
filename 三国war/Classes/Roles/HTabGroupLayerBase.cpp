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
}

bool HTabGroupLayerBase::init()
{
    bool bRet =false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        bRet = true;
    } while (0);
    return bRet;
}

bool HTabGroupLayerBase::creatTabsWithCount(int var)
{
    bool bRet = false;
    if (var<=0) {
        bRet = true;
    }
    
    return bRet;
}
void HTabGroupLayerBase::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    
}
CCTableViewCell* HTabGroupLayerBase::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
}
unsigned int HTabGroupLayerBase::numberOfCellsInTableView(CCTableView *table){
    
}