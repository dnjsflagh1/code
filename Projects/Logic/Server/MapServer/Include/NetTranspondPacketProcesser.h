/******************************************************************************/
#ifndef _NETTRANSPONDPACKETPROCESS_H_
#define _NETTRANSPONDPACKETPROCESS_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "NetTranspondNetPacket.h"
#include "PlayerNetPacket.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // 网络转发包缓存
    /******************************************************************************/
    class NetTranspondPacketProcesser;
    class NetTranspondSendDataBufferPtr
    {
        friend class NetTranspondPacketProcesser;
		friend class SRegionNetPacketProcesser;
		friend class SCampaignNetPacketProcesser;
		friend class SPlayerNetPacketProcesser;

    public:

		NetTranspondSendDataBufferPtr();
        NetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize);

        // 得到缓存
        virtual Char8*      getTranspondData();
        // 得到缓存大小
        virtual U32         getTranspondDataMaxSize( UInt maxClientCount );

    public:

        GameNetSendDataBufferPtr mDataPtr;
        
        //已经使用掉的数据大小
        Int mUsedHeadSize;

        //预估尾部的数据大小
        Int mEstimateTailSize;

    public:

        NetTranspondSendDataBufferPtr(const NetTranspondSendDataBufferPtr& r)
            :mDataPtr(r.mDataPtr),
            mUsedHeadSize(r.mUsedHeadSize),
            mEstimateTailSize(r.mEstimateTailSize)
        {
        }

        NetTranspondSendDataBufferPtr& operator=(const NetTranspondSendDataBufferPtr& r) {
            mDataPtr            = r.mDataPtr;
            mUsedHeadSize       = r.mUsedHeadSize;
            mEstimateTailSize   = r.mEstimateTailSize;
            return *this;
        }
    };

    /******************************************************************************/
    //服务器转发客户端相关消息处理
    /******************************************************************************/
    class NetTranspondPacketProcesser
    {
    public:

		enum GridsBroadcastType
		{
			GBT_NULL,
			GBT_LAST,
			GBT_CURR,
			GBT_FILTER_LAST,
			GBT_FILTER_CURR,
		};

        SINGLETON_INSTANCE(NetTranspondPacketProcesser);
        NetTranspondPacketProcesser();
        ~NetTranspondPacketProcesser();

        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

    public:

        // 得到网络转发发送数据缓存
        void    getClientTranspondSendDataBuffer( NetTranspondSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_BIG_MAX_SIZE );
        // 发送网络转发客户端数据包到FrontServer
        Bool    sendClientTranspondSendDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
                                            I32 frontSvrNetID, I32 client_net_id, U64 account_id );

		// 广播客户端转发数据到FrontServer自动转发客户端 【根据FrontServerId 打包】 同步现在使用的函数
		void    broadcastClientTranspondPackToFrontServer(  NetTranspondSendDataBufferPtr& dataPtr,
															Int dataSize,
															SSceneGrid* currSceneGrid, 
															SSceneGrid* lastSceneGrid, 
															SRegionObjectBase* regionObjectBase,  
															PlayerIdType ignorepPlayerId,
															GridsBroadcastType broadcastType = GBT_CURR );

		// 广播客户端转发数据到FrontServer自动转发客户端 【根据FrontServerId 打包】 同步不要用此函数
		void    gridsBroadcastClientTranspondPackToFrontServer( SSceneGrid* currSceneGrid, SSceneGrid* lastSceneGrid, NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, PlayerIdType ignorepPlayerId, GridsBroadcastType broadcastType = GBT_CURR );

		// 广播客户端转发数据到FrontServer自动转发客户端 【根据FrontServerId 打包】 同步不要用此函数
		void    broadcastClientTranspondPackToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, SRegionObjectBase* region);

    protected:

		void    subSceneGridsPlayerList( SSceneGrid* regionGrids1, SSceneGrid* regionGrids2, std::map<NetIdType, std::map<PlayerIdType, SPlayer*>>& playerList );   
    };

}


#endif