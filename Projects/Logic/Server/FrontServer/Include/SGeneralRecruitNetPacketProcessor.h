//*******************************************************************************************************
#ifndef _S_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_H_
#define _S_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_H_
//*******************************************************************************************************
#include "FrontServerPreqs.h"
#include "GeneralRecruitNetPacket.h"

//*******************************************************************************************************
namespace MG
{
    class SGeneralRecruitNetPacketProcessor
    {
    public:
        SGeneralRecruitNetPacketProcessor(){;}
        ~SGeneralRecruitNetPacketProcessor(){;}
        SINGLETON_INSTANCE(SGeneralRecruitNetPacketProcessor);

    public:
        Bool	processClientPacket(I32 id, NetEventRecv* packet);


	public:
		//����ˢ������佫
		void onRecvFreshFromClient(NetIdType clientNetId, PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA*data);

		//�����ȡ����佫���б�
		void onRecvGetListFromClient(NetIdType clientNetId, PT_GR_C2F_RANDOM_GENERAL_LIST_DATA*data);

		//ȷ����ļ����佫
		void onRecvGeneralRecruitFromClientNewVer(NetIdType clientNetId, PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA*data);

		//�л��佫
		void onRecvChangeGeneralFromClientNewVersion(NetIdType clientNetId, PT_GR_C2F_CHANGE_GENERAL_DATA*data);


	public:
		void sendClearClanToClient(NetIdType clientNetID);

		void sendRandomGeneralListBeginToClient(NetIdType clientNetID);
		void sendRandomGeneralListToClient(NetIdType clientNetID, GeneralRecruitSystem* generalRecruitSystem);
		void sendRandomGeneralListEndToClient(NetIdType clientNetID);

		void sendGeneralRecruitConfirmToClient(NetIdType clientNetID, U32 index);

		void sendGeneralRecruitResultToClient(NetIdType clientNetID, Recruit_Result result);

		//�����ݿ������ļ�佫��Ϣ �����͸��ͻ���
		void loadDbAndSendRecruitGeneralListToClient(NetIdType clientNetID, SClan* clan);

	private:
		//��������ļ�佫���б�
		void sendRecruitGeneralListBeginToClient(NetIdType clientNetID);
		void sendRecruitGeneralListToClient(NetIdType clientNetID, std::vector<PlayerCharacterData>* playerCharacterList);
		void sendRecruitGeneralListEndToClient(NetIdType clientNetID);

    };

}

//*******************************************************************************************************
#endif	//_S_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_H_
//*******************************************************************************************************
