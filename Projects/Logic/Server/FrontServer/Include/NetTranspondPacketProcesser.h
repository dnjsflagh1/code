/******************************************************************************/
#ifndef _NETTRANSPONDPACKETPROCESS_H_
#define _NETTRANSPONDPACKETPROCESS_H_
/******************************************************************************/

#include "NetTranspondNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //服务器转发客户端相关消息处理
    /******************************************************************************/
    class NetTranspondPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(NetTranspondPacketProcesser);
        NetTranspondPacketProcesser();
        ~NetTranspondPacketProcesser();
        
        Bool    isBelongChannel( NetEventRecv* packet );

        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

		Bool	processChatServerPacket(I32 id, NetEventRecv* packet);
		Bool	processCenterServerPacket(I32 id, NetEventRecv* packet);

    public:
        
        //发送客户端转发数据到MapServer
        void sendClientTranspondDataToMapServer( U64 mapID, I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize, I32 mapNetId = 0 );
		//发送客户端转发数据到MapServer
		void sendChatServerTranspondDataToClient( U64 mapID, I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize );
        //广播客户端转发数据到MapServer
        void broadcastClientTranspondDataToMapServer( I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize );


    protected:

        //当服务器转发客户端数据
        void onServerTranspondClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
		
		//广播给所有的客户端
		void onServerTranspondBroadToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
        
    private:

        // 保存服务器转发客户端数据到缓存
        void saveBuffServerTranspondToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
        // 发送服务器转发客户端数据
        void sendServerTranspondToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );

    };

}


#endif