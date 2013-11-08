#include "ActorData.h"
#include "ActorBase.h"
#include "SceneGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int executeGlobalFunction( const char* functionName, int numArgs )
{
    lua_State *luaState =  CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    
    lua_getglobal(luaState, functionName);       /* query function by name, stack: function */
    if (lua_isfunction(luaState, -1))
    {
        if (numArgs > 0)
        {
            lua_insert(luaState, -(numArgs + 1));                        /* stack: ... func arg1 arg2 ... */
        }
        
        int traceback = 0;
        lua_getglobal(luaState, "__G__TRACKBACK__");                     /* stack: ... func arg1 arg2 ... G */
        if (!lua_isfunction(luaState, -1))
        {
            lua_pop(luaState, 1);                                        /* stack: ... func arg1 arg2 ... */
        }
        else
        {
            traceback = -(numArgs + 2);
            lua_insert(luaState, traceback);                             /* stack: ... G func arg1 arg2 ... */
        }
        
        int error = 0;
        error = lua_pcall(luaState, numArgs, 1, traceback);              /* stack: ... ret */
        if (error)
        {
            if (traceback == 0)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(luaState, - 1));    /* stack: ... error */
                lua_pop(luaState, 1); // remove error message from stack
            }
            return 0;
        }
        
        // get return value
        int ret = 0;
        if (lua_isnumber(luaState, -1))
        {
            ret = lua_tointeger(luaState, -1);
        }
        else if (lua_isboolean(luaState, -1))
        {
            ret = lua_toboolean(luaState, -1);
        }
        
        lua_pop(luaState, 1); // remove return value from stack
        return ret;
    }
    else
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(luaState, 1);
        lua_pop(luaState, numArgs); // remove args from stack
        return 0;
    }  
}
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

ActorData* ActorData::getActorData(string id, string groupid, ActorType type, ActorPro pro,SceneGame*gameLayer)
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
    CCScriptEngineManager* manager = CCScriptEngineManager::sharedManager();
    CCLuaEngine* engine = (CCLuaEngine*)manager->getScriptEngine();
    
    data->luaState = engine->getLuaStack()->getLuaState();
    engine->getLuaStack()->pushCCObject(data, "ActorData");
     lua_pushstring(data->luaState, id.c_str());
 //    int rtn = engine->executeGlobalFunction("main");
     executeGlobalFunction("main", 2);
    
     
	return data;
}
bool  ActorData::actorData(int speed,int blood,int damage,int experience,int range)
{
    setspeed(speed);
    setblood(blood);
    setdamage(damage);
    setexperience(experience);
    setattackRange(range);
    return true;
}
