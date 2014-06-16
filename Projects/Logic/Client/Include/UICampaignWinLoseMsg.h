//*************************************************************************************
#ifndef _UI_CAMPAIGN_WIN_LOSE_H_
#define _UI_CAMPAIGN_WIN_LOSE_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************
	class  UICampaignWinLoseMsg : public UIObject
	{
	public:
		UICampaignWinLoseMsg();
		virtual ~UICampaignWinLoseMsg();
		SINGLETON_INSTANCE(UICampaignWinLoseMsg);

	private:
		void		setCloseTime(Flt seconds);

	public:
		virtual void setEvent();
		virtual Bool openGui();
	
	public:
	
		void	UIShowResult();

		void		setTime(U32 time);
		void		setCampaignResult(CampaignResult result);

		static void onCloseTimeCallBack(void* widget);

	public:
		static void onEventConfirm(void* widget);



	private:
		U32							mCloseTimeSecond;

		CampaignResult				mCampaignResult;
	};
}

#endif	//_UI_CAMPAIGN_WIN_LOSE_H_