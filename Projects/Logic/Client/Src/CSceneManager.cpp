/******************************************************************************/
#include "stdafx.h"
#include "CSceneManager.h"
#include "ClientMain.h"
#include "GameMain.h"
#include "SLGCameraOpCtrl.h"
#include "CSkillEffectSystem.h"
#include "CNpcEntity.h"
#include "CBuildingEntity.h"
#include "HeadDamageManage.h"
#include "UIChatSendMsg.h"
#include "UIChatCommonShow.h"
#include "UISkillOperate.h"
#include "UIFamilyInfo.h"
#include "UIGameCalendar.h"
#include "UILoadingProgress.h"

#include "UIMainFunction.h"
#include "UIMiniMap.h"
#include "UIBroadCast.h"

#include "UIManage.h"
#include "CharacterList.h"
#include "GameCameraConfig.h"
#include "CPlayer.h"
#include "GameSoundManager.h"
#include "CRegionManager.h"
#include "BuildingData.h"
#include "PlayerCharacterData.h"
#include "CPlayerCharacterEntity.h"
#include "CThirdPartyCharacterEntity.h"
#include "COrdinaryBuildingEntity.h"
#include "CTroopEntity.h"
#include "IBlockObjectSceneManager.h"
#include "IBlockManager.h"
#include "IPathFindingManager.h"
#include "GameFileDefine.h"
#include "COrdinaryBuildingEntity.h"
#include "OrdinaryBuildingData.h"
#include "CTroopSoldierEntity.h"
#include "RegionObjectData.h"
#include "CAITroopObjectSendSkillPacket.h"
#include "UIJumpOutRegion.h"
#include "IDynamicBlockObject.h"
#include "CMonsterEntity.h"
#include "MonsterData.h"
#include "ICollisionObject.h"
#include "GameSettingManager.h"
#include "GameMiniMapManager.h"
#include "GameRadarConfig.h"
#include "CItemEntity.h"
#include "ItemData.h"
#include "ItemTemplate.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
#include "CAISoldierInTroopMove.h"
#include "UIInteractiveControl.h"
#include "UISLGUP.h"
#include "UISLGLeaveBattle.h"
#include "UISLGTimeLeft.h"
//
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	CSceneManager::CSceneManager()
        :mIsLoadScene(false)
        ,mIsLoadingScene(false)
        ,mMapType(MT_Null)
        ,mCurrRegion(NULL)
		,mIsSupportDynamicPathFind(true)
        ,mLoadSceneEndDirty(false)
		,mSkillEffectSystem(MG_NEW CSkillEffectSystem)
		,mIsStartCampaign(false)
	{
		mAttackForceColorList[0] = Color(222.0/255,198.0/255,61.0/255,255.0/255);
		mAttackForceColorList[1] = Color(246.0/255,136.0/255,25.0/255,255.0/255);
		mAttackForceColorList[2] = Color(247.0/255,62.0/255,5.0/255,255.0/255);
		mAttackForceColorList[3] = Color(208.0/255,11.0/255,2.0/255,255.0/255);
		mAttackForceColorList[4] = Color(137.0/255,19.0/255,122.0/255,255.0/255);
							  
		mDefenseForceColorList[0] = Color(124.0/255,167.0/255,52.0/255,255.0/255);
		mDefenseForceColorList[1] = Color(16.0/255,100.0/255,50.0/255,255.0/255);
		mDefenseForceColorList[2] = Color(42.0/255,134.0/255,159.0/255,255.0/255);
		mDefenseForceColorList[3] = Color(5.0/255,61.0/255,170.0/255,255.0/255);
		mDefenseForceColorList[4] = Color(19.0/255,19.0/255,99.0/255,255.0/255);
	}
    
	//-----------------------------------------------------------------------
	CSceneManager::~CSceneManager()
	{
		destroyRegionScene();
		MG_SAFE_DELETE(mSkillEffectSystem);
	}


    //-----------------------------------------------------------------------
    void CSceneManager::update( Flt delta )
    {
		if(!mCurrRegion)
		{
			return;
		}

		if(/*mCurrRegion->getStartCampaignTime() > 0 && */
			mIsStartCampaign == false && 
			GetCurrentTime() >= mCurrRegion->getStartCampaignTime())
		{
			mIsStartCampaign = true;
			if (mCurrRegion->getStartCampaignTime() > 0)
			{
				//系统-战场开战前10秒倒计时 结束 系统-战场战斗开始.
				mCurrRegion->setStartCampaignTime(0);
				UICampaignFight::getInstance().closeGui();
				UICampaignWar::getInstance().closeGui();
				UISLGUp::getInstance().openGui();
				UISLGTimeLeft::getInstance().openGui();
				UISLGLeaveBattle::getInstance().openGui();
			}
		}
        //FUNDETECTION(__MG_FUNC__);
		///////////////////////////////////////////////////////

        mSkillEffectSystem->update( delta );

        updatePlayerCharacterEntitys( delta );
        updateThirdPartyCharacterEntitys( delta );

		updateMonsterEntitys( delta );

        updateNpcEntitys(delta);
        
        updateOrdinaryBuildingEntitys( delta );
        updateBuildingEntitys( delta );

        updateTroopEntity( delta );

		updateItemEntitys( delta );

        updateLoadScene();
		UIInteractiveControl::getInstance().update(delta);

		///////////////////////////////////////////////////////
    }


    //-----------------------------------------------------------------------
    IScene* CSceneManager::getEngineScene()
    {
        IScene* mainScene = ClientMain::getInstance().getScene();
        return mainScene;
    }


    //-----------------------------------------------------------------------
    CSkillEffectSystem* CSceneManager::getSkillEffectSystem()
    {
        return mSkillEffectSystem;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //-----------------------------------------------------------------------
    void CSceneManager::updateLoadScene()
    {
        if ( mLoadSceneEndDirty )
        {
            onLoadSceneEnd();
            mLoadSceneEndDirty = false;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::setLoadSceneEndDirty()
    {
        mLoadSceneEndDirty = true;
    }

	//-----------------------------------------------------------------------
	Bool CSceneManager::isLoadingScene()
	{
		return mIsLoadingScene;
	}
    
    //-----------------------------------------------------------------------
    void CSceneManager::onLoadSceneStart()
    {
        DYNAMIC_ASSERT(NULL != mCurrRegion);

        mIsLoadingScene = true;

        // 触发事件
        GameMain::getInstance().onStartLoadScene( mRegionId, mRegionObjType );

        // 保存地图类型
        mMapType = mCurrRegion->getData()->getMapListCsvInfo()->mapType;

        //打开加载界面
        UIManager::getInstance().closeAllLayout();

        // 隐藏鼠标
        IPointer* pPointer = ClientMain::getInstance().getPointer();
        if ( pPointer )
            pPointer->setVisible( false );

        // 打开loading界面
        UILoadingProgress::getInstance().openGui();

        // 渲染一帧
        ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );

        //加载地图背景音乐
        U32 tempResid = mCurrRegion->getData()->getMapListCsvInfo()->audioResID;
        GameSoundManager::getInstance().play(tempResid);

        // 设置标志位
        mLoadSceneEndDirty = false;
    }

    //-----------------------------------------------------------------------
    void CSceneManager::onLoadSceneEnd()
    {
        DYNAMIC_ASSERT(NULL != mCurrRegion);
 
        ////////////////////////////////////////////////////////////////////

        // 渲染一帧
        ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );

        //关闭加载界面
        UILoadingProgress::getInstance().closeGui();

        // 显示界面
        IPointer* pPointer = ClientMain::getInstance().getPointer();
        if ( pPointer )
            pPointer->setVisible( true );

        ////////////////////////////////////////////////////////////////////

        // 触发事件
        GameMain::getInstance().onEndLoadScene( mRegionId, mRegionObjType );

        ////////////////////////////////////////////////////////////////////

        mLoadSceneEndDirty = false;
        mIsLoadingScene = false;
    }

	//-----------------------------------------------------------------------
	Bool CSceneManager::loadRegionScene(RegionIdType regionId, REGION_OBJ_TYPE regionObjType)
	{
        // 保存编号
        mRegionId = regionId;
        mRegionObjType = regionObjType;

        // 获得区域对象
		mCurrRegion = CRegionManager::getInstance().getRegionObjectById(regionObjType, regionId);

		DYNAMIC_ASSERT_LOG(NULL != mCurrRegion,"mCurrRegion==null");

		// 加载引擎场景文件
		Str filePath		= mCurrRegion->getFilePath();
		Str fileName		= mCurrRegion->getFileName();
		Str baseFilePath	= mCurrRegion->getBaseFilePath();

		DYNAMIC_ASSERT_LOG(false == filePath.empty() && false == fileName.empty() && false == baseFilePath.empty(),"false == filePath.empty() && false == fileName.empty() && false == baseFilePath.empty()");
		filePath = filePath + "\\" + fileName;
		if(loadRegionScene(baseFilePath, filePath)==false)
		{
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------
	Bool CSceneManager::loadRegionScene(const Str& baseFilePath, const Str& filepath)
	{
        ////////////////////////////////////////////////////////////////////

        if ( GameSettingManager::getInstance().isDebugShowBlock() )
        {
            ClientMain::getInstance().getEngine()->display()->setTerrainRegionDisplayEnabled(true);
            ClientMain::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setBlockRegionVisible(true);
        }

        ////////////////////////////////////////////////////////////////////

		// 触发开始
		onLoadSceneStart();

		//销毁以前场景
		destroyRegionScene();

        // 刷新配置
        GameSettingManager::getInstance().applyDisplayConfig( true );

		////////////////////////////////////////////////////////////////////

        ClientMain::getInstance().getScene()->getXmlSerializer()->clearIgnoreLoadGroup();

		Bool isDebugNoSpeedTree = false;
		Bool isDebugNoSpeedGrass = false;
		Bool isDebugNoStaticentity = false;
        if ( mCurrRegion->getGameType() == GameType_Slg )
        {
            ClientMain::getInstance().getScene()->getXmlSerializer()->addIgnoreLoadGroup( SCENE_OBJECT_GROUP_STR_NPC );
			
			isDebugNoSpeedTree = ClientMain::getInstance().getEngine()->display()->isDebugNoSpeedTree();
			isDebugNoSpeedGrass = ClientMain::getInstance().getEngine()->display()->isDebugNoSpeedGrass();
			isDebugNoStaticentity = ClientMain::getInstance().getEngine()->display()->isDebugNoStaticEntity();

			ClientMain::getInstance().getEngine()->display()->setDebugNoSpeedTree( true );
			ClientMain::getInstance().getEngine()->display()->setDebugNoSpeedGrass( true );
			ClientMain::getInstance().getEngine()->display()->setDebugNoStaticEntity( true );
        }

        ////////////////////////////////////////////////////////////////////


        // 加载美术场景和策划场景
		if(!ClientMain::getInstance().getScene()->getXmlSerializer()->loadAllContent(baseFilePath.c_str(), filepath.c_str(), false))
		{
			return false;
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( mCurrRegion->getGameType() == GameType_Slg )
		{
			ClientMain::getInstance().getEngine()->display()->setDebugNoSpeedTree( isDebugNoSpeedTree );
			ClientMain::getInstance().getEngine()->display()->setDebugNoSpeedGrass( isDebugNoSpeedGrass );
			ClientMain::getInstance().getEngine()->display()->setDebugNoStaticEntity( isDebugNoStaticentity );
		}

        /////////////////////////////////////////////////////////////////////////////////////////////////////

        IScene* mainScene = ClientMain::getInstance().getScene();

		if(!mCurrRegion)
		{
            DYNAMIC_EEXCEPT_LOG("mCurrRegion==null");
			DYNAMIC_ASSERT(0);
			return false;
		}

		ArtMapResCsvInfo* mapResInfo = mCurrRegion->getData()->getArtMapResCsvInfo();
		if(!mapResInfo)
		{
            DYNAMIC_EEXCEPT_LOG("mapResInfo==null");
			DYNAMIC_ASSERT(0);
			return false;
		}

		//设置小地图信息
		U32 radarID = ( mCurrRegion->getGameType() == GameType_Rpg ) ? mapResInfo->rpgRadarId : mapResInfo->slgRadarId;
		const GameRadarConfigInfo* radarInfo = GameRadarConfig::getInstance().getGameRadarConfigInfo(radarID);
		if(!radarInfo)
		{
            DYNAMIC_EEXCEPT_LOG("radarInfo==null");
			DYNAMIC_ASSERT(0);
			return false;
		}

		Vec2 leftBottomPos, rightUpPos;
		leftBottomPos.x = radarInfo->worldCenter.x - radarInfo->worldSize.x / 2;
		leftBottomPos.y = radarInfo->worldCenter.y + radarInfo->worldSize.y / 2;
		rightUpPos.x = radarInfo->worldCenter.x + radarInfo->worldSize.x / 2;
		rightUpPos.y = radarInfo->worldCenter.y - radarInfo->worldSize.y / 2;

        // 加载静态障碍信息
        mainScene->getBlockManager()->loadStaticBlock(leftBottomPos, rightUpPos);

        // 加载动态态障碍信息
        // TODO:
        // 大地图不需要加载

		if(mCurrRegion->getRegionType() != ROT_MAP_DISTRIBUTION)
		{
			//mainScene->getBlockManager()->loadDynamicBlock(leftBottomPos, rightUpPos);
			mainScene->getDynamicBlockObjectSceneManager()->Init(leftBottomPos, rightUpPos, 20);
		}
		
		// 加载寻路信息
		mainScene->getPathFindingManager()->load();

		// 加载Npc逻辑实体
		loadNpcEntity();

		// 加载OrdinaryBuilding逻辑实体
		loadOrdinaryBuildingEntity();

        // 设置标志位
		mIsLoadScene = true;

		return true;
	}

	//-----------------------------------------------------------------------
	void CSceneManager::destroyRegionScene()
	{
        if ( mIsLoadScene )
        {

            //------------------------------------------------------------

            GameMain::getInstance().onUnloadScene( mRegionId, mRegionObjType );

            //------------------------------------------------------------
			//UI交互控制
			UIInteractiveControl::getInstance().clearInteractiveInfo();
			// 释放所有对象

            destroyPlayerCharacterEntitys();
            destroyThirdPartyCharacterEntitys();
			destroyMonsterEntitys();

            destroyNpcEntitys();

            destroyOrdinaryBuildingEntitys();
            destroyBuildingEntitys();

            destroyTroopEntitys();

			destroyItemEntitys();
          
			// 技能特效释放
			mSkillEffectSystem->clear();

            mIsLoadScene = false;
			mAttackForceNum = 0;
			mDefenseForceNum = 0;
			mAttackForceList.clear();
			mDefenseForceList.clear();
			mIsStartCampaign = false;

            ClientMain::getInstance().getScene()->clear();
            ClientMain::getInstance().getEngine()->resourceMgr()->unLoadAllResource();
        }
	}

	//-----------------------------------------------------------------------
	void CSceneManager::setRegionSceneLoaded(Bool isLoadScene)
	{
		mIsLoadScene = true;
	}
    //-----------------------------------------------------------------------
    Bool CSceneManager::isRegionSceneLoaded()
    {
        return mIsLoadScene;
    }

    //-----------------------------------------------------------------------
    MG::IdType CSceneManager::getRegionId()
    {
        return mRegionId;
    }

	//-----------------------------------------------------------------------
	CRegionObject* CSceneManager::getCurrRegion()
	{
		return mCurrRegion;
	}

    //-----------------------------------------------------------------------
    MapType CSceneManager::getMapType()
    {
        return mMapType;
    }

	//-----------------------------------------------------------------------
	void CSceneManager::setDynamicPathFindEnable( Bool enable )
	{
		mIsSupportDynamicPathFind = enable;
	}

	//-----------------------------------------------------------------------
	Bool CSceneManager::getDynamicPathFindEnable()
	{
		return mIsSupportDynamicPathFind;
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //-----------------------------------------------------------------------
    CSceneEntity* CSceneManager::getSceneEntity( IdType id, GAMEOBJ_TYPE type )
    {
		if ( type == GOT_PLAYERCHARACTER )
			return getPlayerCharacterEntity(id);

		if ( type == GOT_THIRDPARTYCHARACTER )
			return getThirdPartyCharacterEntity(id);

		if ( type == GOT_BUILDING )
			return getBuildingEntity(id);

		if ( type == GOT_ORDINARY_BUILDING )
			return getOrdinaryBuildingEntity(id);

		if ( type == GOT_TROOP )
			return getTroopEntity(id);

		if ( type == GOT_MONSTER )
			return getMonsterEntity(id);

		if ( type == GOT_NPC )
			return getNpcEntity(id);

		if ( type == GOT_ITEM )
			return getItemEntity(id);

		return NULL;
    }

    //-----------------------------------------------------------------------
    CCharacterSceneEntity* CSceneManager::getCharacterSceneEntity( GAMEOBJ_TYPE type, IdType id, UInt index )
    {
        if ( type == GOT_PLAYERCHARACTER )
            return getPlayerCharacterEntity(id);

        if ( type == GOT_BUILDING )
            return getBuildingEntity(id);

		if ( type == GOT_SOLDIER )
			return getTroopSoldierEntity(id, index);

		if ( type == GOT_MONSTER )
			return getMonsterEntity(id);

		if ( type == GOT_TROOP )
			return getTroopEntity(id);


        return NULL;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //-----------------------------------------------------------------------
    CPlayerCharacterEntity* CSceneManager::createPlayerCharacterEntity( PlayerCharacterEntityData* data )
    {
        CPlayerCharacterEntity* playerCharacterEntity = getPlayerCharacterEntity( data->mId );
        if ( playerCharacterEntity == NULL )
        {
            const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo( data->mCharacterTemplateID );
            if ( !info )
                return NULL;

            IEntity* entity =  ClientMain::getInstance().getScene()->createEntity( info->getCharacterArtMashId() );
            if ( !entity )
                return NULL;

            entity->getModelObject()->setShadowCastType( SCT_DYNAMIC );
            entity->getModelObject()->setDynamicShadowReceiveEnable( true );

            playerCharacterEntity = MG_NEW CPlayerCharacterEntity( entity );
            mPlayerChaEntityList[data->mId] = playerCharacterEntity;

			// 设置数据
			*(playerCharacterEntity->getDynamicData())  = *data;
			playerCharacterEntity->setPos(data->mPos);

			playerCharacterEntity->initialize();

			if(mCurrRegion && mCurrRegion->getGameType() == GameType_Slg)
			{
				IDynamicBlockObject* dynamicBlockObject = playerCharacterEntity->getEntity()->createOrRetrieveDynamicBlockObject();
				if(dynamicBlockObject)
				{
					dynamicBlockObject->setStructureMode(false);

					if ( playerCharacterEntity->getDynamicData()->force == FORCE_INIT )
					{
						dynamicBlockObject->setEnable(false);
					}else
					{
						dynamicBlockObject->setEnable(true);
					}
				}
			}
        }

        return playerCharacterEntity;
    }


    //-----------------------------------------------------------------------
    void CSceneManager::destroyPlayerCharacterEntity(IdType id)
    {
        PlayerChaEntityListIt it = mPlayerChaEntityList.find(id);
        if(it != mPlayerChaEntityList.end())
        {
            CPlayerCharacterEntity* playCharEntity = it->second;

            MG_SAFE_DELETE( playCharEntity );

            mPlayerChaEntityList.erase(it);
        }
    }

    //-----------------------------------------------------------------------
    CPlayerCharacterEntity* CSceneManager::getPlayerCharacterEntity(IdType id)
    {
        PlayerChaEntityListIt it = mPlayerChaEntityList.find(id);
        if(it != mPlayerChaEntityList.end() && it->second)
        {
            return it->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    CPlayerCharacterEntity* CSceneManager::getPlayerCharacterEntityByName( Char16* name )
    {
        PlayerChaEntityListIt it = mPlayerChaEntityList.begin();
        for(; it != mPlayerChaEntityList.end();it++)
        {
            if (it->second->getName().compare(name) == 0)
            {
                return it->second;
            }
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void CSceneManager::updatePlayerCharacterEntitys( Flt delta )
    {
        //FUNDETECTION(__MG_FUNC__);
        CPlayerCharacterEntity* playerCharEntity = NULL;
        for(PlayerChaEntityListIt it = mPlayerChaEntityList.begin(); it != mPlayerChaEntityList.end();)
        {
            playerCharEntity = it->second;
			if(!playerCharEntity)
			{
				++it;
				continue;
			}

			if(playerCharEntity->getDynamicData()->isDestroy)
			{
				MG_SAFE_DELETE(playerCharEntity);
				it = mPlayerChaEntityList.erase(it);
				continue;
			}

            playerCharEntity->update( delta );
			++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyPlayerCharacterEntitys()
    {
        CPlayerCharacterEntity* playerCharEntity = NULL;
        for(PlayerChaEntityListIt it = mPlayerChaEntityList.begin(); it != mPlayerChaEntityList.end(); ++it)
        {
            playerCharEntity = it->second;
            if(playerCharEntity)
            {
                MG_SAFE_DELETE( playerCharEntity ) ;
            }
        }
        mPlayerChaEntityList.clear();
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//-----------------------------------------------------------------------
	CMonsterEntity* CSceneManager::createMonsterEntity( MonsterEntityData* data )
	{
		CMonsterEntity* monsterEntity = getMonsterEntity( data->mId );
		if ( monsterEntity == NULL )
		{
			const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo( data->mCharacterTemplateID );
			if ( !info )
				return NULL;

			IEntity* entity =  ClientMain::getInstance().getScene()->createEntity( info->getCharacterArtMashId() );
			if ( !entity )
				return NULL;

			entity->getModelObject()->setShadowCastType( SCT_DYNAMIC );
			entity->getModelObject()->setDynamicShadowReceiveEnable( true );

			monsterEntity = MG_NEW CMonsterEntity( entity );
			mMonsterEntityList[data->mId] = monsterEntity;

			// copy data
			*(monsterEntity->getDynamicData())  = *data;
            //从template info中读取额外信息
            monsterEntity->getDynamicData()->surName		 = info->getMonsterSuiName();
            monsterEntity->getDynamicData()->mName			 = info->getMonsterName();
            monsterEntity->getDynamicData()->charArtIcon     = info->getCharacterArtIconId();
            monsterEntity->getDynamicData()->mLevel          = info->getCharacterLevel();
			monsterEntity->initialize();

			monsterEntity->setPos(data->mPos);
			monsterEntity->getEntity()->getSceneNode()->stickTerrain();

            // 怪物一般不设置障碍
       //     if ( monsterEntity->getDynamicData()->force != FORCE_INIT )
       //     {
			    //monsterEntity->getEntity()->createOrRetrieveDynamicBlockObject()->setEnable(true);
       //     }
		}

		return monsterEntity;
	}


	//-----------------------------------------------------------------------
	void CSceneManager::destroyMonsterEntity(IdType id)
	{
		MonsterEntityListIt it = mMonsterEntityList.find(id);
		if(it != mMonsterEntityList.end())
		{
			CMonsterEntity* monsterEntity = it->second;

			MG_SAFE_DELETE( monsterEntity ) ;

			mMonsterEntityList.erase(it);
		}
	}

	//-----------------------------------------------------------------------
	CMonsterEntity* CSceneManager::getMonsterEntity(IdType id)
	{
		MonsterEntityListIt it = mMonsterEntityList.find(id);
		if(it != mMonsterEntityList.end() && it->second)
		{
			return it->second;
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void CSceneManager::updateMonsterEntitys( Flt delta )
	{
		//FUNDETECTION(__MG_FUNC__);
		CMonsterEntity* monsterEntity = NULL;
		for(MonsterEntityListIt it = mMonsterEntityList.begin(); it != mMonsterEntityList.end();)
		{
			monsterEntity = it->second;

			if(monsterEntity->getDynamicData()->isDestroy)
			{
				MG_SAFE_DELETE(monsterEntity);
				it = mMonsterEntityList.erase(it);
				continue;
			}

			monsterEntity->update( delta );
			++it;
		}
	}

	//-----------------------------------------------------------------------
	void CSceneManager::destroyMonsterEntitys()
	{
		CMonsterEntity* monsterEntity = NULL;
		for(MonsterEntityListIt it = mMonsterEntityList.begin(); it != mMonsterEntityList.end(); ++it)
		{
			monsterEntity = it->second;
			if(monsterEntity)
			{
				MG_SAFE_DELETE( monsterEntity ) ;
			}
		}
		mMonsterEntityList.clear();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //-----------------------------------------------------------------------
    CThirdPartyCharacterEntity* CSceneManager::createThirdPartyCharacterEntity(ThirdPartyCharacterEntityData* data)
    {
        CThirdPartyCharacterEntity* thirdPartyCharacterEntity = getThirdPartyCharacterEntity( data->mId );
        if ( thirdPartyCharacterEntity == NULL )
        {
            const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo( data->mCharacterTemplateID );
            if ( !info )
                return NULL;

            IEntity* entity =  ClientMain::getInstance().getScene()->createEntity( info->getCharacterArtMashId() );
            if ( !entity )
                return NULL;

            thirdPartyCharacterEntity = MG_NEW CThirdPartyCharacterEntity( entity );
            mThirdPartyEntityList[data->mId] = thirdPartyCharacterEntity;

            // copy data
            *(thirdPartyCharacterEntity->getDynamicData())  = *data;

			thirdPartyCharacterEntity->initialize();
        }

        return thirdPartyCharacterEntity;

    }

    //-----------------------------------------------------------------------
    CThirdPartyCharacterEntity* CSceneManager::getThirdPartyCharacterEntity( IdType id )
    {
        ThirdPartyChaEntityListIt it = mThirdPartyEntityList.find(id);
        if(it != mThirdPartyEntityList.end() && it->second)
        {
            return it->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyThirdPartyCharacterEntity(IdType id)
    {
        ThirdPartyChaEntityListIt it = mThirdPartyEntityList.find(id);
        if(it != mThirdPartyEntityList.end())
        {
            CThirdPartyCharacterEntity* entity = it->second;

            MG_SAFE_DELETE( entity ) ;

            mThirdPartyEntityList.erase(it);
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::updateThirdPartyCharacterEntitys( Flt delta )
    {
        CThirdPartyCharacterEntity* entity = NULL;
        for(ThirdPartyChaEntityListIt it = mThirdPartyEntityList.begin(); it != mThirdPartyEntityList.end();)
        {
            entity = it->second;

            if(entity->getDynamicData()->isDestroy)
            {
                MG_SAFE_DELETE(entity);
                it = mThirdPartyEntityList.erase(it);
                continue;
            }

            entity->update( delta );
            ++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyThirdPartyCharacterEntitys()
    {
        CThirdPartyCharacterEntity* entity = NULL;
        for(ThirdPartyChaEntityListIt it = mThirdPartyEntityList.begin(); it != mThirdPartyEntityList.end(); ++it)
        {
            MG_SAFE_DELETE(it->second);
        }
        mThirdPartyEntityList.clear();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    //-----------------------------------------------------------------------
    void CSceneManager::loadNpcEntity()
    {
        destroyNpcEntitys();

        IScene* scene = getEngineScene();
        if ( scene )
        {
            UInt count = scene->getEntityCount(SCENE_OBJECT_GROUP_STR_NPC);
            IEntity ** entityBuff = MG_NEW IEntity*[count];
            scene->getEntityList(SCENE_OBJECT_GROUP_STR_NPC,entityBuff,count);

            for (UInt i=0;i<count;i++)
            {
                CNpcEntity* npc = MG_NEW CNpcEntity( entityBuff[i] );
				npc->setID(i);
                npc->initialize();
                mNpcEntityList[i] = npc;
            }

            MG_DELETE_ARRAY( entityBuff );
        }
    }
	CNpcEntity*   CSceneManager::getNpcEntity( IdType id )
	{
		std::map<IdType, CNpcEntity*>::iterator it = mNpcEntityList.find(id);
		if(it != mNpcEntityList.end() && it->second)
		{
			return it->second;
		}
		return NULL;
	}
    //-----------------------------------------------------------------------
    void CSceneManager::updateNpcEntitys( Flt delta )
    {
        //FUNDETECTION(__MG_FUNC__);
        CNpcEntity* entity = NULL;
        for(std::map<IdType, CNpcEntity*>::iterator it = mNpcEntityList.begin(); it != mNpcEntityList.end();)
        {
            entity = it->second;

            if(entity->getDynamicData()->isDestroy)
            {
                entity->unInitialize();
                MG_SAFE_DELETE(entity);
                it = mNpcEntityList.erase(it);
                continue;
            }

            entity->update( delta );
            ++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyNpcEntitys()
    {
        CNpcEntity* entity = NULL;
        for(NpcEntityListIt it = mNpcEntityList.begin(); it != mNpcEntityList.end(); ++it)
        {
            entity = it->second;
            entity->unInitialize();
            MG_SAFE_DELETE( entity )
        }
        mNpcEntityList.clear();
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //-----------------------------------------------------------------------
    void CSceneManager::loadOrdinaryBuildingEntity()
    {
        destroyOrdinaryBuildingEntitys();

        IScene* scene = getEngineScene();
        if ( scene )
        {
            UInt listCount = 0;

            //////////////////////////////////////////////////////////

            // Place
            {
                UInt count  = scene->getEntityCount(SCENE_OBJECT_GROUP_STR_PLACE);
                IEntity ** entityBuff = MG_NEW IEntity*[count];
                scene->getEntityList(SCENE_OBJECT_GROUP_STR_PLACE,entityBuff,count);

                for (UInt i=0;i<count;i++)
                {
                    COrdinaryBuildingEntity* entity = MG_NEW COrdinaryBuildingEntity( entityBuff[i] );
                    mOrdinaryBuildingEntityList[++listCount] = entity;
					entity->setID(listCount);
                    entity->getDynamicData()->buildingType = OBLT_PLACE;
					entity->initialize();
                }

                MG_DELETE_ARRAY( entityBuff );
            }

            //////////////////////////////////////////////////////////

            // Shop
            {
                UInt count  = scene->getEntityCount("Shop");
                IEntity ** entityBuff = MG_NEW IEntity*[count];
                scene->getEntityList("Shop",entityBuff,count);

                for (UInt i=0;i<count;i++)
                {
                    COrdinaryBuildingEntity* entity = MG_NEW COrdinaryBuildingEntity( entityBuff[i] );
                    entity->initialize();
                    mOrdinaryBuildingEntityList[++listCount] = entity;
					entity->setID(listCount);
					entity->getDynamicData()->buildingType = OBLT_SHOP;
                }

                MG_DELETE_ARRAY( entityBuff );
            }

        }
    }
	//-----------------------------------------------------------------------
	COrdinaryBuildingEntity* CSceneManager::getOrdinaryBuildingEntity( IdType id )
	{
		OrdinaryBuildingEntityListIt it = mOrdinaryBuildingEntityList.find(id);
		if(it != mOrdinaryBuildingEntityList.end() && it->second)
		{
			return it->second;
		}
		return NULL;
	}
    //-----------------------------------------------------------------------
    void CSceneManager::updateOrdinaryBuildingEntitys( Flt delta )
    {
        COrdinaryBuildingEntity* entity = NULL;
        for(OrdinaryBuildingEntityListIt it = mOrdinaryBuildingEntityList.begin(); it != mOrdinaryBuildingEntityList.end();)
        {
            entity = it->second;

            if(entity->getDynamicData()->isDestroy)
            {
                entity->unInitialize();
                MG_SAFE_DELETE(entity);
                it = mOrdinaryBuildingEntityList.erase(it);
                continue;
            }

            entity->update( delta );
            ++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyOrdinaryBuildingEntitys()
    {
        COrdinaryBuildingEntity* entity = NULL;
        for(OrdinaryBuildingEntityListIt it = mOrdinaryBuildingEntityList.begin(); it != mOrdinaryBuildingEntityList.end(); ++it)
        {
            entity = it->second;
            if(entity)
            {
                entity->unInitialize();
                MG_SAFE_DELETE( entity ) ;
            }
        }
        mOrdinaryBuildingEntityList.clear();
    }

    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //-----------------------------------------------------------------------
    CBuildingEntity* CSceneManager::createBuildingEntity(BuildingEntityData* data)
    {
        CBuildingEntity* buildingEntity = getBuildingEntity( data->mId );
        if ( buildingEntity == NULL )
        {
            const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo( data->mCharacterTemplateID );
            if ( !info )
                return NULL;

            IEntity* entity =  ClientMain::getInstance().getScene()->createEntity( info->getCharacterArtMashId() );
            if ( !entity )
                return NULL;

            buildingEntity = MG_NEW CBuildingEntity( entity );
            mBattleBuildingEntityList[data->mId] = buildingEntity;

            // copy data
			buildingEntity->setPos(data->mPos);
			buildingEntity->setDir(data->mDir);
			*(buildingEntity->getDynamicData())  = *data;

            buildingEntity->initialize();	

            // 建筑一般都设置障碍
			IDynamicBlockObject* dynamicBlockObject = buildingEntity->getEntity()->createOrRetrieveDynamicBlockObject();

			if(dynamicBlockObject)
			{
				dynamicBlockObject->setStructureMode(true);
                dynamicBlockObject->setStaticBlockEnable(true);
				dynamicBlockObject->setEnable(true);
			}

			ICollisionObject* collisionObject = buildingEntity->getEntity()->createOrRetrieveCollisionObject();
			if(collisionObject)
			{
				collisionObject->setEnable(true);
			}
        }
		else
		{
			//DYNAMIC_ASSERT(0);
		}

        return buildingEntity;
    }

    //-----------------------------------------------------------------------
    CBuildingEntity* CSceneManager::getBuildingEntity( IdType id )
    {
        BattleBuildingEntityListIt it = mBattleBuildingEntityList.find(id);
        if(it != mBattleBuildingEntityList.end() && it->second)
        {
            return it->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyBuildingEntity(IdType buildingId)
    {
        BattleBuildingEntityListIt it = mBattleBuildingEntityList.find(buildingId);
        if(it != mBattleBuildingEntityList.end())
        {
            MG_SAFE_DELETE(it->second);
            mBattleBuildingEntityList.erase(it);
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::updateBuildingEntitys( Flt delta )
    {
        CBuildingEntity* buildingEntity = NULL;
        for(BattleBuildingEntityListIt it = mBattleBuildingEntityList.begin(); it != mBattleBuildingEntityList.end();)
        {
            buildingEntity = it->second;
			if(!buildingEntity)
			{
				++it;
				continue;
			}

			if(buildingEntity->getDynamicData()->isDestroy)
			{
				MG_SAFE_DELETE(buildingEntity);
				it = mBattleBuildingEntityList.erase(it);
				continue;
			}

			buildingEntity->update( delta );
			++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyBuildingEntitys()
    {
        CBuildingEntity* buildingEntity = NULL;
        for(BattleBuildingEntityListIt it = mBattleBuildingEntityList.begin(); it != mBattleBuildingEntityList.end(); ++it)
        {
            MG_SAFE_DELETE(it->second);
        }
        mBattleBuildingEntityList.clear();
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //-----------------------------------------------------------------------
    CTroopEntity* CSceneManager::createTroopEntity( TroopEntityData* data )
    {
        CTroopEntity* troopObject = getTroopEntity( data->mId );
        if ( troopObject == NULL )
        {
            const CharacterTempInfo* info = CharacterTemplate::getInstance().getCharacterTempInfo( data->mCharacterTemplateID );
            if ( !info )
                return NULL;

            IEntityGroup* entityGroup = ClientMain::getInstance().getScene()->createEntityGroup( info->getCharacterArtMashId(), data->mSoldierNum );

            if ( !entityGroup )
                return NULL;

            entityGroup->getModelObject()->setShadowCastType( SCT_DYNAMIC );
            entityGroup->refresh();

            troopObject = MG_NEW CTroopEntity( entityGroup );
            mTroopEntityList[data->mId] = troopObject;

			ILogicBinder* logicBinder = entityGroup->getLogicBinder();
			logicBinder->type = GOT_TROOP;
			logicBinder->manager = troopObject;
			entityGroup->setQueryFlags( GOT_TROOP );

            // copy data
            *(troopObject->getDynamicData())    = *data;

			setTroopSoldierColor( data->force, data->belongPlayerID );

			//CAITroopObjectSendSkillPacket* ai = CAIManager::getInstance().createCAITroopObjectSendSkillPacket();
			//troopObject->getAIStateManager().push(ai);

			TroopSoldierEntityData soldierData;
			soldierData.moveSpeed = data->moveSpeed;
			soldierData.mCharacterTemplateID = data->mCharacterTemplateID;
			soldierData.belongPlayerID = data->belongPlayerID;
			soldierData.force = data->force;
			CTroopSoldierEntity* troopSoldierEntity = NULL;

			for(UInt i = 0; i < data->mSoldierNum/*soldierPosList.size()*/; ++i)
			{
                
				soldierData.mId = i;
				//soldierData.mPos = soldierPosList[i];	
				troopSoldierEntity = troopObject->createSoldierEntitys(i, &soldierData);

                //if(CPlayer::getInstance().getAccountID() == dynamicData->belongPlayerID)
                //{
                    //TROOPTEMPLATE_TYPE troopType = troopSoldierEntity->getCharacterTempInfo()->getArmyArmyType();
                    //if(troopType == TROOPTEMPLATE_TYPE_BROADSWORD || troopType == TROOPTEMPLATE_TYPE_SPEAR || troopType == TROOPTEMPLATE_TYPE_HORSE || troopType == TROOPTEMPLATE_TYPE_BOW)
                    //{
						//troopSoldierEntity->setAIEnable( true );
                    //}

					troopSoldierEntity->setAIEnable( true );
                //}
			}

            //必须在创建Soldier之后调用
            troopObject->initialize();

			//std::map<UInt, CTroopEntity::MoveToPosRow> soldierPosList;
			//troopObject->clacTroopSoldierPos(data->mPos, data->mDir, soldierPosList);

			//UInt index = 0;

			//for(std::map<UInt, CTroopEntity::MoveToPosRow>::iterator it = soldierPosList.begin(); it !=  soldierPosList.end(); ++it)
			//{
			//	for(UInt i = 0; i < it->second.moveToPos.size(); ++i)
			//	{
			//		troopSoldierEntity = troopObject->getSoldierEntitysByIndex(index);
			//		if(!troopSoldierEntity)
			//		{
			//			continue;
			//		}

			//		troopSoldierEntity->getBaseData()->mPos = it->second.moveToPos[i];
			//		troopSoldierEntity->setPos(it->second.moveToPos[i]);
			//		troopSoldierEntity->getEntity()->getSceneNode()->stickTerrain();

			//		index++;
			//	}
			//}

			//std::vector<Vec3> soldierPosList;
			CAISoldierInTroopMove* aISoldierInTroopMove = troopObject->getCAISoldierInTroopMove();
			if(!aISoldierInTroopMove)
			{
				return NULL;
			}

			std::map<UInt, CAISoldierInTroopMove::MoveToPosRow> soldierPosList;
			aISoldierInTroopMove->clacTroopSoldierPos(data->mPos, data->mDir, soldierPosList);

			UInt soldierIndex = 0;
			for(std::map<UInt, CAISoldierInTroopMove::MoveToPosRow>::iterator it = soldierPosList.begin(); it != soldierPosList.end(); ++it)
			{
				for(UInt i = 0; i < it->second.moveToPos.size(); ++i)
				{
					troopSoldierEntity = troopObject->getSoldierEntitysByIndex(soldierIndex);
					if(!troopSoldierEntity)
					{
						soldierIndex++;
						continue;
					}

					troopSoldierEntity->getDynamicData()->mPos = it->second.moveToPos[i];
					troopSoldierEntity->setPos(it->second.moveToPos[i]);
					troopSoldierEntity->getEntity()->getSceneNode()->stickTerrain();

					soldierIndex++;
				}
			}

			//aISoldierInTroopMove->clacTroopSoldierPos(data->mPos, soldierPosList);

			//for(UInt i = 0; i < soldierPosList.size(); ++i)
			//{
			//	troopSoldierEntity = troopObject->getSoldierEntitysByIndex(i);
			//	if(!troopSoldierEntity)
			//	{
			//		continue;
			//	}

			//	troopSoldierEntity->getDynamicData()->mPos = soldierPosList[i];
			//	troopSoldierEntity->setPos(soldierPosList[i]);
			//	troopSoldierEntity->getEntity()->getSceneNode()->stickTerrain();
			//}
			
        }

        return troopObject;
    }

    //-----------------------------------------------------------------------
    CTroopEntity* CSceneManager::getTroopEntity( IdType id )
    {
        TroopObjectListIt it = mTroopEntityList.find(id);
        if(it != mTroopEntityList.end() && it->second)
        {
            return it->second;
        }
        return NULL;
    }

	//-----------------------------------------------------------------------
	CTroopSoldierEntity* CSceneManager::getTroopSoldierEntity( TroopIdType id, UInt index )
	{
		TroopObjectListIt it = mTroopEntityList.find(id);
		if(it != mTroopEntityList.end() && it->second)
		{
			return it->second->getSoldierEntitys(index);
		}

		return NULL;
	}

    //-----------------------------------------------------------------------
    void CSceneManager::destroyTroopEntity(IdType id)
    {
        TroopObjectListIt it = mTroopEntityList.find(id);
        if(it != mTroopEntityList.end())
        {
            MG_SAFE_DELETE(it->second);
            mTroopEntityList.erase(it);
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::updateTroopEntity( Flt delta )
    {
        CTroopEntity* entity = NULL;
        for(TroopObjectListIt it = mTroopEntityList.begin(); it != mTroopEntityList.end(); )
        {
            entity = it->second;
			if(!entity)
			{
				++it;
				continue;
			}

			if(entity->getSoldierEntitysNum() == 0)
			{
				MG_SAFE_DELETE(entity);
				it = mTroopEntityList.erase(it);
				continue;
			}

            entity->update(delta);
			++it;
        }
    }

    //-----------------------------------------------------------------------
    void CSceneManager::destroyTroopEntitys()
    {   
        CTroopEntity* troopObject = NULL;
        for(TroopObjectListIt it = mTroopEntityList.begin(); it != mTroopEntityList.end(); ++it)
        {
			troopObject = it->second;
            MG_SAFE_DELETE( troopObject );
        }
        mTroopEntityList.clear();
    }

	//-----------------------------------------------------------------------
	void CSceneManager::setTroopSoldierColor( FORCE force, IdType playerID )
	{
		if(force == FORCE_ATTACK)
		{
			std::map<IdType, BYTE>::iterator it = mAttackForceList.find(playerID);
			if(it == mAttackForceList.end())
			{
				mAttackForceList[playerID] = mAttackForceNum;
				mAttackForceNum++;
			}
		}
		else if(force == FORCE_DEFENSE)
		{
			std::map<IdType, BYTE>::iterator it = mDefenseForceList.find(playerID);
			if(it == mDefenseForceList.end())
			{
				mDefenseForceList[playerID] = mDefenseForceNum;
				mDefenseForceNum++;
			}
		}
	}

	//-----------------------------------------------------------------------
	Color CSceneManager::getTroopSoldierColor( FORCE force, IdType playerID )
	{
		Color color;
		UInt colorIndex = 0;
		if(force == FORCE_ATTACK)
		{
			std::map<IdType, BYTE>::iterator it = mAttackForceList.find(playerID);
			if(it != mAttackForceList.end())
			{
				colorIndex = mAttackForceList[playerID];
				if(colorIndex < ATTACKFORCEMAXNUM)
				{
					color = mAttackForceColorList[colorIndex];
				}	
			}
		}
		else if(force == FORCE_DEFENSE)
		{
			std::map<IdType, BYTE>::iterator it = mDefenseForceList.find(playerID);
			if(it != mDefenseForceList.end())
			{
				colorIndex = mDefenseForceList[playerID];
				if(colorIndex < DEFENSEFORCEMAXNUM)
				{
					color = mDefenseForceColorList[colorIndex];
				}	
			}
		}

		return color;
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------
	CItemEntity* CSceneManager::createItemEntity( ItemEntityData* data )
	{
		CItemEntity* itemEntity = getItemEntity( data->mId );
		if ( itemEntity == NULL )
		{
			const ItemInfo* info = ItemTemplate::getInstance().getItemInfo( data->mItemTemplateId );
			if ( !info || info->ItemType == ITEM_TYPE_EXP)
				return NULL;


			IEntity* entity =  ClientMain::getInstance().getScene()->createEntity( info->getItemBaseDropMashID() );
			if ( !entity )
				return NULL;

			itemEntity = MG_NEW CItemEntity( entity );
			mItemEntityList[data->mId] = itemEntity;

			// copy data
			*(itemEntity->getDynamicData()) = *data;
			itemEntity->setPos(data->mPos);
			itemEntity->setDir(data->mDir);
			itemEntity->setName(info->getItemBaseItemName().c_str());

			itemEntity->initialize();	
		}
		else
		{
			//DYNAMIC_ASSERT(0);
		}

		return itemEntity;
	}

	//-----------------------------------------------------------------------
	CItemEntity* CSceneManager::getItemEntity( IdType id )
	{
		ItemEntityListIt it = mItemEntityList.find(id);
		if(it != mItemEntityList.end() && it->second)
		{
			return it->second;
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void CSceneManager::destroyItemEntity(IdType buildingId)
	{
		ItemEntityListIt it = mItemEntityList.find(buildingId);
		if(it != mItemEntityList.end())
		{
			it->second->unInitialize();
			MG_SAFE_DELETE(it->second);
			mItemEntityList.erase(it);
		}
	}

	//-----------------------------------------------------------------------
	void CSceneManager::updateItemEntitys( Flt delta )
	{
		CItemEntity* itemEntity = NULL;
		for(ItemEntityListIt it = mItemEntityList.begin(); it != mItemEntityList.end();)
		{
			itemEntity = it->second;
			if(!itemEntity)
			{
				++it;
				continue;
			}

			itemEntity->update( delta );
			++it;
		}
	}

	//-----------------------------------------------------------------------
	void CSceneManager::destroyItemEntitys()
	{
		CItemEntity* itemEntity = NULL;
		for(ItemEntityListIt it = mItemEntityList.begin(); it != mItemEntityList.end(); ++it)
		{
			it->second->unInitialize();
			MG_SAFE_DELETE(it->second);
		}
		mItemEntityList.clear();
	}

	//-----------------------------------------------------------------------
	Bool CSceneManager::getIsStartCampaign()
	{
		return mIsStartCampaign;
	}
	//-----------------------------------------------------------------------
	void CSceneManager::setIsStartCampaign(Bool isStart)
	{
		mIsStartCampaign = isStart;
	}
	//-----------------------------------------------------------------------
	MG::REGION_OBJ_TYPE CSceneManager::getRegionObjType()
	{
		return mRegionObjType;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
