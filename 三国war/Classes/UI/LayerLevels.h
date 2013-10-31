#ifndef _LAYER_LEVELS_H_
#define _LAYER_LEVELS_H_

#include "cocos2d.h"
using namespace cocos2d;

class LayerLevels : public CCLayer
{
public :
	LayerLevels();
	void Show();
	void Hide();

private :
	void click_level(CCObject* pSender);	
	void HideAniCompleted();
};

#endif