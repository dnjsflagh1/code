/******************************************************************************/
#ifndef _NETTRANSPONDPACKETPROCESS_H_
#define _NETTRANSPONDPACKETPROCESS_H_
/******************************************************************************/

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
    public:

        NetTranspondSendDataBufferPtr();
        NetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize);

        // 得到缓存
        virtual Char8*      getTranspondData();
        // 得到缓存大小
        virtual U32         getTranspondDataMaxSize( UInt maxClientCount );

    protected:

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
            mDataPtr = r.mDataPtr;
            mUsedHeadSize = r.mUsedHeadSize;
            mEstimateTailSize = r.mEstimateTailSize;
            return *this;
        }
    };

    /******************************************************************************/
    //服务器转发客户端相关消息处理
    /******************************************************************************/
    class NetTranspondPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(NetTranspondPacketProcesser);
        NetTranspondPacketProcesser();
        ~NetTranspondPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

    public:

        // 得到网络转发发送数据缓存
        void   getClientTranspondSendDataBuffer( NetTranspondSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
       
		// 发送网络转发客户端数据包到FrontServer
        void    sendClientTranspondSendDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
                                            I32 frontSvrNetID,I32 clientNetIdInFrontServer, U64 accountId);
		// 广播客户端转发数据到FrontServer自动转发客户端
		void    broadcastClientTranspondDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize);

    protected:
   
    };

}


#endif