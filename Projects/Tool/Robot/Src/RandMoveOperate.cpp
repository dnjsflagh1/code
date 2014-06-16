/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
//#include "ClientManager.h"
#include "RandMoveOperate.h"
#include "ThreadTaskManager.h"
/******************************************************************************/
namespace MG
{
	//U32	RandMoveOperate::mEnterTick = 0;
	U32	RandMoveOperate::mIntervalTime = 300;
	U32 RandMoveOperate::lifePeroid = 0;
	//----------------------------------------------------------------------
	RandMoveOperate::RandMoveOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{
		mIsEnter = 0;
        mLastMoveTime = 0;
	}
	//----------------------------------------------------------------------
	Bool RandMoveOperate::onEnter()
	{

		if(BaseOperate::onEnter())
		{
			mEnterTick = MGTimeOp::getCurrTick();
			mMsg->AddMsg("������ƶ���������-----������-----");
			if (mClient->getState().isJoinGame)
			{

				mClient->stateRandMove();
				mLastMoveTime = mEnterTick;
				mIsNormalExit = true;
			}
			else
			{
				mMsg->AddErrorMsg("������ƶ�����û�н�����Ϸ");
				mIsNormalExit = false;
				mIsFinish = true;
			}

		}
		return true;
	}
	//----------------------------------------------------------------------
	void RandMoveOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		DYNAMIC_ASSERT(false);
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	void RandMoveOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	MG::Bool RandMoveOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();

		
		if ( lifePeroid == 0)		//move once
		{
			if ( state.isJoinGame && MGTimeOp::getCurrTick() - mEnterTick >= mIntervalTime)
		    {
			     return true;
		    }

		}
		else						// move in time 
		{
              if (state.isJoinGame && MGTimeOp::getCurrTick() - mEnterTick >= lifePeroid)
              {
                    return true;
              }
		}
		
			
		return false;
	}
	//----------------------------------------------------------------------
	void RandMoveOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		
	}
	//----------------------------------------------------------------------
	void RandMoveOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("������ƶ��������");
				}
				else
				{
					mMsg->AddErrorMsg("������ƶ���������");
				}
				mMsg->AddMsg("<---------������ƶ���--------->");
				mManager->setCurrentOperate();
			}
		}
	}

	void RandMoveOperate::update()
	{
		  if (lifePeroid !=0)
		  {
			  ClientState& state = mClient->getState();
			  if (state.isJoinGame && MGTimeOp::getCurrTick() - mLastMoveTime >= mIntervalTime)
			  {
                     mMsg->AddMsg("������ƶ�����-----������-----");
					 mClient->stateRandMove();
			  }
		  }
          
   
	}


	/******************************************************************************/
	//----------------------------------------------------------------------
	ConnectLoginOperate::ConnectLoginOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool ConnectLoginOperate::onEnter()
	{

		if(BaseOperate::onEnter())
		{
			mEnterTick = MGTimeOp::getCurrTick();
			mMsg->AddMsg("�����ӵ�¼��������������-----������-----");
			if (mClient->isDisconnect())
			{
				NetAddress addr(mClient->getIp(),2000);
				I32 netId = mClient->stateConnectLoginServer(addr);
				if(netId > -1)
				{
					//ClientManager::getInstance().addClientToLoginMap(mClient->getLoginServerNetId(),mClient);
					ThreadTaskManager::getInstance().addLoginClient(netId,mClient);
					mMsg->AddMsg("�����ӵ�¼����������������LoginServer");
				}
				else
				{
					mMsg->AddErrorMsg("�����ӵ�¼����������δ������LoginServer");
					mIsNormalExit = true;
				}
				
				mIsFinish = true;

			}
			else
			{
				mMsg->AddErrorMsg("�����ӵ�¼�����������Ѿ�����");
				mIsNormalExit = false;
				mIsFinish = true;
			}

		}
		return true;
	}
	//----------------------------------------------------------------------
	void ConnectLoginOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	void ConnectLoginOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		DYNAMIC_ASSERT(false);
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	Bool ConnectLoginOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------
	void ConnectLoginOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void ConnectLoginOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("�����ӵ�¼�������������");
				}
				else
				{
					mMsg->AddErrorMsg("�����ӵ�¼��������������");
				}
				mMsg->AddMsg("<---------�����ӵ�¼��������--------->");
				mManager->setCurrentOperate();
			}
		}
	}



	/******************************************************************************/
	U32	NetTestLoginOperate::mIntervalTime = 100;
	I32	NetTestLoginOperate::mSize = 3000;
	//----------------------------------------------------------------------
	NetTestLoginOperate::NetTestLoginOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{
		mEnterTick = MGTimeOp::getCurrTick();
		mLastSendTime = mEnterTick;
	}
	//----------------------------------------------------------------------
	Bool NetTestLoginOperate::onEnter()
	{

		if(BaseOperate::onEnter())
		{
			mEnterTick = MGTimeOp::getCurrTick();
			mMsg->AddMsg("������Login������������-----������-----");
			if (mClient->getLoginServerNetId() != -1)
			{

				mClient->stateTestSendDataToLoginServer(mSize);
				mLastSendTime = mEnterTick;
				mIsNormalExit = true;
			}
			else
			{
				mMsg->AddErrorMsg("������Login��������û��������Login");
				mIsNormalExit = false;
				mIsFinish = true;
			}

		}
		return true;
	}
	//----------------------------------------------------------------------
	void NetTestLoginOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		DYNAMIC_ASSERT(false);
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	void NetTestLoginOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	MG::Bool NetTestLoginOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		if ( MGTimeOp::getCurrTick() - mEnterTick >= mIntervalTime)
		{
				return true;
		}
		return false;
	}
	//----------------------------------------------------------------------
	void NetTestLoginOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void NetTestLoginOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("������Login�����������");
				}
				else
				{
					mMsg->AddErrorMsg("������Login������������");
				}
				mMsg->AddMsg("<---------������Login������--------->");
				mManager->setCurrentOperate();
			}
		}
	}

}

