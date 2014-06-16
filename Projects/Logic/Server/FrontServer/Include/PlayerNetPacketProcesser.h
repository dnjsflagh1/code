/******************************************************************************/
#ifndef _PLAYER_NET_PACKET_PROCESSER_H_
#define _PLAYER_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "PlayerNetPacket.h"
#include "FrontServerPreqs.h"
#include "SPlayer.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��ɫ���������Ϣ����
    /******************************************************************************/
	class PlayerNetPacketProcesser
	{
	public:
        SINGLETON_INSTANCE(PlayerNetPacketProcesser);
		PlayerNetPacketProcesser();
		~PlayerNetPacketProcesser();
        
        Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
        
	public:
        
    //************************************************************
    //@{ Client
    public:
        //������ҽ�ɫ�б�
        void    sendPlayerCharacterListToClient(I32 netID, SPlayer* player);

        //���͵����佫��client
        void    sendPlayerCharacterToClient(I32 netID, SPlayerCharacter* pChar);
        
		//�������佫��,�������佫��Ϣ��client
		void    sendMainPlayerCharacterToClient(I32 netID, SPlayerCharacter* pChar);

        //������ҽ�ɫ�б�
        void    sendTroopListToClient(SPlayerPtr player);

        //���������ת������Ϣ���ͻ���
        void    sendPlayerJumpRegionToClient(SPlayerPtr player, PlayerJumpResult jumpResult, const FORCE force, NetVec2Data* pos, NetVec2Data* dir);

		//������ת���� ������Ϣ
		//void	sendJumpRegionErrorToClient( I32 netID, Player_Jump_Error_Type error );
    protected:

        //���յ��������ͼ��Ϣʱ
        void    onRecvPlayerJumpRegionFromClient(I32 netID, PT_PLAYER_C2F_JUMP_REGION_DATA* jumpData);

		void    onRecvPlayerJumpRegionByCharIdFromClient(I32 netID, PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA* jumpData);

		//���ָ�������
		void    onRecvTiroListFromClient(I32 netID, PT_PLAYER_C2F_TIRO_LIST_DATA* tiroList);
        
    //@ }

    //************************************************************
    //@{ MapServer
    public:

		//
		void	onRecvPlayerJumpRegionFromMapServer(I32 id, PT_PLAYER_M2F_JUMP_REGION_DATA* data);

		//void	onRecvPlayerJumpRegionErrorFromMapServer(I32 id, PT_PLAYER_M2F_JUMP_REGION_ERROR_DATA* data);


        //��֪mapServer��ҵ�����Ϸ
        void    broadcastPlayerLoginToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

        //��֪mapServer��ҵǳ���Ϸ
        void    broadcastPlayerLogoutToMapServer(SPlayerPtr player);

        //������ҽ�ɫ�б�
        void    broadcastPlayerCharacterListToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

		//������ļ�Ľ�ɫ���͹�ȥ
		void    sendRecruitPlayerCharacterToMapServer(SPlayerPtr player, SPlayerCharacter* newPlayerCharacter, NetIdType mapServerNetId = 0);
        
		//������ҽ�ɫװ��
		void    broadcastPlayerCharacterEquipListToMapServer(SPlayerPtr player,NetIdType mapServerId = 0);
		
        ////���͵����佫��mapserver
        //void    broadcastPlayerCharacterToMapServer(I32 netID, SPlayerCharacter* pChar);
		
		//�б�ͬ����ɣ� MapServer�����ɹ�
		void    broadcastAllListEndToMapServer(NetIdType mapServerId);

		//���;����б�
		void    broadcastTroopGroupListToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

		void	sendPlayerJumpToRegionNewVer(SPlayerPtr player, NetIdType mapServerNetId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		
		//������ҽ���ĳ������
		void	broadcastPlayerJumpToRegion(SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);

		void	sendPlayerJumpToRegionByCharId(NetIdType mapServerNetId, AccountIdType accountId, PlayerCharacterIdType playerCharacterId);

		void	sendPlayerJumpToMapServer(NetIdType mapServerNetId, SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		
		// ��ӡ�ڴ���Ϣ
		void	broadcastPrintTestToMapServer();
    protected:

    //@ }

	};

}


#endif	//_PLAYER_NET_PACKET_PROCESSER_H_