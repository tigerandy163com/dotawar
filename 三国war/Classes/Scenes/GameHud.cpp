//
//  GameHud.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-13.
//
//

#include "GameHud.h"
#include  "GameRoot.h"
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
        
        CCMenuItemSprite * item1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("A1_0.png"), CCSprite::createWithSpriteFrameName("A1_0.png"), this, menu_selector(GameHud::soldier1_Select));
        item1->setPosition(ccp(10,10));
        CCMenuItemSprite * item2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("A2_0.png"), CCSprite::createWithSpriteFrameName("A2_0.png"), this, menu_selector(GameHud::soldier2_Select));
        item2->setPosition(ccp(110, 10));
        CCMenuItemSprite * item3 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("A3_0.png"), CCSprite::createWithSpriteFrameName("A3_0.png"), this, menu_selector(GameHud::soldier3_Select));
        item3->setPosition(ccp(210, 10));
        CCMenuItemSprite * item4 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("A4_0.png"), CCSprite::createWithSpriteFrameName("A4_0.png"), this, menu_selector(GameHud::soldier4_Select));
        item4->setPosition(ccp(310, 10));
        CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
        menu->setPosition(ccp(100,40));
        
        this->addChild(menu);
        
        CCLabelTTF* lab = CCLabelTTF::create("所需 100 战功", "Arial-BoldMT", 20);
        lab->setColor(ccRED);
        lab->setTag(101);
        lab->setPosition(ccp(600, 40));
        this->addChild(lab);
        
        CCMenuItemSprite* btn_attack = CCMenuItemSprite::create(
                                                                CCSprite::createWithSpriteFrameName("btn_soldierattack1.png"),
                                                                CCSprite::createWithSpriteFrameName("btn_soldierattack2.png"),
                                                                this, menu_selector(GameHud::click_attack));
        CCMenu* menu1 = CCMenu::createWithItem(btn_attack);
        menu1->setPosition(ccp(800,40));
        this->addChild(menu1);
        soldier1_Select();
        ret = true;
    } while (0);
    return ret;
}
void GameHud::soldier1_Select(){
    CCLabelTTF* lab =(CCLabelTTF*) this->getChildByTag(101);
    lab->setString("所需 100 战功");
    selectPro =  Infantry;
    selectID = "A1";
}
void GameHud::soldier2_Select(){
    CCLabelTTF* lab =(CCLabelTTF*) this->getChildByTag(101);
    lab->setString("所需 150 战功");
    selectID = "A2";
    selectPro = Archer;
}
void GameHud::soldier3_Select(){
    CCLabelTTF* lab =(CCLabelTTF*) this->getChildByTag(101);
    lab->setString("所需 300 战功");
    selectID = "A3";
    selectPro = Cavalvy;
}
void GameHud::soldier4_Select(){
    CCLabelTTF* lab =(CCLabelTTF*) this->getChildByTag(101);
    lab->setString("所需 150 战功");
    selectPro = Pikeman;
    selectID = "A4";
}
void GameHud::click_attack(CCObject *pSender)
{
    SceneGame* scene =(SceneGame*)GameRoot::shareGameRoot()->getSceneGame();
    
//    CCPoint pos = ccp(100,400);
    int index = CCRANDOM_0_1()*3;
    CCPoint pos = _startPosArr->getControlPointAtIndex(index);
    scene->addSoldier(pos, selectID.c_str(), selectPro);
}