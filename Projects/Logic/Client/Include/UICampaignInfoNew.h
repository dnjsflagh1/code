
//*************************************************************************************

#ifndef _UICAMPAIGNINFO_NEW_H_
#define _UICAMPAIGNINFO_NEW_H_

//*************************************************************************************

#include "UIObject.h"
#include "DataSetManager.h"
#include "ClientPreqs.h"

//*************************************************************************************

namespace MG
{
	struct UICampaignInfoNewSingle	//��ʾ��UI��Ϣ
	{
		Int					charArtIcon;					//ͷ��ID
		Int					level;
		Str16				clanName;
		Int					curHP;
		Int					maxHP;
		Int					curMP;
		Int					maxMP;
		Bool				isMe;						//�Ƿ������Լ�
		Bool				isReady;

		UICampaignInfoNewSingle()
		{
			clear();
		}

		void clear()
		{
			charArtIcon = 0;
			level = 0;
			curHP = 0;
			maxHP = 0;
			curMP = 0;
			maxMP = 0;
			isMe = false;
			clanName.clear();
			isReady = false;
		}

		Bool empty()
		{
			if (0 != charArtIcon ||
				0 != level ||
				0 != curHP ||
				0 != maxHP ||
				0 != curMP ||
				0 != maxMP ||
				false == clanName.empty())
			{
				return false;
			}

			return true;
		}
	};

	class  UICampaignInfoNew : public UIObject
	{
	public:
		UICampaignInfoNew();
		virtual ~UICampaignInfoNew();
		SINGLETON_INSTANCE(UICampaignInfoNew);


	public:
		virtual void setEvent();
		virtual Bool openGui();
		virtual void restore();


	public:
		static void onEventConfirm(void* widget);
		static void onEventCancel(void* widget);


	public:
		void 	UIReFresh();
		void 	UIReFreshMemberList();		//����ͨ�����Ϣ
		void	UIReFreshMemberByIndex(Int index, UICampaignInfoNewSingle* memberInfo);	//������������ͨ�����Ϣ
		void 	UIReFreshHost();			//��������Ϣ
		void	UIClear();
		void    UIClearMemberInfoByIndex(Int index);
		void	UIClearLeaderInfo();

		void 	addMemberInfo(Int position, UICampaignInfoNewSingle* info);
		void	modifyMemberInfo(Int position, UICampaignInfoNewSingle* memberInfo);
		void	clearMemberInfo(Int position);
		UICampaignInfoNewSingle*	getMemberInfoByPosition(Int position);
		
		void	modifyLeaderInfo(UICampaignInfoNewSingle* memberInfo);


		void	clearAllCampaignInfo();
		
		RegionIdType	getTargetRegionId() const	{ return mTargetRegionId; }
		void 	setTargetRegionId(const RegionIdType regionId) { mTargetRegionId = regionId; }

	private:
		void	createMemberForTest();

	private:
		SimpleMapDataSetManager<Int, UICampaignInfoNewSingle>	mMemberList;	//λ�������� 
		//std::vector<UICampaignInfoNewSingle>				mMemberList;
		SimpleMapDataSetManager<Int, UICampaignInfoNewSingle>				mLearder;

		RegionIdType			mTargetRegionId;

	};
}

#endif	//_UICAMPAIGNINFO_NEW_H_