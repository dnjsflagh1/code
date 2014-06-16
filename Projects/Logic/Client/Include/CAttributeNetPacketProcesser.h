//*****************************************************************************************************
#ifndef _H_CATTRIBUTENETPACKETPROCESSER_
#define _H_CATTRIBUTENETPACKETPROCESSER_
//*****************************************************************************************************
#include "ClientPreqs.h"
#include "AttributeNetPacket.h"
#include "GameNetEvent.h"	
//*****************************************************************************************************
namespace MG
{
    class CAttributeNetPacketProcesser
    {
    public: 
        CAttributeNetPacketProcesser(){;}
        ~CAttributeNetPacketProcesser(){;}
        SINGLETON_INSTANCE(CAttributeNetPacketProcesser);

    public:
        Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

    private:
        void    onRecvSyncCharacterDamage(I32 id, PT_ATTR_S2C_ATTR_HPMPSP_DATA* data);
        void    onRecvCharacterDamage(I32 id, PT_ATTR_F2C_ATTR_HPMPSP_DATA* data);
		void    onRecvUpLevel(I32 id, PT_ATTR_M2C_ATTR_LEVEL_DATA* data);

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************

