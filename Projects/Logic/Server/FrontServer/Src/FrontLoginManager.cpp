/******************************************************************************/
#include "stdafx.h"
#include "FrontLoginNetPacketProcesser.h"
#include "FrontLoginManager.h"
#include "SServerSetting.h"
#include "FrontServerMain.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	FrontLoginManager::FrontLoginManager()
	{

	}

	//-----------------------------------------------------------------------
	FrontLoginManager::~FrontLoginManager()
	{
		uninitialize();
	}

	//-----------------------------------------------------------------------
	Bool FrontLoginManager::initialize(SServerSetting* setting)
	{
		PT_ACC_F2L_LOGIN_DATA data;
		std::string str;
		MGStrOp::sprintf(data.ip,sizeof(data.ip),setting->mClientListen->addr.getIPStr());
		MGStrOp::toString(setting->mCore->name.c_str(),str);
		MGStrOp::sprintf(data.name,sizeof(data.name),str.c_str());
		FrontServerMain::getInstance().getServerLauncher()->sendServerPacket(0,GNPC_ACCOUNT,PT_ACC_F2L_LOGIN,(Char*)(&data),sizeof(data));
		return true;
	}

	//-----------------------------------------------------------------------
	void FrontLoginManager::uninitialize()
	{



	}
	//-----------------------------------------------------------------------
	void FrontLoginManager::handleLoginThread( Ptr ptr )
	{

	}


}
