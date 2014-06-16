/******************************************************************************/
#include "stdafx.h"
#include "ServerLogNetPacketProcesser.h"
//#include "LogAccountDB.h"
#include "DbManager.h"
#include "PlayerLogInAndOut.h"
#include "CharacterLogInAndOut.h"
/******************************************************************************/
namespace MG
{
	Bool MG::ServerLogNetPacketProcesser::processSysLogServerPacket( I32 id,NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_SYSLOG )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
            DYNAMIC_ASSERT(data);
            switch (data->type)
            {
            case PT_SYSLOG_PLAYER_LOGIN:
                recvPlayerLoginFromLoginS( id, (PT_SYSLOG_PLAYER_LOGIN_Data*)(data->data) );
                return true;
			case PT_SYSLOG_CHARACTER_LOGIN:
				recvCharacterLoginFromFrontS( id, (PT_SYSLOG_CHARACTER_LOGIN_Data*)(data->data) );
				return true;
            }
        }
		return false;
	}
	//------------------------------------------------------------------------------------------
	void ServerLogNetPacketProcesser::recvPlayerLoginFromLoginS( I32, PT_SYSLOG_PLAYER_LOGIN_Data* pData )
	{
		PlayerLoginDBOp::insertPlayerLoginDB(DbManager::getInstance().getDBDriver(), pData);
	}
	//------------------------------------------------------------------------------------------
	void ServerLogNetPacketProcesser::recvCharacterLoginFromFrontS( I32, PT_SYSLOG_CHARACTER_LOGIN_Data* pData )
	{
		CharacterloginDBOp::insertCharacterloginDB(DbManager::getInstance().getDBDriver(), pData);
	}
}

