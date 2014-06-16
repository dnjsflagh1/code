/******************************************************************************/
#ifndef _TROOP_NET_PACKET_PROCESSER_H_
#define _TROOP_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "TroopNetPacket.h"
#include "FrontServerPreqs.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//�������������Ϣ����
	/******************************************************************************/
	/******************************************************************************/
	class TroopNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(TroopNetPacketProcesser);
		TroopNetPacketProcesser();
		~TroopNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:

		//************************************************************

		//@{ Client
	public:

	protected:
		void onRecvTroopSoldierMoveClient( I32 id , PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA *data);
	//	//�����ܵ���ɫ����ͼ
	//	void onRecvTroopJumpRegionFromClient( I32 id , PT_TROOP_GROUP_C2F_JUMP_REGION_DATA*data);
	//	//�����ܵ���ɫ�ƶ�
	//	void onRecvTroopGroupMoveClient( I32 id , PT_TROOP_GROUP_C2S_MOVE_POS_DATA*data);

	//	void onRecvTroopGroupYawToDirClient( I32 id , PT_TROOP_GROUP_C2S_YAW_DIR_DATA*data);

	//	void onRecvTroopGroupStopMoveClient( I32 id , PT_TROOP_GROUP_C2S_STOP_MOVE_DATA*data);

	//	void onRecvTroopMoveClient( I32 id , PT_TROOP_C2S_MOVE_POS_DATA*data);

	//	void onRecvTroopGroupMoveToObjectClient( I32 id , PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA* data);
	//	void onRecvTroopMoveToObjectClient( I32 id , PT_TROOP_C2S_MOVE_OBJECT_DATA* data);

 //       //�����ܵ�������������
 //       void onRecvTroopRegion( I32 id , PT_TROOP_GROUP_M2F_ADD_TROOP_DATA*data);
	//	//@ }

	//	//@{ MapServer
	//public:
    //	//���ͽ�ɫ�ƶ���Ϣ
	//	void broadcastTroopJumpToRegion(IdType characterId, Byte regionType, UInt regionId);

	//	void sendTroopGroupMoveToMapServer(I32 id, PT_TROOP_GROUP_C2S_MOVE_POS_DATA* data );
	//	void sendTroopMoveToMapServer(I32 id, PT_TROOP_C2S_MOVE_POS_DATA* data );
	//	void sendTroopGroupMoveToObjectMapServer(I32 id, PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA* data);
	//	void sendTroopGroupYawToDirMapServer(I32 id, PT_TROOP_GROUP_C2S_YAW_DIR_DATA* data);
	//	void sendTroopGroupStopMoveMapServer(I32 id, PT_TROOP_GROUP_C2S_STOP_MOVE_DATA* data);
	//	void sendTroopMoveToObjectMapServer(I32 id, PT_TROOP_C2S_MOVE_OBJECT_DATA* data);
	//	
	//	//����ת������ͻ���
	//	void sendTroopJumpRegionToClient(I32 id, Byte result);

	//	void sendTroopSkillInfoToClient(I32 id, STroopGroup* troopGroup);

	protected:


		//@ }
	};

}


#endif	//_TROOP_NET_PACKET_PROCESSER_H_