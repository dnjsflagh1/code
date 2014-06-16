/******************************************************************************/
#include "stdafx.h"
#include "ServerMain.h"
#include "ServerNetApplyManager.h"
#include "NetAddress.h"
#include "SServerSetting.h"
#include "ServerLauncherDlg.h"
#include "NetSocket.h"
#include <mmsystem.h>
#include "Debug_def.h"
#include "MGExternalPackManager.h"
/******************************************************************************/
CServerLauncherDlg* gLauncherDlg = NULL;
namespace MG
{
	/******************************************************************************/
	//StartServerTask
	/******************************************************************************/
	void StartServerTask::free()
	{
		MG_DELETE this;
	}
	
	//-----------------------------------------------------------------------------
	void StartServerTask::process()
	{
		ServerMain::getInstance().startServerInThread();
	}

	/******************************************************************************/
	//StopServerTask
	/******************************************************************************/
	void StopServerTask::free()
	{
		MG_DELETE this;
	}
	
	//-----------------------------------------------------------------------------
	void StopServerTask::process()
	{
		ServerMain::getInstance().stopServerInThread();
	}

	/******************************************************************************/
	//ServerMain
	/******************************************************************************/
  
    ServerMain::ServerMain()
		:mServerInterface(NULL),
        mMySqlDriver(NULL),
		mIsInited(0),
		mIsUpdate(0),
		mHeartBeatSpeed(0),
		mUpdateCount(0),
		mLastTick(0),
		mCostTime(0),
		mTimerId(0)
    {
		mPackManager = MG_NEW GameFilePackManager();
		mExPackManager = MG_NEW MGExternalPackManager(mPackManager);

		//mThreadPool = ThreadPool::createPool(1,1);
		LogSystem::getInstance().setLogLevel(SServerSetting::getInstance().getCoreInfo()->logLevel);
		//InstallMyExceptHandle();
    }

    //-----------------------------------------------------------------------------
    ServerMain::~ServerMain()
    {
		//if ( mThreadPool )
		//{
		//	mThreadPool->destroyPool();
		//}
		stopServerInThread();
		UnInstallMyExceptHandle();

		MG_SAFE_DELETE(mPackManager);
		MG_SAFE_DELETE(mExPackManager);
    }

	//-----------------------------------------------------------------------------
	Bool ServerMain::startServer()
	{
        // 不用线程开启服务器
		//mThreadPool->addTask(MG_NEW StartServerTask);
        startServerInThread();
		return true;
	}

	//-----------------------------------------------------------------------------
	Bool ServerMain::stopServer()
	{
        // 不用线程关闭服务器
		//mThreadPool->addTask(MG_NEW StopServerTask);
        stopServerInThread();
		return true;
	}
	
	//-----------------------------------------------------------------------------
	Bool ServerMain::_startServerInThread()
	{
		//FUNDETECTION(__MG_FUNC__);
		if ( mIsInited == 1)
		{
			MG::MsgBox::show("服务器已经初始化");
			return false;
		}	

		mIsInited = 1;

		if ( loadConfig() == false )
		{
			MG::MsgBox::show("加载配置文件失败");
			return false;
		}

		//if ( loadDB() == false )
		//{
		//	MG::MsgBox::show("加载数据库失败");
		//	return false;
		//}

		if ( loadGameServer() == false )
		{
			MG::MsgBox::show("加载游戏模块失败");
			return false;
		}

		if ( ServerNetApplyManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("加载网络模块失败");
			return false;
		}

		{
			// 加载打包资源库
			//mPackManager->load();
		}

        {
            mHeartBeatSpeed = SServerSetting::getInstance().getCoreInfo()->updateTick;
            if (mHeartBeatSpeed <= 0)
                mHeartBeatSpeed = 1;
            if (mHeartBeatSpeed > 1000)
                mHeartBeatSpeed = 1000;
            mHeartBeatSpeed = (1000 + mHeartBeatSpeed - 1) / mHeartBeatSpeed;
            //timeBeginPeriod(1);
            //不用定时器，由下面独立线程处理服务器包处理逻辑
            //timeBeginPeriod(1);
            //mTimerId = timeSetEvent(mHeartBeatSpeed, 1, updateServerInThread, (DWORD_PTR)this, TIME_PERIODIC|TIME_CALLBACK_FUNCTION);
            mUpdateCount		= 0;
            mCostTime			= 0;
            mLastTick			= MGTimeOp::getCurrTick();
        }

        // 启动处理包线程
        {
            ServerNetApplyManager::getInstance().startThreadAutoHandle();
			//Ptr ptr1;
            mMainThreadHandles.create(updateServerInThread, this, "");
        }

#ifdef _DEBUG
		Thread::SetThreadName(mMainThreadHandles.getThreadId(),"ServerMain::mMainThreadHandles");
#endif // _DEBUG
        // 设置更新标志位
		mIsUpdate = 1;

        // 发送界面消息
		PostMessage(mDialogHwnd,LAUNCH_SERVER_START,(WPARAM)1,NULL);

		return true;
	}

