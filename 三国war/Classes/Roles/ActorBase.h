#ifndef _ACTOR_BASE_H_
#define _ACTOR_BASE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "ActorData.h"
enum ActorState {Stand = 0, Run, Attack};
class Tower;
class GameRoot;
class ActorBase : public CCNode,public cocos2d::CCTouchDelegate
{
public :
//	ActorBase(ActorData* data);
	~ActorBase();
    CCSprite *_sprite;
    bool initWithActorData(ActorData* data);
    static ActorBase* create(ActorData* data);
     bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
    GameRoot* GR;
    float totalBlood;
    ActorDir getActorDir(void);
    ActorDir mActorDir;
    CCSprite *_aimSprite;
    ActorState mState;
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
    CC_SYNTHESIZE_RETAIN(ActorData*, mActorData, ActorData);
    bool startTowerFight;
    bool ForceAttackTower;
    bool checkCollision();
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
        CCPoint _originalPos;
    
    CC_SYNTHESIZE(ActorBase *, _target, target);
    CC_SYNTHESIZE(Tower*, _towerTarget,TowerTarget);
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