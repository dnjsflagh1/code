//*************************************************************************************************//
#ifndef _H_BATTLE_CONFIG_
#define _H_BATTLE_CONFIG_
//*************************************************************************************************//

#define MAX_TROOP_NUM  5

//*************************************************************************************************//
namespace MG
{
	struct TroopGroupConfigInfo
	{
		Int		troopTemplateId;	//数组的数据 来自troopGroupNum
		Int		troopNum;
		Int		troopSolierNum;
	};

	struct CampConfigInfo
	{
		Int						armyNum;
		Int						troopGroupNum;
		TroopGroupConfigInfo	troopGroupInfo[10];
		
	};

	struct BattleConfigInfo
	{
		//Int		battleSecond;				//战斗持续时间 【秒】
		//Int		prepareSecond;				//战斗准备时间 【秒】

		CampConfigInfo	attackCampInfo[MAX_TROOP_NUM];	//攻击方的军营信息
		CampConfigInfo	defenseCampInfo[MAX_TROOP_NUM]; //防守方的军营信息

		BattleConfigInfo()
			//:battleSecond(0)
			//,prepareSecond(0)
		{
			memset(attackCampInfo,	0, sizeof(attackCampInfo));
			memset(defenseCampInfo,	0, sizeof(defenseCampInfo));
		}

		CampConfigInfo* getCampConfigInfoByForce(const FORCE force, const Int index)
		{
			if(FORCE_ATTACK == force)
			{
				return &(attackCampInfo[index]);
			}
			else if(FORCE_DEFENSE == force)
			{
				return &(defenseCampInfo[index]);
			}
			else
			{
                DEBUG_ASSERT_LOG(false, "load BattleConfigInfo error!!!");
			}
		}
	};

	//*************************************************************************************************//
	class BattleConfig
	{
	public:
	public:
		BattleConfig();
		~BattleConfig();
		SINGLETON_INSTANCE(BattleConfig);

	public:
		// MG_CN_MODIFY
		Bool                loadFile(std::wstring fileName, IMGExternalPackManager* packManager = NULL);
		Int                 getBattleConfigNum();
		BattleConfigInfo*	getBattleConfigByIndex(Int index);

	private:
		void				loadSingleCampInfo(UINI* ini, wchar_t* campName, CampConfigInfo* campInfo);	//读取 单个军营的信息

	protected:
		void                unloadFile();
	private:
		std::vector<BattleConfigInfo>        mBattleConfigList;
	};
}

#endif