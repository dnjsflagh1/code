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
		//����Լ���ͼ��
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

			//�Ȼ�һ�±�������UI����
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
		//�����Կؼ����Ͻǵ�λ��
		Vec2 imagePos;

		imagePos.x = ((Flt)containerPos.x / (Flt)mContainerSize.x) * (Flt)mMiniMapSize.x;
		imagePos.y = ((Flt)containerPos.y / (Flt)mContainerSize.y) * (Flt)mMiniMapSize.y;

		return VecI2((Int)imagePos.x, (Int)imagePos.y);
	}
	//----------------------------------------------------------------------------
	Vec2 GameRadar::convertImagePositionToWorldPosition( VecI2 imagePos )
	{
		//�����Ե�ͼ���ĵ��λ��
		Vec2 worldOffset;
		worldOffset.x = ( (Flt)imagePos.x - (Flt)mMiniMapSize.x * 0.5f ) * ( mVisibleWorldSize.x / (Flt)mMiniMapSize.x );
		worldOffset.y = ( (Flt)imagePos.y - (Flt)mMiniMapSize.y * 0.5f ) * ( mVisibleWorldSize.y / (Flt)mMiniMapSize.y );

		//ͨ�����λ�ƻ�ȡ����λ��
		Vec2 worldPos = mVisibleWorldCenter+ worldOffset;

		return worldPos;
	}
	//----------------------------------------------------------------------------
	VecI2 GameRadar::convertWorldPositionToImagePosition( Vec3 worldPos )
	{
		//��ȡ����ͼƬ��Ե�ͼ���ĵ�λ��
		Vec2 imageOffset;
		imageOffset.x = ( worldPos.x - mVisibleWorldCenter.x ) * ((Flt)mMiniMapSize.x / mVisibleWorldSize.x);
		imageOffset.y = ( worldPos.z - mVisibleWorldCenter.y ) * ((Flt)mMiniMapSize.y / mVisibleWorldSize.y);

		//ͨ�����λ�ƻ�ȡ����λ��
		Vec2 imagePos = Vec2( (Flt)mMiniMapSize.x * 0.5f, (Flt)mMiniMapSize.y * 0.5f ) + imageOffset;
	
		//�����߽�ֵ
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

		//��ȡ���������Ϣ
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

		//����������
		if ( mainPlayerEntity )
		{
			drawUnit( mainPlayerEntity->getPos(), mSelfCharIcon, "" );
		}
	}
	//----------------------------------------------------------------------------
	void GameRadar::drawPeaceUnit(IdType mainId)
	{
		//�������
		CSceneManager::OrdinaryBuildingEntityListIt ordinaryBuildingEntityIt =  CSceneManager::getInstance().mOrdinaryBuildingEntityList.begin();
		while ( ordinaryBuildingEntityIt != CSceneManager::getInstance().mOrdinaryBuildingEntityList.end() )
		{
			//��������
			COrdinaryBuildingEntity* ordinaryBuildingEntity = ordinaryBuildingEntityIt->second;
			if ( ordinaryBuildingEntity && ordinaryBuildingEntity->getEntity() )
			{
				drawUnit( ordinaryBuildingEntity->getPos(), mPeaceBuildIcon, "" );	
			}
			ordinaryBuildingEntityIt++;
		}
		
		//�������
		CSceneManager::PlayerChaEntityListIt playerEntityIter =  CSceneManager::getInstance().mPlayerChaEntityList.begin();
		while ( playerEntityIter != CSceneManager::getInstance().mPlayerChaEntityList.end() )
		{
			//��������
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

		//����NPC
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
		
		//������������Ϣ�����ڴˣ��ӳٽ��л���
		std::vector<CTroopEntity*> companyTroopList;

		//���ƶԷ�����
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
						//ͬ�����
						companyTroopList.push_back(troopObject);	
					}
					else
					{
						//�Է����
						drawUnit( troopObject->getTroopCenterPos(), mRivalArmyIcon, "" );
					}
				}
			}

			troopObjectIter++;
		}

		//�ӳٻ��Ƽ�������
		for ( U32 i = 0; i < companyTroopList.size(); i++ )
		{
			drawUnit( companyTroopList[i]->getTroopCenterPos(), mCompanyArmyIcon, "" );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//����������������Ϣ�����ڴˣ��ӳٽ��л���
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
						//��������
						companyBuildList.push_back(buildingEntity);		
					}
					else
					{
						//�Է�����
						drawUnit( buildingEntity->getPos(), mRivalBuildIcon, "" );
					}
				}
			}

			battleBuildingEntityIter++;
		}

		//�ӳٻ��Ƽ�������
		for ( U32 i = 0; i < companyBuildList.size(); i++ )
		{
			//drawUnit( companyBuildList[i]->getPos(), mCompanyBuildIcon, "" );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//����monster
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

		//�����������Ϣ�����ڴˣ��ӳٽ��л���
		std::vector<CPlayerCharacterEntity*> companyCharList;

		//���ƶԷ���ɫ
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
							//ͬ�����
							companyCharList.push_back(playerEntity);		
						}
						else
						{
							//�Է����
							drawUnit( playerEntity->getPos(), mRivalCharIcon, "" );
						}
					}		
				}
			}

			playerEntityIter++;
		}

		//�ӳٻ��Ƽ�����ɫ
		for ( U32 i = 0; i < companyCharList.size(); i++ )
		{
			drawUnit( companyCharList[i]->getPos(), mCompanyCharIcon, "" );
		}

	
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//����NPC
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
			//ת������
			VecI2 imagePos = convertWorldPositionToImagePosition(pos);

			//��ȡ����ͼ�굥Ԫ�ĳߴ�
			VecI2 unitImageSize = engUtil->getTextureSize( iconName, iconGroup );
			if ( unitImageSize.x == 0 || 
				unitImageSize.y == 0 )
				return;

			//���Ƶ�ͼƬ�Ƿ�����
			VecI2 unitScaledImageSize = unitImageSize;
			unitScaledImageSize.x *= 1;
			unitScaledImageSize.y *= 1;

			//�������
			imagePos.x -= ( unitScaledImageSize.x >> 1);
			imagePos.y -= ( unitScaledImageSize.y >> 1);

			//�����߽�ֵ
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