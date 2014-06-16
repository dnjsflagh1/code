//***************************************************************************************
#ifndef _H_PLAYER_LOGINANDOUT_
#define _H_PLAYER_LOGINANDOUT_
//***************************************************************************************
#include "WorldCorePreqs.h"
#include "SysLogNetPacket.h"
//**********************************************************************************************************
#define PLAYERLOGIN_TABLE_NAME		"syslogplayerloginDB_info"
//***************************************************************************************
namespace MG
{
	class PlayerLoginDBOp
	{
	public:
		static Bool checkOrCreatePlayerLoginDBTable(DBDriver* driver);
		static Bool insertPlayerLoginDB(DBDriver* driver, PT_SYSLOG_PLAYER_LOGIN_Data* data);
	};
}
//***************************************************************************************
#endif
//***************************************************************************************