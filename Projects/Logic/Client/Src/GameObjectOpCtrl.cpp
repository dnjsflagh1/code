/******************************************************************************/

#include "stdafx.h"
#include "GameObjectOpCtrl.h"
#include "ClientMain.h"
#include "CPlayerCharacter.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "SkillNetPacketProcesser.h"
#include "PlaceNetPacketProcesser.h"
#include "GameNetPacket.h"
#include "ICollisionSystem.h"
#include "UIJumpRegion.h"
#include "CBuildingEntity.h"
#include "CNpcEntity.h"
#include "CAIManager.h"
#include "CCharacterSceneEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "UICampaignBarrack.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayerCharacterEntity.h"
#include "ArtDecalResTemplate.h"
#include "UIRPGTargetPic.h"
/******************************************************************************/
namespace MG
{

    //--------------------------------------------------------------------------
    GameObjectOpCtrl::GameObjectOpCtrl()
        :mMySelectDecalGroup(NULL)
         ,mEnemySelectDecalGroup(NULL)
         ,mFriendSelectDecalGroup(NULL)
         ,mClickTerrainSign(NULL)
         ,mCurrOperationObjectGroup(NULL)
		 ,mCurrPointSkillDecal(NULL)
         ,mIsFocusRect(false)
		 ,mIntersectionResult(0)
         ,mState(GOS_NONE)
    {
        mMaxNumInGroup = 200;
        revert();
    }

    //--------------------------------------------------------------------------
    GameObjectOpCtrl::~GameObjectOpCtrl()
    {
        clear();
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::update(Flt delta)
    {
        if ( CSceneManager::getInstance().isRegionSceneLoaded() == false )
            return;

        if ( CPlayer::getInstance().getActiveClan() == NULL )
            return;

		if ( CSceneManager::getInstance().getIsStartCampaign() == false )
			return;


        //////////////////////////////////////////////////////////////////

        IPointer* pPointer = ClientMain::getInstance().getPointer();
        if ( pPointer )
        {
            pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_NORMAL ] );
        }
        
        //////////////////////////////////////////////////////////////////

        updateDecal();
        updateClickTerrainSign();
        updateRectSelectWireframe();

        //////////////////////////////////////////////////////////////////

        if ( mCurrOperationObjectGroup )
            mCurrOperationObjectGroup->update( delta );

		if(mCurrPointSkillDecal)
		{
			Vec3 pos;
			if ( ClientMain::getInstance().getScene()->getCollisionSystem()->getMouseRayIntersection(pos,true) )
			{
				mCurrPointSkillDecal->getDecal(0)->setPosition(pos);
			}
		}

        //////////////////////////////////////////////////////////////////

        checkKeyInput();
        checkMouseInput();

        //////////////////////////////////////////////////////////////////

