//*************************************************************************************

#include "stdafx.h"
#include "UICampaignWar.h"
#include "UICampaignCountDown.h"

#define COUNT_DOWN_TIME	10
//*************************************************************************************
namespace MG
{
	UICampaignWar::UICampaignWar()
		:mIsShow(false)
	{

	}

	UICampaignWar::~UICampaignWar()
	{

	}

	Bool UICampaignWar::openGui()
	{
		if (false == mIsShow)
		{
			return false;
		}

		UIObject::openGui();
		mIsShow = false;

		return true;
	}

	void UICampaignWar::setIsShow(Bool isShow)
	{
		mIsShow = isShow;
	}

	void UICampaignWar::setCountDownTime(Int seconds)
	{
		ITimeText* p = getLayout()->getTimeText("Text_CountDown");
		p->setEventTimeOut(eventCountDown, seconds * 1000, 1*1000);
		p->setCoolDownTime(seconds * 1000);
	}

	void UICampaignWar::eventCountDown(void* widget, Int leftTime)
	{
		//每秒播放滴答声音效果
		//GameSoundManager::getInstance().play(32);
		
		if (leftTime == (COUNT_DOWN_TIME + 1)*1000)
		{
			UICampaignCountDown::getInstance().setCountDownTime(COUNT_DOWN_TIME+1);
			UICampaignCountDown::getInstance().openGui();
			
			UICampaignWar::getInstance().closeGui();
		}
	}

}