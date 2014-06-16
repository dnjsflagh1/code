/******************************************************************************/
#ifndef _INSTANCE_NET_PACKET_PROCESSOR_H_
#define _INSTANCE_NET_PACKET_PROCESSOR_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameNetEvent.h"
#include "InstanceNetPacket.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//������Ϣ����
	/******************************************************************************/
	
	/******************************************************************************/
	class InstanceNetPacketProcesser
	{
	public:
		InstanceNetPacketProcesser();
		~InstanceNetPacketProcesser();
		SINGLETON_INSTANCE(InstanceNetPacketProcesser);

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);


		//************************************************************

		//@{ FrontServer
	public:
		//���͵�������ǰ�˷�����
		void	sendTiroListPacketToFrontServer();



		//�յ����ָ����б�
		//void    onRecvTiroListFromFrontServer( I32 id , PT_PLAYER_M2C_TIRO_LIST_DATA* data );

		//@ }

	};

}
#endif	//_INSTANCE_NET_PACKET_PROCESSOR_H_