//
//  maskLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-15.
//
//

#include "MaskLayer.h"

bool MaskLayer::init()
{
    bool ret = false;
    do {
          CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100)));
        this->setTouchEnabled(true);
        ret = true;
    } while (0);
    return ret;
}
bool MaskLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
    return true;
}
void MaskLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
    
}
void MaskLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    
}
void MaskLayer::registerWithTouchDispatcher()
{
    //使用-128和CCMenu优先级相同,并且吞掉事件true//
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
 //   CCLayer::registerWithTouchDispatcher();
}