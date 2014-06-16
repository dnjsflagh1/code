/******************************************************************************/
#ifndef _GAMENETPACKETFILTER_H_
#define _GAMENETPACKETFILTER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetPacket.h"
#include "NetManager.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏包过滤器
    /******************************************************************************/
    class GameNetPacketFilter
    {
    public:
        GameNetPacketFilter();
        virtual ~GameNetPacketFilter();

        Bool        initialize();
        Bool        update();
        Bool        unInitialize();

        // 检测包
        Bool        checkRecvPacketValid( I32 handle,I32 id, GameNetPacketHeader* packet,I32 packetSize );

    protected:

        void                        addDescribe( GameNetPacketDataDescribe* describe );
        GameNetPacketDataDescribe*  getDescribe( Byte channel, Byte type );

        typedef std::map<Byte, GameNetPacketDataDescribe*>  GameNetPacketDataDescribeList;
        typedef std::map<Byte, GameNetPacketDataDescribeList>  GameNetPacketDataDescribeMap;
        GameNetPacketDataDescribeMap    mGameNetPacketDataDescribeMap;

    };

}

/******************************************************************************/

#endif