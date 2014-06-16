//***************************************************************************************
#ifndef _H_CHARACTER_LOGINANDOUT_
#define _H_CHARACTER_LOGINANDOUT_
//***************************************************************************************
#include "WorldCorePreqs.h"
#include "SysLogNetPacket.h"
//**********************************************************************************************************
#define CHARACTERLOGIN_TABLE_NAME		"syslogcharacterloginDB_info"
//***************************************************************************************
namespace MG
{
	class CharacterloginDBOp
	{
	public:
		static Bool checkOrCreateCharacterloginDBTable(DBDriver* driver);
		static Bool insertCharacterloginDB(DBDriver* driver, PT_SYSLOG_CHARACTER_LOGIN_Data* data);
	};
	
}
//***************************************************************************************
#endif
//***************************************************************************************