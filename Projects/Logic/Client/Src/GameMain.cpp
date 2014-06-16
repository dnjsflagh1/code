/******************************************************************************/
#include "stdafx.h"
#include "GameMain.h"
#include "LogSystem.h"
//#include "CWorldManager.h"
#include "ClientMain.h"
#include "UIManage.h"
#include "TestManager.h"
#include "ClientNetApplyManager.h"
#include "CSelectServerConfig.h"
#include "CGameMessageConfig.h"
#include "LoginManager.h"
#include "CSceneManager.h"
#include "LuaManager.h"
#include "CLuaSkillSystem.h"
#include "CharacterResourceConfig.h"
#include "CharacterList.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "CharacterLvlTemplate.h"
#include "AttributeAppend.h"
#include "AttributePara.h"
#include "AttributeList.h"
#include "CDTemplate.h"
#include "ItemShopTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemRandomTemplate.h"
#include "ArtIconResCsv.h"
#include "NpcFuctionInfo.h"
#include "ItemSiteTemplate.h"
#include "AudioResourceConfig.h"
#include "VideoResourceConfig.h"
#include "GameCameraConfig.h"
#include "CharacterSkillTempLate.h"
#include "GameSoundManager.h"
#include "CItemManager.h"
#include "CClanQuestManager.h"
#include "CPlayer.h"
#include "ChannelInfo.h"
#include "CRegionManager.h"
#include "NetPacketPackManager.h"
#include "Dialog.h"
#include "ItemTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemEquipTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemOtherTemplate.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "LongRangeAuxiliarySkillTemplate.h"
#include "SkillInfoList.h"
#include "SkillLearn.h"
#include "GameSettingManager.h"
#include "IDisplay.h"
#include "QuestList.h"
#include "QuestText.h"
#include "QuestNormalList.h"
#include "QuestValueChange.h"
#include "BigMapResCsv.h"
#include "InstanceListCsv.h"
#include "CGameTimeSystem.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "CalendarInfo.h"
#include "BanKeyword.h"
#include "MessageManager.h"
#include "ArtDecalResTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "GoUpAndDownSkillTemplate.h"
#include "GameMiniMapManager.h"
#include "GameRadarConfig.h"
#include "TestUI.h"
#include "MessageManager.h"
#include "DialogueVassal.h"
#include "BaseAITemplate.h"
#include "BaseAIGroupTemplate.h"
#include "FightAITemplate.h"
#include "FightAiGroupTemplate.h"
#include "LogoScreen.h"
#include "LoginScreen.h"
#include "GameScreen.h"
#include "CClanQuestManager.h"
#include "ItemClanListCsv.h"
#include "ItemExpListCsv.h"
#include "CharacterRandNameCsv.h"
#include "AttributeInit.h"
#include "ClanJudgeTemplate.h"
#include "CharacterJudgeTemplate.h"

#include "CharacterVisionEvent.h"
#include "CharacterVisionEventList.h"
#include "AudioResourceConfig.h"
#include "StatusCharacterList.h"
#include "StatusList.h"
#include "UIClanInfo.h"
#include "ColorResConfig.h"
/******************************************************************************/

namespace MG
{
   
    //-----------------------------------------------------------------------
    GameMain::GameMain()
        :mActiveScreen(NULL)
    {
        
    }

    //-----------------------------------------------------------------------
    GameMain::~GameMain()
    {

    }

