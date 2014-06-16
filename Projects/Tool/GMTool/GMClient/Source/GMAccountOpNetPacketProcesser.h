/******************************************************************************/
#ifndef _GMACCOUNTOPNETPACKETPROCESSER_H_
#define _GMACCOUNTOPNETPACKETPROCESSER_H_
/******************************************************************************/
#include "GMAccountNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //GM�ʺŲ�����Ϣ����
    /******************************************************************************/
    
    class GMAccountOpNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(GMAccountOpNetPacketProcesser);

        Bool	processGMServerManagerPacket(I32 id,NetEventRecv* packet);

    //************************************************************

    public:
        //���͵������󵽵��������
        void	sendLoginPacketToGMServerManager(CChar16* name, CChar16* password,Char8* clientVersion);


    protected:
        
        //��¼���
        void    onGMLoginResultFromLoginServer( I32 id , GMPT_GMMC_ACC_LOGIN_RESULT_DATA* data );
 	
    };

}
#endif