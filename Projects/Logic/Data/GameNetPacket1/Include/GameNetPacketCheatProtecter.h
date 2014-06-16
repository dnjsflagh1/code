/******************************************************************************/
#ifndef _GAMENETPACKETCHEATPROTECTER_H_
#define _GAMENETPACKETCHEATPROTECTER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetPacket.h"
#include "NetManager.h"
#include "GameNetEvent.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // ��Ϸ����ұ���
    /******************************************************************************/
    class GameNetPacketCheatProtecter
    {
    public:
        GameNetPacketCheatProtecter();
        virtual ~GameNetPacketCheatProtecter();

        Bool        initialize();
        Bool        update();
        Bool        unInitialize();


    protected:
        
    };

}

/******************************************************************************/

#endif