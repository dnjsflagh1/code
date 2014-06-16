/******************************************************************************/
#include "stdafx.h"
#include "GameNetEvent.h"
#include "LineUpNetPacketProcesser.h"
#include "UILoginLineUp.h"
#include "ClientNetApplyManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	Bool LineUpNetPacketProcesser::processLoginServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_LINE_UP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LINE_UP_L2C:	
				onRecvLineUpInfoFromLoginServer(id,(PT_LINE_UP_L2C_DATA*)data->data);
				break;
			case PT_LINE_UP_L2C_CANCLE_CMD_RELULT:
				onRecvClientCancleLineUpCmdResultFromLoginServer(id,(PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA*)data->data);	
				break;
			}

			return true;
		}   
		return false;
	}
	//-----------------------------------------------------------------------
	Bool LineUpNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_LINE_UP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LINE_UP_F2C:	
				onRecvLineUpInfoFromFrontServer(id,(PT_LINE_UP_F2C_DATA*)data->data);
				break;
			case PT_LINE_UP_F2C_CANCLE_CMD_RELULT:
				onRecvClientCancleLineUpCmdResultFromFrontServer(id,(PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA*)data->data);	
				break;
			}

			return true;
		}   
		return false;
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvLineUpInfoFromLoginServer( I32 netId,PT_LINE_UP_L2C_DATA* data )
	{
		//�Ŷӽ���
		if (data->waitCount == 0)
		{
			UILoginLineUp::getInstance().closeGui();
		}
		else
		//�Ŷ���Ϣ
		{
			/*switch (data->type)
			{
			case line_up_busy_lc_account_login:
				{

					UILoginLineUp::getInstance().adjustUI(LINE_UP_TYPE_BUSY);
					Str16 waitAccountStr;
					MGStrOp::toString(data->waitCount,waitAccountStr);
					UILoginLineUp::getInstance().setRanKed(waitAccountStr);
					UILoginLineUp::getInstance().openGui();
				}
				break;
			case line_up_busy_lc_server_full:
				{
					UILoginLineUp::getInstance().adjustUI(LINE_UP_TYPE_FULL);
					UILoginLineUp::getInstance().openGui();
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
				}
			}*/
		}
		
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvLineUpInfoFromFrontServer( I32 netId,PT_LINE_UP_F2C_DATA* data )
	{
		//�Ŷӽ���
		if (data->waitCount == 0)
		{
			UILoginLineUp::getInstance().closeGui();
		}

		switch (data->type)
		{
        case line_up_busy_lc_account_login:					//���������Ŷ�
            {

            }
            break;
        case line_up_busy_lc_server_full:					//���������Ŷ�
            {

            }
            break;
        case line_up_busy_fc_account_login:					//���������Ŷ�
            {

            }
            break;
		case line_up_busy_fc_create_clan:					//���������Ŷ�
			{

			}
			break;
		case line_up_busy_fc_del_clan:						//ɾ�������Ŷ�
			{

			}
			break;
		case line_up_busy_fc_create_character:				//������ɫ�Ŷ�
			{

			}
			break;
		case line_up_busy_fc_join_game:						//������Ϸ��ͼ�Ŷ�
			{

			}
			break;
		default:
			{
                DYNAMIC_EEXCEPT_LOG("LineUpNetPacketProcesser::onRecvLineUpInfoFromFrontServer : not define lineup type!");
			}
		}
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::sendCancleLineUpCmdToLoginServer( I32 netId,Byte type )
	{
		// ��ʱLoginServerû�п�ȡ�����Ŷ���Ϣ
		DYNAMIC_ASSERT(false);
		return;

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_C2L_CANCLE_CMD;

			// ת���߼���
			PT_LINE_UP_C2L_CANCLE_CMD_DATA* sendData = (PT_LINE_UP_C2L_CANCLE_CMD_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->type				= type;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO::dataSize );
			}
		}
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::sendCancleLineUpCmdToFrontServer( I32 netId,Byte type )
	{
		switch (type)
		{
		case line_up_busy_fc_create_clan:					//���������Ŷ�
		case line_up_busy_fc_del_clan:						//ɾ�������Ŷ�
		case line_up_busy_fc_create_character:				//������ɫ�Ŷ�
		case line_up_busy_fc_join_game:					//������Ϸ��ͼ�Ŷ�
		default:
			{
				// ���ŶӲ�����ȡ��
				DYNAMIC_ASSERT(false);
				return;
			}
		}
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_C2F_CANCLE_CMD;

			// ת���߼���
			PT_LINE_UP_C2L_CANCLE_CMD_DATA* sendData = (PT_LINE_UP_C2L_CANCLE_CMD_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->type				= type;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO::dataSize );
			}
		}
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvClientCancleLineUpCmdResultFromLoginServer( I32 netId,PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA* data )
	{
		// LoginServer��ʱû�п���ȡ�����Ŷ���Ϣ
		DYNAMIC_ASSERT(false);
		return;
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvClientCancleLineUpCmdResultFromFrontServer( I32 netId,PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA* data )
	{
		switch (data->type)
		{
		case line_up_busy_fc_create_clan:					//���������Ŷ�
			{

			}
			break;
		case line_up_busy_fc_del_clan:						//ɾ�������Ŷ�
			{

			}
			break;
		case line_up_busy_fc_create_character:				//������ɫ�Ŷ�
			{

			}
			break;
		case line_up_busy_fc_join_game:						//������Ϸ��ͼ�Ŷ�
			{

			}
			break;
		default:
			{
				DYNAMIC_ASSERT(false);
			}
		}
	}
}

