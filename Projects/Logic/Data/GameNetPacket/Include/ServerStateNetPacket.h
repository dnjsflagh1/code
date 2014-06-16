/******************************************************************************/
#ifndef _SERVERSTATENETPACKET_H_
#define _SERVERSTATENETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//服务器同步包类型
	/******************************************************************************/
	enum ServerStateNetPacketType
	{
		//PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE,

		PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START,
		PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW
	};

#pragma pack (push)
#pragma pack (1)

    /////////////////////////////////////////////////////////////
#if 0
#define MAX_MAP_NUM		100
	struct MapServerStates
	{
		I32 index;
		U64	serverUniqueFlag;
		I32 mapNum;					//每个MapServer开启的地图个数
		I32 mapId[MAX_MAP_NUM];
	};
#endif
    /////////////////////////////////////////////////////////////
#if 0
	struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA
	{
		I32				mapServerNum;
		MapServerStates serverStates[1];
	};
    struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA_INFO
    {
		static Int  const headSize        = sizeof (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA) - sizeof( MapServerStates );
		static Int  const mapServerStatesSize   = sizeof (MapServerStates);

        static Int  dataSize(PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA* data)
        { 
            return headSize + mapServerStatesSize * data->mapServerNum;
        };
    };

#endif
	/////////////////////////////////////////////////////////////
	struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA
	{
		
	};

	struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA);
	};

	/////////////////////////////////////////////////////////////
	struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA
	{
		I32				mapServerNum;		//mapserver 总数
		I32				mapServerIndex;		//当前mapserver在总mapserver列表中的索引
		U64				serverUniqueFlag;
	};


	struct PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA);
	};

	//**********************************************************************
#pragma pack (pop)

}
#endif