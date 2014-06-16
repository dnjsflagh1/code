//***********************************************************************************************************
#include "stdafx.h"
#include "UIOperateSystem.h"
#include "UIOperateManager.h"
#include "CClientNew.h"
#include "ThreadTaskManager.h"
//***********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------------------
	void UiOperateSystem::setOperateMode( UIOperateMode mode )
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->setOperateMode(mode);
			}
		}

	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addAutoJoinGameOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addAutoJoinGameOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addAccountLoginOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addAccountLoginOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addConnectLsOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addConnectLsOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addSendDataToLsOp(U32 size,U32 intervalTick,U32 lifeCycle)
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addSendDataToLsOp(size,intervalTick,lifeCycle);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addLoginLsOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addLoginLsOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addConnectFsOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addConnectFsOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addSendDataToFsOp(U32 size,U32 intervalTick,U32 lifeCycle)
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addSendDataToFsOp(size,intervalTick,lifeCycle);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addLoginFsOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addLoginFsOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addJoinGameOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addJoinGameOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addCreateClanOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addCreateClanOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addCreateCharacterOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addCreateCharacterOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addRandMoveOp(U32 intervalTick,U32 lifeCycle)
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addRandMoveOp(intervalTick,lifeCycle);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addCreateTroopOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addCreateTroopOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addTestSkillOp(U32 intervalTick,U32 lifeCycle)
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addTestSkillOp(intervalTick,lifeCycle);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addJumpMapOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addJumpMapOp();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UiOperateSystem::addCloseNetOp()
	{
		std::map<I32,CClient*>* clients = ThreadTaskManager::getInstance().getClientMap();
		int count = 0;
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			UiOperateManager* operateMgr = it->second->getUiOperateManger();
			if (operateMgr)
			{
				operateMgr->addCloseNetOp();
				count++;
			}
		}

	}
}
//***********************************************************************************************************