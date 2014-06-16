/******************************************************************************/
#ifndef _SPLAYERNETPACKETPROCESSER_H_
#define _SPLAYERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "PlayerNetPacket.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //玩家相关网络消息处理
    /******************************************************************************/
    class SPlayerNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SPlayerNetPacketProcesser);
        SPlayerNetPacketProcesser();
        ~SPlayerNetPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	procesClientTranspondPacket(I32 client_net_id, U64 account_id, GameNetPacketData* data);

	public:

	//@{ FrontServer
	public:

		//发送永久停留地图的玩家角色数据到客户端 ok
		void    sendRemainedPlayerCharacterListToClient_New(SPlayer* player);
		//void	sendPlayerJumpRegionToClient_New(U64 account_id, U64 regionId, Byte type);
		//void	sendPlayerJumpRegionToClient_New(U64 account_id, SRegionObjectBase* region);
		void	sendPlayerJumpRegionToFrontServer(AccountIdType accountId, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, PlayerJumpResult jumpResult);
		void	sendPlayerJumpRegionToFrontServer(AccountIdType accountId, SRegionObjectBase* region,PlayerJumpResult jumpResult);

		//发送跳转错误信息
		//void	sendPlayerJumpRegionResultToFrontServer(AccountIdType accountId, NetIdType FrontServerId, Player_Jump_Error_Type error);

		void	sendTiroListToClientBegin(SPlayerPtr& player, NetIdType mapServerNetId);
		void	sendTiroListToClient(SPlayerPtr& player, std::map<RegionIdType, SBigRegionObject*>* tiroList, NetIdType mapServerNetId);
		void	sendTiroListToClientEnd(SPlayerPtr& player, NetIdType mapServerNetId);
		
		//当接受到玩家登入 ok
		void	onRecvPlayerLogin( I32 frontId , PT_PLAYER_F2M_LOGIN_DATA* data);

		//当接受到玩家登出 ok
		void	onRecvPlayerLogout( I32 frontId , PT_PLAYER_F2M_LOGOUT_DATA* data);
		
		//当接受到玩家角色列表 ok
		void	onRecvPlayerCharacterList( I32 frontId , PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA* data);
        
		//当接受到玩家角色的装备列表
        void    onRecvPlayerCharacterEquipList(I32 frontId, PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA* data);

		//当接受到军队列表
		void	onRecvTroopList( I32 frontId , PT_PLAYER_F2M_TROOP_INFO_LIST_DATA* data);

		// 接收完列表
		void	onRecvSyncAllListEnd( I32 frontId , PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA* data);

		//void	onRecvBuildingList( I32 frontId ,  PT_PLAYER_F2M_BATTLE_INFO_LIST_DATA* data);

		//玩家跳转地图
		void	onRecvPlayerJumpToRegion( I32 frontId , PT_PLAYER_F2M_JUMP_REGION_DATA* data);
		void	onRecvPlayerJumpToRegionByCharId( I32 frontId , PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA* data);

		//新手副本列表
		void	onRecvTiroList( I32 frontId , PT_PLAYER_F2M_TIRO_LIST_DATA* data);

	//@ }

    };

}


#endif