    //-----------------------------------------------------------------------------
    Bool ServerMain::_stopServerInThread()
    {	
        //FUNDETECTION(__MG_FUNC__);
        if ( mIsInited == 1)
        {
            //ServerNetApplyManager::getInstance().endThreadAutoHandle();
            // 关闭服务器主逻辑处理线程
            mMainThreadHandles.destory();

            // 关闭服务器网络应用管理器
            ServerNetApplyManager::getInstance().unInitialize();

            // 设置标志位
            mIsUpdate = 0;

            //关闭定时器//现在不使用定时器,故屏蔽
            //timeKillEvent(mTimerId);
            //timeEndPeriod(1);

            // 卸载服务器
            unLoadGameServer();

            // 卸载数据库
            unLoadDB();

            // 发送界面消息
            PostMessage(mDialogHwnd,LAUNCH_SERVER_START,(WPARAM)0,NULL);
        }

        mIsInited = 0;	
        return true;
    }

	//-----------------------------------------------------------------------------
	void ServerMain::_updateServerInThread(ServerMain* server)
	{
		//FUNDETECTION(__MG_FUNC__);
		if ( server && server->mIsUpdate == 1 )
		{
			if ( ServerNetApplyManager::getInstance().update() == 0 )
				Sleep(5);

			server->mServerInterface->update();

#ifdef _DEBUG
            // 检测服务器状态信息
            server->checkServerInfo();
#endif

		}
		else
		{
			PostMessage(ServerMain::getInstance().getDialogHandle(),LAUNCH_SERVER_START,(WPARAM)0,NULL);
		}
	}

