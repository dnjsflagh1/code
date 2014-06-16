//*************************************************************************************
#ifndef _UI_CAMPAIGN_WAR_H_
#define _UI_CAMPAIGN_WAR_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"
#include "CampaignNetPacket.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************

	//*************************************************************************************
	class  UICampaignWar : public UIObject
	{
	public:
		UICampaignWar();
		virtual ~UICampaignWar();
		SINGLETON_INSTANCE(UICampaignWar);


	public:
	virtual Bool openGui();


	public:
		void			setIsShow(Bool isShow);
		void			setCountDownTime(Int seconds);

	public:
		static void eventCountDown(void* widget, Int i);
	private:
		Bool			mIsShow;


	};
}

#endif	//_UI_CAMPAIGN_COUNTDOWN_H_