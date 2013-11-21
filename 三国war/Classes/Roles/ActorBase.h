#ifndef _ACTOR_BASE_H_
#define _ACTOR_BASE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "ActorData.h"
class Tower;
class ActorBase : public CCNode
{
public :
//	ActorBase(ActorData* data);
	~ActorBase();
    CCSprite *_sprite;
    bool initWithActorData(ActorData* data);
    static ActorBase* create(ActorData* data);
    CC_SYNTHESIZE_RETAIN(ActorData*, mActorData, ActorData);
    float totalBlood;
    ActorDir getActorDir(void);
    ActorDir mActorDir;
 
	CCAnimate* _action_attack;
	CCAnimate* _action_attack_flip;
	CCAnimate* _action_run;
	CCAnimate* _action_run_flip;
	CCAnimate* _action_stand;
	CCAnimate* _action_stand_flip;
	CCAnimate* _action_dead;
	CCAnimate* _action_dead_flip;

    CCAnimate* _action_attackUp;
	CCAnimate* _action_attackDown;
	CCAnimate* _action_runUp;
	CCAnimate* _action_runDown;
	CCAnimate* _action_standUp;
	CCAnimate* _action_standDown;
	CCAnimate* _action_deadUp;
	CCAnimate* _action_deadDown;
    
	CCAction* _currentAnimateAction;
    CCAction* _onceAnimateAction;
	void StateToRun();
	void StateToAttack();
	void StateToDead();
	void StateToStand();
    void actorLogic();
    void startRun();
    void dealDead();
    void comeInHome();
    virtual  void update(float fDelta);
    static void sortActors(CCArray* array);
    void start();
    void startAttack();
    void fire();
    void findAnotherTarget();
    void attackedByEnemy(int damageval,bool isBoom);
    void backToLine();
    void setoriginalPos(CCPoint var);
    CC_SYNTHESIZE(CCPoint, _destinationPos, destinationPos);
    CC_SYNTHESIZE(bool, _autoFight, AutoFight);
    CC_SYNTHESIZE(bool, isDead, ISDEAD);
private :
    float to360Angle(float angle)
	{
		angle = (int)angle % 360;
		if (angle < 0)
			angle += 360;
		return angle;
	}
    cocos2d::CCProgressTimer* healthBar;
    
    bool isBack;
    bool startTowerFight;
    CCPoint _originalPos;
    CC_SYNTHESIZE(ActorBase *, _target, target);
    Tower* _towerTarget;
    static int less(const CCObject* obj0, const CCObject* obj1);

	void currentAnimateActionStop();
	void RunAnimateAction_RepeatForever(CCAnimate* action);
    void RunAnimateAction_once(CCAnimate* action,SEL_CallFunc selector);
    void oneceAnimteActionStop();
    CCSize winsize;
    bool isFiring;
    void moveToTarget();
    void moveToPositon(CCPoint pos);
};

#endif