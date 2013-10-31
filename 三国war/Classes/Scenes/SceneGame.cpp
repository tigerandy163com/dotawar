#include "SceneGame.h"
#include "GameRoot.h"
CCScene* SceneGame::Scene()
{
	CCScene *scene = CCScene::create();
    SceneGame *layer = SceneGame::create();
    scene->addChild(layer);
    return scene;
}
bool SceneGame::init()
{
	if (!CCLayer::init()) {
        return false;
    }

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCTMXTiledMap* map = CCTMXTiledMap::create("Level0.tmx");
	//map->removeChild(map->layerNamed("units"), false);
	map->setPosition(ccp((
		size.width - map->getContentSize().width) / 2, 
		(size.height - map->getContentSize().height) / 2));
	this->addChild(map);

	CCMenuItemSprite* btn_attack = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("btn_soldierattack1.png"), 
		CCSprite::createWithSpriteFrameName("btn_soldierattack2.png"), 
		this, menu_selector(SceneGame::click_attack));
	CCMenu* menu = CCMenu::createWithItem(btn_attack);
	menu->setPosition(ccp(732, 36));
	this->addChild(menu);
    return true;
}

void SceneGame::click_attack(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene((CCScene*)GameRoot::shareGameRoot()-> getSceneOver());
}