/******************************************************************************/
#ifndef _GAMENETPACKETMANAGER_H_
#define _GAMENETPACKETMANAGER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetPacket.h"
#include "NetManager.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"
#include "GameNetPacketFilter.h"
#include "GameNetDriverManager.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏包管理
    /******************************************************************************/
    class GameNetPacketManager : public NetManager
    {
        friend class Net2LogicEventFromOneConnectHandler;
        friend class Logic2NetEventFromOneConnectHandler;
    public:
        GameNetPacketManager();
        virtual ~GameNetPacketManager();
        

    /*####################################################################
    //      # Main Init
    ####################################################################*/

        // 初始化
        virtual Bool            initialize();
        // 更新
        virtual I32             update();
        // 反初始化
        virtual I32             unInitialize();

        // 启动线程自动处理模式
        virtual void            startThreadAutoHandle();
        // 结束线程自动处理模式
        virtual void            endThreadAutoHandle();
        // 是否线程自动处理模式
        virtual Bool            isThreadAutoHandle();

        // 手动处理一次Logic 2 Net events
        virtual I32             manualDoOneL2NHandle( I32 handle );
        // 手动处理一次Net 2 Logic events
        virtual I32             manualDoOneN2LHandle( I32 handle );
        
    protected:

        // driver 分线程
        static void             checkAndUpdateL2NEventsFromAllDriver(Ptr ptr);
        static void             checkAndUpdateN2LEventsFromAllDriver(Ptr ptr);

    public:

        // 注册Driver,在createDrive后必须调用注册配置
        void                    configDrive(I32 handle, GameNetDriveConfig& config);

        // 得到过滤器
        GameNetPacketFilter*    getPacketFilter();

    /*####################################################################
    //      NetEvent From Logic To NetLib
    ####################################################################*/

    public:

        // 得到游戏发送缓存对象
        void                    getGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr, I32 handle, U32 buffSize = MG_NET_DEFAULT_SEND_BUFFER_SIZE);
        void                    cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader) ;
        void                    cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize) ;

        // 发送数据
        void                    prepareSend( GameNetSendDataBufferPtr& ptr, I32 handle, I32 id, I32 sendSize );
        
    /*####################################################################
    //      NetEvent From NetLib To Logic
    ####################################################################*/

    public:

        // From NetLib 
        virtual	void	        addAcceptEvent(I32 handle,I32 id,NetAddress&address);
        virtual	void	        addConnectEvent(I32 handle,I32 id,NetAddress&address);
		virtual	void	        addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address);
        virtual	void	        addRecvEvent(I32 handle,I32 id, Char8* buff, I32 buffLen);
        virtual	void	        addErrEvent(I32 handle,I32 id);
        virtual	void	        addSendEvent(NetOnceSendConfig* config);

    public:

        virtual void            freeEvent(INetEvent* netEvent);

    protected:

        virtual void		    onAccept(NetEventAccept* netEvent) = 0;
		virtual void		    onConnected(NetEventConnect* netEvent) = 0;
		virtual void		    onClose(NetEventClose* netEvent) = 0;
        virtual void		    onRecv(NetEventRecv* netEvent) =0;
        virtual void		    onError(NetEventErr* netEvent) = 0;

    private:

    /*####################################################################
    //      NetEvent From Drive
    ####################################################################*/

    private:

        // 得到网络事件驱动器
        GameNetDriverManager*   createOrRetrieveGameNetDriverManager( I32 handle );
        // 得到网络事件驱动器
        GameNetDriverManager*   retrieveGameNetDriverManager( I32 handle );
        // 清空所有的网络事件驱动器
        void                    clearAllGameNetDriverManager();

        /*
            @ 网络连接事件队列
            @ 根据NetManager::Driver分类划分
        */
        std::map<I32, GameNetDriverManager*>  mNetDriverEventsMap;
        ObjectPool<GameNetDriverManager,false>      mNetDriverEventsPool;

    private:

        /// 处理数据包线程
        OneThreadHandle             mL2NThreadHandlesForAllDriver;
        OneThreadHandle             mN2LThreadHandlesForAllDriver;

        // 线程自动处理
        Bool                        mThreadAutoHandleStart;
        // 线程自动处理
        Bool                        mThreadAutoHandleForAllDriver;

        // 网络包过滤器
        GameNetPacketFilter         mGameNetPacketFilter;

    };

}

/******************************************************************************/

#endif