//***************************************************************************************************
#include "stdafx.h"
#include "UIGameTick.h"
//***************************************************************************************************
namespace MG
{
    UIGameTick::UIGameTick()
    {
		mAlphaReduce = 0.004f;
    }
    //----------------------------------------------------------------------------------------
    UIGameTick::~UIGameTick()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIGameTick::setEvent()
    {

    }

	void UIGameTick::update()
	{
		if (!isOpen())
		{
			return;
		}
		static U32 tick = MGTimeOp::getCurrTick();
		static U32 dis = 1000;
		if ( MGTimeOp::getCurrTick() - tick > dis)
		{
			tick = MGTimeOp::getCurrTick();
			static Char16 temp[64] = {0};
			MGStrOp::sprintf(temp,64,L"%d%d",tick,tick);
			addStr(temp);
		}
		
		Char8 temp[16] = {0};
		for (Int i = 0; i < tick_count; i++)
		{
			if (!mData[i].isEmpty)
			{
				if (mData[i].alpha < 0.00001)
				{
					mData[i].alpha = 0.0f;
					mData[i].isEmpty = true;
				}
				MGStrOp::sprintf(temp,16,"text_%d",i);
				mData[i].alpha -= mAlphaReduce;
				getLayout()->getText(temp)->getWidget()->setAlpha(mData[i].alpha);
			}

		}
	}

	void UIGameTick::addStr( Char16* str )
	{

		Char8 temp[16] = {0};
		for (Int i  = tick_count - 1; i > 0 ; i--)
		{
			if (!mData[i - 1].isEmpty)
			{
				mData[i].str = mData[i - 1].str;
				mData[i].alpha = mData[i - 1].alpha;
				MGStrOp::sprintf(temp,16,"text_%d",i );
				getLayout()->getText(temp)->getWidget()->setAlpha(mData[i].alpha);
				getLayout()->getText(temp)->getWidget()->setCaption(mData[i].str.c_str());
			}		
		}
	
		mData[0].isEmpty = false;
		mData[0].str = str;
		mData[0].alpha =1.0f;
		getLayout()->getText("text_0")->getWidget()->setCaption(mData[0].str.c_str());
		getLayout()->getText("text_0")->getWidget()->setAlpha(mData[0].alpha);
	}

	void UIGameTick::setAlphaReduce( Flt alpha )
	{
		mAlphaReduce = alpha;
	}

}