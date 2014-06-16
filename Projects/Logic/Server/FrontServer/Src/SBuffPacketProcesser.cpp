//***************************************************************************************
#include "stdafx.h"
#include "SBuffPacketProcesser.h"
#include "SWorldManager.h"
#include "SPlayerCharacter.h"
#include "FrontServerMain.h"
#include "BuffData.h"
//***************************************************************************************
namespace MG
{
	MG::Bool SBuffPacketProcesser::processMapServerPacket( I32 id, NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_BUFF )
		{   
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			case PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA:
				recvBuffDataFromMapServer(id, (PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data*)data->data);
				break;
			}

			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------------
	void SBuffPacketProcesser::sendBuffDataListToMapServer( I32 id, PlayerCharacterIdType charId, std::map<UInt, BuffData>* pMapBuffData )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;

		//// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = NULL;
	    PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data* sendData = NULL;

        //���ͷ�Ĵ�С��CDNetData�Ĵ�С
		UInt headSize = GameNetPacketData_INFO::headSize + PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data::dataSize - netBuffInfoData::dataSize;
        UInt elemSize = netBuffInfoData::dataSize;
        //�����С
        UInt bagSize = headSize;

        std::map<U32, BuffData>::iterator  front = pMapBuffData->begin();
        std::map<U32, BuffData>::iterator  back = pMapBuffData->end();
        for ( ; front != back; front ++ )
        {
			if ( front->second.mTimeUse == false )
			{
				continue;
			}

			//-------------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				//����Ƿ���Ҫ����
				if ( bagSize + elemSize > dataPtr->getLogicDataMaxSize() )
				{
					// ��������
					FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,bagSize, id);

					dataPtr.setNull();
				}
			}

			//-------------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// ���һ�����͡�����ˡ�����
				FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				//// ת���ɱ�׼����ʽ
				packet = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->type = PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST;
				packet->channel = GNPC_BUFF;

				sendData = (PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data*)packet->data;
				if(!sendData)
					return;
				//���ͷ
				sendData->dbId = charId;
				sendData->ncount = 0;

				//���ͷ�Ĵ�С��CDNetData�Ĵ�С
				headSize = GameNetPacketData_INFO::headSize + PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data::dataSize - netBuffInfoData::dataSize;
				elemSize = netBuffInfoData::dataSize;
				//�����С
				bagSize = headSize;
			}

			//-------------------------------------------------------------------------------

            //���
			sendData->buffdatalist[sendData->ncount].buffId =  front->second.mBuffId;
			sendData->buffdatalist[sendData->ncount].timeUse =  front->second.mTimeUse;
			sendData->buffdatalist[sendData->ncount].curAddNum =  front->second.mCurAddNum;

            //���¼�¼����
            bagSize += elemSize;
            ++sendData->ncount;
        }
        
		//-------------------------------------------------------------------------------

        if ( dataPtr.isNull() == false )
		{
			FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,bagSize, id);
			dataPtr.setNull();
		}
	}

	//-------------------------------------------------------------------------------
	void SBuffPacketProcesser::recvBuffDataFromMapServer( I32 id, PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data* pData )
	{
		SPlayerPtr pSPlayer;// = SWorldManager::getInstance().getPlayerByAccountId(pData->acountId);
		if ( pSPlayer.isNull() ) return;

		SBuffManager* pSBuffManager;// = pSPlayer->getMainClan()->getSBuffManager();
		DYNAMIC_ASSERT(pSBuffManager);

		pSBuffManager->updateBuff(pData->dbId, pData->buffdatalist.timeUse, pData->buffdatalist.curAddNum, pData->buffdatalist.buffId);
	}

}