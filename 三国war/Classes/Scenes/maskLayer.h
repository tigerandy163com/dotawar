//
//  maskLayer.h
//  三国war
//
//  Created by chunyu.wang on 13-11-15.
//
//

#ifndef ____war__maskLayer__
#define ____war__maskLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class MaskLayer:public CCLayerColor
{
public:
    virtual bool init();
     
    CREATE_FUNC(MaskLayer);
private:
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
};
#endif /* defined(____war__maskLayer__) */
