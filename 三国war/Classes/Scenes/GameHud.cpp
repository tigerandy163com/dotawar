//
//  GameHud.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-13.
//
//

#include "GameHud.h"
#include  "GameRoot.h"
#include "MaskLayer.h"
static GameHud* _shareHud;
extern CCPointArray* _startPosArr;
GameHud* GameHud::shareGameHud()
{
    if (_shareHud==NULL) {
        _shareHud =  GameHud::create();
        _shareHud->retain();
    }
    return _shareHud;
}
bool GameHud::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        bottomLayer = CCLayer::create();
        bottomLayer->setPosition(0, 0);
        this->addChild(bottomLayer);
       CCSprite* background = CCSprite::create("hud.png");
		background->setAnchorPoint(CCPointZero);
        float saclex = winsize.width/background->boundingBox().size.width;
        background->setScaleX(saclex);
        
		bottomLayer->addChild(background);

        CCMenuItemSprite * item1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("B1_0.png"), CCSprite::createWithSpriteFrameName("B1_0.png"), this, menu_selector(GameHud::soldier1_Select));
        item1->setPosition(ccp(10,10));
        CCMenuItemSprite * item2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("B2_0.png"), CCSprite::createWithSpriteFrameName("B2_0.png"), this, menu_selector(GameHud::soldier2_Select));
        item2->setPosition(ccp(110, 10));
        CCMenuItemSprite * item3 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("B3_0.png"), CCSprite::createWithSpriteFrameName("B3_0.png"), this, menu_selector(GameHud::soldier3_Select));
        item3->setPosition(ccp(210, 10));
        CCMenuItemSprite * item4 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("B4_0.png"), CCSprite::createWithSpriteFrameName("B4_0.png"), this, menu_selector(GameHud::soldier4_Select));
        item4->setPosition(ccp(310, 10));
        CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
        menu->setPosition(ccp(100,30));
        menu->setTag(10);
        bottomLayer->addChild(menu);
        selectFlag = CCSprite::create("select.png");
        selectFlag->retain();
        selectFlag->setScale(0.5f);
        selectFlag->setPosition( ccpAdd(item1->getPosition(), menu->getPosition()));
        bottomLayer->addChild(selectFlag);
        CCLabelTTF* lab = CCLabelTTF::create("所需 100 援兵", "Arial-BoldMT", 20);
        lab->setColor(ccRED);
        lab->setTag(101);
        lab->setPosition(ccp(600, 40));
        bottomLayer->addChild(lab);
        CCMenuItemFont *add = CCMenuItemFont::create("增援", this, menu_selector(GameHud::click_addSoldier));
        
        add->setPosition(CCPointZero);
        add->setFontSizeObj(35);
        add->setColor(ccRED);
        CCMenu *menu0 = CCMenu::createWithItem(add);
        menu0->setPosition( winsize.width-200, 40);
        bottomLayer->addChild(menu0);
        
        CCMenuItemSprite* btn_attack = CCMenuItemSprite::create(
                                                                CCSprite::createWithSpriteFrameName("btn_soldierattack1.png"),
                                                                CCSprite::createWithSpriteFrameName("btn_soldierattack2.png"),
                                                                this, menu_selector(GameHud::click_attack));
        CCMenu* menu1 = CCMenu::createWithItem(btn_attack);
        menu1->setPosition(ccp(winsize.width/2,winsize.height-70));
        this->addChild(menu1);


        
        soldier1_Select(item1);
        
        timerLab = CCLabelTTF::create("3", "Arial-BoldMT", 50);
        timerLab->setPosition(ccp(winsize.width/2, winsize.height/2));
        this->addChild(timerLab);
        
        this->setTouchEnabled(true);
        GameRoot::shareGameRoot()->sethasStart(false);
        count =3;
        isShowing = false;
        showBottomMenu();
        ret = true;
    } while (0);
    return ret;
}
void GameHud::addMask()
{
    MaskLayer*  mask = MaskLayer::create();
    this->schedule(schedule_selector(GameHud::countDown), 1.0f);
    this->addChild(mask);
    mask->setTag(11);
}
void GameHud::countDown()
{
    if (count<=0) {
        this->unschedule(schedule_selector(GameHud::countDown));
       
        timerLab->removeFromParent();
        
        this->removeChildByTag(11);
        return;
    }
    count--;
    CCString* str = CCString::createWithFormat("%d",count);
    timerLab->setString(str->getCString());
}
void GameHud::soldier1_Select(CCNode *pSender){
    CCMenu* menu =(CCMenu*) bottomLayer->getChildByTag(10);
    CCPoint pos = ccpAdd(menu->getPosition(), pSender->getPosition());
    selectFlag->setPosition(pos);
    CCLabelTTF* lab =(CCLabelTTF*) bottomLayer->getChildByTag(101);
    lab->setString("所需 100 援兵");
    selectPro =  Infantry;
    selectID = "B1";
}
void GameHud::soldier2_Select(CCNode *pSender){
    CCMenu* menu =(CCMenu*) bottomLayer->getChildByTag(10);
    CCPoint pos = ccpAdd(menu->getPosition(), pSender->getPosition());
    selectFlag->setPosition(pos);
    CCLabelTTF* lab =(CCLabelTTF*) bottomLayer->getChildByTag(101);
    lab->setString("所需 150 援兵");
    selectID = "B2";
    selectPro = Archer;
}
void GameHud::soldier3_Select(CCNode *pSender){
    CCMenu* menu =(CCMenu*) bottomLayer->getChildByTag(10);
    CCPoint pos = ccpAdd(menu->getPosition(), pSender->getPosition());
    selectFlag->setPosition(pos);
    CCLabelTTF* lab =(CCLabelTTF*) bottomLayer->getChildByTag(101);
    lab->setString("所需 300 援兵");
    selectID = "B3";
    selectPro = Cavalvy;
}
void GameHud::soldier4_Select(CCNode *pSender){
    CCMenu* menu =(CCMenu*) bottomLayer->getChildByTag(10);
    CCPoint pos = ccpAdd(menu->getPosition(), pSender->getPosition());
    selectFlag->setPosition(pos);
    CCLabelTTF* lab =(CCLabelTTF*) bottomLayer->getChildByTag(101);
    lab->setString("所需 150 援兵");
    selectPro = Pikeman;
    selectID = "B4";
}
void GameHud::click_attack(CCNode *pSender)
{
    if (!GameRoot::shareGameRoot()->gethasStart()) {
        GameRoot::shareGameRoot()->startGame();
        GameRoot::shareGameRoot()->sethasStart(true);
    }

    
}
void GameHud::click_addSoldier(CCNode *pSender)
{
    
    SceneGame* scene =(SceneGame*)GameRoot::shareGameRoot()->getSceneGame();
    
    //    CCPoint pos = ccp(100,400);
    int index = CCRANDOM_0_1()*3;
    CCPoint pos = _startPosArr->getControlPointAtIndex(index);
    scene->addSoldier(pos, selectID.c_str(), selectPro);
}
void GameHud::showBottomMenu()
{
    if(isShowing)
    {
        isShowing = false;
    CCPoint pos = bottomLayer->getPosition();
    pos.y = -bottomLayer->boundingBox().size.height;
    CCMoveTo* move = CCMoveTo::create(0.5f, pos);
    bottomLayer->runAction(move);
    }else
    {
        isShowing = true;
        CCPoint pos = bottomLayer->getPosition();
        pos.y=0;
        CCMoveTo* move = CCMoveTo::create(0.5f, pos);
        bottomLayer->runAction(move);
    }
}
void GameHud::unShowBottomMenu()
{
    if (isShowing) {
        isShowing = false;
        CCPoint pos = bottomLayer->getPosition();
        pos.y = -bottomLayer->boundingBox().size.height;
        CCMoveTo* move = CCMoveTo::create(0.5f, pos);
        bottomLayer->runAction(move);
    }
}
void GameHud::addLeftHead(const char *name)
{
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemSprite* btn_My = CCMenuItemSprite::create(
                                                        CCSprite::create(name),
                                                        CCSprite::create(name),
                                                        this, menu_selector(GameHud::selMyHead));
    CCMenu* menu1 = CCMenu::createWithItem(btn_My);
    menu1->setPosition(ccp(70,winsize.height-80));
    addChild(menu1);
}
void GameHud::addRightHead(const char *name)
{
       CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemSprite* btn_My = CCMenuItemSprite::create(
                                                        CCSprite::create(name),
                                                        CCSprite::create(name),
                                                        this, menu_selector(GameHud::selEnemyHead));
    CCMenu* menu1 = CCMenu::createWithItem(btn_My);
    menu1->setPosition(ccp(winsize.width-80,winsize.height-70));
    this->addChild(menu1);
}
void GameHud::selMyHead()
{
    _heroSel =true;
    if (isShowing) {
        isShowing = false;
        CCPoint pos = bottomLayer->getPosition();
        pos.y = -bottomLayer->boundingBox().size.height;
        CCMoveTo* move = CCMoveTo::create(0.5f, pos);
        bottomLayer->runAction(move);
    }
}
void GameHud::selEnemyHead()
{
    
}