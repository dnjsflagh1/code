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

        //��Ϸ�ļ�����
        if ( loadGameFile(packManager) == false )
        {
            MG::MsgBox::show("������Ϸ�ļ�ʧ��","Error");
            return false;
        }

        //��Ϸ�ű�����
        if ( loadGameScript() == false )
        {
            MG::MsgBox::show("���ؽű��ļ�ʧ��","Error");
            return false;
        }

        //������Ϸ����
        //if ( CWorldManager_OldVersion::getInstance().initialize() == false )
        //{
        //	MG::MsgBox::show("��ʼ����Ϸ����ʧ��","Error");
        //	return false;
        //}

        if (CRegionManager::getInstance().initialize() == false)
        {
            MG::MsgBox::show("��ʼ����Ϸ����ʧ��","Error");
            return false;
        }

        //����Ԥ����Ϸ����
        //if (GameSoundManager::getInstance().initialize()==false)
        //{
        //    MG::MsgBox::show("������Ϸ����ʧ��","Error");
        //    return false;
        //}

        if (MessageManager::getInstance().initialize() == false)
        {
            MG::MsgBox::show("������Ϣ������ʧ��","Error");
            return false;
        }

        //���Դ��롣
        if ( TestManager::getInstance().init() == false )
        {
            MG::MsgBox::show("���Դ����ʼ��ʧ��","Error");
            return false;
        }

        if ( CGameTimeSystem::getInstance().initialize() == false )
        {
            MG::MsgBox::show("ʱ��ϵͳ��ʼ��ʧ��","Error");
            return false;
        }

        //��ʼ��С��ͼ
        if ( GameMiniMapManager::getInstance().initilize()  )
        {
            GameMiniMap* miniMap = GameMiniMapManager::getInstance().createOrReteriveMiniMap( "Radar", GameMiniMapManager::MINIMAP_RADAR ); 

            if ( !miniMap )
            {
                MG::MsgBox::show("��ʼ���״�ʧ��","Error");
                return false;
            }
        }
        else
        {
            MG::MsgBox::show("��ʼ��С��ͼϵͳʧ��","Error");
            return false;
        }

        //@ȫ����ȫ�������ڴ���GUI����ϵͳ�����ã�
        //mEngineMain->display()->setFullScreen(true);

        //��Ϸ�������
        if ( UIManager::getInstance().loadLayout() == false )
        {
            MG::MsgBox::show("����UIʧ��","Error");
            return false;
        }

        ClientMain::getInstance().getGui()->resizeWindow();

        //�ѳ�ʼ��������ö���ϵͳ
        GameSettingManager::getInstance().resetInitConfig();
        //����ʱ����
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
        //ж�س���
        CSceneManager::getInstance().destroyRegionScene();

        return true;
    }

    //-----------------------------------------------------------------------
    Bool GameMain::update( Dbl delta )
    {
        // ����AI������
        CAIManager::getInstance().update((Flt)delta);

        // ����������
        for(UInt i=0; i<mOpCtrls.size(); i++)
        {
            mOpCtrls[i]->update((Flt)delta);
        }

        // ���³�������
        CSceneManager::getInstance().update((Flt)delta);

        // ���½������
        UIManager::getInstance().update((Flt)delta);
        
        // ������Ϸʱ��ϵͳ
        CGameTimeSystem::getInstance().update();

        // ��ϷĻ������
        mScreenLinedStateManager.update((Flt)delta);

        //----------------------------------------------

#ifdef _DEBUG
        // ���²��Թ���
        if ( TestManager::getInstance().update((Flt)delta) == false )
        {
            MG::MsgBox::show("���Թ���������","Error");
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

        //�Ͽ���Ϸ����
        ClientNetApplyManager::getInstance().disconnectServers();

        //�ر�������Ϸ����
        UIManager::getInstance().closeAllLayout();

        //��ԭ���벢���µ���
        LoginManager::getInstance().restore();

        CPlayer::getInstance().restore();

        CItemManager::getInstance().clear();

		CClanQuestManager::getInstance().clear();
        

        UIManager::getInstance().restore();

        MessageManager::getInstance().clear();
        
		//���������Ϣ
		CClanQuestManager::getInstance().clear();

        //TODO:
        //��������ģ�黹ԭ����     

        //ж�س������
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
            MG::MsgBox::show("����SelectServerConfig.iniʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (DialogInfos::getInstance().load(L"Config\\Game\\Text\\Dialog.csv", packManager) == false)
        {
            MG::MsgBox::show("����Dialogue.csvʧ��","Error");
            return false;
        }

        if ( CGameMessageConfig::getInstance().loadFile(L"Config\\Game\\Text\\GameMessageConfig.ini", packManager) == false )
        {
            MG::MsgBox::show("����GameMessageConfig.iniʧ��","Error");
            return false;
        }

        if ( CalendarInfos::getInstance().load(L"Config\\Game\\Text\\Calendar.csv", packManager) == false )
        {
            MG::MsgBox::show("����Calendar.csvʧ��","Error");
            return false;
        }

        if (BanKeyword<BanKeywordName>::getInstance().load(L"Config\\Game\\Text\\BanKeywordName.csv", packManager) == false )
        {
            MG::MsgBox::show("����BanKeywordName.csvʧ��","Error");
            return false;
        }

        if (BanKeyword<BanKeywordEnter>::getInstance().load(L"Config\\Game\\Text\\BanKeywordEnter.csv", packManager) == false )
        {
            MG::MsgBox::show("����BanKeywordEnter.csvʧ��","Error");
            return false;
        }

        if (BanKeyword<BanKeywordShow>::getInstance().load(L"Config\\Game\\Text\\BanKeywordShow.csv", packManager) == false )
        {
            MG::MsgBox::show("����BanKeywordShow.csvʧ��","Error");
            return false;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (ChannelInfos::getInstance().loadFile(L"Config\\Game\\Setting\\ChatChannelList.csv", packManager)==false)
        {
            MG::MsgBox::show("����ChatChannel.csvʧ��","Error");
            return false;
        }

        if ( CharacterLvlTemplate::getInstance().load(L"Config\\Game\\Setting\\Level.csv", packManager) == false )
        {
            MG::MsgBox::show("����Level.csvʧ��","Error");
            return false;
        }

        if ( AttributeList::getInstance().load(L"Config\\Game\\Setting\\Ability.csv", packManager) == false )
        {
            MG::MsgBox::show("����Ability.csvʧ��","Error");
            return false;
        }

		if ( AttributeInit::getInstance().load(L"Config\\Game\\Setting\\AbilityInit.csv", packManager) == false )
		{
			MG::MsgBox::show("����AbilityInit.csvʧ��","Error");
			return false;
		}

		if ( AttributeAppend::getInstance().load(L"Config\\Game\\Setting\\AbilityAppend.csv", packManager) == false )
		{
			MG::MsgBox::show("����AbilityAppend.csvʧ��","Error");
			return false;
		}

        if ( AttributePara::getInstance().load(L"Config\\Game\\Setting\\FormulaParameter.csv", packManager) == false )
        {
            MG::MsgBox::show("����FormulaParameter.csvʧ��","Error");
            return false;
        }

        if ( CDTemplate::getInstance().load(L"Config\\Game\\Setting\\Timepiece.csv", packManager) == false )
        {
            MG::MsgBox::show("����Timepiece.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( CharacterResourceConfig::getInstance().load(L"Config\\Game\\Character\\CharacterCreate.csv", packManager) == false)
        {
            MG::MsgBox::show("����CharacterCreate.csvʧ��","Error");
            return false;
        }
        if ( CharacterArmyList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterArmyList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterArmyList.csvʧ��","Error");
            return false;
        }
        if ( CharacterBuildList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterBuildList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterBuildList.csvʧ��","Error");
            return false;
        }
        if ( CharacterGenrealList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterGeneralList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterGeneralList.csvʧ��","Error");
            return false;
        }
        if ( CharacterNpcList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterNpcList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterNpcList.csvʧ��","Error");
            return false;
        }
        if ( CharacterObjectList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterObjectList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterObjectList.csvʧ��","Error");
            return false;
        }
        if ( CharacterMonsterList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterMonsterList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterMonsterList.csvʧ��","Error");
            return false;
        }
        if (DialogueVassal::getInstance().load(L"Config\\Game\\Character\\DialogueVassal.csv", packManager) == false)
        {
            MG::MsgBox::show("����DialogueVassal.csvʧ��","Error");
            return false;
        }

        if ( CharacterTemplate::getInstance().loadFile(L"Config\\Game\\Character\\CharacterList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterList.csvʧ��","Error");
            return false;
        }

        if (NpcFunctionInfos::getInstance().load(L"Config\\Game\\Character\\DialogueFunctionList.csv", packManager) == false)
        {
            MG::MsgBox::show("����DialogueFunctionList.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ArtIconResCsv::getInstance().load(L"Config\\Game\\ArtRes\\IconRes.csv", packManager) == false )
        {
            MG::MsgBox::show("����ArtIconRes.csvʧ��","Error");
            return false;
        }
		
		if ( ColorResConfig::getInstance().load(L"Config\\Game\\ArtRes\\UIColorList.csv", packManager) == false )
		{
			MG::MsgBox::show("����UIColorList.csvʧ��","Error");
			return false;
		}

		if (CharacterRandNameCsv::getInstance().load(L"Config\\Game\\Text\\CharacterRandName.csv", packManager) == false )
		{
			MG::MsgBox::show("����CharacterRandName.csvʧ��","Error");
			return false;
		}

        //if ( AudioResourceConfig::getInstance().load(L"Config\\Game\\ArtRes\\AudioRes.csv", packManager) == false )
        //{
        //    MG::MsgBox::show("����AudioResource.csvʧ��","Error");
        //    return false;
        //}

        if ( VideoResourceConfig::getInstance().load(L"Config\\Game\\ArtRes\\VideoRes.csv", packManager) == false )
        {
            MG::MsgBox::show("����VideoResource.csvʧ��","Error");
            return false;
        }

        if ( GameCameraConfig::getInstance().load(L"Config\\Game\\ArtRes\\CameraSetList.csv", packManager) == false )
        {
            MG::MsgBox::show("����CameraSetList.csvʧ��","Error");
            return false;
        }

        if ( GameRadarConfig::getInstance().load(L"Config\\Game\\ArtRes\\RadarSetList.csv", packManager) == false )
        {
            MG::MsgBox::show("����RadarSetList.csvʧ��","Error");
            return false;
        }

        if ( ArtDecalResTemplate::getInstance().load(L"Config\\Game\\ArtRes\\ArtDecalRes.csv", packManager) == false )
        {
            MG::MsgBox::show("����ArtDecalRes.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ItemShopTemplate::getInstance().load(L"Config\\Game\\Item\\ItemShop.csv", packManager) == false )
        {
            MG::MsgBox::show("����ItemShop.csvʧ��","Error");
            DYNAMIC_ASSERT(0);
            return false;
        }

		if ( ItemClanListCsv::getInstance().load(L"Config\\Game\\Item\\ItemClanUseList.csv", packManager) == false )
		{
			MG::MsgBox::show("����ItemClanListCsv.csvʧ��","Error");
            DYNAMIC_ASSERT(0);
			return false;
		}

		if ( ItemEquipTemplate::getInstance().load(L"Config\\Game\\Item\\ItemEquipList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemEquipTemplate.csvʧ��","Error");
			return false;
		}

		if ( ItemExpListCsv::getInstance().load(L"Config\\Game\\Item\\ItemExpList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemExpListCsv.csvʧ��","Error");
			return false;
		}

		if ( ItemMoneyTemplate::getInstance().load(L"Config\\Game\\Item\\ItemMoneyList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemMoneyTemplate.csvʧ��","Error");
			return false;
		}

		if ( ItemOtherTemplate::getInstance().load(L"Config\\Game\\Item\\ItemOtherList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemOtherTemplate.csvʧ��","Error");
			return false;
		}

		if ( ItemUseTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGeneralUseList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemUseTemplate.csvʧ��","Error");
			return false;
		}

		if ( ItemTemplate::getInstance().load(L"Config\\Game\\Item\\ItemList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			MG::MsgBox::show("����ItemTemplate.csvʧ��","Error");
			return false;
		}

        if ( ItemGroupTemplate::getInstance().load(L"Config\\Game\\Item\\ItemGroup.csv", packManager) == false )
        {
            MG::MsgBox::show("����ItemGroup.csvʧ��","Error");
            return false;
        }

        if ( ItemRandomTemplate::getInstance().load(L"Config\\Game\\Item\\ItemRandom.csv", packManager) == false )
        {
            MG::MsgBox::show("����ItemRandom.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ItemSiteTemplate::getInstance().load(L"Config\\Game\\Clan\\ItemSite.csv", packManager) == false )
        {
            MG::MsgBox::show("����ItemSite.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //����
        //if ( LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType004List.csv") == false )
        //	return false;
        //if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType002List.csv") == false )
        //	return false;

        if ( CharacterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\CharacterTempLateSkill.csv", packManager) == false )
        {
            MG::MsgBox::show("����CharacterTempLateSkill.csvʧ��","Error");
            return false;
        }

        if ( ShortRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType003List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType003List.csvʧ��","Error");
            return false;
        }
        if ( LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType004List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType004List.csvʧ��","Error");
            return false;
        }
        if ( SingleTargetSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType005List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType005List.csvʧ��","Error");
            return false;
        }
        if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType002List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType002List.csvʧ��","Error");
            return false;
        }
        if ( SingleEmitterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType006List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType006List.csvʧ��","Error");
            return false;
        }
        if ( SelfAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType007List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType007List.csvʧ��","Error");
            return false;
        }
        if ( TargetPosAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType008List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType008List.csvʧ��","Error");
            return false;
        }
        if ( ParabolaAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType014List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType014List.csvʧ��","Error");
            return false;
        }
        if ( GoUpAndDownSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType013List.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillType013List.csvʧ��","Error");
            return false;
        }
		if ( LongRangeAuxiliarySkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType009List.csv", packManager) == false )
		{
			MG::MsgBox::show("����SkillType009List.csvʧ��","Error");
			return false;
		}
        if ( SkillInfoList::getInstance().load(L"Config\\Game\\Skill\\SkillList.csv", packManager) == false )
        {
            MG::MsgBox::show("����SkillList.csvʧ��","Error");
            return false;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (QuestTextInfos::getInstance().load(L"Config\\Game\\Quest\\QuestText.csv", packManager) == false)
        {
            MG::MsgBox::show("����QuestText.csvʧ��","Error");
            return false;
        }

        if (QuestValueChangeInfos::getInstance().load(L"Config\\Game\\Quest\\QuestValueChange.csv", packManager) == false)
        {
            MG::MsgBox::show("����QuestValueChange.csvʧ��","Error");
            return false;
        }

        if (QuestNormalInfos::getInstance().load(L"Config\\Game\\Quest\\QuestNormalList.csv", packManager) == false)
        {
            MG::MsgBox::show("����QuestNormalList.csvʧ��","Error");
            return false;
        }

        if (ClanQuestInfos::getInstance().load(L"Config\\Game\\Quest\\QuestList.csv", packManager) == false)
        {
            MG::MsgBox::show("����QuestList.csvʧ��","Error");
            return false;
        }

        if (ClanQuestInfos::getInstance().setQuestInfoData() == false)
        {
            MG::MsgBox::show("setQuestInfoDataʧ��","Error");
            return false;
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (BigMapResCsv::getInstance().load(L"Config\\Game\\World\\PlaceIndex.csv", packManager) == false)
        {
            MG::MsgBox::show("����PlaceIndex.csvʧ��","Error");
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

        // ���ؼ��ܽű��ļ�
        if ( CLuaSkillSystem::getInstance().initialize( ClientMain::getInstance().getLuaManager(), "Config\\Script\\Skill\\Init.lua") == false )
        {
            MG::MsgBox::show("����Skill Init.luaʧ��","Error");
            return false;
        }

        // ���ؼ��ܽű��ļ�
        //if ( LuaBuffSystem::getInstance().initialize( ClientMain::getInstance().getLuaManager(), "Config\\Game\\Buffer\\Init.lua") == false )
        //return false;

        return true;
    }
}


