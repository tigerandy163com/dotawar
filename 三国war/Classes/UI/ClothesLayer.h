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
    KuZi,
    YaoDai
}CLOSETYPE ;
class ClothesLayer:public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(ClothesLayer);
    Item* m_MaoZiBtn;
    Item* m_YiFuBtn;
    Item* m_XieZiBtn;
    Item* m_ShouTaoBtn;
    Item* m_KuZiBtn;
    Item* m_YaoDaiBtn;
};
#endif /* defined(____war__ClothesLayer__) */
