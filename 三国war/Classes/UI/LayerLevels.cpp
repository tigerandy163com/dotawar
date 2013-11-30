#include "LayerLevels.h"
#include "GameRoot.h"

LayerLevels::LayerLevels()
{
	CCPoint* offset = new CCPoint(180, 180);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			CCMenuItemSprite* level = CCMenuItemSprite::create(
				CCSprite::createWithSpriteFrameName("btn_level1.png"), 
				CCSprite::createWithSpriteFrameName("btn_level2.png"), 
				this, menu_selector(LayerLevels::click_level));
            int tag = (j * 4 + i + 1);
            level->setTag(tag);
			CCMenu* menu = CCMenu::createWithItem(level);
			menu->setPosition(CCDirector::sharedDirector()->convertToUI(
				ccp(offset->x + 200* i, offset->y + 85 * j)));
			this->addChild(menu);


			char str[64] = {0};
			sprintf(str, "%d", tag);
			CCMenuItem* menuitem = new CCMenuItem();
			CCLabelTTF* text = CCLabelTTF::create(
				str, "Arial", 22);
			
			text->setColor(ccBLACK);
			menuitem->addChild(text);
			menu->addChild(menuitem);
		}
	}
}

void LayerLevels::click_level(CCNode *pSender)
{
    CCLOG("%d",pSender->getTag());
    GameRoot::shareGameRoot()->resetSceneGame();
    CCScene* pScene = CCScene::create();
    pScene->addChild(GameRoot::shareGameRoot()-> getSceneGame());
	CCDirector::sharedDirector()->pushScene(pScene);
}

void LayerLevels::Show()
{
	this->setVisible(true);
	this->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width, 0));
	CCMoveTo* move = CCMoveTo::create(0.5f, ccp(0, 0));
	this->runAction(move);
}

void LayerLevels::Hide()
{
	CCMoveTo* move = CCMoveTo::create(0.5f, 
		ccp(-(CCDirector::sharedDirector()->getWinSize().width), 0));
	this->runAction(CCSequence::create(move, 
		CCCallFunc::create(this, callfunc_selector(LayerLevels::HideAniCompleted))));
}

void LayerLevels::HideAniCompleted()
{
	this->setVisible(false);
}