    //-----------------------------------------------------------------------------
    void ServerMain::checkServerInfo()
    {
        if ( mIsUpdate == 1 )
        {
            UInt nowTick = MGTimeOp::getCurrTick();

            UInt deltaTime = nowTick - mLastTick;
            ///mCostTime累计时间差
            mCostTime += deltaTime;
            ///累计时间小于一秒
            if (mCostTime < 1000)
            {
                //Update次数
                mUpdateCount++;
            }
            ///累计时间大于一秒时
            else
            {
                I32 num = 1;
                while ((mCostTime -= 1000) >= 1000){
                    num++;
                }
                //发送相关信息给界面
                static I32 count = 0;
                count++;
                if (count > 5)
                {
                    NetConnectInfo* serverInfo = ServerNetApplyManager::getInstance().getServerNetInfo();
                    NetConnectInfo* clientInfo = ServerNetApplyManager::getInstance().getClientNetInfo();
                    I32 currServerCount = ServerNetApplyManager::getInstance().getCurrConnectionCount(ServerNetApplyManager::getInstance().getServerHandle());
                    I32 currClientCount = ServerNetApplyManager::getInstance().getCurrConnectionCount(ServerNetApplyManager::getInstance().getClientHandle());
                    if (serverInfo && clientInfo)
                    {
                        LuanchUpdateInfo* updateInfo = MG_NEW LuanchUpdateInfo[2];
                        updateInfo[0].recvSpeedBytes = serverInfo->mComingLastRateBytes;
                        updateInfo[0].recvBytes	= serverInfo->mComingBytes;
                        updateInfo[0].recvSpeedPackets = serverInfo->mComingLastRateCounts;
                        updateInfo[0].recvPackets = serverInfo->mComingCounts;

                        updateInfo[0].sendSpeedBytes = serverInfo->mGoingLastRateBytes;
                        updateInfo[0].sendBytes = serverInfo->mGoingBytes;
                        updateInfo[0].sendSpeedPackets = serverInfo->mGoingLastRateCounts;
                        updateInfo[0].sendPackets = serverInfo->mGoingCounts;
                        updateInfo[0].currConnectionCount = currServerCount;

                        updateInfo[1].recvSpeedBytes = clientInfo->mComingLastRateBytes;
                        updateInfo[1].recvBytes	= clientInfo->mComingBytes;
                        updateInfo[1].recvSpeedPackets = clientInfo->mComingLastRateCounts;
                        updateInfo[1].recvPackets = clientInfo->mComingCounts;

                        updateInfo[1].sendSpeedBytes = clientInfo->mGoingLastRateBytes;
                        updateInfo[1].sendBytes = clientInfo->mGoingBytes;
                        updateInfo[1].sendSpeedPackets = clientInfo->mGoingLastRateCounts;
                        updateInfo[1].sendPackets = clientInfo->mGoingCounts;
                        updateInfo[1].currConnectionCount = currClientCount;

                        ::PostMessage(ServerMain::getInstance().getDialogHandle(), LAUNCH_UPDATE,(WPARAM)updateInfo, 2);
                    }
					else if (!clientInfo)
					{
						LuanchUpdateInfo* updateInfo = MG_NEW LuanchUpdateInfo;
						updateInfo[0].recvSpeedBytes = serverInfo->mComingLastRateBytes;
						updateInfo[0].recvBytes	= serverInfo->mComingBytes;
						updateInfo[0].recvSpeedPackets = serverInfo->mComingLastRateCounts;
						updateInfo[0].recvPackets = serverInfo->mComingCounts;

						updateInfo[0].sendSpeedBytes = serverInfo->mGoingLastRateBytes;
						updateInfo[0].sendBytes = serverInfo->mGoingBytes;
						updateInfo[0].sendSpeedPackets = serverInfo->mGoingLastRateCounts;
						updateInfo[0].sendPackets = serverInfo->mGoingCounts;
						updateInfo[0].currConnectionCount = currServerCount;
						::PostMessage(ServerMain::getInstance().getDialogHandle(), LAUNCH_UPDATE,(WPARAM)updateInfo, 1);
					}
                    count = 0;
                }

                //::PostMessage(pCenter->m_hWnd, LUANCH_SERVER_UPDATE, pCenter->m_dwUpdateCount, num);
                mUpdateCount = 1;
            }

            mLastTick = nowTick;
        }
    }

