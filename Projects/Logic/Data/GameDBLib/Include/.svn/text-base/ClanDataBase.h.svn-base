/******************************************************************************/
#ifndef _CLANDATABASE_H_
#define _CLANDATABASE_H_
/******************************************************************************/

#define  CLANDATABASE_TABLE_NAME	"clandatabase_info"
#include <CommonGameDefine.h>
#include "Clan.h"
/******************************************************************************/
namespace MG
{
    #define  DB_RECORDS_SEPARATOR ','
    #define  DB_FIELDS_SEPARATOR '.'
    class ClanDataBaseDBOp
    {
    public:
        static Bool checkOrCreateClanDataBaseTable(DBDriver& driver);

		static Bool getClanDataBase(DBDriver& driver, const U64& accountId, std::vector<ClanData>& nameList,std::vector<dbDoingClanQuestObject>& doingQuestData,
			std::vector<FinishedClanQuestObject>& finishedQuestData, std::vector<ItemRecord>& recordList );

        
        static Bool insertClanDataBase(DBDriver& driver, U64& clandatabaseid);
        static Bool deleteClanDataBase(DBDriver& driver, const U64& clandatabaseid);

        static Bool updateClanDataBase(DBDriver& driver, const ClanData* cbDBdata, const U64& clandatabaseid);
        static Bool updateClanDataBaseStatus(DBDriver& driver, const U64& clandatabaseid, const U8& status);
        static Bool updateClanDataBaseMainGenreal(DBDriver& driver, const U64& clandatabaseid, const U64& mainGenrealId);
		static Bool updateClanDataBaseMoney(DBDriver& driver, const U64& clandatabaseid, const UInt& money);
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static Bool updateQuest(DBDriver& driver,const U64 clandatabaseid,std::map< U32 , ClanQuestObject*>* doingQuestData,
			std::map<U32,FinishedClanQuestObject*>* finishedQuestData);
		static Bool updateClanItem(DBDriver& driver,const U64 clandatabaseid,std::vector<PlayerItem*>* clanItemList);

	protected:
        //','为记录分割符 '.'为记录的字段分隔符
		static void loadQuest(const Str16& dbQuestDoingRecordString,const Str16& dbQuestFinishedRecordString,std::vector<dbDoingClanQuestObject>& doingQuestData,
			std::vector<FinishedClanQuestObject>& finishedQuestData);
		static   void loadClanItem(const Str8 dbClanItemRecordString,std::vector<ItemRecord>& recordList);

    };
}

/******************************************************************************/

#endif