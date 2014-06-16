/******************************************************************************/
#include "stdafx.h"
#include "GameNetEvent.h"
#include "LoginNetPacketProcesser.h"
#include "ServerNetApplyManager.h"
#include "ServerMain.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    Bool LoginNetPacketProcesser::processClientPacket(I32 id,NetEventRecv* packet)
    {

        return false;
    }

    //-----------------------------------------------------------------------
    Bool LoginNetPacketProcesser::processServerPacket(I32 id,NetEventRecv* packet)
    {
        if ( packet->getChannel() == GNPC_LOGIN )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            if ( data->type == PT_LOGIN_S2S_SERVER_LOGIN )
            {
                onRecvS2SLoginPacket( id, (PT_LOGIN_S2S_LOGIN_DATA*)data->data );
                return true;
            }
			else if (data->type == PT_SERVER_S2S_LOGIN_VERSION_ERROR)
			{
				onRecvLoginErrorVersionInfo(id,(PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA*)data->data);
				return true;
			}
        }
        return false;
    }

    //-----------------------------------------------------------------------
    void LoginNetPacketProcesser::sendS2SLoginPacket(I32 id, Char16* name, U8 serverType, U64 serverUniqueFlag, U32 serverId,U32 code,Char8* serverVersion)
    {
		printServerLoginLog(id, name,serverType,serverUniqueFlag,serverId,code,serverVersion);

        GameNetSendDataBufferPtr dataPtr;
        ServerMain::getInstance().getServerSendDataBuffer( dataPtr );
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_S2S_SERVER_LOGIN;
            PT_LOGIN_S2S_LOGIN_DATA* data = (PT_LOGIN_S2S_LOGIN_DATA*)(packet->data);

            if ( data )
            {
                data->code = code;
                data->serverType = serverType;
                data->serverUniqueFlag = serverUniqueFlag;
				data->serverId = serverId;
				StrnCpyS(data->serverVersion,serverVersion,StrLen(serverVersion));
                WStrnCpyS(data->name,name,WStrLen(name));

                ServerMain::getInstance().sendServer(   dataPtr, 
                                                        GameNetPacketData_INFO::headSize + PT_LOGIN_S2S_LOGIN_DATA_INFO::dataSize, 
                                                        id );
            }
        }
    }

    //-----------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvS2SLoginPacket(I32 id, PT_LOGIN_S2S_LOGIN_DATA* data)
    {
        ServerNetApplyManager::getInstance().onRecvServerConncectLogin( id,data->name,(GameNetType)data->serverType, data->serverUniqueFlag, data->serverId, data->code,data->serverVersion);
    }
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::printServerLoginLog(I32 id, Char16* name, U8 serverType, U64 serverUniqueFlag, U32 serverId,U32 code,Char8* serverVersion)
	{
		Str8 dest;
		MGStrOp::toString(name,dest);
		NetAddress addr = ServerNetApplyManager::getInstance().getAddress(ServerNetApplyManager::getInstance().getServerHandle(),id);
		MG_LOG(out_debug,"id=%d name=%s ip=%s port=%d type=%d unique=%I64i serverId=%d version=%s\n",id,dest.c_str(),addr.getIPStr(),addr.getPort(),(I32)serverType,serverUniqueFlag,serverId,serverVersion);
	}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginVersionErrorInfo( I32 id,Char16* name, Byte type,Char8* errorInfo,I32 errorInfoSize )
	{
        GameNetSendDataBufferPtr dataPtr ;
        ServerMain::getInstance().getServerSendDataBuffer( dataPtr );
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_SERVER_S2S_LOGIN_VERSION_ERROR;
			PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA* data = (PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA*)(packet->data);

			if ( data )
			{
				WStrnCpyS(data->serverName,name,WStrLen(name));
				data->serverType = type;
				data->dataSize = errorInfoSize + 1;
				data->errorInfo[errorInfoSize] = 0;
				MGStrOp::sprintf(data->errorInfo,errorInfoSize,errorInfo);
				
                ServerMain::getInstance().sendServer( dataPtr, 
                                            GameNetPacketData_INFO::headSize + PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO::dataSize(data), 
                                            id );
			}
		}
	}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvLoginErrorVersionInfo( I32 id,PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA* data )
	{
		ServerNetApplyManager::getInstance().closeServer(id);
		MG::MsgBox::show(data->errorInfo,"∞Ê±æ—È÷§");
	}
}
