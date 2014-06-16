/******************************************************************************/
#include "stdafx.h"
#include "GameRadar.h"
#include "GameMiniMapManager.h"
#include "IEngineUtil.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CPlayerCharacterEntity.h"
#include "CTroopEntity.h"
#include "CNpcEntity.h"
#include "COrdinaryBuildingEntity.h"
#include "CBuildingEntity.h"
#include "CMonsterEntity.h"
#include "UIMiniMap.h"
/******************************************************************************/

namespace MG
{
	GameRadar::GameRadar( Str name )
		:GameMiniMap(name)
		,mUpdateInterval(2.0f)
		,mTimeElapse(0.0f)
	{
		//玩家自己的图标
		mSelfCharIcon = "self.png";
		mCompanyCharIcon = "friend.png";
		mRivalCharIcon = "enemy.png";
		mCompanyArmyIcon = "friend army.png";
		mRivalArmyIcon = "enemy army.png";
		mCompanyBuildIcon = "";
		mRivalBuildIcon = "enemy house.png";
		mPeaceBuildIcon = "house.png";
		mNpcIcon = "NPC.png";
	}
	//----------------------------------------------------------------------------
	GameRadar::~GameRadar()
	{

	}
	//----------------------------------------------------------------------------
	Bool GameRadar::init()
	{
		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			if ( engUtil->load2DTexture( mSelfCharIcon, "", "" ) &&
				engUtil->load2DTexture( mCompanyCharIcon, "", "" ) &&
				engUtil->load2DTexture( mRivalCharIcon, "", "" ) &&
				engUtil->load2DTexture( mCompanyArmyIcon, "", "" ) &&
				engUtil->load2DTexture( mRivalArmyIcon, "", "" ) &&
				engUtil->load2DTexture( mRivalBuildIcon, "", "" ) &&
				engUtil->load2DTexture( mPeaceBuildIcon, "", "" ) &&
				engUtil->load2DTexture( mNpcIcon, "", "" ) )
			{
				mInitialized = true;
			}

		}
		return mInitialized;
	}
	//----------------------------------------------------------------------------
	void GameRadar::unInit()
	{
		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			engUtil->unload2DTexture( mWorldMapName, mWorldMapGroup );

			engUtil->unload2DTexture( mSelfCharIcon, "" );
			engUtil->unload2DTexture( mCompanyCharIcon, "" );
			engUtil->unload2DTexture( mRivalCharIcon, "" );
			engUtil->unload2DTexture( mCompanyArmyIcon, "" );
			engUtil->unload2DTexture( mRivalArmyIcon, "" );
			engUtil->unload2DTexture( mNpcIcon, "" );
			engUtil->unload2DTexture( mRivalBuildIcon, "" );
			engUtil->unload2DTexture( mPeaceBuildIcon, "" );
		}
	}
	//----------------------------------------------------------------------------
	Bool GameRadar::loadMap(Str name, Str path, Vec2 visibleWorldSize, Vec2 worldCenter)
	{
		if ( mWorldMapName == name && 
			mWorldMapGroup == path )
		{
			return true;
		}

		mWorldMapName = name;
		mWorldMapGroup = path;
		mVisibleWorldSize = visibleWorldSize;
		mVisibleWorldCenter = worldCenter;
		mMapLoaded = false;

		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			if ( engUtil->load2DTexture( mWorldMapName, mWorldMapGroup, mWorldMapGroup ) )
			{
				if ( engUtil->isTextureExist( mapName, mapGroup ) )
				{
					engUtil->unload2DTexture( mapName, mapGroup );
				}

				mMiniMapSize = engUtil->getTextureSize( mWorldMapName, mWorldMapGroup );

				if ( engUtil->create2DTexture( mapName, mapGroup, mMiniMapSize.x, mMiniMapSize.y ) )
				{
					mMapLoaded = true;
				}
			}
		}

		if ( mMapLoaded )
		{
			if ( mListener )
				mListener->onMiniMapLoaded(this);

			//先画一下背景，将UI填满
			drawBackGround();
		}

		return mMapLoaded;
	}
	//----------------------------------------------------------------------------
	void GameRadar::unloadMap()
	{
		mWorldMapName.clear();
		mWorldMapGroup.clear();
		mMapLoaded = false;

		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			engUtil->unload2DTexture( mWorldMapName, mWorldMapGroup );
			engUtil->unload2DTexture( mapName, mapGroup );
		}

		if ( mListener )
			mListener->onMiniMapUnLoad(this);
	}
	//----------------------------------------------------------------------------
	void GameRadar::update(Flt delta)
	{
		if ( !mMapLoaded )
			return;

		Bool updateDirty = ( mTimeElapse > mUpdateInterval ) ? true: false;

		if ( !updateDirty )
			mTimeElapse += delta;
		else
			mTimeElapse = 0.0f;

		if ( updateDirty )
		{
			drawBackGround();
			drawAllUnit();
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::setContainerWidget( IImage* image )
	{
		if ( image && isInitialized() && isMapLoaded() )
		{
			image->setRenderTexture( mapName, mapGroup );
			image->setUVCoord(0,0,1.0,1.0);

			mContainerSize.x = (I32)image->getWidget()->getSize().x;
			mContainerSize.y = (I32)image->getWidget()->getSize().y;
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::releaseContainerWidget( IImage* image )
	{
		if ( image && isInitialized() )
		{
			image->setRenderTexture( "", "" );

			mContainerSize.x = 0;
			mContainerSize.x = 0;
		}
	}
	//----------------------------------------------------------------------------
	VecI2 GameRadar::convertContainerPositionToImagePosition(VecI2 containerPos)
	{
		//获得相对控件左上角的位移
		Vec2 imagePos;

		imagePos.x = ((Flt)containerPos.x / (Flt)mContainerSize.x) * (Flt)mMiniMapSize.x;
		imagePos.y = ((Flt)containerPos.y / (Flt)mContainerSize.y) * (Flt)mMiniMapSize.y;

		return VecI2((Int)imagePos.x, (Int)imagePos.y);
	}
	//----------------------------------------------------------------------------
	Vec2 GameRadar::convertImagePositionToWorldPosition( VecI2 imagePos )
	{
		//获得相对地图中心点的位移
		Vec2 worldOffset;
		worldOffset.x = ( (Flt)imagePos.x - (Flt)mMiniMapSize.x * 0.5f ) * ( mVisibleWorldSize.x / (Flt)mMiniMapSize.x );
		worldOffset.y = ( (Flt)imagePos.y - (Flt)mMiniMapSize.y * 0.5f ) * ( mVisibleWorldSize.y / (Flt)mMiniMapSize.y );

		//通过这个位移获取具体位置
		Vec2 worldPos = mVisibleWorldCenter+ worldOffset;

		return worldPos;
	}
	//----------------------------------------------------------------------------
	VecI2 GameRadar::convertWorldPositionToImagePosition( Vec3 worldPos )
	{
		//获取绘制图片相对底图中心的位移
		Vec2 imageOffset;
		imageOffset.x = ( worldPos.x - mVisibleWorldCenter.x ) * ((Flt)mMiniMapSize.x / mVisibleWorldSize.x);
		imageOffset.y = ( worldPos.z - mVisibleWorldCenter.y ) * ((Flt)mMiniMapSize.y / mVisibleWorldSize.y);

		//通过这个位移获取具体位置
		Vec2 imagePos = Vec2( (Flt)mMiniMapSize.x * 0.5f, (Flt)mMiniMapSize.y * 0.5f ) + imageOffset;
	
		//修正边界值
		imagePos.x = min( imagePos.x, (Flt)mMiniMapSize.x );
		imagePos.x = max( 0.0f, imagePos.x );

		imagePos.y = min( imagePos.y, (Flt)mMiniMapSize.y );
		imagePos.y = max( 0.0f, imagePos.y );

		return VecI2((I32)imagePos.x, (I32)imagePos.y);
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawBackGround()
	{
		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			VecI2 srcSize = engUtil->getTextureSize( mWorldMapName, mWorldMapGroup );

			engUtil->drawTextureToSurface(mWorldMapName, mWorldMapGroup, VecI2(0,0), srcSize,
				mapName, mapGroup,  VecI2(0,0), mMiniMapSize);
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawAllUnit()
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//获取自身相关信息
		IdType mainId = 0;
		FORCE mainForce = FORCE_INIT;

		if ( CPlayer::getInstance().getActiveClan() )
			mainId = CPlayer::getInstance().getActiveClan()->getMainGenrealID();

		CPlayerCharacterEntity* mainPlayerEntity = CSceneManager::getInstance().getPlayerCharacterEntity( mainId );
		if ( mainPlayerEntity && mainPlayerEntity->getDynamicData() )
		{
			mainForce = mainPlayerEntity->getDynamicData()->force;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( mainForce != FORCE_INIT )
		{
			drawBattleUnit(mainId, mainForce);
		}
		else
		{
			drawPeaceUnit(mainId);
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//最后绘制自身
		if ( mainPlayerEntity )
		{
			drawUnit( mainPlayerEntity->getPos(), mSelfCharIcon, "" );
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawPeaceUnit(IdType mainId)
	{
		//其他玩家
		CSceneManager::OrdinaryBuildingEntityListIt ordinaryBuildingEntityIt =  CSceneManager::getInstance().mOrdinaryBuildingEntityList.begin();
		while ( ordinaryBuildingEntityIt != CSceneManager::getInstance().mOrdinaryBuildingEntityList.end() )
		{
			//不是自身
			COrdinaryBuildingEntity* ordinaryBuildingEntity = ordinaryBuildingEntityIt->second;
			if ( ordinaryBuildingEntity && ordinaryBuildingEntity->getEntity() )
			{
				drawUnit( ordinaryBuildingEntity->getPos(), mPeaceBuildIcon, "" );	
			}
			ordinaryBuildingEntityIt++;
		}
		
		//其他玩家
		CSceneManager::PlayerChaEntityListIt playerEntityIter =  CSceneManager::getInstance().mPlayerChaEntityList.begin();
		while ( playerEntityIter != CSceneManager::getInstance().mPlayerChaEntityList.end() )
		{
			//不是自身
			if ( playerEntityIter->first != mainId )
			{
				CPlayerCharacterEntity* playerEntity = playerEntityIter->second;
				if ( playerEntity && playerEntity->getEntity() )
				{
					drawUnit( playerEntity->getPos(), mCompanyCharIcon, "" );	
				}
			}
			playerEntityIter++;
		}

		//绘制NPC
		CSceneManager::NpcEntityListIt npcEntityIter =  CSceneManager::getInstance().mNpcEntityList.begin();
		while ( npcEntityIter != CSceneManager::getInstance().mNpcEntityList.end() )
		{
			CNpcEntity* npcEntity = npcEntityIter->second;
			if ( npcEntity && npcEntity->getEntity() )
			{
				drawUnit( npcEntity->getPos(), mNpcIcon, "" );
			}

			npcEntityIter++;
		}		
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawBattleUnit(IdType mainId, FORCE mainForce)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//将己方军队信息保存于此，延迟进行绘制
		std::vector<CTroopEntity*> companyTroopList;

		//绘制对方军队
		CSceneManager::TroopObjectListIt troopObjectIter =  CSceneManager::getInstance().mTroopEntityList.begin();
		while ( troopObjectIter != CSceneManager::getInstance().mTroopEntityList.end() )
		{
			CTroopEntity* troopObject = troopObjectIter->second;
			if ( troopObject )
			{
				TroopEntityData* dynamicData = troopObject->getDynamicData();
				if ( dynamicData && dynamicData->force > FORCE_INIT && dynamicData->force < FORCE_MAX )
				{	
					if ( dynamicData && dynamicData->force == mainForce )
					{
						//同伴玩家
						companyTroopList.push_back(troopObject);	
					}
					else
					{
						//对方玩家
						drawUnit( troopObject->getTroopCenterPos(), mRivalArmyIcon, "" );
					}
				}
			}

			troopObjectIter++;
		}

		//延迟绘制己方军队
		for ( U32 i = 0; i < companyTroopList.size(); i++ )
		{
			drawUnit( companyTroopList[i]->getTroopCenterPos(), mCompanyArmyIcon, "" );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//将己方攻击建筑信息保存于此，延迟进行绘制
		std::vector<CBuildingEntity*> companyBuildList;

		CSceneManager::BattleBuildingEntityListIt  battleBuildingEntityIter =  CSceneManager::getInstance().mBattleBuildingEntityList.begin();
		while ( battleBuildingEntityIter != CSceneManager::getInstance().mBattleBuildingEntityList.end() )
		{
			CBuildingEntity* buildingEntity = battleBuildingEntityIter->second;
			if ( buildingEntity && buildingEntity->getEntity() && 
				buildingEntity->getBuildingType() == CHAR_BUILD_TYPE_FIGHT ||
				buildingEntity->getBuildingType() == CHAR_BUILD_TYPE_BARRACKS ||
				buildingEntity->getBuildingType() == CHAR_BUILD_TYPE_HEADQUARTERS )
			{
				BuildingEntityData* dynamicData = buildingEntity->getDynamicData();
				if ( dynamicData && dynamicData->force > FORCE_INIT && dynamicData->force < FORCE_MAX )
				{
					if ( dynamicData->force == mainForce )
					{
						//己方建筑
						companyBuildList.push_back(buildingEntity);		
					}
					else
					{
						//对方建筑
						drawUnit( buildingEntity->getPos(), mRivalBuildIcon, "" );
					}
				}
			}

			battleBuildingEntityIter++;
		}

		//延迟绘制己方建筑
		for ( U32 i = 0; i < companyBuildList.size(); i++ )
		{
			//drawUnit( companyBuildList[i]->getPos(), mCompanyBuildIcon, "" );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//绘制monster
		CSceneManager::MonsterEntityListIt monsterEntityIt =  CSceneManager::getInstance().mMonsterEntityList.begin();
		while ( monsterEntityIt != CSceneManager::getInstance().mMonsterEntityList.end() )
		{
			CMonsterEntity* monsterEntity = monsterEntityIt->second;
			if ( monsterEntity && monsterEntity->getEntity() )
			{
				drawUnit( monsterEntity->getPos(), mRivalArmyIcon, "" );
			}

			monsterEntity++;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//将己方玩家信息保存于此，延迟进行绘制
		std::vector<CPlayerCharacterEntity*> companyCharList;

		//绘制对方角色
		CSceneManager::PlayerChaEntityListIt playerEntityIter =  CSceneManager::getInstance().mPlayerChaEntityList.begin();
		while ( playerEntityIter != CSceneManager::getInstance().mPlayerChaEntityList.end() )
		{
			if ( playerEntityIter->first != mainId )
			{
				CPlayerCharacterEntity* playerEntity = playerEntityIter->second;
				if ( playerEntity && playerEntity->getEntity() )
				{
					PlayerCharacterEntityData* dynamicData = playerEntity->getDynamicData();

					if ( dynamicData && dynamicData->force > FORCE_INIT && dynamicData->force < FORCE_MAX )
					{
						if ( dynamicData && dynamicData->force == mainForce )
						{
							//同伴玩家
							companyCharList.push_back(playerEntity);		
						}
						else
						{
							//对方玩家
							drawUnit( playerEntity->getPos(), mRivalCharIcon, "" );
						}
					}		
				}
			}

			playerEntityIter++;
		}

		//延迟绘制己方角色
		for ( U32 i = 0; i < companyCharList.size(); i++ )
		{
			drawUnit( companyCharList[i]->getPos(), mCompanyCharIcon, "" );
		}

	
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//绘制NPC
		CSceneManager::NpcEntityListIt npcEntityIter =  CSceneManager::getInstance().mNpcEntityList.begin();
		while ( npcEntityIter != CSceneManager::getInstance().mNpcEntityList.end() )
		{
			CNpcEntity* npcEntity = npcEntityIter->second;
			if ( npcEntity && npcEntity->getEntity() )
			{
				drawUnit( npcEntity->getPos(), mNpcIcon, "" );
			}

			npcEntityIter++;
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawUnit(Vec3 pos, const Str& iconName, const Str& iconGroup)
	{
		IEngineUtil* engUtil = ClientMain::getInstance().getEngine()->engineUtil();
		if ( engUtil )
		{
			//转换坐标
			VecI2 imagePos = convertWorldPositionToImagePosition(pos);

			//获取绘制图标单元的尺寸
			VecI2 unitImageSize = engUtil->getTextureSize( iconName, iconGroup );
			if ( unitImageSize.x == 0 || 
				unitImageSize.y == 0 )
				return;

			//绘制的图片是否缩放
			VecI2 unitScaledImageSize = unitImageSize;
			unitScaledImageSize.x *= 1;
			unitScaledImageSize.y *= 1;

			//中央对齐
			imagePos.x -= ( unitScaledImageSize.x >> 1);
			imagePos.y -= ( unitScaledImageSize.y >> 1);

			//修正边界值
			if ( imagePos.x > mMiniMapSize.x - unitScaledImageSize.x )
				imagePos.x = mMiniMapSize.x - unitScaledImageSize.x;

			if ( imagePos.y > mMiniMapSize.y - unitScaledImageSize.y )
				imagePos.y = mMiniMapSize.y - unitScaledImageSize.y;

			if ( imagePos.x < 0 )
				imagePos.x = 0;

			if ( imagePos.y < 0 )
				imagePos.y = 0;			

			engUtil->drawTextureToSurface( iconName, iconGroup,
				VecI2(0,0), unitImageSize, mapName, mapGroup, imagePos, unitScaledImageSize );
		}
		
	}

	//----------------------------------------------------------------------------

}