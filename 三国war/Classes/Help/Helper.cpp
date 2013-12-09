//
//  Helper.cpp
//  三国war
//
//  Created by chunyu.wang on 13-12-9.
//
//

#include "Helper.h"
CCNode* Helper::getTouchItem(CCNode* ParentNode,const CCPoint& clickPos)
{
    
    CCObject* pObj = NULL;
    CCArray* pChildren = ParentNode->getChildren();
    CCNode* rNode = NULL;
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        if(pChild)
        {
            CCRect fra = pChild->boundingBox();
            if (fra.containsPoint(clickPos))
            {
                {
                    rNode = pChild;
                }
                break;
            }
        }
    }
    return rNode;
}

CCNode* Helper::getTouchItem(const CCArray *pChildren, const cocos2d::CCPoint &clickPos)
{
    CCObject* pObj = NULL;
   
    CCNode* rNode = NULL;
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        if(pChild)
        {
            CCRect fra = pChild->boundingBox();
            if (fra.containsPoint(clickPos))
            {
                {
                    rNode = pChild;
                }
                break;
            }
        }
    }
    return rNode;
}