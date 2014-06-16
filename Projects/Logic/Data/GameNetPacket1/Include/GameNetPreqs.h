/******************************************************************************/
#ifndef _GAMENETPREQS_H_
#define _GAMENETPREQS_H_
/******************************************************************************/


/******************************************************************************/
namespace MG
{
    class GameNetL2NEventDataFactory;
    class GameNetSendDataBufferPtr;
    class GameNetOnceSendConfigPtr;

    struct GameNetDriveConfig;
    class GameNetDriverManager;

    class Logic2NetEventFromOneConnectHandler;
    class Logic2NetEventFromOneConnectHandlerPtr;
    class ExternalRecallL2NManager;

    class Net2LogicEventFromOneConnectHandler;
    class Net2LogicEventFromOneConnectHandlerPtr;
    class ExternalRecallN2LManager;

    class EventOneConnectHandler;

    class GameNetPacketFilter;
    class GameNetPacketAttackProtecter;
    class GameNetPacketCheatProtecter;
}

#endif
