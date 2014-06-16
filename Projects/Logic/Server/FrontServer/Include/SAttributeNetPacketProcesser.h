//*******************************************************************************************************
#ifndef _H_SATTRIBUTENETPACKETPROCESSER_
#define _H_SATTRIBUTENETPACKETPROCESSER_
//*******************************************************************************************************
#include "FrontServerPreqs.h"
#include "AttributeNetPacket.h"
//*******************************************************************************************************
namespace MG
{
    class SAttributeNetPacketProcesser
    {
    public:
        SAttributeNetPacketProcesser(){;}
        ~SAttributeNetPacketProcesser(){;}
        SINGLETON_INSTANCE(SAttributeNetPacketProcesser);

    public:
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

    public:

        //发送角色的伤害包
        void    sendCharacterHpSpMpToClient( SCharacter* pCharacter, DamageType reducetype, UInt val, Byte resType );
		void	sendUpLevel(I32 mapNetId, PlayerCharacterIdType charId, U32 level, Byte levelType);

    private:

        //当接受到角色Hp, sp, mp变化
        void    onRecvCharacterHpSpMp( I32 id , PT_ATTR_M2F_ATTR_HPMPSP_DATA*data);

    };

}
//*******************************************************************************************************
#endif
//*******************************************************************************************************
