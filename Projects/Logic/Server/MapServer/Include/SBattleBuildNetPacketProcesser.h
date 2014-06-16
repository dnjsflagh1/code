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
    //��ս���Խ���������Ϣ����
    /******************************************************************************/
    class SBattleBuildNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SBattleBuildNetPacketProcesser);
        SBattleBuildNetPacketProcesser();
        ~SBattleBuildNetPacketProcesser();

    public:
		void broadChangeBuildingBelongPlayerToRegion(SRegionObjectBase* targetRegion, std::map<BuildingIdType, SBuilding*>* buildingList, SPlayerPtr& belongPlayer);
        //ͬ���������˺�����ͼ�ϵ����еĽ�ɫ��
        //void	sendBattleBuildDamageToClient( SBattleBuildingNew* battleBuildObj, DamageType reducetype, UInt val );

    };

}


#endif