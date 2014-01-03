//
//  ClothesLayer.h
//  三国war
//
//  Created by chunyu.wang on 13-12-5.
//
//

#ifndef ____war__ClothesLayer__
#define ____war__ClothesLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Item;
typedef enum
{
    MaoZi =0,
    YiFu,
    XieZi,
    ShouTao,
    WuQi,
    KuZi
}CLOThESTYPE ;
class ClothesLayer:public CCLayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(ClothesLayer);
    Item* getClothesItem(CLOThESTYPE typeName);
   void setClothesItem(Item* var,CLOThESTYPE type);
    virtual void onEnter();
    virtual void onExit();
    ~ClothesLayer();
    ClothesLayer();
    CCArray* itemsArr;
private:
    Item* selectItem;
    Item* m_MaoZi;
    Item* m_YiFu;
    Item* m_XieZi;
    Item* m_ShouTao;
    Item* m_WuQi;
    Item* m_KuZi;
   
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
};
#endif /* defined(____war__ClothesLayer__) */
