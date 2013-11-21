//
//  tileMapHelp.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-1.
//
//

#include "tileMapHelp.h"
CCPoint TileMapHelp::tileCoordinateFromPosition(CCTMXTiledMap* map,CCTMXLayer* _bg1layer,CCPoint pos)
{
    
    int cox,coy;
    
    
    CCSize szLayer=_bg1layer->getLayerSize();
    
    CCSize szTile=map->getTileSize();
    
    cox = pos.x / szTile.width;
    //与地图坐标相反，所以减
    coy = szLayer.height - pos.y / szTile.height;
    
    if ((cox >=0) && (cox < szLayer.width) && (coy >= 0) && (coy < szLayer.height)) {
        
        
        return  ccp(cox,coy);
    }else {
        
        return ccp(-1,-1);
    }
    
}
 int TileMapHelp:: tileIDFromPosition(CCTMXTiledMap* map,CCTMXLayer* _bg1layer,cocos2d:: CCPoint pos)
{
    CCPoint cpt = TileMapHelp::tileCoordinateFromPosition(map,_bg1layer,pos);
    if (cpt.x < 0) return  -1;
    if (cpt.y < 0) return -1;
    if (cpt.x >= _bg1layer->getLayerSize().width) return -1;
    if (cpt.y >= _bg1layer->getLayerSize().height) return -1;
    
    
    return _bg1layer->tileGIDAt(cpt);
}
CCRect TileMapHelp::objectBoundBox(cocos2d::CCTMXTiledMap *map, cocos2d::CCTMXObjectGroup *group, const char *object)
{
    CCSize tileSize = map->getTileSize();
     CCDictionary *dicT  = group->objectNamed(object);

    CCString* objW = (CCString*)dicT->objectForKey("width");
    CCString* objH =(CCString*)dicT->objectForKey("height");
    CCPoint point ;
    point.x = dicT->valueForKey("x")->intValue();
    point.y =  dicT->valueForKey("y")->intValue();
    CCRect rec = CCRect(point.x, point.y, objW->floatValue(), objH->floatValue());
    return rec;

}
CCPoint TileMapHelp:: objectPosition(CCTMXTiledMap* map,cocos2d::CCTMXObjectGroup *group,const char *object)
{
    CCPoint point;
    CCSize tileSize = map->getTileSize();
    CCDictionary *groupdic  = group->objectNamed(object);
    point.x = groupdic->valueForKey("x")->intValue()+tileSize.width/2;
    point.y =  groupdic->valueForKey("y")->intValue()+tileSize.height/2;
    return point;
}
CCPoint TileMapHelp:: tileCoordForPosition(CCTMXTiledMap* map,cocos2d::CCPoint position)
{
    CCSize mapSize = map->getMapSize();
    CCSize tileSize = map->getTileSize();
   float maxWidth = mapSize.width - tileSize.width - tileSize.width * 0.5f;
   float  maxHeight = mapSize.height - tileSize.height * 2- tileSize.height * 0.5f;
   int  maxTileWidth = mapSize.width;
	int maxTileHeight = mapSize.height;
  	int x, y;
	if(position.x < tileSize.width){
		x = 0;
	}else if(position.x > maxWidth){
		x = maxTileWidth - 1;
	}else{
		x = (position.x - tileSize.width) / tileSize.width;
	}
    
	if(position.y < tileSize.height * 2){
		y = 0;
	}else if(position.y > maxHeight){
		y = maxTileHeight - 1;
	}else{
		y = (position.y - tileSize.height * 2) / tileSize.height;
	}
    
	return ccp(x, y);
}
CCPoint TileMapHelp:: positionForTileCoord(CCTMXTiledMap* map,cocos2d::CCPoint position)
{
    float x, y;
    CCSize tileSize = map->getTileSize();
    CCSize mapSize = map->getContentSize();
	x =  position.x * tileSize.width  + tileSize.width  * 0.5f;
	y = mapSize.height - position.y * tileSize.height - tileSize.height * 0.5f;
    
	return ccp(x, y);
}