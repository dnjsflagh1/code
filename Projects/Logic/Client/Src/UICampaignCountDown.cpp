//*************************************************************************************

#include "stdafx.h"
#include "UICampaignCountDown.h"
#include "GameSoundManager.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
#include "CSceneManager.h"
#include "CRegionObject.h"

//*************************************************************************************
#define  COUNT_DOWN_SOUND		60014
#define  CAMPAIGN_BEGIN_SOUND	60015
//*************************************************************************************
namespace MG
{
	UICampaignCountDown::UICampaignCountDown()
		:mTime(0)
	{

	}

	UICampaignCountDown::~UICampaignCountDown()
	{

	}

	Bool UICampaignCountDown::openGui()
	{
		if (mTime > 0)
		{
			GameSoundManager::getInstance().play(COUNT_DOWN_SOUND);
			UIObject::openGui();
			mTime = 0;
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}

	void UICampaignCountDown::setCountDownTime(U32 timeSecond)
	{
		//设置时间
		{
			IImage* imageTime = getLayout()->getImage("edt_time");
			DYNAMIC_ASSERT(NULL != imageTime);
			imageTime->getWidget()->setVisible(true);
			imageTime->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, timeSecond*1000, timeSecond*1000);
			imageTime->setFrameChangeEvent(eventCountDown);

			mTime = timeSecond;
		}
	}

	void UICampaignCountDown::eventCountDown(void* widget, Int leftTime)
	{
		if (leftTime > 1)
		{
			//每秒播放滴答声音效果
			GameSoundManager::getInstance().play(COUNT_DOWN_SOUND);
		}

		if (leftTime == 1)
		{
			//战斗开始声音
			GameSoundManager::getInstance().play(CAMPAIGN_BEGIN_SOUND);
		}
		if (leftTime == 0)
		{
			UICampaignCountDown::getInstance().closeGui();


			UICampaignFight::getInstance().closeGui();
			UICampaignWar::getInstance().closeGui();
		}
	}
}