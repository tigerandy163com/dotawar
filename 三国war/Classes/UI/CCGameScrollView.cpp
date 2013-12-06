#include "CCGameScrollView.h"


CCCGameScrollView::CCCGameScrollView()
	: m_fAdjustSpeed(ADJUST_ANIM_VELOCITY)
	, m_bSetDirection(false)
	, m_nCurPage(0)
{

}

CCCGameScrollView::~CCCGameScrollView()
{

}



bool CCCGameScrollView::init()
{
	if (!CCScrollView::init())
	{
  //      registerWithTouchDispatcher();
		return false;
	}
    
	return true;
}


bool CCCGameScrollView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint touchPoint=pTouch->getLocation();
    
    //    将世界坐标转换为当前父View的本地坐标系
    
    CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
    //CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    if (!this->boundingBox().containsPoint(reallyPoint)) {
        return false;
    }
	m_BeginOffset = getContentOffset();
   
    return  CCScrollView::ccTouchBegan(pTouch, pEvent);;
}

void CCCGameScrollView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchMoved(pTouch, pEvent);
}

void CCCGameScrollView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);

	CCScrollView::ccTouchEnded(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();

	//点击Page的功能
	if (m_BeginOffset.equals(m_EndOffset))
	{
		int nPage = -1;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			nPage = abs(m_EndOffset.x / (int)m_CellSize.width);
		}
		else
		{
			nPage = abs(m_EndOffset.y / (int)m_CellSize.height);
		}
		CCCGameScrollViewDelegate *pDele = (CCCGameScrollViewDelegate *)m_pDelegate;
		CCNode *pPgae = m_pContainer->getChildByTag(nPage);
		CCRect rcContent;
		rcContent.origin = pPgae->getPosition();
      
		rcContent.size = pPgae->getContentSize();
//		rcContent.origin.x -= rcContent.size.width / 2;
//	rcContent.origin.y -= rcContent.size.height / 2;

		CCPoint pos = touchPoint;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pos.x += nPage * m_CellSize.width;
		}
		else
		{
			pos.y -= nPage * m_CellSize.height;
		}

		if (rcContent.containsPoint(pos))
		{
			pDele->scrollViewClick(m_EndOffset, touchPoint, pPgae, nPage);
		}
		return ;
	}

	//自动调整
	adjustScrollView(m_BeginOffset, m_EndOffset);
}

void CCCGameScrollView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchCancelled(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();
	adjustScrollView(m_BeginOffset, m_EndOffset);
}


void CCCGameScrollView::adjustScrollView( const cocos2d::CCPoint &oBegin, const cocos2d::CCPoint &oEnd)
{
	int nPage = 0;
	int nAdjustPage = 0;

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		nPage = abs(oBegin.x / (int)m_CellSize.width);
		int nDis = oEnd.x - oBegin.x;

		if (nDis < -getViewSize().width / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else if (nDis > getViewSize().width / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}
	else
	{
		nPage = abs(oBegin.y / (int)m_CellSize.height);
		int nDis = oEnd.y - oBegin.y;

		if (nDis < -getViewSize().height / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else if (nDis > getViewSize().height / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}

	nAdjustPage = MIN(nAdjustPage, m_nPageCount - 1);
	nAdjustPage = MAX(nAdjustPage, 0);

	scrollToPage(nAdjustPage);
}


void CCCGameScrollView::scrollToPage( int nPage )
{
	// 关闭CCScrollView中的自调整
	unscheduleAllSelectors();

	CCPoint oOffset = getContentOffset();
	// 调整位置
	CCPoint adjustPos;
	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		adjustPos = ccp(-m_CellSize.width * nPage, 0);
	}
	else
	{
		adjustPos = ccp(0, m_CellSize.height * nPage);
	}
	// 调整动画时间
	float adjustAnimDelay = ccpDistance(adjustPos, oOffset) / m_fAdjustSpeed;

	// 调整位置
	setContentOffsetInDuration(adjustPos, adjustAnimDelay);

	if (nPage != m_nCurPage)
	{
		m_nCurPage = nPage;
		scheduleOnce(schedule_selector(CCCGameScrollView::onScrollEnd), adjustAnimDelay);
	}
}


void CCCGameScrollView::onScrollEnd(float fDelay)
{
	CCCGameScrollViewDelegate *pDele = (CCCGameScrollViewDelegate *)m_pDelegate;
	pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
}



void CCCGameScrollView::scrollToNextPage()
{
	int nCurPage = getCurPage();
	if (nCurPage >= m_nPageCount - 1)
	{
		return ;
	}
	scrollToPage(nCurPage + 1);
}

void CCCGameScrollView::scrollToPrePage()
{
	int nCurPage = getCurPage();
	if (nCurPage <= 0)
	{
		return ;
	}
	scrollToPage(nCurPage - 1);
}


bool CCCGameScrollView::createContainer(CCCGameScrollViewDelegate *pDele, int nCount, const cocos2d::CCSize &oSize )
{
	CCAssert(m_bSetDirection, "must call setDirection first!!!");
	m_nPageCount = nCount;
	m_CellSize = oSize;
	setDelegate(pDele);
    if (nCount==1) {
        
    }
	CCLayer *pContainer = CCLayer::create();

	CCSize winSize =CCSizeZero ; //CCDirector::sharedDirector()->getVisibleSize();
	for (int i = 0; i < nCount; ++i)
	{
		CCNode *pNode = CCNode::create();
        pNode->setAnchorPoint(ccp(0, 0));
		pDele->scrollViewInitPage(this, pNode, i);

		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pNode->setPosition(ccp( i * oSize.width, 0));
		}
		else
		{
			pNode->setPosition(ccp(0,i * oSize.height));
		}

		pNode->setContentSize(m_CellSize);
		pNode->setTag(i);
		pContainer->addChild(pNode);
	}
    
    setViewSize(m_CellSize);
	setContainer(pContainer);
     
	return true;
}

int CCCGameScrollView::getCurPage()
{
	return m_nCurPage;
}

void CCCGameScrollView::setCurPage( int nPage )
{
	CCAssert(m_nCurPage >= 0 && m_nCurPage < m_nPageCount, "");

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		setContentOffset(ccp(-nPage * m_CellSize.width, 0));
	}
	else
	{
		setContentOffset(ccp(0, nPage * m_CellSize.height));
	}
	m_nCurPage = nPage;
}

int CCCGameScrollView::getPageCount()
{
	return m_nPageCount;
}

CCNode *CCCGameScrollView::getPage( int nPage )
{
	return m_pContainer->getChildByTag(nPage);
}

void CCCGameScrollView::setDirection( CCScrollViewDirection eDirection )
{
	CCAssert(eDirection != kCCScrollViewDirectionBoth, "Does not suppost kCCScrollViewDirectionBoth!!!");
	CCScrollView::setDirection(eDirection);
	m_bSetDirection = true;
}
