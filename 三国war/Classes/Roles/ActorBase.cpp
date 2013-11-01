#include "ActorBase.h"
#include "GameRoot.h"
bool ActorBase::initWithActorData(ActorData *data)
{
    bool bRet = false;
    do {
        setActorData(data);
        _action_attack = NULL;
        _action_attack_flip = NULL;
        _action_run = NULL;
        _action_run_flip = NULL;
        _action_stand = NULL;
        _action_stand_flip = NULL;
        _action_dead = NULL;
        _action_dead_flip = NULL;

        _currentAnimateAction = NULL;
        
        CCSpriteFrameCache* cache =
        CCSpriteFrameCache::sharedSpriteFrameCache();
        char str[64] = {0};
        char strf[64] = {0};
        
        CCArray* _attackFrames =  CCArray::create();
        CCArray* _attackFrames_flip =  CCArray::create();

        for (int i = 0; i < 4; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
   
            _attackFrames->addObject(cache->spriteFrameByName(str));
            _attackFrames_flip->addObject(cache->spriteFrameByName(strf));
        }

        _action_attack = CCAnimate::create(
                                           CCAnimation::createWithSpriteFrames(_attackFrames));
        _action_attack->retain();
        _action_attack_flip = CCAnimate::create(
                                                CCAnimation::createWithSpriteFrames(_attackFrames_flip));
        _action_attack_flip->retain();
        
        CCArray* _runFrames =  CCArray::createWithCapacity(10);
        CCArray* _runFrames_flip =  CCArray::createWithCapacity(10);
        for (int i = 4; i < 6; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _runFrames->addObject(cache->spriteFrameByName(str));
            _runFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_run = CCAnimate::create(
                                        CCAnimation::createWithSpriteFrames(_runFrames));
        _action_run->retain();
        _action_run_flip = CCAnimate::create(
                                             CCAnimation::createWithSpriteFrames(_runFrames_flip));
        _action_run_flip->retain();
        
        CCArray* _standFrames =   CCArray::createWithCapacity(10);
        CCArray* _standFrames_flip =   CCArray::createWithCapacity(10);
        for (int i = 6; i < 7; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _standFrames->addObject(cache->spriteFrameByName(str));
            _standFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_stand = CCAnimate::create(
                                          CCAnimation::createWithSpriteFrames(_standFrames));
        _action_stand->retain();
        _action_stand_flip = CCAnimate::create(
                                               CCAnimation::createWithSpriteFrames(_standFrames_flip));
        _action_stand_flip->retain();
        
        CCArray* _deadFrames =  CCArray::createWithCapacity(10);
        CCArray* _deadFrames_flip =  CCArray::createWithCapacity(10);
        for (int i = 7; i < 9; i++) {
            sprintf(str, "%s_%d.png", data->getActorID().c_str(), i);
            sprintf(strf, "%sf_%d.png", data->getActorID().c_str(), i);
            _deadFrames->addObject(cache->spriteFrameByName(str));
            _deadFrames_flip->addObject(cache->spriteFrameByName(strf));
        }
        _action_dead = CCAnimate::create(
                                         CCAnimation::createWithSpriteFrames(_deadFrames));
        _action_dead->retain();
        _action_dead_flip = CCAnimate::create(
                                              CCAnimation::createWithSpriteFrames(_deadFrames_flip));
        _action_dead_flip->retain();
        
        if (mActorData->getGroupID().compare("1")) {
              sprintf(str, "%s_%d.png", data->getActorID().c_str(), 6);
        }else
              sprintf(str, "%sf_%d.png", data->getActorID().c_str(), 6);
      
       _sprite =  CCSprite::createWithSpriteFrameName(str);
        _sprite->retain();
        this->addChild(_sprite);
        setspeed(100.0f);
        this->schedule(schedule_selector(ActorBase::actorLogic), 1.0f, kCCRepeatForever, 1.0f);
        bRet = true;
    } while (0);
    return bRet;
}
ActorBase* ActorBase::create(ActorData* data)
{
    ActorBase* actorbase =new ActorBase();
    if (actorbase&&actorbase->initWithActorData(data)) {
        actorbase->autorelease();
        return actorbase;
    }else
    {
       
        delete actorbase;
        actorbase =NULL;
        return NULL;
    }
}

ActorBase::~ActorBase()
{
    CC_SAFE_RELEASE_NULL(mActorData);
    CC_SAFE_RELEASE_NULL(_action_attack);
    CC_SAFE_RELEASE_NULL(_action_attack_flip);
    CC_SAFE_RELEASE_NULL(_action_dead);
    CC_SAFE_RELEASE_NULL(_action_dead_flip);
    CC_SAFE_RELEASE_NULL(_action_run);
    CC_SAFE_RELEASE_NULL(_action_run_flip);
    CC_SAFE_RELEASE_NULL(_action_stand);
    CC_SAFE_RELEASE_NULL(_action_stand_flip);
}

void ActorBase::StateToRun()
{
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_run);
	else
		RunAnimateAction_RepeatForever(_action_run_flip);
}

void ActorBase::StateToAttack()
{
	currentAnimateActionStop();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_attack);
	else
		RunAnimateAction_RepeatForever(_action_attack_flip);
}

void ActorBase::StateToDead()
{
	currentAnimateActionStop();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_dead);
	else
		RunAnimateAction_RepeatForever(_action_dead_flip);
}

void ActorBase::StateToStand()
{
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_stand);
	else
		RunAnimateAction_RepeatForever(_action_stand_flip);
}

void ActorBase::currentAnimateActionStop()
{
	if (_currentAnimateAction != NULL)
		this->stopAction(_currentAnimateAction);
}

void ActorBase::RunAnimateAction_RepeatForever(CCAnimate* action)
{
	currentAnimateActionStop();
	_currentAnimateAction = runAction(CCRepeatForever::create(action));
}

void ActorBase::actorLogic()
{
    CCArray *arr;
    CCArray *arr1;
    if (getActorData()->getGroupID().compare("1")==0) {
        arr = GameRoot::shareGameRoot()-> getactorArrL();
        arr1 =   GameRoot::shareGameRoot()-> getactorArrR();
    }else{
           arr = GameRoot::shareGameRoot()-> getactorArrR();
        arr1 = GameRoot::shareGameRoot()-> getactorArrL();
    }
    int index = -1;
    index = arr->indexOfObject(this);
    
    settarget((ActorBase*)arr1->objectAtIndex(index));
    
    
}
int ActorBase::less(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1) {
    return ((ActorBase*)in_pCcObj0)->getPositionY() < ((ActorBase*)in_pCcObj1)->getPositionY();
}

void ActorBase::sortActors(CCArray* in_pCcArrDogs) {
    std::sort(in_pCcArrDogs->data->arr, in_pCcArrDogs->data->arr + in_pCcArrDogs->data->num, ActorBase::less);
}