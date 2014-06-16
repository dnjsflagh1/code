//**********************************************************************************************************
#ifndef _H_ITEMDBOP_
#define _H_ITEMDBOP_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
#include "PlayerItem.h"
//**********************************************************************************************************
#define ITEMDB_TABLE_NAME   "itemdb_info"
//**********************************************************************************************************
namespace MG
{
    class ItemDBOp
    {
    public:
        static Bool checkOrCreateItemDBTable(DBDriver& driver);
        static Bool getItemDB(DBDriver& driver, const U64& clanID, const ITEM_BELONG_TYPE& type, std::vector<ItemRecord>& recordList);
        static Bool insertItemDB( DBDriver& driver, U64& itemDBID );

        static Bool updateItemDBNum(DBDriver& driver, const U64& itemDBID, const U8 num);
        static Bool updateItemDBPos(DBDriver& driver, const U64& itemDBID, const U8 belongPos);
        static Bool updateItemDBIndex(DBDriver& driver, const U64& itemDBID, const U32& Index, const U8& belongPos);
        static Bool updateItemDBInfo(DBDriver& driver, const U64& itemDBID, const ItemRecord* itemDBdata);
        //以后会添加其他更新方法。
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************