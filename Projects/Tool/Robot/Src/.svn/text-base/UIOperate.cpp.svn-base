//***********************************************************************************************************
#include "stdafx.h"
#include "UIOperate.h"
#include "CClientNew.h"
//***********************************************************************************************************
namespace MG
{
	//--------------------------------------------------
	void AutoJoinGameOp::exe( CClient* client )
	{
		client->autoJoinGame();
	}
	//--------------------------------------------------
	void AutoJoinGameOp::reset()
	{

	}
	//===================================================
	void AccountLoginOp::exe( CClient* client )
	{
 		client->accountLogin();
	}
	//--------------------------------------------------	
	void AccountLoginOp::reset()
	{

	}
	//===================================================
	void ConnectLsOp::exe( CClient* client )
	{
		client->connectLoginServer();
	}
	//--------------------------------------------------
	void ConnectLsOp::reset()
	{

	}
	//===================================================
	void SendDataToLsOp::exe( CClient* client )
	{
		client->sendDataToLoginServer(mSize);
	}
	//--------------------------------------------------
	void SendDataToLsOp::reset()
	{
		mStartTick = MGTimeOp::getCurrTick();
		mLastTick = mStartTick;
	}
	//--------------------------------------------------
	void SendDataToLsOp::setParam( U32 size,U32 intervalTick,U32 lifeCycle )
	{
		mSize = size;
		mIntervalTick = intervalTick;
		mLifeCycle = lifeCycle;
	}
	//--------------------------------------------------
	Bool SendDataToLsOp::isFinish()
	{
		return (MGTimeOp::getCurrTick() - mStartTick) > mLifeCycle;
	}
	//--------------------------------------------------
	Bool SendDataToLsOp::canGet()
	{
		U32 tempTick = MGTimeOp::getCurrTick();
		if (tempTick - mLastTick > mIntervalTick)
		{
			mLastTick = tempTick;
			return true;
		}
		return false;
	}
	//===================================================
	void LoginLsOp::exe( CClient* client )
	{
		client->accountLoginLoginServer();
	}
	//--------------------------------------------------
	void LoginLsOp::reset()
	{

	}
	//===================================================
	void ConnectFsOp::exe( CClient* client )
	{
		client->connectFrontServer();
	}
	//--------------------------------------------------
	void ConnectFsOp::reset()
	{

	}
	//===================================================
	void SendDataToFsOp::exe( CClient* client )
	{
		client->sendDataToFrontServer(mSize);
	}
	//--------------------------------------------------
	void SendDataToFsOp::reset()
	{
		mStartTick = MGTimeOp::getCurrTick();
		mLastTick = mStartTick;
	}
	//--------------------------------------------------
	void SendDataToFsOp::setParam( U32 size,U32 intervalTick, U32 lifeCycle )
	{
		mSize = size;
		mIntervalTick = intervalTick;
		mLifeCycle = lifeCycle;
	}
	//--------------------------------------------------
	Bool SendDataToFsOp::canGet()
	{
		U32 tempTick = MGTimeOp::getCurrTick();
		if (tempTick - mLastTick > mIntervalTick)
		{
			mLastTick = tempTick;
			return true;
		}
		return false;
	}
	//--------------------------------------------------
	Bool SendDataToFsOp::isFinish()
	{
		return (MGTimeOp::getCurrTick() - mStartTick) > mLifeCycle;
	}
	//===================================================
	void LoginFsOp::exe( CClient* client )
	{
		client->accountLoginFrontServer();
	}
	//--------------------------------------------------
	void LoginFsOp::reset()
	{

	}
	//===================================================
	void CreateClanOp::exe( CClient* client )
	{
		client->createClan();
	}
	//--------------------------------------------------
	void CreateClanOp::reset()
	{

	}
	//===================================================
	void CreateCharacterOp::exe( CClient* client )
	{
		client->createCharacter();
	}
	//--------------------------------------------------
	void CreateCharacterOp::reset()
	{

	}
	//===================================================
	void JoinGameOp::exe( CClient* client )
	{
		client->joinGame();
	}
	//--------------------------------------------------
	void JoinGameOp::reset()
	{

	}
	//===================================================
	void RandMoveOp::exe( CClient* client )
	{
		client->randMove();
	}
	//--------------------------------------------------
	void RandMoveOp::reset()
	{
		mStartTick = MGTimeOp::getCurrTick();
		mLastTick = mStartTick;
	}	
	//--------------------------------------------------
	void RandMoveOp::setParam( U32 intervalTick, U32 lifeCycle )
	{
		mIntervalTick = intervalTick;
		mLifeCycle = lifeCycle;
	}
	//--------------------------------------------------
	Bool RandMoveOp::canGet()
	{
		U32 tempTick = MGTimeOp::getCurrTick();
		if (tempTick - mLastTick > mIntervalTick)
		{
			mLastTick = tempTick;
			return true;
		}
		return false;
	}
	//--------------------------------------------------
	Bool RandMoveOp::isFinish()
	{
		if (mLifeCycle == 0)
		{
			return false;
		}
		return (MGTimeOp::getCurrTick() - mStartTick) > mLifeCycle;
	}
	//===================================================
	void CreateTroopOp::exe( CClient* client )
	{
		client->createTroop();
	}
	//--------------------------------------------------
	void CreateTroopOp::reset()
	{

	}
	//===================================================
	void TestSkillOp::exe( CClient* client )
	{
		client->testSkill();
	}
	//--------------------------------------------------
	void TestSkillOp::reset()
	{
		mStartTick = MGTimeOp::getCurrTick();
		mLastTick = mStartTick;
	}
	//--------------------------------------------------
	Bool TestSkillOp::canGet()
	{
		U32 tempTick = MGTimeOp::getCurrTick();
		if (tempTick - mLastTick > mIntervalTick)
		{
			mLastTick = tempTick;
			return true;
		}
		return false;
	}
	//--------------------------------------------------
	Bool TestSkillOp::isFinish()
	{
		return (MGTimeOp::getCurrTick() - mStartTick) > mLifeCycle;
	}
	//===================================================
	void JumpMapOp::exe( CClient* client )
	{
		client->jumpMap();
	}
	//--------------------------------------------------
	void JumpMapOp::reset()
	{

	}
	//===================================================
	void CloseNetOp::exe( CClient* client )
	{
		client->closeNet();
	}
	//--------------------------------------------------
	void CloseNetOp::reset()
	{
		mStartTick = MGTimeOp::getCurrTick();
		mLastTick = mStartTick;
	}
	//--------------------------------------------------
	Bool CloseNetOp::canGet()
	{
		return false;
	}
	//--------------------------------------------------
	Bool CloseNetOp::isFinish()
	{
		return (MGTimeOp::getCurrTick() - mStartTick) > mLifeCycle;
	}
}