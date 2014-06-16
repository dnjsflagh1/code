//****************************************************************************************************
#include "stdafx.h"
#include "newFuction.h"
#include "GuiDelegateElementPool.h"
//****************************************************************************************************
namespace MG
{
	void GuiFuction::update(Flt delta)
	{
		checkCloseEvent(delta);
	}
	//-----------------------------------------------------------------------------------
	void GuiFuction::setCloseEvent( MyGUI::Widget* pWidget, Flt lastTime, PVOID_CALLBACK func )
	{
		closeCallBack tempCallBack;
		tempCallBack.mpWidget = pWidget;
		tempCallBack.mLastTime = lastTime;
		tempCallBack.mpCallBack = func;

		mMapcloseCallBack[pWidget] = tempCallBack;

		if ( MGMath::MG_compareFloat(lastTime, 0) > 0 )
			mListCallBack.push_back(tempCallBack);
	}
	//-----------------------------------------------------------------------------------
	void GuiFuction::setCloseTime( MyGUI::Widget* pWidget, Flt lastTime )
	{
		std::map<MyGUI::Widget*, closeCallBack>::iterator iter = mMapcloseCallBack.find(pWidget);
		if ( mMapcloseCallBack.end() != iter )
		{
			iter->second.mLastTime = lastTime;
			if ( MGMath::MG_compareFloat(lastTime, 0) > 0 )
				mListCallBack.push_back(iter->second);
		}
		else
		{
			closeCallBack tempcloseCallBack;
			tempcloseCallBack.mLastTime = lastTime;
			tempcloseCallBack.mpCallBack = NULL;
			tempcloseCallBack.mpWidget = pWidget;

			mMapcloseCallBack[pWidget] = tempcloseCallBack;

			if ( MGMath::MG_compareFloat(lastTime, 0) > 0 )
				mListCallBack.push_back(tempcloseCallBack);
		}
	}
	//-----------------------------------------------------------------------------------
	void GuiFuction::checkCloseEvent(Flt delta)
	{
		std::list<closeCallBack>::iterator front = mListCallBack.begin();
		std::list<closeCallBack>::iterator back = mListCallBack.end();
		while ( front != back )
		{
			(*front).mLastTime -= delta;
			if ( MGMath::MG_compareFloat((*front).mLastTime, 0) <= 0 )
			{
				handleCloseEvent(&(*front));
				front = mListCallBack.erase(front);
				continue;
			}

			++front;
		}
	}
	//-----------------------------------------------------------------------------------
	void GuiFuction::handleCloseEvent( closeCallBack* pcloseCallBack )
	{
		//检查是否已经关闭。
		if ( pcloseCallBack->mpWidget->getVisible() == false )
			return;

		//关闭控件
		pcloseCallBack->mpWidget->setVisible(false);

		//调用Callback
		if ( pcloseCallBack->mpCallBack )
		{
			DEWidget* pDEWidget = GuiDgElmPool::getInstance().getDEWidget(pcloseCallBack->mpWidget);
			DYNAMIC_ASSERT(pDEWidget);
			(pcloseCallBack->mpCallBack)(pDEWidget);
		}	
	}
}