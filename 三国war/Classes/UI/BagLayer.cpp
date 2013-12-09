//
//  BagLayer.cpp
//  三国war
//
//  Created by chunyu.wang on 13-11-28.
//
//

#include "BagLayer.h"
#include "Item.h"
#include "Helper.h"
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
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(250, 100, 250, 200)));
        
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
      
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
        m_ScrollView->setViewSize(CCSizeMake(ww,hh));
        m_ScrollView->createContainer(this, pageCount, CCSizeMake(ww,hh));
        //一般是原点
       
        m_ScrollView->setAnchorPoint(CCPointZero);
        m_ScrollView->retain();
        //视口的尺寸(一般是屏幕的尺寸)
        setContentSize(CCSizeMake(ww+150, winsize.height));
  //      this->setContentSize(CCSizeMake(ww,hh));
  //      this->addChild(m_ScrollView);
   //     registerWithTouchDispatcher();
        m_Htab = HTabGroupLayerBase::create();
        m_Htab->creatTabsWithCount(this, 4,AlignRight,this->getContentSize());
        m_Htab->setAnchorPoint(CCPointZero);
        m_Htab->setPosition(0, 0);
        m_Htab->retain();
        this->addChild(m_Htab);
        selectItem = NULL;
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
                item = Item::Create(-1, tag, 2, NULL,CCSprite::createWithSpriteFrameName("BagItemBgNormal"),CCSprite::createWithSpriteFrameName("BagItemBgDown"));
            }else
            {
            item = Item::Create(500173, tag, 2, CCSprite::create("500173.png"),CCSprite::createWithSpriteFrameName("BagItemBgNormal"),CCSprite::createWithSpriteFrameName("BagItemBgDown"));
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

 void BagLayer::scrollViewClick(const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pScroll, int nPage )
{
    nodeDidClick(pScroll, oPoint);
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
    Item* selItem = (Item*)clickNode;
    selItem->singleClickSprite();
}
//bool BagLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
//    return true;
//}
//void BagLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
//{
//    
//}
//void BagLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
//{
//    
//}
//void BagLayer::registerWithTouchDispatcher()
//{
//    //使用-128和CCMenu优先级相同,并且吞掉事件true//
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
// //   CCLayer::registerWithTouchDispatcher();
//}
 CCNode* BagLayer::viewTabIndex(CCNode* pTabLayer,int index)
{
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCNode* node = NULL;
    switch (index) {
        case 0:
        {
//            node = CCNode::create();
//            node->addChild(m_ScrollView);
//            node->setAnchorPoint(CCPointZero);
//            node->setContentSize(m_ScrollView->boundingBox().size);
            m_ScrollView->setPosition(0, 0);
            node = m_ScrollView;
        }
            
            
            break;
        case 1:
            node = CCLabelTTF::create(
                                      "01 page", "Arial", 22);
            break;
        case 2:
            node = CCLabelTTF::create(
                                      "02 page", "Arial", 22);
            break;
        case 3:
            node = CCLabelTTF::create(
                                      "03 page", "Arial", 22);
            break;
        default:
            node = CCLabelTTF::create(
                                      "no page", "Arial", 22);
            break;
    }
    CCRect size = node->boundingBox();
    node->setPosition(ccp(200, (winsize.height - size.size.height)/2+20));
    return node;
}
 bool BagLayer::tabViewInitPage( CCNode* pTabLayer,cocos2d::CCNode *pPage, int nPage)
{
    char str[64] = {0};
    sprintf(str, "%d", nPage);
    CCMenuItem* menuitem = CCMenuItem::create();
    CCLabelTTF* text = CCLabelTTF::create(
                                          str, "Arial", 22);
    text->setAnchorPoint(CCPointZero);
    text->setColor(ccBLACK);
    menuitem->addChild(text);
    pPage->addChild(menuitem);
    return true;
}
  void BagLayer::tabItemClick(CCNode* pTabLayer,CCNode* object)
{
    
}
 void BagLayer::scrollViewTouchBegan(cocos2d::CCNode *pScroll,CCPoint pos)
{
    if (!m_ScrollView->isVisible()) {
        return;
    }
    selectItem = (Item*)Helper::getTouchItem(pScroll, pos);
    if (selectItem) {
       
        selectItem->itemTouchBegan();
    }
}

 void BagLayer::scrollViewTouchMoved(cocos2d::CCNode *pScroll,CCPoint pos )
{
    if (!m_ScrollView->isVisible()) {
        return;
    }
    if (selectItem) {
        selectItem->itemTouchMoved();
    }
}

 void BagLayer::scrollViewTouchEnded(cocos2d::CCNode *pScroll,CCPoint pos)
{
    if (!m_ScrollView->isVisible()) {
        return;
    }
    if (selectItem) {
        selectItem->itemTouchEnded();
    }
}

 void BagLayer::scrollViewTouchCancelled(cocos2d::CCNode *pScroll, CCPoint pos)
{
    if (!m_ScrollView->isVisible()) {
        return;
    }
    if (selectItem) {
        selectItem->itemTouchCancelled();
    }
}
void BagLayer::nodeDidClick(CCNode* pNode,const CCPoint& clickPos)
{
    if (!this->isVisible()) {
        return;
    }
    CCNode* node =Helper::getTouchItem(pNode, clickPos);
    if (node) {
   //      ItemDidClick(node);
    }
}

