#include "SceneGame.h"
#include "GameRoot.h"
#include "tileMapHelp.h"

#include "GameHud.h"
#include "MaskLayer.h"
#include "Tower.h"
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
    float scalex =size.width/mapcontent.width;
    ScaleX = scalex;
    map->setScaleX(scalex);
    float scaley =size.height/mapcontent.height;
    map->setScaleY(scaley);
    ScaleY = scaley;
    _touchObj = map->objectGroupNamed("touch");
    CCArray* arrT = _touchObj->getObjects();
    
    CCDictionary* dicT = (CCDictionary*)arrT->objectAtIndex(0);
    CCString* objName = (CCString*)dicT->objectForKey("name");
    
    CCRect rec = TileMapHelp::objectBoundBox(map, _touchObj, objName->getCString());
    CCPoint posT = rec.origin;
        posT.x *= ScaleX;
        posT.y *= ScaleY;
    CCSize sizeT = rec.size;
    sizeT.width *=ScaleX;
    sizeT.height *=ScaleY;
    rec = CCRectMake(posT.x, posT.y
                     , sizeT.width, sizeT.height);
    
    GameRoot::shareGameRoot()->setLimitRect(rec);
    
 
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
        CCString* objName = (CCString*)dic->objectForKey("name");
        CCPoint point = TileMapHelp::objectPosition(_map, _objects, objName->getCString());
        int  type = dic->valueForKey("type")->intValue() ;
        CCString *id =(CCString*)dic->objectForKey("id");
        CCString *groupid = (CCString*)dic->objectForKey("group");
        int  pro = dic->valueForKey("pro")->intValue();
        
        point.x *=ScaleX;
        point.y *=ScaleY;
      // point = TileMapHelp::positionForTileCoord(_map, point);
        {
            ActorData *data = ActorData::getActorData(id->getCString(),groupid->getCString(), (ActorType)type, (ActorPro)pro,this);
            ActorBase *actor = ActorBase::create(data);
   
        GameRoot::shareGameRoot()->addSpriteTag();
        actor->setTag(GameRoot::shareGameRoot()->getspriteTag());
  
        if (groupid->compare("1")==0) {
            arrL->addObject(actor);
            if(type==Soldier)
            _startPosArr->addControlPoint(point);
            else if (type==Hero)
                GameRoot::shareGameRoot()->setMyHero(actor);
        }else
        {
            arrR->addObject(actor);
        }
            actor->setPosition(point);
            actor->setoriginalPos(point);
                       this->addChild(actor);
    }
//    

    }
    //    ActorBase::sortActors(arrL);
    //    ActorBase::sortActors(arrR);
    GameRoot::shareGameRoot()->getactorArrL()->addObjectsFromArray(arrL);
    GameRoot::shareGameRoot()->getactorArrR()->addObjectsFromArray(arrR);
    
    _objects = _map->objectGroupNamed("towers");
    objects = _objects->getObjects();
    CCARRAY_FOREACH(objects,obj )
    {
        CCDictionary* dic = (CCDictionary*)obj;
        CCString *str =(CCString*) dic->objectForKey("type");
        CCString* str1 = CCString::createWithFormat("%s.png",str->getCString());
        CCString* groudid =(CCString*) dic->objectForKey("group");
        CCString* objName = (CCString*)dic->objectForKey("name");
        CCPoint point = TileMapHelp::objectPosition(_map, _objects, objName->getCString());
        point.x *=ScaleX;
        point.y *=ScaleY;
       {
            Tower* tower = Tower::create(str1->getCString());
           GameRoot::shareGameRoot()->addSpriteTag();
           tower->setTag(GameRoot::shareGameRoot()->getspriteTag());
           tower->setGroupID(groudid->intValue());
           if (groudid->intValue()==1) {
               GameRoot::shareGameRoot()->getTowerArrL()->addObject(tower);
           }else
               GameRoot::shareGameRoot()->getTowerArrR()->addObject(tower);

           
           if (str->compare("home")==0) {
               tower->setCanAttack(false);
           }else
               tower->setCanAttack(true);
           tower->setRange(200);
           tower->setDamage(100);
           tower->setTotalBlood(500);

            tower->setPosition(point);
            this->addChild(tower);
           tower->startUpdate();
        }
    }
    this->addChild(GameHud::shareGameHud());
    _aimSprite = CCSprite::create("aim.png");
    _aimSprite->retain();
    _aimSprite->setScale(0.5f);
    _aimSprite->setVisible(false);
    this->addChild(_aimSprite);
    GameRoot::shareGameRoot()->setAimSprite(_aimSprite);
    GameHud::shareGameHud()->addLeftHead("guanyu.png");
    GameHud::shareGameHud()->addRightHead("jiangwei.png");
    GameHud::shareGameHud()->addMask();
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, GameNodePority, true);
    return true;
}

bool SceneGame:: ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    GameHud::shareGameHud()->setHeroSel(true);
    GameHud::shareGameHud()->unShowBottomMenu();
    if (!GameRoot::shareGameRoot()->gethasStart()) {
        return false;
    }
    CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
    if (GameRoot::shareGameRoot()->getLimitRect().containsPoint(touchLocation)) {
 
        if (!GameRoot::shareGameRoot()->getMyHero()->getISDEAD()) {
            GameRoot::shareGameRoot()->setMyTargetPos(touchLocation);
            GameRoot::shareGameRoot()->flagNewTargetPos();
            GameRoot::shareGameRoot()->getMyHero()->setAutoFight(false);
            GameRoot::shareGameRoot()->getMyHero()->moveToPositon(touchLocation);
            unscheduleAllSelectors();
        }
        unscheduleAllSelectors();
        scheduleOnce(schedule_selector(SceneGame::hidenAimSprite), 0.3f);
    }
    return false;
}
void SceneGame::hidenAimSprite()
{
    _aimSprite->setVisible(false);
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