    //-----------------------------------------------------------------------------
    Bool ServerMain::loadConfig()
    {
		//FUNDETECTION(__MG_FUNC__);
		
		//if ( SServerSetting::getInstance().loadFile( getConfigName().c_str()) )
		//{
#ifndef MG_WCHAR_T_STRINGS
			MGStrOp::toString(SServerSetting::getInstance().getCoreInfo()->dllName.c_str(),mDllName);
#else
			mDllName = SServerSetting::getInstance().getCoreInfo()->dllName;
#endif
			LogSystem::getInstance().setEnableConsole(SServerSetting::getInstance().getCoreInfo()->isOpenConsole);
		//}else
		//{
		//	return false;
		//}

        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ServerMain::loadDB()
    {
		//FUNDETECTION(__MG_FUNC__);
        if ( !mMySqlDriver )
        {
			DbConnectInfo* dbConnectInfo = SServerSetting::getInstance().getDbConnectInfo();
			if ( dbConnectInfo )
			{
				mMySqlDriver = MG_NEW MySqlDriver;
				MySqlInitParam param;
#ifndef MG_WCHAR_T_STRINGS 
				MGStrOp::toString(dbConnectInfo->ip.c_str(),param.ip);
				MGStrOp::toString(dbConnectInfo->account.c_str(),param.account);
				MGStrOp::toString(dbConnectInfo->name.c_str(),param.dbName);
				MGStrOp::toString(dbConnectInfo->password.c_str(),param.password);		
#else
				param.ip = dbConnectInfo->ip;
				param.account = dbConnectInfo->account;
				param.dbName = dbConnectInfo->name;
				param.password = dbConnectInfo->password;
#endif
				param.port = dbConnectInfo->port;
				if ( mMySqlDriver->connect(param,"GBK") == false )
				{
					return false;
				}
			}
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    void ServerMain::unLoadDB()
    {
        MG_SAFE_DELETE(mMySqlDriver);
    }

    //-----------------------------------------------------------------------------
    Bool ServerMain::loadGameServer()
    {
		//FUNDETECTION(__MG_FUNC__);
        Bool result = false;
        GET_MGSERVERDLL_INTERFACE_PROC proc; 

        if (mServerDllLoader.load(mDllName.c_str(),false)) 
        { 
            proc = (GET_MGSERVERDLL_INTERFACE_PROC) mServerDllLoader.getProcAddress("GET_MGSERVERDLL_INTERFACE"); 
            if (NULL != proc) 
            {
                mServerInterface = (MG::IServerDllInterface*)proc(); 
                if (mServerInterface==NULL)
                {
                    MG::MsgBox::show("Load IEngineMain Failed!");
                    return 0;
                }
            }else
            {
                MG::MsgBox::show("Don't Find IEngineMain Entry!");
                return 0;
            }
        }else
        {
            MG::MsgBox::show("Don't Load IEngineMain DLL!");
            return 0;
        }

        if ( mServerInterface )
        {
            result = mServerInterface->initialize(this);
        }

        return result;
    }

    //-----------------------------------------------------------------------------
    Bool ServerMain::unLoadGameServer()
    {
		//FUNDETECTION(__MG_FUNC__);
        Bool result = false;

        if ( mServerInterface )
        {
            result = mServerInterface->unInitialize();
        }
        
        mServerDllLoader.unload();
        return result;
    }

    //-----------------------------------------------------------------------------
    void ServerMain::getClientSendDataBuffer(GameNetSendDataBufferPtr& ptr, U32 buffSize)
    {
       // FUNDETECTION(__MG_FUNC__);
        I32 handle = ServerNetApplyManager::getInstance().getClientHandle();
        ServerNetApplyManager::getInstance().getGameNetSendDataBufferPtr(ptr,handle,buffSize);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::setClientNetCode(I32 id,U64 code)
    {
        ServerNetApplyManager::getInstance().setCode(ServerNetApplyManager::getInstance().getClientHandle(),id,code);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::getServerSendDataBuffer(GameNetSendDataBufferPtr& ptr, U32 buffSize)
    {
       // FUNDETECTION(__MG_FUNC__);
        I32 handle = ServerNetApplyManager::getInstance().getServerHandle();
        ServerNetApplyManager::getInstance().getGameNetSendDataBufferPtr(ptr,handle,buffSize);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader)
    {
        ServerNetApplyManager::getInstance().cloneSendDataBuffer(srcPtr,desPtr,isCopyHeader);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize)
    {
        ServerNetApplyManager::getInstance().cloneSendDataBuffer(srcPtr,desPtr,cloneSize);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::setServerNetCode(I32 id,U64 code)
    {
        ServerNetApplyManager::getInstance().setCode(ServerNetApplyManager::getInstance().getServerHandle(),id,code);
    }


    //-----------------------------------------------------------------------------
    void ServerMain::sendClient( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id )
    {
        I32 handle = ServerNetApplyManager::getInstance().getClientHandle();
        ServerNetApplyManager::getInstance().prepareSend(ptr,handle,id,sendSize);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::sendServer( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id )
    {
        I32 handle = ServerNetApplyManager::getInstance().getServerHandle();
        ServerNetApplyManager::getInstance().prepareSend(ptr,handle,id,sendSize);
    }

    //-----------------------------------------------------------------------------
    void ServerMain::closeAllClient()
    {
        
    }

	//-----------------------------------------------------------------------------
	void ServerMain::closeClient( I32 id )
	{
		ServerNetApplyManager::getInstance().closeClient(id);
	}

	//-----------------------------------------------------------------------------
	void ServerMain::closeServer(I32 id)
	{
		ServerNetApplyManager::getInstance().closeClient(id);
	}

    //-----------------------------------------------------------------------------
	U64 ServerMain::getClientUid( I32 id )
	{
		return ServerNetApplyManager::getInstance().getClientUid(id);
	}
	//-----------------------------------------------------------------------------
	void ServerMain::setDialogHandle( HWND handle )
	{
		mDialogHwnd = handle;
	}
	//-----------------------------------------------------------------------------
	HWND ServerMain::getDialogHandle()
	{
		return mDialogHwnd;
	}
	//-----------------------------------------------------------------------------
	void ServerMain::writeDBLog( CChar* msg )//需要换成异步方式
	{
		//FUNDETECTION(__MG_FUNC__);
		Str16 wstr;
		if (gLauncherDlg)
		{
			MGStrOp::toString(msg,wstr);
			Char16* buf = new Char16[wstr.size()];
			buf[wstr.size() - 1] = 0;
			WStrnCpyS(buf,wstr.size(),wstr.c_str(),wstr.size() - 1);
			::PostMessage(ServerMain::getInstance().getDialogHandle(), LAUNCH_WRITE_DB_LOG,(WPARAM)buf, NULL);
		}
	}
	//-----------------------------------------------------------------------------
	void ServerMain::writeCoreLog( CChar* msg )
	{
		//FUNDETECTION(__MG_FUNC__);
		Str16 wstr;
		if (gLauncherDlg)
		{
			MGStrOp::toString(msg,wstr);
			Char16* buf = new Char16[wstr.size()];
			buf[wstr.size() - 1] = 0;
			WStrnCpyS(buf,wstr.size(),wstr.c_str(),wstr.size() - 1);
			::PostMessage(ServerMain::getInstance().getDialogHandle(), LAUNCH_WRITE_CORE_LOG,(WPARAM)buf, NULL);
		}
	}
	//-----------------------------------------------------------------------------
	void ServerMain::writeShellLog( CChar* msg )
	{
		//FUNDETECTION(__MG_FUNC__);
		Str16 wstr;
		if (gLauncherDlg)
		{
			MGStrOp::toString(msg,wstr);
			Char16* buf = new Char16[wstr.size()];
			buf[wstr.size() - 1] = 0;
			WStrnCpyS(buf,wstr.size(),wstr.c_str(),wstr.size() - 1);
			::PostMessage(ServerMain::getInstance().getDialogHandle(), LAUNCH_WRITE_SHELL_LOG,(WPARAM)buf, NULL);
		}
	}
	//-----------------------------------------------------------------------------
	U64 ServerMain::getUniqueFlag()
	{
		return ServerNetApplyManager::getInstance().getUniqueFlag();
	}
	//-----------------------------------------------------------------------------
	Bool ServerMain::startServerInThread()
	{
		Bool tempRet = false;
		//MG_EXCEPTION_BEGIN
		tempRet =  _startServerInThread();
		//MG_EXCEPTION_END("ServerMain-startServerInThread");
		return tempRet;
	}
	//-----------------------------------------------------------------------------
	void ServerMain::updateServerInThread( Ptr ptr )
	{
		//MG_EXCEPTION_BEGIN
        OneThreadHandle* thd = (OneThreadHandle* )ptr;
        if ( thd )
        {
            ServerMain* server = &(ServerMain::getInstance());
            while( thd->isRun())
            {
                ServerMain::_updateServerInThread(server);
            }
        }
		//MG_EXCEPTION_END("ServerMain-updateServerInThread");
	}
	//-----------------------------------------------------------------------------
	Bool ServerMain::stopServerInThread()
	{
		//MG_EXCEPTION_BEGIN
		return _stopServerInThread();
		//MG_EXCEPTION_END("ServerMain-stopServerInThread");
		return false;
	}
	//-----------------------------------------------------------------------------
	void ServerMain::setSettingPathName( Char16* name )
	{
		mSettingPathName = name;
	}
	//-----------------------------------------------------------------------------
	MG::Str16 ServerMain::getSettingPathName()
	{
		return mSettingPathName;
	}
	//-----------------------------------------------------------------------------
	Bool ServerMain::isNetAvailable()
	{
		if (mIsUpdate == 1)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ServerMain::addServer( U32 serverId, I32 netId)
	{
		std::map< U32, std::vector< I32 > >::iterator it = mServerIdMap.find(serverId);
		if (it != mServerIdMap.end())
		{
			if (it->second.empty())
			{
				DYNAMIC_ASSERT(false);
			}
			DYNAMIC_ASSERT(false);
			it->second.push_back(netId);
			return false;
		}
		std::vector< I32 > temp;
		temp.push_back(netId);
		mServerIdMap[serverId] = temp;
		return true;
	}

	//-----------------------------------------------------------------------------
	void ServerMain::removeServerById( U32 serverId )
	{
		std::map< U32, std::vector< I32 > >	::iterator it = mServerIdMap.find(serverId);
		if (it != mServerIdMap.end())
		{
			mServerIdMap.erase(it);
		}
	}

	//-----------------------------------------------------------------------------
	void ServerMain::removeServerByNetId( I32 netId )
	{
		std::map< U32, std::vector< I32 > >	::iterator it = mServerIdMap.begin();
		for (; it != mServerIdMap.end(); it++)
		{
			if (it->second.empty())
			{
				DYNAMIC_ASSERT(false);
				mServerIdMap.erase(it);
			}
			std::vector< I32 >::iterator netIdit = it->second.begin();
			for (; netIdit != it->second.end(); netIdit++)
			{
				if (netId == *netIdit)
				{
					if (it->second.size() == 1)
					{
						mServerIdMap.erase(it);
					}
					else
					{
						it->second.erase(netIdit);
					}
					return;
				}
			}
		}
	}

	//-----------------------------------------------------------------------------
	U32 ServerMain::getServerIdByNetId( I32 netId )
	{
		U32 serverId = 0;
		if (netId <= -1)
		{
			return serverId;
		}
		std::map< U32, std::vector< I32 > >	::iterator it = mServerIdMap.begin();
		for (; it != mServerIdMap.end(); it++)
		{
			if (it->second.empty())
			{
				continue;
			}
			std::vector< I32 >::iterator netIdit = it->second.begin();
			for (; netIdit != it->second.end(); netIdit++)
			{
				if (netId == *netIdit)
				{
					serverId = it->first;
					return serverId;
				}
			}
		}
		return serverId;
	}

	//-----------------------------------------------------------------------------
	I32 ServerMain::getNetIdByServerId( U32 serverId )
	{
		U32 serverNetId = -1;
		std::map< U32, std::vector< I32 > >::iterator it = mServerIdMap.find(serverId);
		if (it != mServerIdMap.end())
		{
			if (it->second.empty())
			{
				return serverId;
			}
			std::vector< I32 >::iterator netIdit = it->second.begin();
			for (; netIdit != it->second.end(); netIdit++)
			{
				if (*netIdit != -1)
				{
					return *netIdit;
				}
			}
		}
		return serverId;
	}

	//-----------------------------------------------------------------------------
	void ServerMain::freeEvent(INetEvent* netEvent)
	{
		ServerNetApplyManager::getInstance().freeEvent(netEvent);
	}
	//-----------------------------------------------------------------------------
	MG::Str16 ServerMain::getConfigKeyName()
	{
         return mConfigKeyName;
	}
	//-----------------------------------------------------------------------------
	void ServerMain::setConfigKeyName( Char16* name )
	{
           mConfigKeyName = name;
	}
}


