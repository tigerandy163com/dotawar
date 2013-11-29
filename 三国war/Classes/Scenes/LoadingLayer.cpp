//
//  LoadingLayer.cpp
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#include "LoadingLayer.h"
#include "GameRoot.h"
#include "MyXMLParser.h"
USING_NS_CC;


#define ToTalResCount 4
LoadingLayer::LoadingLayer(){
    
}
LoadingLayer::~LoadingLayer(){
    
}

CCScene* LoadingLayer::scene(){
    do {
        CCLayer *layer = LoadingLayer::create();
        CC_BREAK_IF(!layer);
        CCScene *scene = CCScene::create();
        scene->addChild(layer);
        return scene;
    } while (0);
    return NULL;
}
CCScene* LoadingLayer:: scene(int lev){
    do {
        CCLayer *layer = LoadingLayer::create(lev);
        CC_BREAK_IF(!layer);
        CCScene *scene = CCScene::create();
        scene->addChild(layer);
        return scene;
    } while (0);
    return NULL;
}
LoadingLayer* LoadingLayer::create(int Lev){
    LoadingLayer *layer =new  LoadingLayer;
    if (layer&&layer->initWithLevel(Lev)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

bool LoadingLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        scheduleUpdate();
        
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::create("Loading(0%)..."," Marker Felt", 30);
        label->setPosition(ccp(winsize.width/2, winsize.height/2));
        addChild(label);
        label->setTag(123);
        currentCount = 0;
        totalCount = ToTalResCount;
  
        CCSpriteFrameCache* cache =
        CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile("GameUI01.plist", "GameUI01.png");
        currentCount++;
        cache->addSpriteFramesWithFile("GameUI02.plist", "GameUI02.png");
        currentCount++;
        cache->addSpriteFramesWithFile("ActorsPack1.plist", "ActorsPack1.png");
        currentCount++;


        
      
       MyXMLParser::parserWithFile("image");

        currentCount++;
        bRet = true;
    } while (0);
    return bRet;
}
bool LoadingLayer::initWithLevel(int lev){
    bool bRet = false;
    do {
        CC_BREAK_IF(!LoadingLayer::init());
        scheduleUpdate();
        
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::create("Loading(0%)..."," Marker Felt", 30);
        label->setPosition(ccp(winsize.width/2, winsize.height/2));
        addChild(label);
        label->setTag(123);
        currentCount = 0;
        totalCount = ToTalResCount;
        
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("battle1.wav");
//        currentCount++;
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower1.wav");
//        currentCount++;
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower2.wav");
//        currentCount++;
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower3.wav");
//        currentCount++;
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower4.wav");
//        currentCount++;

        CCSpriteFrameCache* cache =
        CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile("GameUI01.plist", "GameUI01.png");
        currentCount++;
        cache->addSpriteFramesWithFile("GameUI02.plist", "GameUI02.png");
        currentCount++;
        cache->addSpriteFramesWithFile("ActorsPack1.plist", "ActorsPack1.png");
        currentCount++;
        
//        CCTextureCache::sharedTextureCache()->addImageAsync("GameUI01.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
//        CCTextureCache::sharedTextureCache()->addImageAsync("GameUI02.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
//        CCTextureCache::sharedTextureCache()->addImageAsync("ActorsPack1.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        
        
        bRet =true;
    } while (0 );
    return bRet;
}

void LoadingLayer::loadingCallBack(cocos2d::CCObject *psender){
    ++currentCount;
}
void LoadingLayer::startGame(){

	CCDirector::sharedDirector()->pushScene((CCScene*)GameRoot::shareGameRoot()-> getSceneStart());
}
void LoadingLayer::update(float delta){
    float percent = (float)currentCount/(float)totalCount*100;
    CCLabelTTF *label =(CCLabelTTF*) getChildByTag(123);
    CCString *str = CCString::createWithFormat("Loading(%d)...",(int)percent);
    label->setString(str->getCString());
    if (currentCount==totalCount) {
        label->setString("Load finished");
        unscheduleUpdate();
        scheduleOnce(schedule_selector(LoadingLayer::startGame), 0.3);
    }
}