    //-----------------------------------------------------------------------
    Bool GameMain::initialize(IMGExternalPackManager* packManager)
    {

        //游戏文件加载
        if ( loadGameFile(packManager) == false )
        {
            MG::MsgBox::show("加载游戏文件失败","Error");
            return false;
        }

        //游戏脚本加载
        if ( loadGameScript() == false )
        {
            MG::MsgBox::show("加载脚本文件失败","Error");
            return false;
        }

        //加载游戏世界
        //if ( CWorldManager_OldVersion::getInstance().initialize() == false )
        //{
        //	MG::MsgBox::show("初始化游戏世界失败","Error");
        //	return false;
        //}

        if (CRegionManager::getInstance().initialize() == false)
        {
            MG::MsgBox::show("初始化游戏世界失败","Error");
            return false;
        }

        //加载预载游戏音乐
        //if (GameSoundManager::getInstance().initialize()==false)
        //{
        //    MG::MsgBox::show("加载游戏音乐失败","Error");
        //    return false;
        //}

        if (MessageManager::getInstance().initialize() == false)
        {
            MG::MsgBox::show("加载信息管理器失败","Error");
            return false;
        }

        //测试代码。
        if ( TestManager::getInstance().init() == false )
        {
            MG::MsgBox::show("测试代码初始化失败","Error");
            return false;
        }

        if ( CGameTimeSystem::getInstance().initialize() == false )
        {
            MG::MsgBox::show("时间系统初始化失败","Error");
            return false;
        }

        //初始化小地图
        if ( GameMiniMapManager::getInstance().initilize()  )
        {
            GameMiniMap* miniMap = GameMiniMapManager::getInstance().createOrReteriveMiniMap( "Radar", GameMiniMapManager::MINIMAP_RADAR ); 

            if ( !miniMap )
            {
                MG::MsgBox::show("初始化雷达失败","Error");
                return false;
            }
        }
        else
        {
            MG::MsgBox::show("初始化小地图系统失败","Error");
            return false;
        }

        //@全屏（全屏必须在创建GUI管理系统后设置）
        //mEngineMain->display()->setFullScreen(true);

        //游戏界面加载
        if ( UIManager::getInstance().loadLayout() == false )
        {
            MG::MsgBox::show("加载UI失败","Error");
            return false;
        }

        ClientMain::getInstance().getGui()->resizeWindow();

        //把初始化后的配置读入系统
        GameSettingManager::getInstance().resetInitConfig();
        //运行时配置
        GameSettingManager::getInstance().restoreRuningConfig();

        ::ShowCursor(false); 

		return true;
    }

    //-----------------------------------------------------------------------
    void GameMain::run()
    {
        enterLogoScreen();
    }

    //-----------------------------------------------------------------------
    Bool GameMain::uninitialize()
    {
        //卸载场景
        CSceneManager::getInstance().destroyRegionScene();

        return true;
    }

    //-----------------------------------------------------------------------
    Bool GameMain::update( Dbl delta )
    {
        // 更新AI管理器
        CAIManager::getInstance().update((Flt)delta);

        // 操作控制器
        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->update((Flt)delta);
        }

        // 更新场景管理
        CSceneManager::getInstance().update((Flt)delta);

        // 更新界面管理
        UIManager::getInstance().update((Flt)delta);
        
        // 更新游戏时间系统
        CGameTimeSystem::getInstance().update();

        // 游戏幕管理器
        mScreenLinedStateManager.update((Flt)delta);

        //----------------------------------------------

#ifdef _DEBUG
        // 更新测试管理
        if ( TestManager::getInstance().update((Flt)delta) == false )
        {
            MG::MsgBox::show("测试管理器出错","Error");
            return false;
        }
#endif

        //----------------------------------------------

