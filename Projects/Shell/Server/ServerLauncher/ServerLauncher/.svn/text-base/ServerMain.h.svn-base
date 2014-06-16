/******************************************************************************/
#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_
/******************************************************************************/

#include "Singleton.h"
#include "ServerDllInterface.h"
#include "Task.h"
#include "ServerLauncher.h"
#include "GameFilePackManager.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//服务器任务
	/******************************************************************************/
	class StartServerTask : public Task
	{
		virtual	void	free();
		virtual	void	process();
	};

	class StopServerTask : public Task
	{
		virtual	void	free();
		virtual	void	process();
	};
	
    /******************************************************************************/
    //服务器管理
    /******************************************************************************/
    class ServerMain : public ServerLauncherInterface
    {
    public:
        SINGLETON_INSTANCE(ServerMain);
        ServerMain();
        virtual ~ServerMain();

		/// 启动服务器
		Bool			                    startServer();
		/// 关闭服务器
		Bool                                stopServer();

	public:	
        /// 线程启动服务器
        Bool                                startServerInThread();
        /// 线程运行服务器
        static void		                    updateServerInThread(Ptr ptr);
        /// 线程关闭服务器
        Bool                                stopServerInThread();
	private:

        /// 启动服务器
		Bool					            _startServerInThread();
        /// 停止服务器
		Bool					            _stopServerInThread();
        // 更新服务器
		static void				            _updateServerInThread(ServerMain* server);

        //---------------------------------------------------------------------------------------------------------------

    protected:

        // 检查服务器信息
                void                        checkServerInfo();
	public:

        //---------------------------------------------------------------------------------------------------------------

        IServerDllInterface*                getServerDllInterface(){return mServerInterface;};
    
        virtual SServerSetting*             getServerSetting(){return &SServerSetting::getInstance();};
        virtual DBDriver*                   getDBDriver(){return mMySqlDriver;};
		virtual	U64				            getClientUid( I32 id );
		virtual IMGExternalPackManager*     getMGExternalPackManager(){return mExPackManager;};

        //---------------------------------------------------------------------------------------------------------------

        virtual void                        closeAllClient();
		virtual void                        closeClient(I32 id);
		virtual void                        closeServer(I32 id);

		virtual void					    freeEvent(INetEvent* netEvent);

        //---------------------------------------------------------------------------------------------------------------

        virtual void                        getClientSendDataBuffer( GameNetSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
        virtual void                        getServerSendDataBuffer( GameNetSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
        virtual void                        cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader) ;
        virtual void                        cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize) ;
        virtual void                        sendClient( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id );
        virtual void                        sendServer( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id );
        virtual void                        setClientNetCode(I32 id,U64 code);
        virtual void                        setServerNetCode(I32 id,U64 code);

        //---------------------------------------------------------------------------------------------------------------

		virtual void                        setDialogHandle(HWND handle);
		virtual HWND                        getDialogHandle();
		virtual	U64				            getUniqueFlag();


        virtual void                        writeDBLog(CChar* msg);
        virtual void                        writeCoreLog(CChar* msg);
        virtual void                        writeShellLog(CChar* msg);

        //---------------------------------------------------------------------------------------------------------------

		virtual	Bool					    isNetAvailable();

		virtual	Str16					    getSettingPathName();
		virtual	void					    setSettingPathName(Char16* name);

		virtual	Str16					    getConfigKeyName();
		virtual	void					    setConfigKeyName(Char16* name);

        //---------------------------------------------------------------------------------------------------------------

		///	当服务器连接登录 添加服务器
		Bool	                            addServer(U32 serverId,I32 netId);
		/// 移除服务器
		void	                            removeServerById(U32 serverId);
		void	                            removeServerByNetId(I32 netId);
		///获取服务器ID
		virtual	U32						    getServerIdByNetId(I32 netId);
		virtual	I32						    getNetIdByServerId(U32 serverId);

    protected:

        /// 读取配置文件
        Bool    loadConfig();

        /// 加载数据库
        Bool    loadDB();
        /// 卸载数据库
        void    unLoadDB();

        /// 加载服务器
        Bool    loadGameServer();
        /// 卸载服务器
        Bool    unLoadGameServer();
		
    private:
		
		/// 资源打包接口指针
		GameFilePackManager*	mPackManager;
		IMGExternalPackManager* mExPackManager;

		/// 是否已经初始化
		InterLocked             mIsInited;
		InterLocked             mIsUpdate;

		/// 加载服务器的Dll名字
        Str                     mDllName;
        /// 游戏引擎接口指针
        IServerDllInterface*    mServerInterface;
        /// 游戏引擎DLL加载器
        DllLoader               mServerDllLoader;

		/// MySql管理对象
        MySqlDriver*	        mMySqlDriver;

		/// 线程池
		ThreadPool*             mThreadPool;

        /// 处理数据包线程
        OneThreadHandle         mMainThreadHandles;

		/// 心跳频率
		I32	                    mHeartBeatSpeed;

		/// 定时器的id
		Int                     mTimerId;

		///一个周期（在计算一秒更新次数时实际花去的时间）更新的次数
		Int                     mUpdateCount;

		///一个周期（在计算一秒更新次数时实际花去的时间）update实际花去的时间
		U32                     mCostTime;

		///最近一次更新的tick
		U32                     mLastTick;
		
		HWND                    mDialogHwnd;

		Str16					mSettingPathName;
		Str16					mConfigKeyName;
		/*  
			<serverId, netId>
			目的： 避免相同编号的服务器同时登录
		*/
		std::map< U32, std::vector< I32 > >			mServerIdMap;
    };

}

/******************************************************************************/

#endif