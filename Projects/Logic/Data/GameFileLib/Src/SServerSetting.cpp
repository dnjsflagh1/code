//*************************************************************************************************//
#include "stdafx.h"
#include "SServerSetting.h"
#include "Ini.h"
//*************************************************************************************************//

namespace MG
{

	//--------------------------------------------------------------------------
	SServerSetting::SServerSetting()
		:mDb(NULL),
		mClientListen(NULL),
		mServerListen(NULL),
		mConnectServers(NULL),
		mAllowedServerIps(NULL),
		mLinstenSendToClient(NULL)
	{
		mCore = MG_NEW CoreInfo;
		DYNAMIC_ASSERT(mCore);
	}
	//--------------------------------------------------------------------------
	SServerSetting::~SServerSetting()
	{
		unloadFile();
		MG_SAFE_DELETE(mCore);
		MG_SAFE_DELETE(mDb);
		MG_SAFE_DELETE(mClientListen);
		MG_SAFE_DELETE(mServerListen);
		MG_SAFE_DELETE(mConnectServers);
		MG_SAFE_DELETE(mAllowedServerIps);
	}
	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool SServerSetting::loadFile(std::wstring fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		unloadFile();
		DYNAMIC_ASSERT(fileName.length() > 4);
		UINI ini;
		// MG_CN_MODIFY
		if (ini.create(fileName, packManager))
		{
			//CoreInfo
			ini.setGroup(L"Core");
			Int subGroupCount = ini.getSubGroupCount(L"Core");
			DYNAMIC_ASSERT(subGroupCount == 12);
			mCore->name = ini.getValue(L"Name", L"");
			MGStrOp::toI32(ini.getValue(L"ID", L"").c_str(),mCore->id);
			MGStrOp::toI32(ini.getValue(L"Type", L"").c_str(),mCore->type);

			mCore->dllName = ini.getValue(L"DllFileName", L"");
#ifdef _DEBUG	
			mCore->dllName += L"_d.dll";
#else
			mCore->dllName += L".dll";
#endif
			
			MGStrOp::toI32(ini.getValue(L"UpdateTick", L"").c_str(),mCore->updateTick);
			MGStrOp::toI32(ini.getValue(L"CloseTime", L"").c_str(),mCore->closeTime);
			Int isWriteLog = 0;
			MGStrOp::toI32(ini.getValue(L"CoreLog", L"").c_str(),isWriteLog);
			mCore->isWriteCoreLog = isWriteLog > 0 ? true : false;
			MGStrOp::toI32(ini.getValue(L"DbLog", L"").c_str(),isWriteLog);
			mCore->isWriteDbLog = isWriteLog > 0 ? true : false;
			MGStrOp::toI32(ini.getValue(L"ShellLog", L"").c_str(),isWriteLog);
			mCore->isWriteShellLog = isWriteLog > 0 ? true : false;

			MGStrOp::toI32(ini.getValue(L"AutoStart", L"").c_str(),isWriteLog);
			mCore->isAutoStart = isWriteLog > 0 ? true : false;

			MGStrOp::toI32(ini.getValue(L"LogLevel", L"").c_str(),mCore->logLevel);

			MGStrOp::toI32(ini.getValue(L"IsOpenConsole", L"").c_str(),isWriteLog);
			mCore->isOpenConsole = isWriteLog > 0 ? true : false;
			
		
			//DB
			if ( ini.hasGroup(L"DB") )
			{
				if ( mDb == NULL )
					mDb = MG_NEW DbConnectInfo;

				ini.setGroup(L"DB");
				subGroupCount = ini.getSubGroupCount(L"DB");
				DYNAMIC_ASSERT(subGroupCount == 6);
				mDb->ip = ini.getValue(L"IP", L"");
				MGStrOp::toI32(ini.getValue(L"Port", L"").c_str(),mDb->port);
				mDb->name = ini.getValue(L"Name", L"");
				mDb->account = ini.getValue(L"Account", L"");
				mDb->password = ini.getValue(L"Password", L"");
				Int isCreate = 0;
				MGStrOp::toI32(ini.getValue(L"IsCreate", L"").c_str(),isCreate);
				mDb->isCreate = isCreate > 0 ? true : false;
			}

			Int port = 0;
			ConnectRemoteInfo* connection = NULL;
			Char16 temp[64] = {0};
			std::wstring tempIpW;
			std::string tempIpA;

			//ClientListen
			if ( ini.hasGroup(L"ClientLisiten") )
			{
				if ( mClientListen==NULL )
					mClientListen = MG_NEW ClientListenInfo;

				ini.setGroup(L"ClientLisiten");
				subGroupCount = ini.getSubGroupCount(L"ClientLisiten");
				DYNAMIC_ASSERT(subGroupCount == 4);
				MGStrOp::toI32( ini.getValue(L"MaxConnect", L"").c_str(),mClientListen->maxConnects);
				MGStrOp::toI32( ini.getValue(L"Port", L"").c_str(),port);
				MGStrOp::toString(ini.getValue(L"Ip", L"").c_str(),tempIpA);
				mClientListen->addr = NetAddress(tempIpA.c_str(),port);
				Int isEncrypt = 0;
				MGStrOp::toI32(ini.getValue(L"Encrypt", L"").c_str(),isEncrypt);
				mClientListen->isEncrypted = isEncrypt > 0 ? true : false;
			}
			//ListenSendToClient
			if ( ini.hasGroup(L"ListenSendToClient") )
			{
				if ( mLinstenSendToClient == NULL )
					mLinstenSendToClient = MG_NEW ListenInfoSendToClient;

				ini.setGroup(L"ListenSendToClient");
				subGroupCount = ini.getSubGroupCount(L"ListenSendToClient");
				DYNAMIC_ASSERT(subGroupCount == 2);
				MGStrOp::toString(ini.getValue(L"Ip", L"").c_str(),tempIpA);
				MGStrOp::toI32( ini.getValue(L"Port", L"").c_str(),port);
				mLinstenSendToClient->addr = NetAddress(tempIpA.c_str(),port);
			}

			//ServerListen
			if ( ini.hasGroup(L"ServerLisiten") )
			{
				if ( mServerListen==NULL )
					mServerListen = MG_NEW ServerListenInfo;

				ini.setGroup(L"ServerLisiten");
				subGroupCount = ini.getSubGroupCount(L"ServerLisiten");
				DYNAMIC_ASSERT(subGroupCount == 4);
				MGStrOp::toI32( ini.getValue(L"MaxConnect", L"").c_str(),mServerListen->maxConnects);
				MGStrOp::toI32( ini.getValue(L"Port", L"").c_str(),port);
				MGStrOp::toString(ini.getValue(L"Ip", L"").c_str(),tempIpA);
				mServerListen->addr = NetAddress(tempIpA.c_str(),port);	
				Int isEncrypt = 0;
				MGStrOp::toI32(ini.getValue(L"Encrypt", L"").c_str(),isEncrypt);
				mServerListen->isEncrypted = isEncrypt > 0 ? true : false;
			}


			//ListenServerS
			if ( ini.hasGroup(L"AllowedServerIpList") )
			{
				if ( mAllowedServerIps == NULL )
					mAllowedServerIps = MG_NEW AllowedServerIpCollection;
				DYNAMIC_ASSERT(mAllowedServerIps);
				ini.setGroup(L"AllowedServerIpList");
				I32 isValid = 0;
				MGStrOp::toI32( ini.getValue(L"IsValid", L"").c_str(),isValid);
				mAllowedServerIps->isValid = isValid > 0 ? true : false;
				I32 count = 0;
				MGStrOp::toI32( ini.getValue(L"Count", L"").c_str(),count);

				for (int i = 0; i < count; i++)
				{
					MGStrOp::sprintf(temp,64,L"LisitenIP_%d",i);
					Str16 ip = ini.getValue(temp, L"");
					mAllowedServerIps->allowedIps.push_back(ip);
				}
			}
			
			//ConnectServerS
			if ( ini.hasGroup(L"ConnectServerList") )
			{
				if ( mConnectServers == NULL )
					mConnectServers = MG_NEW ConnectServerCollection;
				DYNAMIC_ASSERT(mConnectServers);
				ini.setGroup(L"ConnectServerList");
				MGStrOp::toI32( ini.getValue(L"Count", L"").c_str(),mConnectServers->maxConnects);
				for (int i = 0; i < mConnectServers->maxConnects; i++)
				{
					connection = new ConnectRemoteInfo;
					DYNAMIC_ASSERT(connection);

					MGStrOp::sprintf(temp,64,L"Name_%d",i);
					connection->name = ini.getValue(temp, L"");

					MGStrOp::sprintf(temp,64,L"Type_%d",i);
					MGStrOp::toI32(ini.getValue(temp, L"").c_str(),connection->type);

					MGStrOp::sprintf(temp,64,L"Port_%d",i);
					MGStrOp::toI32(ini.getValue(temp, L"").c_str(),port);

					MGStrOp::sprintf(temp,64,L"IP_%d",i);
					MGStrOp::toString(ini.getValue(temp, L"").c_str(),tempIpA);
					connection->addr = NetAddress(tempIpA.c_str(),port);

					mConnectServers->connectServers.insert(std::make_pair(connection->addr.getUin(),connection));
				}
			}
			
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	void SServerSetting::unloadFile()
	{
		
	}
	//--------------------------------------------------------------------------
	Bool SServerSetting::isClientLisiten()
	{
		if (mClientListen)
		{
			return mClientListen->maxConnects > 0;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	Bool SServerSetting::isServerLisiten()
	{
		if (mServerListen)
		{
			return mServerListen->maxConnects > 0;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	CoreInfo* SServerSetting::getCoreInfo() const
	{
		return mCore;
	}
	//--------------------------------------------------------------------------
	DbConnectInfo* SServerSetting::getDbConnectInfo() const
	{
		return mDb;
	}
	//--------------------------------------------------------------------------
	ClientListenInfo* SServerSetting::getClientListenInfo() const
	{
		return mClientListen;
	}
	//--------------------------------------------------------------------------
	ServerListenInfo* SServerSetting::getServerListenInfo() const
	{
		return mServerListen;
	}
	//--------------------------------------------------------------------------
	ConnectServerCollection* SServerSetting::getConnectServers() const
	{	
		return mConnectServers;
	}
	//--------------------------------------------------------------------------
	AllowedServerIpCollection* SServerSetting::getAllowedServerIpCollection() const
	{
		return mAllowedServerIps;
	}

	ListenInfoSendToClient*		SServerSetting::getListenInfoSendToClient()const
	{
		return mLinstenSendToClient;
	}
	//--------------------------------------------------------------------------
}

//*************************************************************************************************//