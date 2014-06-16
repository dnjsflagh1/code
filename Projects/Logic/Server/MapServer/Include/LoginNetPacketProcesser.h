/******************************************************************************/
#ifndef _LOGIN_NET_PACKET_PROCESSER_H_
#define _LOGIN_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //���������½���������Ϣ����
	//�ͻ��˵�½�����Ϣ����
    /******************************************************************************/
    class LoginNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(LoginNetPacketProcesser);
        LoginNetPacketProcesser();
        ~LoginNetPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:

        //һЩ���崦�������


		//���յ�Front���ͻ����Ƿ���
		void	onCheckClientInFrontServerResult(PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA* data);

		// ��Э���Ѿ���������ȷ�ϣ���ʱע�ͣ�
		//void	onRecvMapListFromFrontServer( I32 id, PT_F2M_MAPLIST_DATA* data);
        //һЩ���巢�Ͱ�����

		///���ͻ����Ƿ���FrontSrrver
		void	sendCheckClientInFrontServer(I32 frontServerId,I32 clientNetIdInFs);


    };

}


#endif	//_LOGIN_NET_PACKET_PROCESSER_H_