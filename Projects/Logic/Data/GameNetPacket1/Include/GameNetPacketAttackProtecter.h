/******************************************************************************/
#ifndef _GAMENETPACKETATTACKPROTECTER_H_
#define _GAMENETPACKETATTACKPROTECTER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetPacket.h"
#include "NetManager.h"
#include "GameNetEvent.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // ��Ϸ����������
    /******************************************************************************/
    class GameNetPacketAttackProtecter
    {
    public:
        GameNetPacketAttackProtecter();
        virtual ~GameNetPacketAttackProtecter();

        Bool        initialize();
        Bool        update();
        Bool        unInitialize();


    protected:

    };

}

/******************************************************************************/

#endif