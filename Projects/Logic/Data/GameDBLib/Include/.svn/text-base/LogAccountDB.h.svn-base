//***************************************************************************************
#ifndef _H_LOG_ACCOUNT_
#define _H_LOG_ACCOUNT_
//***************************************************************************************
#include "WorldCorePreqs.h"
#include "SysLogNetPacket.h"
//**********************************************************************************************************
#define LOGACCOUNT_TABLE_NAME   "logaccountdb_info"
//***************************************************************************************
namespace MG
{
	//test
    class LogAccountDBOp
    {
    public:
        static Bool checkOrCreateLogAccountDBTable(DBDriver* driver);
        static Bool insertLogAccountDB(DBDriver* driver, PT_SYSLOG_ACCOUNT_OPERATE_DATA* data);
        static Bool getLogAccountDB(DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, U64 accountID);
        static Bool getLogAccountDB(DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, Str16 accountName);
		
		static Bool getLogAccountDB(DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, U64 startTime, U64 endTime);
		static Bool getLogAccountDB(DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, Str16 accountName, U64 startTime, U64 endTime);
    };
	//end test

}
//***************************************************************************************
#endif
//***************************************************************************************