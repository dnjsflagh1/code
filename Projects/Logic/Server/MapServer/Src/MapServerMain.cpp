/******************************************************************************/

#include "stdafx.h"
#include "MapServerMain.h"
#include "ServerManager.h"
#include "SLuaSkillSystem.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "CharacterList.h"
#include "CharacterLvlTemplate.h"
#include "CharacterSkillTempLate.h"
#include "AttributeAppend.h"
#include "AttributeList.h"
#include "AttributePara.h"
#include "LineageTemplate.h"
#include "BattleConfig.h"
#include "SWorldManager.h"
#include "InstanceListCsv.h"
#include "InstanceTiroListCsv.h"
#include "InstancePvEListCsv.h"
#include "InstanceAtkListCsv.h"
#include "ItemShopTemplate.h"
#include "ItemTemplate.h"
#include "ItemEquipTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemOtherTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemRandomTemplate.h"
#include "ItemClanListCsv.h"
#include "ItemExpListCsv.h"
#include "SkillInfoList.h"
#include "SingleTargetSkillTemplate.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "LongRangeAuxiliarySkillTemplate.h"
#include "MGameTimeSystem.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "GoUpAndDownSkillTemplate.h"
#include "CalendarInfo.h"
#include "PrintDialog.h"
#include "PointTemplate.h"
#include "CDTemplate.h"
#include "BattleScoresParamListCsv.h"
#include "BattleScoresRankListCsv.h"
#include "BattleFieldNoticeListCsv.h"
#include "ThreadTaskManager.h"
#include "PrintWindowsCfg.h"
#include "BaseAIGroupTemplate.h"
#include "FightAiGroupTemplate.h"
#include "AttributeInit.h"
#include "StatusCharacterList.h"
#include "StatusList.h"
#include "ClanJudgeTemplate.h"
#include "CharacterJudgeTemplate.h"
#include "SPlayerManager.h"
#include "SWorldObjectFactoryManager.h"
#include "SHeartbeatManager.h"

