#ifndef _ACTOR_DATA_H_
#define _ACTOR_DATA_H_

#include "cocos2d.h"
USING_NS_CC;
using std::string;

enum ActorType {Type_None = 0, Soldier, Hero};
enum ActorPro {Pro_None = 0, Infantry, Pikeman, Cavalvy, Archer};
enum ActorDir {Dir_None = 0, Right, Left};

class ActorData:public CCObject
{
public :
	ActorData(string id);
	ActorData(ActorData* pActorData);


	static ActorData* getActorData(string id, string groupid, ActorType type, ActorPro pro);
    CC_SYNTHESIZE(std::string, mActorID, ActorID);
    CC_SYNTHESIZE(std::string, mGroupID, GroupID);
    CC_SYNTHESIZE(ActorType, mActorType, ActorType);
    CC_SYNTHESIZE(ActorPro, mActorPro, ActorPro);

};

#endif