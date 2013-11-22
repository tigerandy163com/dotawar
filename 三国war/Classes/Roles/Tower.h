//
//  Tower.h
//  三国war
//
//  Created by chunyu.wang on 13-11-18.
//
//

#ifndef ____war__Tower__
#define ____war__Tower__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class ActorBase;
class Tower:public CCNode,public cocos2d::CCTouchDelegate
{
public:
    CCSprite* _sprite;
    CCProgressTimer* healthBar;
    ~Tower();
    static Tower* create(const char* name);
    bool initWithName(const char* name);
    void towerData(int totalblood,int range,int damage,int group,bool canAttack,int fireSpeed,int bulletSpeed);
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
    void attackedByEnemy(int damageval,bool isBoom);
    CC_SYNTHESIZE(float, _blood, Blood);
    CCSprite*  _aimSprite;
    void setTotalBlood(float var)
    {
        _blood = var;
        _totalBlood = var;
    }
    int getTotalBlood()
    {
        return _totalBlood;
    }
    CC_SYNTHESIZE(bool, _canAttack, CanAttack);
    CC_SYNTHESIZE(int, _range, Range);
    CC_SYNTHESIZE(float, _damage, Damage);
    CC_SYNTHESIZE(int, _groupID, GroupID);
    CC_SYNTHESIZE(float, _fireSpeed, FireSpeed);
    CC_SYNTHESIZE(int, _bulletSpeed, BulletSpeed);
    
    void startUpdate();
protected:
    
    ActorBase* _enemy;
    ActorBase* getCloseEnemy();
    void removeSelf();
    int _totalBlood;
    void towerLogic();
    void fire();
    
};

class Home:public Tower
{
    
};
#endif /* defined(____war__Tower__) */
