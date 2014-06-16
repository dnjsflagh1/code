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
		friend class PlayCharacterNetPacketProcesser;
		SINGLETON_INSTANCE(PlayerNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

		//��ӡ��Ϣ
		void	sendPrintTest();

		//���ָ������б�
		void	sendTiroList();


		void	sendPlayerEnterRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);

	private:
		void	sendPlayerEnterRegionByCharId(AccountIdType accountId, PlayerCharacterIdType playerCharacterId);

	public:

		void	onRecvPlayerJumpMap(I32 id, PT_PLAYER_F2C_JUMP_REGION_DATA* data);
		//void	onRecvPlayerJumpMapError(I32 id, PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA* data);
        
		//��ȡ���佫��Ϣ
		void    onRecvMainGenrealInfoFromFrontServer(I32 id, PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA* data );
        //��ȡ�佫��Ϣ
        void    onRecvClientGenrealInfoFromFrontServer( I32 id, PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* data );

		void	onRecvRemainPlayerCharacterListFromMapServer( I32 id, PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA* data );
        //��ȡ������Ϣ
        void    onRecvClientTroopListFromFrontServer( I32 id, PT_PLAYER_F2C_TROOP_INFO_LIST_DATA* data );

		// �յ����ָ����б�
		void    onRecvTiroListFromMapServerBegin( I32 id, PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA* data );
		void    onRecvTiroListFromMapServer( I32 id, PT_PLAYER_M2C_TIRO_LIST_DATA* data );
		void    onRecvTiroListFromMapServerEnd( I32 id, PT_PLAYER_M2C_TIRO_LIST_END_DATA* data );

    };
}

#endif
