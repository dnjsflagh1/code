//*************************************************************************************
#ifndef _UI_CAMPAIGN_BARRACK_H_
#define _UI_CAMPAIGN_BARRACK_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"
#include "CampaignNetPacket.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************

	struct CampControllerInfo
	{
		AccountIdType			accountId;
		Str16					accountIdStr;
		Str16					name;
		Bool					isController;		//是否是当前控制者
		PlayerCharacterIdType	playerCharacterId;
		Int						playerCharacterTemplateId;
		U32						charArtIcon;
		CampControllerInfo()
		{
			clear();
		}

		void clear()
		{
			accountIdStr.clear();
			name.clear();
			isController = false;
			playerCharacterId = 0;
			playerCharacterTemplateId = 0;
		}
	};

	struct CampInfoInBarrack
	{
		Str16	campHp;
		Str16	campTroopNum;
		Str16	campAllTroopNum;
	};

	//*************************************************************************************
	class  UICampaignBarrack : public UIObject
	{
	public:
		UICampaignBarrack();
		virtual ~UICampaignBarrack();
		SINGLETON_INSTANCE(UICampaignBarrack);


	public:
		virtual void setEvent();
		virtual Bool openGui();

		static void onEventConfirm(void* widget);

		static void onClickChangeTroopInfo(void* widget, Int index);

	public:
		void		setCampId(const CampIdType campId);
		CampIdType	getCampId() const;

		void		setCampOwnerId(const AccountIdType campOwnerId);
		AccountIdType getCampOwnerId() const;

		void				setTargetAccountId(AccountIdType accountId);
		AccountIdType		getTargetAccountId() const;

	public:
		void		UIFresh();
		void		UIFreshCharIcon(const CampControllerInfo* info);

	public:
		void		loadData(const CampIdType campId, const AccountIdType troopCurControllerAccountId, const Int addNum, const NetTroopControllerInfo* addInfo, const NetCampInfo* campInfo);
		void		clear();

	private:
		void		testCreate();

	private:
		CampIdType		mCampId;
		AccountIdType	mCampOwnerId;

		AccountIdType	mTargetAccountId;				//保存目标控制者的ID

		std::vector<CampControllerInfo>		mControllerList;

		CampInfoInBarrack				mCampInfo;

	};
}

#endif	//_UI_CAMPAIGN_BARRACK_H_