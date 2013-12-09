//
//  ActorBoardLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-12-2.
//
//

#include "ActorBoardLayer.h"
#include "GameHud.h"
#include "ClothesLayer.h"
ActorBoardLayer::ActorBoardLayer()
{
    
}
ActorBoardLayer::~ActorBoardLayer()
{
    
}
//bool ActorBoardLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
//    return true;
//}
//void ActorBoardLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
//{
//    
//}
//void ActorBoardLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
//{
//    
//}
//void ActorBoardLayer::registerWithTouchDispatcher()
//{
//    //使用-128和CCMenu优先级相同,并且吞掉事件true//
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -127, true);
//   // CCLayer::registerWithTouchDispatcher();
//}
void ActorBoardLayer::tabItemClick(cocos2d::CCNode *pTabLayer, cocos2d::CCNode *object)
{
    
}


CCNode* ActorBoardLayer::viewTabIndex(CCNode* pTabLayer,int index)
{
    CCNode* node = NULL;
    switch (index) {
        case 0:
        {
          //  node = BagLayer::create();
            CCSize winsize = CCDirector::sharedDirector()->getWinSize();
            ClothesLayer* layer1 = ClothesLayer::create();
            BagLayer* layer2 = BagLayer::create();
            node = CCNode::create();
          
            node->addChild(layer1);
            layer1->setAnchorPoint(ccp(0,0));
            layer1->setPosition(ccp(50, winsize.height/3));
            node->addChild(layer2);
            
            layer2->setPosition(layer1->boundingBox().size.width+150,0);
 
            
        }
            break;
        case 1:
            node = CCLabelTTF::create(
                         "1 page", "Arial", 22);
            break;
        case 2:
            node = CCLabelTTF::create(
                                      "2 page", "Arial", 22);
            break;
        case 3:
            node = CCLabelTTF::create(
                                      "3 page", "Arial", 22);
            break;
        default:
            node = CCLabelTTF::create(
                                      "no page", "Arial", 22);
            break;
    }
    node->retain();
    return node;
}
bool ActorBoardLayer::tabViewInitPage( CCNode* pTabLayer,cocos2d::CCNode *pPage, int nPage)
{
    char str[64] = {0};
    sprintf(str, "%d", nPage);
    CCMenuItem* menuitem = CCMenuItem::create();
    CCLabelTTF* text = CCLabelTTF::create(
                                          str, "Arial", 22);
    text->setAnchorPoint(CCPointZero);
    text->setColor(ccBLACK);
    menuitem->addChild(text);
    pPage->addChild(menuitem);
    return true;
}

bool ActorBoardLayer::init()
{
    bool bRet =false;
    do {
        CC_BREAK_IF(!CCLayer::init());
         setTouchEnabled(true);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite* background = CCSprite::createWithSpriteFrameName("bg_over.png");
        background->setAnchorPoint(ccp(0, 0));
        this->addChild(background);
        CCSize size1 = background->getContentSize();
        float scale1 = winSize.width/size1.width;
        float scale2 = winSize.height/size1.height;
        background->setScaleX(scale1);
        background->setScaleY(scale2);
        
        CCMenuItemFont *add = CCMenuItemFont::create("关闭", this, menu_selector(ActorBoardLayer::closeMe));
        
        add->setPosition(CCPointZero);
        add->setFontSizeObj(35);
        add->setColor(ccRED);
        CCMenu *menu0 = CCMenu::createWithItem(add);
        menu0->setPosition( winSize.width-150, winSize.height-100);
        this->addChild(menu0);
        
        m_Htab = HTabGroupLayerBase::create();
        m_Htab->creatTabsWithCount(this, 4,AlignLeft,winSize);
        m_Htab->setAnchorPoint(CCPointZero);
        m_Htab->setPosition(0, 0);
        this->addChild(m_Htab);
        
        bRet = true;
    } while (0);
    return bRet;
}
void ActorBoardLayer::closeMe()
{
    GameHud::shareGameHud()->enableAllHeroMenu();
    this->removeFromParent();
}