/******************************************************************************/
#include "stdafx.h"
#include "CClient.h"
#include "Operate.h"
#include "OperateManager.h"
#include "OperatePage.h"
//#include "ClientManager.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	ObjectPool<AccountLoginOperate>		OperateManager::mAccountLoginOperatePool;
	ObjectPool<CreateClanOperate>		OperateManager::mCreateClanOperatePool;
	ObjectPool<DeleteClanOperate>		OperateManager::mDeleteClanOperatePool;
	ObjectPool<JoinGameOperate>			OperateManager::mJoinGameOperatePool;
	ObjectPool<CloseOperate>			OperateManager::mCloseOperatePool;
	ObjectPool<AutoJoinGameOperate>		OperateManager::mAutoJoinGameOperatePool;
	ObjectPool<UseSkillOperate>			OperateManager::mUseSkillOperatePool;
	ObjectPool<RandMoveOperate>			OperateManager::mRandMoveOperatePool;
	ObjectPool<NetTestOperate>			OperateManager::mNetTestOperatePool;
	ObjectPool<CreateTroopOperate>		OperateManager::mCreateTroopOperatePool;
	ObjectPool<CampaignOperate>			OperateManager::mCampaignOperatePool;
	ObjectPool<NetTestLoginOperate>		OperateManager::mNetTestLoginOperatePool;
	ObjectPool<ConnectLoginOperate>		OperateManager::mConnectLoginOperatePool;
	//--------------------------------------------------------------------------------
	OperateManager::OperateManager( CClient* client )
	{
		DYNAMIC_ASSERT(client);
		mClient = client;
		mCurrOperate = NULL;
		mIsCreateOperate = false;
		mAccountLoginOperate	= MG_NEW AccountLoginOperate(this,mClient,client->getClientMessage(),OperateType_AccountLogin);
		mCreateClanOperate		= MG_NEW CreateClanOperate(this,mClient,client->getClientMessage(),OperateType_CreateClan);
		mDeleteClanOperate		= MG_NEW DeleteClanOperate(this,mClient,client->getClientMessage(),OperateType_DeleteClan);
		mJoinGameOperate		= MG_NEW JoinGameOperate(this,mClient,client->getClientMessage(),OperateType_Close);
		mCloseOperate			= MG_NEW CloseOperate(this,mClient,client->getClientMessage(),OperateType_AccountLogin);
		mAutoJoinGameOperate	= MG_NEW AutoJoinGameOperate(this,mClient,client->getClientMessage(),OperateType_AutoJoinGame);
		mUseSkillOperate		= MG_NEW UseSkillOperate(this,mClient,client->getClientMessage(),OperateType_UseSkill);
		mRandMoveOperate		= MG_NEW RandMoveOperate(this,mClient,client->getClientMessage(),OperateType_RandMove);
		mNetTestOperate			= MG_NEW NetTestOperate(this,mClient,client->getClientMessage(),OperateType_NetTest);
		mCreateTroopOperate		= MG_NEW CreateTroopOperate(this,mClient,client->getClientMessage(),OperateType_CreateTroop);
		mCampaignOperate		= MG_NEW CampaignOperate(this,mClient,client->getClientMessage(),OperateType_CreateCampaign);
		mNetTestLoginOperate	= MG_NEW NetTestLoginOperate(this,mClient,client->getClientMessage(),OperateType_TestNetLogin);
		mConnectLoginOperate	= MG_NEW ConnectLoginOperate(this,mClient,client->getClientMessage(),OperateType_connectLogin);
		mChatOperate            = MG_NEW ChatOperate(this,mClient,client->getClientMessage(),OperateType_netChat);

		mCurrOperateIndex = 0;
	}
	//--------------------------------------------------------------------------------
	OperateManager::~OperateManager()
	{
		MG_SAFE_DELETE(mCurrOperate				);
		MG_SAFE_DELETE(mAccountLoginOperate		);
		MG_SAFE_DELETE(mCreateClanOperate		);		
		MG_SAFE_DELETE(mDeleteClanOperate		);		
		MG_SAFE_DELETE(mJoinGameOperate			);	
		MG_SAFE_DELETE(mCloseOperate			);		
		MG_SAFE_DELETE(mAutoJoinGameOperate		);
		MG_SAFE_DELETE(mUseSkillOperate			);
		MG_SAFE_DELETE(mRandMoveOperate			);
		MG_SAFE_DELETE(mNetTestOperate			);
		MG_SAFE_DELETE(mCreateTroopOperate		);
		MG_SAFE_DELETE(mCampaignOperate			);
		MG_SAFE_DELETE(mNetTestLoginOperate		);
		MG_SAFE_DELETE(mConnectLoginOperate		);
		clear();
	}
	//--------------------------------------------------------------------------------
	void OperateManager::update()
	{
		
		if (!mCurrOperate)
		{
			setCurrentOperate();
		}
		
		if (mCurrOperate )
		{
			
			if (!mCurrOperate->isEnter())
			{
				mCurrOperate->onEnter();
			}
			else
			{
				//rand move需要update可以继续添加
				if (mCurrOperate->getType() == OperateType_RandMove)
				{
                         mCurrOperate->update();
				}
			}
			if (mCurrOperate->isFinish())
			{
				mCurrOperate->onLeave();
			}
			
		}
	}
	//--------------------------------------------------------------------------------
	BaseOperate* OperateManager::getCurrentOperate()
	{
		return mCurrOperate;
	}
	//
	BaseOperate* OperateManager::createOperate( OperateType optype)
	{
		if (mIsCreateOperate)
		{
			switch(optype)
			{
			case OperateType_AccountLogin:
				{

					return MG_POOL_NEW(mAccountLoginOperatePool,AccountLoginOperate,(this,mClient,mClient->getClientMessage(),optype));						   
				}
				break;
			case OperateType_CreateClan:
				{
					return MG_POOL_NEW (mCreateClanOperatePool,CreateClanOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_DeleteClan:
				{
					return MG_POOL_NEW (mDeleteClanOperatePool,DeleteClanOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_JoinGame:
				{
					return MG_POOL_NEW (mJoinGameOperatePool,JoinGameOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_Close:
				{
					return MG_POOL_NEW (mCloseOperatePool,CloseOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_AutoJoinGame:
				{
					return MG_POOL_NEW (mAutoJoinGameOperatePool,AutoJoinGameOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_UseSkill:
				{
					return MG_POOL_NEW (mUseSkillOperatePool,UseSkillOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_RandMove:
				{
					return MG_POOL_NEW (mRandMoveOperatePool,RandMoveOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_NetTest:
				{
					return MG_POOL_NEW (mNetTestOperatePool,NetTestOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_CreateTroop:
				{
					return MG_POOL_NEW (mCreateTroopOperatePool,CreateTroopOperate,(this,mClient,mClient->getClientMessage(),optype));
					//return MG_POOL_NEW (mCreateTroopOperatePool,CreateTroopOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_CreateCampaign:
				{
					return MG_POOL_NEW (mCampaignOperatePool,CampaignOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_TestNetLogin:
				{
					return MG_POOL_NEW (mNetTestLoginOperatePool,NetTestLoginOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			case OperateType_connectLogin:
				{
					return MG_POOL_NEW (mConnectLoginOperatePool,ConnectLoginOperate,(this,mClient,mClient->getClientMessage(),optype));
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
					return NULL;
				}
			}
		}
		else
		{
			switch(optype)
			{
			case OperateType_AccountLogin:
				{   
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_AccountLogin])->index;
					return mAccountLoginOperate;						   
				}
				break;
			case OperateType_CreateClan:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_CreateClan])->index;
					return mCreateClanOperate;
				}
				break;
			case OperateType_DeleteClan:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_DeleteClan])->index;
					return mDeleteClanOperate;
				}
				break;
			case OperateType_JoinGame:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_JoinGame])->index;
					return mJoinGameOperate;
				}
				break;
			case OperateType_Close:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_Close])->index;
					return mCloseOperate;
					
				}
				break;
			case OperateType_AutoJoinGame:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_AutoJoinGame])->index;
					return mAutoJoinGameOperate;
					
				}
				break;
			case OperateType_UseSkill:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_UseSkill])->index;
					return mUseSkillOperate;
				}
				break;
			case OperateType_RandMove:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_RandMove])->index;
					U32 lifePeroid = (COperatePage::mOperateModeAttrMap[OperateType_RandMove])->lifePeriod;
					mRandMoveOperate->lifePeroid = lifePeroid;
					return mRandMoveOperate;
				}
				break;
			case OperateType_NetTest:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_NetTest])->index;
					return mNetTestOperate;
				}
				break;
			case OperateType_CreateTroop:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_CreateTroop])->index;
					return mCreateTroopOperate;
				}
			case OperateType_CreateCampaign:
				{
					//COperatePage::mCurrOperateIndex = (COperatePage::mOperateModeAttrMap[OperateType_CreateCampaign])->index;
					return mCampaignOperate;
				}
			case OperateType_TestNetLogin:
				{
					return mNetTestLoginOperate;
				}
				break;
			case OperateType_connectLogin:
				{
					return mConnectLoginOperate;
				}
				break;
			case OperateType_netChat:
				{
                    return mChatOperate;
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
					return NULL;
				}
			}
		}
		
	}
	//--------------------------------------------------------------------------------
	void OperateManager::setCurrentOperate()
	{
		BaseOperate* operate = mCurrOperate;
		OperateType operateType = OperateType_null;
		if (COperatePage::isOperateStart())
		{
            OperateType tempOperateType;
			if (COperatePage::mOperateMode == OperateMode_Order)
			{
                  tempOperateType = COperatePage::getOneOperate(mCurrOperateIndex);
				  mCurrOperateIndex++;
				  if ( mCurrOperateIndex >= COperatePage::mOperates.size())
				  {
					  mCurrOperateIndex = 0;	

				  }

			}
			else if (COperatePage::mOperateMode == OperateMode_Random)
			{
					tempOperateType = COperatePage::getOneOperate();
			}
			
			mCurrOperate = createOperate(tempOperateType);
			mCurrOperate->reset();
		}
		else
		{
			
			if (mOperates.empty())
			{
				mCurrOperate = NULL;
			}
			else
			{
				mCurrOperate = *mOperates.begin();
				mOperates.pop_front();
				mCurrOperate->reset();
			}
			
		}
		if (mIsCreateOperate)
		{
			freeOperate(operate);
		}
		else
		{

		}
		
	}
	//--------------------------------------------------------------------------------
	void OperateManager::pushOperate(BaseOperate* operate)
	{
		mOperates.push_back(operate);
	}
	//--------------------------------------------------------------------------------
	void OperateManager::clear()
	{
		std::list<BaseOperate*>::iterator it = mOperates.begin();

		/*if (mIsCreateOperate)
		{	for (; it != mOperates.end();it++)
			{
				MG_POOL_DELETE(*it);
			}
		}*/
		mOperates.clear();
	}
	//--------------------------------------------------------------------------------
	MG::CClient* OperateManager::getClient()
	{
		return mClient;
	}
	//--------------------------------------------------------------------------------
	void OperateManager::onNetEvent( Byte channel,Byte type,void* data )
	{
		if (mCurrOperate)
		{
			mCurrOperate->onNetEvent(channel,type,data);
		}
	}
	//--------------------------------------------------------------------------------
	void OperateManager::onCloseByLoginServer()
	{
		if (mCurrOperate)
		{
			mCurrOperate->onCloseByLoginServer();
		}
	}
	//--------------------------------------------------------------------------------
	void OperateManager::onCloseByFrontServer()
	{
		if (mCurrOperate)
		{
			mCurrOperate->onCloseByFrontServer();
		}
	}
	//--------------------------------------------------------------------------------
	void OperateManager::freeOperate( BaseOperate* operate )
	{
		//operate->reset();
		if (!mIsCreateOperate)
		{
			return;
		}
		switch(operate->getType())
		{
		case OperateType_AccountLogin:
			{
				AccountLoginOperate* tempOperate = dynamic_cast<AccountLoginOperate*>(operate);
				MG_POOL_DELETE(mAccountLoginOperatePool,tempOperate);						   
			}
			break;
		case OperateType_CreateClan:
			{
				CreateClanOperate* tempOperate = dynamic_cast<CreateClanOperate*>(operate);
				MG_POOL_DELETE(mCreateClanOperatePool,tempOperate);	
			}
			break;
		case OperateType_DeleteClan:
			{
				DeleteClanOperate* tempOperate = dynamic_cast<DeleteClanOperate*>(operate);
				MG_POOL_DELETE(mDeleteClanOperatePool,tempOperate);
			}
			break;
		case OperateType_JoinGame:
			{
				JoinGameOperate* tempOperate = dynamic_cast<JoinGameOperate*>(operate);
				MG_POOL_DELETE(mJoinGameOperatePool,tempOperate);
			}
			break;
		case OperateType_Close:
			{
				CloseOperate* tempOperate = dynamic_cast<CloseOperate*>(operate);
				MG_POOL_DELETE(mCloseOperatePool,tempOperate);
			}
			break;
		case OperateType_AutoJoinGame:
			{
				AutoJoinGameOperate* tempOperate = dynamic_cast<AutoJoinGameOperate*>(operate);
				MG_POOL_DELETE(mAutoJoinGameOperatePool,tempOperate);
			}
			break;
		case OperateType_UseSkill:
			{
				UseSkillOperate* tempOperate = dynamic_cast<UseSkillOperate*>(operate);
				MG_POOL_DELETE(mUseSkillOperatePool,tempOperate);
			}
			break;
		case OperateType_RandMove:
			{
				RandMoveOperate* tempOperate = dynamic_cast<RandMoveOperate*>(operate);
				MG_POOL_DELETE(mRandMoveOperatePool,tempOperate);
			}
			break;
		case OperateType_NetTest:
			{
				NetTestOperate* tempOperate = dynamic_cast<NetTestOperate*>(operate);
				MG_POOL_DELETE(mNetTestOperatePool,tempOperate);
			}
			break;
		case OperateType_CreateTroop:
			{
				CreateTroopOperate* tempOperate = dynamic_cast<CreateTroopOperate*>(operate);
				MG_POOL_DELETE (mCreateTroopOperatePool,tempOperate);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(false);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void OperateManager::setCreateMode( Bool isCreate )
	{
		mIsCreateOperate = isCreate;
	}
	//--------------------------------------------------------------------------------
	MG::Bool OperateManager::getCreateMode()
	{
		return mIsCreateOperate;
	}
	//-----------------------------------------------------------------------------
	CampaignOperate* OperateManager::getcreateCampaignOperateObject()
	{
           return mCampaignOperate;
	}
	//-----------------------------------------------------------------------------
	/*MG::Bool OperateManager::isAllCreatCampaignFinish()
	{
        
	}
	*/
}