/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    MapServerMain::MapServerMain()
    {
		mLuaMgr = MG_NEW LuaManager;

		//如果需要用第一帧，可以将其放在初始化之后。
		mCurrUpdateTicks = GetTickCount() * 0.001;
		mLastUpdateTicks = mCurrUpdateTicks;
		mUpdateDelta = 0.0;
    }

    //-----------------------------------------------------------------------------
    MapServerMain::~MapServerMain()
    {
		MG_SAFE_DELETE(mLuaMgr);
    }

    //-----------------------------------------------------------------------------
    Bool MapServerMain::initialize(ServerLauncherInterface* launcher)
    {
		//FUNDETECTION(__MG_FUNC__);

        //-------------------------------------------------------------------------------

		mServerLauncher = launcher;
		DYNAMIC_ASSERT(mServerLauncher);
		if ( launcher == NULL )
			return false;

        //-------------------------------------------------------------------------------

		Str16 str16KeyName = launcher->getConfigKeyName();
		str16KeyName = L"..\\Log\\" + str16KeyName;
		Str8 str8KeyName;
		MGStrOp::toString(str16KeyName.c_str(),str8KeyName);

		LogSystem::getInstance().setSysLogPath(str8KeyName.c_str());
		LogSystem::getInstance().setGameLogicLogPath(str8KeyName.c_str());
		LogSystem::getInstance().setPartName("MapServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);

        //-------------------------------------------------------------------------------

		if(mLuaMgr->initialize() == false)
		{
			return false;
		}

        //-------------------------------------------------------------------------------

		if (loadFile() == false)
			return false;

        //-------------------------------------------------------------------------------

        if (SWorldObjectFactoryManager::getInstance().initialize() == false)
            return false;

		if (SWorldManager::getInstance().initialize(launcher) == false)
			return false;

		if (MGameTimeSystem::getInstance().initialize() == false)
			return false;

        if (SPlayerManager::getInstance().initialize(launcher) == false)
            return false;

        //-------------------------------------------------------------------------------

		PrintDialog::getInstance().createMainDialog();

        //-------------------------------------------------------------------------------

		ThreadTaskManager::getInstance().initialize();

        SHeartbeatManager::getInstance().initialize();

        //-------------------------------------------------------------------------------

        return true;
    }
    
    //-----------------------------------------------------------------------------
    void MapServerMain::update()
    {
		//FUNDETECTION(__MG_FUNC__);
		// 开始更新
		//第一帧的时间可能会长一些。
		//因为第一帧包括初始化的时间。
		mCurrUpdateTicks = GetTickCount() * 0.001;
		mUpdateDelta = mCurrUpdateTicks - mLastUpdateTicks;
		mLastUpdateTicks = mCurrUpdateTicks;

        SWorldManager::getInstance().update(mUpdateDelta);
        SPlayerManager::getInstance().update(mUpdateDelta);
		MGameTimeSystem::getInstance().update();
        SWorldObjectFactoryManager::getInstance().update(mUpdateDelta);
    }
    
    //-----------------------------------------------------------------------------
    Bool MapServerMain::unInitialize()
    {
		//FUNDETECTION(__MG_FUNC__);
        //SWorldManager::getInstance().unInitialize();
		mLuaMgr->unInitialize();

        SHeartbeatManager::getInstance().unInitialize();
        ThreadTaskManager::getInstance().unInitialize();
        MGameTimeSystem::getInstance().unInitialize();
        SWorldManager::getInstance().unInitialize();
        SPlayerManager::getInstance().unInitialize();
        SWorldObjectFactoryManager::getInstance().unInitialize();

        return true;
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onClientConnected(I32 id,NetAddress*address, INetConnect* connect)
    {
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onClientDisconnect(I32 id, INetConnect* connect)
    {
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect)
    {
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
    {
        ServerManager::getInstance().onConnected( id, type, serverId,address);
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onServerDisconnect(I32 id,NetAddress*address)
    {
        ServerManager::getInstance().onDisconnect( id );
    }

    //-----------------------------------------------------------------------------
    void MapServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
    {
        ServerManager::getInstance().processPacket( id,  packet );
    }

    //-----------------------------------------------------------------------------
    Bool MapServerMain::loadFile()
    {
		//FUNDETECTION(__MG_FUNC__);

		if ( CharacterArmyList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterArmyList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CharacterBuildList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterBuildList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CharacterGenrealList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterGeneralList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CharacterNpcList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterNpcList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CharacterObjectList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterObjectList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CharacterMonsterList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterMonsterList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        if ( CharacterTemplate::getInstance().loadFile(L"Config\\Game\\Character\\CharacterList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        if ( CharacterLvlTemplate::getInstance().load(L"Config\\Game\\Setting\\Level.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        if ( ItemShopTemplate::getInstance().load(L"Config\\Game\\Item\\ItemShop.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemClanListCsv::getInstance().load(L"Config\\Game\\Item\\ItemClanUseList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        if ( ItemEquipTemplate::getInstance().load(L"Config\\Game\\Item\\ItemEquipList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemExpListCsv::getInstance().load(L"Config\\Game\\Item\\ItemExpList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemMoneyTemplate::getInstance().load(L"Config\\Game\\Item\\ItemMoneyList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemOtherTemplate::getInstance().load(L"Config\\Game\\Item\\ItemOtherList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        if ( ItemUseTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGeneralUseList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
      
        if ( ItemTemplate::getInstance().load(L"Config\\Game\\Item\\ItemList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        if ( ItemGroupTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGroup.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        if ( ItemRandomTemplate::getInstance().load(L"Config\\Game\\Item\\ItemRandom.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        /*if ( CharacterGenrealTemplate::getInstance().load(L"MapData\\CharacterGenrealTemplate.csv") == false )
        return false;*/

        if ( CharacterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\CharacterTempLateSkill.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( AttributeList::getInstance().load(L"Config\\Game\\Setting\\Ability.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( AttributeInit::getInstance().load(L"Config\\Game\\Setting\\AbilityInit.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		} 
		if ( AttributeAppend::getInstance().load(L"Config\\Game\\Setting\\AbilityAppend.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		} 
        if ( AttributePara::getInstance().load(L"Config\\Game\\Setting\\FormulaParameter.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
       
		if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType002List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (ShortRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType003List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType004List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (SingleTargetSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType005List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( SingleEmitterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType006List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( SelfAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType007List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( TargetPosAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType008List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ParabolaAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType014List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( GoUpAndDownSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType013List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( LongRangeAuxiliarySkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType009List.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if (SkillInfoList::getInstance().load(L"Config\\Game\\Skill\\SkillList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if ( CalendarInfos::getInstance().load(L"Config\\Game\\Text\\Calendar.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		
		
		//战斗相关配置
		if ( BattleConfig::getInstance().loadFile(getSettingFilePath() + L"BattleConfig.ini") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//打印相关配置
		if ( PrintWindowsCfg::getInstance().loadFile(getSettingFilePath() + L"PrintWindowsCfg.ini") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if (PointTemplate::getInstance().load(L"Config\\Game\\ArtRes\\ArtPointRes.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if (CDTemplate::getInstance().load(L"Config\\Game\\Setting\\Timepiece.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//
		if (BattleScoresParamListCsv::getInstance().load(L"Config\\Game\\Setting\\BattleScoresParamList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (BattleScoresRankListCsv::getInstance().load(L"Config\\Game\\Fight\\BattleScoresRankList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (BattleFieldNoticeListCsv::getInstance().load(L"Config\\Game\\Fight\\BattleFieldNoticeList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( BaseAITemplate::getInstance().load(L"Config\\Game\\Fight\\AIBase.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( BaseAIGroupTemplate::getInstance().load(L"Config\\Game\\Fight\\AIBaseGroup.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( FightAITemplate::getInstance().load(L"Config\\Game\\Fight\\AIFight.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( FightAIGroupTemplate::getInstance().load(L"Config\\Game\\Fight\\AIFightGroup.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( StatusCharacterList::getInstance().load(L"Config\\Game\\Status\\StatusCharacterList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( StatusList::getInstance().load(L"Config\\Game\\Status\\StatusList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        
		if (ClanJudgeTemplate::getInstance().load(L"Config\\Game\\Clan\\ClanJudge.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (CharacterJudgeTemplate::getInstance().load(L"Config\\Game\\Character\\CharacterJudge.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

        return true;
    }

	//-----------------------------------------------------------------------------
	void MapServerMain::freeEvent(INetEvent* netEvent)
	{
		if ( mServerLauncher )
		{
			mServerLauncher->freeEvent( netEvent );
		}
	}

    //-----------------------------------------------------------------------------
	MG::Str16 MapServerMain::getSettingFilePath()
	{
      return mServerLauncher->getSettingPathName();
	}
}


