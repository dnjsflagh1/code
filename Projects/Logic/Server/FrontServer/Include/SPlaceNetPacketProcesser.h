/******************************************************************************/
#ifndef _SPLACENETPACKETPROCESSER_H_
#define _SPLACENETPACKETPROCESSER_H_
/******************************************************************************/
#include "PlaceNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//�ݵ���Ϣ����
	/******************************************************************************/
	class SPlaceNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPlaceNetPacketProcesser);
		SPlaceNetPacketProcesser();
		~SPlaceNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);

	public:

		//���յ��ݵ���������Ϣ�Ƿ��;ݵ���Ϣ��MapServer
		void	onRecvPlaceClickFromClient( I32 netId, PT_PLACE_C2F_CLICED_INFO_DATA* data);

	protected:


	};

}


#endif