//*************************************************************************************
#ifndef _UI_BATTLE_SCORE_H_
#define _UI_BATTLE_SCORE_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"
#include "CampaignNetPacket.h"

//*************************************************************************************

namespace MG
{
	//*************************************************************************************
	struct BattleScoreInfo
	{
		Str16	strGeneralName;			//��������
		Str16	strKillGeneralPoint;	//���ܵн�
		Str16	strKillArmyPoint;		//���ܵб�
		Str16	strDestoryForcePoint;	//���ƾݵ�
		Str16	strConstructBuild;		//������ʩ
		Str16	strHealGeneralPoint;	//������
		Str16	strDeathPoint;			//��������
		Str16	strBattleAchievement;	//ս�۹���
		Str16	strRankList;			//ս������
	};

	struct ForceInfo
	{
		Str8	strWinResult;	//ʤ����Main_Icon_War\Wars\1  ʧ�ܣ�Main_Icon_War\Wars\2
		Str16	strRegionName;
		Str16	generalNum;
		Str16	troopNum;
		void clear()
		{
			strWinResult.clear();
			strRegionName.clear();
			generalNum.clear();
			troopNum.clear();
		}
	};
	//*************************************************************************************
	class  UIBattleScore : public UIObject
	{
	public:
		UIBattleScore();
		virtual ~UIBattleScore();
		SINGLETON_INSTANCE(UIBattleScore);

	private:
		void		setCloseTime(Flt seconds);


	public:
		virtual void setEvent();
		virtual Bool openGui();


		void		setTime(U32 time);
		U32			getTime();
		void		setCampaignResult(CampaignResult result);


		void	UIFresh();
		void	UIFreshByButton();
		void	UIFreshItem(U32 groupItemId);
		void	UIFreshByForceWinLose();
		
		static void onEventConfirm(void* widget);
		static void onEventLeave(void* widget);

		//��ʾToolTips
		static void onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);

		static void onCloseTimeCallBack(void* widget);


		void	setItemGroupId(U32 itemGroupId);
		U32		getItemGroupId() const;

	public:
		void	addForceInfo(const NetAddForceInfo* forceInfo, const FORCE winnerForce);
		void	addBattleScore(const Int num, const NetAddCampaignEnd* info, const FORCE winnerForce);

	private:
		void	UIFreshByForce(const FORCE force);
		void	UIFreshMainMixList(std::vector<BattleScoreInfo>* battleList);
		void	UIFreshText(const ForceInfo* forceInfo);

	private:

		std::vector<BattleScoreInfo>		mAttackBattleScoreList;
		std::vector<BattleScoreInfo>		mDefenseBattleScoreList;

		ForceInfo							mAttackInfo;
		ForceInfo							mDefenseInfo;

		FORCE								mCurBattleInfoForce;

		U32									mItemGroupId;
		U32									mCloseTimeSecond;

		CampaignResult				mCampaignResult;
	};
}

#endif	//_UI_BATTLE_SCORE_H_