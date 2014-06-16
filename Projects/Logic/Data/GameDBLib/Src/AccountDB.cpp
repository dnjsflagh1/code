/******************************************************************************/
#include "stdafx.h"
#include "AccountDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
/******************************************************************************/

namespace MG
{
 
	//-------------------------------------------------------------------------------------------------
	Bool AccountDBOp::checkOrCreateAccountTable( DBDriver& driver )
	{
		static Colume accountColumn[] = 
		{
			{"acc_name",			"VARCHAR(50)",		"0"},				//账号名
			{"acc_psw",				"VARCHAR(50)",		"0"},				//密码md5码
			{"acc_superpsd",		"VARCHAR(50)",		"0"},				//超级密码md5码
			{"acc_vip",				"INT",				"0"},				//vip
			{"acc_state",			"TINYINT",			"0"},				//状态
			{"acc_startforbidtime",	"DATETIME",			"0"},				//禁止登陆开始时间
			{"acc_endforbidtime",	"DATETIME",			"0"},				//禁止登陆结束时间
			{"acc_currgamebin",		"INT",				"0"},				//当前游戏币
			{"acc_totalgamebinpast","INT",				"0"},				//累计充值游戏币
			{"acc_lastaddbintime",	"DATETIME",			"0"},				//上次充值时间
			{"acc_lastcostbintime",	"DATETIME",			"0"},				//上次消费时间
			{"acc_lastloginip",		"INT",				"0"},				//上次登陆ip
			{"acc_lastLoginTime",	"DATETIME",			"0"},				//上次登陆时间
			{"acc_lastLogoutTime",	"DATETIME",			"0"},				//上次登出时间
			{"acc_lastServerId",	"INT",				"0"},				//上次所在服务器id
			{"acc_lastClanId",	    "BIGINT",		    "0"},		        //上次登陆的角色id
			{"acc_createTime",		"DATETIME",			"0"},				//账号创建的时间
			{"acc_allInGameTime",	"DATETIME",			"0"},				//累计在线时间
			{"acc_loginTimes",		"INT",				"0"},				//累计登陆次数
		};
		DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS account_info (acc_uin BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(acc_uin))");
        DBQueryResult* res1 = *resEx;
		if (!res1 ||(res1 && res1->getResultType() == DBQuery_Result_INVALID))
		{
			return false;
		}
		Bool res2 = driver.addColume(ACCOUNT_TABLE_NAME,accountColumn,sizeof(accountColumn)/sizeof(Colume));
		if (!res2)
		{
			return false;
		}
		
		return true;
	}
	//-------------------------------------------------------------------------------------------------
	Bool AccountDBOp::checkAccount(DBDriver& driver,IdType& accountId,Char16* accountName,Char16* accountPsw)
	{
		return true;
		Char8 sql[4096] = {0};
		Str8 name;
		Str8 psw;
		MGStrOp::toString(accountName,name);
		MGStrOp::toString(accountPsw,psw);
		MGStrOp::sprintf(sql,4096,"select acc_uin from account_info where acc_name = binary('%s') and acc_psw = binary('%s')",name.c_str(),psw.c_str());
		
        //所有数据库返回值要重写，因为getResultType()暂时不能判断执行情况
        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
		if (res && res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0)
		{
            accountId = res->getFieldData(0,0)->ulonglongData;
			return true;
		}

		return false;
	}
	//-------------------------------------------------------------------------------------------------
    Bool AccountDBOp::getActiveAccountsNameMap( DBDriver& driver, std::map<Str,Player>& nameList )
    {
        return false;
    }
	//-------------------------------------------------------------------------------------------------
    Bool AccountDBOp::createAccount( DBDriver& driver, Player& accountDB, U64& accountid )
    {
        ////插入
        //Char8 sql[1028] = {0};
        //Char8 startForbidTime[32] = {0};
        //Char8 endForbidTime[32] = {0};
        //Char8 lastAddBinTime[32] = {0};
        //Char8 lastCostBinTime[32] = {0};
        //Char8 lastLoginTime[32] = {0};
        //Char8 lastLogoutTime[32] = {0};
        //Char8 createTime[32] = {0};
        //Char8 allInGameTime[32] = {0};

        //MGStrOp::sprintf(
        //    sql,
        //    1028, 
        //    "insert into clandatabase_info\
        //    (acc_name, acc_psw, acc_superpsd, acc_vip, acc_state, acc_startforbidtime,\
        //    acc_endforbidtime, acc_currgamebin, acc_totalgamebinpast, acc_lastaddbintime, acc_lastcostbintime,\
        //    acc_lastloginip, acc_lastLoginTime, acc_lastLogoutTime, acc_lastServerId, acc_lastPlayerCharacterId,\
        //    acc_createTime, acc_allInGameTime, acc_loginTimes) \
        //    values('%s', '%s', '%s', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '%s', '%d',\
        //    '%s', '%s', '%d', '%d', '%s', '%s', '%d')",
        //    accountDB.name, accountDB.psw, accountDB.superPsw, accountDB.vip, accountDB.state, accountDB.startForbidTime,
        //    accountDB.endForbidTime, accountDB.currGameBin, accountDB.totalGameBinPast, accountDB.lastAddBinTime,
        //    accountDB.lastCostBinTime, accountDB.lastLoginIp, accountDB.lastLoginTime, accountDB.lastLogoutTime,
        //    accountDB.lastServerId, accountDB.lastPlayerCharacterId, accountDB.createTime, accountDB.allInGameTime,
        //    accountDB.loginTimes
        //    );

        //Bool result = false; 
        //DBQueryResult* dbRes = NULL;
        //driver.queryLock();
        //{
        //    DBQueryResultEx resEx = driver.query(sql);
        //    DBQueryResult* dbRes = *resEx;
        //    dbRes = driver.query( sql, false );
        //    if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        //    {  
        //        result = true;
        //        accountid = CommonGameDBOp::getLastInsertID( driver, false );
        //    }
        //}
        //driver.queryUnLock();
        //return result;
        return false;
    }
	//-------------------------------------------------------------------------------------------------
	Bool AccountDBOp::createAccount(DBDriver& driver, Char16* accountName,Char16* accountPsw,AccountIdType& accountId )
	{
		Char8 sql[4096] = {0};
		Str8 name;
		Str8 psw;
		MGStrOp::toString(accountPsw,psw);
		MGStrOp::toString(accountName,name);
		MGStrOp::sprintf(sql,4096,"insert into account_info(acc_name, acc_psw) values ( binary('%s'),binary('%s')) ",name.c_str(),psw.c_str());

		Bool result = false;
		driver.queryLock();
		{
			DBQueryResultEx resEx = driver.query(sql);
			DBQueryResult* dbRes = *resEx;
			if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
			{  
				result = true;
				accountId = CommonGameDBOp::getLastInsertID( driver, false );
			}
		}
		driver.queryUnLock();

		return result;
	}
	//-------------------------------------------------------------------------------------------------
	Bool AccountDBOp::selectAccountByName(DBDriver& driver, Char16* accountName, AccountIdType& accountId)
	{
		Char8 sql[4096] = {0};
		Str8 name;
		MGStrOp::toString(accountName,name);
		MGStrOp::sprintf(sql,4096,"select * from account_info where acc_name = binary('%s')",name.c_str());

		//所有数据库返回值要重写，因为getResultType()暂时不能判断执行情况
		DBQueryResultEx resEx = driver.query(sql);
		DBQueryResult* res = *resEx;
		if (res && res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0)
		{
			accountId = res->getFieldData(0,0)->ulonglongData;
			return true;
		}

		return false;
	}
}


