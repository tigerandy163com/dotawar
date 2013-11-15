#include "SceneGame.h"
#include "GameRoot.h"
#include "tileMapHelp.h"

#include "GameHud.h"
#include "MaskLayer.h"
 CCPointArray* _startPosArr;
SceneGame::~SceneGame()
{
    CC_SAFE_RELEASE_NULL(_map);

}
CCScene* SceneGame::Scene()
{
	CCScene *scene = CCScene::create();
    SceneGame *layer = SceneGame::create();
    scene->addChild(layer);
    return scene;
}
bool SceneGame::init()
{
	if (!CCLayer::init()) {
        return false;
    }

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCTMXTiledMap* map = CCTMXTiledMap::create("Level0.tmx");
    CCSize mapcontent = map->getContentSize();
    map->setScaleX(size.width/mapcontent.width);
    map->setScaleY(size.height/mapcontent.height);
    _map = map;
    _map->retain();

//	map->setPosition(ccp((
//		size.width - map->getContentSize().width) / 2, 
//		(size.height - map->getContentSize().height) / 2));
	this->addChild(map);
    _objects = map->objectGroupNamed("objects");
    _bg1layer = map->layerNamed("ground");
    CCArray *objects = _objects->getObjects();
    CCObject *obj = NULL;
    CCSize tileSize = map->getTileSize();
    CCArray *arrL = CCArray::create();
    CCArray *arrR = CCArray::create();
    if(_startPosArr)
        CC_SAFE_RELEASE_NULL(_startPosArr);
   _startPosArr=CCPointArray::create(5) ;
    _startPosArr->retain();
    CCARRAY_FOREACH(objects, obj){
        CCDictionary *dic = (CCDictionary *)obj;
        int  type = dic->valueForKey("type")->intValue() ;
        CCString *id =(CCString*)dic->objectForKey("id");
        CCString *groupid = (CCString*)dic->objectForKey("group");
        int  pro = dic->valueForKey("pro")->intValue();
         CCPoint point;
        point.x = dic->valueForKey("x")->intValue()+tileSize.width/2;
        point.y = dic->valueForKey("y")->intValue()+tileSize.height/2;
        CCLOG("%f,,,%f",point.x,point.y);
     //   point = TileMapHelp::positionForTileCoord(_map, point);
      //    CCLOG("%f---%f",point.x,point.y);
            ActorData *data = ActorData::getActorData(id->getCString(),groupid->getCString(), (ActorType)type, (ActorPro)pro,this);
            ActorBase *actor = ActorBase::create(data);
            actor->setPosition(point);
        actor->setoriginalPos(point);
        GameRoot::shareGameRoot()->addSpriteTag();
        actor->setTag(GameRoot::shareGameRoot()->getspriteTag());
           this->addChild(actor);
  
        if (groupid->compare("1")==0) {
            arrL->addObject(actor);
            if(type==Soldier)
            _startPosArr->addControlPoint(point);
        }else
        {
            arrR->addObject(actor);
        }
    }
    
    ActorBase::sortActors(arrL);
    ActorBase::sortActors(arrR);
    GameRoot::shareGameRoot()->getactorArrL()->addObjectsFromArray(arrL);
    GameRoot::shareGameRoot()->getactorArrR()->addObjectsFromArray(arrR);

    this->addChild(GameHud::shareGameHud());

    return true;
}

void SceneGame::addSoldier(cocos2d::CCPoint pos, const char* soldierId,ActorPro pro)
{
    ActorData *data = ActorData::getActorData(soldierId,"1",Soldier, pro,this);
    ActorBase *actor = ActorBase::create(data);
    GameRoot::shareGameRoot()->addSpriteTag();
    actor->setTag(GameRoot::shareGameRoot()->getspriteTag());
    actor->setPosition(pos);
    actor->setoriginalPos(pos);
    this->addChild(actor);
    CCArray *larr = GameRoot::shareGameRoot()->getactorArrL();
    larr->addObject(actor);
    if(GameRoot::shareGameRoot()->gethasStart())
    actor->start();

}
void SceneGame::removeMask()
{
    this->removeChildByTag(11);
 }