//*************************************************************************************
#ifndef _UI_CAMPAIGN_CAMPAIGNFIGHT_H_
#define _UI_CAMPAIGN_CAMPAIGNFIGHT_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"
#include "CampaignNetPacket.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************
	struct UICampaignFightInfo
	{
		U32		charArtIcon;
	};
	//*************************************************************************************
	class  UICampaignFight : public UIObject
	{
	public:
		UICampaignFight();
		virtual ~UICampaignFight();
		SINGLETON_INSTANCE(UICampaignFight);


	public:
	virtual Bool openGui();

	virtual	void	restore();


	public:
		void		UIFresh();

	public:
		Bool			getIsShow() const;
		void			setIsShow(Bool isShow);

		void			clear();
		void			addCampaignFightInfo(FORCE force, U32 charArtIcon, Byte pos, Bool isHost);

	private:
		Bool			mIsShow;

		std::map<POSITION, UICampaignFightInfo>	mAttackList;
		std::map<POSITION, UICampaignFightInfo>	mDefenseList;

	};
}

#endif	//_UI_CAMPAIGN_CAMPAIGNFIGHT_H_