/******************************************************************************/
#ifndef _SBATTLEBUILDNETPACKETPROCESSER_H_
#define _SBATTLEBUILDNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
#include "BuildNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //可战斗性建筑网络消息处理
    /******************************************************************************/
    class SBattleBuildNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SBattleBuildNetPacketProcesser);
        SBattleBuildNetPacketProcesser();
        ~SBattleBuildNetPacketProcesser();

    public:
		void broadChangeBuildingBelongPlayerToRegion(SRegionObjectBase* targetRegion, std::map<BuildingIdType, SBuilding*>* buildingList, SPlayerPtr& belongPlayer);
        //同步建筑的伤害到地图上的所有的角色。
        //void	sendBattleBuildDamageToClient( SBattleBuildingNew* battleBuildObj, DamageType reducetype, UInt val );

    };

}


#endif