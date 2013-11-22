#ifndef _ACTOR_DATA_H_
#define _ACTOR_DATA_H_

#include "cocos2d.h"
#import "CCLuaBridge.h"
USING_NS_CC;
using std::string;

enum ActorType {Type_None = 0, Soldier, Hero};
enum ActorPro {Pro_None = 0, Infantry, Pikeman, Cavalvy, Archer};//步兵，矛兵，骑兵，弓兵
enum ActorDir {Dir_None = 0, Right, Left,Up,Down};
class ActorBase;
class SceneGame;
class ActorData:public CCObject
{
public :
	ActorData(string id);
	ActorData(ActorData* pActorData);

   bool actorData(int speed,int blood,int damage,int experience,int range);
	static ActorData* getActorData(string id, string groupid, ActorType type, ActorPro pro,SceneGame* gameLayer);
    CC_SYNTHESIZE(std::string, mActorID, ActorID);
    CC_SYNTHESIZE(std::string, mGroupID, GroupID);
    CC_SYNTHESIZE(ActorType, mActorType, ActorType);
    CC_SYNTHESIZE(ActorPro, mActorPro, ActorPro);
    CC_SYNTHESIZE(bool, _itsMe, ITISME);
    CC_SYNTHESIZE(int, _speed, speed);
    CC_SYNTHESIZE(int, _blood, blood);
    CC_SYNTHESIZE(int, _damage, damage);
    CC_SYNTHESIZE(int, _experience, experience);
    CC_SYNTHESIZE(int, _attackRange, attackRange);
    lua_State *luaState;
};

#endif