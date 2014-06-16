/******************************************************************************/
#ifndef _SERVERDLLINTERFACE_H_
#define _SERVERDLLINTERFACE_H_
/******************************************************************************/

/******************************************************************************/
typedef void* (__cdecl *GET_MGSERVERDLL_INTERFACE_PROC)(void); 
#define DLL_ENTRY_MGSERVERDLL_PROC GET_MGSERVERDLL_INTERFACE
/******************************************************************************/

#include "GameNetPacket.h"
#include "GameNetPacketManager.h"
#include "SServerSetting.h"
#include "GameNetEvent.h"
#include "NetDefine.h"
#include "IMGPackExterInterface.h"

namespace MG
{
    /******************************************************************************/
    //游戏服务器主接口
    /******************************************************************************/
    class ServerLauncherInterface
    {
    public:
        virtual SServerSetting*             getServerSetting() = 0;
        virtual DBDriver*                   getDBDriver() = 0;
		virtual	U64				            getClientUid( I32 id ) = 0;
		virtual IMGExternalPackManager*     getMGExternalPackManager() = 0;
		
        virtual void                        closeAllClient() = 0;
		virtual void                        closeClient(I32 id) = 0;
		virtual void                        closeServer(I32 id) = 0;

		virtual void					    freeEvent(INetEvent* netEvent) = 0;

        virtual void                        getClientSendDataBuffer( GameNetSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE ) = 0;
        virtual void                        getServerSendDataBuffer( GameNetSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE ) = 0;

        virtual void                        cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader) = 0;
        virtual void                        cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize) = 0;

        virtual void                        sendClient( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id ) = 0;
        virtual void                        sendServer( GameNetSendDataBufferPtr& ptr, I32 sendSize, I32 id ) = 0;

        virtual void                        setClientNetCode(I32 id,U64 code) = 0;
        virtual void                        setServerNetCode(I32 id,U64 code) = 0;
		virtual	void			            setDialogHandle(HWND handle) = 0;
		virtual	HWND			            getDialogHandle() = 0;
		virtual	U64				            getUniqueFlag() = 0;

        virtual void                        writeDBLog(CChar* msg) = 0;
        virtual void                        writeCoreLog(CChar* msg) = 0;
        virtual void                        writeShellLog(CChar* msg) = 0;

		virtual Bool					    isNetAvailable() = 0;

		virtual	Str16					    getSettingPathName() = 0;
		virtual	void					    setSettingPathName(Char16* name) = 0;
       
		virtual	Str16					    getConfigKeyName() = 0;
		virtual	void					    setConfigKeyName(Char16* name) = 0;

		virtual	U32						    getServerIdByNetId(I32 netId) = 0;
		virtual	I32						    getNetIdByServerId(U32 serverId) = 0;
    };

    /******************************************************************************/
    //游戏服务器主接口
    /******************************************************************************/
    class IServerDllInterface
    {
    public:
        virtual Bool    initialize(ServerLauncherInterface* launcher) = 0;
        virtual Bool    unInitialize() = 0;
		virtual void	update(){};
        
        virtual void    onClientConnected(I32 id,NetAddress*address, INetConnect* connect) = 0;
        virtual void    onClientDisconnect(I32 id, INetConnect* connect) = 0;
		virtual void    onClientRecvPacket(I32 id,NetEventRecv* packet,INetConnect* connect) = 0;
		
		virtual void    onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address) = 0;
		virtual void    onServerDisconnect(I32 id,NetAddress*address) = 0;
        virtual void    onServerRecvPacket(I32 id,NetEventRecv* packet) = 0;


    };

}

/******************************************************************************/
#endif

