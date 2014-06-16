/******************************************************************************/
#include "stdafx.h"
#include "ClientManager.h"
#include "CClient.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "SkillInfoList.h"
#include "ClientNetApplyManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	ClientManager::ClientManager()
	:mInited(false)
	,mLastTick(0)
	{
	}
	//-----------------------------------------------------------------------------
	ClientManager::~ClientManager()
	{

	}
	//-----------------------------------------------------------------------------
	void ClientManager::closeAll()
	{
		//关闭所有链接
	}
	//-----------------------------------------------------------------------------
	CClient* ClientManager::createOrRetrieve( I32 index, Char* service,Char16* accountName,Char16* password,I32 nClan )
	{
		return NULL;//mClients.createOrRetrieve<I32,Char*,Char16*,Char16*,I32>( index,index,service,accountName,password,nClan );
	}
	//-----------------------------------------------------------------------------
	void ClientManager::update(Flt delta)
	{
		
		//lockClients();
		std::map<I32,CClient*>* dataMap = mClients.getDataSet();
		if (!dataMap || dataMap->empty())
		{
			//unLockClients();
			return;
		}
		for (std::map<I32,CClient*>::iterator it = dataMap->begin(); it != dataMap->end(); it++)
		{
			CClient* client = it->second;
			if (client)
			{
				client->update(delta);
			}
			static U64 currTick = 0;
			currTick = MGTimeOp::getCurrTick();
			if (currTick - mLastTick > 1000)
			{
				ClientNetApplyManager::getInstance().update();
				mLastTick = currTick;
			}
		
		}
		//unLockClients();
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClientManager::initialize()
	{
		if ( ShortRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType003List.csv") == false )
			return false;
		if ( LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType004List.csv") == false )
			return false;
		if ( SingleTargetSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType005List.csv") == false )
			return false;
		if ( PassivenessSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType002List.csv") == false )
			return false;
		if ( SingleEmitterSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType006List.csv") == false )
			return false;
		if ( SelfAreaSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType007List.csv") == false )
			return false;
		if ( TargetPosAreaSkillTemplate::getInstance().load(L"Config\\Skill\\SkillType008List.csv") == false )
			return false;
		if ( SkillInfoList::getInstance().load(L"Config\\Skill\\SkillList.csv") == false )
			return false;
		mInited = true;
		return true;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClientManager::isInit()
	{
		return mInited;
	}
	//-----------------------------------------------------------------------------
	CClient* ClientManager::getClientbyLoginServerId( I32 netId )
	{
		CClient* client = NULL;
		std::map<loginNetId,CClient*>::iterator it = mClientLoginMap.find(netId);
		if (it != mClientLoginMap.end())
		{
			client = it->second;
		}
		return client;
	}
	//-----------------------------------------------------------------------------
	CClient* ClientManager::getClientbyFrontServerId( I32 netId )
	{
		CClient* client = NULL;
		std::map<loginNetId,CClient*>::iterator it = mClientFrontMap.find(netId);
		if (it != mClientFrontMap.end())
		{
			client = it->second;
		}
		return client;
		
	}
	//-----------------------------------------------------------------------------
	map<I32,CClient*>* ClientManager::getDataSet()
	{
		return mClients.getDataSet();
	}
	//-----------------------------------------------------------------------------
	SimpleMapDataSetManager<I32, CClient>* ClientManager::getClients()
	{
		return &mClients;
	}
	map<I32,CClient*>*				ClientManager::getFrontClients()
	{
		return &mClientFrontMap;
	}
	//-----------------------------------------------------------------------------
	void ClientManager::lockClients()
	{
		mClientsLock.lock();
	}
	//-----------------------------------------------------------------------------
	void ClientManager::unLockClients()
	{
		mClientsLock.unlock();
	}
	//-----------------------------------------------------------------------------
	void ClientManager::pushOperate( OperateType optype )
	{
		lockClients();
		
		std::map<I32,CClient*>* dataMap = mClients.getDataSet();
		for (std::map<I32,CClient*>::iterator it = dataMap->begin(); it != dataMap->end(); it++)
		{
			CClient* client = it->second;
			OperateManager* opMgr = client->getOperateManager();
			if (client && opMgr)
			{
				opMgr->pushOperate(opMgr->createOperate(optype));
			}
		}
		unLockClients();
	}
	//-----------------------------------------------------------------------------
	void ClientManager::addClientToLoginMap( loginNetId netId,CClient* client )
	{
		mClientLoginMap[netId] = client;
	}
	//-----------------------------------------------------------------------------
	void ClientManager::addClientToFrontMap( frontNetId netId,CClient* client )
	{
		mClientFrontMap[netId] = client;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClientManager::removeClientFormLoginMap( loginNetId netId )
	{
		std::map<loginNetId,CClient*>::iterator it = mClientLoginMap.find(netId);
		if (it != mClientLoginMap.end())
		{
			mClientLoginMap.erase(it);
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClientManager::removeClientFormFrontMap( frontNetId netId )
	{
		std::map<frontNetId,CClient*>::iterator it = mClientFrontMap.find(netId);
		if (it != mClientFrontMap.end())
		{
			mClientFrontMap.erase(it);
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClientManager::isAllCreatCampaignFinish()
	{	
		Bool flag = true;
		std::map<I32,CClient*>* dataMap = mClients.getDataSet();
		for (std::map<I32,CClient*>::iterator it = dataMap->begin(); it != dataMap->end(); it++)
		{
			CClient* client = it->second;
			if (!client->getCampaign())
			{
				continue;
			}
            if (!client->getOperateManager()->getcreateCampaignOperateObject()->isFinish())
            {
                  flag = false;
            }
			
		}

		return flag;

	}
}