//
//  __warAppDelegate.cpp
//  三国war
//
//  Created by chunyu.wang on 13-10-31.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameRoot.h"
#include "CCLuaEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Create lua engine
    CCLuaEngine* engine = CCLuaEngine::defaultEngine();
    assert(engine);
    if (!engine)
        return false;
    engine->executeScriptFile("actor.lua");
    CCScriptEngineManager::sharedManager()->setScriptEngine(engine);
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
   CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480*2, 320*2,kResolutionExactFit);
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
   
    
    // create a scene. it's an autorelease object
    CCScene *pScene =  (CCScene*)GameRoot::shareGameRoot()-> getSceneStart();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
