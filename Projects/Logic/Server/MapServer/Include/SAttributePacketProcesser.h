//*******************************************************************************************************
#ifndef _H_SATTRIBUTEPACKETPROCESSER_
#define _H_SATTRIBUTEPACKETPROCESSER_
//*******************************************************************************************************
#include "MapServerPreqs.h"
#include "AttributeNetPacket.h"
//*******************************************************************************************************
namespace MG
{
    class SAttributePacketProcesser
    {
    public:
        SAttributePacketProcesser(){;}
        ~SAttributePacketProcesser(){;}
        SINGLETON_INSTANCE(SAttributePacketProcesser);
    
    public:
        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:
        //发送角色伤害包给Client
        void    syncCharacterHPMPSPToClient( SCharacter* sender, SCharacter* master, Byte reducetype, UInt val, Byte resType, Int hateValue = 0 );
        //发送角色伤害包给FrontServer
        void    sendCharacterDamageToFrontServer( SCharacter* sender, Byte reducetype, UInt val, Byte resType );
        //发送角色治疗包给FrontServer
        void    sendCharacterCureToFrontServer( SCharacter* sender, Byte reducetype, UInt val, Byte resType );
        // 发送HPMPSP到FrontServer
        void    sendCharacterHPMPSPToFrontServer( NetIdType id, SCharacter* sender, Byte reducetype, UInt val, Byte resType);
		void	syncUpLevelToClient(SPlayerCharacter* pSPlayerCharacter, U32 level, Byte levelType);
    private:
        void	recvUpLevel(I32 id, PT_ATTR_F2M_ATTR_LEVEL_DATA* pData);
        
    };

}
//*******************************************************************************************************
#endif
//*******************************************************************************************************