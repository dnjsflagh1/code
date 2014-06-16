//***************************************************************************************
#include "stdafx.h"
#include "CharacterLogInAndOut.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
#include "NetAddress.h"
//***************************************************************************************
namespace MG
{
	MG::Bool CharacterloginDBOp::checkOrCreateCharacterloginDBTable( DBDriver* driver )
	{
		static Colume CDDBColumn[] = 
		{
			{"id",					   "BIGINT",                "0"},								  //序号ID
			{"type",				   "INT",                   "0"},								  //类型
			{"characterid",            "BIGINT",                "0"},                                 //武将id
			{"name",				   "VARCHAR(8)",            "0"},                                 //武将的名
			{"surname",				   "VARCHAR(8)",            "0"},                                 //武将的姓
			{"accountid",              "BIGINT",                "0"},                                 //账号id
			{"logintime",              "DATETIME",              "0"},                                 //武将登录时间
			{"ipaddress",              "VARCHAR(64)",           "0"}                                  //武将登录的IP
		};
		DBQueryResultEx resEx = driver->query("CREATE TABLE IF NOT EXISTS syslogcharacterloginDB_info (id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(id))");
		DBQueryResult* res1 =  *resEx;
		if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
		{
			return false;
		}

		Bool  res2 = driver->addColume( CHARACTERLOGIN_TABLE_NAME, CDDBColumn, sizeof(CDDBColumn)/sizeof(Colume) );
		if ( !res2 )
		{
			return false;
		}

		//查询自己的CD的索引
		if ( !( *( driver->query("CREATE INDEX characteridid ON syslogcharacterloginDB_info (characterid)") ) ) )
		{
			return false;
		} 

		//查询自己的CD的索引
		if ( !( *( driver->query("CREATE INDEX accountidid ON syslogcharacterloginDB_info (accountid)") ) ) )
		{
			return false;
		} 

		return true;
	}
	//-----------------------------------------------------------------------------------
	MG::Bool CharacterloginDBOp::insertCharacterloginDB( DBDriver* driver, PT_SYSLOG_CHARACTER_LOGIN_Data* data )
	{
		Str8  strName;
		Str8 strSurName;
		Char8 ip[32] = "";
		Char8 dataTime[32];
		
		MGStrOp::toString(data->name, strName);
		MGStrOp::toString(data->surName, strSurName);
		NetAddress::inetNtoA(data->ipAddress, ip, 32);
		SYSTEMTIME systemTime = MGTimeOp::getLocalTime(data->logTime);
		MGStrOp::sprintf(dataTime, 32, "%d-%d-%d %d:%d:%d", 
			systemTime.wYear, systemTime.wMonth, systemTime.wDay,
			systemTime.wHour, systemTime.wMinute, systemTime.wSecond
			);

		Char8 sql[1024] = "";
		MGStrOp::sprintf(
			sql, 
			1024,
			"insert into syslogcharacterloginDB_info \
			(type, characterid, name, surname, accountid, logintime, ipaddress) \
			values('%d', '%I64d', '%s', '%s', '%I64d', '%s', '%s')",
			data->type, data->characterId, strName.c_str(), strSurName.c_str(), data->playerId, dataTime, ip
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