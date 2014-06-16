/******************************************************************************/
#ifndef _C_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_
#define _C_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "GeneralRecruitNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
	class CGeneralRecruitNetPacketProcessor
	{
	public:
		CGeneralRecruitNetPacketProcessor(){}
		~CGeneralRecruitNetPacketProcessor(){}
		SINGLETON_INSTANCE(CGeneralRecruitNetPacketProcessor)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

	public:

		void    onRecvRandomGeneralListBeginFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA* data );
		void    onRecvRandomGeneralListFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_DATA* data );
		void    onRecvRandomGeneralListEndFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA* data );

		void    onRecvClientGenrealInfoFromFrontServer( I32 id, PT_GR_F2C_CLEAR_CLAN_DATA* data );

		void    onRecvRecruitResultFromFrontServer( I32 id, PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA* data );

		void    onRecvRecruitConfirmFromFrontServer( I32 id, PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA* data );

		void    onRecvRecruitGeneralListBeginFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA* data );
		void    onRecvRecruitGeneralListFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA* data );
		void    onRecvRecruitGeneralListEndFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA* data );


	public:

		//ˢ������佫�б�
		void	sendFreshRandomGeneral(U32 GeneralRecruitId);

		//����佫�б�
		void	sendGetRandomGeneralList(U32 GeneralRecruitId);

		//ȷ����ļ�佫
		void	sendGeneralRecruit(RECRUIT_POSITION index);

		//�л��佫
		void	sendChangeGeneral(PlayerCharacterIdType charId);



	};
}

#endif	//_C_GENERAL_RECRUIT_NET_PACKET_PROCESSOR_