        mAIGroupManager.update(delta);
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::clear()
    {
        mMySelectDecalGroup     = NULL;
        mFriendSelectDecalGroup = NULL;
        mEnemySelectDecalGroup  = NULL;

        mClickTerrainSign       = NULL;

		mPointSkillDecalList.clear();

		if(mCurrPointSkillDecal)
		{
			mCurrPointSkillDecal = NULL;
			//ClientMain::getInstance().getScene()->destroyEffectComponent(mPointSkillDecal->getName().c_str());
		}

        revert();
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::revert()
    {
        setState( GOS_NORMAL );

        clearSelected();
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        mMySelectDecalGroup = CSceneManager::getInstance().getEngineScene()->createDecalSet(mMaxNumInGroup,"SelectedCircle.png", DT_SIMPLE);
        mFriendSelectDecalGroup = CSceneManager::getInstance().getEngineScene()->createDecalSet(mMaxNumInGroup,"SelectedCircle2.png", DT_SIMPLE);
        mEnemySelectDecalGroup = CSceneManager::getInstance().getEngineScene()->createDecalSet(mMaxNumInGroup,"SelectedCircle3.png", DT_SIMPLE);

        mClickTerrainSign = CSceneManager::getInstance().getEngineScene()->createEntity("clickGround", 200003);
        if (mClickTerrainSign)
        {
            mClickTerrainSign->getSceneNode()->setVisible( false );
            mClickTerrainSign->getAnimationController()->setLoop("click01",false);
            //mClickTerrainSign->getAnimationController()->setLastFrameStopEnable("gather",true);
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        clear();
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::addSelected( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->addGameObject( entity );
        }
    }

    //--------------------------------------------------------------------------   
    void GameObjectOpCtrl::clearSelected()
    {
        mCurrOperationObjectGroup = &mDefaultOperationObjectGroup;

        mCurrOperationObjectGroup->clear();
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::requestUseSkill(IdType skillId, GAMEOBJ_TYPE userType, IdType userId, UInt userIndex)
    {
        if ( mCurrOperationObjectGroup )
		{
			destroyPointSkillDecal();
            mCurrOperationObjectGroup->requestUseSkill( skillId, userType, userId, userIndex );
        }
    }


    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::setState(GAMEOBJECT_OP_STATE state)
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->setState( state );
        }
        mState = state;
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::updateDecal()
    {

        if ( mMySelectDecalGroup )
        {
            mMySelectDecalNum = 0;

            UInt count = mMySelectDecalGroup->getDecalNum();
            for ( UInt i=mMySelectDecalNum; i<count; i++ ) 
            {
                mMySelectDecalGroup->getDecal(i)->setVisible( false );
            }
        }

        if ( mFriendSelectDecalGroup )
        {
            mFriendSelectDecalNum = 0;

            UInt count = mFriendSelectDecalGroup->getDecalNum();
            for ( UInt i=mFriendSelectDecalNum; i<count; i++ ) 
            {
                mFriendSelectDecalGroup->getDecal(i)->setVisible( false );
            }
        }

        if ( mEnemySelectDecalGroup )
        {
            mEnemySelectDecalNum = 0;

            UInt count = mEnemySelectDecalGroup->getDecalNum();
            for ( UInt i=mEnemySelectDecalNum; i<count; i++ ) 
            {
                mEnemySelectDecalGroup->getDecal(i)->setVisible( false );
            }
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::updateClickTerrainSign()
    {
        if ( mClickTerrainSign )
        {
            if ( mClickTerrainSign->getSceneNode()->getVisible() )
            {
                if ( mClickTerrainSign->getAnimationController()->isPlaying("click01") == false )
                {
                    mClickTerrainSign->getSceneNode()->setVisible(false);
                }
            }
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::updateRectSelectWireframe()
    {
        IInput* input =  ClientMain::getInstance().getEngine()->input();
        IWireframeManager* wireframeMgr =  ClientMain::getInstance().getScene()->getWireframeManager();
        if (!input)
        {
            return;
        }
        if (!wireframeMgr)
        {
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////

        if ( input->isMouseHolded(MB_Left) && mIsFocusEnable )
        {
            mIsFocusRect = true;
        }else
        {
            mIsFocusRect = false;
        }

        if ( input->isMousePressed(MB_Left) )
        {
            Vec2 mousePos = input->getMousePos();
            if ( ClientMain::getInstance().getGui()->isMouseCanHoldUI() )
            {
                mIsFocusEnable = false;
            }else
            {
                mIsFocusEnable = true;
            }
            mRectPressedMousePos = input->getMousePos();
        }

        if ( mIsFocusRect )
        {
            mRectHoledMousePos = input->getMousePos();

            IScreenRectWireframeDecorator* decoratorShadow = wireframeMgr->createScreenRectWireframeDecorator( "Client_RectSelectShadow_ScreenRectWireframeDecorator" );
            IScreenRectWireframeDecorator* decorator = wireframeMgr->createScreenRectWireframeDecorator( "Client_RectSelect_ScreenRectWireframeDecorator" );
            
            RectF rect;
            rect.left           = mRectPressedMousePos.x;
            rect.top            = mRectPressedMousePos.y;
            rect.right          = mRectHoledMousePos.x;
            rect.bottom         = mRectHoledMousePos.y;

            RectF rectShadow;
            rectShadow.left     = mRectPressedMousePos.x + 1;
            rectShadow.top      = mRectPressedMousePos.y + 1;
            rectShadow.right    = mRectHoledMousePos.x + 1;
            rectShadow.bottom   = mRectHoledMousePos.y + 1;

            if ( decorator && decoratorShadow )
            {
                decorator->setRect( rect, true );
                decoratorShadow->setRect( rectShadow, true );
                decoratorShadow->setColour( Color(0.5,0.5,0.5,1) );
            }
        }
    }

    //--------------------------------------------------------------------------
    Bool GameObjectOpCtrl::checkKeyInput()
    {
        checkShortcutKey();
        return true;
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::checkShortcutKey()
    {
        //if ( ClientMain::getInstance().getEngine()->input()->isKeyPressed(KC_E) )
        //{
        //    revert();
        //}
    }

    //--------------------------------------------------------------------------
    Bool GameObjectOpCtrl::checkMouseInput()
    {
        // 如果鼠标是在UI上面，则不处理游戏对象操作
        if ( ClientMain::getInstance().getGui()->isMouseCanHoldUI() )
        {
            return true;
        }

        // 输入管理者
        IInput* input = ClientMain::getInstance().getEngine()->input();

        // 射线查询对象
        ISceneObject* sceneObject   =   NULL;
        ILogicBinder* logicBinder   =   NULL;
        CSceneEntity* cSceneEntity  =   NULL;

        //////////////////////////////////////////////////////////////////////////////////////////////////////

        // 拾取实体的检测
        {
            ISceneObjectCollisionCallback callback;
            callback.isCheckSingle = false;
            callback.queryFlagsMask = GQT_TROOP | GQT_NPC | GQT_SOLDIER | GQT_PLAYERCHARACTER | GQT_ORDINARY_BUILDING | GQT_BUILDING | GQT_MONSTER | GQT_ITEM;
            Vec2 mouseOffset = Vec2(16,16);
            if ( ClientMain::getInstance().getScene()->getCollisionSystem()->checkMouseRayCollision(&callback,mouseOffset) )
            {
                sceneObject = callback.collisionList[0].second;

                if ( (mState == GOS_NORMAL) && mCurrOperationObjectGroup )
                {
                    CSceneEntity* ctempSceneEntity  =   NULL;
                    for ( UInt i=0; i<callback.collisionList.size(); i++ )
                    {
                        ctempSceneEntity = static_cast<CSceneEntity*>( callback.collisionList[i].second->getLogicBinder()->manager ) ;
                        DYNAMIC_ASSERT_LOG( ctempSceneEntity!=NULL, "GameObjectOpCtrl::checkMouseInput : logicBinder is null!");

                        if ( mCurrOperationObjectGroup->hasGameObject( ctempSceneEntity ) == false )
                        {
                            sceneObject = callback.collisionList[i].second;
                            break;
                        }
                    }
                }

                if(sceneObject)
                {
                    // 根据游戏逻辑绑定对象分派消息
                    logicBinder =  sceneObject->getLogicBinder();

                    // 分派处理鼠标点击事件
                    // 游戏玩家角色对象
                    if( logicBinder )
                    {
                        /////////////////////////////////////////////////////////////////////////////////////////

                        //if(logicBinder->type != GOT_TROOP)
                        //{
                            cSceneEntity = static_cast<CSceneEntity*>(logicBinder->manager);
                        //}
                        //else
                        //{
                        //    //entity = ((CTroopObject*)logicBinder->manager)->getSoldierEntitys( sceneObject );
                        //    entity = ((CTroopEntity*)logicBinder->manager)->getSoldierEntitys( UInt(0) );
                        //}

                        /////////////////////////////////////////////////////////////////////////////////////////

                        DYNAMIC_ASSERT_LOG( cSceneEntity!=NULL, "GameObjectOpCtrl::checkMouseInput : logicBinder is null!");

                        if ( !cSceneEntity )
                            return false;
                    }
                }
            }
        }
       
        //////////////////////////////////////////////////////////////////////////////////////////////////////

        // 地面可新走区域检测
        Bool isInterseced = false;
        Vec3 pos;
        {
            //if ( input->isMouseHolded(MB_Left)   || input->isMouseHolded(MB_Right)  ||
            //    input->isMousePressed(MB_Left)  || input->isMousePressed(MB_Right) || 
            //    input->isMouseReleased(MB_Left) || input->isMouseReleased(MB_Right) )
			if ( !cSceneEntity )
            {

                // 分配处理鼠标左健地面事件
                mIntersectionResult = 0;
                if ( mIntersectionResult = ClientMain::getInstance().getScene()->getCollisionSystem()->getMouseRayIntersection(pos,true) )
                {
                    isInterseced = true;
                }else
                if ( mIntersectionResult = ClientMain::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,false) )
                {
                    isInterseced = true;
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( isInterseced || cSceneEntity )
        {
            //////////////////////////////////////////////////////////////////
            // 过滤
            if ( cSceneEntity )
            {
                if ( cSceneEntity->getType() == GOT_BUILDING )
                {
                    if ( mIntersectionResult == 2 )
                    {
                        // 如果点选中建筑表面，则忽略点选建筑
                        cSceneEntity = NULL;
                    }
                }
            }

            ////////////////////////////////////////////////////////////////// 
            // 点选位置
            if ( isInterseced )
            {
                // 如果选取实体为空
                if ( cSceneEntity == NULL )
                {
                    if ( input->isMousePressed(MB_Left) )
                    {
                        onLeftMousePressed( pos );
                    }else
                    if ( input->isMouseReleased(MB_Left) )
                    {
                        onLeftMouseReleased( pos );
                    }

                    if ( input->isMousePressed(MB_Right) )
                    {
                        onRightMousePressed( pos );
                    }else
                    if ( input->isMouseReleased(MB_Right) )
                    {
                        onRightMouseReleased( pos );
                    }
                }

                //////////////////////////////////////////////////////////////

                if ( input->isMousePressed(MB_Left) )
                {
                    mLeftMousePressedPos = pos;
                }else
                if ( input->isMouseReleased(MB_Left) )
                {
                    onLeftMouseClick( mLeftMousePressedPos, pos );
                }

                if ( input->isMousePressed(MB_Right) )
                {
                    mRightMousePressedPos = pos;
                }else
                if ( input->isMouseReleased(MB_Right) )
                {
                    onRightMouseClick( mRightMousePressedPos, pos );
                }

                //////////////////////////////////////////////////////////////

                if ( input->isMouseHolded(MB_Left) )
                {
                    onLeftMouseHoled( mLeftMousePressedPos, pos );
                }

                if ( input->isMouseHolded(MB_Right) )
                {
                    onRightMouseHoled( mRightMousePressedPos, pos );
                }
            }

            //////////////////////////////////////////////////////////////////
            // 拾取实体
            if ( cSceneEntity )
            {
                if ( input->isMousePressed(MB_Left) )
                {
                    mLeftMousePressedObj = cSceneEntity;
                    onLeftMousePressed( cSceneEntity );

                }else
                if ( input->isMouseReleased(MB_Left) )
                {
                    onLeftMouseReleased( cSceneEntity );

                    if ( cSceneEntity == mLeftMousePressedObj )
                    {
                        onLeftMouseClick(cSceneEntity);
                    }
                }

                //////////////////////////////////////////////////////////////////

                if ( input->isMousePressed(MB_Right) )
                {

                    mRightMousePressedObj = cSceneEntity;
                    onRightMousePressed( cSceneEntity );

                }else
                if ( input->isMouseReleased(MB_Right) )
                {
                    onRightMouseReleased( cSceneEntity );

                    if ( cSceneEntity == mRightMousePressedObj )
                    {
                        onRightMouseClick(cSceneEntity);
                    }
                }

                //////////////////////////////////////////////////////////////////

                onMouseOver( cSceneEntity );
            }
			else
			{
				onMouseOver( pos );
			}
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( input->isMouseReleased(MB_Left) )
        {
            mLeftMousePressedObj = NULL;

        }else
        if ( input->isMouseReleased(MB_Right) )
        {
            mRightMousePressedObj = NULL;
        }

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		Vec2 mousePos = ClientMain::getInstance().getEngine()->input()->getMouseScreenPos();
		if ( input->isMousePressed(MB_Left) )
		{
			mLeftMousePressedScreenPos = mousePos;
		}

		if ( input->isMousePressed(MB_Right) )
		{
			mRightMousePressedScreenPos = mousePos;
		}

		if ( input->isMouseHolded(MB_Left) )
		{
			onLeftMouseHoled( mLeftMousePressedScreenPos, mousePos );
		}

		if ( input->isMouseHolded(MB_Right) )
		{
			onRightMouseHoled( mRightMousePressedScreenPos, mousePos );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( input->isCtrlOn() && 
			input->isKeyReleased(KC_F) )
		{
			U32 trackID = 0;

			CPlayer* myPlayer = &(CPlayer::getInstance());
			if ( CPlayer::getInstance().getActiveClan() )
			{
				trackID = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
			}

			if ( trackID != 0 )
			{
				CPlayerCharacterEntity* playerEntity = CSceneManager::getInstance().getPlayerCharacterEntity( trackID );
				if ( playerEntity )
				{
					static bool battleState = false;

					battleState = !battleState;
					playerEntity->setBattleState(battleState);
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////

        return true;
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onMouseOver( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onMouseOver( entity );

            setHightLight( entity );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onMouseOver( Vec3 pos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onMouseOver( pos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMousePressed( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
			if (entity)
			{
				if( entity->getType() == GOT_PLAYERCHARACTER ||  
					entity->getType() == GOT_MONSTER || 
					entity->getType() == GOT_THIRDPARTYCHARACTER || 
					entity->getType() == GOT_NPC
					)
				{	
					
					UIRPGTargetPic::getInstance().setTargetEntity(entity);
					UIRPGTargetPic::getInstance().openGui();
				}
				
			}
		
			mCurrOperationObjectGroup->onLeftMousePressed( entity );
        }

		if (GOT_BUILDING == entity->getType())
		{
			//暂不上线
			//return;

			CPlayer* myPlayer = &(CPlayer::getInstance());
			
			//暂不检测势力
			//const PlayerCharacterIdType myPlayerCharacterId = myPlayer->getMainGenreal()->getData()->mId;
			//CPlayerCharacterEntity* myPlayerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(myPlayerCharacterId);
			//if (NULL == myPlayerCharacterEntity)
			//{
			//	DYNAMIC_ASSERT(0);
			//	return;
			//}

			const FORCE myPlayerCharacterForce = myPlayer->getForce()/*((CCharacterSceneEntityDynamicData*)myPlayerCharacterEntity->getDynamicData())->force*/;
			if (myPlayerCharacterForce != entity->getDynamicData()->force)
			{
				return;
			}

			
			const AccountIdType accountId = myPlayer->getAccountID();
			const CampaignIdType campaignId = myPlayer->getMyCampaignId();
			const CampIdType campId = entity->getID();
			
			if (campaignId <= 0)
			{
				return;
			}

			AccountIdType campOwnerAccountId = entity->getDynamicData()->belongPlayerID;
			DYNAMIC_ASSERT(campOwnerAccountId > 0);
			UICampaignBarrack::getInstance().setCampId(campId);
			UICampaignBarrack::getInstance().setCampOwnerId(campOwnerAccountId);
			CampaignNetPacketProcesser::getInstance().sendCampaignTroopControllerList(accountId, campaignId, campId);
			
			
			return;
		}
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMouseReleased( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onLeftMouseReleased( entity );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMouseClick( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onLeftMouseClick( entity );

            /*mCurrOperationObjectGroup->clearState();*/
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMousePressed( Vec3 pos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onLeftMousePressed( pos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMouseReleased( Vec3 pos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onLeftMouseReleased( pos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMouseClick( Vec3 pressedPos, Vec3 releasedPos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onLeftMouseClick( pressedPos, releasedPos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onLeftMouseHoled( Vec3 pressedPos, Vec3 holedPos )
    {
    }

	//--------------------------------------------------------------------------
	void GameObjectOpCtrl::onLeftMouseHoled( Vec2 pressedScreenPos, Vec2 holedScreenPos )
	{
		if(mCurrOperationObjectGroup && mCurrOperationObjectGroup->getState() == GOS_NORMAL)
		{
			rectSelect( pressedScreenPos, holedScreenPos );
			mCurrOperationObjectGroup->revert();
		}
	}

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMousePressed( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
			if (entity)
			{
				if( entity->getType() == GOT_PLAYERCHARACTER ||  
					entity->getType() == GOT_MONSTER || 
					entity->getType() == GOT_THIRDPARTYCHARACTER || 
					entity->getType() == GOT_NPC
					)
				{	

					UIRPGTargetPic::getInstance().setTargetEntity(entity);
					UIRPGTargetPic::getInstance().openGui();
				}

			}
            mCurrOperationObjectGroup->onRightMousePressed( entity );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMouseReleased( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onRightMouseReleased( entity );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMouseClick( CSceneEntity* entity )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onRightMouseClick( entity );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMousePressed( Vec3 pos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onRightMousePressed( pos );
        }

        showClickTerrainEffect( pos );
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMouseReleased( Vec3 pos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onRightMouseReleased( pos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMouseClick( Vec3 pressedPos, Vec3 releasedPos )
    {
        if ( mCurrOperationObjectGroup )
        {
            mCurrOperationObjectGroup->onRightMouseClick( pressedPos, releasedPos );
        }
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::onRightMouseHoled( Vec3 pressedPos, Vec3 holedPos )
    {
        
    }

	//--------------------------------------------------------------------------
	void GameObjectOpCtrl::onRightMouseHoled( Vec2 pressedScreenPos, Vec2 holedScreenPos )
	{

	}

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::setHightLight( CSceneEntity* entity )
    {
        IEntity* iEntity = entity->getEntity();
        if ( iEntity )
        {
            iEntity->getModelObject()->setHightLight(Flt(1.2),true);
        }
    }

	//--------------------------------------------------------------------------
	Bool GameObjectOpCtrl::isInRect( RectF& rect, CSceneEntity* entity )
	{	
		if ( !entity )
			return false;

		Vec2 screenPos;
		if ( entity->getScreenPos( screenPos, Vec3(0,0,0) ) == false )
			return false;


		if(screenPos.y  >= rect.top)
		{
			return false;
		}
		else 
		if(screenPos.y  <= rect.bottom)
		{
			return false;
		}
		else 
		if(screenPos.x  <= rect.left)
		{
			return false;
		}
		else 
		if(screenPos.x  >= rect.right)
		{
			return false;
		}

		return true;
	}

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::rectSelect( Vec2 pressedPos, Vec2 releasedPos )
    {
        if ( mCurrOperationObjectGroup )
        {

			mGameObjectList.clear();

			CSceneManager& scnMgr = CSceneManager::getInstance();
            CSceneEntity* entity   =   NULL;

            MG::RectF rect;
			rect.left   = (pressedPos.x>releasedPos.x) ? releasedPos.x : pressedPos.x;
            rect.right  = (pressedPos.x>releasedPos.x) ? pressedPos.x  : releasedPos.x;

            rect.top    = (pressedPos.y>releasedPos.y) ? pressedPos.y  : releasedPos.y;
            rect.bottom = (pressedPos.y>releasedPos.y) ? releasedPos.y : pressedPos.y;

			// CPlayerCharacterEntity
			{
				std::map<IdType, CPlayerCharacterEntity*>::iterator iter = scnMgr.mPlayerChaEntityList.begin();
				for ( ; iter != scnMgr.mPlayerChaEntityList.end(); iter ++)
				{
					if ( isInRect( rect, iter->second ) )
					{
						mGameObjectList.push_back( iter->second );
					}
				}
			}



			// troop
			{
				std::map<IdType, CTroopEntity*>::iterator iter = scnMgr.mTroopEntityList.begin();
				for ( ; iter != scnMgr.mTroopEntityList.end(); iter ++)
				{
					//std::map<UInt, CTroopSoldierEntity*>::iterator jter = iter->second->mTroopSoldierEntityList.begin();
					//for ( ; jter != iter->second->mTroopSoldierEntityList.end(); jter ++)
					//{
						if ( isInRect( rect, iter->second ) )
						{
							mGameObjectList.push_back( iter->second );
						}
					//}
				}
			}

			// selectGameObject
			{
				if ( mGameObjectList.empty() == false )
				{
					mCurrOperationObjectGroup->clear();

					for ( UInt i=0; i<mGameObjectList.size(); i++ )
					{
						mCurrOperationObjectGroup->selectGameObject( mGameObjectList[i] );
					}
				}
			}
		}
    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::showClickTerrainEffect( Vec3 pos )
    {   
        if (mClickTerrainSign)
        {
            mClickTerrainSign->getSceneNode()->setVisible( true );
            mClickTerrainSign->getSceneNode()->setPosition(pos);
            mClickTerrainSign->getAnimationController()->setTimePosition("click01",0);
            mClickTerrainSign->getAnimationController()->play("click01");
        }

    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::addGroup( UInt groupIndex )
    {

    }

    //--------------------------------------------------------------------------
    void GameObjectOpCtrl::selectGroup( UInt groupIndex )
    {
        
    }

	//--------------------------------------------------------------------------
	void GameObjectOpCtrl::createPointSkillDecal( UInt pointSkillDecalID, UInt size )
	{
		IDecalSet* pointSkillDecal = NULL;
		std::map<UInt, IDecalSet*>::iterator it = mPointSkillDecalList.find(pointSkillDecalID);
		if(it != mPointSkillDecalList.end())
		{
			pointSkillDecal = it->second;
			if(!pointSkillDecal)
			{
				return;
			}

		}
		else
		{
			const ArtDecalResInfo* artDecalResInfo = ArtDecalResTemplate::getInstance().getArtDecalResInfo(pointSkillDecalID);
			if(!artDecalResInfo)
			{		
				return;
			}

			Str aFlieName;
			MGStrOp::toString(artDecalResInfo->fileName.c_str(), aFlieName);
			pointSkillDecal = CSceneManager::getInstance().getEngineScene()->createDecalSet(1, aFlieName.c_str(), DT_SIMPLE);
			mPointSkillDecalList[pointSkillDecalID] = pointSkillDecal;
		}

		pointSkillDecal->getDecal(0)->setVisible(true);
		//pointSkillDecal->getDecal(0)->setSize(size);
		pointSkillDecal->setSize(size);
		mCurrPointSkillDecal = pointSkillDecal;
	}

	//--------------------------------------------------------------------------
	void GameObjectOpCtrl::destroyPointSkillDecal()
	{
		if(mCurrPointSkillDecal)
		{
			mCurrPointSkillDecal->getDecal(0)->setVisible(false);
			mCurrPointSkillDecal = NULL;
		}
	}

	//--------------------------------------------------------------------------
	Int GameObjectOpCtrl::getIntersectionResult()
	{
		return mIntersectionResult;
	}

	//--------------------------------------------------------------------------
	OperationObjectGroup*  GameObjectOpCtrl::getCurrOperationObjectGroup()
	{
		return mCurrOperationObjectGroup;
	}
	

}