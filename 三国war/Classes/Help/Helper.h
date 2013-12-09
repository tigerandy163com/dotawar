//
//  Helper.h
//  三国war
//
//  Created by chunyu.wang on 13-12-9.
//
//

#ifndef ____war__Helper__
#define ____war__Helper__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Helper
{
public:
   static   CCNode* getTouchItem(CCNode* ParentNode,const CCPoint& clickPos);
    static   CCNode* getTouchItem(const CCArray* arr,const CCPoint& clickPos);
};
#endif /* defined(____war__Helper__) */
