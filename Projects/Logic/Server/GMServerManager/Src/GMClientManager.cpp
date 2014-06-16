/******************************************************************************/
#include "stdafx.h"
#include "GMClientManager.h"
#include "GMAccountDB.h"
#include "GMServerManagerMain.h"
#include "GMAccountNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//GMClient服务器管理 
	/******************************************************************************/
	GMClientManager::GMClientManager()
	{

	}
	//----------------------------------------------------------------------------
	GMClientManager::~GMClientManager()
	{
		
	}
	//----------------------------------------------------------------------------
	Bool GMClientManager::initialize()
	{
		DBDriver* dbDrive =  GMServerManagerMain::getInstance().getServerLauncher()->getDBDriver();
		if (!dbDrive)
		{
			return false;
		}
		if (!loadFromDb(dbDrive))
		{   
			return false;
		}
	
		return true;
	}
	//----------------------------------------------------------------------------
	void GMClientManager::uninitialize()
	{
		clearGMDataSet();	
	}
	//----------------------------------------------------------------------------
	Bool GMClientManager::loadFromDb( DBDriver* dbDriver )
	{
		clearGMDataSet();
		GMAccountDBOp::selectGMAccountList(*dbDriver,mGMDataSet);
		if (mGMDataSet.empty())
		{   
			DYNAMIC_ASSERT_LOG(mGMDataSet.empty() == false,"error: 没有管理管帐号!");
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------------------
	void GMClientManager::onGMClientLoginIn(  I32 id, Char16* name,Char16* psw )
	{
		GMClientInfo* gmData = getGMDataByGMName(name);
		if (gmData)
		{
			
			if (WStrnCmp(psw,gmData->password,_countof(gmData->password)))
			{
				GMAccountNetPacketProcesser::getInstance().sendGMClientLoginResult(id,gaor_err_psw,0);
			}
			else
			{
				GMAccountNetPacketProcesser::getInstance().sendGMClientLoginResult(id,gaor_success,gmData->authority);
			}
		}
		else
		{
			GMAccountNetPacketProcesser::getInstance().sendGMClientLoginResult(id,gaor_errname,0);
		}

	}
	//----------------------------------------------------------------------------
	void GMClientManager::onGMClientLoginOut( I32 netId)
	{
		GMClientInfo* gmData = getGMDataByNetId(netId);
		if (gmData)
		{
			gmData->gmId = -1;
			gmData->isOnline = false;
		}
		else
		{
			DYNAMIC_ASSERT_LOG(false,"GM数据出错");
		}
	}
	//----------------------------------------------------------------------------
	GMClientInfo* GMClientManager::getGMDataByNetId( U32 netId )
	{
		std::map<U32,GMClientInfo*>::iterator it = mGMDataSet.begin();
		for (; it != mGMDataSet.end(); it++)
		{
			if (it->second->netId == netId)
			{
				return it->second;
			}
		}
		return NULL;
	}
	//----------------------------------------------------------------------------
	GMClientInfo* GMClientManager::getGMDataByGMName( Char16* name )
	{
		std::map<U32,GMClientInfo*>::iterator it = mGMDataSet.begin();
		for (; it != mGMDataSet.end(); it++)
		{
			if (WStrnCmp(it->second->name,name,_countof(it->second->name)) == 0)
			{
				return it->second;
			}
		}
		return NULL;
	}
	//----------------------------------------------------------------------------
	GMClientInfo* GMClientManager::getGMDataByGMId( U32 gmId )
	{
		std::map<U32,GMClientInfo*>::iterator it = mGMDataSet.find(gmId);
		if (it != mGMDataSet.end())
		{
			return it->second;
		}
	}
	//----------------------------------------------------------------------------
	void GMClientManager::clearGMDataSet()
	{
		std::map<U32,GMClientInfo*>::iterator it = mGMDataSet.begin();
		for (; it != mGMDataSet.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mGMDataSet.clear();
	}
	//----------------------------------------------------------------------------
	void GMClientManager::boardcastNetPacketToGMClient( GameNetSendDataBufferPtr packetPtr ,I32 dataSize )
	{
		std::map<U32,GMClientInfo*>::iterator it = mGMDataSet.begin();
		for (; it != mGMDataSet.end(); it++)
		{
			if (it->second->netId > -1)
			{   
                GMServerManagerMain::getInstance().getServerLauncher()->sendClient(packetPtr,dataSize,it->second->netId);
			}
		}
	}
	//----------------------------------------------------------------------------
	void GMClientManager::processPacket( I32 id,NetEventRecv* packet )
	{
		if (GMAccountNetPacketProcesser::getInstance().processGMClientPacket(id,packet))
		{
			return;
		}
	}
	//----------------------------------------------------------------------------

}
