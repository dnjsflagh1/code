//***************************************************************************************
#include "stdafx.h"
#include "PlayerLogInAndOut.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
#include "NetAddress.h"
//***************************************************************************************
namespace MG
{
	MG::Bool PlayerLoginDBOp::checkOrCreatePlayerLoginDBTable( DBDriver* driver )
	{
		static Colume CDDBColumn[] = 
		{
			{"id",					   "BIGINT",                "0"},								  //序号ID
			{"type",				   "INT",					"0"},								  //类型
			{"accountid",              "BIGINT",                "0"},                                 //账号id
			{"logintime",              "DATETIME",              "0"},                                 //账号登录时间
			{"ipaddress",              "VARCHAR(64)",           "0"}                                  //账号登录的IP
		};
		DBQueryResultEx resEx = driver->query("CREATE TABLE IF NOT EXISTS syslogplayerloginDB_info (id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(id))");
		DBQueryResult* res1 =  *resEx;
		if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
		{
			return false;
		}

		Bool  res2 = driver->addColume( PLAYERLOGIN_TABLE_NAME, CDDBColumn, sizeof(CDDBColumn)/sizeof(Colume) );
		if ( !res2 )
		{
			return false;
		}

		//查询自己的CD的索引
		if ( !( *( driver->query("CREATE INDEX accountidid ON syslogplayerloginDB_info (accountid)") ) ) )
		{
			return false;
		} 

		return true;
	}
	//-----------------------------------------------------------------------------------
	MG::Bool PlayerLoginDBOp::insertPlayerLoginDB( DBDriver* driver, PT_SYSLOG_PLAYER_LOGIN_Data* data )
	{
		Char8 ip[32] = "";
		Char8 dataTime[32];

		NetAddress::inetNtoA(data->ipAddress, ip, 32);
		SYSTEMTIME systemTime = MGTimeOp::getLocalTime(data->logTime);
		MGStrOp::sprintf(dataTime, 32, "%d-%d-%d %d:%d:%d", 
			systemTime.wYear, systemTime.wMonth, systemTime.wDay,
			systemTime.wHour, systemTime.wMinute, systemTime.wSecond
			);

		Char8 sql[256] = "";
		MGStrOp::sprintf(
			sql, 
			256,
			"insert into syslogplayerloginDB_info \
			(type, accountid, logintime, ipaddress) \
			values('%d', '%I64d', '%s', '%s')",
			data->type, data->playerId, dataTime, ip
			);

		DBQueryResultEx resEx = driver->query(sql);
		DBQueryResult* res = *resEx;
		if ( res  &&  res->getResultType() != DBQuery_Result_INVALID )
		{
			return true;
		}

		return false;
	}
	
}