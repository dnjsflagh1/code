/******************************************************************************/
#include "stdafx.h"
#include "SCharacterMoveToAction.h"
#include "SCharacter.h"
/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	//游戏对象移动行为
	/******************************************************************************/

	//Str SCharacterMoveToAction::STATE_NAME = "SCharacterMoveToAction";

	//-----------------------------------------------------------------------
	SCharacterMoveToAction::SCharacterMoveToAction( SCharacter* character, Vec3 startMovePos, Vec3 moveToPos )
		:LinedStateObject(STATE_NAME)
		,mCharacter(character)
		,mStartMovePos(startMovePos)
		,mMoveToPos(moveToPos)
		,mCurrMoveTime(0)
		,mMoveTimeLength(0)
		,mMoveSpeed(0)
	{

	}

	//-----------------------------------------------------------------------
	SCharacterMoveToAction::~SCharacterMoveToAction()
	{

	}

	//-----------------------------------------------------------------------
	void SCharacterMoveToAction::onEnter()
	{
		if(mStartMovePos == Vec3(0,0,0))
		{
			mStartMovePos = mCharacter->getPos();
		}
		
		mCharacter->setPos(mStartMovePos);

		mMoveToDir = mMoveToPos - mStartMovePos;
		mMoveDis = mMoveToDir.length();
		mMoveToDir.normalise();

		mMoveTimeLength = mMoveDis / mMoveSpeed;
	}

	//-----------------------------------------------------------------------
	void SCharacterMoveToAction::update( Flt delta )
	{
		mCurrMoveTime += delta;
		Flt currMoveDis = (mCurrMoveTime / mMoveTimeLength) * mMoveDis;

		Vec3 currPos;
		if(mMoveTimeLength > mCurrMoveTime)
		{
			currPos = mStartMovePos + (mMoveToDir * currMoveDis);
		}
		else
		{
			currPos = mMoveToPos;
		}

		mCharacter->setPos(currPos);

		//SRegionObjectBase* regionObjectBase = 0;//mCharacter->getCurrentRegionObject();
		//if(!regionObjectBase)
		//{
		//	return;
		//}

		//if(regionObjectBase->getGameType() == GameType_Rpg)
		//{
		//	GAMEOBJ_TYPE gameObjType = mCharacter->getType();
		//	if(gameObjType == GOT_PLAYERCHARACTER || gameObjType == GOT_MONSTER)
		//	{
		//		mCharacter->addOrUpdateInSceneGrid();
		//	}
		//}
		
	}

	//-----------------------------------------------------------------------
	Bool SCharacterMoveToAction::isFinished()
	{
		if(mCurrMoveTime >= mMoveTimeLength)
		{
			mCharacter->setPos(mMoveToPos);
			return true;
		}
		
		return false;
	}

	//-----------------------------------------------------------------------
	void SCharacterMoveToAction::onLeave()
	{

	}

	//-----------------------------------------------------------------------
	void SCharacterMoveToAction::setMoveSpeed( Flt speed )
	{
		mMoveSpeed = speed;
	}

	//-----------------------------------------------------------------------
	Vec3 SCharacterMoveToAction::getMoveToPos()
	{
		return mMoveToPos;
	}
}