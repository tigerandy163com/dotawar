//
//  Bullet.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-18.
//
//

#include "Bullet.h"
#include "GameRoot.h"
Bullet*  Bullet::create(const char* name)
{
    Bullet* bullet = new Bullet();
    if (bullet&&bullet->initWithName(name)) {
        bullet->autorelease();
        return bullet;
    }else
    {
        delete bullet;
        bullet = NULL;
        return bullet;
    }
}
bool Bullet::initWithName(const char* name)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCNode::init());
        _sprite = CCSprite::create(name);
        this->addChild(_sprite);
        gm = GameRoot::shareGameRoot();
        winsize = CCDirector::sharedDirector()->getWinSize();
        scheduleUpdate();
        bRet = true;
    } while (0);
    return bRet;
}
void Bullet::setEnemy(ActorBase *var)
{
    if (var!=NULL) {
    _enemy = var;

        float dis = ccpDistance(this->getPosition(), _enemy->getPosition());
        float dur = dis/_speed;
        CCMoveTo* action = CCMoveTo::create(dur, _enemy->getPosition());
        CCCallFunc* moveDone = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
        CCSequence *seq = CCSequence::create(action,moveDone,NULL);
        this->runAction(seq);

    }
//    _enemy = var;
//    CCLOG("enemy::%f,%f",var->getPositionX(),var->getPositionY());
}
void Bullet::update(float dt)
{
    if (this->getPositionX()<=0||this->getPositionX()>winsize.width||getPositionY()<0||getPositionY()>winsize.height) {
        removeSelf();
        return;
    }
    if (_enemy&& _enemy->getActorData()->getblood()>0) {

        //碰撞检测
        CCRect targetRect =
        CCRectMake(
                   _enemy->getPosition().x,
                   _enemy->getPosition().y,
                   _enemy->_sprite->getContentSize().width,
                   _enemy->_sprite->getContentSize().height);
        
        CCRect actorRect = CCRectMake(
                                      this->getPosition().x ,
                                      this->getPosition().y ,
                                      _sprite->getContentSize().width/2,
                                      _sprite->getContentSize().height/2);
  
        if (actorRect.intersectsRect(targetRect)) {
            _enemy->attackedByEnemy(_damage, false);
            removeSelf();
            return;
        }else
        {
//
//            CCPoint targetPos = _enemy->getPosition();
//            CCPoint myPos = this->getPosition();
//            float radian = atan2f(targetPos.y - myPos.y, targetPos.x - myPos.x);
//            float angle = -CC_RADIANS_TO_DEGREES(radian);
//            angle = to360Angle(angle);
//         
//        //    this->setRotation(angle);
//            float myRadian = CC_DEGREES_TO_RADIANS(angle);
//            
//            float x = cosf(myRadian) * this->getSpeed() * dt;
//            float y = -sinf(myRadian) * this->getSpeed() * dt;
//            
//            this->setPosition(ccp(myPos.x + x, myPos.y + y));
//
        }
    }else
        removeSelf();
        
}
void Bullet::removeSelf()
{
       this->unscheduleUpdate();
    this->stopAllActions();
    removeFromParentAndCleanup(true);
}