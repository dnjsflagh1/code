/******************************************************************************/
#ifndef _NETTRANSPONDPACKETPROCESS_H_
#define _NETTRANSPONDPACKETPROCESS_H_
/******************************************************************************/

#include "NetTranspondNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //������ת���ͻ��������Ϣ����
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
        
        //���Ϳͻ���ת�����ݵ�MapServer
        void sendClientTranspondDataToMapServer( U64 mapID, I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize, I32 mapNetId = 0 );
		//���Ϳͻ���ת�����ݵ�MapServer
		void sendChatServerTranspondDataToClient( U64 mapID, I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize );
        //�㲥�ͻ���ת�����ݵ�MapServer
        void broadcastClientTranspondDataToMapServer( I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize );


    protected:

        //��������ת���ͻ�������
        void onServerTranspondClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
		
		//�㲥�����еĿͻ���
		void onServerTranspondBroadToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
        
    private:

        // ���������ת���ͻ������ݵ�����
        void saveBuffServerTranspondToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );
        // ���ͷ�����ת���ͻ�������
        void sendServerTranspondToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize );

    };

}


#endif