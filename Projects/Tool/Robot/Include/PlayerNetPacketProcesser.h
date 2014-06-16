/******************************************************************************/
#ifndef _PLAYERNETPACKETPROCESSER_H_
#define _PLAYERNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "PlayerNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
	class PlayerNetPacketProcesser
	{
		SINGLETON_INSTANCE(PlayerNetPacketProcesser)

	public:
		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);

		//��ӡ��Ϣ
		void	sendPrintTest(I32 frontServerNetId);

		//���ָ������б�
		void	sendTiroList(I32 frontServerNetId,RegionIdType regionId, REGION_OBJ_TYPE regionType);


		void	sendPlayerEnterRegion(I32 frontServerNetId,RegionIdType regionId, REGION_OBJ_TYPE regionType);


		void	onRecvPlayerJumpMap(CClient* client, PT_PLAYER_F2C_JUMP_REGION_DATA* data);
		//void	onRecvPlayerJumpMapError(I32 id, PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA* data);

        //��ȡ�佫��Ϣ
        void    onRecvClientGenrealInfoFromFrontServer( CClient* client, PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* data );

		void	onRecvRemainPlayerCharacterListFromMapServer( CClient* client, PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA* data );
        //��ȡ������Ϣ
        void    onRecvClientTroopListFromFrontServer( CClient* client, PT_PLAYER_F2C_TROOP_INFO_LIST_DATA* data );

		// �յ����ָ����б�
		void    onRecvTiroListFromMapServer( CClient* client, PT_PLAYER_M2C_TIRO_LIST_DATA* data );


    };
}

#endif
