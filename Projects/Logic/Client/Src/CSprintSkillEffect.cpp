/******************************************************************************/
#include "stdafx.h"
#include "CSprintSkillEffect.h"
#include "CSceneManager.h"
#include "ICollisionSystem.h"
#include "CLuaSkillSystem.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "ClientMain.h"
/******************************************************************************/

namespace MG
{
	CSprintSkillEffect::CSprintSkillEffect( CSkillObject* object )
		: CSkillEffect( object ) 
		, mEffectEntity(NULL)
		, mEngineUtil(NULL)
		, mUseCharacter(NULL)
		, mAlreadyMoveDis(0)
		, mCurrMoveDis(0)
		, mMapId(0)
		, mDis(0)
	{

	}

	CSprintSkillEffect::~CSprintSkillEffect()
	{

	}

	void CSprintSkillEffect::start()
	{
		//CSprintSkillEffect::start();

		//mEffectEntity = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mEffectfileName.c_str());
		//if(!mEffectEntity)
		//{
		//	return;
		//}	

		//mEffectEntity->getSceneNode()->setPosition(mPos);
		//mStartPos = mPos;
		//mLastClickTerrainPos = mPos;
		////ClientMain::getInstance().getGameObjectOpCtrl()->setClickTerrainPos(mPos);
		//Vec3 dir(0,0,0);
		//Vec3 dest(0,0,0);

		//if(mUserType == GOT_PLAYERCHARACTER)
		//{
		//	CPlayerCharacterEntity* playerCharacter = CSceneManager::getInstance().getPlayerCharacterEntity(mUserID);

		//	if(playerCharacter)
		//	{
		//		playerCharacter->getEntity()->getSceneNode()->getDirection(dir);
		//		mUseCharacter = playerCharacter;
		//	}
		//}
		////else if(mUserType == GOT_TROOP)
		////{
		////	CTroopGroupEntity* troop = CSceneManager::getInstance().getTroopGroupEntity(mUserID);
		////	if(troop)
		////	{
		////		dir = troop->getDir();
		////		//mUseCharacter = troop;
		////	}
		////}

		//if(mUseCharacter)
		//{
		//	dest = mPos + dir * mDis;
		//	//mUseCharacter->moveTo(dest);
		//}


		//mEngineUtil = ClientMain::getInstance().getEngine()->engineUtil();
		//mMapId = CSceneManager::getInstance().getRegionId();
	}

	void CSprintSkillEffect::end()
	{
		/*CSprintSkillEffect::end();
		
		if(mEffectEntity)
		{
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(mEffectEntity->getName().c_str());
			mEffectEntity = NULL;
		}*/
	}

	void CSprintSkillEffect::update( Flt delta )
	{
		////FUNDETECTION(__MG_FUNC__);
		//CSprintSkillEffect::update( delta );

		//if(!mEffectEntity || !mUseCharacter)
		//{
		//	return;
		//}
		//
		//Vec3 clickTerrainPos = ClientMain::getInstance().getGameObjectOpCtrl()->getLastClickTerrainPos();
		//if(mLastClickTerrainPos != clickTerrainPos)
		//{
		//	mAlreadyMoveDis += /*mEngineUtil->getVectorLenght*/(mPos - mLastClickTerrainPos).length();
		//	
		//	mLastClickTerrainPos = clickTerrainPos;
		//	Vec3 dir(0,0,0);
		//	Vec3 dest(0,0,0);
		//	dir = clickTerrainPos - mPos;
		//	/*dir = */dir.normalise()/*mEngineUtil->getNormaliseVector(dir)*/;
		//	dest = mPos + dir * mDis;

		//	//mUseCharacter->moveTo(dest);	
		//}
		//
		//mCurrMoveDis = /*mEngineUtil->getVectorLenght*/(mPos - clickTerrainPos).length() + mAlreadyMoveDis;

		////Flt currDis = mEngineUtil->getVecterLenght(mPos - mStartPos);

		//mEffectEntity->getSceneNode()->setPosition(mPos);
		//	
		//if( mCurrMoveDis >= mDis)
		//{
		//	mSkillObject->stopUse();
		//	//mUseCharacter->stopMove();
		//	end();
		//}

		//// 检测碰撞
		////Vec3 currPos;
		////mEffectEntity->getSceneNode()->getPosition( currPos );

		//ISceneObjectCollisionCallback callback;
		//callback.queryFlagsMask =  GOT_TROOP | GOT_PLAYERCHARACTER ;
		//callback.isCheckSingle = false;
		//if ( CSceneManager::getInstance().getEngineScene()->getCollisionSystem()->checkLineCollision(mPos, mEffectEntityLastPos, &callback)/*CSceneManager::getInstance().getEngineScene()->getCollisionSystem()->checkLineCollision(currPos,mEffectEntityLastPos,callback)*/ )
		//{
		//	ISceneObject* sceneObject = callback.collisionList[0].second;
		//	ILogicBinder* logicBinder =  NULL;
		//	logicBinder =  sceneObject->getLogicBinder();

		//	if(!logicBinder)
		//	{
		//		return;
		//	}

		//	CCharacterSceneEntity* character= (CCharacterSceneEntity*)logicBinder->manager;
		//	if(!character || character->getID() == mUserID)
		//	{
		//		return;
		//	}

		//	//LuaSkillSystem::getInstance().execClientCollisionAffectScript( character, 1, mSkillObject, this);

		//	if(character->getBelongPlayerID() == CPlayer::getInstance().getAccountID())
		//	{
		//		//SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(mUserType, mSkillObject->getOwner(), (GAMEOBJ_TYPE)logicBinder->type, character, 1, mSkillID, mMapId);
		//	}
		//	//// 分派处理鼠标点击事件
		//	//if(logicBinder->type == GOT_PLAYERCHARACTER)
		//	//{
		//	//	if(character->getID() != mUserID)
		//	//	{

		//	//		

		//	//		if ( !CPlayer::getInstance().getActiveClan()->hasPlayerCharacter( character->getID() ) )
		//	//		{
		//	//			return;
		//	//		}

		//	//		if(mUserType == GOT_PLAYERCHARACTER)
		//	//		{
		//	//			SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket( mUserID, character->getID(), 1, this->getSkillID() );
		//	//		}
		//	//		else if(mUserType == GOT_TROOP)
		//	//		{
		//	//			SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectPlayerCharacterPacket( mUserID, character->getID(), 1, this->getSkillID() );
		//	//		}
		//	//		
		//	//	}

		//	//}
		//	//else if(logicBinder->type == GOT_TROOP)
		//	//{
		//	//	if(character->getID() != mUserID)
		//	//	{

		//	//		LuaSkillSystem::getInstance().execClientCollisionAffectScript( character, 1, mSkillObject, this);

		//	//		if ( !CPlayer::getInstance().getActiveClan()->hasPlayerTroop( character->getID() ) )
		//	//		{
		//	//			return;
		//	//		}

		//	//		if(mUserType == GOT_PLAYERCHARACTER)
		//	//		{
		//	//			SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectTroopPacket( mUserID, character->getID(), 1, this->getSkillID() );
		//	//		}
		//	//		else if(mUserType == GOT_TROOP)
		//	//		{
		//	//			SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectTroopPacket( mUserID, character->getID(), 1, this->getSkillID() );
		//	//		}

		//	//	}
		//	//}

		//}

		//mEffectEntityLastPos = mPos;
	}

	void CSprintSkillEffect::setPos( Vec3 pos )
	{
		mPos = pos;
	}

	void CSprintSkillEffect::setDis( UInt dis )
	{
		mDis = dis;
	}
}