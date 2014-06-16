/******************************************************************************/
#ifndef _REGIONNETPACKETPROCESSER_H_
#define _REGIONNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "RegionNetPacket.h"
/******************************************************************************/
namespace MG
{
	class RegionNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(RegionNetPacketProcesser)

		Bool	processFrontServerPacket(CClient *client,NetEventRecv* packet);
	public:


		void onRecvPlayerCharacterCreateAndAppear( CClient* client, PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* data );
		void onRecvPlayerCharacterDestroyAndDisappear( CClient* client, PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* data );
		
		void onRecvPlayerCharacterEnter( CClient *client, PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data );
		void onRecvPlayerCharacterLeave( CClient *client, PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* data );

#if 0
		void onRecvTroopGroupEnter( CClient *client, PT_REGION_M2C_ADD_TROOP_GROUP_DATA* data );
		void onRecvTroopGroupLeave( CClient *client, PT_REGION_M2C_REMOVE_TROOP_GROUP_DATA* data );
#endif

		void onRecvBattleBuildingEnter( CClient *client, PT_REGION_M2C_ADD_BUILDING_DATA* data );
		void onRecvBattleBuildingLeave( CClient *client, PT_REGION_M2C_REMOVE_BUILDING_DATA* data );

		//��������ɫ����
		//void onRecvThirdPartCharacterEnter( CClient *client, PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA* data );
		
		//��Ӫ
		void onRecvCampEnter( CClient *client, PT_REGION_M2C_ADD_BUILDING_DATA* data );

		//��Ҫ����ʿ����λ��
		void onRecvTroopCreate( CClient *client, PT_REGION_M2C_CREATE_TROOP_DATA* data );
		
		//����
		void onRecvTroopEnter( CClient *client, PT_REGION_M2C_ADD_TROOP_DATA* data );

		
	public:
		//������Ӻ�ʿ����λ�� ��֪ͨ������
		void	sendCreateTroopReturn(I32 frontServerNetId,PT_REGION_M2C_CREATE_TROOP_DATA* data);
		//void	sendAddBattleBuildingByPlayer(I32 frontServerNetId,U64 characterId, U64 regionId, Byte regionType, Int addBuildingNum, NetAddBuildingInfoFront* addBuildingInfo);
		//void	sendRemoveBattleBuildingByPlayer(I32 frontServerNetId,U64  buildingId);
		void	sendAddTroopTest(I32 frontServerId,AccountIdType accountId);
	};
}

#endif	//_REGIONNETPACKETPROCESSER_H_
