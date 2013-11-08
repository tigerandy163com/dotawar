#include "ActorBase.h"
#include "GameRoot.h"
bool ActorBase::initWithActorData(ActorData *data)
{
 
    bool bRet = false;
    do {
        setActorData(data);
        totalBlood = data->getblood();
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
                                           CCAnimation::createWithSpriteFrames(_attackFrames,0.2f));
        _action_attack->retain();
        _action_attack_flip = CCAnimate::create(
                                                CCAnimation::createWithSpriteFrames(_attackFrames_flip,0.2f));
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
                                        CCAnimation::createWithSpriteFrames(_runFrames,0.3f));
        _action_run->retain();
        _action_run_flip = CCAnimate::create(
                                             CCAnimation::createWithSpriteFrames(_runFrames_flip,0.3f));
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
                                          CCAnimation::createWithSpriteFrames(_standFrames,0.3f));
        _action_stand->retain();
        _action_stand_flip = CCAnimate::create(
                                               CCAnimation::createWithSpriteFrames(_standFrames_flip,0.3f));
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
                                         CCAnimation::createWithSpriteFrames(_deadFrames,0.3f));
        _action_dead->retain();
        _action_dead_flip = CCAnimate::create(
                                              CCAnimation::createWithSpriteFrames(_deadFrames_flip,0.3f));
        _action_dead_flip->retain();
        
        if (mActorData->getGroupID().compare("1")) {
              sprintf(str, "%s_%d.png", data->getActorID().c_str(),6);
            mActorDir = Left;
            
        }else{
              sprintf(str, "%sf_%d.png", data->getActorID().c_str(), 6);
            mActorDir = Right;
        }
       _sprite =  CCSprite::createWithSpriteFrameName(str);
        _sprite->retain();
        this->addChild(_sprite);

        healthBar = CCProgressTimer::create(CCSprite::create("health_bar_green.png"));
        
		healthBar->setType(kCCProgressTimerTypeBar);
		healthBar->setMidpoint(ccp(0, 0));
		healthBar->setBarChangeRate(ccp(1, 0));
		healthBar->setPercentage(100);
		healthBar->setScale(0.2f);
		healthBar->setPosition(ccp(0,_sprite->getContentSize().height* 0.5f));
		this->addChild(healthBar,2);
        CCSprite *redBar = CCSprite::create("health_bar_red.png");
        redBar->setPosition(healthBar->getPosition());
        redBar->setScale(0.2);
        this->addChild(redBar,1);
        this->scheduleOnce(schedule_selector(ActorBase::startRun), 2.0f);
        schedule(schedule_selector(ActorBase::actorLogic), 0.5f);
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
ActorDir ActorBase::getActorDir(void){
    if (_target) {
        
        if (_target->getPositionX()>this->getPositionX()) {
            mActorDir = Right;
        }else{
            mActorDir = Left;
        }
    }
}
void ActorBase::StateToRun()
{
    getActorDir();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_run);
	else
		RunAnimateAction_RepeatForever(_action_run_flip);
}

void ActorBase::StateToAttack()
{
    
//	currentAnimateActionStop();

}

void ActorBase::StateToDead()
{
   
	currentAnimateActionStop();
     getActorDir();
	if (mActorDir == Left)
		RunAnimateAction_once(_action_dead,callfunc_selector(ActorBase::dealDead));
	else
		RunAnimateAction_once(_action_dead_flip,callfunc_selector(ActorBase::dealDead));
}

void ActorBase::StateToStand()
{
    getActorDir();
	if (mActorDir == Left)
		RunAnimateAction_RepeatForever(_action_stand);
	else
		RunAnimateAction_RepeatForever(_action_stand_flip);
}

void ActorBase::currentAnimateActionStop()
{
    
	if (_currentAnimateAction != NULL)
		_sprite->stopAction(_currentAnimateAction);
    this->stopAllActions();
    
}

