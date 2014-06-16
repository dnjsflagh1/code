
//*************************************************************************************

#ifndef _UICAMPAIGN_INVITE_DEFENSE_H_
#define _UICAMPAIGN_INVITE_DEFENSE_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"

//*************************************************************************************

namespace MG
{
	class  UICampaignInviteDefense : public UIObject
	{
	public:
		UICampaignInviteDefense();
		virtual ~UICampaignInviteDefense();
		SINGLETON_INSTANCE(UICampaignInviteDefense);


	public:
		virtual void setEvent();
		virtual Bool openGui();

	public:
		static void onEventConfirm(void* widget);
		static void onEventCancel(void* widget);


		void	setCampaignInfo(const RegionIdType mRegionId, const InstanceIdType mInstanceId, const CampaignIdType mCampaignId);

		RegionIdType 	getCampaignTargetRegionId();
		InstanceIdType 	getCampaignInstanceId();
		CampaignIdType 	getCampaignId();
		
	public:
		void 	UIReFresh();


	private:
		RegionIdType		mRegionId;
		InstanceIdType		mInstanceId;
		CampaignIdType		mCampaignId;



	};
}

#endif	//_UICAMPAIGN_INVITE_DEFENSE_H_