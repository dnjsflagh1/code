/******************************************************************************/
#include "stdafx.h"
#include "CommonGameDBOp.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    void CommonGameDBOp::lockTable(DBDriver& driver, Char16* tableName, Bool lockWrite, Bool lockRead)
    {
        //lock tables 'tablename' write
    }
    
    //-----------------------------------------------------------------------
    void CommonGameDBOp::unLockTable(DBDriver& driver, Char16* tableName)
    {
        //unlock tables 'tablename'
    }

    //-----------------------------------------------------------------------
    U64 CommonGameDBOp::getLastInsertID(DBDriver& driver, Bool isCheckLock)
    {
        U64 mainId = 0;
        DBQueryResultEx resEx = driver.query("select LAST_INSERT_ID()",isCheckLock);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            mainId = res->getFieldData(0, 0)->ulonglongData;
        }
        return mainId;
    }
}