void ActorBase::RunAnimateAction_RepeatForever(CCAnimate* action)
{
	currentAnimateActionStop();
	_currentAnimateAction = _sprite-> runAction(CCRepeatForever::create(action));
}
void ActorBase:: RunAnimateAction_once(CCAnimate* action,SEL_CallFunc selector)
{
    CCSequence *sequece = CCSequence::create(action,CCCallFunc::create(this, selector),NULL);
    _onceAnimateAction =  _sprite->runAction(sequece);
}
 void ActorBase:: oneceAnimteActionStop()
{
   // this->scheduleOnce(schedule_selector(ActorBase::StateToAttack), 1.5f);
}
void ActorBase::actorLogic(){
    if (mActorData->getblood()<=0) {
        stopAllActions();
        unscheduleAllSelectors();
        isDead =true;
        StateToDead();
    }
        if (!isDead&& _target)
        {
            if (_target-> mActorData->getblood()<=0) {
                StateToStand();
                unschedule(schedule_selector(ActorBase::fire));
                _target =NULL;
                //CC_SAFE_RELEASE_NULL(_target);
                scheduleOnce(schedule_selector(ActorBase::findAnotherTarget), 2.0f) ;
            }
          }
    
    
}
void ActorBase::dealDead()
{
    removeFromParentAndCleanup(true);
    if (mActorDir == Left) {
        GameRoot::shareGameRoot()->getactorArrR()->removeObject(this);
        CCLog("count:%d",GameRoot::shareGameRoot()->getactorArrR()->count());
    }
    else{
        GameRoot::shareGameRoot()->getactorArrL()->removeObject(this);
        CCLog("count:%d",GameRoot::shareGameRoot()->getactorArrL()->count());
    }
}
void ActorBase::findAnotherTarget()
{
    if (isDead) {
        return;
    }
    CCArray *enmeys ;
    if (mActorData->getGroupID().compare("1")) {
        enmeys=GameRoot::shareGameRoot()->getactorArrL();
       
    }else
        enmeys = GameRoot::shareGameRoot()->getactorArrR();
     CCLog("count:%d",enmeys->count());
    ActorBase* closestEnemy = NULL;
	double maxDistant = 99999;

	CCObject* temp;
	CCARRAY_FOREACH(enmeys, temp){
		ActorBase* enemy = (ActorBase*)temp;
		if(enemy->getActorData()->getblood() <= 0){
			continue;
		}
		double curDistance = ccpDistance(this->getPosition(), enemy->getPosition());
		if(curDistance < maxDistant){
			closestEnemy = enemy;
			maxDistant = curDistance;
		}
	}
    if (closestEnemy) {
 
	settarget(closestEnemy);
    StateToRun();
    moveToTarget();
    this->scheduleUpdate();
    }
}
void ActorBase::startRun()
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
    StateToRun();
    moveToTarget();
    
    this->scheduleUpdate();
}
void ActorBase::moveToTarget()
{
    if (_target) {
        CCPoint pos;
        if (_target->getActorDir()==Left) {
            pos = ccp(_target->getPositionX()+40 ,_target->getPositionY());
        }else
             pos = ccp(_target->getPositionX()-40,_target->getPositionY());
    float dis = ccpDistance(this->getPosition(), pos);
    float time = dis/mActorData->getspeed();
    CCMoveTo *move = CCMoveTo::create(time, pos);
        _move = move;
    this->runAction(move);
    }
}
void ActorBase::startAttack(){
    int val = mActorData->getdamage();
    if (_target)
   _target ->attackedByEnemy(val, false);
 }
void ActorBase::fire(){
    getActorDir();
    if (mActorDir == Left)
    RunAnimateAction_once(_action_attack,callfunc_selector(ActorBase::startAttack));
    else
         RunAnimateAction_once(_action_attack_flip,callfunc_selector(ActorBase::startAttack));
}

void ActorBase::attackedByEnemy(int damageval,bool isBoom)
{
    int bloodval = mActorData->getblood();
    bloodval -= damageval;
    mActorData->setblood(bloodval);
    
    CCString *str = CCString::createWithFormat("-%d",damageval);
    //  CCLog(str->getCString());
    float font = 30;
    if (isBoom) {
        font = 60;
    }
    CCLabelTTF* demageLab = CCLabelTTF::create(str->getCString(),  "Marker Felt", font);
    if (isBoom) {
        demageLab->setColor(ccYELLOW);
    }else
        demageLab->setColor(ccRED);
    float x = CCRANDOM_0_1()*40;
    float y = CCRANDOM_0_1()*40;
    demageLab->setPositionX(x);
    demageLab->setPositionY(y);
    this->addChild(demageLab);
    CCActionInterval* scale=CCScaleTo::create(10, 0.5);
    CCActionInterval *fade = CCFadeOut::create(0.5);
    demageLab->runAction(CCSpawn::create(scale,fade,NULL));
    
    float f = (float)mActorData->getblood()/totalBlood;
    healthBar->setPercentage(f*100);
}
void ActorBase:: update(float fDelta){
    if (!_target) {
        return;
    }
    CCRect targetRect =
    CCRectMake(
                                   _target->getPosition().x,
                                   _target->getPosition().y,
                                   _target->_sprite->getContentSize().width,
                                  _target->_sprite->getContentSize().height);

    CCRect actorRect = CCRectMake(
                                   this->getPosition().x ,
                                  this->getPosition().y ,
                                   _sprite->getContentSize().width+mActorData->getattackRange(),
                                   _sprite->getContentSize().height+mActorData->getattackRange());
    int YY=_target->getPositionY()-this->getPositionY();
    if (actorRect.intersectsRect(targetRect)&& abs(YY)<5) {
        this->unscheduleUpdate();
        this->StateToStand();
        schedule( schedule_selector(ActorBase::fire), 1.0f);
    }
}
int ActorBase::less(const CCObject* in_pCcObj0, const CCObject* in_pCcObj1) {
    return ((ActorBase*)in_pCcObj0)->getPositionY() < ((ActorBase*)in_pCcObj1)->getPositionY();
}

void ActorBase::sortActors(CCArray* array) {
    std::sort(array->data->arr, array->data->arr + array->data->num, ActorBase::less);
}

