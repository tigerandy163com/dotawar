//
//  Tower.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-18.
//
//

#include "Tower.h"
#include "Bullet.h"
#include "GameRoot.h"
Tower* Tower::create(const char *name)
{
    Tower* tower = new Tower();
    
    if (tower!=NULL&&tower->initWithName(name)) {
        tower->autorelease();
        return tower;
    }else
    {
        delete tower;
        tower = NULL;
        return NULL;
    }
}

bool Tower::initWithName(const char *name)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCNode::init());
        _sprite = CCSprite::create(name);
        this->addChild(_sprite);
        
        healthBar = CCProgressTimer::create(CCSprite::create("health_bar_green.png"));
        
		healthBar->setType(kCCProgressTimerTypeBar);
		healthBar->setMidpoint(ccp(0, 0));
		healthBar->setBarChangeRate(ccp(1, 0));
		healthBar->setPercentage(100);
		healthBar->setScale(0.25f);
		healthBar->setPosition(ccp(0,_sprite->getContentSize().height* 0.5f));
		this->addChild(healthBar,2);
        CCSprite *redBar = CCSprite::create("health_bar_red.png");
        redBar->setPosition(healthBar->getPosition());
        redBar->setScale(0.25f);
        this->addChild(redBar,1);
        
        bRet = true;
    } while (0);
    return bRet;
}
void Tower::startUpdate()
{
     this->schedule(schedule_selector(Tower::towerLogic), 0.1f);
    if (_canAttack) {
       
        this->schedule(schedule_selector(Tower::fire),0.5f);
    }
}
void Tower::removeSelf()
{
    unscheduleAllSelectors();
    stopAllActions();
    removeFromParentAndCleanup(true);
  }
void Tower:: towerData(int totalblood,int range,int damage,int group,bool canAttack,int fireSpeed,int bulletSpeed){
    _totalBlood = totalblood;
    _range = range;
    _damage = damage;
    _groupID = group;
    _canAttack = canAttack;
    _fireSpeed = fireSpeed;
    _bulletSpeed = bulletSpeed;
    
}
void Tower::attackedByEnemy(int damageval,bool isBoom)
{
   
    _blood -= damageval;
    CCString *str = CCString::createWithFormat("-%d",damageval);
    //  CCLog(str->getCString());
    float font = 30;
    if (isBoom) {
        font = 60;
    }
    CCLabelTTF* demageLab = CCLabelTTF::create(str->getCString(),  "Marker Felt", font);
    if (isBoom) {
        demageLab->setColor(ccYELLOW);
    }else
        demageLab->setColor(ccRED);
    float x = CCRANDOM_0_1()*40;
    float y = CCRANDOM_0_1()*40;
    demageLab->setPositionX(x);
    demageLab->setPositionY(y);
    this->addChild(demageLab);
    CCActionInterval* scale=CCScaleTo::create(10, 0.5);
    CCActionInterval *fade = CCFadeOut::create(0.5);
    demageLab->runAction(CCSpawn::create(scale,fade,NULL));
    
    float f = _blood/_totalBlood;
    healthBar->setPercentage(f*100);
   // CCLOG("blood:%f",_blood);
    if (_blood<=0) {
        removeSelf();
        return;
    }
}
void Tower::towerLogic()
{

    if (!_enemy) {
        _enemy = getCloseEnemy();
    }
    if (_enemy) {
        if (_enemy->getActorData()->getblood()<=0 ) {
            _enemy = NULL;
           // unschedule(schedule_selector(Tower::fire));
        }
    }
}
void Tower::fire()
{
    if (_enemy&&_enemy->getActorData()->getblood()>0) {
        float dis = ccpDistance(_enemy->getPosition(), this->getPosition());
        if (dis<=_range) {
            CCPoint shootVector = ccpSub(_enemy->getPosition(), this->getPosition());
            float shootAngle = ccpToAngle(shootVector);
            float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

             string bulletname;
            if(_groupID==1)
                bulletname ="bullet1.png";
            else
                bulletname = "bullet2.png";
            Bullet *bullet = Bullet::create(bulletname.c_str());
            bullet->setPosition(this->getPosition());
            bullet->setRotation(cocosAngle);
            bullet->setDamage(_damage);
            bullet->setSpeed(200);
            bullet->setEnemy(_enemy);
            GameRoot::shareGameRoot()->getSceneGame()->addChild(bullet, 2);
        }

    }
}
ActorBase*  Tower::getCloseEnemy()
{
    if (!_canAttack) {
        return NULL;
    }
    CCArray *enmeys ;
    if (_groupID==1) {
        enmeys=GameRoot::shareGameRoot()->getactorArrR();
        
    }else
        enmeys = GameRoot::shareGameRoot()->getactorArrL();
    // CCLog("count:%d",enmeys->count());
    if (enmeys->count()==0)
    {
        unscheduleAllSelectors();
        return NULL;
    }
    //查找最近距离的敌人
    ActorBase* closestEnemy = NULL;
	double maxDistant = 99999;
    
	CCObject* temp;
	CCARRAY_FOREACH(enmeys, temp){
		ActorBase* enemy = (ActorBase*)temp;
		if(enemy->getActorData()->getblood() <= 0){
			continue;
		}

		double curDistance = ccpDistance(this->getPosition(), enemy->getPosition());
		if(curDistance < maxDistant){
			closestEnemy = enemy;
			maxDistant = curDistance;
		}
	}
    if (closestEnemy) {
        
        return  closestEnemy;
    }
    return NULL;
}