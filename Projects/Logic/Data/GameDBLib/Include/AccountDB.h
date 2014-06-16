/******************************************************************************/
#ifndef _ACCOUNTDB_H_
#define _ACCOUNTDB_H_
/******************************************************************************/

#define  ACCOUNT_TABLE_NAME	"account_info"
#include <CommonGameDefine.h>
#include "Player.h"
/******************************************************************************/
namespace MG
{
    class AccountDBOp
    {
    public:
		static Bool checkOrCreateAccountTable(DBDriver& driver);
		static Bool selectAccountByName(DBDriver& driver,Char16* accountName,AccountIdType& accountId);
		static Bool	createAccount(DBDriver& driver,Char16* accountName,Char16* psw,AccountIdType& accountId);
		static Bool checkAccount(DBDriver& driver,IdType& accountId,Char16* accountName,Char16* accountPsw);
        static Bool createAccount(DBDriver& driver, Player& accountDB, U64& accountid);
        static Bool createActiveAccount(DBDriver& driver, Player& accountDB);
        static Bool getActiveAccountsNameMap(DBDriver& driver, std::map<Str,Player>& nameList);
    };

}

/******************************************************************************/

#endif