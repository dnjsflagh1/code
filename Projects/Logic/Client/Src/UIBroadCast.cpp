//***************************************************************************************************
#include "stdafx.h"
#include "UIBroadCast.h"
//***************************************************************************************************
namespace MG
{
    UISystemInfoBroadCast::UISystemInfoBroadCast()
    {
		mRollState = UI_ROLL_STATE_PLAY;
    }
    //----------------------------------------------------------------------------------------
    UISystemInfoBroadCast::~UISystemInfoBroadCast()
    {
		if (mSystemBroadCastDatas.empty())
		{
			return;
		}
		for(std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin(); it != mSystemBroadCastDatas.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}
		mSystemBroadCastDatas.clear();
    }
    //----------------------------------------------------------------------------------------
    void UISystemInfoBroadCast::setEvent()
    {

    }
	//----------------------------------------------------------------------------------------
	void UISystemInfoBroadCast::update(Flt delta)
	{
		if (!isOpen())
		{
			return;
		}
		IText* rollText = getLayout()->getText("text_roll");
		IImage* rollImage = getLayout()->getImage("_Main");
		if (!rollImage || !rollText)
		{
			return;
		}
		
		switch(mRollState)
		{
		case UI_ROLL_STATE_PLAY:
			{
				if (!mCurrData)
				{
					if (mSystemBroadCastDatas.empty())
					{
						mRollState = UI_ROLL_STATE_END;
						return;
					}
					MG_SAFE_DELETE(mCurrData);
					std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin();
					mCurrData = *it;
					mSystemBroadCastDatas.pop_front();
					rollText->getWidget()->setCaption(mCurrData->Data);
				}
				else if ( mCurrData->times <= 0)
				{
					MG_SAFE_DELETE(mCurrData);
					if (mSystemBroadCastDatas.empty())
					{
						mRollState = UI_ROLL_STATE_END;
						return;
					}
					std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin();
					mCurrData = *it;
					mSystemBroadCastDatas.pop_front();
					rollText->getWidget()->setCaption(mCurrData->Data);
				}

				Vec2 rollTextPos = rollText->getWidget()->getPosition();
				Vec2 rollEditSize = rollImage->getWidget()->getSize();
				Vec2 newPos; 
				newPos.y = rollTextPos.y;
				if (rollTextPos.x + rollEditSize.x <= 0)
				{
					newPos.x = rollEditSize.x;
					mCurrData->times--;
				}
				else
				{
					Flt x = rollTextPos.x - mCurrData->speed;
					newPos.x = x;
				}
				rollText->getWidget()->setPosition(newPos);
			}
			break;
		case UI_ROLL_STATE_END:
			{
				closeGui();
			}
			break;
		case UI_ROLL_STATE_STOP:
			{
				
			}
			break;
		}
		
	}
	//----------------------------------------------------------------------------------------
	void UISystemInfoBroadCast::addData( Char16* text,Int speed /*= 0.9f*/,Int times /*= 3*/ )
	{

		if (speed > 4|| speed < 1)
		{
			return;
		}
		if (times < 0 || times > 10)
		{
			return;
		}
		if (!text)
		{
			return;
		}

		BroadCastData* data = MG_NEW BroadCastData;
		data->speed = speed;
		data->times = times;
		data->Data = text;
		mSystemBroadCastDatas.push_back(data);

		if (mRollState == UI_ROLL_STATE_END)
		{
			mRollState = UI_ROLL_STATE_PLAY;
			openGui();
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemInfoBroadCast::setState( UI_ROLL_STATE rollState )
	{
		mRollState = rollState;
		if (mRollState == UI_ROLL_STATE_PLAY)
		{
			openGui();
		}
	}

	//*************************************************************************************
	UIGMInfoBroadCast::UIGMInfoBroadCast()
	{
		mRollState = UI_ROLL_STATE_PLAY;
	}
	//----------------------------------------------------------------------------------------
	UIGMInfoBroadCast::~UIGMInfoBroadCast()
	{
		if (mSystemBroadCastDatas.empty())
		{
			return;
		}
		for(std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin(); it != mSystemBroadCastDatas.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}
		mSystemBroadCastDatas.clear();
	}
	//----------------------------------------------------------------------------------------
	void UIGMInfoBroadCast::setEvent()
	{

	}
	//----------------------------------------------------------------------------------------
	void UIGMInfoBroadCast::update(Flt delta)
	{
		if (!isOpen())
		{
			return;
		}
		IText* rollText = getLayout()->getText("text_roll");
		IImage* rollImage = getLayout()->getImage("_Main");
		if (!rollImage || !rollText)
		{
			return;
		}

		switch(mRollState)
		{
		case UI_ROLL_STATE_PLAY:
			{
				if (!mCurrData)
				{
					if (mSystemBroadCastDatas.empty())
					{
						mRollState = UI_ROLL_STATE_END;
						return;
					}
					MG_SAFE_DELETE(mCurrData);
					std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin();
					mCurrData = *it;
					mSystemBroadCastDatas.pop_front();
					rollText->getWidget()->setCaption(mCurrData->Data);
				}
				else if ( mCurrData->times <= 0)
				{
					MG_SAFE_DELETE(mCurrData);
					if (mSystemBroadCastDatas.empty())
					{
						mRollState = UI_ROLL_STATE_END;
						return;
					}
					std::list<BroadCastData*>::iterator it = mSystemBroadCastDatas.begin();
					mCurrData = *it;
					mSystemBroadCastDatas.pop_front();
					rollText->getWidget()->setCaption(mCurrData->Data);
				}

				Vec2 rollTextPos = rollText->getWidget()->getPosition();
				Vec2 rollEditSize = rollImage->getWidget()->getSize();
				Vec2 newPos; 
				newPos.y = rollTextPos.y;
				if (rollTextPos.x + rollEditSize.x <= 0)
				{
					newPos.x = rollEditSize.x;
					mCurrData->times--;
				}
				else
				{
					Flt x = rollTextPos.x - mCurrData->speed;
					newPos.x = x;
				}
				rollText->getWidget()->setPosition(newPos);
			}
			break;
		case UI_ROLL_STATE_END:
			{
				closeGui();

			}
			break;
		case UI_ROLL_STATE_STOP:
			{

			}
			break;
		}

	}
	//----------------------------------------------------------------------------------------
	void UIGMInfoBroadCast::addData( Char16* text,Int speed /*= 0.9f*/,Int times /*= 3*/ )
	{

		if (speed > 4|| speed < 1)
		{
			return;
		}
		if (times < 0 || times > 10)
		{
			return;
		}
		if (!text)
		{
			return;
		}

		BroadCastData* data = MG_NEW BroadCastData;
		data->speed = speed;
		data->times = times;
		data->Data = text;
		mSystemBroadCastDatas.push_back(data);

		if (mRollState == UI_ROLL_STATE_END)
		{
			mRollState = UI_ROLL_STATE_PLAY;
			openGui();
		}
	}
	//----------------------------------------------------------------------------------------
	void UIGMInfoBroadCast::setState( UI_ROLL_STATE rollState )
	{
		mRollState = rollState;
		if (mRollState != UI_ROLL_STATE_STOP)
		{
			openGui();
		}
	}


	//----------------------------------------------------------------------------------------
}