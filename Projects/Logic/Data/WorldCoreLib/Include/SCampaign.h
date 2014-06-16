//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: SCampaign.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:18
//   Description: 
//			��������ʹ�õ�ս��ʵ��
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////

#ifndef _S_CAMPAIGN_H_
#define _S_CAMPAIGN_H_

/******************************************************************************/

#include "WorldCorePreqs.h"
#include "DataSetManager.h"

#include "InstanceTimeListCsv.h"
//#include "Campaign.h"

/******************************************************************************/

#define CAMPAIGN_BATTLE_TIME		(30*1000*1000)		//��Ϸ��ʼ30���Ӻ����

/******************************************************************************/
namespace MG
{
	enum ARMY_READY_STATE
	{
		ARMY_READY_INITIAL,
		ARMY_READY_CANCEL,
		ARMY_READY_CONFIRM,
		ARMY_READY_MAX,
	};





	//�佫��Ϣ
	struct ClanArmyPlayerCharacterInfo	
	{
		U64		playerCharacterId;
		Str16	playerCharacterName;
		U32		charArtIcon;

		ClanArmyPlayerCharacterInfo()
			:playerCharacterId(0)
			,charArtIcon(0)
		{
			playerCharacterName.reserve(MAX_CHARACTER_NAME_LEN);
		}

		void clear()
		{
			playerCharacterId = 0;
			charArtIcon = 0;

		}
	};

	//������Ϣ
	struct ClanArmyTroopInfo
	{
		U64		troopId;
		U64		troopTemplateId;
		//Char16	troopName[MAX_TROOP_NAME_LEN];
		ClanArmyTroopInfo()
			:troopId(0)
			,troopTemplateId(0)
		{

		}
	};

	//�佫�Ͳ����б�
	struct ClanArmy
	{
		NetIdType						frontServerNetId;
		NetIdType						clientNetId;
		U64								accountId;
		ClanIdType						clanID;
		Str16							clanName;
		FORCE							force;
		ARMY_READY_STATE				readyState;
		POSITION						position;
		Bool							isLeave;

		ClanArmyPlayerCharacterInfo		playerCharacterInfo;
		
		ClanArmy()
		{
			clear();
		}

		void clear()
		{
			frontServerNetId = 0;
			clientNetId = 0;
			accountId = 0;
			clanID = 0;
			force = FORCE_INIT;
			readyState = ARMY_READY_INITIAL;
			clanName.clear();
			isLeave = false;
			playerCharacterInfo.clear();
		}

		Bool empty()
		{
			if (0 != frontServerNetId	||
				0 != clientNetId		||
				0 != accountId			||
				0 != clanID				||
				FORCE_INIT != force		||
				ARMY_READY_INITIAL != readyState ||
				false == clanName.empty())
			{
				return false;
			}

			return true;
		}

	};

	/******************************************************************************/
	class SCampaign
	{
	public:
		SCampaign(AccountIdType creatorAccountId, ClanIdType creatorClanId, const Char16* creatorClanName, const Char16* campaignName, RegionIdType regionId, REGION_OBJ_TYPE regionType);
		~SCampaign();

		PlaceListCsvInfo*				getPlaceListInfo();
		InstanceAtkListCsvInfo*			getAtkListInfo();
		InstanceTimeListCsvInfo*		getTimeListInfo();

	public:

		AccountIdType	getAttackCampOwnerAccountId() const;
		void			setAttackCampOwnerAccountId(const AccountIdType accountId);
		AccountIdType	getDefenseCampOwnerAccountId() const;
		void			setDefenseCampOwnerAccountId(const AccountIdType accountId);

		//�������������в��� ��Ӫ������
		AccountIdType	getRandomCampOwnerAccountId(const FORCE force, const AccountIdType currentOwnerAccountId);
		AccountIdType	getRandomCampOwnerAccountId(std::map<POSITION, ClanArmy*>* clanList, const AccountIdType currentOwnerAccountId);

		ClanIdType		getCampaignCreatorClanId() const;
		AccountIdType	getCampaignCreatorAccountId() const;
		ClanIdType		getCampaignId() const;
		Str16&			getCampaignName();
		Str16&			getCampaignCreatorClanName();

		RegionIdType	getCampaignTargetRegionId() const;
		REGION_OBJ_TYPE getCampaignTargetRegionType() const;

		//���ս����ʼǰ׼��ʱ��
		void			setPrepareTimeSecond(U32 prepareTime);
		U32				getPrepareTimeSecond() const;

		void					setCampaignTargetInstanceId(InstanceUIdType campaignInstanceUid);
		InstanceUIdType			getCampaignTargetInstance() const;
	
