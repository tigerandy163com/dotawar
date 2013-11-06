#ifndef _ACTOR_BASE_H_
#define _ACTOR_BASE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "ActorData.h"

class ActorBase : public CCNode
{
public :
//	ActorBase(ActorData* data);
	~ActorBase();
    CCSprite *_sprite;
    bool initWithActorData(ActorData* data);
    static ActorBase* create(ActorData* data);
    CC_SYNTHESIZE_RETAIN(ActorData*, mActorData, ActorData);
    CC_SYNTHESIZE(ActorDir, mActorDir, ActorDir);


	CCAnimate* _action_attack;
	CCAnimate* _action_attack_flip;
	CCAnimate* _action_run;
	CCAnimate* _action_run_flip;
	CCAnimate* _action_stand;
	CCAnimate* _action_stand_flip;
	CCAnimate* _action_dead;
	CCAnimate* _action_dead_flip;

	CCAction* _currentAnimateAction;
    CCAction* _onceAnimateAction;
	void StateToRun();
	void StateToAttack();
	void StateToDead();
	void StateToStand();
    void actorLogic();
    void startRun();
    void dealDead();
    virtual  void update(float fDelta);
    static void sortActors(CCArray* array);
   
    void startAttack();
    void fire();
    void findAnotherTarget();
    void attackedByEnemy(int damageval,bool isBoom);
private :

    bool isDead;
    CC_SYNTHESIZE_RETAIN(ActorBase *, _target, target);
    static int less(const CCObject* obj0, const CCObject* obj1);

	void currentAnimateActionStop();
	void RunAnimateAction_RepeatForever(CCAnimate* action);
    void RunAnimateAction_once(CCAnimate* action,SEL_CallFunc selector);
    void oneceAnimteActionStop();
    
    void moveToTarget();
};

#endif