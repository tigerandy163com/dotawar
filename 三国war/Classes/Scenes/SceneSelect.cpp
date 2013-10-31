#include "SceneSelect.h"
#include "GameRoot.h"
CCScene* SceneSelect::Scene()
{
	CCScene *scene = CCScene::create();
    SceneSelect *layer = SceneSelect::create();
    scene->addChild(layer);
    return scene;
}
bool SceneSelect::init()
{
	
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	story_tabs = NULL;
	currentlayerlevels = NULL;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::createWithSpriteFrameName("bg_select.png");
	background->setAnchorPoint(ccp(0, 0));
    CCSize size1 = background->getContentSize();
    float scale1 = size.width/size1.width;
    float scale2 = size.height/size1.height;
    background->setScaleX(scale1);
    background->setScaleY(scale2);
	this->addChild(background);
   
	CCMenuItemSprite* btn_back = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("btn_back1.png"), 
		CCSprite::createWithSpriteFrameName("btn_back2.png"), 
		this, menu_selector(SceneSelect::click_back));
	CCMenu* menu = CCMenu::createWithItem(btn_back);
    size1 =CCSprite::createWithSpriteFrameName("btn_back1.png")->getContentSize();
	menu->setPosition(ccp(size.width- size1.width/2, 32));
	this->addChild(menu);

	CCMenuItemSprite* tab1 = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("tab_shu2.png"), 
		CCSprite::createWithSpriteFrameName("tab_shu1.png"), 
		CCSprite::createWithSpriteFrameName("tab_shu1.png"), 
		this, menu_selector(SceneSelect::click_story_tab));
	tab1->setTag(0);
	CCMenuItemSprite* tab2 = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("tab_wu2.png"), 
		CCSprite::createWithSpriteFrameName("tab_wu1.png"), 
		CCSprite::createWithSpriteFrameName("tab_wu1.png"), 
		this, menu_selector(SceneSelect::click_story_tab));
	tab2->setTag(1);
	CCMenuItemSprite* tab3 = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("tab_wei2.png"), 
		CCSprite::createWithSpriteFrameName("tab_wei1.png"), 
		CCSprite::createWithSpriteFrameName("tab_wei1.png"), 
		this, menu_selector(SceneSelect::click_story_tab));
	tab3->setTag(2);
	this->story_tabs = CCMenu::create(tab1, tab2, tab3, NULL);
	this->story_tabs->alignItemsHorizontallyWithPadding(10);
	this->story_tabs->setPosition(
		CCDirector::sharedDirector()->convertToUI(ccp(500, 72)));
	tab1->setEnabled(false);
	this->addChild(story_tabs);

	for (int i = 0; i < 3; i++) {
		this->arrLayerLevels[i] = NULL;
		this->arrLayerLevels[i] = new LayerLevels();
		this->arrLayerLevels[i]->setVisible(false);
		this->addChild(arrLayerLevels[i]);
	}
	showLayerLevels(arrLayerLevels[tab1->getTag()]);
    return true;
}

SceneSelect::~SceneSelect()
{
	for (int i = 0; i < 3; i++) {
		if (arrLayerLevels[i] != NULL)
			delete arrLayerLevels[i];
		arrLayerLevels[i] = NULL;
	}
}

void SceneSelect::click_back(CCObject *pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void SceneSelect::click_story_tab(CCObject *pSender)
{
	CCObject *item;
	CCARRAY_FOREACH(story_tabs->getChildren(), item)
	{
		CCMenuItem *menuitem = dynamic_cast<CCMenuItem *>(item);
		menuitem->setEnabled(true);
	}
	CCMenuItem *sender = dynamic_cast<CCMenuItem *>(pSender);
	sender->setEnabled(false);
	showLayerLevels(arrLayerLevels[sender->getTag()]);
}

void SceneSelect::showLayerLevels(LayerLevels* pLayer)
{
	if (currentlayerlevels != NULL)
		currentlayerlevels->Hide();
	pLayer->Show();
	currentlayerlevels = pLayer;
}