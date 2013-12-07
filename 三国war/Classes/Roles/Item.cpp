//
//  Item.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-29.
//
//

#include "Item.h"
//    获取当前时间 精确到毫秒数

static inline long millisecondNow()

{
    
    struct cc_timeval now;
    
    CCTime::gettimeofdayCocos2d(&now, NULL);
    
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
    
}

// 判断是不是 双击

static inline bool isDoubleTouch(){
    
    static long lastTouchTime=0;
    
    long thisTouchTime=millisecondNow();
    long ti = abs(thisTouchTime-lastTouchTime);

    if(ti<250){
        
        lastTouchTime=0;
        
        return true;
        
    }else{
        
        lastTouchTime=millisecondNow();
        
        return false;
        
    }
    
}
Item::Item()
{
    
}
Item::~Item()
{
    CC_SAFE_RELEASE_NULL(m_Sprite);
    CC_SAFE_RELEASE_NULL(SBackGroundSprite);
    CC_SAFE_RELEASE_NULL(NBackGroundSprite);
}
bool Item::init()
{
    bool Ret = false;
    do {
        CC_BREAK_IF(!CCNode::init());
        Ret =true;
    } while (0);
    return Ret;
}
Item* Item::Create(int id_var, int lev_var, int count_var)
{
    Item* item = new Item();
    if (item && item->initWithItemID(id_var, lev_var, count_var)) {
        item->autorelease();
        
        return item;
    }else
    {
        delete item;
        item =NULL;
        return NULL;
    }
}
bool Item::initWithItemID(int id_var,int lev_var,int count_var)
{
      bool Ret = false;
    do {
        CC_BREAK_IF(!CCNode::init());
        m_ID = id_var;
        m_Level = lev_var;
        m_Count = count_var;
        

        
        NBackGroundSprite = CCSprite::createWithSpriteFrameName("BagItemBgNormal");
        NBackGroundSprite->setAnchorPoint(CCPointZero);
        NBackGroundSprite->setPosition(CCPointZero);
        NBackGroundSprite->retain();
        this->addChild(NBackGroundSprite, 0);

        SBackGroundSprite = CCSprite::createWithSpriteFrameName("BagItemBgDown");
        SBackGroundSprite->setAnchorPoint(CCPointZero);
        SBackGroundSprite->setPosition(CCPointZero);
        SBackGroundSprite->retain();
        this->addChild(SBackGroundSprite,0);
        SBackGroundSprite->setVisible(false);
        
        
        if (m_ID==-1) {
            return true;
        }
        
        char imageN[64] = {0};
        sprintf(imageN,"%d.png",id_var);
        m_Sprite = CCSprite::create(imageN);
        if (m_Sprite==NULL) {
            Ret= false;
            break;
        }
        m_Sprite->retain();
        addChild(m_Sprite,1);
        m_Sprite->setAnchorPoint(CCPointZero);
        m_Sprite->setPosition(ccp(8, 8));
        
        CCRect msize = m_Sprite->boundingBox();
        float h = msize.size.height;
        float w = msize.size.width;
        if (lev_var>0) {
            char levstr[10]={0};
            sprintf(levstr, "%d",lev_var);
            CCLabelTTF* levLab = CCLabelTTF::create(levstr, "Arial-BoldMT",20);
            levLab->setColor(ccBLACK);
            addChild(levLab,2);
            levLab->setPosition(ccp(w-5,h));
        }
        if (count_var>1) {
            char countstr[10]={0};
            sprintf(countstr, "%d",count_var);
            CCLabelTTF* conutLab = CCLabelTTF::create(countstr, "Arial-BoldMT",20);
            conutLab->setColor(ccBLUE);
            addChild(conutLab,2);
            conutLab->setPosition(ccp(w-5,20));
        }
        setContentSize(NBackGroundSprite->boundingBox().size);
        isSelect = false;
        Ret =true;
    } while (0);

    return Ret;
}
void Item::selectItem(bool var)
{
     CCLOG("item single:%d",getTag());
    if (m_ID==-1) {
        return;
    }
    if (var) {
        if (isSelect) {
            return;
        }else
        {
            isSelect = true;
            NBackGroundSprite->setVisible(false);
            SBackGroundSprite->setVisible(true);
        }
    }else
    {
        if (!isSelect) {
            return;
        }else
        {
            isSelect = false;
            NBackGroundSprite->setVisible(true);
            SBackGroundSprite->setVisible(false);
        }
        
    }
}
bool Item::isInSprite(cocos2d::CCTouch *theTouch)
{
    //    返回当前触摸位置在OpenGL坐标
    
    CCPoint touchPoint=theTouch->getLocation();
    
    //    将世界坐标转换为当前父View的本地坐标系
    
    CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
    
    //    获取当前基于父view的坐标系
    
    CCRect rect=this->boundingBox();
    
    //    CCnode->convertToNodeSpace 或者  convertToWorldSpace 是基于当前Node的  与当前Node相关
    
    if(rect.containsPoint(reallyPoint)){
        return true;
    }
    return false;
}

void Item::checkLongPress(){
    
    this->unschedule(schedule_selector(Item::checkLongPress));
    
    if (isInTouch&&!isInMove) {
        
        CCLog("LONGLONG %d",getTag());
//        
//        this->setScale(2);
//        
//        this->setOpacity(200);
        
        afterLongPress=true;
        
    }
    
}
void Item:: singleClickSprite()
{
    if (!afterDoublePress&&!afterLongPress)
    {
    selectItem(true);
        afterDoublePress = false;
        afterLongPress = false;
    }
}
void Item:: doubleClickSprite()
{
    
    CCLog("double click %d",getTag());
}
bool Item::itemTouchBegan(){
    // CCLOG("item touch began:%d",getTag());
    {
        isInTouch=true;
        
        if (isDoubleTouch()) {
            afterDoublePress = true;
            this->doubleClickSprite();
            
            this->touchBeginTime=millisecondNow();
            
        }else{
            
            //this->singleClickSprite();
            
            this->touchBeginTime=millisecondNow();
            
            this->schedule(schedule_selector(Item::checkLongPress), 2);
            
        }

        return true;
        
    }
    
    return false;
}

void Item::itemTouchMoved() {
    
//    CCPoint deltaPoint=pTouch->getDelta();
//    
//    CCLog("x=%f,y=%f",deltaPoint.x,deltaPoint.y);
//    
//    if(fabs(deltaPoint.x)>1||fabs(deltaPoint.y)>1){
//        
//        isInMove=true;
//        
//    }
    isInMove=true;
    afterLongPress=false;
    afterDoublePress = false;
}

void Item::itemTouchEnded() {
    
    isInTouch=false;
    
    isInMove=false;
    
    afterLongPress=false;
   
    
    //     恢复 精灵
    
//    this->setScale(1);
//    
//    this->setPosition(orignalPoint);
//    
//    this->setOpacity(255);
    
    
    
}

void Item::itemTouchCancelled(){
    
    isInTouch=false;
    
    isInMove=false;
    
    afterLongPress=false;
    
    
//    //     恢复 精灵
//    
//    this->setScale(1);
//    
//    this->setPosition(orignalPoint);
//    
//    m_Sprite->setOpacity(255);
    
}