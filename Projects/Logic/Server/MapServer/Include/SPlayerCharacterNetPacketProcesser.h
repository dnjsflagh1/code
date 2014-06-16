/******************************************************************************/
#ifndef _SCHARACTERNETPACKETPROCESSER_H_
#define _SCHARACTERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LoginNetPacket.h"
#include "PlayerCharacterNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //角色相关网络消息处理
    /******************************************************************************/
    class SPlayerCharacterNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SPlayerCharacterNetPacketProcesser);
        SPlayerCharacterNetPacketProcesser();
        ~SPlayerCharacterNetPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
        
    public:
		//一些具体发送包方法

		void sendPlayerCharacterJumpregionResult(SPlayerCharacterPtr& playerCharacter, ChatarcterJumpRegionResult result);
		
#if 0
		//在MapServer改变了 副本信息， 同步到FrontServer
		void sendPlayerCharacterChangeRegion(SPlayerCharacter* playerCharacter);
#endif

		//广播角色移动消息
		void broadcastPlayerCharacterMove(SPlayerCharacter* playerCharacter, NetVec2 startMovePos, NetVec2 endMovePos, Bool isBlockCheck);

		void broadcastPlayerCharacterStopMove(SPlayerCharacter* playerCharacter);

		void broadcastPlayerCharacterEnterFight(SPlayerCharacter* playerCharacter);

		void broadcastPlayerCharacterEndFight(SPlayerCharacter* playerCharacter);

        //发送角色伤害包给客户端
        //void sendPlayerCharacterDamageToClient( SPlayerCharacterNew* playerCharacter, DamageType reducetype, UInt val );

        //发送角色伤害包给mapserver
        //void sendPlayerCharacterDamageToFrontServer( SPlayerCharacterNew* pPlayerCharacter, AttackType attackType, DamageType reducetype, UInt val  );
		void	onRecvPlayerCharacterMoveFromFrontServer( I32 id, Byte	regionType, U64	regionId, I32 instanceId, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data );

		void	onRecvPlayerCharacterStopMoveFromFrontServer( I32 id, Byte	regionType, U64	regionId, I32 instanceId, PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA* data);

	public:
        //一些具体处理包方法

		//void    onRecvPlayerCharacterAttrFormFrontServer( I32 id, PT_PLAYERCHARACTER_F2M_ATTR_DATA* data);
		
		void	onRecvPlayerCharacterJumpFromFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA* data);
		void	onRecvPlayerCharacterJumpEmptyRegionFromFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA* data);
		void	onRecvPlayerCharacterJumpCampaignRegionFormFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA* data);

		void	onRecvPlayerCharacterSkillList(I32 id, PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA* data);

    };

}


#endif