//*************************************************************************************
#ifndef _UICAMPAIGN_SYSTEM_NEW_H_
#define _UICAMPAIGN_SYSTEM_NEW_H_
//*************************************************************************************
#include "UIObject.h"
#include "ClientPreqs.h"
//*************************************************************************************



namespace MG
{
	class  UICampaignSystemNew
	{
	public:
		UICampaignSystemNew();
		virtual ~UICampaignSystemNew();
		SINGLETON_INSTANCE(UICampaignSystemNew);

		Bool openGui();
		Bool closeGui();
	};
}

#endif	//_UICAMPAIGN_SYSTEM_H_