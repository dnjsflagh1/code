/******************************************************************************/
#ifndef _CLAN_DB_SYSTEM_H_
#define _CLAN_DB_SYSTEM_H_
/******************************************************************************/


#include <CommonGameDefine.h>
#include "Clan.h"

/******************************************************************************/
//表名字
#define  CLANDATABASE_TABLE_NAME	"clandatabase_info"

//定义列 名字
#define AccountId			"Account_Id"
#define Clan_Id				"Clan_Id"
//#define Genreal_Id_List 	"Genreal_Id_List"	
#define MainGenereal_id 	"MainGenereal_id"	
#define Region_Id 			"Region_Id"
#define Region_Type 		"Region_Type"
#define Status 				"Status"
#define Ancestry 			"Ancestry"
#define Homeland_Name 		"Homeland_Name"	
#define Name 				"Name"
#define Blem 				"Blem"
#define Blem_color 			"Blem_color"
#define BackGroud 			"BackGroud"
#define BackGroud_color 	"BackGroud_color"	
#define Login_num 			"Login_num"
#define Clanbag_size 		"Clanbag_size"	
#define Quest_doing 		"Quest_doing"	
#define Quest_finished 		"Quest_finished"
#define Bag_item 			"Bag_item"
#define money 				"money"	

enum ClanDBRow
{
	ClanDBRow_AccountId,
	ClanDBRow_Clan_Id,
	//ClanDBRow_Genreal_Id_List,
	ClanDBRow_MainGenereal_id,
	ClanDBRow_Region_Id,
	ClanDBRow_Region_Type,
	ClanDBRow_Status,
	ClanDBRow_Ancestry,
	ClanDBRow_Homeland_Name,
	ClanDBRow_Name,
	ClanDBRow_Blem,
	ClanDBRow_Blem_color,
	ClanDBRow_BackGroud,
	ClanDBRow_BackGroud_color,
	ClanDBRow_Login_num,
	ClanDBRow_Clanbag_size,
	ClanDBRow_Quest_doing,
	ClanDBRow_Quest_finished,
	ClanDBRow_Bag_item,
	ClanDBRow_money,

	ClanDBRow_Max
};
/******************************************************************************/
namespace MG
{
#define  DB_RECORDS_SEPARATOR ','
#define  DB_FIELDS_SEPARATOR '.'
	class ClanDBSystem
	{
	public:
		static Bool checkOrCreateClanDataBaseTable(DBDriver* driver);

		static Bool getClanDataBase(DBDriver* driver, 
									AccountIdType accountId, 
									std::vector<ClanData>				*	clanDataList,
									std::vector<dbDoingClanQuestObject>	*	doingQuestData,
									std::vector<FinishedClanQuestObject>*	finishedQuestData, 
									std::vector<ItemRecord>				*	recordList );

		static Bool insertClanDataBase(DBDriver* driver, const ClanData* clanData);
		static Bool deleteClanDataBase(DBDriver* driver, AccountIdType accountId, ClanIdType clanId);
		static Bool updateClanDataBase(DBDriver* driver, const ClanData* clanData);

	private:
		//','为记录分割符 '.'为记录的字段分隔符
		static void loadQuest(const Str16& dbQuestDoingRecordString,
							  const Str16& dbQuestFinishedRecordString,
							  std::vector<dbDoingClanQuestObject>* doingQuestData,
							  std::vector<FinishedClanQuestObject>* finishedQuestData);

		static void loadClanItem(const Str8 dbClanItemRecordString,std::vector<ItemRecord>* recordList);
	};
}

/******************************************************************************/

#endif	//_CLAN_DB_SYSTEM_H_