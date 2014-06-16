/******************************************************************************/
#ifndef _GAMENETUDPPACKET_H_
#define _GAMENETUDPPACKET_H_
/******************************************************************************/


/******************************************************************************/
namespace MG
{
#pragma pack (push)
#pragma pack (1)
	/******************************************************************************/
	//游戏包头
	/******************************************************************************/
	struct GameNetUdpPacketHeader
	{
		Byte channel;
	};

	/******************************************************************************/
	//游戏包数据
	/******************************************************************************/
	struct GameNetUdpPacketData : public GameNetUdpPacketHeader
	{
		Byte    type;
		Char8   data[1];
	};
	struct GameNetUdpPacketData_INFO
	{
		static const Int headSize = sizeof(GameNetUdpPacketData) - sizeof(Char8);
	};
#pragma pack (pop)
}
#endif