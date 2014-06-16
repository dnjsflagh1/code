/******************************************************************************/
#include "stdafx.h"
#include "LoginScreen.h"
#include "ClientMain.h"
#include "GameMain.h"
#include "LoginManager.h"
#include "GameSoundManager.h"
#include "CSceneManager.h"
#include "LoginScreenOpCtrl.h"
#include "IEntity.h"
#include "CClan.h"
#include "CPlayer.h"
#include "CCharacterSceneEntity.h"
#include "CPlayerCharacterEntity.h"
#include "CharacterList.h"
#include "CharacterResourceConfig.h"
#include "CActionManager.h"
#include "HeadDes.h"
#include "UILoadingProgress.h"
#include "UICreateCharacter.h"
#include "UIClanControl.h"
#include "UISelectServer.h"
#include "UIManage.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    Str LoginScreen::STATE_NAME = "LoginScreen";
    //-----------------------------------------------------------------------------
    LoginScreen::LoginScreen()
        :IScreen( STATE_NAME )
		,mSelectedGeneralIndex(-1)
		,mSceneFinishDirty(false)
    {
        setManagedLifeTime( false );

		/////////////////////////////////////////////////////////////////

		mEntityList.push_back("SceneCenter");			//场景中心点

		mEntityList.push_back("Susaku_Entity");			//朱雀
		mEntityList.push_back("Biakko_Entity");			//白虎
		mEntityList.push_back("Kenbu_Entity");			//玄武
		mEntityList.push_back("Seiryu_Entity");			//青龙
		
		mEntityList.push_back("Susaku_Entity_Front");	//朱雀(前景)
		mEntityList.push_back("Biakko_Entity_Front");	//白虎(前景)
		mEntityList.push_back("Kenbu_Entity_Front");	//玄武(前景)
		mEntityList.push_back("Seiryu_Entity_Front");	//青龙(前景)
		
		mEntityList.push_back("Susaku_Entity_Back");	//朱雀(背景)
		mEntityList.push_back("Biakko_Entity_Back");	//白虎(背景)
		mEntityList.push_back("Kenbu_Entity_Back");		//玄武(背景)
		mEntityList.push_back("Seiryu_Entity_Back");	//青龙(背景)
		
		mEntityList.push_back("Sky_001");				//天空盒1
		mEntityList.push_back("Sky_002");				//天空盒2
		mEntityList.push_back("Sky_003");				//天空盒3

		mEntityList.push_back("Camera01");				//摄像机1
		mEntityList.push_back("Camera02");				//摄像机2
		mEntityList.push_back("Camera01.Target");		//摄像机1目标
		mEntityList.push_back("Camera02.Target");		//摄像机2目标

		mEntityList.push_back("Hall01");				//议事厅1
		mEntityList.push_back("Hall02");				//议事厅2

		mEntityList.push_back("CreateCharScene_Seat");					//(创建武将场景)主武将的位置

		mEntityList.push_back("CreateCharScene_Stand00");				//(创建武将场景)站立位置1
		mEntityList.push_back("CreateCharScene_Stand01");				//(创建武将场景)站立位置2
		mEntityList.push_back("CreateCharScene_Stand10");				//(创建武将场景)站立位置3
		mEntityList.push_back("CreateCharScene_Stand11");				//(创建武将场景)站立位置4
		mEntityList.push_back("CreateCharScene_Stand20");				//(创建武将场景)站立位置5
		mEntityList.push_back("CreateCharScene_Stand21");				//(创建武将场景)站立位置6
		mEntityList.push_back("CreateCharScene_Stand30");				//(创建武将场景)站立位置7
		mEntityList.push_back("CreateCharScene_Stand31");				//(创建武将场景)站立位置8

		mEntityList.push_back("CreateCharScene_StandRow0");				//(创建武将场景)第一排
		mEntityList.push_back("CreateCharScene_StandRow1");				//(创建武将场景)第二排
		mEntityList.push_back("CreateCharScene_StandRow2");				//(创建武将场景)第三排	
		mEntityList.push_back("CreateCharScene_StandRow3");				//(创建武将场景)第四排

		mEntityList.push_back("SelectCharScene_Seat");						//(选择武将场景)主武将的位置
		mEntityList.push_back("SelectCharScene_Seat_Left");				//(选择武将场景)左边副将的位置
		mEntityList.push_back("SelectCharScene_Seat_Left");				//(选择武将场景)右边副将的位置

		mEntityList.push_back("SelectCharScene_Stand00");					//站立位置1
		mEntityList.push_back("SelectCharScene_Stand01");					//站立位置2
		mEntityList.push_back("SelectCharScene_Stand10");					//站立位置3
		mEntityList.push_back("SelectCharScene_Stand11");					//站立位置4
		mEntityList.push_back("SelectCharScene_Stand20");					//站立位置5
		mEntityList.push_back("SelectCharScene_Stand21");					//站立位置6
		mEntityList.push_back("SelectCharScene_Stand30");					//站立位置7
		mEntityList.push_back("SelectCharScene_Stand31");					//站立位置8

		/////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------------
    LoginScreen::~LoginScreen()
    {

    }

    //-----------------------------------------------------------------------------
    void LoginScreen::update( Flt delta )
    {
		if ( LoginScreenOpCtrl::getInstance().getCtrlState() == 
			LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR )
		{
			CSceneManager::getInstance().updatePlayerCharacterEntitys(delta);
		}
    }

    //-----------------------------------------------------------------------------
    bool LoginScreen::isFinished()
    {
        if ( getEnterGameDirty() )
        {
            return true;
        }

        return false;
    }

    //-----------------------------------------------------------------------------
    void LoginScreen::onEnter()
    {
		// dirty清除;
		mSceneFinishDirty = false; 
		
        // 设置操作
        GameMain::getInstance().clearOperatorCtrls();
        GameMain::getInstance().addOperatorCtrls( &LoginScreenOpCtrl::getInstance() );

		// 播放音乐
		LoginManager::getInstance().start();
		GameSoundManager::getInstance().play(10001);

		// 设置了资源读取监听器
		ClientMain::getInstance().getScene()->setResourceLoadListener(this);
		GameSettingManager::getInstance().addListener("LoginScreen", this);

		// 加载场景
		loadCreateClanScene();
	}

    //-----------------------------------------------------------------------------
    void LoginScreen::onLeave()
    {
        clearEnterGameDirty();

		GameSettingManager::getInstance().removeListener("LoginScreen");

		LoginScreenOpCtrl::getInstance().setCtrlState( LoginScreenOpCtrl::CTRL_STATE_SEL_NONE );

		CSceneManager::getInstance().destroyPlayerCharacterEntitys();

		ClientMain::getInstance().getScene()->clear();

		GameMain::getInstance().clearOperatorCtrls();

        GameMain::getInstance().enterGameScreen();

		
    }
	//-----------------------------------------------------------------------------
	void LoginScreen::loadScene(CChar* newPath, I32 ctrlType)
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Str currPath = ClientMain::getInstance().getScene()->getXmlSerializer()->getScenePath();

		if ( currPath.compare( newPath ) != 0 )
		{
            ClientMain::getInstance().getEngine()->display()->setDebugNoEntity( false );

			ClientMain::getInstance().getScene()->clear();
			ClientMain::getInstance().getScene()->getXmlSerializer()->loadAllContent(newPath, NULL, false);
            
            if ( GameSettingManager::getInstance().isDebugNoEntity() )
            {
                ClientMain::getInstance().getEngine()->display()->setDebugNoEntity( true );
            }
		}

		setAllEntitysVisible(false);

		////////////////////////////////////////////////////////////////////////////////////////////////////

		LoginScreenOpCtrl::getInstance().setCtrlState(ctrlType);
		LoginScreenOpCtrl::getInstance().revert();

		////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::beginLoadScene(CChar* newPath, I32 ctrlType)
	{
		if ( ctrlType == LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN )
		{
			UISelectServer::getInstance().closeGui();
		}

		if ( ctrlType == LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR ||
			ctrlType == LoginScreenOpCtrl::CTRL_STATE_SEL_CHAR )
		{
			Str currPath = ClientMain::getInstance().getScene()->getXmlSerializer()->getScenePath();

			if ( currPath.compare( newPath ) != 0 )
			{
				// 假设之前并未读入过该场景，所以需要加载其他的资源
				// 于是设定这边的加载进度占总加载进度的50%

				mObjectTotalProgress = 0.5f;
				mCustomObjectProgress = 0.5f;
				mFreshTime = 0.0f;
			}
			else
			{
				// 假设之前已经读入了该场景，除了这边的逻辑，其他不需要加载资源
				// 所以这边的需要的加载进度是100%

				mObjectTotalProgress = 1.0f;
				mCustomObjectProgress = 0.0f;
				mFreshTime = 0.0f;
			}
		}

		IPointer* pPointer = ClientMain::getInstance().getPointer();
		if ( pPointer )
		{
			pPointer->setVisible( false );
		}

		UILoadingProgress::getInstance().openGui();

		CSceneManager::getInstance().setRegionSceneLoaded(false);

		CSceneManager::getInstance().destroyPlayerCharacterEntitys();
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::endLoadScene(CChar* newPath, I32 ctrlType)
	{
		CSceneManager::getInstance().setRegionSceneLoaded(true);

		UILoadingProgress::getInstance().closeGui();

		IPointer* pPointer = ClientMain::getInstance().getPointer();
		if ( pPointer )
		{
			pPointer->setVisible( true );
		}

		if ( ctrlType == LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN )
		{
			UISelectServer::getInstance().openGui();
		}
		else if ( ctrlType == LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR )
		{
			std::map<U32,CharacterResInfo*> tempResInfoList = 
				CharacterResourceConfig::getInstance().getCharacterResourceInfoList();

			U32 playerIndex = 0;
			U32 imageId = 110001;
			Flt imageHeight = 1.0f;

			for ( std::map<U32, CharacterResInfo*>::iterator iter = tempResInfoList.begin(); 
				iter != tempResInfoList.end(); iter++ )
			{
				CPlayerCharacterEntity* playerEntity = 
					CSceneManager::getInstance().getPlayerCharacterEntity((IdType)iter->second->templateid);

				if ( playerEntity )
				{
					playerEntity->getHeadDes()->setFlagImg(imageId + playerIndex / 2);
					playerEntity->getHeadDes()->setHeight(0.8f);
					playerEntity->setHeadDesVisible(true);
				}

				playerIndex++;
			}
		}
	}
	//-----------------------------------------------------------------------------
	Bool LoginScreen::loadCreateClanScene()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////

		beginLoadScene("Media//Scene//03_MapIndoor//Map_1201", LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN);

		////////////////////////////////////////////////////////////////////////////////////////////////////

		loadScene("Media//Scene//03_MapIndoor//Map_1201", 
			LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN );

		////////////////////////////////////////////////////////////////////////////////////////////////////

		initManualRenderState( LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN );
		
		////////////////////////////////////////////////////////////////////////////////////////////////////

		endLoadScene("Media//Scene//03_MapIndoor//Map_1201", LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN);

		////////////////////////////////////////////////////////////////////////////////////////////////////

		return true;

	}

	//-----------------------------------------------------------------------
	void LoginScreen::destroyCreateClanScene()
	{
	}

	//-----------------------------------------------------------------------
	Bool LoginScreen::loadSelectGeneralScene()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////

		beginLoadScene("Media//Scene//03_MapIndoor//Map_1202", LoginScreenOpCtrl::CTRL_STATE_SEL_CHAR);

		////////////////////////////////////////////////////////////////////////////////////////////////////

		loadScene("Media//Scene//03_MapIndoor//Map_1202", 
			LoginScreenOpCtrl::CTRL_STATE_SEL_CHAR );

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 设置各个物件的可见性

		for ( int i = ENTITY_HALL_PART_1; i <= ENTITY_HALL_PART_2; i++ )
		{
			IEntity* entity = ClientMain::getInstance().getScene()->getEntity(mEntityList[i].c_str());
			if ( entity )
				entity->getSceneNode()->setVisible(true);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 光照

		ILight* light = ClientMain::getInstance().getScene()->getLight( "SpotLight" );
		if ( light )
		{
			light->getSceneNode()->setVisible(false);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 初始化玩家角色列表中的所有角色

		CClan* pClan = CPlayer::getInstance().getActiveClan();
		if ( pClan && pClan->getPlayerCharacterList() )
		{
			size_t	index = 0;
			size_t	count = pClan->getPlayerCharacterNum();

			if ( count > ENTITY_SELCHAR_STAND_POINT_8 - ENTITY_SELCHAR_STAND_POINT_1 + 1 )
				count =  ENTITY_SELCHAR_STAND_POINT_8 - ENTITY_SELCHAR_STAND_POINT_1 + 1;
			
			///////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 放置主武将

			Bool			  mainPlayerInited		= false;
			CPlayerCharacter* mainPlayerCharacter	= pClan->getMainGenreal();
			
			for ( std::map<U64, CPlayerCharacter*>::iterator iter = pClan->getPlayerCharacterList()->begin();
				iter != pClan->getPlayerCharacterList()->end(); iter++ )
			{
				// 假设数量超过了能够显示的数量
				if ( index >= count )
					break;

				preloadCustomObject( index, count );

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				// 获取摆放的位置 

				Vec3		slotPos;
				Vec3		slotDir;
				IEntity*	slotEntity = NULL;

				CPlayerCharacter* playerCharacter = iter->second;

				if ( playerCharacter == mainPlayerCharacter )
				{
					mainPlayerInited = true;

					slotEntity = ClientMain::getInstance().getScene()->getEntity(mEntityList[ENTITY_SELCHAR_SEAT_POINT].c_str());
				}
				else
				{
					Int slot = ENTITY_SELCHAR_STAND_POINT_1 + index;
					if ( mainPlayerInited )
						slot--;

					slotEntity = ClientMain::getInstance().getScene()->getEntity(mEntityList[slot].c_str());
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				// 摆放角色拥有的所有武将

				if ( slotEntity )
				{
					slotEntity->getSceneNode()->getPosition(slotPos);
					slotEntity->getSceneNode()->getDirection(slotDir);

					PlayerCharacterData*		pPlayerCharacterData = playerCharacter->getData();
					PlayerCharacterEntityData	dynamicDate;

					dynamicDate.belongPlayerID = CPlayer::getInstance().getAccountID();
					dynamicDate.mCharacterTemplateID = pPlayerCharacterData->mCharacterTemplateID;
					dynamicDate.mName = pPlayerCharacterData->mName;
					dynamicDate.surName = pPlayerCharacterData->charSurName;
					dynamicDate.mId = pPlayerCharacterData->mId;
					dynamicDate.mLevel = pPlayerCharacterData->mLevel;
					dynamicDate.hp = pPlayerCharacterData->mHp;
					dynamicDate.mp = pPlayerCharacterData->mMp;

					CPlayerCharacterEntity* playerEntity = CSceneManager::getInstance().createPlayerCharacterEntity( &dynamicDate );
					if ( playerEntity )
					{
						playerEntity->getEntity()->getAnimationController()->setBlendingEnable(false);
						playerEntity->getEntity()->getAnimationController()->addAnimationLisitener( "LoginScreenOpCtrl", this );

						playerEntity->setPos(slotPos);
						playerEntity->setDir(slotDir);

						playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_MAIN, true);
						playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_DEPUTY, true);
						playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_HORSE, true);

						playerEntity->setHeadDesVisible(false);
						playerEntity->getHeadDes()->setIsTemplateCharacter(true);

						if ( playerCharacter == mainPlayerCharacter )
						{		
							playerEntity->setIdleAnimation( "guard", false );
							playerEntity->setIdleAnimation( "stand", true );
							playerEntity->playAnimation( "emote2", false, true );
						}
						else
						{
							playerEntity->setIdleAnimation( "guard", false );
							playerEntity->setIdleAnimation( "stand", false );
							playerEntity->setIdleAnimation( "emote4", true );
						}
					}
				}
		
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				postloadCustomObject( NULL, index, count );

				index++;

			}
		}
			
		////////////////////////////////////////////////////////////////////////////////////////////////////

		endLoadScene("Media//Scene//03_MapIndoor//Map_1202", LoginScreenOpCtrl::CTRL_STATE_SEL_CHAR );

		////////////////////////////////////////////////////////////////////////////////////////////////////

		return true;
	}
	//-----------------------------------------------------------------------
	void LoginScreen::destroySelectGeneralScene()
	{

	}
	//-----------------------------------------------------------------------------
	Bool LoginScreen::loadCreateGeneralScene()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////

		beginLoadScene("Media//Scene//03_MapIndoor//Map_1202", LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR);

		////////////////////////////////////////////////////////////////////////////////////////////////////

		loadScene("Media//Scene//03_MapIndoor//Map_1202", 
			LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR );

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 设置各个物件的可见性

		for ( int i = ENTITY_HALL_PART_1; i <= ENTITY_HALL_PART_2; i++ )
		{
			IEntity* entity = ClientMain::getInstance().getScene()->getEntity(mEntityList[i].c_str());
			if ( entity )
				entity->getSceneNode()->setVisible(true);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 设置光照

		ILight* light = ClientMain::getInstance().getScene()->getLight( "SpotLight" );

		if ( !light )
			light = ClientMain::getInstance().getScene()->createLight( "SpotLight" );

		if ( light )
		{
			Vec3 lightPos;

			IEntity* entity = getEntity(ENTITY_CRECHAR_STAND_ROW_1);
			if ( entity )
			{
				entity->getSceneNode()->getPosition(lightPos);
			}

			
			light->setLightType(ILight::LT_DIRECTIONAL);
			light->getSceneNode()->setPosition(lightPos + Vec3(0.0f, 2.0f, 0.0f));
			light->getSceneNode()->setDirection(Vec3(0.0f,-1.0f,0.0f));
			light->setDiffuseColour(COLOR_YELLOW);
			light->setAttenuation(5.0, 5.0, 0.0f, 0.0f);
			//light->setAttenuation(3.0, 1.0, 0.0, 0.0 );
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////

		// 创建八名武将
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			std::map<U32,CharacterResInfo*> tempResInfoList = 
				CharacterResourceConfig::getInstance().getCharacterResourceInfoList();
			
			I32 count = tempResInfoList.size();
			if ( count > ENTITY_CRECHAR_STAND_POINT_8 - ENTITY_CRECHAR_STAND_POINT_1 + 1 )
				count = ENTITY_CRECHAR_STAND_POINT_8 - ENTITY_CRECHAR_STAND_POINT_1 + 1;

			I32 index = 0;

			for ( std::map<U32, CharacterResInfo*>::iterator iter = tempResInfoList.begin(); 
				iter != tempResInfoList.end(); iter++ )
			{
				if ( ENTITY_CRECHAR_STAND_POINT_1 + index > ENTITY_CRECHAR_STAND_POINT_8 )
					break;

				preloadCustomObject( index, count );

				const CharacterTempInfo* tempInfo = 
					CharacterTemplate::getInstance().getCharacterTempInfo(iter->second->templateid);

				if ( tempInfo )
				{
					PlayerCharacterEntityData dynamicDate;
					dynamicDate.belongPlayerID = CPlayer::getInstance().getAccountID();
					dynamicDate.mCharacterTemplateID = tempInfo->getCharacterTempId();
					dynamicDate.mId += iter->second->templateid;


					CPlayerCharacterEntity* playerEntity = 
						CSceneManager::getInstance().createPlayerCharacterEntity( &dynamicDate );

					if ( playerEntity )
					{
						IEntity* entity = getEntity( ENTITY_CRECHAR_STAND_POINT_1 + index );
						if ( entity )
						{
							Vec3 entityPos;
							Vec3 entityDir;

							entity->getSceneNode()->getPosition( entityPos );
							entity->getSceneNode()->getDirection( entityDir);

							playerEntity->setPos( entityPos );
							playerEntity->setDir( entityDir );

							playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_MAIN, true);
							playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_DEPUTY, true);
							playerEntity->detachItem(ITEM_EQUIP_SLOT_TYPE_HORSE, true);

							playerEntity->setIdleAnimation( "guard", false );
							playerEntity->setIdleAnimation( "stand", false );
							playerEntity->setIdleAnimation( "emote4", true );

							playerEntity->setHeadDesVisible(false);
							playerEntity->getHeadDes()->setIsTemplateCharacter(true);

							playerEntity->getEntity()->getAnimationController()
								->addAnimationLisitener( "LoginScreenOpCtrl", this );

							mTempCharEntityList[index] = playerEntity;
						}
					}
				}

				postloadCustomObject( NULL, index, count );

				index++;
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		endLoadScene( "Media//Scene//03_MapIndoor//Map_1202", LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR );

		////////////////////////////////////////////////////////////////////////////////////////////////////

		return true;

	}
	//-----------------------------------------------------------------------------
	void LoginScreen::destroyCreateGeneralScene()
	{

	}
    //-----------------------------------------------------------------------------
    void LoginScreen::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //-----------------------------------------------------------------------------
    void LoginScreen::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //-----------------------------------------------------------------------------
    void LoginScreen::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

	//--------------------------------------------------------------------------
	void LoginScreen::onAnimationStop( CChar* animName )
	{
		Str anim = animName;

		if ( LoginScreenOpCtrl::getInstance().getCtrlState() == LoginScreenOpCtrl::CTRL_STATE_SEL_CHAR )
		{
			if ( !Str(anim).compare("none_none_emote3") )
			{
				mSceneFinishDirty = true;
			}
		}
		else if ( LoginScreenOpCtrl::getInstance().getCtrlState() == LoginScreenOpCtrl::CTRL_STATE_CREATE_CHAR )
		{
			if ( !Str(anim).compare("none_none_emote5") )
			{
				UICreateCharacter::getInstance().sendCharacterData();
			}
		}
	}

	//-----------------------------------------------------------------------------
	IEntity* LoginScreen::getEntity( Int index )
	{
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			if ( index >= 0 && index < ENTITY_SLOT_MAX )
			{
				return scene->getEntity( mEntityList[index].c_str() );
			}
		}

		return NULL;
	}

	//-----------------------------------------------------------------------------
	IEntity* LoginScreen::getEntity( Str8 name )
	{
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			for ( size_t i = 0; i < mEntityList.size(); i++ )
			{
				if ( !mEntityList[i].compare(name) )
				{
					return scene->getEntity( name.c_str() );
				}
			}
		}

		return NULL;
	}

	//-----------------------------------------------------------------------------
	void LoginScreen::setAllEntitysVisible( Bool isVisible )
	{
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			for ( size_t i = 0; i < mEntityList.size(); i++ )
			{
				IEntity* entity = scene->getEntity( mEntityList[i].c_str() );
				if ( entity )
					entity->getSceneNode()->setVisible(isVisible);
			}
		}
	}

	//-----------------------------------------------------------------------------
	I32 LoginScreen::getTempCharIndex( CCharacterSceneEntity* sceneEntity )
	{
		for ( std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.begin(); 
			iter != mTempCharEntityList.end(); iter++)
		{
			if ( iter->second == sceneEntity )
			{
				return iter->first;
			}
		}

		return -1;
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::onInitResourceLoadListener()
	{
		mObjectTotalProgress = 1.0f;
		mCustomObjectProgress = 0.0f;
	}

	//-----------------------------------------------------------------------------
	void LoginScreen::onClearResourceLoadListener()
	{
		mFreshTime = 0.0f;
	}

	//-----------------------------------------------------------------------
	void LoginScreen::preLoadTerrainChunk( UInt index, UInt total )
	{

	}

	//-----------------------------------------------------------------------
	void LoginScreen::postLoadTerrainChunk( UInt index, UInt total )
	{
	}

	//-----------------------------------------------------------------------
	void LoginScreen::preloadObject( UInt index, UInt total )
	{
	}

	//-----------------------------------------------------------------------
	void LoginScreen::postloadObject( ISceneObject* object, UInt index, UInt total )
	{
		if ( total == 0 )
		{
			UILoadingProgress::getInstance().setValue(mObjectTotalProgress);
			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
			return;
		}

		Flt new_progress = Flt(index + 1) / (Flt)total * mObjectTotalProgress;		
		UILoadingProgress::getInstance().setValue(new_progress);

		if ( new_progress - mFreshTime > 0.01f )
		{
			mFreshTime = new_progress;

			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
		}			
	}
	//-----------------------------------------------------------------------
	void LoginScreen::preloadCustomObject( UInt index, UInt total )
	{
		
	}
	//-----------------------------------------------------------------------
	void LoginScreen::postloadCustomObject( ISceneObject* entity, UInt index, UInt total )
	{
		if ( total == 0 )
		{
			UILoadingProgress::getInstance().setValue(mCustomObjectProgress + mObjectTotalProgress);
			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
			return;
		}

		Flt new_progress = Flt(index + 1) / (Flt)total * mCustomObjectProgress + mObjectTotalProgress;		
		UILoadingProgress::getInstance().setValue(new_progress);

		if ( new_progress - mFreshTime > 0.01f )
		{
			mFreshTime = new_progress;

			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
		}			
	}

	//-----------------------------------------------------------------------------
	void LoginScreen::prepareJoiningGame()
	{
		CClan* pClan = CPlayer::getInstance().getActiveClan();
		if ( pClan )
		{				
			CPlayerCharacter* playerCharacter = pClan->getMainGenreal();
			// 如果已经有武将被创建，播放动画进入游戏
			if ( playerCharacter )
			{
				PlayerCharacterData*		pPlayerCharacterData = playerCharacter->getData();
				PlayerCharacterEntityData dynamicDate;
				dynamicDate.belongPlayerID = CPlayer::getInstance().getAccountID();
				dynamicDate.mCharacterTemplateID = pPlayerCharacterData->mCharacterTemplateID;
				dynamicDate.mName = pPlayerCharacterData->mName;
				dynamicDate.surName = pPlayerCharacterData->charSurName;
				dynamicDate.mId = pPlayerCharacterData->mId;
				dynamicDate.mLevel = pPlayerCharacterData->mLevel;
				dynamicDate.hp = pPlayerCharacterData->mHp;
				dynamicDate.mp = pPlayerCharacterData->mMp;

				CPlayerCharacterEntity* playerEntity = CSceneManager::getInstance().createPlayerCharacterEntity( &dynamicDate );
				if ( playerEntity )
				{
					playerEntity->getEntity()->getAnimationController()->setBlendingEnable(true);

					playerEntity->playAnimation( "emote3", false, false, false );
				}

				UIManager::getInstance().closeAllLayout();
			}
			else
			{
				LoginManager::getInstance().sendToFrontServerJoingame();
			}

		}
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::prepareCreateGeneral()
	{
		std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.find(mSelectedGeneralIndex);
		if ( iter != mTempCharEntityList.end() )
		{
			CPlayerCharacterEntity* characterEntity = iter->second;

			characterEntity->playAnimation("emote5",false, false, false);
		}

	}
	//-----------------------------------------------------------------------------
	void LoginScreen::prepareSelectGeneral( CCharacterSceneEntity* characterSceneEntity )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		UICreateCharacter::getInstance().OnMouseOverCharacter( characterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CPlayerCharacterEntity* currentCharacter = NULL;

		std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.find(mSelectedGeneralIndex);
		if ( iter != mTempCharEntityList.end() )
		{
			currentCharacter = iter->second;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for ( std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.begin();
				iter != mTempCharEntityList.end(); iter++ )
		{
			CPlayerCharacterEntity* characterEntity = iter->second;

			if ( characterEntity != currentCharacter )
			{
				characterEntity->getEntity()->
					getModelObject()->setHightLight(1.0f, false);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( characterSceneEntity 
			&& characterSceneEntity != currentCharacter )
		{
			bool highlight = true;

			if ( highlight )
			{
				characterSceneEntity->getEntity()->
					getModelObject()->setHightLight(2.0f, false);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::randomGeneralbyId(U32 randomId)
	{
		if (randomId < 0)
		{
			return;
		}
		
		
		std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.find(randomId); 
		if ( iter != mTempCharEntityList.end() )
		{
			CPlayerCharacterEntity* newChar = iter->second; //随机将要出现的角色
			if (newChar)
			{
				//////////////////
				//旧的归位
				if (mSelectedGeneralIndex > 0)
				{
					CPlayerCharacterEntity* oldChar = mTempCharEntityList.find(mSelectedGeneralIndex)->second; //已经出现的角色
					DYNAMIC_ASSERT(oldChar);
					Vec3 oldPos;
					Vec3 oldDir;

					IEntity* oldEntity = getEntity( ENTITY_CRECHAR_STAND_POINT_1 + mSelectedGeneralIndex );
					if ( oldEntity )
					{
						oldEntity->getSceneNode()->getPosition(oldPos);
						oldEntity->getSceneNode()->getDirection(oldDir);

						oldChar->setPos(oldPos);
						oldChar->setDir(oldDir);
					}
				}
				
				/////
				//设置新的位置

				Vec3 destPos;
				Vec3 destDir;

				IEntity* newEntity = getEntity( ENTITY_CRECHAR_STAND_ROW_1 );
				if ( newEntity )
				{
					newEntity->getSceneNode()->getPosition(destPos);
					newEntity->getSceneNode()->getDirection(destDir);

					newChar->setPos(destPos);
					newChar->setDir(destDir);
				}
				newChar->playAnimation( "emote4", false, true );
				//////
				mSelectedGeneralIndex = randomId;
			}

		}
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::selectGeneral(CCharacterSceneEntity* characterSceneEntity)
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		UICreateCharacter::getInstance().OnClickCharacter( characterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CPlayerCharacterEntity* currentCharacter = NULL;

		std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.find(mSelectedGeneralIndex);
		if ( iter != mTempCharEntityList.end() )
		{
			currentCharacter = iter->second;

			if ( characterSceneEntity == currentCharacter )
				return;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		I32 newCharIndex = -1;

		for ( std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.begin();
			iter != mTempCharEntityList.end(); iter++ )
		{
			if ( iter->second == characterSceneEntity )
			{
				newCharIndex = iter->first;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( newCharIndex >= 0 )
		{
			if ( currentCharacter )
			{
				Vec3 destPos;
				Vec3 destDir;

				IEntity* entity = getEntity( ENTITY_CRECHAR_STAND_POINT_1 + mSelectedGeneralIndex );
				if ( entity )
				{
					entity->getSceneNode()->getPosition(destPos);
					entity->getSceneNode()->getDirection(destDir);
					entity->getModelObject()->setHightLight(1.0f, false);

					currentCharacter->setPos(destPos);
					currentCharacter->setDir(destDir);

					currentCharacter->setHeadDesVisible(true);
				}
			}

			{
				Vec3 destPos;
				Vec3 destDir;

				IEntity* entity = getEntity( ENTITY_CRECHAR_STAND_ROW_1 );
				if ( entity )
				{
					entity->getSceneNode()->getPosition(destPos);
					entity->getSceneNode()->getDirection(destDir);
					entity->getModelObject()->setHightLight(1.4f, false);

					characterSceneEntity->setPos(destPos);
					characterSceneEntity->setDir(destDir);

					characterSceneEntity->setHeadDesVisible(false);
				}

				characterSceneEntity->playAnimation( "emote4", false, true );
			}
		}

		mSelectedGeneralIndex = newCharIndex;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::selectGeneral2( CCharacterSceneEntity* characterSceneEntity )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CPlayerCharacterEntity* currentCharacter = NULL;

		std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.find(mSelectedGeneralIndex);
		if ( iter != mTempCharEntityList.end() )
		{
			currentCharacter = iter->second;

			if ( characterSceneEntity == currentCharacter )
				return;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		I32 newCharIndex = -1;

		for ( std::map<I32, CPlayerCharacterEntity*>::iterator iter = mTempCharEntityList.begin();
			iter != mTempCharEntityList.end(); iter++ )
		{
			if ( iter->second == characterSceneEntity )
			{
				newCharIndex = iter->first;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( newCharIndex >= 0 )
		{
			if ( currentCharacter )
			{
				////////////////////////////////////////////////////////////////////////////

				Vec3 startPos, destPos;

				currentCharacter->getEntity()->
					getSceneNode()->getPosition( startPos );

				IEntity* entity = getEntity( ENTITY_CRECHAR_STAND_POINT_1 + mSelectedGeneralIndex );
				if ( entity )
					entity->getSceneNode()->getPosition(destPos);

				////////////////////////////////////////////////////////////////////////////

				CCSEntityLineMoveAcion* action = CActionManager::getInstance().createCCSEntityLineMoveAcion( currentCharacter, startPos, destPos, 0 );

				action->setMoveSpeed( 1.5f );
				action->setYawSpeed( 0.5f );
				action->setBlockCheck( false );
				action->setAnimation("move");

				currentCharacter->getActionStateManager().push(action/*, false*/);

				////////////////////////////////////////////////////////////////////////////

			}

			{
				Vec3 startPos, destPos;

				characterSceneEntity->getEntity()->
					getSceneNode()->getPosition( startPos );

				IEntity* entity = getEntity( ENTITY_CRECHAR_STAND_ROW_1 + (I32)newCharIndex / (I32)2 );
				if ( entity )
				{
					entity->getSceneNode()->getPosition(destPos);
				}

				////////////////////////////////////////////////////////////////////////////

				CCSEntityLineMoveAcion* action = CActionManager::getInstance().createCCSEntityLineMoveAcion( characterSceneEntity, startPos, destPos, 0 );

				action->setMoveSpeed( 1.5f );
				action->setYawSpeed( 0.5f );
				action->setBlockCheck( false );
				action->setAnimation("move");

				characterSceneEntity->getActionStateManager().push(action/*, false*/);

				////////////////////////////////////////////////////////////////////////////
			}
		}

		mSelectedGeneralIndex = newCharIndex;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::initManualRenderState( I32 ctrlType )
	{
		if ( ctrlType == LoginScreenOpCtrl::CTRL_STATE_SEL_CLAN )
		{
			// 默认的渲染顺序会导致透明物体的渲染异常， 需要调整下渲染顺序...

			IEntity* entity = ClientMain::getInstance().getScene()->getEntity("Sky_001");
			if ( entity )
			{
				entity->setRenderGroup(2, 90);
				entity->getAnimationController()->setIsIdle(true, "none_none_stand");
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Sky_002");
			if ( entity )
			{
				entity->setRenderGroup(2, 91);
				ClientMain::getInstance().getEngine()->engineUtil()->setDepthCheck(entity, false);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Sky_003");
			if ( entity )
			{
				entity->setRenderGroup(2, 92);
				ClientMain::getInstance().getEngine()->engineUtil()->setDepthCheck(entity, false);
				ClientMain::getInstance().getEngine()->engineUtil()->setTextureAnimation( entity, Vec2(0.0f, 0.0f), Vec2(0.02f, 0.0f) );
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Susaku_Entity_Back");
			if ( entity )
			{
				entity->setRenderGroup(2, 93);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Seiryu_Entity_Back");
			if ( entity )
			{
				entity->setRenderGroup(2, 93);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Kenbu_Entity_Back");
			if ( entity )
			{
				entity->setRenderGroup(2, 93);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Biakko_Entity_Back");
			if ( entity )
			{
				entity->setRenderGroup(2, 93);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Susaku_Entity_Front");
			if ( entity )
			{
				entity->setRenderGroup(2, 94);
				ClientMain::getInstance().getEngine()->engineUtil()->setMaterialShiness(entity, 0.8f);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Seiryu_Entity_Front");
			if ( entity )
			{
				entity->setRenderGroup(2, 94);
				ClientMain::getInstance().getEngine()->engineUtil()->setMaterialShiness(entity, 0.8f);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Kenbu_Entity_Front");
			if ( entity )
			{
				entity->setRenderGroup(2, 94);
				ClientMain::getInstance().getEngine()->engineUtil()->setMaterialShiness(entity, 0.8f);
			}

			entity = ClientMain::getInstance().getScene()->getEntity("Biakko_Entity_Front");
			if ( entity )
			{
				entity->setRenderGroup(2, 94);
				ClientMain::getInstance().getEngine()->engineUtil()->setMaterialShiness(entity, 0.8f);
			}
		}
	}
	//-----------------------------------------------------------------------------
	void LoginScreen::onApplyDisplayConfig()
	{
		initManualRenderState(LoginScreenOpCtrl::getInstance().getCtrlState());
	}
}	