        return true;
    }

    //-----------------------------------------------------------------------
    void GameMain::stopAndRestore()
    {
        //FUNDETECTION(__MG_FUNC__);

        //断开游戏连接
        ClientNetApplyManager::getInstance().disconnectServers();

        //关闭所有游戏界面
        UIManager::getInstance().closeAllLayout();

        //还原登入并重新登入
        LoginManager::getInstance().restore();

        CPlayer::getInstance().restore();

        CItemManager::getInstance().clear();

		CClanQuestManager::getInstance().clear();
        

        UIManager::getInstance().restore();

        MessageManager::getInstance().clear();
        
		//清空任务信息
		CClanQuestManager::getInstance().clear();

        //TODO:
        //增加其他模块还原方法     

        //卸载场景相关
        CSceneManager::getInstance().destroyRegionScene();
		CSceneManager::getInstance().destroyRegionInfo();
        CSceneManager::getInstance().getEngineScene()->getXmlSerializer()->unLoad();
        CSceneManager::getInstance().getEngineScene()->clear();


        enterLoginScreen();
    }

    //-----------------------------------------------------------------------
    void GameMain::enterLogoScreen()
    {
        mScreenLinedStateManager.clear();
        mActiveScreen = &(LogoScreen::getInstance());
        mScreenLinedStateManager.push( mActiveScreen );
    }

    //-----------------------------------------------------------------------
    void GameMain::enterLoginScreen()
    {
        mScreenLinedStateManager.clear();
        mActiveScreen = &(LoginScreen::getInstance());
        mScreenLinedStateManager.push(mActiveScreen);
    }

    //-----------------------------------------------------------------------
    void GameMain::enterGameScreen()
    {
        mScreenLinedStateManager.clear();
        mActiveScreen = &(GameScreen::getInstance());
        mScreenLinedStateManager.push(mActiveScreen);
    }

    //-----------------------------------------------------------------------
    void GameMain::clearOperatorCtrls()
    {
        mOpCtrls.clear();
    }

    //-----------------------------------------------------------------------
    void GameMain::revertOperatorCtrls()
    {
        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->revert();
        }
    }
   
    //-----------------------------------------------------------------------
    void GameMain::addOperatorCtrls(IOpCtrl* ctrl)
    {
        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            if ( mOpCtrls[i] == ctrl )
                return;
        }
        mOpCtrls.push_back( ctrl );
    }

    //-----------------------------------------------------------------------
    void GameMain::removeOperatorCtrls(IOpCtrl* ctrl)
    {
        std::vector<IOpCtrl*>::iterator iter = mOpCtrls.begin();
        std::vector<IOpCtrl*>::iterator end_iter = mOpCtrls.end();
        for( ; iter != end_iter; iter++ )
        {
            if ( *iter == ctrl )
            {
                mOpCtrls.erase( iter );
                return;
            }
        }
    }

    //-----------------------------------------------------------------------
    void GameMain::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        if ( mActiveScreen )
        {
            mActiveScreen->onStartLoadScene( regionId, regionType );
        }

        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->onStartLoadScene( regionId, regionType );
        }
    }

    //-----------------------------------------------------------------------
    void GameMain::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        if ( mActiveScreen )
        {
            mActiveScreen->onEndLoadScene( regionId, regionType );
        }

        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->onEndLoadScene( regionId, regionType );
        }
    }

    //-----------------------------------------------------------------------
    void GameMain::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        if ( mActiveScreen )
        {
            mActiveScreen->onUnloadScene( regionId, regionType );
        }

        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->onUnloadScene( regionId, regionType );
        }
    }

    //-----------------------------------------------------------------------
    Bool GameMain::loadGameFile(IMGExternalPackManager* packManager)
    {	

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( CSelectServerConfig::getInstance().loadFile(L"Config\\SelectServerConfig.ini", packManager) == false )
        {
            MG::MsgBox::show("加载SelectServerConfig.ini失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (DialogInfos::getInstance().load(L"Config\\Game\\Text\\Dialog.csv", packManager) == false)
        {
            MG::MsgBox::show("加载Dialogue.csv失败","Error");
            return false;
        }

        if ( CGameMessageConfig::getInstance().loadFile(L"Config\\Game\\Text\\GameMessageConfig.ini", packManager) == false )
        {
            MG::MsgBox::show("加载GameMessageConfig.ini失败","Error");
            return false;
        }

        if ( CalendarInfos::getInstance().load(L"Config\\Game\\Text\\Calendar.csv", packManager) == false )
        {
            MG::MsgBox::show("加载Calendar.csv失败","Error");
            return false;
        }

        if (BanKeyword<BanKeywordName>::getInstance().load(L"Config\\Game\\Text\\BanKeywordName.csv", packManager) == false )
        {
            MG::MsgBox::show("加载BanKeywordName.csv失败","Error");
            return false;
        }

        if (BanKeyword<BanKeywordEnter>::getInstance().load(L"Config\\Game\\Text\\BanKeywordEnter.csv", packManager) == false )
        {
            MG::MsgBox::show("加载BanKeywordEnter.csv失败","Error");
            return false;
        }

        if (BanKeyword<BanKeywordShow>::getInstance().load(L"Config\\Game\\Text\\BanKeywordShow.csv", packManager) == false )
        {
            MG::MsgBox::show("加载BanKeywordShow.csv失败","Error");
            return false;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (ChannelInfos::getInstance().loadFile(L"Config\\Game\\Setting\\ChatChannelList.csv", packManager)==false)
        {
            MG::MsgBox::show("加载ChatChannel.csv失败","Error");
            return false;
        }

        if ( CharacterLvlTemplate::getInstance().load(L"Config\\Game\\Setting\\Level.csv", packManager) == false )
        {
            MG::MsgBox::show("加载Level.csv失败","Error");
            return false;
        }

        if ( AttributeList::getInstance().load(L"Config\\Game\\Setting\\Ability.csv", packManager) == false )
        {
            MG::MsgBox::show("加载Ability.csv失败","Error");
            return false;
        }

		if ( AttributeInit::getInstance().load(L"Config\\Game\\Setting\\AbilityInit.csv", packManager) == false )
		{
			MG::MsgBox::show("加载AbilityInit.csv失败","Error");
			return false;
		}

		if ( AttributeAppend::getInstance().load(L"Config\\Game\\Setting\\AbilityAppend.csv", packManager) == false )
		{
			MG::MsgBox::show("加载AbilityAppend.csv失败","Error");
			return false;
		}

        if ( AttributePara::getInstance().load(L"Config\\Game\\Setting\\FormulaParameter.csv", packManager) == false )
        {
            MG::MsgBox::show("加载FormulaParameter.csv失败","Error");
            return false;
        }

        if ( CDTemplate::getInstance().load(L"Config\\Game\\Setting\\Timepiece.csv", packManager) == false )
        {
            MG::MsgBox::show("加载Timepiece.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( CharacterResourceConfig::getInstance().load(L"Config\\Game\\Character\\CharacterCreate.csv", packManager) == false)
        {
            MG::MsgBox::show("加载CharacterCreate.csv失败","Error");
            return false;
        }
        if ( CharacterArmyList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterArmyList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterArmyList.csv失败","Error");
            return false;
        }
        if ( CharacterBuildList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterBuildList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterBuildList.csv失败","Error");
            return false;
        }
        if ( CharacterGenrealList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterGeneralList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterGeneralList.csv失败","Error");
            return false;
        }
        if ( CharacterNpcList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterNpcList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterNpcList.csv失败","Error");
            return false;
        }
        if ( CharacterObjectList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterObjectList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterObjectList.csv失败","Error");
            return false;
        }
        if ( CharacterMonsterList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterMonsterList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterMonsterList.csv失败","Error");
            return false;
        }
        if (DialogueVassal::getInstance().load(L"Config\\Game\\Character\\DialogueVassal.csv", packManager) == false)
        {
            MG::MsgBox::show("加载DialogueVassal.csv失败","Error");
            return false;
        }

        if ( CharacterTemplate::getInstance().loadFile(L"Config\\Game\\Character\\CharacterList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterList.csv失败","Error");
            return false;
        }

        if (NpcFunctionInfos::getInstance().load(L"Config\\Game\\Character\\DialogueFunctionList.csv", packManager) == false)
        {
            MG::MsgBox::show("加载DialogueFunctionList.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ArtIconResCsv::getInstance().load(L"Config\\Game\\ArtRes\\IconRes.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ArtIconRes.csv失败","Error");
            return false;
        }
		
		if ( ColorResConfig::getInstance().load(L"Config\\Game\\ArtRes\\UIColorList.csv", packManager) == false )
		{
			MG::MsgBox::show("加载UIColorList.csv失败","Error");
			return false;
		}

		if (CharacterRandNameCsv::getInstance().load(L"Config\\Game\\Text\\CharacterRandName.csv", packManager) == false )
		{
			MG::MsgBox::show("加载CharacterRandName.csv失败","Error");
			return false;
		}

        //if ( AudioResourceConfig::getInstance().load(L"Config\\Game\\ArtRes\\AudioRes.csv", packManager) == false )
        //{
        //    MG::MsgBox::show("加载AudioResource.csv失败","Error");
        //    return false;
        //}

        if ( VideoResourceConfig::getInstance().load(L"Config\\Game\\ArtRes\\VideoRes.csv", packManager) == false )
        {
            MG::MsgBox::show("加载VideoResource.csv失败","Error");
            return false;
        }

        if ( GameCameraConfig::getInstance().load(L"Config\\Game\\ArtRes\\CameraSetList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CameraSetList.csv失败","Error");
            return false;
        }

        if ( GameRadarConfig::getInstance().load(L"Config\\Game\\ArtRes\\RadarSetList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载RadarSetList.csv失败","Error");
            return false;
        }

        if ( ArtDecalResTemplate::getInstance().load(L"Config\\Game\\ArtRes\\ArtDecalRes.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ArtDecalRes.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ItemShopTemplate::getInstance().load(L"Config\\Game\\Item\\ItemShop.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ItemShop.csv失败","Error");
            DYNAMIC_ASSERT(0);
            return false;
        }

		if ( ItemClanListCsv::getInstance().load(L"Config\\Game\\Item\\ItemClanUseList.csv", packManager) == false )
		{
			MG::MsgBox::show("加载ItemClanListCsv.csv失败","Error");
            DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemEquipTemplate::getInstance().load(L"Config\\Game\\Item\\ItemEquipList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemEquipTemplate.csv失败","Error");
			return false;
		}

		if ( ItemExpListCsv::getInstance().load(L"Config\\Game\\Item\\ItemExpList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemExpListCsv.csv失败","Error");
			return false;
		}

		if ( ItemMoneyTemplate::getInstance().load(L"Config\\Game\\Item\\ItemMoneyList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemMoneyTemplate.csv失败","Error");
			return false;
		}

		if ( ItemOtherTemplate::getInstance().load(L"Config\\Game\\Item\\ItemOtherList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemOtherTemplate.csv失败","Error");
			return false;
		}

		if ( ItemUseTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGeneralUseList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemUseTemplate.csv失败","Error");
			return false;
		}

		if ( ItemTemplate::getInstance().load(L"Config\\Game\\Item\\ItemList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("加载ItemTemplate.csv失败","Error");
			return false;
		}

        if ( ItemGroupTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGroup.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ItemGroup.csv失败","Error");
            return false;
        }

        if ( ItemRandomTemplate::getInstance().load(L"Config\\Game\\Item\\ItemRandom.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ItemRandom.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ItemSiteTemplate::getInstance().load(L"Config\\Game\\Clan\\ItemSite.csv", packManager) == false )
        {
            MG::MsgBox::show("加载ItemSite.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //技能
        //if ( LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType004List.csv") == false )
        //	return false;
        //if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType002List.csv") == false )
        //	return false;

        if ( CharacterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\CharacterTempLateSkill.csv", packManager) == false )
        {
            MG::MsgBox::show("加载CharacterTempLateSkill.csv失败","Error");
            return false;
        }

        if ( ShortRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType003List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType003List.csv失败","Error");
            return false;
        }
        if ( LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType004List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType004List.csv失败","Error");
            return false;
        }
        if ( SingleTargetSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType005List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType005List.csv失败","Error");
            return false;
        }
        if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType002List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType002List.csv失败","Error");
            return false;
        }
        if ( SingleEmitterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType006List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType006List.csv失败","Error");
            return false;
        }
        if ( SelfAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType007List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType007List.csv失败","Error");
            return false;
        }
        if ( TargetPosAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType008List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType008List.csv失败","Error");
            return false;
        }
        if ( ParabolaAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType014List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType014List.csv失败","Error");
            return false;
        }
        if ( GoUpAndDownSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType013List.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillType013List.csv失败","Error");
            return false;
        }
		if ( LongRangeAuxiliarySkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType009List.csv", packManager) == false )
		{
			MG::MsgBox::show("加载SkillType009List.csv失败","Error");
			return false;
		}
        if ( SkillInfoList::getInstance().load(L"Config\\Game\\Skill\\SkillList.csv", packManager) == false )
        {
            MG::MsgBox::show("加载SkillList.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (QuestTextInfos::getInstance().load(L"Config\\Game\\Quest\\QuestText.csv", packManager) == false)
        {
            MG::MsgBox::show("加载QuestText.csv失败","Error");
            return false;
        }

        if (QuestValueChangeInfos::getInstance().load(L"Config\\Game\\Quest\\QuestValueChange.csv", packManager) == false)
        {
            MG::MsgBox::show("加载QuestValueChange.csv失败","Error");
            return false;
        }

        if (QuestNormalInfos::getInstance().load(L"Config\\Game\\Quest\\QuestNormalList.csv", packManager) == false)
        {
            MG::MsgBox::show("加载QuestNormalList.csv失败","Error");
            return false;
        }

        if (ClanQuestInfos::getInstance().load(L"Config\\Game\\Quest\\QuestList.csv", packManager) == false)
        {
            MG::MsgBox::show("加载QuestList.csv失败","Error");
            return false;
        }

        if (ClanQuestInfos::getInstance().setQuestInfoData() == false)
        {
            MG::MsgBox::show("setQuestInfoData失败","Error");
            return false;
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (BigMapResCsv::getInstance().load(L"Config\\Game\\World\\PlaceIndex.csv", packManager) == false)
        {
            MG::MsgBox::show("加载PlaceIndex.csv失败","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( BaseAITemplate::getInstance().load(L"Config\\Game\\Fight\\AIBase.csv", packManager) == false )
        {
            DYNAMIC_ASSERT(0);
            return false;
        }

        if ( BaseAIGroupTemplate::getInstance().load(L"Config\\Game\\Fight\\AIBaseGroup.csv", packManager) == false )
        {
            DYNAMIC_ASSERT(0);
            return false;
        }

        if ( FightAITemplate::getInstance().load(L"Config\\Game\\Fight\\AIFight.csv", packManager) == false )
        {
            DYNAMIC_ASSERT(0);
            return false;
        }

        if ( FightAIGroupTemplate::getInstance().load(L"Config\\Game\\Fight\\AIFightGroup.csv", packManager) == false )
        {
            DYNAMIC_ASSERT(0);
            return false;
        }

		if ( CharacterVisionEvent::getInstance().load(L"Config\\Game\\ArtRes\\CharacterVisionEvent.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( CharacterVisionEventList::getInstance().load(L"Config\\Game\\ArtRes\\CharacterVisionEventList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        
		if(AudioResourceConfig::getInstance().load(L"Config\\Game\\ArtRes\\AudioRes.csv",packManager) == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( StatusCharacterList::getInstance().load(L"Config\\Game\\Status\\StatusCharacterList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		if(StatusList::getInstance().load(L"Config\\Game\\Status\\StatusList.csv",packManager) == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//gamejudge
		if (ClanJudgeTemplate::getInstance().load(L"Config\\Game\\Clan\\ClanJudge.csv",packManager) == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		if (CharacterJudgeTemplate::getInstance().load(L"Config\\Game\\Character\\CharacterJudge.csv",packManager) == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        return true;
    }

    //-----------------------------------------------------------------------
    Bool GameMain::loadGameScript()
    {
        //FUNDETECTION(__MG_FUNC__);

        // 加载技能脚本文件
        if ( CLuaSkillSystem::getInstance().initialize( ClientMain::getInstance().getLuaManager(), "Config\\Script\\Skill\\Init.lua") == false )
        {
            MG::MsgBox::show("加载Skill Init.lua失败","Error");
            return false;
        }

        // 加载技能脚本文件
        //if ( LuaBuffSystem::getInstance().initialize( ClientMain::getInstance().getLuaManager(), "Config\\Game\\Buffer\\Init.lua") == false )
        //return false;

        return true;
    }
}


