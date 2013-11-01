//
//  tileMapHelp.h
//  三国war
//
//  Created by chunyu.wang on 13-11-1.
//
//

#ifndef ____war__tileMapHelp__
#define ____war__tileMapHelp__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class TileMapHelp{
public:
  static  CCPoint tileCoordinateFromPosition(CCTMXTiledMap* map,CCTMXLayer* _bg1layer,CCPoint pos);
   static int tileIDFromPosition(CCTMXTiledMap* map,CCTMXLayer* _bg1layer,cocos2d:: CCPoint pos);
  static  cocos2d:: CCPoint objectPosition(CCTMXTiledMap* map,cocos2d::CCTMXObjectGroup *group,const char *object);
   static cocos2d::CCPoint tileCoordForPosition(CCTMXTiledMap* map,cocos2d::CCPoint position);
	static cocos2d::CCPoint positionForTileCoord(CCTMXTiledMap* map,cocos2d::CCPoint position);
};
#endif /* defined(____war__tileMapHelp__) */
