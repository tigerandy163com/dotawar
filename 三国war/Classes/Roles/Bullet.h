//
//  Bullet.h
//  三国war
//
//  Created by chunyu.wang on 13-11-18.
//
//

#ifndef ____war__Bullet__
#define ____war__Bullet__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class ActorBase;
class GameRoot;
class Bullet: public CCNode
{
public:
    static Bullet* create(const char* name);
    bool initWithName(const char* name);
 //   CC_SYNTHESIZE(ActorBase*, _enemy, Enemy);
    void setEnemy(ActorBase* actor);
    
    CC_SYNTHESIZE(float, _damage, Damage);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(float, _probability, Probability);
    CC_SYNTHESIZE(CCPoint, _targetPos, TargetPos);
protected:
    ActorBase* _enemy;
    CCSprite* _sprite;
    GameRoot* gm;
    CCSize winsize;
    bool hasRemoved;
	void removeSelf();
    void update(float delta);
   float  angularVelocity = 10.0f;
	float to360Angle(float angle)
	{
		angle = (int)angle % 360;
		if (angle < 0)
			angle += 360;
		return angle;
	}

};
#endif /* defined(____war__Bullet__) */
