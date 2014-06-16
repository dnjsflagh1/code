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
		//排队结束
		if (data->waitCount == 0)
		{
			UILoginLineUp::getInstance().closeGui();
		}
		else
		//排队信息
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
		//排队结束
		if (data->waitCount == 0)
		{
			UILoginLineUp::getInstance().closeGui();
		}

		switch (data->type)
		{
        case line_up_busy_lc_account_login:					//创建家族排队
            {

            }
            break;
        case line_up_busy_lc_server_full:					//创建家族排队
            {

            }
            break;
        case line_up_busy_fc_account_login:					//创建家族排队
            {

            }
            break;
		case line_up_busy_fc_create_clan:					//创建家族排队
			{

			}
			break;
		case line_up_busy_fc_del_clan:						//删除家族排队
			{

			}
			break;
		case line_up_busy_fc_create_character:				//创建角色排队
			{

			}
			break;
		case line_up_busy_fc_join_game:						//进入游戏地图排队
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
		// 暂时LoginServer没有可取消的排队信息
		DYNAMIC_ASSERT(false);
		return;

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_C2L_CANCLE_CMD;

			// 转换逻辑包
			PT_LINE_UP_C2L_CANCLE_CMD_DATA* sendData = (PT_LINE_UP_C2L_CANCLE_CMD_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->type				= type;

				// 发送数据
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
		case line_up_busy_fc_create_clan:					//创建家族排队
		case line_up_busy_fc_del_clan:						//删除家族排队
		case line_up_busy_fc_create_character:				//创建角色排队
		case line_up_busy_fc_join_game:					//进入游戏地图排队
		default:
			{
				// 此排队不可以取消
				DYNAMIC_ASSERT(false);
				return;
			}
		}
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_C2F_CANCLE_CMD;

			// 转换逻辑包
			PT_LINE_UP_C2L_CANCLE_CMD_DATA* sendData = (PT_LINE_UP_C2L_CANCLE_CMD_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->type				= type;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO::dataSize );
			}
		}
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvClientCancleLineUpCmdResultFromLoginServer( I32 netId,PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA* data )
	{
		// LoginServer暂时没有可以取消的排队信息
		DYNAMIC_ASSERT(false);
		return;
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvClientCancleLineUpCmdResultFromFrontServer( I32 netId,PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA* data )
	{
		switch (data->type)
		{
		case line_up_busy_fc_create_clan:					//创建家族排队
			{

			}
			break;
		case line_up_busy_fc_del_clan:						//删除家族排队
			{

			}
			break;
		case line_up_busy_fc_create_character:				//创建角色排队
			{

			}
			break;
		case line_up_busy_fc_join_game:						//进入游戏地图排队
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

