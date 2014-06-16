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
    //角色相关网络消息处理
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
        //发送玩家角色列表
        void    sendPlayerCharacterListToClient(I32 netID, SPlayer* player);

        //发送单个武将到client
        void    sendPlayerCharacterToClient(I32 netID, SPlayerCharacter* pChar);
        
		//设置主武将后,发送主武将信息给client
		void    sendMainPlayerCharacterToClient(I32 netID, SPlayerCharacter* pChar);

        //发送玩家角色列表
        void    sendTroopListToClient(SPlayerPtr player);

        //发送玩家跳转区域消息给客户端
        void    sendPlayerJumpRegionToClient(SPlayerPtr player, PlayerJumpResult jumpResult, const FORCE force, NetVec2Data* pos, NetVec2Data* dir);

		//发送跳转区域 错误信息
		//void	sendJumpRegionErrorToClient( I32 netID, Player_Jump_Error_Type error );
    protected:

        //当收到玩家跳地图消息时
        void    onRecvPlayerJumpRegionFromClient(I32 netID, PT_PLAYER_C2F_JUMP_REGION_DATA* jumpData);

		void    onRecvPlayerJumpRegionByCharIdFromClient(I32 netID, PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA* jumpData);

		//新手副本请求
		void    onRecvTiroListFromClient(I32 netID, PT_PLAYER_C2F_TIRO_LIST_DATA* tiroList);
        
    //@ }

    //************************************************************
    //@{ MapServer
    public:

		//
		void	onRecvPlayerJumpRegionFromMapServer(I32 id, PT_PLAYER_M2F_JUMP_REGION_DATA* data);

		//void	onRecvPlayerJumpRegionErrorFromMapServer(I32 id, PT_PLAYER_M2F_JUMP_REGION_ERROR_DATA* data);


        //告知mapServer玩家登入游戏
        void    broadcastPlayerLoginToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

        //告知mapServer玩家登出游戏
        void    broadcastPlayerLogoutToMapServer(SPlayerPtr player);

        //发送玩家角色列表
        void    broadcastPlayerCharacterListToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

		//把新招募的角色发送过去
		void    sendRecruitPlayerCharacterToMapServer(SPlayerPtr player, SPlayerCharacter* newPlayerCharacter, NetIdType mapServerNetId = 0);
        
		//发送玩家角色装备
		void    broadcastPlayerCharacterEquipListToMapServer(SPlayerPtr player,NetIdType mapServerId = 0);
		
        ////发送单个武将到mapserver
        //void    broadcastPlayerCharacterToMapServer(I32 netID, SPlayerCharacter* pChar);
		
		//列表同步完成， MapServer启动成功
		void    broadcastAllListEndToMapServer(NetIdType mapServerId);

		//发送军队列表
		void    broadcastTroopGroupListToMapServer(SPlayerPtr player, NetIdType mapServerId = 0);

		void	sendPlayerJumpToRegionNewVer(SPlayerPtr player, NetIdType mapServerNetId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		
		//发送玩家进入某个区域
		void	broadcastPlayerJumpToRegion(SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);

		void	sendPlayerJumpToRegionByCharId(NetIdType mapServerNetId, AccountIdType accountId, PlayerCharacterIdType playerCharacterId);

		void	sendPlayerJumpToMapServer(NetIdType mapServerNetId, SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);
		
		// 打印内存信息
		void	broadcastPrintTestToMapServer();
    protected:

    //@ }

	};

}


#endif	//_PLAYER_NET_PACKET_PROCESSER_H_