//**********************************************************************************************************
#ifndef _H_CD_DBOP_
#define _H_CD_DBOP_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
#include "CDTimer.h"
//**********************************************************************************************************
#define CDDB_TABLE_NAME   "cddb_info"
//**********************************************************************************************************
namespace MG
{
    class CDDBOp
    {
    public:
        static Bool checkOrCreateCDDBTable(DBDriver& driver);

        static Bool getCDDBList(DBDriver& driver, const IdType& masterID, const CD_MASTER_TYPE& masterType,  std::vector<CDDBData>& CDList);
        static Bool insertCDDB( DBDriver& driver, IdType masterID, CD_MASTER_TYPE masterType, U32 CDtempID, U32 lastTime );
        static Bool checkCDDBExist(DBDriver& driver, const IdType& masterID, const CD_MASTER_TYPE& masterType,  U32 CDtempID);

        //update
        static Bool updateCDDB(DBDriver& driver, IdType masterID, CD_MASTER_TYPE masterType, U32 CDtempID, U32 lastTime);
        //以后会添加其他更新方法。
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************