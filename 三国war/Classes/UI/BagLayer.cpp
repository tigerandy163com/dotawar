//
//  BagLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-28.
//
//

#include "BagLayer.h"
#include "Item.h"
#define BAGROW 4
#define BAGCOL 3
BagLayer:: BagLayer()
{
    m_ItemCount =25;
}
BagLayer:: ~BagLayer()
{
    
}
bool BagLayer::init()
{
    bool ret =false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("BagItemBgNormal");
        itemSize = sprite->boundingBox().size;
         itemSizeWithMargin = CCSizeMake((int)(itemSize.width*9/8), (int)(itemSize.height*9/8));
        // CCScrollView
        m_ScrollView = CCCGameScrollView::create();	//创建一个scrollview
        m_ScrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，目前来说只能横方向和纵方向
        int pageCount = m_ItemCount/(BAGROW*BAGCOL);
        if ( m_ItemCount==0|| m_ItemCount%(BAGROW*BAGCOL)!=0) {
            pageCount++;
        }
            float ww =itemSizeWithMargin.width*(BAGCOL);
            float hh =itemSizeWithMargin.height*(BAGROW);

        m_ScrollView->createContainer(this, pageCount, CCSizeMake(ww,hh));
        //一般是原点
        m_ScrollView->setPosition(ccp(0, 0));
        m_ScrollView->setAnchorPoint(CCPointZero);
        //视口的尺寸(一般是屏幕的尺寸)
       // m_ScrollView->setViewSize(CCDirector::sharedDirector()->getVisibleSize());
        this->setContentSize(CCSizeMake(ww,hh));
        this->addChild(m_ScrollView);
   //     registerWithTouchDispatcher();
        ret = true;
    } while (0 );
    return ret;
}
 void BagLayer::scrollViewDidScroll(CCScrollView* view){
    
}
 void BagLayer::scrollViewDidZoom(CCScrollView* view){
    
}
bool BagLayer::scrollViewInitPage(cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage)
{

	const int row = BAGROW;
    const int column = BAGCOL;
 
    Item* item = NULL;
 
    int posX = 0;
    int posY = (row-1)*itemSizeWithMargin.height;
   
    int tag = 0;
    for(int i = 0; i< row; ++i)
    {
        for (int j = 0; j <column; ++j)
        {
            tag = i*column +j+1;
            tag += nPage*BAGROW*BAGCOL;
            if (tag>m_ItemCount) {
                item = Item::Create(-1, tag, 2);
            }else
            {
            item = Item::Create(500169, tag, 2);
            }
            item->retain();
            item->setAnchorPoint(ccp(0, 0));
            item->setPosition(ccp(posX, posY));
            pPage->addChild(item,2,tag);

            posX += itemSizeWithMargin.width;

        }
        
        posY  -= itemSizeWithMargin.height;
        posX =0;
    }
    CCLOG("npage:%d",nPage);
    
	return true;
}

 void BagLayer::scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage )
{
    nodeDidClick(pPage, oPoint);
//    switch(nPage)
//	{
//        case 0:
//		{
//			//切换场景
////			CCScene* pScene=CCScene::create();
////			pScene->addChild(CMenuScene::create());
////			CCDirector::sharedDirector()->replaceScene(pScene);
//		}
//            break;
//        case 1:
//		{
//			//滚动到某个页面
//			m_ScrollView->scrollToPage(2);
//		}
//            break;
//        case 2:
//		{
//			//设置当前页面
//			m_ScrollView->setCurPage(3);
//		}
//            break;
//	}

}
 void BagLayer::scrollViewScrollEnd(cocos2d::CCNode *pPage, int nPage)
{
    	CCLog("Current Page=%d", nPage);
}
void BagLayer::ItemDidClick(cocos2d::CCNode *clickNode)
{
    CCLog("item:::%d",clickNode->getTag());
    Item* selItem = (Item*)clickNode;
    selItem->selectItem(true);
}
bool BagLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
    return true;
}
void BagLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
    
}
void BagLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    
}
void BagLayer::registerWithTouchDispatcher()
{
    //使用-128和CCMenu优先级相同,并且吞掉事件true//
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
 //   CCLayer::registerWithTouchDispatcher();
}
void BagLayer::nodeDidClick(CCNode* pNode,const CCPoint& clickPos)
{
    if (!this->isVisible()) {
        return;
    }
    CCObject* pObj = NULL;
    CCArray* pChildren = pNode->getChildren();
    
    CCARRAY_FOREACH(pChildren, pObj)
    {
        Item* pChild = (Item*)pObj;
        if(pChild)
        {
            CCRect fra = pChild->boundingBox();
            if (fra.containsPoint(clickPos))
            {
              {
                    ItemDidClick(pChild);
              }
                return;
            }
        }
    }
}