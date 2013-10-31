#ifndef _SCENE_SELECT_H_
#define _SCENE_SELECT_H_

#include "cocos2d.h"
#include "LayerLevels.h"
using namespace cocos2d;

class SceneSelect : public CCLayer
{
public :
    virtual bool init();
    static CCScene *Scene();
    CREATE_FUNC(SceneSelect);
	~SceneSelect();
    
private :
	CCMenu* story_tabs;
	LayerLevels* arrLayerLevels[3];
	LayerLevels* currentlayerlevels;

	void click_back(CCObject* pSender);
	void click_story_tab(CCObject* pSender);
	void showLayerLevels(LayerLevels* pLayer);
};

#endif