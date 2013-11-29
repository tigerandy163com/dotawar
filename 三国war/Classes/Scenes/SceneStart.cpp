#include "SceneStart.h"
#include "GameRoot.h"

#include "ActorBase.h"
#include "ActorData.h"

CCScene* SceneStart::Scene()
{
	CCScene *scene = CCScene::create();
    SceneStart *layer = SceneStart::create();
    scene->addChild(layer);
    return scene;
}
bool SceneStart::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::createWithSpriteFrameName("bg_start.png");
	background->setAnchorPoint(ccp(0, 0));
    CCSize size1 = background->getContentSize();
    float scale1 = size.width/size1.width;
    float scale2 = size.height/size1.height;
    background->setScaleX(scale1);
    background->setScaleY(scale2);
	this->addChild(background);
    
	CCSprite* logo = CCSprite::createWithSpriteFrameName("logo.png");
	logo->setPosition(ccp(size.width/2, size.height/2+120));
	this->addChild(logo);
    
	CCMenuItemSprite* btn_start = CCMenuItemSprite::create(
                                                           CCSprite::createWithSpriteFrameName("btn_start1.png"),
                                                           CCSprite::createWithSpriteFrameName("btn_start2.png"),
                                                           this, menu_selector(SceneStart::click_start));
	CCMenuItemSprite* btn_setting = CCMenuItemSprite::create(
                                                             CCSprite::createWithSpriteFrameName("btn_setting1.png"),
                                                             CCSprite::createWithSpriteFrameName("btn_setting2.png"),
                                                             this, menu_selector(SceneStart::click_setting));
	CCMenu* menu = CCMenu::create(btn_start, btn_setting, NULL);
	menu->alignItemsVerticallyWithPadding(10);
	menu->setPosition(ccp(size.width/2, size.height/2-120));
	this->addChild(menu);
    
    
//	/**********TEST**********/
//	std::string id_buff[] =
//    {"B1", "B2", "B3", "B4", "Hero02",
//		"A1", "A2", "A3", "A4", "Hero11"};
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 5; j++) {
//			ActorBase* actor = new ActorBase(new ActorData(id_buff[i*5 + j]));
//			actor->setActorDir((ActorDir)(i + 1));
//			actor->setPosition(ccp(64 + i * 64, 64 + j * 64));
//			if (j % 2 == 1)
//				actor->StateToRun();
//			else
//				actor->StateToAttack();
//			this->addChild(actor);
//            
//			/****************/
//			ActorBase* actor2 = new ActorBase(new ActorData(id_buff[i*5 + j]));
//			actor2->setActorDir((ActorDir)(i + 1));
//			actor2->setPosition(ccp(672 + i * 64, 64 + j * 64));
//			this->addChild(actor2);
//			/****************/
//		}
//	}
//	/**********TEST**********/
    return true;
}
void SceneStart::click_start(CCObject* pSender)
{
    CCScene* pScene = CCScene::create();
    pScene->addChild(GameRoot::shareGameRoot()-> getSceneSelect());
	CCScene* tmpScene = CCTransitionFade::create(0.5f, pScene);
	CCDirector::sharedDirector()->pushScene(tmpScene);
}

void SceneStart::click_setting(CCObject* pSender)
{
}