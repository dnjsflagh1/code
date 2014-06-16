/******************************************************************************/
#ifndef _TESTNETPACKET_H_
#define _TESTNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //测试数据包想关类型
    /******************************************************************************/
    enum TestNetPacket
    {
        PT_TEST_UNKNOW = 0,

        PT_TEST_CF_BASE,
		PT_TEST_FC_BASE,

		//PT_TEST_CFM_BASE,
        PT_TEST_CF_CFM_BASE,
		PT_TEST_FM_CFM_BASE,
		PT_TEST_MC_CFM_BASE,

		PT_TEST_CL_BASE,
		PT_TEST_LC_BASE

    };

#pragma pack (push)
#pragma pack (1)
	//**********************************************************************
	//@名字:        
	//@功能:        
	//@备注:        
	//**********************************************************************/
	struct PT_TEST_CF_BASE_DATA
	{
		Int     player_id;
		U64     character_Id;
		Int		size;
		U64     num;
		Char	data[1];
	};
	struct PT_TEST_CF_BASE_DATA_INFO
	{
		static const Int headSize = sizeof(PT_TEST_CF_BASE_DATA) - sizeof(Char);
		static const Int dataSize(PT_TEST_CF_BASE_DATA* data)
		{
			return headSize + data->size;
		}
	};
	//**********************************************************************/
	struct PT_TEST_FC_BASE_DATA
	{
		PT_TEST_CF_BASE_DATA data;
	};
	struct PT_TEST_FC_BASE_DATA_INFO
	{
		static const Int dataSize(PT_TEST_FC_BASE_DATA* data)
		{
			return PT_TEST_CF_BASE_DATA_INFO::dataSize(&data->data);
		}
	};

	//**********************************************************************/
	struct PT_TEST_CF_CFM_BASE_DATA
	{
		PT_TEST_CF_BASE_DATA data;
	};
	struct PT_TEST_CF_CFM_BASE_DATA_INFO
	{
		static const Int dataSize(PT_TEST_CF_CFM_BASE_DATA* data)
		{
			return PT_TEST_CF_BASE_DATA_INFO::dataSize(&data->data);
		}
	};
	//**********************************************************************/
	struct PT_TEST_FM_CFM_BASE_DATA
	{
		PT_TEST_CF_BASE_DATA data;
	};
	struct PT_TEST_FM_CFM_BASE_DATA_INFO
	{
		static const Int dataSize(PT_TEST_FM_CFM_BASE_DATA* data)
		{
			return PT_TEST_CF_BASE_DATA_INFO::dataSize(&data->data);
		}
	};
	//**********************************************************************/
	struct PT_TEST_MC_CFM_BASE_DATA
	{
		PT_TEST_CF_BASE_DATA data;
	};
	struct PT_TEST_MC_CFM_BASE_DATA_INFO
	{
		static const Int dataSize(PT_TEST_MC_CFM_BASE_DATA* data)
		{
			return PT_TEST_CF_BASE_DATA_INFO::dataSize(&data->data);
		}
	};
	//**********************************************************************/
   /* struct PT_TEST_BASE_DATA
    {
        Int     player_id;
        U64     character_Id;
		Int		size;
		U64     num;
        Char	data[1];
    };
    struct PT_TEST_BASE_DATA_INFO
    {
		static const Int headSize = sizeof(PT_TEST_BASE_DATA) - sizeof(Char);
        static const Int dataSize(PT_TEST_BASE_DATA* data)
		{
			return headSize + data->size;
		}
    };*/
	//**********************************************************************
	struct PT_TEST_CL_BASE_DATA
	{
		Int     size;
		Char	data[1];
	};
	struct PT_TEST_CL_BASE_DATA_INFO
	{
		static const Int headSize = sizeof(PT_TEST_CL_BASE_DATA) - sizeof(Char);
		static Int dataSize(PT_TEST_CL_BASE_DATA* data) 
		{	
			return  headSize + data->size;
		}
	};
	//**********************************************************************
	struct PT_TEST_LC_BASE_DATA
	{
		PT_TEST_CL_BASE_DATA data;
	};
	struct PT_TEST_LC_BASE_DATA_INFO
	{
		static Int dataSize(PT_TEST_LC_BASE_DATA* data) 
		{	
			return  PT_TEST_CL_BASE_DATA_INFO::dataSize(&data->data);
		}
	};
	//**********************************************************************
#pragma pack (pop)
}

/******************************************************************************/

#endif