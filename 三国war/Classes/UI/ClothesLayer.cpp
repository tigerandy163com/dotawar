//
//  ClothesLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-12-5.
//
//

#include "ClothesLayer.h"
#include "Item.h"
#include "Helper.h"
void ClothesLayer::onEnter()
{
    
}
void ClothesLayer::onExit()
{

}
ClothesLayer:: ClothesLayer()
{
    
}
ClothesLayer::~ClothesLayer()
{
    CC_SAFE_RELEASE_NULL(m_WuQi);
    CC_SAFE_RELEASE_NULL(m_MaoZi);
    CC_SAFE_RELEASE_NULL(m_YiFu);
    CC_SAFE_RELEASE_NULL(m_KuZi);
    CC_SAFE_RELEASE_NULL(m_ShouTao);
    CC_SAFE_RELEASE_NULL(m_XieZi);
    CC_SAFE_RELEASE_NULL(itemsArr);
}
bool ClothesLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(100, 100, 250, 200)));
        CCLayer:: setTouchEnabled(true);
        
        CCSprite* bgsprite = CCSprite::create("Player0Large.png");
        bgsprite->setPosition( ccp(10,0));
        bgsprite->setAnchorPoint(CCPointZero);
        addChild(bgsprite);
       // bgsprite->setScale(0.8);
        CCSize bgsize = bgsprite->boundingBox().size;
//        bgsize.height *=1.5;
//        bgsize.width *=1.5;
        setContentSize(bgsize);
        CCSize asize = CCSprite::create("Maozhi.jpg")->boundingBox().size;
        
        m_MaoZi = Item::Create(100, 10, 1, NULL, CCSprite::create("Maozhi.jpg"),  CCSprite::create("Maozhi.jpg"));
        m_MaoZi->setAnchorPoint(CCPointZero);
        m_MaoZi->setPosition(0,boundingBox().size.height-asize.height);
        addChild(m_MaoZi);
        m_MaoZi->retain();
        
        m_YiFu = Item::Create(100, 110, 1, NULL, CCSprite::create("Yifu.jpg"),  CCSprite::create("Yifu.jpg"));
        m_YiFu->setAnchorPoint(CCPointZero);
        m_YiFu->setPosition(0, m_MaoZi->getPositionY() - asize.height-50);
        addChild(m_YiFu);
        m_YiFu->retain();
       
        m_XieZi = Item::Create(100, 111, 1, NULL, CCSprite::create("Xiezhi.jpg"),  CCSprite::create("Xiezhi.jpg"));
        m_XieZi->setAnchorPoint(CCPointZero);
        m_XieZi->setPosition(0, m_YiFu->getPositionY() - asize.height-50);
        addChild(m_XieZi);
        m_XieZi->retain();
        
        
        m_WuQi = Item::Create(100, 112, 1, NULL, CCSprite::create("Wuqi.jpg"),  CCSprite::create("Wuqi.jpg"));
        m_WuQi->setAnchorPoint(CCPointZero);
        m_WuQi->setPosition(boundingBox().size.width - asize.width, boundingBox().size.height-asize.height);
        addChild(m_WuQi);
        m_WuQi->retain();
        
        m_ShouTao = Item::Create(100, 113, 1, NULL, CCSprite::create("Shoutao.jpg"),  CCSprite::create("Shoutao.jpg"));
        m_ShouTao->setAnchorPoint(CCPointZero);
        m_ShouTao->setPosition(boundingBox().size.width - asize.width, m_WuQi->getPositionY()-asize.height-50);
        addChild(m_ShouTao);
        m_ShouTao->retain();
        
        m_KuZi = Item::Create(100, 114, 1, NULL, CCSprite::create("Kuzhi.jpg"),  CCSprite::create("Kuzhi.jpg"));
        m_KuZi->setAnchorPoint(CCPointZero);
        m_KuZi->setPosition(boundingBox().size.width - asize.width, m_ShouTao->getPositionY()-asize.height-50);
        addChild(m_KuZi);
        m_KuZi->retain();
        
        itemsArr = CCArray::create(m_MaoZi,m_WuQi,m_YiFu,m_ShouTao,m_KuZi,m_XieZi,NULL);
        itemsArr->retain();
      //  registerWithTouchDispatcher();
        bRet = true;
    } while (0);
    return bRet;
}

Item* ClothesLayer::getClothesItem(CLOThESTYPE typeName)
{
    Item* rItem =NULL;
    switch (typeName) {
        case MaoZi:
            rItem = m_MaoZi;
            break;
        case WuQi:
            rItem = m_WuQi;
            break;
        case ShouTao:
            rItem = m_ShouTao;
            break;
        case YiFu:
            rItem = m_YiFu;
            break;
        case XieZi:
            rItem = m_XieZi;
            break;
        case KuZi:
            rItem = m_KuZi;
            break;
        default:
            break;
    }
    return rItem;
}

void ClothesLayer::setClothesItem(Item *var, CLOThESTYPE type)
{
    Item* rItem =NULL;
    switch (type) {
        case MaoZi:
        {
            rItem = m_MaoZi;
            
        }
            break;
        case WuQi:
            rItem = m_WuQi;
            break;
        case ShouTao:
            rItem = m_ShouTao;
            break;
        case YiFu:
            rItem = m_YiFu;
            break;
        case XieZi:
            rItem = m_XieZi;
            break;
        case KuZi:
            rItem = m_KuZi;
            break;
        default:
            break;
    }
    CC_SAFE_RELEASE_NULL(rItem);
    rItem = var;
    rItem->retain();
}

 bool  ClothesLayer:: ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    selectItem = (Item*)Helper::getTouchItem(itemsArr, touchPoint);
    if (selectItem) {
        CCLog("touch:%d",selectItem->getLevel());
        selectItem->itemTouchBegan();
    }
    return true;
}
 void ClothesLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
    if (selectItem) {
        
        selectItem->itemTouchMoved();
    }
   
}
 void ClothesLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    if (selectItem) {
        
        selectItem->itemTouchEnded();
    }

}
 void ClothesLayer::registerWithTouchDispatcher()
{
      CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

