#include "SceneOver.h"
CCScene* SceneOver::Scene()
{
	CCScene *scene = CCScene::create();
    SceneOver *layer = SceneOver::create();
    scene->addChild(layer);
    return scene;
}
bool SceneOver::init()
{
	if (!CCLayer::init()) {
        return false;
    }
   CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::createWithSpriteFrameName("bg_over.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background);
    CCSize size1 = background->getContentSize();
    float scale1 = winSize.width/size1.width;
    float scale2 = winSize.height/size1.height;
    background->setScaleX(scale1);
    background->setScaleY(scale2);
	
	CCSprite* title = CCSprite::createWithSpriteFrameName("text_over.png");
	title->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 150));
	this->addChild(title);

	CCMenuItemSprite* btn_back = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("btn_back1.png"), 
		CCSprite::createWithSpriteFrameName("btn_back2.png"), 
		this, menu_selector(SceneOver::click_back));
	CCMenu* menu = CCMenu::createWithItem(btn_back);
	menu->setPosition(ccp(666, 32));
	this->addChild(menu);
    return true;
}

void SceneOver::click_back(CCObject *pSender)
{
	CCDirector::sharedDirector()->popScene();
}