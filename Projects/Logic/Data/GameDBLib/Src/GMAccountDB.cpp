/******************************************************************************/
#include "stdafx.h"
#include "GMAccountDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
#include "GMCommonData.h"
/******************************************************************************/

namespace MG
{
 
	//-------------------------------------------------------------------------------------------------
	Bool GMAccountDBOp::checkOrCreateGMAccountTable( DBDriver& driver )
	{
		static Colume accountColumn[] = 
		{
			{"gm_acc_name",				"VARCHAR(50)",		"0"},				//账号名
			{"gm_acc_psw",				"VARCHAR(50)",		"0"},				//密码md5码
			{"gm_acc_level",			"INT",				"0"},				//vip
			{"gm_acc_state",			"TINYINT",			"0"},				//状态
			{"gm_acc_lastloginip",		"INT",				"0"},				//上次登陆ip
			{"gm_acc_lastLoginTime",	"DATETIME",			"0"},				//上次登陆时间
			{"gm_acc_lastLogoutTime",	"DATETIME",			"0"},				//上次登出时间
			{"gm_acc_createTime",		"DATETIME",			"0"},				//账号创建的时间
			{"gm_acc_loginTimes",		"INT",				"0"},				//累计登陆次数
		};
		DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS gm_account_info (gm_acc_uin INT NOT NULL AUTO_INCREMENT,PRIMARY KEY(gm_acc_uin))");
        DBQueryResult* res1 = *resEx;
		if (!res1 ||(res1 && res1->getResultType() == DBQuery_Result_INVALID))
		{
			return false;
		}
		Bool res2 = driver.addColume(GM_ACCOUNT_TABLE_NAME,accountColumn,sizeof(accountColumn)/sizeof(Colume));
		if (!res2)
		{
			return false;
		}
		
		return true;
	}
	//-------------------------------------------------------------------------------------------------
	Bool GMAccountDBOp::checkGMAccount(DBDriver& driver,IdType& accountId,Char16* accountName,Char16* accountPsw)
	{
		Char8 sql[4096] = {0};
		Str8 name;
		Str8 psw;
		MGStrOp::toString(accountName,name);
		MGStrOp::toString(accountPsw,psw);
		MGStrOp::sprintf(sql,4096,"select gm_acc_uin from gm_account_info where gm_acc_name = binary('%s') and gm_acc_psw = binary('%s')",name.c_str(),psw.c_str());
		
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
	Bool GMAccountDBOp::createGMAccount(DBDriver& driver, Char16* accountName,Char16* accountPsw,Int authority,AccountIdType& accountId )
	{
		Char8 sql[4096] = {0};
		Str8 name;
		Str8 psw;
		MGStrOp::toString(accountPsw,psw);
		MGStrOp::toString(accountName,name);
		MGStrOp::sprintf(sql,4096,"insert into gm_account_info(gm_acc_name, gm_acc_psw, gm_acc_level) values ( binary('%s'),binary('%s'),%d) ",name.c_str(),psw.c_str(),authority);

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

	Bool GMAccountDBOp::selectGMAccountList( DBDriver& driver,std::map<U32,GMClientInfo*>& dataSet )
	{
		Char8 sql[4096] = {0};
		MGStrOp::sprintf(sql,4096,"select gm_acc_name,gm_acc_psw,gm_acc_uin,gm_acc_level from gm_account_info");

		//所有数据库返回值要重写，因为getResultType()暂时不能判断执行情况
		DBQueryResultEx resEx = driver.query(sql);
		DBQueryResult* res = *resEx;
		
		if (res && res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0)
		{
			for (int row = 0; row < res->getRowCount(); row++)
			{
				GMClientInfo* gmData = MG_NEW GMClientInfo;
				wstring dest;

				res->getFieldData(row,0)->stringBuf;
				MGStrOp::toString(res->getFieldData(row,0)->stringBuf,dest);
				WStrnCpyS(gmData->name,dest.c_str(),MAX_ACCOUNT_LONGIN_NAME_LEN - 1);

				res->getFieldData(row,1)->stringBuf;
				MGStrOp::toString(res->getFieldData(row,1)->stringBuf,dest);
				WStrnCpyS(gmData->password,dest.c_str(),MAX_ACCOUNT_LONGIN_PSW_LEN - 1);

				gmData->gmId = res->getFieldData(row,2)->intData;
				gmData->authority = res->getFieldData(row,3)->intData;
				dataSet[gmData->gmId] = gmData;
			}
			 
			return true;
		}

		return false;
	}

}