		std::map<POSITION, ClanArmy*>*  getAttackHostList();
		std::map<POSITION, ClanArmy*>*  getAttackMemberList();
		std::map<POSITION, ClanArmy*>*  getDefenseMemberList();

		ClanArmy*		getAttackHostClanArmyInfo();
		
		Int				getDefenseMemberSize();

		// �����б�����
		ClanArmy*		getAttackHostMemberInfoByClanId(const ClanIdType clanId);	
		ClanArmy*		getAttackHostInfoByClanId();								//���ҷ�����Ϣ

		//���ҿ�λ��
		ClanArmy*		getAttackArmyByEmptyPosition(const ClanIdType clanId);
		
		//�����Լ�����Ϣ
		ClanArmy*		getAttackMemberInfoByClanId(const ClanIdType clanId);
		ClanArmy*		getDefenseMemberInfoByClanId(const ClanIdType clanId);
		ClanArmy*		getClanArmyByClanId(const ClanIdType clanId);		//�����б�����
		
		//�ҿ�λ��
		ClanArmy*		getAttackArmyByEmptyPosition();
		ClanArmy*		getDefenseArmyByEmptyPosition();
		
	
		//���е���Ҷ��뿪�� ����������
		Bool			isAllClanLeave();
	public:
		Bool 	joinAttackList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName);
		Bool 	joinDefenseList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName);
		Bool 	setCampaignReadyStateMySelf(ClanIdType myClanId, ARMY_READY_STATE readyState);

		void 	setEndBattleTime(const U64 seconds);
		U64 	getEndBattleTime() const;

		void	setDestroyBattleTime(const U64 seconds);
		U64		getDestroyBattleTime() const;

		Bool	canStartBattle(const ClanIdType hostClanId);	//������ս���Ƿ����㿪ʼ����
		Bool	setReady(const ClanIdType myClanId);			//����׼��


		void	setAttackRealMemberNum(Int num);
		Int		getAttackRealMemberNum() const;
		void	setDefenseRealMemberNum(Int num);
		Int		getDefenseRealMemberNum() const;
	

		FORCE	getWinnerForce() const						{ return mWinnerForce;			}
		void	setWinnerForce(const FORCE winnerForce)		{ mWinnerForce = winnerForce;	}

		Bool	getCampaignIsStart() const			{ return mIsStart;		}
		void	setCampaignIsStart(Bool isStart)	{ mIsStart = isStart;	}


	private:
		ClanArmy*		getMemberInfoByClanId(const ClanIdType clanId, std::map<POSITION, ClanArmy*>* memberList);
		ClanArmy*		getArmyByEmptyPosition(std::map<POSITION, ClanArmy*>* memberList);


	private:
		//SRealRegionObject*		mOwnerRealRegionObject;				//����Ŀ��ָ��

		AccountIdType					mAttackCampOwnerAccountId;			//�������о�Ӫ�ķ���Ȩ������ý�ɫ�뿪�������ѡһ�� Ĭ���Ƿ���
		AccountIdType					mDefenseCampOwnerAccountId;

		AccountIdType					mCampaignCreatorAccountId;					//�������AccountId
		ClanIdType						mCampaignCreatorClanId;						//�������
		Str16							mCampaignCreatorClanName;					//�����������
		Str16							mCampaignName;								//ս������
		
		RegionIdType					mCampaignTargetRegionId;
		REGION_OBJ_TYPE					mCampaignTargetRegionType;
		InstanceUIdType					mCampaignInstanceUid;						//MapServer�����ĸ���
		U64								mPrepareEndTime;							//ս����ʼǰ׼��ʱ�� ����ʱ��

		PlaceListCsvInfo*				mPlaceListInfo;
		InstanceAtkListCsvInfo*			mAtkListInfo;
		InstanceTimeListCsvInfo*		mTimeListInfo;

		U64						mStartBattleTime;							//����ʱ��
		U64						mEndBattleTime;								//����ʱ�䡾�ر�ս�ۡ�
		U64						mDestoryBattleTime;							//���������� �����ת��ͼ
		U64						mMarchTime;									//�о�ʱ��
		U64						mReachTime;									//����ʱ��	����Ҫ���������

		FORCE					mWinnerForce;								//ʤ���ߵ�����
		Bool					mIsStart;									//�Ƿ��Ѿ���ʼ

		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanAttackHost;	//����������
		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanAttackList;	//�������б�
		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanDenfenseList;	//���ط��б�

		Int						mAttackMemberNum;									// �����������
		Int						mDefenseMemberNum;									// �����������
	private:
		SCampaign();
		SCampaign(const SCampaign&);
		SCampaign& operator=(const SCampaign&);
	};
}

#endif	//_S_CAMPAIGN_H_