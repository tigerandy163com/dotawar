#include "ActorData.h"

ActorData::ActorData(string id)
{
	this->mActorID = id;
	this->mGroupID = "-1";
	this->mActorType = Type_None;
	this->mActorPro = Pro_None;
}

ActorData::ActorData(ActorData* pActorData)
{
	if (pActorData != NULL) {
		this->setActorID(pActorData->getActorID());
		this->setGroupID(pActorData->getGroupID());
		this->setActorType(pActorData->getActorType());
		this->setActorPro(pActorData->getActorPro());
	} else {
		ActorData("-1");
	}
}

ActorData* ActorData::getActorData(string id, string groupid, ActorType type, ActorPro pro)
{
	ActorData* data = new ActorData(id);
    if (data) {
        data->autorelease();
    }else
    {
        delete data;
        data = NULL;
        return NULL;
    }
	data->setGroupID(groupid);
	data->setActorType(type);
	data->setActorPro(pro);
	return data;
}

