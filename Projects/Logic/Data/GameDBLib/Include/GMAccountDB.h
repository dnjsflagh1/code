/******************************************************************************/
#ifndef _GMACCOUNTDB_H_
#define _GMACCOUNTDB_H_
/******************************************************************************/

#define  GM_ACCOUNT_TABLE_NAME	"gm_account_info"
#include <CommonGameDefine.h>
/******************************************************************************/
namespace MG
{
	struct GMClientInfo;
    class GMAccountDBOp
    {
    public:
		static Bool checkOrCreateGMAccountTable(DBDriver& driver);
		static Bool	createGMAccount(DBDriver& driver,Char16* accountName,Char16* psw,Int authority,AccountIdType& accountId );
		static Bool checkGMAccount(DBDriver& driver,IdType& accountId,Char16* accountName,Char16* accountPsw);
		static Bool selectGMAccountList(DBDriver& driver,std::map<U32,GMClientInfo*>& dataSet);
    };

}

/******************************************************************************/

#endif