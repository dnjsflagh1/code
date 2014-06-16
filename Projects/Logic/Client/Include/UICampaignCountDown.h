//*************************************************************************************
#ifndef _UI_CAMPAIGN_COUNTDOWN_H_
#define _UI_CAMPAIGN_COUNTDOWN_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"
#include "CampaignNetPacket.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************

	//*************************************************************************************
	class  UICampaignCountDown : public UIObject
	{
	public:
		UICampaignCountDown();
		virtual ~UICampaignCountDown();
		SINGLETON_INSTANCE(UICampaignCountDown);


	public:
	virtual Bool openGui();


	public:
	void	setCountDownTime(U32 timeSecond);

	static void eventCountDown(void* widget, Int i);
		
	private:
		U32				mTime;
	};
}

#endif	//_UI_CAMPAIGN_COUNTDOWN_H_